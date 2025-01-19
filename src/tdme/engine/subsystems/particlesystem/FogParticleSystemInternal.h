#pragma once

#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemInternal.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::string;
using std::unique_ptr;
using std::vector;

using tdme::engine::Texture;
using tdme::engine::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::particlesystem::ParticleSystemInternal;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::engine::Engine;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Fog particle system
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::particlesystem::FogParticleSystemInternal
	: public Transform
	, public virtual ParticleSystemInternal
{
protected:
	string id;
	Engine* engine { nullptr };
	RendererBackend* rendererBackend { nullptr };
	bool enabled;
	bool active;
	unique_ptr<ParticleEmitter> emitter;
	vector<Particle> particles;
	int32_t maxPoints;
	float pointSize;
	float pointSizeScale;
	Texture* texture { nullptr };
	int32_t textureHorizontalSprites;
	int32_t textureVerticalSprites;
	float fps;
	unique_ptr<TransparentRenderPointsPool> pointsRenderPool;

	BoundingBox boundingBox;
	BoundingBox worldBoundingBox;
	Color4 effectColorMul;
	Color4 effectColorAdd;
	bool pickable;

	Transform parentTransform;
	Transform localTransform;
	Matrix4x4 entityTransformMatrix;

	/**
	 * Update bounding volume
	 */
	inline void updateInternal() {
		Vector3 scale;
		entityTransformMatrix.getScale(scale);
		pointSizeScale = Math::max(scale.getX(), Math::max(scale.getY(), scale.getZ()));
		pointSizeScale*= Math::max(localTransform.getScale().getX(), Math::max(localTransform.getScale().getY(), localTransform.getScale().getZ()));
		worldBoundingBox.fromBoundingVolumeWithTransformMatrix(&boundingBox, entityTransformMatrix);
		worldBoundingBox.getMin().sub(0.05f); // scale a bit up to make picking work better
		worldBoundingBox.getMax().add(0.05f); // same here
		worldBoundingBox.update();
	}

public:
	// forbid class copy
	FORBID_CLASS_COPY(FogParticleSystemInternal)

	/**
	 * Public constructor
	 * @param id id
	 * @param emitter emitter
	 * @param maxPoints max points
	 * @param pointSize point size
	 * @param texture texture
	 * @param textureHorizontalSprites texture horizonal sprites
	 * @param textureVerticalSprites texture vertical sprites
	 * @param fps frames per seconds
	 */
	FogParticleSystemInternal(const string& id, ParticleEmitter* emitter, int32_t maxPoints, float pointSize, Texture* texture = nullptr, int32_t textureHorizontalSprites = 1, int32_t textureVerticalSprites = 1, float fps = 10.0f);

	/**
	 * Destructor
	 */
	virtual ~FogParticleSystemInternal();

	/**
	 * Initialize
	 */
	void initialize();

	inline ParticleEmitter* getEmitter() override {
		return emitter.get();
	}

	inline const string& getId() override {
		return id;
	}

	/**
	 * Set rendererBackend
	 * @param rendererBackend renderer backend
	 */
	inline void setRenderer(RendererBackend* rendererBackend) {
		this->rendererBackend = rendererBackend;
	}

	/**
	 * Set engine
	 * @param engine engine
	 */
	inline void setEngine(Engine* engine) {
		this->engine = engine;
	}

	inline bool isEnabled() override {
		return enabled;
	}

	inline bool isActive() override {
		return active;
	}

	inline void setEnabled(bool enabled) override {
		this->enabled = enabled;
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

	inline bool isPickable() override {
		return pickable;
	}

	inline void setPickable(bool pickable) override {
		this->pickable = pickable;
	}

	inline bool isAutoEmit() override {
		return true;
	}

	inline void setAutoEmit(bool autoEmit) override {
		// no op
	}

	/**
	 * @returns if entity contributes to shadows
	 */
	inline bool isContributesShadows() {
		return false;
	}

	/**
	 * Enable/disable contributes shadows
	 * @param contributesShadows contributes shadows
	 */
	inline void setContributesShadows(bool contributesShadows) {
		//
	}

	/**
	 * @returns if entity receives shadows
	 */
	inline bool isReceivesShadows() {
		return false;
	}

	/**
	 * Enable/disable receives shadows
	 * @param receivesShadows receives shadows
	 */
	inline void setReceivesShadows(bool receivesShadows) {
		//
	}

	/**
	 * @returns point size
	 */
	inline float getPointSize() {
		return pointSize * pointSizeScale;
	}

	/**
	 * @returns texture
	 */
	inline Texture* getTexture() {
		return texture;
	}

	/**
	 * @returns texture horizontal sprites
	 */
	inline int32_t getTextureHorizontalSprites(){
		return textureHorizontalSprites;
	}

	/**
	 * @returns texture vertical sprites
	 */
	inline int32_t getTextureVerticalSprites(){
		return textureVerticalSprites;
	}

	// overridden methods
	void update() override;
	void setTransform(const Transform& transform) override;
	void updateParticles() override;
	void dispose();
	inline int emitParticles() override {
		return 0;
	}
	inline const Transform& getParentTransform() {
		return parentTransform;
	}
	inline void setParentTransform(const Transform& transform) {
		parentTransform = transform;
		auto entityTransform = parentTransform * (*this);
		entityTransformMatrix = entityTransform.getTransformMatrix();
		//
		updateInternal();
	}
	inline const Transform& getLocalTransform() override {
		return localTransform;
	}
	inline void setLocalTransform(const Transform& transform) override {
		this->localTransform = transform;
		updateInternal();
	}

	/**
	 * @returns render points pool
	 */
	inline TransparentRenderPointsPool* getRenderPointsPool() {
		return pointsRenderPool.get();
	}

};
