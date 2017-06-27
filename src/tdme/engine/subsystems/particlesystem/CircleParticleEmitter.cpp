// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/CircleParticleEmitter.java
#include <tdme/engine/subsystems/particlesystem/CircleParticleEmitter.h>

#include <java/lang/Math.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using tdme::engine::subsystems::particlesystem::CircleParticleEmitter;
using java::lang::Math;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

CircleParticleEmitter::CircleParticleEmitter(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

CircleParticleEmitter::CircleParticleEmitter(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, Vector3* axis0, Vector3* axis1, Vector3* center, float radius, float mass, float massRnd, Vector3* velocity, Vector3* velocityRnd, Color4* colorStart, Color4* colorEnd) 
	: CircleParticleEmitter(*static_cast< ::default_init_tag* >(0))
{
	ctor(count,lifeTime,lifeTimeRnd,axis0,axis1,center,radius,mass,massRnd,velocity,velocityRnd,colorStart,colorEnd);
}

void CircleParticleEmitter::ctor(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, Vector3* axis0, Vector3* axis1, Vector3* center, float radius, float mass, float massRnd, Vector3* velocity, Vector3* velocityRnd, Color4* colorStart, Color4* colorEnd)
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

int32_t CircleParticleEmitter::getCount()
{
	return count;
}

Vector3* CircleParticleEmitter::getVelocity()
{
	return velocity;
}

Vector3* CircleParticleEmitter::getVelocityRnd()
{
	return velocityRnd;
}

Color4* CircleParticleEmitter::getColorStart()
{
	return colorStart;
}

Color4* CircleParticleEmitter::getColorEnd()
{
	return colorEnd;
}

void CircleParticleEmitter::emit(Particle* particle)
{
	auto velocityXYZ = velocity->getArray();
	auto velocityRndXYZ = velocityRnd->getArray();
	particle->active = true;
	auto rnd = static_cast< float >(Math::random());
	cosOnAxis0->set(axis0Transformed)->scale(static_cast< float >(Math::cos(Math::PI * 2 * rnd)));
	sinOnAxis1->set(axis1Transformed)->scale(static_cast< float >(Math::sin(Math::PI * 2 * rnd)));
	particle->position->set(cosOnAxis0);
	particle->position->add(sinOnAxis1);
	particle->position->scale(radiusTransformed);
	particle->position->add(centerTransformed);
	particle->velocity->set((*velocityXYZ)[0] + static_cast< float >((Math::random() * (*velocityRndXYZ)[0] * (Math::random() > 0.5 ? +1.0f : -1.0f))), (*velocityXYZ)[1] + static_cast< float >((Math::random() * (*velocityRndXYZ)[1] * (Math::random() > 0.5 ? +1.0f : -1.0f))), (*velocityXYZ)[2] + static_cast< float >((Math::random() * (*velocityRndXYZ)[2] * (Math::random() > 0.5 ? +1.0f : -1.0f))));
	particle->mass = mass + static_cast< float >((Math::random() * (massRnd)));
	particle->lifeTimeMax = lifeTime + static_cast< int64_t >((Math::random() * lifeTimeRnd));
	particle->lifeTimeCurrent = 0LL;
	particle->color->set(static_cast< Color4Base* >(colorStart));
	particle->colorAdd->set((colorEnd->getRed() - colorStart->getRed()) / particle->lifeTimeMax, (colorEnd->getGreen() - colorStart->getGreen()) / particle->lifeTimeMax, (colorEnd->getBlue() - colorStart->getBlue()) / particle->lifeTimeMax, (colorEnd->getAlpha() - colorStart->getAlpha()) / particle->lifeTimeMax);
}

void CircleParticleEmitter::fromTransformations(Transformations* transformations)
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

java::lang::Class* CircleParticleEmitter::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.particlesystem.CircleParticleEmitter", 59);
    return c;
}

java::lang::Class* CircleParticleEmitter::getClass0()
{
	return class_();
}

