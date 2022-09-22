#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/Transform.h>

using std::string;

using tdme::engine::model::Color4;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::Transform;

/**
 * Particle system entity internal interface
 * @author Andreas Drewke
 */
struct tdme::engine::subsystems::particlesystem::ParticleSystemInternal
{

	/**
	 * Public destructor
	 */
	virtual ~ParticleSystemInternal() {}

	/**
	 * @return particle emitter
	 */
	virtual ParticleEmitter* getEmitter() = 0;

	/**
	 * @return object id
	 */
	virtual const string& getId() = 0;

	/**
	 * @return true if enabled to be rendered
	 */
	virtual bool isEnabled() = 0;

	/**
	 * @return true if active / particles available
	 */
	virtual bool isActive() = 0;

	/**
	 * Enable/disable rendering
	 * @param enabled enabled
	 */
	virtual void setEnabled(bool enabled) = 0;

	/**
	 * @return if object is pickable
	 */
	virtual bool isPickable() = 0;

	/**
	 * Set this object pickable
	 * @param pickable pickable
	 */
	virtual void setPickable(bool pickable) = 0;

	/**
	 * @return if auto emit is enabled
	 */
	virtual bool isAutoEmit() = 0;

	/**
	 * Set auto emit
	 * @param autoEmit auto emit
	 */
	virtual void setAutoEmit(bool autoEmit) = 0;

	/**
	 * The effect color will be multiplied with fragment color
	 * @return effect color
	 */
	virtual const Color4& getEffectColorMul() const = 0;

	/**
	 * Set the effect color that will be multiplied with fragment color
	 * @param effectColorMul effect color
	 */
	virtual void setEffectColorMul(const Color4& effectColorMul) = 0;

	/**
	 * The effect color will be added to fragment color
	 * @return effect color
	 */
	virtual const Color4& getEffectColorAdd() const = 0;

	/**
	 * Set the effect color that will be added to fragment color
	 * @param effectColorAdd effect color
	 */
	virtual void setEffectColorAdd(const Color4& effectColorAdd) = 0;

	/**
	 * Updates the particle entity
	 */
	virtual void updateParticles() = 0;

	/**
	 * Adds particles to this particle entity at given position
	 */
	virtual int emitParticles() = 0;

	/**
	 * Set transform
	 * @param transform transform
	 */
	virtual void setTransform(const Transform& transform) = 0;

	/**
	 * Update transform
	 */
	virtual void update() = 0;

	/**
	 * @return local transform
	 */
	virtual const Transform& getLocalTransform() = 0;

	/**
	 * Set local transform
	 * @param transform local transform
	 */
	virtual void setLocalTransform(const Transform& transform) = 0;
};
