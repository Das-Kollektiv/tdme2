#include <tdme/engine/subsystems/lines/LinesShader.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::lines::LinesShader;
using tdme::engine::Engine;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix4x4;

LinesShader::LinesShader(Engine* engine, Renderer* renderer)
{
	this->engine = engine;
	this->renderer = renderer;
	isRunning = false;
	initialized = false;
}

bool LinesShader::isInitialized()
{
	return initialized;
}

void LinesShader::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();
	// particles
	//	fragment shader
	renderFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lines",
		"render_fragmentshader.c"
	);
	if (renderFragmentShaderId == 0)
		return;
	//	vertex shader
	renderVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lines",
		"render_vertexshader.c"
	);
	if (renderVertexShaderId == 0)
		return;
	// create, attach and link program
	renderProgramId = renderer->createProgram();
	renderer->attachShaderToProgram(renderProgramId, renderVertexShaderId);
	renderer->attachShaderToProgram(renderProgramId, renderFragmentShaderId);
	// map inputs to attributes
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(renderProgramId, 0, "inVertex");
		renderer->setProgramAttributeLocation(renderProgramId, 3, "inColor");
	}
	// link program
	if (renderer->linkProgram(renderProgramId) == false)
		return;

	// get uniforms
	uniformMVPMatrix = renderer->getProgramUniformLocation(renderProgramId, "mvpMatrix");
	if (uniformMVPMatrix == -1)
		return;
	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(renderProgramId, "diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1)
		return;
	uniformEffectColorMul = renderer->getProgramUniformLocation(renderProgramId, "effectColorMul");
	if (uniformEffectColorMul == -1)
		return;
	uniformEffectColorAdd = renderer->getProgramUniformLocation(renderProgramId, "effectColorAdd");
	if (uniformEffectColorAdd == -1)
		return;
	initialized = true;
}

void LinesShader::useProgram(void* context)
{
	isRunning = true;
	renderer->useProgram(renderProgramId);
	renderer->setProgramUniformInteger(context, uniformDiffuseTextureUnit, 0);
}

void LinesShader::updateEffect(Renderer* renderer, void* context)
{
	// skip if not running
	if (isRunning == false)
		return;
	// effect color
	renderer->setProgramUniformFloatVec4(context, uniformEffectColorMul, renderer->getEffectColorMul(context));
	renderer->setProgramUniformFloatVec4(context, uniformEffectColorAdd, renderer->getEffectColorAdd(context));
}

void LinesShader::unUseProgram(void* context)
{
	isRunning = false;
	renderer->setLineWidth(1.0f);
	renderer->bindTexture(context, renderer->ID_NONE);
}

void LinesShader::updateMatrices(Renderer* renderer, void* context)
{
	// skip if not running
	if (isRunning == false)
		return;
	// object to screen matrix
	mvpMatrix.set(renderer->getModelViewMatrix()).multiply(renderer->getProjectionMatrix());
	// upload matrices
	renderer->setProgramUniformFloatMatrix4x4(context, uniformMVPMatrix, mvpMatrix.getArray());
}

void LinesShader::setParameters(void* context, int32_t textureId, float lineWidth) {
	renderer->setLineWidth(lineWidth);
	renderer->bindTexture(context, textureId);
}
