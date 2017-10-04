// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/CircleParticleEmitter.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/engine/subsystems/particlesystem/ParticleEmitter.h>

using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::math::Vector3;

/** 
 * Circle particle emitter
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::particlesystem::CircleParticleEmitter final
	: public ParticleEmitter
{
private:
	int32_t count {  };
	int64_t lifeTime {  };
	int64_t lifeTimeRnd {  };
	Vector3 axis0 {  };
	Vector3 axis1 {  };
	Vector3 center {  };
	float radius {  };
	Vector3 axis0Transformed;
	Vector3 axis1Transformed;
	Vector3 centerTransformed;
	float radiusTransformed;
	float mass {  };
	float massRnd {  };
	Vector3 velocity {  };
	Vector3 velocityRnd {  };
	Color4 colorStart {  };
	Color4 colorEnd {  };
public:
	int32_t getCount() override;
	Vector3& getVelocity();
	Vector3& getVelocityRnd();
	Color4& getColorStart() override;
	Color4& getColorEnd() override;
	void emit(Particle* particle) override;
	void fromTransformations(Transformations* transformations) override;

	/**
	 * Public constructor
	 * @param particles to emit in one second
	 * @param life time
	 * @param life time rnd
	 * @param axis 0
	 * @param axis 1
	 * @param center
	 * @param radius
	 * @param mass
	 * @param mass rnd
	 * @param velocity
	 * @param velocity rnd
	 * @param color start
	 * @param color end
	 */
	CircleParticleEmitter(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, const Vector3& axis0, const Vector3& axis1, const Vector3& center, float radius, float mass, float massRnd, const Vector3& velocity, const Vector3& velocityRnd, const Color4& colorStart, const Color4& colorEnd);
};
