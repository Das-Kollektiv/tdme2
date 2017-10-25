#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/TextureLoader.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
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
	renderFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + rendererVersion + "/particles",
		"render_fragmentshader.c"
	);
	if (renderFragmentShaderId == 0)
		return;

	renderVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + rendererVersion + "/particles",
		"render_vertexshader.c"
	);
	if (renderVertexShaderId == 0)
		return;

	renderProgramId = renderer->createProgram();
	renderer->attachShaderToProgram(renderProgramId, renderVertexShaderId);
	renderer->attachShaderToProgram(renderProgramId, renderFragmentShaderId);
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(renderProgramId, 0, "inVertex");
		renderer->setProgramAttributeLocation(renderProgramId, 3, "inColor");
	}
	if (renderer->linkProgram(renderProgramId) == false)
		return;

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

	pointTextureId = engine->getTextureManager()->addTexture(TextureLoader::loadTexture("resources/textures", "point.png"));
	initialized = true;
}

void ParticlesShader::useProgram()
{
	isRunning = true;
	renderer->useProgram(renderProgramId);
	renderer->setProgramUniformInteger(uniformDiffuseTextureUnit, 0);
	renderer->setProgramUniformFloat(uniformPointSize, renderer->pointSize);
	renderer->bindTexture(pointTextureId);
}

void ParticlesShader::updateEffect(GLRenderer* renderer)
{
	if (isRunning == false)
		return;

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
	if (isRunning == false)
		return;

	mvpMatrix.set(renderer->getModelViewMatrix()).multiply(renderer->getProjectionMatrix());
	renderer->setProgramUniformFloatMatrix4x4(uniformMVPMatrix, mvpMatrix.getArray());
	renderer->setProgramUniformFloatMatrix4x4(uniformMVMatrix, renderer->getModelViewMatrix().getArray());
}
