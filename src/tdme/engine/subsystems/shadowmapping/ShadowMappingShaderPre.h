
#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;

/** 
 * Pre shadow mapping shader for render shadow map pass 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPre
{
private:
	GLRenderer* renderer {  };
	int32_t vertexShaderGlId {  };
	int32_t fragmentShaderGlId {  };
	int32_t programGlId {  };
	int32_t uniformMVPMatrix {  };
	int32_t uniformDiffuseTextureUnit {  };
	int32_t uniformDiffuseTextureAvailable {  };
	int32_t uniformDiffuseTextureMaskedTransparency {  };
	bool initialized {  };

public:

	/** 
	 * @return if initialized and ready to use
	 */
	virtual bool isInitialized();

	/** 
	 * Init shadow mapping
	 */
	virtual void initialize();

	/** 
	 * Use pre render shadow mapping program
	 */
	virtual void useProgram();

	/** 
	 * Un use pre render shadow mapping program
	 */
	virtual void unUseProgram();

	/** 
	 * Set up pre program mvp matrix
	 * @param mvp matrix
	 */
	virtual void setProgramMVPMatrix(const Matrix4x4& mvpMatrix);

	/**
	 * Update material
	 * @param renderer
	 */
	virtual void updateMaterial(GLRenderer* renderer);

	/**
	 * Bind texture
	 * @param renderer
	 * @param texture id
	 */
	virtual void bindTexture(GLRenderer* renderer, int32_t textureId);

	/**
	 * Constructor
	 * @param renderer
	 */
	ShadowMappingShaderPre(GLRenderer* renderer);
};
