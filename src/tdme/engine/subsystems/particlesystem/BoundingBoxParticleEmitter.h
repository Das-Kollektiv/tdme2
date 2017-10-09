#pragma once

#include <tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/engine/subsystems/particlesystem/ParticleEmitter.h>

using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::math::Vector3;

/** 
 * Sphere particle emitter
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::particlesystem::BoundingBoxParticleEmitter final
	: public ParticleEmitter
{
private:
	int32_t count {  };
	int64_t lifeTime {  };
	int64_t lifeTimeRnd {  };
	float mass {  };
	float massRnd {  };
	OrientedBoundingBox* obb {  };
	OrientedBoundingBox* obbTransformed {  };
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
	 * @param life time in milli seconds
	 * @param life time rnd in milli seconds
	 * @param mass in kg
	 * @param mass rnd in kg
	 * @param oriented bounding box
	 * @param velocity in meter / seconds
	 * @param velocity rnd in meter / seconds
	 * @param color start
	 * @param color end 
	 */
	BoundingBoxParticleEmitter(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, float mass, float massRnd, OrientedBoundingBox* obb, const Vector3& velocity, const Vector3& velocityRnd, const Color4& colorStart, const Color4& colorEnd);

	/**
	 * Destructor
	 */
	virtual ~BoundingBoxParticleEmitter();
};
