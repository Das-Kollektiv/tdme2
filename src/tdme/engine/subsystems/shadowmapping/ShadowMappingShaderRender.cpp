#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRender.h>

#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRenderImplementation.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRenderBaseImplementation.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRender;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRenderBaseImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;

ShadowMappingShaderRender::ShadowMappingShaderRender(GLRenderer* renderer) 
{
	defaultImplementation = new ShadowMappingShaderRenderBaseImplementation(renderer);
	foliageImplementation = new ShadowMappingShaderRenderBaseImplementation(renderer);
}

ShadowMappingShaderRender::~ShadowMappingShaderRender()
{
	delete defaultImplementation;
	delete foliageImplementation;
}

bool ShadowMappingShaderRender::isInitialized()
{
	return defaultImplementation->isInitialized() && foliageImplementation->isInitialized();
}

void ShadowMappingShaderRender::initialize()
{
	defaultImplementation->initialize();
	foliageImplementation->initialize();
}

void ShadowMappingShaderRender::useProgram()
{
	running = true;
}

void ShadowMappingShaderRender::unUseProgram()
{
	running = false;
	if (implementation != nullptr) {
		implementation->unUseProgram();;
	}
	implementation = nullptr;
}

void ShadowMappingShaderRender::setProgramMVMatrix(const Matrix4x4& mvMatrix)
{
	if (implementation == nullptr) return;
	implementation->setProgramMVMatrix(mvMatrix);
}

void ShadowMappingShaderRender::setProgramMVPMatrix(const Matrix4x4& mvpMatrix)
{
	if (implementation == nullptr) return;
	implementation->setProgramMVPMatrix(mvpMatrix);
}

void ShadowMappingShaderRender::setProgramNormalMatrix(const Matrix4x4& normalMatrix)
{
	if (implementation == nullptr) return;
	implementation->setProgramNormalMatrix(normalMatrix);
}

void ShadowMappingShaderRender::updateTextureMatrix(GLRenderer* renderer) {
	if (implementation == nullptr) return;
	implementation->updateTextureMatrix(renderer);
}

void ShadowMappingShaderRender::updateMaterial(GLRenderer* renderer)
{
	if (implementation == nullptr) return;
	implementation->updateMaterial(renderer);
}

void ShadowMappingShaderRender::updateLight(GLRenderer* renderer, int32_t lightId) {
	if (implementation == nullptr) return;
	implementation->updateLight(renderer, lightId);
}

void ShadowMappingShaderRender::bindTexture(GLRenderer* renderer, int32_t textureId)
{
	if (implementation == nullptr) return;
	implementation->bindTexture(renderer, textureId);
}

void ShadowMappingShaderRender::setProgramDepthBiasMVPMatrix(const Matrix4x4& depthBiasMVPMatrix)
{
	this->depthBiasMVPMatrix = depthBiasMVPMatrix;
}

void ShadowMappingShaderRender::setRenderLightId(int32_t lightId) {
	this->lightId = lightId;
}

void ShadowMappingShaderRender::updateApplyFoliageAnimation(GLRenderer* renderer) {
	auto currentImplementation = implementation;
	implementation = renderer->applyFoliageAnimation == true?foliageImplementation:defaultImplementation;
	if (currentImplementation != implementation) {
		if (currentImplementation != nullptr) currentImplementation->unUseProgram();
		implementation->useProgram();
	}
	implementation->setProgramDepthBiasMVPMatrix(depthBiasMVPMatrix);
	implementation->setRenderLightId(lightId);
}
