#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/Object3DInternal.h>
#include <tdme/engine/Entity.h>
#include <tdme/utils/Console.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::rendering::Object3DInternal;
using tdme::engine::Entity;
using tdme::engine::Engine;
using tdme::engine::Object3D;
using tdme::engine::Rotation;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utils::Console;

/** 
 * LOD Object 3D
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::LODObject3D final:
	public Transformations,
	public Entity
{
public:
	enum LODLevelType { LODLEVELTYPE_NONE, LODLEVELTYPE_MODEL, LODLEVELTYPE_IGNORE };

private:
	Engine* engine { nullptr };
	bool frustumCulling { true };

	Model* modelLOD1;
	Model* modelLOD2;
	Model* modelLOD3;
	float modelLOD2MinDistance;
	float modelLOD3MinDistance;
	LODLevelType levelTypeLOD2;
	LODLevelType levelTypeLOD3;

	string id;
	Object3D* objectLOD1 {  };
	Object3D* objectLOD2 {  };
	Object3D* objectLOD3 {  };
	Object3D* objectLOD {  };
	int levelLOD {  };
	bool enabled {  };
	bool pickable {  };
	bool dynamicShadowing {  };
	Color4 effectColorMul {  };
	Color4 effectColorAdd {  };
	Color4 effectColorMulLOD2 {  };
	Color4 effectColorAddLOD2 {  };
	Color4 effectColorMulLOD3 {  };
	Color4 effectColorAddLOD3 {  };
	string shaderId { "default" };
	string distanceShaderId { "" };
	float distanceShaderDistance { 50.0f };

public:
	void setEngine(Engine* engine) override;
	void setRenderer(GLRenderer* renderer) override;
	void fromTransformations(const Transformations& transformations) override;
	void update() override;
	void setEnabled(bool enabled) override;
	bool isFrustumCulling() override;
	void setFrustumCulling(bool frustumCulling) override;

	/**
	 * Public constructor
	 * @param id id
	 * @param modelLOD1 model LOD 1
	 * @param levelTypeLOD2 LOD level type LOD2
	 * @param modelLOD2MinDistance model LOD 2 min distance
	 * @param modelLOD2 model LOD 2
	 * @param levelTypeLOD3 LOD level type LOD3
	 * @param modelLOD3MinDistance model LOD 3 min distance
	 * @param modelLOD3 model LOD 3
	 * @param planeRotationYLOD2 model LOD2 plane rotation around Y axis
	 * @param planeRotationYLOD3 model LOD3 plane rotation around Y axis
	 */
	LODObject3D(
		const string& id,
		Model* modelLOD1,
		LODLevelType levelTypeLOD2,
		float modelLOD2MinDistance,
		Model* modelLOD2,
		LODLevelType levelTypeLOD3,
		float modelLOD3MinDistance,
		Model* modelLOD3
	);

