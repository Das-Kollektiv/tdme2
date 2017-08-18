// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/BoundingBoxParticleEmitter.java
#include <tdme/engine/subsystems/particlesystem/BoundingBoxParticleEmitter.h>

#include <java/lang/Math.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::particlesystem::BoundingBoxParticleEmitter;
using java::lang::Math;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::math::Vector3;

BoundingBoxParticleEmitter::BoundingBoxParticleEmitter(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

BoundingBoxParticleEmitter::BoundingBoxParticleEmitter(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, float mass, float massRnd, OrientedBoundingBox* obb, Vector3* velocity, Vector3* velocityRnd, Color4* colorStart, Color4* colorEnd) 
	: BoundingBoxParticleEmitter(*static_cast< ::default_init_tag* >(0))
{
	ctor(count,lifeTime,lifeTimeRnd,mass,massRnd,obb,velocity,velocityRnd,colorStart,colorEnd);
}

void BoundingBoxParticleEmitter::init()
{
	tmpAxis = new Vector3();
}

void BoundingBoxParticleEmitter::ctor(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, float mass, float massRnd, OrientedBoundingBox* obb, Vector3* velocity, Vector3* velocityRnd, Color4* colorStart, Color4* colorEnd)
{
	super::ctor();
	init();
	this->count = count;
	this->lifeTime = lifeTime;
	this->lifeTimeRnd = lifeTimeRnd;
	this->mass = mass;
	this->massRnd = massRnd;
	this->obb = obb;
	this->velocity = velocity;
	this->velocityRnd = velocityRnd;
	this->colorStart = colorStart;
	this->colorEnd = colorEnd;
	this->obbTransformed = dynamic_cast< OrientedBoundingBox* >(obb->clone());
}

int32_t BoundingBoxParticleEmitter::getCount()
{
	return count;
}

Vector3* BoundingBoxParticleEmitter::getVelocity()
{
	return velocity;
}

Vector3* BoundingBoxParticleEmitter::getVelocityRnd()
{
	return velocityRnd;
}

Color4* BoundingBoxParticleEmitter::getColorStart()
{
	return colorStart;
}

Color4* BoundingBoxParticleEmitter::getColorEnd()
{
	return colorEnd;
}

void BoundingBoxParticleEmitter::emit(Particle* particle)
{
	auto velocityXYZ = velocity->getArray();
	auto velocityRndXYZ = velocityRnd->getArray();
	particle->active = true;
	auto obbAxes = obbTransformed->getAxes();
	auto obbHalfExtensionXYZ = obbTransformed->getHalfExtension()->getArray();
	particle->position->set(0.0f, 0.0f, 0.0f);
	particle->position->add(tmpAxis->set(&(*obbAxes)[0])->scale((static_cast< float >(Math::random()) * (*obbHalfExtensionXYZ)[0] * 2.0f) - (*obbHalfExtensionXYZ)[0]));
	particle->position->add(tmpAxis->set(&(*obbAxes)[1])->scale((static_cast< float >(Math::random()) * (*obbHalfExtensionXYZ)[1] * 2.0f) - (*obbHalfExtensionXYZ)[1]));
	particle->position->add(tmpAxis->set(&(*obbAxes)[2])->scale((static_cast< float >(Math::random()) * (*obbHalfExtensionXYZ)[2] * 2.0f) - (*obbHalfExtensionXYZ)[2]));
	particle->position->add(obbTransformed->getCenter());
	particle->velocity->set((*velocityXYZ)[0] + static_cast< float >((Math::random() * (*velocityRndXYZ)[0] * (Math::random() > 0.5 ? +1.0f : -1.0f))), (*velocityXYZ)[1] + static_cast< float >((Math::random() * (*velocityRndXYZ)[1] * (Math::random() > 0.5 ? +1.0f : -1.0f))), (*velocityXYZ)[2] + static_cast< float >((Math::random() * (*velocityRndXYZ)[2] * (Math::random() > 0.5 ? +1.0f : -1.0f))));
	particle->mass = mass + static_cast< float >((Math::random() * (massRnd)));
	particle->lifeTimeMax = lifeTime + static_cast< int64_t >((Math::random() * lifeTimeRnd));
	particle->lifeTimeCurrent = 0LL;
	particle->color->set(static_cast< Color4Base* >(colorStart));
	particle->colorAdd->set((colorEnd->getRed() - colorStart->getRed()) / particle->lifeTimeMax, (colorEnd->getGreen() - colorStart->getGreen()) / particle->lifeTimeMax, (colorEnd->getBlue() - colorStart->getBlue()) / particle->lifeTimeMax, (colorEnd->getAlpha() - colorStart->getAlpha()) / particle->lifeTimeMax);
}

void BoundingBoxParticleEmitter::fromTransformations(Transformations* transformations)
{
	obbTransformed->fromBoundingVolumeWithTransformations(obb, transformations);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* BoundingBoxParticleEmitter::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.particlesystem.BoundingBoxParticleEmitter", 64);
    return c;
}

java::lang::Class* BoundingBoxParticleEmitter::getClass0()
{
	return class_();
}

