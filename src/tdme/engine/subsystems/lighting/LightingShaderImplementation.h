#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using std::array;

using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;

/** 
 * Lighting shader implementation interface
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::subsystems::lighting::LightingShaderImplementation
{
public:
	/**
	 * Destructor
	 */
	virtual ~LightingShaderImplementation() {}

	/** 
	 * @return initialized and ready to be used
	 */
	virtual bool isInitialized() = 0;

	/** 
	 * Initialize renderer
	 */
	virtual void initialize() = 0;

	/** 
	 * Use lighting program
	 */
	virtual void useProgram() = 0;

	/** 
	 * Unuse lighting program
	 */
	virtual void unUseProgram() = 0;

	/** 
	 * Update effect to program
	 * @param renderer renderer
	 */
	virtual void updateEffect(GLRenderer* renderer) = 0;

	/** 
	 * Update material to program
	 * @param renderer gl3 renderer
	 */
	virtual void updateMaterial(GLRenderer* renderer) = 0;

	/** 
	 * Update light to program
	 * @param renderer renderer
	 * @param lightId light id
	 */
	virtual void updateLight(GLRenderer* renderer, int32_t lightId) = 0;

	/** 
	 * Update matrices to program
	 * @param renderer renderer
	 */
	virtual void updateMatrices(GLRenderer* renderer) = 0;

	/** 
	 * Update texture matrix to program
	 * @param renderer renderer
	 */
	virtual void updateTextureMatrix(GLRenderer* renderer) = 0;

	/**
	 * Bind texture
	 * @param renderer renderer
	 * @param textureId texture id
	 */
	virtual void bindTexture(GLRenderer* renderer, int32_t textureId) = 0;

};
