#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/fwd-tdme.h>

using std::string;

using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::SceneConnector;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Engine entity
 * @author Andreas Drewke
 */
class tdme::engine::Entity
{
	friend class Engine;
	friend class EntityHierarchy;
	friend class OctTreePartition;
	friend class ObjectRenderGroup;
	friend class ParticleSystemGroup;
	friend class SceneConnector;

protected:
	Entity* parentEntity { nullptr };

	/**
	 * Set parent entity, needs to be called before adding to engine
	 * @param entity entity
	 */
	inline void setParentEntity(Entity* entity) {
		this->parentEntity = entity;
	}

	/**
	 * @return parent entity
	 */
	inline Entity* getParentEntity() {
		return parentEntity;
	}

private:
	static constexpr int UNIQUEPARTITIONID_NONE { -1 };

	int uniquePartitionId { UNIQUEPARTITIONID_NONE };

	/**
	 * Set unique partition id
	 * @param uniquePartitionId unique partition id
	 */
	inline void setUniquePartitionId(int uniquePartitionId) {
		this->uniquePartitionId = uniquePartitionId;
	}

	/**
	 * @return unique partition id
	 */
	inline int getUniquePartitionId() {
		return uniquePartitionId;
	}

	/**
	 * Set parent transform
	 * @param parentTransform parent transform
	 */
	virtual void setParentTransform(const Transform& parentTransform) = 0;

public:
	static constexpr int RENDERPASS_MAX { 5 };
	static constexpr int RENDERPASS_ALL { 1 + 2 + 4 + 8 + 16 + 32 };
	enum RenderPass { RENDERPASS_NONE = 0, RENDERPASS_SKY = 1, RENDERPASS_NOFRUSTUMCULLING = 1, RENDERPASS_TERRAIN = 2, RENDERPASS_STANDARD = 4, RENDERPASS_WATER = 8, RENDERPASS_POST_POSTPROCESSING = 16, RENDERPASS_GIZMO = 32 };

	enum EntityType {
		ENTITYTYPE_DECAL,
		ENTITYTYPE_ENTITYHIERARCHY,
		ENTITYTYPE_ENVIRONMENTMAPPING,
		ENTITYTYPE_IMPOSTEROBJECT,
		ENTITYTYPE_LINES,
		ENTITYTYPE_LODOBJECT,
		ENTITYTYPE_LODOBJECTIMPOSTER,
		ENTITYTYPE_OBJECT,
		ENTITYTYPE_OBJECTRENDERGROUP,
		ENTITYTYPE_FOGPARTICLESYSTEM,
		ENTITYTYPE_OBJECTPARTICLESYSTEM,
		ENTITYTYPE_PARTICLESYSTEMGROUP,
		ENTITYTYPE_POINTSPARTICLESYSTEM
	};

	/**
	 * @return entity type
	 */
	virtual EntityType getEntityType() = 0;

	/**
	 * Set up engine
	 * @param engine engine
	 */
	virtual void setEngine(Engine* engine) = 0;

	/**
	 * Set up renderer
	 * @param renderer renderer
	 */
	virtual void setRenderer(Renderer* renderer) = 0;

	/**
	 * @return entity id
	 */
	virtual const string& getId() = 0;

	/**
	 * @return true if enabled to be rendered
	 */
	virtual bool isEnabled() = 0;

	/**
	 * Enable/disable rendering
	 * @param enabled enabled
	 */
	virtual void setEnabled(bool enabled) = 0;

	/**
	 * @return if frustum culling is enabled
	 */
	virtual bool isFrustumCulling() = 0;

	/**
	 * Set frustum culling
	 * @param frustumCulling frustum culling
	 */
	virtual void setFrustumCulling(bool frustumCulling) = 0;

	/**
	 * @return if entity is pickable
	 */
	virtual bool isPickable() = 0;

	/**
	 * Set this entity pickable
	 * @param pickable pickable
	 */
	virtual void setPickable(bool pickable) = 0;

	/**
	 * @return if entity contributes to shadows
	 */
	virtual bool isContributesShadows() = 0;

