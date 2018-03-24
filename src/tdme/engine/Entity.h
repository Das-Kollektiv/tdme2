#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

using std::string;

using tdme::engine::Engine;
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
	virtual const Vector3& getTranslation() const = 0;

	/**
	 * Set translation
	 * @param translation
	 */
	virtual void setTranslation(const Vector3& translation) = 0;

	/**
	 * @return object scale
	 */
	virtual const Vector3& getScale() const = 0;

	/**
	 * Set scale
	 * @param scale
	 */
	virtual void setScale(const Vector3& scale) = 0;

	/**
	 * @return pivot or center of rotations
	 */
	virtual const Vector3& getPivot() const = 0;

	/**
	 * Set pivot
	 * @param pivot
	 */
	virtual void setPivot(const Vector3& pivot) = 0;

	/**
	 * @return rotation count
	 */
	virtual const int getRotationCount() const = 0;

	/**
	 * Get rotation at given index
	 * @param rotation index
	 * @return rotation
	 */
	virtual Rotation& getRotation(const int idx) = 0;

	/**
	 * Add rotation
	 * @param axis
	 * @param angle
	 */
	virtual void addRotation(const Vector3& axis, const float angle) = 0;

	/**
	 * Remove rotation
	 * @param index
	 */
	virtual void removeRotation(int idx) = 0;

	/**
	 * @param rotation index
	 * @return rotation axis for rotation with given index
	 */
	virtual const Vector3& getRotationAxis(const int idx) const = 0;

	/**
	 * Set rotation axis
	 * @param rotation index
	 * @param rotation axis
	 */
	virtual void setRotationAxis(const int idx, const Vector3& axis) = 0;

	/**
	 * @param rotation index
	 * @return rotation angle for rotation with given index
	 */
	virtual const float getRotationAngle(const int idx) const = 0;

	/**
	 * @param rotation index
	 * @param rotation angle
	 * @return rotation angle for rotation with given index
	 */
	virtual void setRotationAngle(const int idx, const float angle) = 0;

	/**
	 * @return rotations quaternion
	 */
	virtual const Quaternion& getRotationsQuaternion() const = 0;

	/**
	 * @return this transformations matrix
	 */
	virtual const Matrix4x4& getTransformationsMatrix() const = 0;

	/**
	 * Set up this transformations from given transformations
	 * @param transformations
	 */
	virtual void fromTransformations(const Transformations& transformations) = 0;

	/** 
	 * Update transformations
	 */
	virtual void update() = 0;

	/**
	 * @return this transformations
	 */
	virtual const Transformations& getTransformations() const = 0;

	/**
	 * Destructor
	 */
	virtual ~Entity() {}
};
