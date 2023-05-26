#pragma once

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/ObjectInternal.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::remove;
using std::string;
using std::to_string;
using std::unordered_map;
using std::vector;

using tdme::engine::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::ObjectInternal;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Object;
using tdme::engine::Rotation;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Entity hierarchy to be used with engine class
 * @author Andreas Drewke
 */
class tdme::engine::EntityHierarchy final:
	public Transform,
	public Entity
{
private:
	struct EntityHierarchyLevel {
		EntityHierarchyLevel(const string& id, EntityHierarchyLevel* parent, Entity* entity): id(id), parent(parent), entity(entity) {}
		string id;
		EntityHierarchyLevel* parent { nullptr };
		Entity* entity { nullptr };
		unordered_map<string, EntityHierarchyLevel*> children;
	};
	Engine* engine { nullptr };
	Renderer* renderer { nullptr };
	bool frustumCulling { true };
	bool initialized { false };

	string id;
	bool enabled;
	bool pickable;
	bool contributesShadows;
	bool receivesShadows;
	Color4 effectColorMul;
	Color4 effectColorAdd;
	BoundingBox boundingBox;
	BoundingBox worldBoundingBox;
	vector<Entity*> entities;
	EntityHierarchyLevel entityRoot { string(), nullptr, nullptr };

	RenderPass renderPass { RENDERPASS_STANDARD };

	Transform parentTransform;
	Matrix4x4 entityTransformMatrix;
	Matrix4x4 entityTransformMatrixInverted;

	// overridden methods
	inline void setParentTransform(const Transform& parentTransform) override {
		//
		this->parentTransform = parentTransform;
		auto entityTransform = parentTransform * (*this);
		entityTransformMatrix = entityTransform.getTransformMatrix();
		entityTransformMatrixInverted = entityTransformMatrix.clone().invert();
		//
		worldBoundingBox.fromBoundingVolumeWithTransformMatrix(&boundingBox, entityTransformMatrix);
	}

	/**
	 * Get entity hierarchy level by given entity id
	 */
	inline EntityHierarchyLevel* getEntityHierarchyLevel(const string& id) {
		if (id.empty()) return &entityRoot;
		return getEntityHierarchyLevel(&entityRoot, id);
	}

	/**
	 * Retrieve entity hierarchy level by given entity id or nullptr if not found
	 * @param entityHierarchyLevel entity hierarchy level
	 * @param id entity id
	 * @return entity hierarchy level by given entity id or nullptr if not found
	 */
	inline EntityHierarchyLevel* getEntityHierarchyLevel(EntityHierarchyLevel* entityHierarchyLevel, const string& id) {
		if (id == entityHierarchyLevel->id) return entityHierarchyLevel;
		for (auto& it: entityHierarchyLevel->children) {
			auto childEntityHierarchyLevel = getEntityHierarchyLevel(it.second, id);
			if (childEntityHierarchyLevel != nullptr) return childEntityHierarchyLevel;
		}
		return nullptr;
	}

	/**
	 * Update hierarchy from given entity hierarchy level ongoing
	 * @param parentTransform parent transform
	 * @param entityHierarchyLevel entity hierarchy level
	 * @param depth depth
	 * @param firstEntity first entity
	 */
	void updateHierarchy(const Transform& parentTransform, EntityHierarchyLevel* entityHierarchyLevel, int depth, bool& firstEntity);

public:
	/**
	 * Public constructor
	 * @param id id
	 */
	EntityHierarchy(const string& id);

	/**
	 * Destructor
	 */
	virtual ~EntityHierarchy();

	// overridden method
	inline EntityType getEntityType() override {
		return ENTITYTYPE_ENTITYHIERARCHY;
	}

	/**
	 * @return entity from hierarchy by given unique id
	 */
	Entity* getEntity(const string& id);

	/**
	 * Adds a entity to the hierarchy
	 * @param entity entity to add
	 * @param parentId parent entity id to add entity to
	 */
	void addEntity(Entity* entity, const string& parentId = string());

	/**
	 * Removes a entity from hierarchy by given unique entity id
	 */
	void removeEntity(const string& id);

	/**
	 * Query direct sub entities for given parent entity id
	 * @param parentId parent id to entities from
	 * @return entities
	 */
	const vector<Entity*> query(const string& parentId = string());

	/**
	 * @return entities
	 */
	inline const vector<Entity*>& getEntities() {
		return entities;
	}

	/**
	 * Returns first found entity with given entity type
	 * @param entityType entity type
	 * @return entity
	 */
	inline Entity* getEntityByType(EntityType entityType) {
		for (auto entity: entities) {
			if (entity->getEntityType() == entityType) {
				return entity;
			}
		}
		return nullptr;
	}

	/**
	 * Return entities with given entity type
	 * @param entityType entity type
	 * @return entities by type
	 */
	inline vector<Entity*> getEntitiesByType(EntityType entityType) {
		vector<Entity*> entitiesByType;
		for (auto entity: entities) {
			if (entity->getEntityType() == entityType) {
				entitiesByType.push_back(entity);
			}
		}
		return entitiesByType;
	}

	// overridden methods
	void setEngine(Engine* engine) override;
	void setRenderer(Renderer* renderer) override;
	void initialize() override;
	void dispose() override;

	inline bool isEnabled() override {
		return enabled;
	}

	void setEnabled(bool enabled) override;
	bool isFrustumCulling() override;
	void setFrustumCulling(bool frustumCulling) override;
	void update() override;

	inline BoundingBox* getBoundingBox() override {
		return &boundingBox;
	}

	inline BoundingBox* getWorldBoundingBox() override {
		return &worldBoundingBox;
	}

	inline const Color4& getEffectColorMul() const override {
		return effectColorMul;
	}

	inline void setEffectColorMul(const Color4& effectColorMul) override {
		this->effectColorMul = effectColorMul;
		for (auto entity: entities) entity->setEffectColorMul(effectColorMul);
	}

	inline const Color4& getEffectColorAdd() const override {
		return effectColorAdd;
	}

	inline void setEffectColorAdd(const Color4& effectColorAdd) override {
		this->effectColorAdd = effectColorAdd;
		for (auto entity: entities) entity->setEffectColorAdd(effectColorAdd);
	}

	inline const string& getId() override {
		return id;
	}

	inline bool isContributesShadows() override {
		return contributesShadows;
	}

	inline void setContributesShadows(bool contributesShadows) override {
		this->contributesShadows = contributesShadows;
		for (auto entity: entities) entity->setContributesShadows(contributesShadows);
	}

	inline bool isReceivesShadows() override {
		return receivesShadows;
	}

	inline void setReceivesShadows(bool receivesShadows) override {
		this->receivesShadows = receivesShadows;
		for (auto entity: entities) entity->setReceivesShadows(receivesShadows);
	}

	inline bool isPickable() override {
		return pickable;
	}

	inline void setPickable(bool pickable) override {
		this->pickable = pickable;
		for (auto entity: entities) entity->setPickable(pickable);
	}

	inline const Vector3& getTranslation() const override {
		return Transform::getTranslation();
	}

	inline void setTranslation(const Vector3& translation) override {
		Transform::setTranslation(translation);
	}

	inline const Vector3& getScale() const override {
		return Transform::getScale();
	}

	inline void setScale(const Vector3& scale) override {
		Transform::setScale(scale);
	}

	inline const int getRotationCount() const override {
		return Transform::getRotationCount();
	}

	inline Rotation& getRotation(const int idx) override {
		return Transform::getRotation(idx);
	}

	inline void addRotation(const Vector3& axis, const float angle) override {
		Transform::addRotation(axis, angle);
	}

	inline void removeRotation(const int idx) override {
		Transform::removeRotation(idx);
	}

	inline const Vector3& getRotationAxis(const int idx) const override {
		return Transform::getRotationAxis(idx);
	}

	inline void setRotationAxis(const int idx, const Vector3& axis) override {
		Transform::setRotationAxis(idx, axis);
	}

	inline const float getRotationAngle(const int idx) const override {
		return Transform::getRotationAngle(idx);
	}

	inline void setRotationAngle(const int idx, const float angle) override {
		Transform::setRotationAngle(idx, angle);
	}

	inline const Quaternion& getRotationsQuaternion() const override {
		return Transform::getRotationsQuaternion();
	}

	inline const Matrix4x4& getTransformMatrix() const override {
		return entityTransformMatrix;
	}

	inline const Transform& getParentTransform() const override {
		return parentTransform;
	}

	inline const Transform& getTransform() const override {
		return *this;
	}

	void setTransform(const Transform& transform) override;

	inline RenderPass getRenderPass() const override {
		return renderPass;
	}

	inline void setRenderPass(RenderPass renderPass) override {
		this->renderPass = renderPass;
	}

};