	/**
	 * Enable/disable contributes shadows
	 * @param contributesShadows contributes shadows
	 */
	virtual void setContributesShadows(bool contributesShadows) = 0;

	/**
	 * @return if entity receives shadows
	 */
	virtual bool isReceivesShadows() = 0;

	/**
	 * Enable/disable receives shadows
	 * @param receivesShadows receives shadows
	 */
	virtual void setReceivesShadows(bool receivesShadows) = 0;

	/**
	 * The effect color will be multiplied with fragment color
	 * @return effect color
	 */
	virtual const Color4& getEffectColorMul() const = 0;

	/**
	 * Set effect color that will be multiplied with fragment color
	 * @param effectColorMul effect color
	 */
	virtual void setEffectColorMul(const Color4& effectColorMul) = 0;

	/**
	 * The effect color will be added to fragment color
	 * @return effect color
	 */
	virtual const Color4& getEffectColorAdd() const = 0;

	/**
	 * Set effect color that will be added to fragment color
	 * @return effect color
	 */
	virtual void setEffectColorAdd(const Color4& effectColorAdd) = 0;

	/**
	 * Initiates this entity
	 */
	virtual void initialize() = 0;

	/**
	 * Dispose this entity
	 */
	virtual void dispose() = 0;

	/**
	 * @return bounding box / in model coordinate space
	 */
	virtual BoundingBox* getBoundingBox() = 0;

	/**
	 * @return world bounding box
	 */
	virtual BoundingBox* getWorldBoundingBox() = 0;

	/**
	 * @return entity translation
	 */
	virtual const Vector3& getTranslation() const = 0;

	/**
	 * Set translation
	 * @param translation translation
	 */
	virtual void setTranslation(const Vector3& translation) = 0;

	/**
	 * @return entity scale
	 */
	virtual const Vector3& getScale() const = 0;

	/**
	 * Set scale
	 * @param scale scale
	 */
	virtual void setScale(const Vector3& scale) = 0;

	/**
	 * @return rotation count
	 */
	virtual const int getRotationCount() const = 0;

	/**
	 * Get rotation at given index
	 * @param idx rotation index
	 * @return rotation
	 */
	virtual Rotation& getRotation(const int idx) = 0;

	/**
	 * Add rotation
	 * @param axis axis
	 * @param angle angle
	 */
	virtual void addRotation(const Vector3& axis, const float angle) = 0;

	/**
	 * Remove rotation
	 * @param idx index
	 */
	virtual void removeRotation(int idx) = 0;

	/**
	 * @param idx rotation index
	 * @return rotation axis for rotation with given index
	 */
	virtual const Vector3& getRotationAxis(const int idx) const = 0;

	/**
	 * Set rotation axis
	 * @param idx rotation index
	 * @param axis rotation axis
	 */
	virtual void setRotationAxis(const int idx, const Vector3& axis) = 0;

	/**
	 * @param idx rotation index
	 * @return rotation angle for rotation with given index
	 */
	virtual const float getRotationAngle(const int idx) const = 0;

	/**
	 * @param idx rotation index
	 * @param angle rotation angle
	 * @return rotation angle for rotation with given index
	 */
	virtual void setRotationAngle(const int idx, const float angle) = 0;

	/**
	 * @return rotations quaternion
	 */
	virtual const Quaternion& getRotationsQuaternion() const = 0;

	/**
	 * @return this transform matrix
	 */
	virtual const Matrix4x4& getTransformMatrix() const = 0;

	/**
	 * Update transform
	 */
	virtual void update() = 0;

	/**
	 * @return transform
	 */
	virtual const Transform& getTransform() const = 0;

	/**
	 * Set transform
	 * @param transform transform
	 */
	virtual void setTransform(const Transform& transform) = 0;

	/**
	 * @return render pass
	 */
	virtual RenderPass getRenderPass() const = 0;

	/**
	 * Set render pass
	 * @param renderPass render pass
	 */
	virtual void setRenderPass(RenderPass renderPass) = 0;

	/**
	 * Destructor
	 */
	virtual ~Entity() {}
};
