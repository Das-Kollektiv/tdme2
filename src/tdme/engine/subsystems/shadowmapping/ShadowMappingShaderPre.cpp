#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPre.h>

#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPreDefaultImplementation.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPreFoliageImplementation.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPreImplementation.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPre;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreBaseImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreDefaultImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreFoliageImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix4x4;
using tdme::utils::Console;

ShadowMappingShaderPre::ShadowMappingShaderPre(Renderer* renderer) 
{
	if (ShadowMappingShaderPreDefaultImplementation::isSupported(renderer) == true) shader["default"] = new ShadowMappingShaderPreDefaultImplementation(renderer);
	if (ShadowMappingShaderPreFoliageImplementation::isSupported(renderer) == true) shader["foliage"] = new ShadowMappingShaderPreFoliageImplementation(renderer);
}

ShadowMappingShaderPre::~ShadowMappingShaderPre() {
	for (auto shaderIt: shader) {
		delete shaderIt.second;
	}
}

bool ShadowMappingShaderPre::isInitialized()
{
	bool initialized = true;
	for (auto shaderIt: shader) {
		initialized&= shaderIt.second->isInitialized();
	}
	return initialized;
}

void ShadowMappingShaderPre::initialize()
{
	for (auto shaderIt: shader) {
		shaderIt.second->initialize();
	}
}

void ShadowMappingShaderPre::useProgram(Engine* engine)
{
	running = true;
	this->engine = engine;
}

void ShadowMappingShaderPre::unUseProgram()
{
	running = false;
	if (implementation != nullptr) {
		implementation->unUseProgram();;
	}
	implementation = nullptr;
	engine = nullptr;
}

void ShadowMappingShaderPre::updateMatrices(void* context, const Matrix4x4& mvpMatrix)
{
	if (implementation == nullptr) return;
	implementation->updateMatrices(context, mvpMatrix);
}

void ShadowMappingShaderPre::updateTextureMatrix(Renderer* renderer, void* context) {
	if (implementation == nullptr) return;
	implementation->updateTextureMatrix(renderer, context);
}

void ShadowMappingShaderPre::updateMaterial(Renderer* renderer, void* context)
{
	if (implementation == nullptr) return;
	implementation->updateMaterial(renderer, context);
}

void ShadowMappingShaderPre::bindTexture(Renderer* renderer, void* context, int32_t textureId)
{
	if (implementation == nullptr) return;
	implementation->bindTexture(renderer, context, textureId);
}

void ShadowMappingShaderPre::setShader(void* context, const string& id) {
	auto currentImplementation = implementation;

	auto shaderIt = shader.find(id);
	if (shaderIt == shader.end()) {
		shaderIt = shader.find("default");
	}
	implementation = shaderIt->second;

	if (currentImplementation != implementation) {
		if (currentImplementation != nullptr) currentImplementation->unUseProgram();
		implementation->useProgram(engine, context);
	}
}
