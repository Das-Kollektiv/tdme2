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
	enum LODLevelType { LODLEVELTYPE_NONE, LODLEVELTYPE_MODEL, LODLEVELTYPE_PLANE, LODLEVELTYPE_IGNORE };

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
	int transformationsRotationYIndex;
	float planeRotationYLOD2;
	float planeRotationYLOD3;

	string id;
	Object3D* objectLOD1 {  };
	Object3D* objectLOD2 {  };
	Object3D* objectLOD3 {  };
	Object3D* objectLOD {  };
	bool enabled {  };
	bool pickable {  };
	bool dynamicShadowing {  };
	Color4 effectColorMul {  };
	Color4 effectColorAdd {  };

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
	 * @param id
	 * @param LOD level type LOD1
	 * @param model LOD 1
	 * @param LOD level type LOD2
	 * @param model LOD 2 min distance
	 * @param model LOD 2
	 * @param LOD level type LOD3
	 * @param model LOD 3 min distance
	 * @param model LOD 3
	 * @param model LOD2 axis Y index
	 * @param model LOD3 axis Y index
	 */
	LODObject3D(
		const string& id,
		Model* modelLOD1,
		LODLevelType levelTypeLOD2,
		float modelLOD2MinDistance,
		Model* modelLOD2,
		LODLevelType levelTypeLOD3,
		float modelLOD3MinDistance,
		Model* modelLOD3,
		float planeRotationYLOD2 = 0.0f,
		float planeRotationYLOD3 = 0.0f
	);

public:
	/**
	 * @return LOD object
	 */
	inline Object3D* getLODObject() {
		return objectLOD;
	}

	/**
	 * Get current lod object
	 * @param camera
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
				(objectCamFromLengthSquared = objectCamFromAxis.set(getTranslation()).sub(camera->getLookFrom()).computeLengthSquared()) >= Math::square(modelLOD3MinDistance)) {
				lodLevelType = levelTypeLOD3;
				planeRotationYLOD = planeRotationYLOD3;
				objectLOD = objectLOD3;
			} else
			if (levelTypeLOD2 != LODLEVELTYPE_NONE &&
				(objectCamFromLengthSquared = objectCamFromAxis.set(getTranslation()).sub(camera->getLookFrom()).computeLengthSquared()) >= Math::square(modelLOD2MinDistance)) {
				lodLevelType = levelTypeLOD2;
				planeRotationYLOD = planeRotationYLOD2;
				objectLOD = objectLOD2;
			} else {
				objectLOD = objectLOD1;
			}

			// do plane rotation to viewer on Y axis
			// TODO: unsure here, works but need to find a better way
			if (objectLOD != nullptr &&
				lodLevelType == LODLEVELTYPE_PLANE &&
				transformationsRotationYIndex != -1 &&
				objectCamFromLengthSquared > Math::square(Math::EPSILON)) {
				objectCamFromAxis.normalize();
				auto angle = Vector3::computeAngle(Rotation::Z_AXIS, objectCamFromAxis, Rotation::Y_AXIS);
				objectLOD->setRotationAngle(
					transformationsRotationYIndex,
					planeRotationYLOD + 90 + angle
				);
				objectLOD->update();
			}
		}

		return objectLOD;
	}

	/**
	 * @return LOD object 1
	 */
	Object3D* getObjectLOD1();

	/**
	 * @return LOD object 2
	 */
	Object3D* getObjectLOD2();

	/**
	 * @return LOD object 3
	 */
	Object3D* getObjectLOD3();

	// overriden methods
	virtual void dispose() override;

	inline virtual BoundingBox* getBoundingBox() override {
		return objectLOD1->getBoundingBox();
	}

	inline virtual BoundingBox* getBoundingBoxTransformed() override {
		return objectLOD1->getBoundingBoxTransformed();
	}

	inline virtual Color4& getEffectColorAdd() override {
		return effectColorAdd;
	}

	inline virtual Color4& getEffectColorMul() override {
		return effectColorMul;
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

	virtual Matrix4x4* getTransformationsMatrix(const string& id);

	// override methods
	virtual void setDynamicShadowingEnabled(bool dynamicShadowing) override;
	virtual void setPickable(bool pickable) override;
	virtual const Vector3& getTranslation() const override;
	virtual void setTranslation(const Vector3& translation) override;
	virtual const Vector3& getScale() const override;
	virtual void setScale(const Vector3& scale) override;
	virtual const Vector3& getPivot() const override;
	virtual void setPivot(const Vector3& pivot) override;
	virtual const int getRotationCount() const override;
	virtual Rotation& getRotation(const int idx) override;
	virtual void addRotation(const Vector3& axis, const float angle) override;
	virtual void removeRotation(const int idx) override;
	virtual const Vector3& getRotationAxis(const int idx) const override;
	virtual void setRotationAxis(const int idx, const Vector3& axis) override;
	virtual const float getRotationAngle(const int idx) const override;
	virtual void setRotationAngle(const int idx, const float angle) override;
	virtual const Quaternion& getRotationsQuaternion() const override;

	inline virtual const Matrix4x4& getTransformationsMatrix() const override {
		return Transformations::getTransformationsMatrix();
	}

	inline virtual const Transformations& getTransformations() const override {
		return *this;
	}
};
