#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using tdme::engine::Color4;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::engine::Transform;
using tdme::math::Vector3;

/**
 * Particle emitter interface
 * @author Andreas Drewke
 */
struct tdme::engine::subsystems::particlesystem::ParticleEmitter
{
	/**
	 * @returns center
	 */
	virtual const Vector3& getCenter() const = 0;


	/**
	 * @returns number of particles to emit in one second
	 */
	virtual int32_t getCount() const = 0;

	/**
	 * @returns color start
	 */
	virtual const Color4& getColorStart() const = 0;

	/**
	 * Set start color
	 * @param colorStart color start
	 */
	virtual void setColorStart(const Color4& colorStart) = 0;

	/**
	 * @returns color end
	 */
	virtual const Color4& getColorEnd() const = 0;

	/**
	 * Set end color
	 * @param colorEnd color end
	 */
	virtual void setColorEnd(const Color4& colorEnd) = 0;

	/**
	 * Emits particles
	 * @param particle particle
	 */
	virtual void emit(Particle* particle) = 0;

	/**
	 * Update transform with given transform
	 * @param transform transform
	 */
	virtual void setTransform(const Transform& transform) = 0;

	/**
	 * Destructor
	 */
	virtual ~ParticleEmitter() {}
};
