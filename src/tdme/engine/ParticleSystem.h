#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Transform.h>

using std::string;

using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::Entity;
using tdme::engine::Transform;

/**
 * Particle system entity interface
 * @author Andreas Drewke
 */
struct tdme::engine::ParticleSystem: public Entity
{
	/**
	 * Public destructor
	 */
	virtual ~ParticleSystem() {}

	/**
	 * @returns particle emitter
	 */
	virtual ParticleEmitter* getEmitter() = 0;

	/**
	 * @returns true if active / particles available
	 */
	virtual bool isActive() = 0;

	/**
	 * @returns if auto emit is enabled
	 */
	virtual bool isAutoEmit() = 0;

	/**
	 * Set auto emit
	 * @param autoEmit auto emit
	 */
	virtual void setAutoEmit(bool autoEmit) = 0;

	/**
	 * Updates the particle entity
	 */
	virtual void updateParticles() = 0;

	/**
	 * Adds particles to this particle entity at given position
	 */
	virtual int emitParticles() = 0;

	/**
	 * @returns local transform
	 */
	virtual const Transform& getLocalTransform() = 0;

	/**
	 * Set local transform
	 * @param transform local transform
	 */
	virtual void setLocalTransform(const Transform& transform) = 0;

};
