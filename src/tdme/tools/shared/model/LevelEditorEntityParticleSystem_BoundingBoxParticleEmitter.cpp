// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.java
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/Vector3.h>

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::model::Color4;
using tdme::math::Vector3;

LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter() 
	: LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::ctor()
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
	obbCenter = new Vector3(0.0f, 0.5f, 0.0f);
	obbHalfextension = new Vector3(0.5f, 0.5f, 0.5f);
	obbAxis0 = new Vector3(1.0f, 0.0f, 0.0f);
	obbAxis1 = new Vector3(0.0f, 1.0f, 0.0f);
	obbAxis2 = new Vector3(0.0f, 0.0f, 1.0f);
}

int32_t LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getCount()
{
	return count;
}

void LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::setCount(int32_t count)
{
	this->count = count;
}

int64_t LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getLifeTime()
{
	return lifeTime;
}

void LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::setLifeTime(int64_t lifeTime)
{
	this->lifeTime = lifeTime;
}

int64_t LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getLifeTimeRnd()
{
	return lifeTimeRnd;
}

void LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::setLifeTimeRnd(int64_t lifeTimeRnd)
{
	this->lifeTimeRnd = lifeTimeRnd;
}

float LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getMass()
{
	return mass;
}

void LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::setMass(float mass)
{
	this->mass = mass;
}

float LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getMassRnd()
{
	return massRnd;
}

void LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::setMassRnd(float massRnd)
{
	this->massRnd = massRnd;
}

Vector3* LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getVelocity()
{
	return velocity;
}

Vector3* LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getVelocityRnd()
{
	return velocityRnd;
}

Color4* LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getColorStart()
{
	return colorStart;
}

Color4* LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getColorEnd()
{
	return colorEnd;
}

Vector3* LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getObbCenter()
{
	return obbCenter;
}

Vector3* LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getObbHalfextension()
{
	return obbHalfextension;
}

Vector3* LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getObbAxis0()
{
	return obbAxis0;
}

Vector3* LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getObbAxis1()
{
	return obbAxis1;
}

Vector3* LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getObbAxis2()
{
	return obbAxis2;
}

String* LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::toString()
{
	return ::java::lang::StringBuilder().append(u"BoundingBoxParticleEmitter [count="_j)->append(count)
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
		/*
		// TODO: implement me!
		->append(u", colorStart="_j)
		->append(static_cast< Object* >(colorStart))
		->append(u", colorEnd="_j)
		->append(static_cast< Object* >(colorEnd))
		*/
		->append(u", obbCenter="_j)
		->append(static_cast< Object* >(obbCenter))
		->append(u", obbHalfextension="_j)
		->append(static_cast< Object* >(obbHalfextension))
		->append(u", obbAxis0="_j)
		->append(static_cast< Object* >(obbAxis0))
		->append(u", obbAxis1="_j)
		->append(static_cast< Object* >(obbAxis1))
		->append(u", obbAxis2="_j)
		->append(static_cast< Object* >(obbAxis2))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.LevelEditorEntityParticleSystem.BoundingBoxParticleEmitter", 82);
    return c;
}

java::lang::Class* LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getClass0()
{
	return class_();
}

