#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/Object3DGroup.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupVBORenderer.h>
#include <tdme/engine/subsystems/rendering/Object3DInternal.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Quaternion.h>

using std::string;

using tdme::engine::Entity;
using tdme::engine::Engine;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::engine::subsystems::rendering::Object3DGroupVBORenderer;
using tdme::engine::subsystems::rendering::Object3DInternal;
using tdme::engine::subsystems::shadowmapping::ShadowMap;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::math::Quaternion;

/** 
 * Object 3D to be used with engine class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Object3D final
	: public Object3DInternal
	, public Entity
{

private:
	friend class Engine;
	friend class LODObject3D;
	friend class ObjectParticleSystemEntity;
	friend class tdme::engine::subsystems::shadowmapping::ShadowMap;


	Engine* engine { nullptr };
	Entity* parentEntity { nullptr };
	bool frustumCulling { true };
	string shaderId { "default" };
	string distanceShaderId { "" };
	float distanceShaderDistance { 50.0f };

	/**
	 * Compute skinning
	 */
	inline void computeSkinning() {
		if (hasSkinning == true) computeTransformations();
	}

	/**
	 * Pre render step like uploading VBOs and such
	 */
	inline void preRender() {
		for (auto object3DGroup: object3dGroups) {
			if (object3DGroup->renderer->needsPreRender() == true) {
				object3DGroup->renderer->preRender();
			}
		}
	}

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
	 * @param model model
	 */
	Object3D(const string& id, Model* model);

public:
	// overriden methods
	virtual void dispose() override;

	inline virtual BoundingBox* getBoundingBox() override {
		return Object3DInternal::getBoundingBox();
	}

	inline virtual BoundingBox* getBoundingBoxTransformed() override {
		return Object3DInternal::getBoundingBoxTransformed();
	}

	inline virtual const Color4& getEffectColorAdd() const override {
		return Object3DInternal::getEffectColorAdd();
	}

	inline virtual void setEffectColorAdd(const Color4& effectColorAdd) override {
		return Object3DInternal::setEffectColorAdd(effectColorAdd);
	}

	inline virtual const Color4& getEffectColorMul() const override {
		return Object3DInternal::getEffectColorMul();
	}

	inline virtual void setEffectColorMul(const Color4& effectColorMul) override {
		return Object3DInternal::setEffectColorMul(effectColorMul);
	}

	inline virtual const string& getId() override {
		return Object3DInternal::getId();
	}

	virtual void initialize() override;

	inline virtual bool isDynamicShadowingEnabled() override {
		return Object3DInternal::isDynamicShadowingEnabled();
	}

	inline virtual bool isEnabled() override {
		return Object3DInternal::isEnabled();
	}

	inline virtual bool isPickable() override {
		return Object3DInternal::isPickable();
	}

	inline virtual void setDynamicShadowingEnabled(bool dynamicShadowing) override {
		Object3DInternal::setDynamicShadowingEnabled(dynamicShadowing);
	}

	inline virtual void setPickable(bool pickable) override {
		Object3DInternal::setPickable(pickable);
	}

	inline virtual Matrix4x4* getTransformationsMatrix(const string& id) override {
		return Object3DInternal::getTransformationsMatrix(id);
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

	inline void computeTransformations() {
		Object3DInternal::computeTransformations(engine->getTiming());
	}

	/**
	 * @return shader id
	 */
	inline const string& getShader() {
		return shaderId;
	}

	/**
	 * Set shader
	 * @param id shader id
	 */
	inline void setShader(const string& id) {
		shaderId = id;
	}

	/**
	 * @return distance shader id
	 */
	inline const string& getDistanceShader() {
		return distanceShaderId;
	}

	/**
	 * Set distance shader
	 * @param id shader id
	 */
	inline void setDistanceShader(const string& id) {
		distanceShaderId = id;
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
	}

};
