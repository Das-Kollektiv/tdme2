#include <tdme/engine/subsystems/particlesystem/SphereParticleEmitter.h>

#include <tdme/math/Math.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::particlesystem::SphereParticleEmitter;
using tdme::math::Math;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Sphere;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::math::Vector3;

SphereParticleEmitter::SphereParticleEmitter(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, float mass, float massRnd, Sphere* sphere, const Vector3& velocity, const Vector3& velocityRnd, const Color4& colorStart, const Color4& colorEnd)
{
	this->count = count;
	this->lifeTime = lifeTime;
	this->lifeTimeRnd = lifeTimeRnd;
	this->mass = mass;
	this->massRnd = massRnd;
	this->sphere = sphere;
	this->sphereTransformed = static_cast< Sphere* >(sphere->clone());
	this->scale.set(1.0f, 1.0f, 1.0f);
	this->velocity.set(velocity);
	this->velocityRnd.set(velocityRnd);
	this->colorStart.set(colorStart);
	this->colorEnd.set(colorEnd);
}

SphereParticleEmitter::~SphereParticleEmitter() {
	delete sphere;
	delete sphereTransformed;
}

void SphereParticleEmitter::emit(Particle* particle)
{
	// set up particle
	particle->active = true;
	particle->position.set(
		Math::random() * 2.0f - 1.0f,
		Math::random() * 2.0f - 1.0f,
		Math::random() * 2.0f - 1.0f
	).normalize().scale(sphereTransformed->getRadius());
	particle->position.add(sphereTransformed->getCenter());
	particle->velocity.set(
		scale[0] * velocity[0] + (Math::random() * scale[0] * velocityRnd[0] * (Math::random() > 0.5 ? +1.0f : -1.0f)),
		scale[1] * velocity[1] + (Math::random() * scale[1] * velocityRnd[1] * (Math::random() > 0.5 ? +1.0f : -1.0f)),
		scale[2] * velocity[2] + (Math::random() * scale[2] * velocityRnd[2] * (Math::random() > 0.5 ? +1.0f : -1.0f))
	);
	particle->mass = mass + (Math::random() * (massRnd));
	particle->lifeTimeMax = lifeTime + static_cast< int64_t >((Math::random() * lifeTimeRnd));
	particle->lifeTimeCurrent = 0LL;
	particle->color.set(colorStart);
	particle->colorAdd.set(
		(colorEnd.getRed() - colorStart.getRed()) / particle->lifeTimeMax,
		(colorEnd.getGreen() - colorStart.getGreen()) / particle->lifeTimeMax,
		(colorEnd.getBlue() - colorStart.getBlue()) / particle->lifeTimeMax,
		(colorEnd.getAlpha() - colorStart.getAlpha()) / particle->lifeTimeMax
	);
}

void SphereParticleEmitter::fromTransformations(const Transformations& transformations)
{
	auto& transformationsMatrix = transformations.getTransformationsMatrix();
	// apply translations
	Vector3 center;
	Vector3 axis;
	// 	translate center
	transformationsMatrix.multiply(sphere->getCenter(), center);
	// scale and radius transformed
	transformationsMatrix.getScale(scale);
	*sphereTransformed = Sphere(center, sphere->getRadius() * Math::max(scale.getX(), Math::max(scale.getY(), scale.getZ())));
}
