#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

using std::string;

using tdme::engine::Engine;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * TDME engine entity
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::Entity
{

	/** 
	 * Set up engine
	 * @param engine
	 */
	virtual void setEngine(Engine* engine) = 0;

	/** 
	 * Set up renderer
	 * @param renderer
	 */
	virtual void setRenderer(GLRenderer* renderer) = 0;

	/** 
	 * @return object id
	 */
	virtual const string& getId() = 0;

	/** 
	 * @return true if enabled to be rendered
	 */
	virtual bool isEnabled() = 0;

	/** 
	 * Enable/disable rendering
	 * @param enabled
	 */
	virtual void setEnabled(bool enabled) = 0;

	/**
	 * @return if frustum culling is enabled
	 */
	virtual bool isFrustumCulling() = 0;

	/**
	 * Set frustum culling
	 * @param frustum culling
	 */
	virtual void setFrustumCulling(bool frustumCulling) = 0;

	/** 
	 * @return if object is pickable
	 */
	virtual bool isPickable() = 0;

	/** 
	 * Set this object pickable
	 * @param pickable
	 */
	virtual void setPickable(bool pickable) = 0;

	/** 
	 * @return dynamic shadowing enabled
	 */
	virtual bool isDynamicShadowingEnabled() = 0;

	/** 
	 * Enable/disable dynamic shadowing
	 * @param dynamicShadowing
	 */
	virtual void setDynamicShadowingEnabled(bool dynamicShadowing) = 0;

	/** 
	 * The effect color will be multiplied with fragment color
	 * @return effect color
	 */
	virtual Color4& getEffectColorMul() = 0;

	/** 
	 * The effect color will be added to fragment color
	 * @return effect color
	 */
	virtual Color4& getEffectColorAdd() = 0;

	/** 
	 * Initiates this object 3d 
	 */
	virtual void initialize() = 0;

	/** 
	 * Dispose this object 3d
	 */
	virtual void dispose() = 0;

	/** 
	 * @return bounding box / in model coordinate space
	 */
	virtual BoundingBox* getBoundingBox() = 0;

	/** 
	 * @return bounding box transformed / in world coordinate space
	 */
	virtual BoundingBox* getBoundingBoxTransformed() = 0;

	/** 
	 * @return object translation
	 */
	virtual Vector3& getTranslation() = 0;

	/** 
	 * @return object scale
	 */
	virtual Vector3& getScale() = 0;

	/** 
	 * @return pivot or center of rotations
	 */
	virtual Vector3& getPivot() = 0;

	/** 
	 * @return object rotations
	 */
	virtual Rotations* getRotations() = 0;

	/** 
	 * @return this transformations matrix
	 */
	virtual Matrix4x4& getTransformationsMatrix() = 0;

	/** 
	 * Set up this transformations from given transformations
	 * @param transformations
	 */
	virtual void fromTransformations(Transformations* transformations) = 0;

	/** 
	 * Update transformations
	 */
	virtual void update() = 0;

	/**
	 * Destructor
	 */
	virtual ~Entity() {}
};
