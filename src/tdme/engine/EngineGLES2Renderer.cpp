#include <tdme/tdme.h>
#include <tdme/engine/subsystems/earlyzrejection/EZRShader.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/lines/LinesShader.h>
#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/EngineGLES2Renderer.h>
#include <tdme/gui/renderer/GUIShader.h>

using tdme::engine::subsystems::earlyzrejection::EZRShader;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::lines::LinesShader;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::engine::Engine;
using tdme::engine::EngineGLES2Renderer;
using tdme::gui::renderer::GUIShader;

EngineGLES2Renderer::EngineGLES2Renderer(Engine *engine) :
	engine(engine)
{
}

void EngineGLES2Renderer::onUpdateProjectionMatrix(int contextIdx)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(contextIdx);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(contextIdx);

	if (Engine::linesShader != nullptr)
		Engine::linesShader->updateMatrices(contextIdx);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMatrices(contextIdx);

	if (Engine::ezrShader != nullptr)
		Engine::ezrShader->updateMatrices(contextIdx);
}

void EngineGLES2Renderer::onUpdateCameraMatrix(int contextIdx)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(contextIdx);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(contextIdx);

	if (Engine::linesShader != nullptr)
		Engine::linesShader->updateMatrices(contextIdx);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMatrices(contextIdx);

	if (Engine::ezrShader != nullptr)
		Engine::ezrShader->updateMatrices(contextIdx);
}

void EngineGLES2Renderer::onUpdateModelViewMatrix(int contextIdx)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMatrices(contextIdx);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateMatrices(contextIdx);

	if (Engine::linesShader != nullptr)
		Engine::linesShader->updateMatrices(contextIdx);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMatrices(contextIdx);

	if (Engine::ezrShader != nullptr)
		Engine::ezrShader->updateMatrices(contextIdx);
}

void EngineGLES2Renderer::onBindTexture(int contextIdx, int32_t textureId)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->bindTexture(contextIdx, textureId);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->bindTexture(textureId);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->bindTexture(contextIdx, textureId);

	if (Engine::ezrShader != nullptr)
		Engine::ezrShader->bindTexture(contextIdx, textureId);
}

void EngineGLES2Renderer::onUpdateTextureMatrix(int contextIdx)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateTextureMatrix(contextIdx);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateTextureMatrix(contextIdx);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->updateTextureMatrix();

	if (Engine::ezrShader != nullptr)
		Engine::ezrShader->updateTextureMatrix(contextIdx);
}

void EngineGLES2Renderer::onUpdateEffect(int contextIdx)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateEffect(contextIdx);

	if (Engine::particlesShader != nullptr)
		Engine::particlesShader->updateEffect(contextIdx);

	if (Engine::linesShader != nullptr)
		Engine::linesShader->updateEffect(contextIdx);

	if (Engine::guiShader != nullptr)
		Engine::guiShader->updateEffect();

}

void EngineGLES2Renderer::onUpdateLight(int contextIdx, int32_t lightId)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateLight(contextIdx, lightId);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateLight(contextIdx, lightId);
}

void EngineGLES2Renderer::onUpdateMaterial(int contextIdx)
{
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateMaterial(contextIdx);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateMaterial(contextIdx);

	if (Engine::ezrShader != nullptr)
		Engine::ezrShader->updateMaterial(contextIdx);
}

void EngineGLES2Renderer::onUpdateShader(int contextIdx) {
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->setShader(contextIdx, getShader(contextIdx));

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->setShader(contextIdx, getShader(contextIdx));

	if (Engine::ezrShader != nullptr)
		Engine::ezrShader->setShader(contextIdx, getShader(contextIdx));
}

void EngineGLES2Renderer::onUpdateShaderParameters(int contextIdx) {
	if (Engine::lightingShader != nullptr)
		Engine::lightingShader->updateShaderParameters(contextIdx);

	if (Engine::currentEngine->shadowMapping != nullptr)
		Engine::currentEngine->shadowMapping->updateShaderParameters(contextIdx);

	if (Engine::ezrShader != nullptr)
		Engine::ezrShader->updateShaderParameters(contextIdx);
}
