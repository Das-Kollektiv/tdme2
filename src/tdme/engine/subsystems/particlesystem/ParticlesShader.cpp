#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::Engine;
using tdme::engine::fileio::textures::TextureLoader;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;

ParticlesShader::ParticlesShader(Engine* engine, GLRenderer* renderer) 
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
	auto rendererVersion = renderer->getGLVersion();
	// particles
	//	fragment shader
	renderFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + rendererVersion + "/particles",
		"render_fragmentshader.c"
	);
	if (renderFragmentShaderId == 0)
		return;
	//	vertex shader
	renderVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + rendererVersion + "/particles",
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
	uniformMVMatrix = renderer->getProgramUniformLocation(renderProgramId, "mvMatrix");
	if (uniformMVMatrix == -1)
		return;
	uniformPointSize = renderer->getProgramUniformLocation(renderProgramId, "pointSize");
	if (uniformPointSize == -1)
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

void ParticlesShader::useProgram()
{
	isRunning = true;
	renderer->useProgram(renderProgramId);
	renderer->setProgramUniformInteger(uniformDiffuseTextureUnit, 0);
	renderer->setProgramUniformFloat(uniformPointSize, renderer->pointSize);
}

void ParticlesShader::updateEffect(GLRenderer* renderer)
{
	// skip if not running
	if (isRunning == false)
		return;
	// effect color
	renderer->setProgramUniformFloatVec4(uniformEffectColorMul, renderer->effectColorMul);
	renderer->setProgramUniformFloatVec4(uniformEffectColorAdd, renderer->effectColorAdd);
}

void ParticlesShader::unUseProgram()
{
	isRunning = false;
	renderer->bindTexture(renderer->ID_NONE);
}

void ParticlesShader::updateMatrices(GLRenderer* renderer)
{
	// skip if not running
	if (isRunning == false)
		return;
	// object to screen matrix
	mvpMatrix.set(renderer->getModelViewMatrix()).multiply(renderer->getProjectionMatrix());
	// upload matrices
	renderer->setProgramUniformFloatMatrix4x4(uniformMVPMatrix, mvpMatrix.getArray());
	renderer->setProgramUniformFloatMatrix4x4(uniformMVMatrix, renderer->getModelViewMatrix().getArray());
}

void ParticlesShader::setParameters(int32_t textureId, float pointSize) {
	renderer->setProgramUniformFloat(uniformPointSize, renderer->pointSize * pointSize);
	renderer->bindTexture(textureId);
}
