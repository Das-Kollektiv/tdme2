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

void EngineVKRenderer::onUpdateProjectionMatrix()
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(this);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(this);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMatrices(this);

}

void EngineVKRenderer::onUpdateCameraMatrix()
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(this);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(this);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMatrices(this);

}

void EngineVKRenderer::onUpdateModelViewMatrix()
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(this);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(this);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMatrices(this);

}

void EngineVKRenderer::onBindTexture(int32_t textureId)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->bindTexture(this, textureId);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->bindTexture(this, textureId);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->bindTexture(this, textureId);
}

void EngineVKRenderer::onUpdateTextureMatrix()
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateTextureMatrix(this);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateTextureMatrix(this);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->updateTextureMatrix(this);
}

void EngineVKRenderer::onUpdateEffect()
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateEffect(this);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateEffect(this);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->updateEffect(this);

}

void EngineVKRenderer::onUpdateLight(int32_t lightId)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateLight(this, lightId);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateLight(this, lightId);
}

void EngineVKRenderer::onUpdateMaterial()
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMaterial(this);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMaterial(this);
}

void EngineVKRenderer::onUpdateShader() {
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->setShader(shaderId);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->setShader(shaderId);
}
