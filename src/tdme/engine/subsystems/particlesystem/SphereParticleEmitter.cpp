#include <tdme/engine/subsystems/particlesystem/SphereParticleEmitter.h>

#include <tdme/math/Math.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::particlesystem::SphereParticleEmitter;
using tdme::math::Math;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Sphere;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::math::Vector3;

SphereParticleEmitter::SphereParticleEmitter(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, float mass, float massRnd, Sphere* sphere, Vector3* velocity, Vector3* velocityRnd, Color4* colorStart, Color4* colorEnd) 
{
	this->count = count;
	this->lifeTime = lifeTime;
	this->lifeTimeRnd = lifeTimeRnd;
	this->mass = mass;
	this->massRnd = massRnd;
	this->sphere = sphere;
	this->sphereTransformed = dynamic_cast< Sphere* >(sphere->clone());
	this->velocity.set(*velocity);
	this->velocityRnd.set(*velocityRnd);
	this->colorStart.set(colorStart);
	this->colorEnd.set(colorEnd);
}

int32_t SphereParticleEmitter::getCount()
{
	return count;
}

Vector3* SphereParticleEmitter::getVelocity()
{
	return &velocity;
}

Vector3* SphereParticleEmitter::getVelocityRnd()
{
	return &velocityRnd;
}

Color4* SphereParticleEmitter::getColorStart()
{
	return &colorStart;
}

Color4* SphereParticleEmitter::getColorEnd()
{
	return &colorEnd;
}

void SphereParticleEmitter::emit(Particle* particle)
{
	auto& velocityXYZ = velocity.getArray();
	auto& velocityRndXYZ = velocityRnd.getArray();
	particle->active = true;
	particle->position.set(
		Math::random() * 2.0f - 1.0f,
		Math::random() * 2.0f - 1.0f,
		Math::random() * 2.0f - 1.0f
	).normalize().scale(sphereTransformed->getRadius());
	particle->position.add(*sphereTransformed->getCenter());
	particle->velocity.set(
		velocityXYZ[0] + (Math::random() * velocityRndXYZ[0] * (Math::random() > 0.5 ? +1.0f : -1.0f)),
		velocityXYZ[1] + (Math::random() * velocityRndXYZ[1] * (Math::random() > 0.5 ? +1.0f : -1.0f)),
		velocityXYZ[2] + (Math::random() * velocityRndXYZ[2] * (Math::random() > 0.5 ? +1.0f : -1.0f))
	);
	particle->mass = mass + (Math::random() * (massRnd));
	particle->lifeTimeMax = lifeTime + static_cast< int64_t >((Math::random() * lifeTimeRnd));
	particle->lifeTimeCurrent = 0LL;
	particle->color.set(&colorStart);
	particle->colorAdd.set(
		(colorEnd.getRed() - colorStart.getRed()) / particle->lifeTimeMax,
		(colorEnd.getGreen() - colorStart.getGreen()) / particle->lifeTimeMax,
		(colorEnd.getBlue() - colorStart.getBlue()) / particle->lifeTimeMax,
		(colorEnd.getAlpha() - colorStart.getAlpha()) / particle->lifeTimeMax
	);
}

void SphereParticleEmitter::fromTransformations(Transformations* transformations)
{
	sphereTransformed->fromBoundingVolumeWithTransformations(sphere, transformations);
}
