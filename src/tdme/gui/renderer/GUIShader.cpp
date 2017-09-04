// Generated from /tdme/src/tdme/gui/renderer/GUIShader.java
#include <tdme/gui/renderer/GUIShader.h>

#include <tdme/engine/subsystems/renderer/GLRenderer.h>

using tdme::gui::renderer::GUIShader;
using tdme::engine::subsystems::renderer::GLRenderer;

GUIShader::GUIShader(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIShader::GUIShader(GLRenderer* renderer) 
	: GUIShader(*static_cast< ::default_init_tag* >(0))
{
	ctor(renderer);
}

void GUIShader::ctor(GLRenderer* renderer)
{
	super::ctor();
	this->renderer = renderer;
	initialized = false;
	isRunning = false;
}

bool GUIShader::isInitialized()
{
	return initialized;
}

void GUIShader::initialize()
{
	auto rendererVersion = renderer->getGLVersion();
	vertexShaderGlId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		L"shader/" + rendererVersion + L"/gui",
		L"render_vertexshader.c"
	);
	if (vertexShaderGlId == 0)
		return;

	fragmentShaderGlId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		L"shader/" + rendererVersion + L"/gui",
		L"render_fragmentshader.c"
	);
	if (fragmentShaderGlId == 0)
		return;

	programGlId = renderer->createProgram();
	renderer->attachShaderToProgram(programGlId, vertexShaderGlId);
	renderer->attachShaderToProgram(programGlId, fragmentShaderGlId);
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(programGlId, 0, L"inVertex");
		renderer->setProgramAttributeLocation(programGlId, 2, L"inTextureUV");
		renderer->setProgramAttributeLocation(programGlId, 3, L"inColor");
	}
	if (renderer->linkProgram(programGlId) == false)
		return;

	uniformDiffuseTextureUnit = renderer->getProgramUniformLocation(programGlId, L"diffuseTextureUnit");
	if (uniformDiffuseTextureUnit == -1)
		return;

	uniformDiffuseTextureAvailable = renderer->getProgramUniformLocation(programGlId, L"diffuseTextureAvailable");
	if (uniformDiffuseTextureAvailable == -1)
		return;

	uniformEffectColorMul = renderer->getProgramUniformLocation(programGlId, L"effectColorMul");
	if (uniformEffectColorMul == -1)
		return;

	uniformEffectColorAdd = renderer->getProgramUniformLocation(programGlId, L"effectColorAdd");
	if (uniformEffectColorAdd == -1)
		return;

	initialized = true;
}

void GUIShader::useProgram()
{
	renderer->useProgram(programGlId);
	renderer->setProgramUniformInteger(uniformDiffuseTextureUnit, 0);
	isRunning = true;
}

void GUIShader::unUseProgram()
{
	isRunning = false;
}

void GUIShader::bindTexture(GLRenderer* renderer, int32_t textureId)
{
	if (isRunning == false)
		return;

	renderer->setProgramUniformInteger(uniformDiffuseTextureAvailable, textureId == 0 ? 0 : 1);
}

void GUIShader::updateEffect(GLRenderer* renderer)
{
	if (isRunning == false)
		return;

	renderer->setProgramUniformFloatVec4(uniformEffectColorMul, &renderer->effectColorMul);
	renderer->setProgramUniformFloatVec4(uniformEffectColorAdd, &renderer->effectColorAdd);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIShader::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.renderer.GUIShader", 27);
    return c;
}

java::lang::Class* GUIShader::getClass0()
{
	return class_();
}

