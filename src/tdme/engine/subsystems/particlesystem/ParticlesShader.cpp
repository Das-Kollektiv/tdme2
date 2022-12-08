#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/TextureAtlas.h>

using tdme::engine::Texture;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;
using tdme::utilities::TextureAtlas;

ParticlesShader::ParticlesShader(Engine* engine, Renderer* renderer)
{
	this->engine = engine;
	this->renderer = renderer;
	isRunning = false;
	initialized = false;
}

bool ParticlesShader::isInitialized()
{
	return initialized;
}

void ParticlesShader::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();
	// particles
	//	vertex shader
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/particles",
		"render_vertexshader.vert",
		string() +
			"#define HAVE_DEPTH_FOG\n" +
			"#define ATLASTEXTURE_COUNT " + to_string(ATLASTEXTURE_COUNT) + "\n"
	);
	if (vertexShaderId == 0) return;
	//	fragment shader
	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/particles",
		"render_fragmentshader.frag",
		string() +
			"#define HAVE_DEPTH_FOG\n" +
			"#define ATLASTEXTURE_COUNT " + to_string(ATLASTEXTURE_COUNT) + "\n"
	);
	if (fragmentShaderId == 0) return;
	// create, attach and link program
	programId = renderer->createProgram(renderer->PROGRAM_POINTS);
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);
	// map inputs to attributes
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(programId, 0, "inVertex");
		renderer->setProgramAttributeLocation(programId, 1, "inTextureSpriteIndex");
		renderer->setProgramAttributeLocation(programId, 3, "inColor");
		renderer->setProgramAttributeLocation(programId, 5, "inPointSize");
		renderer->setProgramAttributeLocation(programId, 6, "inSpriteSheetDimensions");
		renderer->setProgramAttributeLocation(programId, 10, "inEffectColorMul");
		renderer->setProgramAttributeLocation(programId, 11, "inEffectColorAdd");
	}
	// link program
	if (renderer->linkProgram(programId) == false) return;

	// get uniforms
	uniformMVPMatrix = renderer->getProgramUniformLocation(programId, "mvpMatrix");
	if (uniformMVPMatrix == -1) return;

	// TODO: use ivec2 and vec2
	uniformViewPortWidth = renderer->getProgramUniformLocation(programId, "viewPortWidth");
	if (uniformViewPortWidth == -1) return;
	uniformViewPortHeight = renderer->getProgramUniformLocation(programId, "viewPortHeight");
	if (uniformViewPortHeight == -1) return;
	uniformProjectionMatrixXx = renderer->getProgramUniformLocation(programId, "projectionMatrixXx");
	if (uniformProjectionMatrixXx == -1) return;
	uniformProjectionMatrixYy = renderer->getProgramUniformLocation(programId, "projectionMatrixYy");
	if (uniformProjectionMatrixYy == -1) return;

	//
	uniformTextureAtlasTextureUnit = renderer->getProgramUniformLocation(programId, "textureAtlasTextureUnit");
	if (uniformTextureAtlasTextureUnit == -1) return;

	//
	for (auto i = 0; i < ATLASTEXTURE_COUNT; i++) {
		uniformAtlasTextureOrientation[i] = renderer->getProgramUniformLocation(programId, "atlasTextures[" + to_string(i) + "].orientation");
		if (uniformAtlasTextureOrientation[i] == -1) return;
		uniformAtlasTexturePosition[i] = renderer->getProgramUniformLocation(programId, "atlasTextures[" + to_string(i) + "].position");
		if (uniformAtlasTexturePosition[i] == -1) return;
		uniformAtlasTextureDimension[i] = renderer->getProgramUniformLocation(programId, "atlasTextures[" + to_string(i) + "].dimension");
		if (uniformAtlasTextureDimension[i] == -1) return;
	}

	//
	initialized = true;
}

