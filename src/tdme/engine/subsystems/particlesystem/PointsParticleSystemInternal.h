#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/engine/subsystems/particlesystem/ParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemInternal.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::string;
using std::vector;

using tdme::engine::Texture;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::particlesystem::ParticleSystemInternal;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::engine::Engine;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Points particle system
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::particlesystem::PointsParticleSystemInternal
	: public Transform
	, public virtual ParticleSystemInternal
{

protected:
	string id;
	Engine* engine { nullptr };
	Renderer* renderer { nullptr };
	bool autoEmit;
	bool enabled;
	bool active;
	ParticleEmitter* emitter { nullptr };
	vector<Particle> particles;
	int32_t maxPoints;
	float pointSize;
	float pointSizeScale;
	Texture* texture { nullptr };
	int32_t textureHorizontalSprites;
	int32_t textureVerticalSprites;
	float fps;
	TransparentRenderPointsPool* pointsRenderPool { nullptr };

	BoundingBox boundingBox;
	BoundingBox boundingBoxTransformed;
	Transform inverseTransform;
	Color4 effectColorMul;
	Color4 effectColorAdd;
	bool pickable;
	float particlesToSpawnRemainder;

	Transform localTransform;

	/**
	 * Update bounding volume
	 */
	inline void updateInternal() {
		Vector3 scale;
		getTransformMatrix().getScale(scale);
		pointSizeScale = Math::max(scale.getX(), Math::max(scale.getY(), scale.getZ()));
		pointSizeScale*= Math::max(localTransform.getScale().getX(), Math::max(localTransform.getScale().getY(), localTransform.getScale().getZ()));
		boundingBoxTransformed.fromBoundingVolumeWithTransform(&boundingBox, *this);
		boundingBoxTransformed.getMin().sub(0.05f); // scale a bit up to make picking work better
		boundingBoxTransformed.getMax().add(0.05f); // same here
		boundingBoxTransformed.update();
	}

public:
	/**
	 * Public constructor
	 * @param id id
	 * @param emitter emitter
	 * @param maxPoints max points
	 * @param pointSize point size
	 * @param autoEmit auto emit
	 * @param texture texture
	 * @param textureHorizonalSprites texture horizonal sprites
	 * @param textureVerticalSprites texture vertical sprites
	 * @param fps frames per seconds
	 */
	PointsParticleSystemInternal(const string& id, ParticleEmitter* emitter, int32_t maxPoints, float pointSize, bool autoEmit, Texture* texture = nullptr, int32_t textureHorizontalSprites = 1, int32_t textureVerticalSprites = 1, float fps = 10.0f);

	/**
	 * Destructor
	 */
	virtual ~PointsParticleSystemInternal();

	/**
	 * Initialize
	 */
	void initialize();

	// overridden methods
	inline ParticleEmitter* getEmitter() override {
		return emitter;
	}

	inline const string& getId() override {
		return id;
	}
	inline void setRenderer(Renderer* renderer) {
		this->renderer = renderer;
	}
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
		return autoEmit;
	}
	inline void setAutoEmit(bool autoEmit) override {
		this->autoEmit = autoEmit;
	}

	/**
	 * @return if entity contributes to shadows
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
	 * @return if entity receives shadows
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
	 * @return point size
	 */
	inline float getPointSize() {
		return pointSize * pointSizeScale;
	}

	/**
	 * @return texture
	 */
	inline Texture* getTexture() {
		return texture;
	}

	/**
	 * @return texture horizontal sprites
	 */
	inline int32_t getTextureHorizontalSprites(){
		return textureHorizontalSprites;
	}

	/**
	 * @return texture vertical sprites
	 */
	inline int32_t getTextureVerticalSprites(){
		return textureVerticalSprites;
	}

	/**
	 * Update transform
	 */
	void update() override;
	void setTransform(const Transform& transform) override;
	void updateParticles() override;
	void dispose();
	int emitParticles() override;
	inline const Transform& getLocalTransform() override {
		return localTransform;
	}
	inline void setLocalTransform(const Transform& transform) override {
		this->localTransform = transform;
		updateInternal();
	}

	/**
	 * @return render points pool
	 */
	TransparentRenderPointsPool* getRenderPointsPool();

};
