#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemEntityInternal.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::string;
using std::vector;

using tdme::engine::Transformations;
using tdme::engine::subsystems::particlesystem::ParticleSystemEntityInternal;
using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Fog particle system
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::particlesystem::FogParticleSystemInternal
	: public Transformations
	, public virtual ParticleSystemEntityInternal
{

protected:
	string id;
	Engine* engine { nullptr };
	Renderer* renderer { nullptr };
	bool enabled;
	bool active;
	ParticleEmitter* emitter { nullptr };
	vector<Particle> particles;
	int32_t maxPoints;
	float pointSize;
	float pointSizeScale;
	Texture* texture { nullptr };
	int32_t textureId;
	TransparentRenderPointsPool* pointsRenderPool { nullptr };

	BoundingBox boundingBox;
	BoundingBox boundingBoxTransformed;
	Color4 effectColorMul;
	Color4 effectColorAdd;
	bool pickable;

	/**
	 * Update bounding volume
	 */
	inline void updateInternal() {
		Vector3 scale;
		getTransformationsMatrix().getScale(scale);
		pointSizeScale = Math::max(scale.getX(), Math::max(scale.getY(), scale.getZ()));
		boundingBoxTransformed.fromBoundingVolumeWithTransformations(&boundingBox, *this);
		boundingBoxTransformed.getMin().sub(0.05f); // scale a bit up to make picking work better
		boundingBoxTransformed.getMax().add(0.05f); // same here
		boundingBoxTransformed.update();
	}

public:
	/**
	 * Initialize
	 */
	void initialize();

	inline const string& getId() override {
		return id;
	}

	/**
	 * Set renderer
	 * @param renderer renderer
	 */
	inline virtual void setRenderer(Renderer* renderer) {
		this->renderer = renderer;
	}

	/**
	 * Set engine
	 * @param engine engine
	 */
	inline virtual void setEngine(Engine* engine) {
		this->engine = engine;
	}

	inline virtual bool isEnabled() override {
		return enabled;
	}

	inline virtual bool isActive() override {
		return active;
	}

	inline virtual void setEnabled(bool enabled) override {
		this->enabled = enabled;
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

	inline virtual bool isPickable() override {
		return pickable;
	}

	inline virtual void setPickable(bool pickable) override {
		this->pickable = pickable;
	}

	inline virtual bool isAutoEmit() override {
		return true;
	}

	inline virtual void setAutoEmit(bool autoEmit) override {
		// no op
	}

	/**
	 * @return if entity contributes to shadows
	 */
	inline virtual bool isContributesShadows() {
		return false;
	}

	/**
	 * Enable/disable contributes shadows
	 * @param contributesShadows contributes shadows
	 */
	inline virtual void setContributesShadows(bool contributesShadows) {
		//
	}

	/**
	 * @return if entity receives shadows
	 */
	inline virtual bool isReceivesShadows() {
		return false;
	}

	/**
	 * Enable/disable receives shadows
	 * @param receivesShadows receives shadows
	 */
	inline virtual void setReceivesShadows(bool receivesShadows) {
		//
	}

	/**
	 * @return point size
	 */
	inline virtual float getPointSize() {
		return pointSize * pointSizeScale;
	}

	/**
	 * @return texture id
	 */
	inline virtual int32_t getTextureId() {
		return textureId;
	}

	// overriden methods
	void update() override;
	void fromTransformations(const Transformations& transformations) override;
	void updateParticles() override;
	virtual void dispose();
	inline int32_t emitParticles() override {
		return 0;
	}

	/** 
	 * @return render points pool
	 */
	inline virtual TransparentRenderPointsPool* getRenderPointsPool() {
		return pointsRenderPool;
	}

	/**
	 * Public constructor
	 * @param id id
	 * @param emitter emitter
	 * @param maxPoints max points
	 * @param pointSize point size
	 * @param texture texture
	 */
	FogParticleSystemInternal(const string& id, ParticleEmitter* emitter, int32_t maxPoints, float pointSize, Texture* texture = nullptr);

	/**
	 * Destructor
	 */
	virtual ~FogParticleSystemInternal();
};
