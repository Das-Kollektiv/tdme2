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

ShadowMappingShaderRender::ShadowMappingShaderRender(Renderer* renderer): renderer(renderer)
{
	if (ShadowMappingShaderRenderDefaultImplementation::isSupported(renderer) == true) shader["default"] = new ShadowMappingShaderRenderDefaultImplementation(renderer);
	if (ShadowMappingShaderRenderFoliageImplementation::isSupported(renderer) == true) shader["foliage"] = new ShadowMappingShaderRenderFoliageImplementation(renderer);
	auto threadCount = renderer->isSupportingMultithreadedRendering() == true?Engine::getThreadCount():1;
	contexts.resize(threadCount);
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
	auto i = 0;
	for (auto& shadowMappingShaderRenderContext: contexts) {
		if (shadowMappingShaderRenderContext.implementation != nullptr) {
			shadowMappingShaderRenderContext.implementation->unUseProgram(renderer->getContext(i));
		}
		shadowMappingShaderRenderContext.implementation = nullptr;
		i++;
	}
	engine = nullptr;
}

void ShadowMappingShaderRender::setProgramMVMatrix(void* context, const Matrix4x4& mvMatrix)
{
	auto& shadowMappingShaderRenderContext = contexts[renderer->getContextIndex(context)];
	if (shadowMappingShaderRenderContext.implementation == nullptr) return;
	shadowMappingShaderRenderContext.implementation->setProgramMVMatrix(context, mvMatrix);
}

void ShadowMappingShaderRender::setProgramMVPMatrix(void* context, const Matrix4x4& mvpMatrix)
{
	auto& shadowMappingShaderRenderContext = contexts[renderer->getContextIndex(context)];
	if (shadowMappingShaderRenderContext.implementation == nullptr) return;
	shadowMappingShaderRenderContext.implementation->setProgramMVPMatrix(context, mvpMatrix);
}

void ShadowMappingShaderRender::setProgramNormalMatrix(void* context, const Matrix4x4& normalMatrix)
{
	auto& shadowMappingShaderRenderContext = contexts[renderer->getContextIndex(context)];
	if (shadowMappingShaderRenderContext.implementation == nullptr) return;
	shadowMappingShaderRenderContext.implementation->setProgramNormalMatrix(context, normalMatrix);
}

void ShadowMappingShaderRender::updateTextureMatrix(Renderer* renderer, void* context) {
	auto& shadowMappingShaderRenderContext = contexts[renderer->getContextIndex(context)];
	if (shadowMappingShaderRenderContext.implementation == nullptr) return;
	shadowMappingShaderRenderContext.implementation->updateTextureMatrix(renderer, context);
}

void ShadowMappingShaderRender::updateMaterial(Renderer* renderer, void* context)
{
	auto& shadowMappingShaderRenderContext = contexts[renderer->getContextIndex(context)];
	if (shadowMappingShaderRenderContext.implementation == nullptr) return;
	shadowMappingShaderRenderContext.implementation->updateMaterial(renderer, context);
}

void ShadowMappingShaderRender::updateLight(Renderer* renderer, void* context, int32_t lightId) {
	auto& shadowMappingShaderRenderContext = contexts[renderer->getContextIndex(context)];
	if (shadowMappingShaderRenderContext.implementation == nullptr) return;
	shadowMappingShaderRenderContext.implementation->updateLight(renderer, context, lightId);
}

void ShadowMappingShaderRender::bindTexture(Renderer* renderer, void* context, int32_t textureId)
{
	auto& shadowMappingShaderRenderContext = contexts[renderer->getContextIndex(context)];
	if (shadowMappingShaderRenderContext.implementation == nullptr) return;
	shadowMappingShaderRenderContext.implementation->bindTexture(renderer, context, textureId);
}

void ShadowMappingShaderRender::setProgramDepthBiasMVPMatrix(void* context, const Matrix4x4& depthBiasMVPMatrix)
{
	this->depthBiasMVPMatrix = depthBiasMVPMatrix;
	auto& shadowMappingShaderRenderContext = contexts[renderer->getContextIndex(context)];
	if (shadowMappingShaderRenderContext.implementation == nullptr) return;
	shadowMappingShaderRenderContext.implementation->setProgramDepthBiasMVPMatrix(context, this->depthBiasMVPMatrix);
}

void ShadowMappingShaderRender::setRenderLightId(int32_t lightId) {
	this->lightId = lightId;
}

void ShadowMappingShaderRender::setShader(void* context, const string& id) {
	auto& shadowMappingShaderRenderContext = contexts[renderer->getContextIndex(context)];
	auto currentImplementation = shadowMappingShaderRenderContext.implementation;

	auto shaderIt = shader.find(id);
	if (shaderIt == shader.end()) {
		shaderIt = shader.find("default");
	}
	shadowMappingShaderRenderContext.implementation = shaderIt->second;

	if (currentImplementation != shadowMappingShaderRenderContext.implementation) {
		if (currentImplementation != nullptr) currentImplementation->unUseProgram(context);
		shadowMappingShaderRenderContext.implementation->useProgram(engine, context);
	}

	shadowMappingShaderRenderContext.implementation->setProgramDepthBiasMVPMatrix(context, depthBiasMVPMatrix);
	shadowMappingShaderRenderContext.implementation->setRenderLightId(lightId);
}