void ParticlesShader::useProgram(int contextIdx)
{
	isRunning = true;
	renderer->useProgram(contextIdx, programId);
	renderer->setLighting(contextIdx, renderer->LIGHTING_NONE);
	renderer->setProgramUniformInteger(contextIdx, uniformTextureAtlasTextureUnit, 0);
}

void ParticlesShader::updateEffect(int contextIdx)
{
	// skip if not running
	if (isRunning == false) return;
}

void ParticlesShader::unUseProgram(int contextIdx)
{
	isRunning = false;
	renderer->setTextureUnit(contextIdx, 0);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
}

void ParticlesShader::updateMatrices(int contextIdx)
{
	// skip if not running
	if (isRunning == false) return;
	// object to screen matrix
	mvpMatrix.set(renderer->getModelViewMatrix()).multiply(renderer->getProjectionMatrix());
	renderer->setProgramUniformFloatMatrix4x4(contextIdx, uniformMVPMatrix, mvpMatrix.getArray());
	renderer->setProgramUniformFloat(contextIdx, uniformProjectionMatrixXx, renderer->getProjectionMatrix().getArray()[0]);
	renderer->setProgramUniformFloat(contextIdx, uniformProjectionMatrixYy, renderer->getProjectionMatrix().getArray()[5]);
	renderer->setProgramUniformInteger(contextIdx, uniformViewPortWidth, renderer->getViewPortWidth());
	renderer->setProgramUniformInteger(contextIdx, uniformViewPortHeight, renderer->getViewPortHeight());
}

void ParticlesShader::setTextureAtlas(int contextIdx, TextureAtlas* textureAtlas) {
	if (textureAtlas->isRequiringUpdate() == true) {
		textureAtlas->update();
		if (textureAtlas->getAtlasTexture() != nullptr) {
			if (ppsTextureAtlasTextureId == renderer->ID_NONE) ppsTextureAtlasTextureId = renderer->createTexture();
			renderer->bindTexture(contextIdx, ppsTextureAtlasTextureId);
			renderer->uploadTexture(contextIdx, textureAtlas->getAtlasTexture());
		} else
		if (ppsTextureAtlasTextureId != renderer->ID_NONE) {
			renderer->disposeTexture(ppsTextureAtlasTextureId);
			ppsTextureAtlasTextureId = renderer->ID_NONE;
		}
	}

	//
	auto textureAtlasTexture = textureAtlas->getAtlasTexture();
	if (textureAtlasTexture == nullptr) return;

	//
	auto textureAtlasTextureWidth = textureAtlasTexture->getTextureWidth();
	auto textureAtlasTextureHeight = textureAtlasTexture->getTextureHeight();
	renderer->bindTexture(contextIdx, ppsTextureAtlasTextureId);
	for (auto atlasTextureIdx = 0; atlasTextureIdx < ATLASTEXTURE_COUNT; atlasTextureIdx++) {
		auto atlasTexture = textureAtlas->getAtlasTexture(atlasTextureIdx);
		if (atlasTexture == nullptr) break;
		renderer->setProgramUniformInteger(contextIdx, uniformAtlasTextureOrientation[atlasTextureIdx], atlasTexture->orientation);
		renderer->setProgramUniformFloatVec2(
			contextIdx,
			uniformAtlasTexturePosition[atlasTextureIdx],
			{
				static_cast<float>(atlasTexture->left) / static_cast<float>(textureAtlasTextureWidth),
				static_cast<float>(atlasTexture->top) / static_cast<float>(textureAtlasTextureHeight)
			}
		);
		renderer->setProgramUniformFloatVec2(
			contextIdx,
			uniformAtlasTextureDimension[atlasTextureIdx],
			{
				static_cast<float>(atlasTexture->width) / static_cast<float>(textureAtlasTextureWidth),
				static_cast<float>(atlasTexture->height) / static_cast<float>(textureAtlasTextureHeight)
			}
		);
	}
}
