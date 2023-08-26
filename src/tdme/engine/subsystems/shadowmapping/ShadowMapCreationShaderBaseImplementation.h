#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShaderImplementation.h>
#include <tdme/math/fwd-tdme.h>

using std::string;

using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderImplementation;
using tdme::engine::Engine;
using tdme::math::Matrix4x4;

/**
 * Shadow mapping shader base class to create shadow map
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::shadowmapping::ShadowMapCreationShaderBaseImplementation: public ShadowMapCreationShaderImplementation
{
protected:
	Renderer* renderer { nullptr };
	int32_t vertexShaderId { -1 };
	int32_t geometryShaderId { -1 };
	int32_t fragmentShaderId { -1 };
	int32_t programId { -1 };
	int32_t uniformProjectionMatrix { -1 };
	int32_t uniformCameraMatrix { -1 };
	int32_t uniformMVPMatrix { -1 };
	int32_t uniformTextureAtlasSize { -1 };
	int32_t uniformTextureAtlasPixelDimension { -1 };
	int32_t uniformTextureMatrix { -1 };
	int32_t uniformModelTranslation { -1 };
	int32_t uniformDiffuseTextureUnit { -1 };
	int32_t uniformDiffuseTextureAvailable { -1 };
	int32_t uniformDiffuseTextureMaskedTransparency { -1 };
	int32_t uniformDiffuseTextureMaskedTransparencyThreshold { -1 };
	int32_t uniformTime { -1 };
	bool initialized { false };

public:
	// forbid class copy
	FORBID_CLASS_COPY(ShadowMapCreationShaderBaseImplementation)

	/**
	 * Constructor
	 * @param renderer renderer
	 */
	ShadowMapCreationShaderBaseImplementation(Renderer* renderer);

	/**
	 * Destructor
	 */
	~ShadowMapCreationShaderBaseImplementation();

	// overridden methods
	virtual bool isInitialized() override;
	virtual void initialize() override;
	virtual void useProgram(Engine* engine, int contextIdx) override;
	virtual void unUseProgram(int contextIdx) override;
	virtual void updateMatrices(int contextIdx) override;
	virtual void updateTextureMatrix(Renderer* renderer, int contextIdx) override;
	virtual void updateMaterial(Renderer* renderer, int contextIdx) override;
	virtual void updateShaderParameters(Renderer* renderer, int contextIdx) override = 0;
	virtual void bindTexture(Renderer* renderer, int contextIdx, int32_t textureId) override;
	virtual void unloadTextures() override;
	virtual void loadTextures(const string& pathName) override;

};
