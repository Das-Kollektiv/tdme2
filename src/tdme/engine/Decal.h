#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/decals/DecalInternal.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>

using std::string;

using tdme::engine::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::subsystems::decals::DecalInternal;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;

/**
 * Decal entity to be used with engine class
 * @author Andreas Drewke
 */
class tdme::engine::Decal final: public DecalInternal, public Entity
{

private:
	friend class Engine;

	Engine* engine { nullptr };
	bool frustumCulling { true };
	RenderPass renderPass { RENDERPASS_STANDARD };

	// overridden methods
	inline void setParentTransform(const Transform& parentTransform) override {
		DecalInternal::setParentTransform(parentTransform);
	}

public:
	// forbid class copy
	FORBID_CLASS_COPY(Decal)

	/**
	 * Public constructor
	 * @param id id
	 * @param obb oriented bounding box
	 * @param texture texture
	 * @param textureHorizonalSprites texture horizonal sprites
	 * @param textureVerticalSprites texture vertical sprites
	 * @param fps frames per seconds
	 */
	Decal(const string& id, OrientedBoundingBox* obb, Texture* texture = nullptr, int32_t textureHorizontalSprites = 1, int32_t textureVerticalSprites = 1, float fps = 10.0f);

	// overridden methods
	inline EntityType getEntityType() override {
		return ENTITYTYPE_DECAL;
	}

	void setEngine(Engine* engine) override;

	inline void setRenderer(Renderer* renderer) override {
		DecalInternal::setRenderer(renderer);
	}

	inline void initialize() override {
		DecalInternal::initialize();
	}

	inline void dispose() override {
		DecalInternal::dispose();
	}

	inline bool isEnabled() override {
		return DecalInternal::isEnabled();
	}

	void setEnabled(bool enabled) override;
	inline bool isFrustumCulling() override {
		return frustumCulling;
	}
	void setFrustumCulling(bool frustumCulling) override;
	void update() override;

	inline BoundingBox* getBoundingBox() override {
		return DecalInternal::getBoundingBox();
	}

	inline BoundingBox* getWorldBoundingBox() override {
		return DecalInternal::getWorldBoundingBox();
	}

	inline const Color4& getEffectColorAdd() const override {
		return DecalInternal::getEffectColorAdd();
	}

	inline void setEffectColorAdd(const Color4& effectColorAdd) override {
		return DecalInternal::setEffectColorAdd(effectColorAdd);
	}

	inline const Color4& getEffectColorMul() const override {
		return DecalInternal::getEffectColorMul();
	}

	inline void setEffectColorMul(const Color4& effectColorMul) override {
		return DecalInternal::setEffectColorMul(effectColorMul);
	}

	inline const string& getId() override {
		return DecalInternal::getId();
	}

	inline bool isContributesShadows() override {
		return DecalInternal::isContributesShadows();
	}

	inline void setContributesShadows(bool contributesShadows) override {
		DecalInternal::setContributesShadows(contributesShadows);
	}

	inline bool isReceivesShadows() override {
		return DecalInternal::isReceivesShadows();
	}

	inline void setReceivesShadows(bool receivesShadows) override {
		DecalInternal::setReceivesShadows(receivesShadows);
	}

	inline bool isPickable() override {
		return DecalInternal::isPickable();
	}

	inline void setPickable(bool pickable) override {
		DecalInternal::setPickable(pickable);
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

	/**
	 * @return decal texture
	 */
	inline Texture* getDecalTexture() {
		return DecalInternal::getDecalTexture();
	}

	/**
	 * @return world to decal space matrix
	 */
	inline const Matrix4x4& getWorldToDecalSpaceMatrix() {
		return DecalInternal::getWorldToDecalSpaceMatrix();
	}

};
