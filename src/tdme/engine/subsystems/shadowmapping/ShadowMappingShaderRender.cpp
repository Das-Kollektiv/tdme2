#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRender.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRenderImplementation.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRenderDefaultImplementation.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRenderFoliageImplementation.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRender;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderDefaultImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderFoliageImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix4x4;

ShadowMappingShaderRender::ShadowMappingShaderRender(Renderer* renderer) 
{
	if (ShadowMappingShaderRenderDefaultImplementation::isSupported(renderer) == true) shader["default"] = new ShadowMappingShaderRenderDefaultImplementation(renderer);
	if (ShadowMappingShaderRenderFoliageImplementation::isSupported(renderer) == true) shader["foliage"] = new ShadowMappingShaderRenderFoliageImplementation(renderer);
}

ShadowMappingShaderRender::~ShadowMappingShaderRender()
{
	for (auto shaderIt: shader) {
		delete shaderIt.second;
	}
}

bool ShadowMappingShaderRender::isInitialized()
{
	bool initialized = true;
	for (auto shaderIt: shader) {
		initialized&= shaderIt.second->isInitialized();
	}
	return initialized;
}

void ShadowMappingShaderRender::initialize()
{
	for (auto shaderIt: shader) {
		shaderIt.second->initialize();
	}
}

void ShadowMappingShaderRender::useProgram(Engine* engine)
{
	running = true;
	this->engine = engine;
}

void ShadowMappingShaderRender::unUseProgram()
{
	running = false;
	if (implementation != nullptr) {
		implementation->unUseProgram();;
	}
	implementation = nullptr;
	engine = nullptr;
}

void ShadowMappingShaderRender::setProgramMVMatrix(void* context, const Matrix4x4& mvMatrix)
{
	if (implementation == nullptr) return;
	implementation->setProgramMVMatrix(context, mvMatrix);
}

void ShadowMappingShaderRender::setProgramMVPMatrix(void* context, const Matrix4x4& mvpMatrix)
{
	if (implementation == nullptr) return;
	implementation->setProgramMVPMatrix(context, mvpMatrix);
}

void ShadowMappingShaderRender::setProgramNormalMatrix(void* context, const Matrix4x4& normalMatrix)
{
	if (implementation == nullptr) return;
	implementation->setProgramNormalMatrix(context, normalMatrix);
}

void ShadowMappingShaderRender::updateTextureMatrix(Renderer* renderer, void* context) {
	if (implementation == nullptr) return;
	implementation->updateTextureMatrix(renderer, context);
}

void ShadowMappingShaderRender::updateMaterial(Renderer* renderer, void* context)
{
	if (implementation == nullptr) return;
	implementation->updateMaterial(renderer, context);
}

void ShadowMappingShaderRender::updateLight(Renderer* renderer, void* context, int32_t lightId) {
	if (implementation == nullptr) return;
	implementation->updateLight(renderer, context, lightId);
}

void ShadowMappingShaderRender::bindTexture(Renderer* renderer, void* context, int32_t textureId)
{
	if (implementation == nullptr) return;
	implementation->bindTexture(renderer, context, textureId);
}

void ShadowMappingShaderRender::setProgramDepthBiasMVPMatrix(void* context, const Matrix4x4& depthBiasMVPMatrix)
{
	this->depthBiasMVPMatrix = depthBiasMVPMatrix;
	if (implementation == nullptr) return;
	implementation->setProgramDepthBiasMVPMatrix(context, this->depthBiasMVPMatrix);
}

void ShadowMappingShaderRender::setRenderLightId(int32_t lightId) {
	this->lightId = lightId;
}

void ShadowMappingShaderRender::setShader(void* context, const string& id) {
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

	implementation->setProgramDepthBiasMVPMatrix(context, depthBiasMVPMatrix);
	implementation->setRenderLightId(lightId);
}
