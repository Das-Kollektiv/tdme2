// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/PointParticleEmitter.java
#include <tdme/engine/subsystems/particlesystem/PointParticleEmitter.h>

#include <java/lang/Math.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using tdme::engine::subsystems::particlesystem::PointParticleEmitter;
using java::lang::Math;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

PointParticleEmitter::PointParticleEmitter(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

PointParticleEmitter::PointParticleEmitter(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, float mass, float massRnd, Vector3* position, Vector3* velocity, Vector3* velocityRnd, Color4* colorStart, Color4* colorEnd) 
	: PointParticleEmitter(*static_cast< ::default_init_tag* >(0))
{
	ctor(count,lifeTime,lifeTimeRnd,mass,massRnd,position,velocity,velocityRnd,colorStart,colorEnd);
}

void PointParticleEmitter::ctor(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, float mass, float massRnd, Vector3* position, Vector3* velocity, Vector3* velocityRnd, Color4* colorStart, Color4* colorEnd)
{
	super::ctor();
	this->count = count;
	this->lifeTime = lifeTime;
	this->lifeTimeRnd = lifeTimeRnd;
	this->mass = mass;
	this->massRnd = massRnd;
	this->position = position;
	this->positionTransformed = new Vector3();
	this->positionTransformed->set(position);
	this->velocity = velocity;
	this->velocityRnd = velocityRnd;
	this->colorStart = colorStart;
	this->colorEnd = colorEnd;
}

int32_t PointParticleEmitter::getCount()
{
	return count;
}

Vector3* PointParticleEmitter::getVelocity()
{
	return velocity;
}

Vector3* PointParticleEmitter::getVelocityRnd()
{
	return velocityRnd;
}

Color4* PointParticleEmitter::getColorStart()
{
	return colorStart;
}

Color4* PointParticleEmitter::getColorEnd()
{
	return colorEnd;
}

void PointParticleEmitter::emit(Particle* particle)
{
	auto velocityXYZ = velocity->getArray();
	auto velocityRndXYZ = velocityRnd->getArray();
	particle->active = true;
	particle->position->set(positionTransformed);
	particle->velocity->set((*velocityXYZ)[0] + static_cast< float >((Math::random() * (*velocityRndXYZ)[0] * (Math::random() > 0.5 ? +1.0f : -1.0f))), (*velocityXYZ)[1] + static_cast< float >((Math::random() * (*velocityRndXYZ)[1] * (Math::random() > 0.5 ? +1.0f : -1.0f))), (*velocityXYZ)[2] + static_cast< float >((Math::random() * (*velocityRndXYZ)[2] * (Math::random() > 0.5 ? +1.0f : -1.0f))));
	particle->mass = mass + static_cast< float >((Math::random() * (massRnd)));
	particle->lifeTimeMax = lifeTime + static_cast< int64_t >((Math::random() * lifeTimeRnd));
	particle->lifeTimeCurrent = 0LL;
	particle->color->set(static_cast< Color4Base* >(colorStart));
	particle->colorAdd->set((colorEnd->getRed() - colorStart->getRed()) / particle->lifeTimeMax, (colorEnd->getGreen() - colorStart->getGreen()) / particle->lifeTimeMax, (colorEnd->getBlue() - colorStart->getBlue()) / particle->lifeTimeMax, (colorEnd->getAlpha() - colorStart->getAlpha()) / particle->lifeTimeMax);
}

void PointParticleEmitter::fromTransformations(Transformations* transformations)
{
	auto transformationsMatrix = transformations->getTransformationsMatrix();
	transformationsMatrix->multiply(position, positionTransformed);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PointParticleEmitter::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.particlesystem.PointParticleEmitter", 58);
    return c;
}

java::lang::Class* PointParticleEmitter::getClass0()
{
	return class_();
}

