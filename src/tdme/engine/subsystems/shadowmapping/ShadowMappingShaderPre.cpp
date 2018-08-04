#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPre.h>

#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPreBaseImplementation.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPreImplementation.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPre;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreBaseImplementation;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::utils::Console;

ShadowMappingShaderPre::ShadowMappingShaderPre(GLRenderer* renderer) 
{
	defaultImplementation = new ShadowMappingShaderPreBaseImplementation(renderer);
	foliageImplementation = new ShadowMappingShaderPreBaseImplementation(renderer);
}

ShadowMappingShaderPre::~ShadowMappingShaderPre() {
	delete defaultImplementation;
	delete foliageImplementation;
}

bool ShadowMappingShaderPre::isInitialized()
{
	return defaultImplementation->isInitialized() && foliageImplementation->isInitialized();
}

void ShadowMappingShaderPre::initialize()
{
	defaultImplementation->initialize();
	foliageImplementation->initialize();
}

void ShadowMappingShaderPre::useProgram()
{
	running = true;
}

void ShadowMappingShaderPre::unUseProgram()
{
	running = false;
	if (implementation != nullptr) {
		implementation->unUseProgram();;
	}
	implementation = nullptr;
}

void ShadowMappingShaderPre::updateMatrices(const Matrix4x4& mvpMatrix)
{
	if (implementation == nullptr) return;
	implementation->updateMatrices(mvpMatrix);
}

void ShadowMappingShaderPre::updateTextureMatrix(GLRenderer* renderer) {
	if (implementation == nullptr) return;
	implementation->updateTextureMatrix(renderer);
}

void ShadowMappingShaderPre::updateMaterial(GLRenderer* renderer)
{
	if (implementation == nullptr) return;
	implementation->updateMaterial(renderer);
}

void ShadowMappingShaderPre::bindTexture(GLRenderer* renderer, int32_t textureId)
{
	if (implementation == nullptr) return;
	implementation->bindTexture(renderer, textureId);
}

void ShadowMappingShaderPre::updateApplyFoliageAnimation(GLRenderer* renderer) {
	auto currentImplementation = implementation;
	implementation = renderer->applyFoliageAnimation == true?foliageImplementation:defaultImplementation;
	if (currentImplementation != implementation) {
		if (currentImplementation != nullptr) currentImplementation->unUseProgram();
		implementation->useProgram();
	}
}
