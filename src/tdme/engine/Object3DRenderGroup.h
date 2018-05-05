#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Camera.h>
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
#include <tdme/utils/Console.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::Entity;
using tdme::engine::Engine;
using tdme::engine::Rotation;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utils::Console;

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
	bool enabled {  };
	bool pickable {  };
	bool dynamicShadowing {  };
	Color4 effectColorMul {  };
	Color4 effectColorAdd {  };
	BoundingBox boundingBox {  };
	BoundingBox boundingBoxTransformed {  };
	Matrix4x4 identityMatrix {  };
	vector<Object3D*> objects {  };
	vector<Object3D*> objectsCombined {  };
	Model* combinedModel {  };

	/**
	 * Compute bounding box
	 */
	void computeBoundingBox();

	/**
	 * Combine group into given combined model
	 * @param source group to combine into current model
	 * @param parent transformations matrix
	 * @param combined model
	 */
	static void combineGroup(Group* sourceGroup, const Matrix4x4& parentTransformationsMatrix, Model* combinedModel);

	/**
	 * Combine model with transformations into current model
	 * @param model
	 * @param transformations
	 * @param combined model
	 * @return model
	 */
	static void combine(Model* model, const Transformations& transformations, Model* combinedModel);

	/**
	 * Update render group model and bounding box
	 */
	void updateRenderGroup();

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
	 */
	Object3DRenderGroup(const string& id);

	/**
	 * Destructor
	 */
	virtual ~Object3DRenderGroup();

public:
	/**
	 * @return objects
	 */
	inline vector<Object3D*>& getObjects() {
		return objectsCombined.size() > 0?objectsCombined:objects;
	}

	/**
	 * Adds a object to this render group
	 * @param object
	 */
	void addObject(Object3D* object);

	// overriden methods
	virtual void dispose() override;

	inline virtual BoundingBox* getBoundingBox() override {
		return &boundingBox;
	}

	inline virtual BoundingBox* getBoundingBoxTransformed() override {
		return &boundingBoxTransformed;
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
