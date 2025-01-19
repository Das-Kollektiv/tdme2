#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/TextureAtlas.h>

using tdme::engine::Texture;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;
using tdme::utilities::TextureAtlas;

ParticlesShader::ParticlesShader(Engine* engine, RendererBackend* rendererBackend)
{
	this->engine = engine;
	this->rendererBackend = rendererBackend;
	isRunning = false;
	initialized = false;
}

bool ParticlesShader::isInitialized()
{
	return initialized;
}

void ParticlesShader::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();
	// particles
	//	vertex shader
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/particles",
		"render_vertexshader.vert",
		string() +
			"#define HAVE_DEPTH_FOG\n" +
			"#define ATLASTEXTURE_COUNT " + to_string(ATLASTEXTURE_COUNT) + "\n"
	);
	if (vertexShaderId == 0) return;
	//	fragment shader
	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/particles",
		"render_fragmentshader.frag",
		string() +
			"#define HAVE_DEPTH_FOG\n" +
			"#define ATLASTEXTURE_COUNT " + to_string(ATLASTEXTURE_COUNT) + "\n"
	);
	if (fragmentShaderId == 0) return;
	// create, attach and link program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_POINTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);
	// map inputs to attributes
	if (rendererBackend->isUsingProgramAttributeLocation() == true) {
		rendererBackend->setProgramAttributeLocation(programId, 0, "inVertex");
		rendererBackend->setProgramAttributeLocation(programId, 1, "inTextureSpriteIndex");
		rendererBackend->setProgramAttributeLocation(programId, 3, "inColor");
		rendererBackend->setProgramAttributeLocation(programId, 5, "inPointSize");
		rendererBackend->setProgramAttributeLocation(programId, 6, "inSpriteSheetDimensions");
		rendererBackend->setProgramAttributeLocation(programId, 10, "inEffectColorMul");
		rendererBackend->setProgramAttributeLocation(programId, 11, "inEffectColorAdd");
	}
	// link program
	if (rendererBackend->linkProgram(programId) == false) return;

	// get uniforms
	uniformMVPMatrix = rendererBackend->getProgramUniformLocation(programId, "mvpMatrix");
	if (uniformMVPMatrix == -1) return;

	// TODO: use ivec2 and vec2
	uniformViewPortWidth = rendererBackend->getProgramUniformLocation(programId, "viewPortWidth");
	if (uniformViewPortWidth == -1) return;
	uniformViewPortHeight = rendererBackend->getProgramUniformLocation(programId, "viewPortHeight");
	if (uniformViewPortHeight == -1) return;
	uniformProjectionMatrixXx = rendererBackend->getProgramUniformLocation(programId, "projectionMatrixXx");
	if (uniformProjectionMatrixXx == -1) return;
	uniformProjectionMatrixYy = rendererBackend->getProgramUniformLocation(programId, "projectionMatrixYy");
	if (uniformProjectionMatrixYy == -1) return;

	//
	uniformTextureAtlasTextureUnit = rendererBackend->getProgramUniformLocation(programId, "textureAtlasTextureUnit");
	if (uniformTextureAtlasTextureUnit == -1) return;

	//
	for (auto i = 0; i < ATLASTEXTURE_COUNT; i++) {
		uniformAtlasTextureOrientation[i] = rendererBackend->getProgramUniformLocation(programId, "atlasTextures[" + to_string(i) + "].orientation");
		if (uniformAtlasTextureOrientation[i] == -1) return;
		uniformAtlasTexturePosition[i] = rendererBackend->getProgramUniformLocation(programId, "atlasTextures[" + to_string(i) + "].position");
		if (uniformAtlasTexturePosition[i] == -1) return;
		uniformAtlasTextureDimension[i] = rendererBackend->getProgramUniformLocation(programId, "atlasTextures[" + to_string(i) + "].dimension");
		if (uniformAtlasTextureDimension[i] == -1) return;
	}

	//
	initialized = true;
}

