#include <tdme/engine/subsystems/particlesystem/CircleParticleEmitterPlaneVelocity.h>

#include <tdme/math/Math.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::particlesystem::CircleParticleEmitterPlaneVelocity;
using tdme::math::Math;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

CircleParticleEmitterPlaneVelocity::CircleParticleEmitterPlaneVelocity(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, Vector3* axis0, Vector3* axis1, Vector3* center, float radius, float mass, float massRnd, float velocity, float velocityRnd, Color4* colorStart, Color4* colorEnd) 
{
	this->count = count;
	this->lifeTime = lifeTime;
	this->lifeTimeRnd = lifeTimeRnd;
	this->axis0.set(axis0)->normalize();
	this->axis1.set(axis1)->normalize();
	this->center.set(center);
	this->radius = radius;
	this->mass = mass;
	this->massRnd = massRnd;
	this->velocity = velocity;
	this->velocityRnd = velocityRnd;
	this->colorStart.set(colorStart);
	this->colorEnd.set(colorEnd);
	this->centerTransformed.set(center);
	this->radiusTransformed = radius;
	this->axis0Transformed.set(axis0)->normalize();
	this->axis1Transformed.set(axis1)->normalize();
}

int32_t CircleParticleEmitterPlaneVelocity::getCount()
{
	return count;
}

Vector3* CircleParticleEmitterPlaneVelocity::getVelocity()
{
	return nullptr;
}

Vector3* CircleParticleEmitterPlaneVelocity::getVelocityRnd()
{
	return nullptr;
}

Color4* CircleParticleEmitterPlaneVelocity::getColorStart()
{
	return &colorStart;
}

Color4* CircleParticleEmitterPlaneVelocity::getColorEnd()
{
	return &colorEnd;
}

void CircleParticleEmitterPlaneVelocity::emit(Particle* particle)
{
	Vector3 cosOnAxis0;
	Vector3 sinOnAxis1;
	Vector3 side;
	particle->active = true;
	auto rnd = static_cast< float >(Math::random());
	cosOnAxis0.set(&axis0Transformed)->scale(static_cast< float >(Math::cos(Math::PI * 2 * rnd)));
	sinOnAxis1.set(&axis1Transformed)->scale(static_cast< float >(Math::sin(Math::PI * 2 * rnd)));
	particle->position.set(&cosOnAxis0);
	particle->position.add(&sinOnAxis1);
	particle->position.scale(radiusTransformed);
	particle->position.add(&centerTransformed);
	particle->velocity.set(&particle->position)->sub(&centerTransformed)->normalize()->scale(velocity + static_cast< float >((Math::random() * velocityRnd)));
	particle->mass = mass + static_cast< float >((Math::random() * (massRnd)));
	particle->lifeTimeMax = lifeTime + static_cast< int64_t >((Math::random() * lifeTimeRnd));
	particle->lifeTimeCurrent = 0LL;
	particle->color.set(&colorStart);
	particle->colorAdd.set(
		(colorEnd.getRed() - colorStart.getRed()) / particle->lifeTimeMax,
		(colorEnd.getGreen() - colorStart.getGreen()) / particle->lifeTimeMax,
		(colorEnd.getBlue() - colorStart.getBlue()) / particle->lifeTimeMax,
		(colorEnd.getAlpha() - colorStart.getAlpha()) / particle->lifeTimeMax);
}

void CircleParticleEmitterPlaneVelocity::fromTransformations(Transformations* transformations)
{
	Vector3 side;
	auto& transformationsMatrix = transformations->getTransformationsMatrix();
	transformationsMatrix.multiply(center, centerTransformed);
	transformationsMatrix.multiplyNoTranslation(axis0, axis0Transformed);
	transformationsMatrix.multiplyNoTranslation(axis1, axis1Transformed);
	side.set(&axis0)->scale(radius)->add(&center);
	transformationsMatrix.multiply(side, side);
	radius = side.sub(&center)->computeLength();
}
