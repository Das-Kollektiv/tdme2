#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/lines/LinesObject3DInternal.h>
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
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::lines::LinesObject3DInternal;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::math::Quaternion;

/** 
 * Object 3D to be used with engine class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::LinesObject3D final
	: public LinesObject3DInternal
	, public Entity
{

public:

private:
	friend class Engine;

	Engine* engine { nullptr };
	Entity* parentEntity { nullptr };
	bool frustumCulling { true };

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
	void setEngine(Engine* engine) override;
	inline void setRenderer(Renderer* renderer) override {
		LinesObject3DInternal::setRenderer(renderer);
	}
	void fromTransformations(const Transformations& transformations) override;
	void update() override;
	void setEnabled(bool enabled) override;
	bool isFrustumCulling() override;
	void setFrustumCulling(bool frustumCulling) override;

	/**
	 * Public constructor
	 * @param id id
	 * @param lineWidth line width
	 * @param points points
	 * @param color color
	 * @param colors optional colors
	 * @param texture optional texture
	 */
	LinesObject3D(const string& id, float lineWidth, const vector<Vector3>& points, const Color4& color, const vector<Color4>& colors = {}, Texture* texture = nullptr);

	// overriden methods
	void dispose() override;

	inline BoundingBox* getBoundingBox() override {
		return LinesObject3DInternal::getBoundingBox();
	}

	inline BoundingBox* getBoundingBoxTransformed() override {
		return LinesObject3DInternal::getBoundingBoxTransformed();
	}

	inline const Color4& getEffectColorAdd() const override {
		return LinesObject3DInternal::getEffectColorAdd();
	}

	inline void setEffectColorAdd(const Color4& effectColorAdd) override {
		return LinesObject3DInternal::setEffectColorAdd(effectColorAdd);
	}

	inline const Color4& getEffectColorMul() const override {
		return LinesObject3DInternal::getEffectColorMul();
	}

	inline void setEffectColorMul(const Color4& effectColorMul) override {
		return LinesObject3DInternal::setEffectColorMul(effectColorMul);
	}

	inline const string& getId() override {
		return LinesObject3DInternal::getId();
	}

	void initialize() override;

	inline bool isDynamicShadowingEnabled() override {
		return LinesObject3DInternal::isDynamicShadowingEnabled();
	}

	inline bool isEnabled() override {
		return LinesObject3DInternal::isEnabled();
	}

	inline bool isPickable() override {
		return LinesObject3DInternal::isPickable();
	}

	inline void setDynamicShadowingEnabled(bool dynamicShadowing) override {
		LinesObject3DInternal::setDynamicShadowingEnabled(dynamicShadowing);
	}

	inline void setPickable(bool pickable) override {
		LinesObject3DInternal::setPickable(pickable);
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

};
