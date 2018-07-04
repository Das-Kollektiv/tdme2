#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
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
	bool groupRendering { true };

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
	Model* model {  };
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
	static void combineObject(Model* model, const Transformations& transformations, Model* combinedModel);

	/**
	 * Update render group model and bounding box
	 */
	void updateRenderGroup();

public:
	// overriden methods
	void setEngine(Engine* engine) override;
	void setRenderer(GLRenderer* renderer) override;
	void fromTransformations(const Transformations& transformations) override;
	void update() override;
	void setEnabled(bool enabled) override;
	bool isFrustumCulling() override;
	void setFrustumCulling(bool frustumCulling) override;

	/**
	 * @return if is using group rendering
	 */
	inline bool isGroupRendering() {
		return groupRendering;
	}

	/**
	 * Set if to use group rendering
	 * @param group rendering
	 */
	inline void setGroupRendering(bool groupRendering) {
		this->groupRendering = groupRendering;
	}

	/**
	 * Public constructor
	 * @param id
	 * @param model
	 */
	Object3DRenderGroup(const string& id, Model* model);

	/**
	 * Destructor
	 */
	virtual ~Object3DRenderGroup();

public:

	/**
	 * @return associated model
	 */
	inline Model* getModel() {
		return model;
	}

	/**
	 * Set model
	 * @param model
	 */
	void setModel(Model* model);

	/**
	 * @return objects
	 */
	inline vector<Object3D*>& getObjects() {
		return objects;
	}

	/**
	 * Adds a instance this render group
	 * @param model
	 * @param transformations
	 */
	void addObject(const Transformations& transformations);

	// overriden methods
	virtual void dispose() override;

	inline virtual BoundingBox* getBoundingBox() override {
		return &boundingBox;
	}

	inline virtual BoundingBox* getBoundingBoxTransformed() override {
		return &boundingBoxTransformed;
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

	// override methods
	inline virtual void setDynamicShadowingEnabled(bool dynamicShadowing) override {
		this->dynamicShadowing = dynamicShadowing;
	}

	inline virtual void setPickable(bool pickable) override {
		this->pickable = pickable;
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

};
