// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.java
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_CircleParticleEmitter.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/Vector3.h>

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::model::Color4;
using tdme::math::Vector3;

LevelEditorEntityParticleSystem_CircleParticleEmitter::LevelEditorEntityParticleSystem_CircleParticleEmitter(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelEditorEntityParticleSystem_CircleParticleEmitter::LevelEditorEntityParticleSystem_CircleParticleEmitter() 
	: LevelEditorEntityParticleSystem_CircleParticleEmitter(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void LevelEditorEntityParticleSystem_CircleParticleEmitter::ctor()
{
	super::ctor();
	count = 2000;
	lifeTime = 1500;
	lifeTimeRnd = 500;
	mass = 0.0f;
	massRnd = 0.0f;
	velocity = new Vector3(0.0f, 1.0f, 0.0f);
	velocityRnd = new Vector3(0.0f, 0.5f, 0.0f);
	colorStart = new Color4(0.5f, 0.5f, 0.5f, 0.5f);
	colorEnd = new Color4(1.0f, 1.0f, 1.0f, 0.5f);
	center = new Vector3(0.0f, 0.0f, 0.0f);
	radius = 0.5f;
	axis0 = new Vector3(1.0f, 0.0f, 0.0f);
	axis1 = new Vector3(0.0f, 0.0f, 1.0f);
}

int32_t LevelEditorEntityParticleSystem_CircleParticleEmitter::getCount()
{
	return count;
}

void LevelEditorEntityParticleSystem_CircleParticleEmitter::setCount(int32_t count)
{
	this->count = count;
}

int64_t LevelEditorEntityParticleSystem_CircleParticleEmitter::getLifeTime()
{
	return lifeTime;
}

void LevelEditorEntityParticleSystem_CircleParticleEmitter::setLifeTime(int64_t lifeTime)
{
	this->lifeTime = lifeTime;
}

int64_t LevelEditorEntityParticleSystem_CircleParticleEmitter::getLifeTimeRnd()
{
	return lifeTimeRnd;
}

void LevelEditorEntityParticleSystem_CircleParticleEmitter::setLifeTimeRnd(int64_t lifeTimeRnd)
{
	this->lifeTimeRnd = lifeTimeRnd;
}

float LevelEditorEntityParticleSystem_CircleParticleEmitter::getMass()
{
	return mass;
}

void LevelEditorEntityParticleSystem_CircleParticleEmitter::setMass(float mass)
{
	this->mass = mass;
}

float LevelEditorEntityParticleSystem_CircleParticleEmitter::getMassRnd()
{
	return massRnd;
}

void LevelEditorEntityParticleSystem_CircleParticleEmitter::setMassRnd(float massRnd)
{
	this->massRnd = massRnd;
}

Vector3* LevelEditorEntityParticleSystem_CircleParticleEmitter::getVelocity()
{
	return velocity;
}

Vector3* LevelEditorEntityParticleSystem_CircleParticleEmitter::getVelocityRnd()
{
	return velocityRnd;
}

Color4* LevelEditorEntityParticleSystem_CircleParticleEmitter::getColorStart()
{
	return colorStart;
}

Color4* LevelEditorEntityParticleSystem_CircleParticleEmitter::getColorEnd()
{
	return colorEnd;
}

Vector3* LevelEditorEntityParticleSystem_CircleParticleEmitter::getCenter()
{
	return center;
}

float LevelEditorEntityParticleSystem_CircleParticleEmitter::getRadius()
{
	return radius;
}

void LevelEditorEntityParticleSystem_CircleParticleEmitter::setRadius(float radius)
{
	this->radius = radius;
}

Vector3* LevelEditorEntityParticleSystem_CircleParticleEmitter::getAxis0()
{
	return axis0;
}

Vector3* LevelEditorEntityParticleSystem_CircleParticleEmitter::getAxis1()
{
	return axis1;
}

String* LevelEditorEntityParticleSystem_CircleParticleEmitter::toString()
{
	return ::java::lang::StringBuilder().append(u"CircleParticleEmitter [count="_j)->append(count)
		->append(u", lifeTime="_j)
		->append(lifeTime)
		->append(u", lifeTimeRnd="_j)
		->append(lifeTimeRnd)
		->append(u", mass="_j)
		->append(mass)
		->append(u", massRnd="_j)
		->append(massRnd)
		->append(u", velocity="_j)
		->append(static_cast< Object* >(velocity))
		->append(u", velocityRnd="_j)
		->append(static_cast< Object* >(velocityRnd))
		->append(u", colorStart="_j)
		->append(static_cast< Object* >(colorStart))
		->append(u", colorEnd="_j)
		->append(static_cast< Object* >(colorEnd))
		->append(u", center="_j)
		->append(static_cast< Object* >(center))
		->append(u", radius="_j)
		->append(radius)
		->append(u", axis0="_j)
		->append(static_cast< Object* >(axis0))
		->append(u", axis1="_j)
		->append(static_cast< Object* >(axis1))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorEntityParticleSystem_CircleParticleEmitter::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.LevelEditorEntityParticleSystem.CircleParticleEmitter", 77);
    return c;
}

java::lang::Class* LevelEditorEntityParticleSystem_CircleParticleEmitter::getClass0()
{
	return class_();
}