public:
	/**
	 * @return LOD object
	 */
	inline Object3D* getLODObject() {
		// set effect colors
		if (objectLOD != nullptr) {
			// set effect colors
			if (objectLOD != nullptr) {
				if (levelLOD == 3) {
					objectLOD->setEffectColorAdd(effectColorAddLOD3);
					objectLOD->setEffectColorMul(effectColorMulLOD3);
				} else
				if (levelLOD == 2) {
					objectLOD->setEffectColorAdd(effectColorAddLOD2);
					objectLOD->setEffectColorMul(effectColorMulLOD2);
				} else {
					objectLOD->setEffectColorAdd(Color4(0.0f, 0.0f, 0.0f, 0.0f));
					objectLOD->setEffectColorMul(Color4(1.0f, 1.0f, 1.0f, 1.0f));
				}
				auto effectColorAdd = objectLOD->getEffectColorAdd();
				auto effectColorMul = objectLOD->getEffectColorMul();
				effectColorAdd.add(this->effectColorAdd);
				effectColorMul.scale(this->effectColorMul);
				objectLOD->setEffectColorAdd(effectColorAdd);
				objectLOD->setEffectColorMul(effectColorMul);
			}
		}

		//
		return objectLOD;
	}

	/**
	 * Get current lod object
	 * @param camera camera
	 * @return LOD object to render
	 */
	inline Object3D* determineLODObject(Camera* camera) {
		if (objectLOD == nullptr || camera->hasFrustumChanged() == true) {
			LODObject3D::LODLevelType lodLevelType = LODObject3D::LODLEVELTYPE_NONE;
			Vector3 objectCamFromAxis;
			float objectCamFromLengthSquared;
			float planeRotationYLOD;

			// determine LOD object and level type
			if (levelTypeLOD3 != LODLEVELTYPE_NONE &&
				(objectCamFromLengthSquared = objectCamFromAxis.set(getBoundingBoxTransformed()->getCenter()).sub(camera->getLookFrom()).computeLengthSquared()) >= Math::square(modelLOD3MinDistance)) {
				lodLevelType = levelTypeLOD3;
				objectLOD = objectLOD3;
				levelLOD = 3;
			} else
			if (levelTypeLOD2 != LODLEVELTYPE_NONE &&
				(objectCamFromLengthSquared = objectCamFromAxis.set(getBoundingBoxTransformed()->getCenter()).sub(camera->getLookFrom()).computeLengthSquared()) >= Math::square(modelLOD2MinDistance)) {
				lodLevelType = levelTypeLOD2;
				objectLOD = objectLOD2;
				levelLOD = 2;
			} else {
				objectLOD = objectLOD1;
				levelLOD = 1;
			}
		}

		// set effect colors
		if (objectLOD != nullptr) {
			if (levelLOD == 3) {
				objectLOD->setEffectColorAdd(effectColorAddLOD3);
				objectLOD->setEffectColorMul(effectColorMulLOD3);
			} else
			if (levelLOD == 2) {
				objectLOD->setEffectColorAdd(effectColorAddLOD2);
				objectLOD->setEffectColorMul(effectColorMulLOD2);
			} else {
				objectLOD->setEffectColorAdd(Color4(0.0f, 0.0f, 0.0f, 0.0f));
				objectLOD->setEffectColorMul(Color4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			auto effectColorAdd = objectLOD->getEffectColorAdd();
			auto effectColorMul = objectLOD->getEffectColorMul();
			effectColorAdd.add(this->effectColorAdd);
			effectColorMul.scale(this->effectColorMul);
			objectLOD->setEffectColorAdd(effectColorAdd);
			objectLOD->setEffectColorMul(effectColorMul);
		}

		// done
		return objectLOD;
	}

	/**
	 * @return effect color add for LOD2 level
	 */
	inline virtual const Color4& getEffectColorAddLOD2() const {
		return effectColorAddLOD2;
	}

	/**
	 * Set effect color add for LOD2 level
	 * @param effectColorAddLOD2 effect color add for LOD2 level
	 */
	inline void setEffectColorAddLOD2(const Color4& effectColorAddLOD2) {
		this->effectColorAddLOD2 = effectColorAddLOD2;
	}

	/**
	 * @return effect color mul for LOD2 level
	 */
	inline virtual const Color4& getEffectColorMulLOD2() const {
		return effectColorMulLOD2;
	}

	/**
	 * Set effect color mul for LOD2 level
	 * @param effectColorMulLOD2 effect color mul for LOD2 level
	 */
	inline void setEffectColorMulLOD2(const Color4& effectColorMulLOD2) {
		this->effectColorMulLOD2 = effectColorMulLOD2;
	}

	/**
	 * @return effect color add for LOD3 level
	 */
	inline virtual const Color4& getEffectColorAddLOD3() const {
		return effectColorAddLOD3;
	}

	/**
	 * Set effect color add for LOD3 level
	 * @param effectColorAddLOD3 effect color add for LOD3 level
	 */
	inline void setEffectColorAddLOD3(const Color4& effectColorAddLOD3) {
		this->effectColorAddLOD3 = effectColorAddLOD3;
	}

	/**
	 * @return effect color mul for LOD3 level
	 */
	inline virtual const Color4& getEffectColorMulLOD3() const {
		return effectColorMulLOD3;
	}

	/**
	 * Set effect color mul for LOD3 level
	 * @param effectColorMulLOD3 effect color mul for LOD3 level
	 */
	inline void setEffectColorMulLOD3(const Color4& effectColorMulLOD3) {
		this->effectColorMulLOD3 = effectColorMulLOD3;
	}

	// overriden methods
	virtual void dispose() override;

	inline virtual BoundingBox* getBoundingBox() override {
		return objectLOD1->getBoundingBox();
	}

	inline virtual BoundingBox* getBoundingBoxTransformed() override {
		return objectLOD1->getBoundingBoxTransformed();
	}

	inline virtual const Color4& getEffectColorMul() const override {
		return effectColorMul;
	}

	inline virtual void setEffectColorMul(const Color4& effectColorMul) override {
		this->effectColorMul = effectColorMul;
	}

	inline virtual const Color4& getEffectColorAdd() const override {
		return effectColorAdd;
	}

	inline virtual void setEffectColorAdd(const Color4& effectColorAdd) override {
		this->effectColorAdd = effectColorAdd;
	}

	inline virtual const string& getId() override {
		return id;
	}

	virtual void initialize() override;

	inline virtual bool isDynamicShadowingEnabled() override {
		return dynamicShadowing;
	}

	inline virtual bool isEnabled() override {
		return enabled;
	}

	inline virtual bool isPickable() override {
		return pickable;
	}

	inline virtual void setDynamicShadowingEnabled(bool dynamicShadowing) override {
		this->dynamicShadowing = dynamicShadowing;
		// delegate to LOD objects
		if (objectLOD1 != nullptr) objectLOD1->setDynamicShadowingEnabled(dynamicShadowing);
		if (objectLOD2 != nullptr) objectLOD2->setDynamicShadowingEnabled(dynamicShadowing);
		if (objectLOD3 != nullptr) objectLOD3->setDynamicShadowingEnabled(dynamicShadowing);
	}

	inline virtual void setPickable(bool pickable) override {
		this->pickable = pickable;
	}

	inline virtual Matrix4x4* getTransformationsMatrix(const string& id) {
		return objectLOD1->getTransformationsMatrix(id);
	}

	inline virtual const Vector3& getTranslation() const override {
		return Transformations::getTranslation();
	}

	inline virtual void setTranslation(const Vector3& translation) override {
		Transformations::setTranslation(translation);
	}

	inline virtual const Vector3& getScale() const override {
		return Transformations::getScale();
	}

	inline virtual void setScale(const Vector3& scale) override {
		Transformations::setScale(scale);
	}

	inline virtual const Vector3& getPivot() const override {
		return Transformations::getPivot();
	}

	inline virtual void setPivot(const Vector3& pivot) override {
		Transformations::setPivot(pivot);
	}

	inline virtual const int getRotationCount() const override {
		return Transformations::getRotationCount();
	}

	inline virtual Rotation& getRotation(const int idx) override {
		return Transformations::getRotation(idx);
	}

	inline virtual void addRotation(const Vector3& axis, const float angle) override {
		Transformations::addRotation(axis, angle);
	}

	inline virtual void removeRotation(const int idx) override {
		Transformations::removeRotation(idx);
	}

	inline virtual const Vector3& getRotationAxis(const int idx) const override {
		return Transformations::getRotationAxis(idx);
	}

	inline virtual void setRotationAxis(const int idx, const Vector3& axis) override {
		Transformations::setRotationAxis(idx, axis);
	}

	inline virtual const float getRotationAngle(const int idx) const override {
		return Transformations::getRotationAngle(idx);
	}

	inline virtual void setRotationAngle(const int idx, const float angle) override {
		Transformations::setRotationAngle(idx, angle);
	}

	inline virtual const Quaternion& getRotationsQuaternion() const override {
		return Transformations::getRotationsQuaternion();
	}

	inline virtual const Matrix4x4& getTransformationsMatrix() const override {
		return Transformations::getTransformationsMatrix();
	}

	inline virtual const Transformations& getTransformations() const override {
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
		if (objectLOD1 != nullptr) objectLOD1->setShader(shaderId);
		if (objectLOD2 != nullptr) objectLOD2->setShader(shaderId);
		if (objectLOD3 != nullptr) objectLOD3->setShader(shaderId);
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
		if (objectLOD1 != nullptr) objectLOD1->setDistanceShader(distanceShaderId);
		if (objectLOD2 != nullptr) objectLOD2->setDistanceShader(distanceShaderId);
		if (objectLOD3 != nullptr) objectLOD3->setDistanceShader(distanceShaderId);
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
		if (objectLOD1 != nullptr) objectLOD1->setDistanceShaderDistance(distanceShaderDistance);
		if (objectLOD2 != nullptr) objectLOD2->setDistanceShaderDistance(distanceShaderDistance);
		if (objectLOD3 != nullptr) objectLOD3->setDistanceShaderDistance(distanceShaderDistance);
	}

};
