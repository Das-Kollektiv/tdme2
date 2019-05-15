#include <tdme/engine/EngineVKRenderer.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/gui/renderer/GUIShader.h>

using tdme::engine::EngineVKRenderer;
using tdme::engine::Engine;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::gui::renderer::GUIShader;

EngineVKRenderer::EngineVKRenderer(Engine* engine) :
	engine(engine)
{
}

void EngineVKRenderer::onUpdateProjectionMatrix(void* context)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(this, context);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(this, context);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMatrices(this, context);

}

void EngineVKRenderer::onUpdateCameraMatrix(void* context)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(this, context);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(this, context);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMatrices(this, context);

}

void EngineVKRenderer::onUpdateModelViewMatrix(void* context)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(this, context);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(this, context);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMatrices(this, context);

}

void EngineVKRenderer::onBindTexture(void* context, int32_t textureId)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->bindTexture(this, context, textureId);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->bindTexture(this, textureId);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->bindTexture(this, context, textureId);
}

void EngineVKRenderer::onUpdateTextureMatrix(void* context)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateTextureMatrix(this, context);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateTextureMatrix(this, context);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->updateTextureMatrix(this);
}

void EngineVKRenderer::onUpdateEffect(void* context)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateEffect(this, context);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateEffect(this, context);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->updateEffect(this);

}

void EngineVKRenderer::onUpdateLight(void* context, int32_t lightId)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateLight(this, context, lightId);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateLight(this, context, lightId);
}

void EngineVKRenderer::onUpdateMaterial(void* context)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMaterial(this, context);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMaterial(this, context);
}

void EngineVKRenderer::onUpdateShader(void* context) {
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->setShader(context, shaderId);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->setShader(context, shaderId);
}
