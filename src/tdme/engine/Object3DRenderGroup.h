#pragma once

#include <array>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/LODObject3D.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
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
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Object 3D render group
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Object3DRenderGroup final:
	public Transformations,
	public Entity
{
private:
	Engine* engine { nullptr };
	bool frustumCulling { true };

	string id;
	bool enabled;
	bool pickable;
	bool dynamicShadowing;
	Color4 effectColorMul;
	Color4 effectColorAdd;
	BoundingBox boundingBox;
	BoundingBox boundingBoxTransformed;
	Matrix4x4 identityMatrix;
	Entity* combinedEntity;
	vector<Transformations> objectsTransformations;
	Model* model;
	vector<Model*> combinedModels;
	string shaderId { "default" };
	string distanceShaderId { "" };
	float distanceShaderDistance { 50.0f };
	array<int, 3> lodReduceBy;
	bool enableEarlyZRejection { false };

	/**
	 * Compute bounding box
	 */
	void computeBoundingBox();

	/**
	 * Combine group into given combined model
	 * @param sourceGroup source group to combine into current model
	 * @param parentTransformationsMatrix parent transformations matrix
	 * @param combinedModel combined model
	 * @param reduceFactorBy reduce factor by
	 */
	static void combineGroup(Group* sourceGroup, const vector<Matrix4x4>& objectParentTransformationsMatrices, Model* combinedModel);

	/**
	 * Combine model with transformations into current model
	 * @param model model
	 * @param transformations transformations
	 * @param combinedModel combined model
	 * @param reduceFactorBy reduce factor by
	 * @return model
	 */
	static void combineObjects(Model* model, const vector<Transformations>& objectsTransformations, Model* combinedModel);

public:
	// overriden methods
	void setEngine(Engine* engine) override;
	void setRenderer(Renderer* renderer) override;
	void fromTransformations(const Transformations& transformations) override;
	void update() override;
	void setEnabled(bool enabled) override;
	bool isFrustumCulling() override;
	void setFrustumCulling(bool frustumCulling) override;

	/**
	 * Public constructor
	 * @param id id
	 * @param model model
	 * @param lodLevels lod levels
	 * @param modelLOD2MinDistance model LOD 2 min distance
	 * @param modelLOD3MinDistance model LOD 3 min distance
	 * @param modelLOD2ReduceBy model LOD 2 reduce by factor
	 * @param modelLOD3ReduceBy model LOD 3 reduce by factor
	 */
	Object3DRenderGroup(
		const string& id,
		Model* model,
		int lodLevels = 1,
		float modelLOD2MinDistance = 25.0f,
		float modelLOD3MinDistance = 50.0f,
		int modelLOD2ReduceBy = 4,
		int modelLOD3ReduceBy = 16
	);

	/**
	 * Destructor
	 */
	~Object3DRenderGroup();

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
	 * @return entity
	 */
	inline Entity* getEntity() {
		return combinedEntity;
	}

	/**
	 * Adds a instance this render group
	 * @param transformations transformations
	 */
	void addObject(const Transformations& transformations);

	// overriden methods
	void dispose() override;

	inline BoundingBox* getBoundingBox() override {
		return &boundingBox;
	}

	inline BoundingBox* getBoundingBoxTransformed() override {
		return &boundingBoxTransformed;
	}

	inline const Color4& getEffectColorMul() const override {
		return effectColorMul;
	}

	inline void setEffectColorMul(const Color4& effectColorMul) override {
		this->effectColorMul = effectColorMul;
	}

	inline const Color4& getEffectColorAdd() const override {
		return effectColorAdd;
	}

	inline void setEffectColorAdd(const Color4& effectColorAdd) override {
		this->effectColorAdd = effectColorAdd;
	}

	inline const string& getId() override {
		return id;
	}

	void initialize() override;

	inline bool isDynamicShadowingEnabled() override {
		return dynamicShadowing;
	}

	inline bool isEnabled() override {
		return enabled;
	}

	inline bool isPickable() override {
		return pickable;
	}

	// override methods
	inline void setDynamicShadowingEnabled(bool dynamicShadowing) override {
		this->dynamicShadowing = dynamicShadowing;
		if (combinedEntity != nullptr) {
			combinedEntity->setDynamicShadowingEnabled(dynamicShadowing);
		}
	}

	inline void setPickable(bool pickable) override {
		if (combinedEntity != nullptr) {
			combinedEntity->setPickable(pickable);
		}
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
		return shaderId;
	}

	/**
	 * Set shader id
	 * @param id shader
	 */
	inline void setShader(const string& id) {
		this->shaderId = id;
		// TODO: put me into entity interface
		if (dynamic_cast<Object3D*>(combinedEntity) != nullptr) {
			dynamic_cast<Object3D*>(combinedEntity)->setShader(id);
		} else
		if (dynamic_cast<LODObject3D*>(combinedEntity) != nullptr) {
			dynamic_cast<LODObject3D*>(combinedEntity)->setShader(id);
		}
	}

	/**
	 * @return distance shader id
	 */
	inline const string& getDistanceShader() {
		return distanceShaderId;
	}

	/**
	 * Set distance shader id
	 * @param id shader
	 */
	inline void setDistanceShader(const string& id) {
		this->distanceShaderId = id;
		// TODO: put me into entity interface
		if (dynamic_cast<Object3D*>(combinedEntity) != nullptr) {
			dynamic_cast<Object3D*>(combinedEntity)->setDistanceShader(id);
		} else
		if (dynamic_cast<LODObject3D*>(combinedEntity) != nullptr) {
			dynamic_cast<LODObject3D*>(combinedEntity)->setDistanceShader(id);
		}
	}

	/**
	 * @return distance shader distance
	 */
	inline float getDistanceShaderDistance() {
		return distanceShaderDistance;
	}

	/**
	 * Set distance shader distance
	 * @param distanceShaderDistance shader
	 */
	inline void setDistanceShaderDistance(float distanceShaderDistance) {
		this->distanceShaderDistance = distanceShaderDistance;
		// TODO: put me into entity interface
		if (dynamic_cast<Object3D*>(combinedEntity) != nullptr) {
			dynamic_cast<Object3D*>(combinedEntity)->setDistanceShaderDistance(distanceShaderDistance);
		} else
		if (dynamic_cast<LODObject3D*>(combinedEntity) != nullptr) {
			dynamic_cast<LODObject3D*>(combinedEntity)->setDistanceShaderDistance(distanceShaderDistance);
		}
	}

	/**
	 * @return If early z rejection is enabled
	 */
	bool isEnableEarlyZRejection() const {
		return enableEarlyZRejection;
	}

	/**
	 * Enable/disable early z rejection
	 * @param enableEarlyZRejection enable early z rejection
	 */
	inline void setEnableEarlyZRejection(bool enableEarlyZRejection) {
		this->enableEarlyZRejection = enableEarlyZRejection;
	}

};
