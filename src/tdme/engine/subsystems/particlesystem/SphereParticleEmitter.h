// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/SphereParticleEmitter.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/engine/subsystems/particlesystem/ParticleEmitter.h>

using java::lang::Object;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::primitives::Sphere;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Sphere particle emitter
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::particlesystem::SphereParticleEmitter final
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
	Sphere* sphere {  };
	Sphere* sphereTransformed {  };
	Vector3* velocity {  };
	Vector3* velocityRnd {  };
	Color4* colorStart {  };
	Color4* colorEnd {  };
protected:

	/** 
	 * @param number of particles to emit in one second
	 * @param life time in milli seconds
	 * @param life time rnd in milli seconds
	 * @param mass in kg
	 * @param mass rnd in kg
	 * @param sphere
	 * @param velocity in meter / seconds
	 * @param velocity rnd in meter / seconds
	 * @param color start
	 * @param color end
	 */
	void ctor(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, float mass, float massRnd, Sphere* sphere, Vector3* velocity, Vector3* velocityRnd, Color4* colorStart, Color4* colorEnd);

public:
	int32_t getCount() override;
	Vector3* getVelocity() override;
	Vector3* getVelocityRnd() override;
	Color4* getColorStart() override;
	Color4* getColorEnd() override;
	void emit(Particle* particle) override;
	void fromTransformations(Transformations* transformations) override;

	// Generated
	SphereParticleEmitter(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, float mass, float massRnd, Sphere* sphere, Vector3* velocity, Vector3* velocityRnd, Color4* colorStart, Color4* colorEnd);
protected:
	SphereParticleEmitter(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
