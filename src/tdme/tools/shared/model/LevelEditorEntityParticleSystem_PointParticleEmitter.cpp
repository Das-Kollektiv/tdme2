// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.java
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleEmitter.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/Vector3.h>

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::model::Color4;
using tdme::math::Vector3;

LevelEditorEntityParticleSystem_PointParticleEmitter::LevelEditorEntityParticleSystem_PointParticleEmitter(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelEditorEntityParticleSystem_PointParticleEmitter::LevelEditorEntityParticleSystem_PointParticleEmitter() 
	: LevelEditorEntityParticleSystem_PointParticleEmitter(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void LevelEditorEntityParticleSystem_PointParticleEmitter::ctor()
{
	super::ctor();
	count = 2000;
	lifeTime = 1500;
	lifeTimeRnd = 500;
	mass = 0.0f;
	massRnd = 0.0f;
	position = new Vector3(0.0f, 0.0f, 0.0f);
	velocity = new Vector3(0.0f, 1.0f, 0.0f);
	velocityRnd = new Vector3(0.0f, 0.5f, 0.0f);
	colorStart = new Color4(0.5f, 0.5f, 0.5f, 0.5f);
	colorEnd = new Color4(1.0f, 1.0f, 1.0f, 0.5f);
}

int32_t LevelEditorEntityParticleSystem_PointParticleEmitter::getCount()
{
	return count;
}

void LevelEditorEntityParticleSystem_PointParticleEmitter::setCount(int32_t count)
{
	this->count = count;
}

int64_t LevelEditorEntityParticleSystem_PointParticleEmitter::getLifeTime()
{
	return lifeTime;
}

void LevelEditorEntityParticleSystem_PointParticleEmitter::setLifeTime(int64_t lifeTime)
{
	this->lifeTime = lifeTime;
}

int64_t LevelEditorEntityParticleSystem_PointParticleEmitter::getLifeTimeRnd()
{
	return lifeTimeRnd;
}

void LevelEditorEntityParticleSystem_PointParticleEmitter::setLifeTimeRnd(int64_t lifeTimeRnd)
{
	this->lifeTimeRnd = lifeTimeRnd;
}

float LevelEditorEntityParticleSystem_PointParticleEmitter::getMass()
{
	return mass;
}

void LevelEditorEntityParticleSystem_PointParticleEmitter::setMass(float mass)
{
	this->mass = mass;
}

float LevelEditorEntityParticleSystem_PointParticleEmitter::getMassRnd()
{
	return massRnd;
}

void LevelEditorEntityParticleSystem_PointParticleEmitter::setMassRnd(float massRnd)
{
	this->massRnd = massRnd;
}

Vector3* LevelEditorEntityParticleSystem_PointParticleEmitter::getPosition()
{
	return position;
}

Vector3* LevelEditorEntityParticleSystem_PointParticleEmitter::getVelocity()
{
	return velocity;
}

Vector3* LevelEditorEntityParticleSystem_PointParticleEmitter::getVelocityRnd()
{
	return velocityRnd;
}

Color4* LevelEditorEntityParticleSystem_PointParticleEmitter::getColorStart()
{
	return colorStart;
}

Color4* LevelEditorEntityParticleSystem_PointParticleEmitter::getColorEnd()
{
	return colorEnd;
}

String* LevelEditorEntityParticleSystem_PointParticleEmitter::toString()
{
	return ::java::lang::StringBuilder().append(u"PointParticleEmitter [count="_j)->append(count)
		->append(u", lifeTime="_j)
		->append(lifeTime)
		->append(u", lifeTimeRnd="_j)
		->append(lifeTimeRnd)
		->append(u", mass="_j)
		->append(mass)
		->append(u", massRnd="_j)
		->append(massRnd)
		->append(u", position="_j)
		->append(static_cast< Object* >(position))
		->append(u", velocity="_j)
		->append(static_cast< Object* >(velocity))
		->append(u", velocityRnd="_j)
		->append(static_cast< Object* >(velocityRnd))
		/*
		// TODO: Implement me!
		->append(u", colorStart="_j)
		->append(static_cast< Object* >(colorStart))
		->append(u", colorEnd="_j)
		->append(static_cast< Object* >(colorEnd))
		*/
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorEntityParticleSystem_PointParticleEmitter::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.LevelEditorEntityParticleSystem.PointParticleEmitter", 76);
    return c;
}

java::lang::Class* LevelEditorEntityParticleSystem_PointParticleEmitter::getClass0()
{
	return class_();
}

