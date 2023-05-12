#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/lines/LinesInternal.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>

using std::string;

using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::lines::LinesInternal;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;

/**
 * Lines entity to be used with engine class
 * @author Andreas Drewke
 */
class tdme::engine::Lines final: public LinesInternal, public Entity
{

private:
	friend class Engine;

	Engine* engine { nullptr };
	bool frustumCulling { true };
	RenderPass renderPass { RENDERPASS_STANDARD };

	// overridden methods
	inline void setParentTransform(const Transform& parentTransform) override {
		LinesInternal::setParentTransform(parentTransform);
	}

public:
	/**
	 * Public constructor
	 * @param id id
	 * @param lineWidth line width
	 * @param points points
	 * @param color color
	 * @param colors optional colors
	 * @param texture optional texture
	 */
	Lines(const string& id, float lineWidth, const vector<Vector3>& points, const Color4& color, const vector<Color4>& colors = {}, Texture* texture = nullptr);

	// overridden methods
	inline EntityType getEntityType() override {
		return ENTITYTYPE_LINES;
	}

	void setEngine(Engine* engine) override;

	inline void setRenderer(Renderer* renderer) override {
		LinesInternal::setRenderer(renderer);
	}

	inline void initialize() override {
		LinesInternal::initialize();
	}

	inline void dispose() override {
		LinesInternal::dispose();
	}

	inline bool isEnabled() override {
		return LinesInternal::isEnabled();
	}

	void setEnabled(bool enabled) override;

	inline bool isFrustumCulling() override {
		return frustumCulling;
	}

	void setFrustumCulling(bool frustumCulling) override;
	void update() override;

	inline BoundingBox* getBoundingBox() override {
		return LinesInternal::getBoundingBox();
	}

	inline BoundingBox* getWorldBoundingBox() override {
		return LinesInternal::getWorldBoundingBox();
	}

	inline const Color4& getEffectColorAdd() const override {
		return LinesInternal::getEffectColorAdd();
	}

	inline void setEffectColorAdd(const Color4& effectColorAdd) override {
		return LinesInternal::setEffectColorAdd(effectColorAdd);
	}

	inline const Color4& getEffectColorMul() const override {
		return LinesInternal::getEffectColorMul();
	}

	inline void setEffectColorMul(const Color4& effectColorMul) override {
		return LinesInternal::setEffectColorMul(effectColorMul);
	}

	inline const string& getId() override {
		return LinesInternal::getId();
	}

	inline bool isContributesShadows() override {
		return LinesInternal::isContributesShadows();
	}

	inline void setContributesShadows(bool contributesShadows) override {
		LinesInternal::setContributesShadows(contributesShadows);
	}

	inline bool isReceivesShadows() override {
		return LinesInternal::isReceivesShadows();
	}

	inline void setReceivesShadows(bool receivesShadows) override {
		LinesInternal::setReceivesShadows(receivesShadows);
	}

	inline bool isPickable() override {
		return LinesInternal::isPickable();
	}

	inline void setPickable(bool pickable) override {
		LinesInternal::setPickable(pickable);
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

	inline const Vector3& getPivot() const override {
		return Transform::getPivot();
	}

	inline void setPivot(const Vector3& pivot) override {
		Transform::setPivot(pivot);
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
