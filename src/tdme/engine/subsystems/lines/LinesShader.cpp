#include <tdme/engine/subsystems/lines/LinesShader.h>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::lines::LinesShader;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
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
	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lines",
		"render_fragmentshader.frag"
	);
	if (fragmentShaderId == 0)
		return;
	//	vertex shader
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lines",
		"render_vertexshader.vert"
	);
	if (vertexShaderId == 0)
		return;
	// create, attach and link program
	programId = renderer->createProgram(renderer->PROGRAM_LINES);
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);
	// map inputs to attributes
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(programId, 0, "inVertex");
		renderer->setProgramAttributeLocation(programId, 3, "inColor");
	}
	// link program
	if (renderer->linkProgram(programId) == false)
		return;

	// get uniforms
	uniformMVPMatrix = renderer->getProgramUniformLocation(programId, "mvpMatrix");
	if (uniformMVPMatrix == -1)
		return;
	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(programId, "diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1)
		return;
	uniformEffectColorMul = renderer->getProgramUniformLocation(programId, "effectColorMul");
	if (uniformEffectColorMul == -1)
		return;
	uniformEffectColorAdd = renderer->getProgramUniformLocation(programId, "effectColorAdd");
	if (uniformEffectColorAdd == -1)
		return;
	initialized = true;
}

void LinesShader::useProgram(int contextIdx)
{
	isRunning = true;
	renderer->useProgram(contextIdx, programId);
	renderer->setLighting(contextIdx, renderer->LIGHTING_NONE);
	renderer->setProgramUniformInteger(contextIdx, uniformDiffuseTextureUnit, 0);
}

void LinesShader::updateEffect(int contextIdx)
{
	// skip if not running
	if (isRunning == false)
		return;
	// effect color
	renderer->setProgramUniformFloatVec4(contextIdx, uniformEffectColorMul, renderer->getEffectColorMul(contextIdx));
	renderer->setProgramUniformFloatVec4(contextIdx, uniformEffectColorAdd, renderer->getEffectColorAdd(contextIdx));
}

void LinesShader::unUseProgram(int contextIdx)
{
	isRunning = false;
	renderer->setLineWidth(1.0f);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
}

void LinesShader::updateMatrices(int contextIdx)
{
	// skip if not running
	if (isRunning == false)
		return;
	// object to screen matrix
	mvpMatrix.set(renderer->getModelViewMatrix()).multiply(renderer->getProjectionMatrix());
	// upload matrices
	renderer->setProgramUniformFloatMatrix4x4(contextIdx, uniformMVPMatrix, mvpMatrix.getArray());
}

void LinesShader::setParameters(int contextIdx, int32_t textureId, float lineWidth) {
	renderer->setLineWidth(lineWidth);
	renderer->bindTexture(contextIdx, textureId);
}