void ParticlesShader::useProgram(int contextIdx)
{
	isRunning = true;
	rendererBackend->useProgram(contextIdx, programId);
	rendererBackend->setLighting(contextIdx, rendererBackend->LIGHTING_NONE);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformTextureAtlasTextureUnit, 0);
}

void ParticlesShader::updateEffect(int contextIdx)
{
	// skip if not running
	if (isRunning == false) return;
}

void ParticlesShader::unUseProgram(int contextIdx)
{
	isRunning = false;
	rendererBackend->setTextureUnit(contextIdx, 0);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
}

void ParticlesShader::updateMatrices(int contextIdx)
{
	// skip if not running
	if (isRunning == false) return;
	// object to screen matrix
	mvpMatrix.set(rendererBackend->getModelViewMatrix()).multiply(rendererBackend->getProjectionMatrix());
	rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformMVPMatrix, mvpMatrix.getArray());
	rendererBackend->setProgramUniformFloat(contextIdx, uniformProjectionMatrixXx, rendererBackend->getProjectionMatrix().getArray()[0]);
	rendererBackend->setProgramUniformFloat(contextIdx, uniformProjectionMatrixYy, rendererBackend->getProjectionMatrix().getArray()[5]);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformViewPortWidth, rendererBackend->getViewPortWidth());
	rendererBackend->setProgramUniformInteger(contextIdx, uniformViewPortHeight, rendererBackend->getViewPortHeight());
}

void ParticlesShader::setTextureAtlas(int contextIdx, TextureAtlas* textureAtlas) {
	if (textureAtlas->isRequiringUpdate() == true) {
		textureAtlas->update();
		if (textureAtlas->getAtlasTexture() != nullptr) {
			if (ppsTextureAtlasTextureId == rendererBackend->ID_NONE) ppsTextureAtlasTextureId = rendererBackend->createTexture();
			rendererBackend->bindTexture(contextIdx, ppsTextureAtlasTextureId);
			rendererBackend->uploadTexture(contextIdx, textureAtlas->getAtlasTexture());
		} else
		if (ppsTextureAtlasTextureId != rendererBackend->ID_NONE) {
			rendererBackend->disposeTexture(ppsTextureAtlasTextureId);
			ppsTextureAtlasTextureId = rendererBackend->ID_NONE;
		}
	}

	//
	auto textureAtlasTexture = textureAtlas->getAtlasTexture();
	if (textureAtlasTexture == nullptr) return;

	//
	auto textureAtlasTextureWidth = textureAtlasTexture->getTextureWidth();
	auto textureAtlasTextureHeight = textureAtlasTexture->getTextureHeight();
	rendererBackend->bindTexture(contextIdx, ppsTextureAtlasTextureId);
	for (auto atlasTextureIdx = 0; atlasTextureIdx < ATLASTEXTURE_COUNT; atlasTextureIdx++) {
		auto atlasTexture = textureAtlas->getAtlasTexture(atlasTextureIdx);
		if (atlasTexture == nullptr) break;
		rendererBackend->setProgramUniformInteger(contextIdx, uniformAtlasTextureOrientation[atlasTextureIdx], atlasTexture->orientation);
		rendererBackend->setProgramUniformFloatVec2(
			contextIdx,
			uniformAtlasTexturePosition[atlasTextureIdx],
			{
				static_cast<float>(atlasTexture->left) / static_cast<float>(textureAtlasTextureWidth),
				static_cast<float>(atlasTexture->top) / static_cast<float>(textureAtlasTextureHeight)
			}
		);
		rendererBackend->setProgramUniformFloatVec2(
			contextIdx,
			uniformAtlasTextureDimension[atlasTextureIdx],
			{
				static_cast<float>(atlasTexture->width) / static_cast<float>(textureAtlasTextureWidth),
				static_cast<float>(atlasTexture->height) / static_cast<float>(textureAtlasTextureHeight)
			}
		);
	}
}
