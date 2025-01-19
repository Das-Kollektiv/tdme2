#include <tdme/engine/subsystems/lighting/LightingShader.h>

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/DeferredLightingShaderDefaultImplementation.h>
#include <tdme/engine/subsystems/lighting/DeferredLightingShaderFoliageImplementation.h>
#include <tdme/engine/subsystems/lighting/DeferredLightingShaderPBRDefaultImplementation.h>
#include <tdme/engine/subsystems/lighting/DeferredLightingShaderPBRFoliageImplementation.h>
#include <tdme/engine/subsystems/lighting/DeferredLightingShaderPBRTreeImplementation.h>
#include <tdme/engine/subsystems/lighting/DeferredLightingShaderSolidImplementation.h>
#include <tdme/engine/subsystems/lighting/DeferredLightingShaderTerrainImplementation.h>
#include <tdme/engine/subsystems/lighting/DeferredLightingShaderTreeImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderDefaultImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderFoliageImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderLightScatteringDefaultImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderLightScatteringFoliageImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderLightScatteringTreeImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderPBRDefaultImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderPBRFoliageImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderPBRTreeImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderSolidImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderTerrainEditorImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderTerrainImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderTreeImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderWaterImplementation.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::subsystems::lighting::DeferredLightingShaderDefaultImplementation;
using tdme::engine::subsystems::lighting::DeferredLightingShaderFoliageImplementation;
using tdme::engine::subsystems::lighting::DeferredLightingShaderPBRDefaultImplementation;
using tdme::engine::subsystems::lighting::DeferredLightingShaderPBRFoliageImplementation;
using tdme::engine::subsystems::lighting::DeferredLightingShaderPBRTreeImplementation;
using tdme::engine::subsystems::lighting::DeferredLightingShaderSolidImplementation;
using tdme::engine::subsystems::lighting::DeferredLightingShaderTerrainImplementation;
using tdme::engine::subsystems::lighting::DeferredLightingShaderTreeImplementation;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::lighting::LightingShaderDefaultImplementation;
using tdme::engine::subsystems::lighting::LightingShaderFoliageImplementation;
using tdme::engine::subsystems::lighting::LightingShaderImplementation;
using tdme::engine::subsystems::lighting::LightingShaderLightScatteringDefaultImplementation;
using tdme::engine::subsystems::lighting::LightingShaderPBRDefaultImplementation;
using tdme::engine::subsystems::lighting::LightingShaderPBRFoliageImplementation;
using tdme::engine::subsystems::lighting::LightingShaderPBRTreeImplementation;
using tdme::engine::subsystems::lighting::LightingShaderSolidImplementation;
using tdme::engine::subsystems::lighting::LightingShaderTerrainEditorImplementation;
using tdme::engine::subsystems::lighting::LightingShaderTerrainImplementation;
using tdme::engine::subsystems::lighting::LightingShaderTreeImplementation;
using tdme::engine::subsystems::lighting::LightingShaderWaterImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::utilities::Console;
using tdme::utilities::StringTools;

