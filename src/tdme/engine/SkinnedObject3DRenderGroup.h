#pragma once

#include <array>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/engine/Entity.h>

using std::array;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::Entity;
using tdme::engine::Engine;
using tdme::engine::Object3D;
using tdme::engine::LODObject3D;
using tdme::engine::Rotation;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::Object3DAnimation;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Object 3D render group for skinned objects
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::SkinnedObject3DRenderGroup final:
	public Transformations,
	public Entity
{
private:
	Engine* engine { nullptr };
	Entity* parentEntity { nullptr };
	bool frustumCulling { true };

	string id;
	BoundingBox boundingBox;
	BoundingBox boundingBoxTransformed;
	Model* model { nullptr };
	int objectCount;
	vector<Transformations> objectTransformations;
	vector<Object3DAnimation*> objectAnimations;
	Object3D* object { nullptr };

	/**
	 * Compute bounding box
	 */
	void updateBoundingBox();

	// overridden methods
	inline void setParentEntity(Entity* entity) override {
		this->parentEntity = entity;
	}
	inline Entity* getParentEntity() override {
		return parentEntity;
	}
	inline void applyParentTransformations(const Transformations& parentTransformations) override {
		Transformations::applyParentTransformations(parentTransformations);
		updateBoundingBox();
	}

public:
	// overriden methods
	inline void setEngine(Engine* engine) override {
		this->engine = engine;
		object->setEngine(engine);
	}
	inline void setRenderer(Renderer* renderer) override {
		object->setRenderer(renderer);
	}
	void fromTransformations(const Transformations& transformations) override;
	void update() override;
	void setEnabled(bool enabled) override;
	bool isFrustumCulling() override;
	void setFrustumCulling(bool frustumCulling) override;

	/**
	 * Public constructor
	 * @param id id
	 * @param model model
	 * @param objectCount object count
	 */
	SkinnedObject3DRenderGroup(
		const string& id,
		Model* model,
		int objectCount
	);

	/**
	 * Destructor
	 */
	virtual ~SkinnedObject3DRenderGroup();

	/**
	 * Update render group model and bounding box
	 */
	void updateRenderGroup();

public:

	/**
	 * @return associated model
	 */
	inline Model* getModel() {
		return model;
	}

	/**
	 * Set model
	 * @param model model
	 */
	void setModel(Model* model);

	/**
	 * @return object
	 */
	inline Object3D* getObject() {
		return object;
	}

	/**
	 *@return object 3d animation for given index
	 */
	inline Object3DAnimation* getObjectAnimation(int idx) {
		return objectAnimations[idx];
	}

	/**
	 *@return object 3d transformations for given index
	 */
	inline Transformations& getObjectTransformations(int idx) {
		return objectTransformations[idx];
	}

	// overriden methods
	void dispose() override;

	inline BoundingBox* getBoundingBox() override {
		return &boundingBox;
	}

	inline BoundingBox* getBoundingBoxTransformed() override {
		return &boundingBoxTransformed;
	}

	inline const Color4& getEffectColorMul() const override {
		return object->getEffectColorMul();
	}

	inline void setEffectColorMul(const Color4& effectColorMul) override {
		object->setEffectColorMul(getEffectColorMul());
	}

	inline const Color4& getEffectColorAdd() const override {
		return object->getEffectColorAdd();
	}

	inline void setEffectColorAdd(const Color4& effectColorAdd) override {
		object->setEffectColorAdd(effectColorAdd);
	}

	inline const string& getId() override {
		return id;
	}

	void initialize() override;

	inline bool isEnabled() override {
		return object->isEnabled();
	}

	inline bool isPickable() override {
		return object->isPickable();
	}

	inline bool isContributesShadows() override {
		return object->isContributesShadows();
	}

	inline void setContributesShadows(bool contributesShadows) override {
		return object->setContributesShadows(contributesShadows);
	}

	inline bool isReceivesShadows() override {
		return object->isReceivesShadows();
	}

	inline void setReceivesShadows(bool receivesShadows) override {
		object->setReceivesShadows(receivesShadows);
	}

	inline void setPickable(bool pickable) override {
		object->setPickable(pickable);
	}

	inline const Vector3& getTranslation() const override {
		return Transformations::getTranslation();
	}

	inline void setTranslation(const Vector3& translation) override {
		Transformations::setTranslation(translation);
	}

	inline const Vector3& getScale() const override {
		return Transformations::getScale();
	}

	inline void setScale(const Vector3& scale) override {
		Transformations::setScale(scale);
	}

	inline const Vector3& getPivot() const override {
		return Transformations::getPivot();
	}

	inline void setPivot(const Vector3& pivot) override {
		Transformations::setPivot(pivot);
	}

	inline const int getRotationCount() const override {
		return Transformations::getRotationCount();
	}

	inline Rotation& getRotation(const int idx) override {
		return Transformations::getRotation(idx);
	}

	inline void addRotation(const Vector3& axis, const float angle) override {
		Transformations::addRotation(axis, angle);
	}

	inline void removeRotation(const int idx) override {
		Transformations::removeRotation(idx);
	}

	inline const Vector3& getRotationAxis(const int idx) const override {
		return Transformations::getRotationAxis(idx);
	}

	inline void setRotationAxis(const int idx, const Vector3& axis) override {
		Transformations::setRotationAxis(idx, axis);
	}

	inline const float getRotationAngle(const int idx) const override {
		return Transformations::getRotationAngle(idx);
	}

	inline void setRotationAngle(const int idx, const float angle) override {
		Transformations::setRotationAngle(idx, angle);
	}

	inline const Quaternion& getRotationsQuaternion() const override {
		return Transformations::getRotationsQuaternion();
	}

	inline const Matrix4x4& getTransformationsMatrix() const override {
		return Transformations::getTransformationsMatrix();
	}

	inline const Transformations& getTransformations() const override {
		return *this;
	}

	/**
	 * @return shader id
	 */
	inline const string& getShader() {
		return object->getShader();
	}

	/**
	 * Set shader id
	 * @param id shader
	 */
	inline void setShader(const string& id) {
		object->setShader(id);
	}

	/**
	 * @return distance shader id
	 */
	inline const string& getDistanceShader() {
		return object->getDistanceShader();
	}

	/**
	 * Set distance shader id
	 * @param id shader
	 */
	inline void setDistanceShader(const string& id) {
		object->setDistanceShader(id);
	}

	/**
	 * @return distance shader distance
	 */
	inline float getDistanceShaderDistance() {
		return object->getDistanceShaderDistance();
	}

	/**
	 * Set distance shader distance
	 * @param distanceShaderDistance shader
	 */
	inline void setDistanceShaderDistance(float distanceShaderDistance) {
		object->setDistanceShaderDistance(distanceShaderDistance);
	}

	/**
	 * @return If early z rejection is enabled
	 */
	bool isEnableEarlyZRejection() const {
		return object->isEnableEarlyZRejection();
	}

	/**
	 * Enable/disable early z rejection
	 * @param enableEarlyZRejection enable early z rejection
	 */
	inline void setEnableEarlyZRejection(bool enableEarlyZRejection) {
		object->setEnableEarlyZRejection(enableEarlyZRejection);
	}

};
