#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/earlyzrejection/EZRShaderPre.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/lines/LinesShader.h>
#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/gui/renderer/GUIShader.h>
#include <tdme/engine/EngineGLES2Renderer.h>

using tdme::engine::EngineGLES2Renderer;
using tdme::engine::Engine;
using tdme::engine::subsystems::earlyzrejection::EZRShaderPre;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::lines::LinesShader;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::gui::renderer::GUIShader;

EngineGLES2Renderer::EngineGLES2Renderer(Engine *engine) :
	engine(engine)
{
}

void EngineGLES2Renderer::onUpdateProjectionMatrix(void* context)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(context);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(context);

	if (Engine::linesShader != nullptr)
		Engine::linesShader->updateMatrices(context);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMatrices(context);

	if (Engine::ezrShaderPre != nullptr)
		Engine::ezrShaderPre->updateMatrices(context);
}

void EngineGLES2Renderer::onUpdateCameraMatrix(void* context)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(context);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(context);

	if (Engine::linesShader != nullptr)
		Engine::linesShader->updateMatrices(context);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMatrices(context);

	if (Engine::ezrShaderPre != nullptr)
		Engine::ezrShaderPre->updateMatrices(context);
}

void EngineGLES2Renderer::onUpdateModelViewMatrix(void* context)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(context);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(context);

	if (Engine::linesShader != nullptr)
		Engine::linesShader->updateMatrices(context);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMatrices(context);

	if (Engine::ezrShaderPre != nullptr)
		Engine::ezrShaderPre->updateMatrices(context);
}

void EngineGLES2Renderer::onBindTexture(void* context, int32_t textureId)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->bindTexture(context, textureId);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->bindTexture(textureId);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->bindTexture(context, textureId);

	if (Engine::ezrShaderPre != nullptr)
		Engine::ezrShaderPre->bindTexture(context, textureId);
}

void EngineGLES2Renderer::onUpdateTextureMatrix(void* context)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateTextureMatrix(context);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateTextureMatrix(context);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->updateTextureMatrix();

	if (Engine::ezrShaderPre != nullptr)
		Engine::ezrShaderPre->updateTextureMatrix(context);
}

void EngineGLES2Renderer::onUpdateEffect(void* context)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateEffect(context);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateEffect(context);

	if (Engine::linesShader != nullptr)
		Engine::linesShader->updateEffect(context);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->updateEffect();

}

void EngineGLES2Renderer::onUpdateLight(void* context, int32_t lightId)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateLight(context, lightId);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateLight(context, lightId);
}

void EngineGLES2Renderer::onUpdateMaterial(void* context)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMaterial(context);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMaterial(context);

	if (Engine::ezrShaderPre != nullptr)
		Engine::ezrShaderPre->updateMaterial(context);
}

void EngineGLES2Renderer::onUpdateShader(void* context) {
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->setShader(context, shader);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->setShader(context, shader);

	if (Engine::ezrShaderPre != nullptr)
		Engine::ezrShaderPre->setShader(context, shader);
}
