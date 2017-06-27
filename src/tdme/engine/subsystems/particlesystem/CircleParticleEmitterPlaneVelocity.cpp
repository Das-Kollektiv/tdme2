// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/CircleParticleEmitterPlaneVelocity.java
#include <tdme/engine/subsystems/particlesystem/CircleParticleEmitterPlaneVelocity.h>

#include <java/lang/Math.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::particlesystem::CircleParticleEmitterPlaneVelocity;
using java::lang::Math;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

CircleParticleEmitterPlaneVelocity::CircleParticleEmitterPlaneVelocity(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

CircleParticleEmitterPlaneVelocity::CircleParticleEmitterPlaneVelocity(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, Vector3* axis0, Vector3* axis1, Vector3* center, float radius, float mass, float massRnd, float velocity, float velocityRnd, Color4* colorStart, Color4* colorEnd) 
	: CircleParticleEmitterPlaneVelocity(*static_cast< ::default_init_tag* >(0))
{
	ctor(count,lifeTime,lifeTimeRnd,axis0,axis1,center,radius,mass,massRnd,velocity,velocityRnd,colorStart,colorEnd);
}

void CircleParticleEmitterPlaneVelocity::ctor(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, Vector3* axis0, Vector3* axis1, Vector3* center, float radius, float mass, float massRnd, float velocity, float velocityRnd, Color4* colorStart, Color4* colorEnd)
{
	super::ctor();
	this->count = count;
	this->lifeTime = lifeTime;
	this->lifeTimeRnd = lifeTimeRnd;
	this->axis0 = axis0->normalize();
	this->axis1 = axis1->normalize();
	this->center = center;
	this->radius = radius;
	this->mass = mass;
	this->massRnd = massRnd;
	this->velocity = velocity;
	this->velocityRnd = velocityRnd;
	this->colorStart = colorStart;
	this->colorEnd = colorEnd;
	this->centerTransformed = this->center->clone();
	this->radiusTransformed = radius;
	this->axis0Transformed = axis0->clone();
	this->axis1Transformed = axis1->clone();
	this->side = new Vector3();
	this->cosOnAxis0 = new Vector3();
	this->sinOnAxis1 = new Vector3();
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
	return colorStart;
}

Color4* CircleParticleEmitterPlaneVelocity::getColorEnd()
{
	return colorEnd;
}

void CircleParticleEmitterPlaneVelocity::emit(Particle* particle)
{
	particle->active = true;
	auto rnd = static_cast< float >(Math::random());
	cosOnAxis0->set(axis0Transformed)->scale(static_cast< float >(Math::cos(Math::PI * 2 * rnd)));
	sinOnAxis1->set(axis1Transformed)->scale(static_cast< float >(Math::sin(Math::PI * 2 * rnd)));
	particle->position->set(cosOnAxis0);
	particle->position->add(sinOnAxis1);
	particle->position->scale(radiusTransformed);
	particle->position->add(centerTransformed);
	particle->velocity->set(particle->position)->sub(centerTransformed)->normalize()->scale(velocity + static_cast< float >((Math::random() * velocityRnd)));
	particle->mass = mass + static_cast< float >((Math::random() * (massRnd)));
	particle->lifeTimeMax = lifeTime + static_cast< int64_t >((Math::random() * lifeTimeRnd));
	particle->lifeTimeCurrent = 0LL;
	particle->color->set(static_cast< Color4Base* >(colorStart));
	particle->colorAdd->set((colorEnd->getRed() - colorStart->getRed()) / particle->lifeTimeMax, (colorEnd->getGreen() - colorStart->getGreen()) / particle->lifeTimeMax, (colorEnd->getBlue() - colorStart->getBlue()) / particle->lifeTimeMax, (colorEnd->getAlpha() - colorStart->getAlpha()) / particle->lifeTimeMax);
}

void CircleParticleEmitterPlaneVelocity::fromTransformations(Transformations* transformations)
{
	auto transformationsMatrix = transformations->getTransformationsMatrix();
	transformationsMatrix->multiply(center, centerTransformed);
	transformationsMatrix->multiplyNoTranslation(axis0, axis0Transformed);
	transformationsMatrix->multiplyNoTranslation(axis1, axis1Transformed);
	side->set(axis0)->scale(radius)->add(center);
	transformationsMatrix->multiply(side, side);
	radius = side->sub(center)->computeLength();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* CircleParticleEmitterPlaneVelocity::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.particlesystem.CircleParticleEmitterPlaneVelocity", 72);
    return c;
}

java::lang::Class* CircleParticleEmitterPlaneVelocity::getClass0()
{
	return class_();
}

