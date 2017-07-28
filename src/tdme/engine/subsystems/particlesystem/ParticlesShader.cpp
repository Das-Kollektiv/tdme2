// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/ParticlesShader.java
#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/TextureLoader.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::particlesystem::ParticlesShader;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::Engine;
using tdme::engine::fileio::textures::TextureLoader;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;

ParticlesShader::ParticlesShader(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ParticlesShader::ParticlesShader(Engine* engine, GLRenderer* renderer) 
	: ParticlesShader(*static_cast< ::default_init_tag* >(0))
{
	ctor(engine,renderer);
}

void ParticlesShader::ctor(Engine* engine, GLRenderer* renderer)
{
	super::ctor();
	this->engine = engine;
	this->renderer = renderer;
	isRunning = false;
	initialized = false;
	mvpMatrix = new Matrix4x4();
}

bool ParticlesShader::isInitialized()
{
	return initialized;
}

void ParticlesShader::initialize()
{
	auto rendererVersion = renderer->getGLVersion();
	renderFragmentShaderId = renderer->loadShader(renderer->SHADER_FRAGMENT_SHADER, ::java::lang::StringBuilder().append(u"shader/"_j)->append(rendererVersion)
		->append(u"/particles"_j)->toString(), u"render_fragmentshader.c"_j);
	if (renderFragmentShaderId == 0)
		return;

	renderVertexShaderId = renderer->loadShader(renderer->SHADER_VERTEX_SHADER, ::java::lang::StringBuilder().append(u"shader/"_j)->append(rendererVersion)
		->append(u"/particles"_j)->toString(), u"render_vertexshader.c"_j);
	if (renderVertexShaderId == 0)
		return;

	renderProgramId = renderer->createProgram();
	renderer->attachShaderToProgram(renderProgramId, renderVertexShaderId);
	renderer->attachShaderToProgram(renderProgramId, renderFragmentShaderId);
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(renderProgramId, 0, u"inVertex"_j);
		renderer->setProgramAttributeLocation(renderProgramId, 3, u"inColor"_j);
	}
	if (renderer->linkProgram(renderProgramId) == false)
		return;

	uniformMVPMatrix = renderer->getProgramUniformLocation(renderProgramId, u"mvpMatrix"_j);
	if (uniformMVPMatrix == -1)
		return;

	uniformMVMatrix = renderer->getProgramUniformLocation(renderProgramId, u"mvMatrix"_j);
	if (uniformMVMatrix == -1)
		return;

	uniformPointSize = renderer->getProgramUniformLocation(renderProgramId, u"pointSize"_j);
	if (uniformPointSize == -1)
		return;

	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(renderProgramId, u"diffuseTextureUnit"_j);
	if (uniformDiffuseTextureUnit == -1)
		return;

	uniformEffectColorMul = renderer->getProgramUniformLocation(renderProgramId, u"effectColorMul"_j);
	if (uniformEffectColorMul == -1)
		return;

	uniformEffectColorAdd = renderer->getProgramUniformLocation(renderProgramId, u"effectColorAdd"_j);
	if (uniformEffectColorAdd == -1)
		return;

	pointTextureId = engine->getTextureManager()->addTexture(TextureLoader::loadTexture(L"resources/textures", L"point.png"));
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

	renderer->setProgramUniformFloatVec4(uniformEffectColorMul, &renderer->effectColorMul);
	renderer->setProgramUniformFloatVec4(uniformEffectColorAdd, &renderer->effectColorAdd);
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

	mvpMatrix->set(renderer->getModelViewMatrix())->multiply(renderer->getProjectionMatrix());
	renderer->setProgramUniformFloatMatrix4x4(uniformMVPMatrix, mvpMatrix->getArray());
	renderer->setProgramUniformFloatMatrix4x4(uniformMVMatrix, renderer->getModelViewMatrix()->getArray());
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ParticlesShader::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.particlesystem.ParticlesShader", 53);
    return c;
}

java::lang::Class* ParticlesShader::getClass0()
{
	return class_();
}

