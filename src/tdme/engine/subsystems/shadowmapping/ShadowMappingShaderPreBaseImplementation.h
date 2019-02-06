
#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPreImplementation.h>
#include <tdme/math/fwd-tdme.h>

using tdme::engine::Engine;
using tdme::engine::subsystems::renderer::GLRenderer;
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
	GLRenderer* renderer {  };
	int32_t vertexShaderGlId {  };
	int32_t geometryShaderGlId {  };
	int32_t fragmentShaderGlId {  };
	int32_t programGlId {  };
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
	virtual void useProgram(Engine* engine) override;
	virtual void unUseProgram() override;
	virtual void updateMatrices(const Matrix4x4& mvpMatrix) override;
	virtual void updateTextureMatrix(GLRenderer* renderer) override;
	virtual void updateMaterial(GLRenderer* renderer) override;
	virtual void bindTexture(GLRenderer* renderer, int32_t textureId) override;

	/**
	 * Constructor
	 * @param renderer renderer
	 */
	ShadowMappingShaderPreBaseImplementation(GLRenderer* renderer);

	/**
	 * Destructor
	 */
	~ShadowMappingShaderPreBaseImplementation();
};
