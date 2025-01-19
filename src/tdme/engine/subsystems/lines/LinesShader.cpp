#include <tdme/engine/subsystems/lines/LinesShader.h>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::lines::LinesShader;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;

LinesShader::LinesShader(Engine* engine, RendererBackend* rendererBackend)
{
	this->engine = engine;
	this->rendererBackend = rendererBackend;
	isRunning = false;
	initialized = false;
}

bool LinesShader::isInitialized()
{
	return initialized;
}

void LinesShader::initialize()
{
	auto shaderVersion = rendererBackend->getShaderVersion();
	// particles
	//	fragment shader
	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/lines",
		"render_fragmentshader.frag"
	);
	if (fragmentShaderId == 0)
		return;
	//	vertex shader
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/lines",
		"render_vertexshader.vert"
	);
	if (vertexShaderId == 0)
		return;
	// create, attach and link program
	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_LINES);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);
	// map inputs to attributes
	if (rendererBackend->isUsingProgramAttributeLocation() == true) {
		rendererBackend->setProgramAttributeLocation(programId, 0, "inVertex");
		rendererBackend->setProgramAttributeLocation(programId, 3, "inColor");
	}
	// link program
	if (rendererBackend->linkProgram(programId) == false)
		return;

	// get uniforms
	uniformMVPMatrix = rendererBackend->getProgramUniformLocation(programId, "mvpMatrix");
	if (uniformMVPMatrix == -1)
		return;
	uniformDiffuseTextureUnit = rendererBackend->getProgramUniformLocation(programId, "diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1)
		return;
	uniformEffectColorMul = rendererBackend->getProgramUniformLocation(programId, "effectColorMul");
	if (uniformEffectColorMul == -1)
		return;
	uniformEffectColorAdd = rendererBackend->getProgramUniformLocation(programId, "effectColorAdd");
	if (uniformEffectColorAdd == -1)
		return;
	initialized = true;
}

void LinesShader::useProgram(int contextIdx)
{
	isRunning = true;
	rendererBackend->useProgram(contextIdx, programId);
	rendererBackend->setLighting(contextIdx, rendererBackend->LIGHTING_NONE);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformDiffuseTextureUnit, 0);
}

void LinesShader::updateEffect(int contextIdx)
{
	// skip if not running
	if (isRunning == false)
		return;
	// effect color
	rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformEffectColorMul, rendererBackend->getEffectColorMul(contextIdx));
	rendererBackend->setProgramUniformFloatVec4(contextIdx, uniformEffectColorAdd, rendererBackend->getEffectColorAdd(contextIdx));
}

void LinesShader::unUseProgram(int contextIdx)
{
	isRunning = false;
	rendererBackend->setLineWidth(1.0f);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
}

void LinesShader::updateMatrices(int contextIdx)
{
	// skip if not running
	if (isRunning == false)
		return;
	// object to screen matrix
	mvpMatrix.set(rendererBackend->getModelViewMatrix()).multiply(rendererBackend->getProjectionMatrix());
	// upload matrices
	rendererBackend->setProgramUniformFloatMatrix4x4(contextIdx, uniformMVPMatrix, mvpMatrix.getArray());
}

void LinesShader::setParameters(int contextIdx, int32_t textureId, float lineWidth) {
	rendererBackend->setLineWidth(lineWidth);
	rendererBackend->bindTexture(contextIdx, textureId);
}
