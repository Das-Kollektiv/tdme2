// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.java
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_SphereParticleEmitter.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/Vector3.h>

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::model::Color4;
using tdme::math::Vector3;

LevelEditorEntityParticleSystem_SphereParticleEmitter::LevelEditorEntityParticleSystem_SphereParticleEmitter(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelEditorEntityParticleSystem_SphereParticleEmitter::LevelEditorEntityParticleSystem_SphereParticleEmitter() 
	: LevelEditorEntityParticleSystem_SphereParticleEmitter(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void LevelEditorEntityParticleSystem_SphereParticleEmitter::ctor()
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
	center = new Vector3(0.0f, 0.5f, 0.0f);
	radius = 0.5f;
}

int32_t LevelEditorEntityParticleSystem_SphereParticleEmitter::getCount()
{
	return count;
}

void LevelEditorEntityParticleSystem_SphereParticleEmitter::setCount(int32_t count)
{
	this->count = count;
}

int64_t LevelEditorEntityParticleSystem_SphereParticleEmitter::getLifeTime()
{
	return lifeTime;
}

void LevelEditorEntityParticleSystem_SphereParticleEmitter::setLifeTime(int64_t lifeTime)
{
	this->lifeTime = lifeTime;
}

int64_t LevelEditorEntityParticleSystem_SphereParticleEmitter::getLifeTimeRnd()
{
	return lifeTimeRnd;
}

void LevelEditorEntityParticleSystem_SphereParticleEmitter::setLifeTimeRnd(int64_t lifeTimeRnd)
{
	this->lifeTimeRnd = lifeTimeRnd;
}

float LevelEditorEntityParticleSystem_SphereParticleEmitter::getMass()
{
	return mass;
}

void LevelEditorEntityParticleSystem_SphereParticleEmitter::setMass(float mass)
{
	this->mass = mass;
}

float LevelEditorEntityParticleSystem_SphereParticleEmitter::getMassRnd()
{
	return massRnd;
}

void LevelEditorEntityParticleSystem_SphereParticleEmitter::setMassRnd(float massRnd)
{
	this->massRnd = massRnd;
}

Vector3* LevelEditorEntityParticleSystem_SphereParticleEmitter::getVelocity()
{
	return velocity;
}

Vector3* LevelEditorEntityParticleSystem_SphereParticleEmitter::getVelocityRnd()
{
	return velocityRnd;
}

Color4* LevelEditorEntityParticleSystem_SphereParticleEmitter::getColorStart()
{
	return colorStart;
}

Color4* LevelEditorEntityParticleSystem_SphereParticleEmitter::getColorEnd()
{
	return colorEnd;
}

Vector3* LevelEditorEntityParticleSystem_SphereParticleEmitter::getCenter()
{
	return center;
}

float LevelEditorEntityParticleSystem_SphereParticleEmitter::getRadius()
{
	return radius;
}

void LevelEditorEntityParticleSystem_SphereParticleEmitter::setRadius(float radius)
{
	this->radius = radius;
}

String* LevelEditorEntityParticleSystem_SphereParticleEmitter::toString()
{
	return ::java::lang::StringBuilder().append(u"SphereParticleEmitter [count="_j)->append(count)
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
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorEntityParticleSystem_SphereParticleEmitter::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.LevelEditorEntityParticleSystem.SphereParticleEmitter", 77);
    return c;
}

java::lang::Class* LevelEditorEntityParticleSystem_SphereParticleEmitter::getClass0()
{
	return class_();
}

