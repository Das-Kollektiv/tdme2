
#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPreImplementation.h>
#include <tdme/math/fwd-tdme.h>

using tdme::engine::Engine;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreImplementation;
using tdme::math::Matrix4x4;

/** 
 * Shadow mapping shader base class to render shadow map
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPreBaseImplementation: public ShadowMappingShaderPreImplementation
{
protected:
	Renderer* renderer {  };
	int32_t vertexShaderId {  };
	int32_t geometryShaderId {  };
	int32_t fragmentShaderId {  };
	int32_t programId {  };
	int32_t uniformProjectionMatrix { -1 };
	int32_t uniformCameraMatrix { -1 };
	int32_t uniformMVPMatrix { -1 };
	int32_t uniformTextureMatrix { -1 };
	int32_t uniformDiffuseTextureUnit { -1 };
	int32_t uniformDiffuseTextureAvailable { -1 };
	int32_t uniformDiffuseTextureMaskedTransparency { -1 };
	int32_t uniformDiffuseTextureMaskedTransparencyThreshold { -1 };
	int32_t uniformFrame { -1 };
	bool initialized {  };

public:

	// overriden methods
	virtual bool isInitialized() override;
	virtual void initialize() override;
	virtual void useProgram(Engine* engine, void* context) override;
	virtual void unUseProgram() override;
	virtual void updateMatrices(void* context, const Matrix4x4& mvpMatrix) override;
	virtual void updateTextureMatrix(Renderer* renderer, void* context) override;
	virtual void updateMaterial(Renderer* renderer, void* context) override;
	virtual void bindTexture(Renderer* renderer, void* context, int32_t textureId) override;

	/**
	 * Constructor
	 * @param renderer renderer
	 */
	ShadowMappingShaderPreBaseImplementation(Renderer* renderer);

	/**
	 * Destructor
	 */
	~ShadowMappingShaderPreBaseImplementation();
};
