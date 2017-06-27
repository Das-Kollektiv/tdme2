// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/SphereParticleEmitter.java
#include <tdme/engine/subsystems/particlesystem/SphereParticleEmitter.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Math.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using tdme::engine::subsystems::particlesystem::SphereParticleEmitter;
using java::lang::ClassCastException;
using java::lang::Math;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Sphere;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::math::Vector3;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

SphereParticleEmitter::SphereParticleEmitter(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

SphereParticleEmitter::SphereParticleEmitter(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, float mass, float massRnd, Sphere* sphere, Vector3* velocity, Vector3* velocityRnd, Color4* colorStart, Color4* colorEnd) 
	: SphereParticleEmitter(*static_cast< ::default_init_tag* >(0))
{
	ctor(count,lifeTime,lifeTimeRnd,mass,massRnd,sphere,velocity,velocityRnd,colorStart,colorEnd);
}

void SphereParticleEmitter::ctor(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, float mass, float massRnd, Sphere* sphere, Vector3* velocity, Vector3* velocityRnd, Color4* colorStart, Color4* colorEnd)
{
	super::ctor();
	this->count = count;
	this->lifeTime = lifeTime;
	this->lifeTimeRnd = lifeTimeRnd;
	this->mass = mass;
	this->massRnd = massRnd;
	this->sphere = sphere;
	this->sphereTransformed = java_cast< Sphere* >(sphere->clone());
	this->velocity = velocity;
	this->velocityRnd = velocityRnd;
	this->colorStart = colorStart;
	this->colorEnd = colorEnd;
}

int32_t SphereParticleEmitter::getCount()
{
	return count;
}

Vector3* SphereParticleEmitter::getVelocity()
{
	return velocity;
}

Vector3* SphereParticleEmitter::getVelocityRnd()
{
	return velocityRnd;
}

Color4* SphereParticleEmitter::getColorStart()
{
	return colorStart;
}

Color4* SphereParticleEmitter::getColorEnd()
{
	return colorEnd;
}

void SphereParticleEmitter::emit(Particle* particle)
{
	auto velocityXYZ = velocity->getArray();
	auto velocityRndXYZ = velocityRnd->getArray();
	particle->active = true;
	particle->position->set(static_cast< float >(Math::random()) * 2.0f - 1.0f, static_cast< float >(Math::random()) * 2.0f - 1.0f, static_cast< float >(Math::random()) * 2.0f - 1.0f)->normalize()->scale(sphereTransformed->getRadius());
	particle->position->add(sphereTransformed->getCenter());
	particle->velocity->set((*velocityXYZ)[0] + static_cast< float >((Math::random() * (*velocityRndXYZ)[0] * (Math::random() > 0.5 ? +1.0f : -1.0f))), (*velocityXYZ)[1] + static_cast< float >((Math::random() * (*velocityRndXYZ)[1] * (Math::random() > 0.5 ? +1.0f : -1.0f))), (*velocityXYZ)[2] + static_cast< float >((Math::random() * (*velocityRndXYZ)[2] * (Math::random() > 0.5 ? +1.0f : -1.0f))));
	particle->mass = mass + static_cast< float >((Math::random() * (massRnd)));
	particle->lifeTimeMax = lifeTime + static_cast< int64_t >((Math::random() * lifeTimeRnd));
	particle->lifeTimeCurrent = 0LL;
	particle->color->set(static_cast< Color4Base* >(colorStart));
	particle->colorAdd->set((colorEnd->getRed() - colorStart->getRed()) / particle->lifeTimeMax, (colorEnd->getGreen() - colorStart->getGreen()) / particle->lifeTimeMax, (colorEnd->getBlue() - colorStart->getBlue()) / particle->lifeTimeMax, (colorEnd->getAlpha() - colorStart->getAlpha()) / particle->lifeTimeMax);
}

void SphereParticleEmitter::fromTransformations(Transformations* transformations)
{
	sphereTransformed->fromBoundingVolumeWithTransformations(sphere, transformations);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* SphereParticleEmitter::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.particlesystem.SphereParticleEmitter", 59);
    return c;
}

java::lang::Class* SphereParticleEmitter::getClass0()
{
	return class_();
}

