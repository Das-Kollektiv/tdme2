#include <tdme/engine/subsystems/particlesystem/CircleParticleEmitter.h>

#include <tdme/math/Math.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::particlesystem::CircleParticleEmitter;
using tdme::math::Math;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

CircleParticleEmitter::CircleParticleEmitter(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, Vector3* axis0, Vector3* axis1, Vector3* center, float radius, float mass, float massRnd, Vector3* velocity, Vector3* velocityRnd, Color4* colorStart, Color4* colorEnd) 
{
	this->count = count;
	this->lifeTime = lifeTime;
	this->lifeTimeRnd = lifeTimeRnd;
	this->axis0.set(axis0)->normalize();
	this->axis1.set(axis1)->normalize();
	this->center.set(center);
	this->radius = radius;
	this->axis0Transformed.set(axis0)->normalize();
	this->axis1Transformed.set(axis1)->normalize();
	this->centerTransformed.set(center);
	this->radiusTransformed = radius;
	this->mass = mass;
	this->massRnd = massRnd;
	this->velocity.set(velocity);
	this->velocityRnd.set(velocityRnd);
	this->colorStart.set(colorStart);
	this->colorEnd.set(colorEnd);
}

int32_t CircleParticleEmitter::getCount()
{
	return count;
}

Vector3* CircleParticleEmitter::getVelocity()
{
	return &velocity;
}

Vector3* CircleParticleEmitter::getVelocityRnd()
{
	return &velocityRnd;
}

Color4* CircleParticleEmitter::getColorStart()
{
	return &colorStart;
}

Color4* CircleParticleEmitter::getColorEnd()
{
	return &colorEnd;
}

void CircleParticleEmitter::emit(Particle* particle)
{
	Vector3 cosOnAxis0;
	Vector3 sinOnAxis1;
	auto velocityXYZ = velocity.getArray();
	auto velocityRndXYZ = velocityRnd.getArray();
	particle->active = true;
	auto rnd = static_cast< float >(Math::random());
	cosOnAxis0.set(&axis0Transformed)->scale(static_cast< float >(Math::cos(Math::PI * 2 * rnd)));
	sinOnAxis1.set(&axis1Transformed)->scale(static_cast< float >(Math::sin(Math::PI * 2 * rnd)));
	particle->position.set(&cosOnAxis0);
	particle->position.add(&sinOnAxis1);
	particle->position.scale(radiusTransformed);
	particle->position.add(&centerTransformed);
	particle->velocity.set(
		(*velocityXYZ)[0] + static_cast< float >((Math::random() * (*velocityRndXYZ)[0] * (Math::random() > 0.5 ? +1.0f : -1.0f))),
		(*velocityXYZ)[1] + static_cast< float >((Math::random() * (*velocityRndXYZ)[1] * (Math::random() > 0.5 ? +1.0f : -1.0f))),
		(*velocityXYZ)[2] + static_cast< float >((Math::random() * (*velocityRndXYZ)[2] * (Math::random() > 0.5 ? +1.0f : -1.0f)))
	);
	particle->mass = mass + static_cast< float >((Math::random() * (massRnd)));
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

void CircleParticleEmitter::fromTransformations(Transformations* transformations)
{
	Vector3 side;
	auto transformationsMatrix = transformations->getTransformationsMatrix();
	transformationsMatrix->multiply(&center, &centerTransformed);
	transformationsMatrix->multiplyNoTranslation(&axis0, &axis0Transformed);
	transformationsMatrix->multiplyNoTranslation(&axis1, &axis1Transformed);
	side.set(&axis0)->scale(radius)->add(&center);
	transformationsMatrix->multiply(&side, &side);
	radius = side.sub(&center)->computeLength();
}
