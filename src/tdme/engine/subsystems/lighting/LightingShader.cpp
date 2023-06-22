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
#include <tdme/engine/subsystems/lighting/DeferredLightingShaderSkyImplementation.h>
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
#include <tdme/engine/subsystems/lighting/LightingShaderSkyImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderSolidImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderTerrainEditorImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderTerrainImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderTreeImplementation.h>
#include <tdme/engine/subsystems/lighting/LightingShaderWaterImplementation.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
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
using tdme::engine::subsystems::lighting::DeferredLightingShaderSkyImplementation;
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
using tdme::engine::subsystems::lighting::LightingShaderSkyImplementation;
using tdme::engine::subsystems::lighting::LightingShaderSolidImplementation;
using tdme::engine::subsystems::lighting::LightingShaderTerrainEditorImplementation;
using tdme::engine::subsystems::lighting::LightingShaderTerrainImplementation;
using tdme::engine::subsystems::lighting::LightingShaderTreeImplementation;
using tdme::engine::subsystems::lighting::LightingShaderWaterImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::utilities::Console;
using tdme::utilities::StringTools;

LightingShader::LightingShader(Renderer* renderer): renderer(renderer)
{
	// light scattering
	if (LightingShaderLightScatteringDefaultImplementation::isSupported(renderer) == true) { auto shaderProgram = new LightingShaderLightScatteringDefaultImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderLightScatteringFoliageImplementation::isSupported(renderer) == true) { auto shaderProgram = new LightingShaderLightScatteringFoliageImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderLightScatteringTreeImplementation::isSupported(renderer) == true) { auto shaderProgram = new LightingShaderLightScatteringTreeImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	// spec
	if (LightingShaderDefaultImplementation::isSupported(renderer) == true) { auto shaderProgram = new LightingShaderDefaultImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderFoliageImplementation::isSupported(renderer) == true) { auto shaderProgram = new LightingShaderFoliageImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderSkyImplementation::isSupported(renderer) == true) { auto shaderProgram = new LightingShaderSkyImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderSolidImplementation::isSupported(renderer) == true) { auto shaderProgram = new LightingShaderSolidImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderTerrainEditorImplementation::isSupported(renderer) == true) { auto shaderProgram = new LightingShaderTerrainEditorImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderTerrainImplementation::isSupported(renderer) == true) { auto shaderProgram = new LightingShaderTerrainImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderTreeImplementation::isSupported(renderer) == true) { auto shaderProgram = new LightingShaderTreeImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderWaterImplementation::isSupported(renderer) == true) { auto shaderProgram = new LightingShaderWaterImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	// spec + deferred
	if (DeferredLightingShaderDefaultImplementation::isSupported(renderer) == true) { auto shaderProgram = new DeferredLightingShaderDefaultImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (DeferredLightingShaderFoliageImplementation::isSupported(renderer) == true) { auto shaderProgram = new DeferredLightingShaderFoliageImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (DeferredLightingShaderSkyImplementation::isSupported(renderer) == true) { auto shaderProgram = new DeferredLightingShaderSkyImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (DeferredLightingShaderSolidImplementation::isSupported(renderer) == true) { auto shaderProgram = new DeferredLightingShaderSolidImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (DeferredLightingShaderTerrainImplementation::isSupported(renderer) == true) { auto shaderProgram = new DeferredLightingShaderTerrainImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (DeferredLightingShaderTreeImplementation::isSupported(renderer) == true) { auto shaderProgram = new DeferredLightingShaderTreeImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	// pbr
	if (LightingShaderPBRDefaultImplementation::isSupported(renderer) == true) { auto shaderProgram = new LightingShaderPBRDefaultImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderPBRFoliageImplementation::isSupported(renderer) == true) { auto shaderProgram = new LightingShaderPBRFoliageImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (LightingShaderPBRTreeImplementation::isSupported(renderer) == true) { auto shaderProgram = new LightingShaderPBRTreeImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (DeferredLightingShaderPBRDefaultImplementation::isSupported(renderer) == true) { auto shaderProgram = new DeferredLightingShaderPBRDefaultImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (DeferredLightingShaderPBRFoliageImplementation::isSupported(renderer) == true) { auto shaderProgram = new DeferredLightingShaderPBRFoliageImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	if (DeferredLightingShaderPBRTreeImplementation::isSupported(renderer) == true) { auto shaderProgram = new DeferredLightingShaderPBRTreeImplementation(renderer); shader[shaderProgram->getId()] = shaderProgram; }
	auto threadCount = renderer->isSupportingMultithreadedRendering() == true?Engine::getThreadCount():1;
	contexts.resize(threadCount);
}

LightingShader::~LightingShader() {
	for (auto shaderIt: shader) {
		delete shaderIt.second;
	}
}

bool LightingShader::isInitialized()
{
	bool initialized = true;
	for (auto shaderIt: shader) {
		if (shaderIt.second->isInitialized() == false) {
			Console::println("LightingShader::isInitialized(): " + shaderIt.first + ": not initialized!");
		} else {
			shaderIt.second->registerShader();
		}
		initialized&= shaderIt.second->isInitialized();
	}
	return initialized;
}

void LightingShader::initialize()
{
	for (auto shaderIt: shader) {
		shaderIt.second->initialize();
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
	lightingShaderContext.implementation->updateEffect(renderer, contextIdx);
}

void LightingShader::updateMaterial(int contextIdx)
{
	auto& lightingShaderContext = contexts[contextIdx];
	if (lightingShaderContext.implementation == nullptr) return;
	lightingShaderContext.implementation->updateMaterial(renderer, contextIdx);
}

void LightingShader::updateLight(int contextIdx, int32_t lightId)
{
	auto& lightingShaderContext = contexts[contextIdx];
	if (lightingShaderContext.implementation == nullptr) return;
	lightingShaderContext.implementation->updateLight(renderer, contextIdx, lightId);
}

void LightingShader::updateMatrices(int contextIdx)
{
	auto& lightingShaderContext = contexts[contextIdx];
	if (lightingShaderContext.implementation == nullptr) return;
	lightingShaderContext.implementation->updateMatrices(renderer, contextIdx);
}

void LightingShader::updateTextureMatrix(int contextIdx) {
	auto& lightingShaderContext = contexts[contextIdx];
	if (lightingShaderContext.implementation == nullptr) return;
	lightingShaderContext.implementation->updateTextureMatrix(renderer, contextIdx);
}

void LightingShader::setShader(int contextIdx, const string& id) {
	if (running == false) return;
	auto shaderId = id;
	// TODO: find a better solution to remove pbr from lightscattering pass
	if ((renderer->isPBRAvailable() == false || renderer->getShaderPrefix() == "ls_") &&
		StringTools::startsWith(id, "pbr-") == true) {
		shaderId = StringTools::substring(id, 4, id.size());
	}
	auto& lightingShaderContext = contexts[contextIdx];
	auto currentImplementation = lightingShaderContext.implementation;
	auto shaderIt = shader.find(renderer->getShaderPrefix() + shaderId);
	if (shaderIt == shader.end()) shaderIt = shader.find(renderer->getShaderPrefix() + "default");
	if (shaderIt == shader.end()) shaderIt = shader.find("default");
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
	lightingShaderContext.implementation->updateShaderParameters(renderer, contextIdx);
}

void LightingShader::bindTexture(int contextIdx, int32_t textureId)
{
	auto& lightingShaderContext = contexts[contextIdx];
	if (lightingShaderContext.implementation == nullptr) return;
	lightingShaderContext.implementation->bindTexture(renderer, contextIdx, textureId);
}

void LightingShader::loadTextures(const string& pathName) {
	{
		auto shader = dynamic_cast<LightingShaderTerrainImplementation*>(getShader("terrain"));
		if (shader != nullptr) shader->loadTextures(pathName);
	}
	{
		auto shader = dynamic_cast<DeferredLightingShaderTerrainImplementation*>(getShader("defer_terrain"));
		if (shader != nullptr) shader->loadTextures(pathName);
	}
}
