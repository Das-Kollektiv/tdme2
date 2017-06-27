// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/PointParticleEmitter.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/engine/subsystems/particlesystem/ParticleEmitter.h>

using java::lang::Object;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Point particle emitter
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::particlesystem::PointParticleEmitter final
	: public virtual Object
	, public ParticleEmitter
{

public:
	typedef Object super;

private:
	int32_t count {  };
	int64_t lifeTime {  };
	int64_t lifeTimeRnd {  };
	float mass {  };
	float massRnd {  };
	Vector3* position {  };
	Vector3* positionTransformed {  };
	Vector3* velocity {  };
	Vector3* velocityRnd {  };
	Vector3* zeroPosition {  };
	Color4* colorStart {  };
	Color4* colorEnd {  };
protected:

	/** 
	 * @param number of particles to emit in one second
	 * @param life time in milli seconds
	 * @param life time rnd in milli seconds
	 * @param mass in kg
	 * @param mass rnd in kg
	 * @param velocity in meter / seconds
	 * @param velocity rnd in meter / seconds
	 */
	void ctor(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, float mass, float massRnd, Vector3* position, Vector3* velocity, Vector3* velocityRnd, Color4* colorStart, Color4* colorEnd);

public:
	int32_t getCount() override;
	Vector3* getVelocity() override;
	Vector3* getVelocityRnd() override;
	Color4* getColorStart() override;
	Color4* getColorEnd() override;
	void emit(Particle* particle) override;
	void fromTransformations(Transformations* transformations) override;

	// Generated
	PointParticleEmitter(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, float mass, float massRnd, Vector3* position, Vector3* velocity, Vector3* velocityRnd, Color4* colorStart, Color4* colorEnd);
protected:
	PointParticleEmitter(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
