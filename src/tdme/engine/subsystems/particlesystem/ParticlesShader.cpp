#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::Engine;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix4x4;

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
	//	fragment shader
	renderFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/particles",
		"render_fragmentshader.frag",
		"#define HAVE_DEPTH_FOG"
	);
	if (renderFragmentShaderId == 0) return;
	//	vertex shader
	renderVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/particles",
		"render_vertexshader.vert",
		"#define HAVE_DEPTH_FOG"
	);
	if (renderVertexShaderId == 0) return;
	// create, attach and link program
	renderProgramId = renderer->createProgram(renderer->PROGRAM_POINTS);
	renderer->attachShaderToProgram(renderProgramId, renderVertexShaderId);
	renderer->attachShaderToProgram(renderProgramId, renderFragmentShaderId);
	// map inputs to attributes
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(renderProgramId, 0, "inVertex");
		renderer->setProgramAttributeLocation(renderProgramId, 1, "inSpriteIndex");
		renderer->setProgramAttributeLocation(renderProgramId, 3, "inColor");
	}
	// link program
	if (renderer->linkProgram(renderProgramId) == false) return;

	// get uniforms
	uniformMVPMatrix = renderer->getProgramUniformLocation(renderProgramId, "mvpMatrix");
	if (uniformMVPMatrix == -1) return;
	uniformPointSize = renderer->getProgramUniformLocation(renderProgramId, "pointSize");
	if (uniformPointSize == -1) return;
	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(renderProgramId, "diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1) return;
	uniformEffectColorMul = renderer->getProgramUniformLocation(renderProgramId, "effectColorMul");
	if (uniformEffectColorMul == -1) return;
	uniformEffectColorAdd = renderer->getProgramUniformLocation(renderProgramId, "effectColorAdd");
	if (uniformEffectColorAdd == -1) return;
	uniformSpritesHorizontal = renderer->getProgramUniformLocation(renderProgramId, "spritesHorizontal");
	if (uniformSpritesHorizontal == -1) return;
	uniformSpritesVertical = renderer->getProgramUniformLocation(renderProgramId, "spritesVertical");
	if (uniformSpritesVertical == -1) return;
	uniformViewPortWidth = renderer->getProgramUniformLocation(renderProgramId, "viewPortWidth");
	if (uniformViewPortWidth == -1) return;
	uniformViewPortHeight = renderer->getProgramUniformLocation(renderProgramId, "viewPortHeight");
	if (uniformViewPortHeight == -1) return;
	uniformProjectionMatrixXx = renderer->getProgramUniformLocation(renderProgramId, "projectionMatrixXx");
	if (uniformProjectionMatrixXx == -1) return;
	uniformProjectionMatrixYy = renderer->getProgramUniformLocation(renderProgramId, "projectionMatrixYy");
	if (uniformProjectionMatrixYy == -1) return;
	initialized = true;
}

void ParticlesShader::useProgram(void* context)
{
	isRunning = true;
	renderer->useProgram(context, renderProgramId);
	renderer->setLighting(context, renderer->LIGHTING_NONE);
	renderer->setProgramUniformInteger(context, uniformDiffuseTextureUnit, 0);
}

void ParticlesShader::updateEffect(void* context)
{
	// skip if not running
	if (isRunning == false) return;
	// effect color
	renderer->setProgramUniformFloatVec4(context, uniformEffectColorMul, renderer->getEffectColorMul(context));
	renderer->setProgramUniformFloatVec4(context, uniformEffectColorAdd, renderer->getEffectColorAdd(context));
}

void ParticlesShader::unUseProgram(void* context)
{
	isRunning = false;
	renderer->bindTexture(context, renderer->ID_NONE);
}

void ParticlesShader::updateMatrices(void* context)
{
	// skip if not running
	if (isRunning == false) return;
	// object to screen matrix
	mvpMatrix.set(renderer->getModelViewMatrix()).multiply(renderer->getProjectionMatrix());
	renderer->setProgramUniformFloatMatrix4x4(context, uniformMVPMatrix, mvpMatrix.getArray());
	renderer->setProgramUniformFloat(context, uniformProjectionMatrixXx, renderer->getProjectionMatrix().getArray()[0]);
	renderer->setProgramUniformFloat(context, uniformProjectionMatrixYy, renderer->getProjectionMatrix().getArray()[5]);
	renderer->setProgramUniformInteger(context, uniformViewPortWidth, renderer->getViewPortWidth());
	renderer->setProgramUniformInteger(context, uniformViewPortHeight, renderer->getViewPortHeight());
}

void ParticlesShader::setParameters(void* context, int32_t textureId, int32_t textureSpritesHorizontal, int32_t textureSpritesVertical, float pointSize) {
	renderer->setProgramUniformFloat(context, uniformPointSize, pointSize);
	renderer->setProgramUniformInteger(context, uniformSpritesHorizontal, textureSpritesHorizontal);
	renderer->setProgramUniformInteger(context, uniformSpritesVertical, textureSpritesVertical);
	renderer->bindTexture(context, textureId);
}
