#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using tdme::engine::subsystems::lighting::LightingShaderBaseImplementation;

using tdme::engine::Texture;
using tdme::engine::subsystems::renderer::RendererBackend;

/**
 * Lighting shader implementation
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::lighting::DeferredLightingShaderTerrainImplementation: public LightingShaderBaseImplementation
{
public:
	// forbid class copy
	FORBID_CLASS_COPY(DeferredLightingShaderTerrainImplementation)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 */
	DeferredLightingShaderTerrainImplementation(RendererBackend* rendererBackend);

	/**
	 * @return if supported by rendererBackend
	 * @param rendererBackend renderer backend
	 */
	static bool isSupported(RendererBackend* rendererBackend);

	// overridden methods
	virtual const string getId() override;
	virtual void initialize() override;
	virtual void registerShader() override;
	virtual void useProgram(Engine* engine, int contextIdx) override;
	virtual void unUseProgram(int contextIdx) override;
	virtual void updateMatrices(RendererBackend* rendererBackend, int contextIdx) override;
	virtual void updateShaderParameters(RendererBackend* rendererBackend, int contextIdx) override;
	virtual void unloadTextures() override;
	virtual void loadTextures(const string& pathName) override;

private:
	int32_t uniformModelMatrix { -1 };
	int32_t uniformGrasTextureUnit { -1 };
	int32_t uniformDirtTextureUnit { -1 };
	int32_t uniformSnowTextureUnit { -1 };
	int32_t uniformStoneTextureUnit { -1 };
	Texture* grasTexture { nullptr };
	Texture* dirtTexture { nullptr };
	Texture* snowTexture { nullptr };
	Texture* stoneTexture { nullptr };
	int32_t grasTextureId { 0 };
	int32_t dirtTextureId { 0 };
	int32_t snowTextureId { 0 };
	int32_t stoneTextureId { 0 };

protected:
	string additionalDefinitions;

};
