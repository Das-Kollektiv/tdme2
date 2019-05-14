#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/gui/renderer/GUIShader.h>
#include <tdme/engine/EngineGLES2Renderer.h>

using tdme::engine::EngineGLES2Renderer;
using tdme::engine::Engine;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::gui::renderer::GUIShader;

EngineGLES2Renderer::EngineGLES2Renderer(Engine *engine) :
	engine(engine)
{
}

void EngineGLES2Renderer::onUpdateProjectionMatrix()
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(this);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(this);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMatrices(this);

}

void EngineGLES2Renderer::onUpdateCameraMatrix()
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(this);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(this);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMatrices(this);

}

void EngineGLES2Renderer::onUpdateModelViewMatrix()
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(this);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(this);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMatrices(this);

}

void EngineGLES2Renderer::onBindTexture(void* context, int32_t textureId)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->bindTexture(this, textureId);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->bindTexture(this, textureId);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->bindTexture(this, textureId);
}

void EngineGLES2Renderer::onUpdateTextureMatrix(void* context)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateTextureMatrix(this, context);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateTextureMatrix(this);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->updateTextureMatrix(this);
}

void EngineGLES2Renderer::onUpdateEffect(void* context)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateEffect(this, context);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateEffect(this, context);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->updateEffect(this);

}

void EngineGLES2Renderer::onUpdateLight(void* context, int32_t lightId)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateLight(this, context, lightId);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateLight(this, lightId);
}

void EngineGLES2Renderer::onUpdateMaterial(void* context)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMaterial(this, context);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMaterial(this);
}

void EngineGLES2Renderer::onUpdateShader() {
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->setShader(shaderId, nullptr); // TODO: a.drewke

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->setShader(shaderId);
}