LightingShader::LightingShader(RendererBackend* rendererBackend): rendererBackend(rendererBackend)
{
	// light scattering
	if (LightingShaderLightScatteringDefaultImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new LightingShaderLightScatteringDefaultImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderLightScatteringFoliageImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new LightingShaderLightScatteringFoliageImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderLightScatteringTreeImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new LightingShaderLightScatteringTreeImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	// spec
	if (LightingShaderDefaultImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new LightingShaderDefaultImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderFoliageImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new LightingShaderFoliageImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderSolidImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new LightingShaderSolidImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderTerrainEditorImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new LightingShaderTerrainEditorImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderTerrainImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new LightingShaderTerrainImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderTreeImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new LightingShaderTreeImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderWaterImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new LightingShaderWaterImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	// spec + deferred
	if (DeferredLightingShaderDefaultImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new DeferredLightingShaderDefaultImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (DeferredLightingShaderFoliageImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new DeferredLightingShaderFoliageImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (DeferredLightingShaderSolidImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new DeferredLightingShaderSolidImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (DeferredLightingShaderTerrainImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new DeferredLightingShaderTerrainImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (DeferredLightingShaderTreeImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new DeferredLightingShaderTreeImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	// pbr
	if (LightingShaderPBRDefaultImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new LightingShaderPBRDefaultImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderPBRFoliageImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new LightingShaderPBRFoliageImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderPBRTreeImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new LightingShaderPBRTreeImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (DeferredLightingShaderPBRDefaultImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new DeferredLightingShaderPBRDefaultImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (DeferredLightingShaderPBRFoliageImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new DeferredLightingShaderPBRFoliageImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	if (DeferredLightingShaderPBRTreeImplementation::isSupported(rendererBackend) == true) { auto shaderProgram = new DeferredLightingShaderPBRTreeImplementation(rendererBackend); shaders[shaderProgram->getId()] = shaderProgram; }
	auto threadCount = rendererBackend->isSupportingMultithreadedRendering() == true?Engine::getThreadCount():1;
	contexts.resize(threadCount);
}

LightingShader::~LightingShader() {
	for (const auto& [shaderId, shader]: shaders) {
		delete shader;
	}
}

bool LightingShader::isInitialized()
{
	bool initialized = true;
	for (const auto& [shaderId, shader]: shaders) {
		if (shader->isInitialized() == false) {
			Console::printLine("LightingShader::isInitialized(): " + shaderId + ": not initialized!");
		} else {
			shader->registerShader();
		}
		initialized&= shader->isInitialized();
	}
	return initialized;
}

void LightingShader::initialize()
{
	for (const auto& [shaderId, shader]: shaders) {
		shader->initialize();
	}
}

void LightingShader::dispose()
{
	for (const auto& [shaderId, shader]: shaders) {
		shader->unloadTextures();
	}
}

void LightingShader::useProgram(Engine* engine)
{
	running = true;
	this->engine = engine;
}

void LightingShader::unUseProgram()
{
	running = false;
	auto i = 0;
	for (auto& lightingShaderContext: contexts) {
		if (lightingShaderContext.implementation != nullptr) lightingShaderContext.implementation->unUseProgram(i);
		lightingShaderContext.implementation = nullptr;
		i++;
	}
	engine = nullptr;
}

void LightingShader::updateEffect(int contextIdx)
{
	auto& lightingShaderContext = contexts[contextIdx];
	if (lightingShaderContext.implementation == nullptr) return;
	lightingShaderContext.implementation->updateEffect(rendererBackend, contextIdx);
}

void LightingShader::updateMaterial(int contextIdx)
{
	auto& lightingShaderContext = contexts[contextIdx];
	if (lightingShaderContext.implementation == nullptr) return;
	lightingShaderContext.implementation->updateMaterial(rendererBackend, contextIdx);
}

void LightingShader::updateLight(int contextIdx, int32_t lightId)
{
	auto& lightingShaderContext = contexts[contextIdx];
	if (lightingShaderContext.implementation == nullptr) return;
	lightingShaderContext.implementation->updateLight(rendererBackend, contextIdx, lightId);
}

void LightingShader::updateMatrices(int contextIdx)
{
	auto& lightingShaderContext = contexts[contextIdx];
	if (lightingShaderContext.implementation == nullptr) return;
	lightingShaderContext.implementation->updateMatrices(rendererBackend, contextIdx);
}

void LightingShader::updateTextureMatrix(int contextIdx) {
	auto& lightingShaderContext = contexts[contextIdx];
	if (lightingShaderContext.implementation == nullptr) return;
	lightingShaderContext.implementation->updateTextureMatrix(rendererBackend, contextIdx);
}

void LightingShader::setShader(int contextIdx, const string& id) {
	if (running == false) return;
	auto shaderId = id;
	// TODO: find a better solution to remove pbr from lightscattering pass
	if ((rendererBackend->isPBRAvailable() == false || rendererBackend->getShaderPrefix() == "ls_") &&
		StringTools::startsWith(id, "pbr-") == true) {
		shaderId = StringTools::substring(id, 4, id.size());
	}
	auto& lightingShaderContext = contexts[contextIdx];
	auto currentImplementation = lightingShaderContext.implementation;
	auto shaderIt = shaders.find(rendererBackend->getShaderPrefix() + shaderId);
	if (shaderIt == shaders.end()) shaderIt = shaders.find(rendererBackend->getShaderPrefix() + "default");
	if (shaderIt == shaders.end()) shaderIt = shaders.find("default");
	auto nextImplementation = shaderIt->second;
	if (currentImplementation != nextImplementation) {
		if (currentImplementation != nullptr) currentImplementation->unUseProgram(contextIdx);
		lightingShaderContext.implementation = nextImplementation;
		lightingShaderContext.implementation->useProgram(engine, contextIdx);
	}
}

void LightingShader::updateShaderParameters(int contextIdx) {
	auto& lightingShaderContext = contexts[contextIdx];
	if (lightingShaderContext.implementation == nullptr) return;
	lightingShaderContext.implementation->updateShaderParameters(rendererBackend, contextIdx);
}

void LightingShader::bindTexture(int contextIdx, int32_t textureId)
{
	auto& lightingShaderContext = contexts[contextIdx];
	if (lightingShaderContext.implementation == nullptr) return;
	lightingShaderContext.implementation->bindTexture(rendererBackend, contextIdx, textureId);
}


void LightingShader::loadTextures(const string& pathName) {
	for (const auto& [shaderId, shader]: shaders) {
		shader->unloadTextures();
		shader->loadTextures(pathName);
	}
}
