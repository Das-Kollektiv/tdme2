// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.java
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity.h>

#include <tdme/engine/model/Color4.h>
#include <tdme/math/Vector3.h>

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::engine::model::Color4;
using tdme::math::Vector3;

LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity() 
{
	count = 2000;
	lifeTime = 1500;
	lifeTimeRnd = 500;
	mass = 0.0f;
	massRnd = 0.0f;
	velocity = 1.0f;
	velocityRnd = 0.5f;
	colorStart.set(0.5f, 0.5f, 0.5f, 0.5f);
	colorEnd.set(1.0f, 1.0f, 1.0f, 0.5f);
	center.set(0.0f, 0.0f, 0.0f);
	radius = 0.5f;
	axis0.set(1.0f, 0.0f, 0.0f);
	axis1.set(0.0f, 0.0f, 1.0f);
}

int32_t LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::getCount()
{
	return count;
}

void LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::setCount(int32_t count)
{
	this->count = count;
}

int64_t LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::getLifeTime()
{
	return lifeTime;
}

void LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::setLifeTime(int64_t lifeTime)
{
	this->lifeTime = lifeTime;
}

int64_t LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::getLifeTimeRnd()
{
	return lifeTimeRnd;
}

void LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::setLifeTimeRnd(int64_t lifeTimeRnd)
{
	this->lifeTimeRnd = lifeTimeRnd;
}

float LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::getMass()
{
	return mass;
}

void LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::setMass(float mass)
{
	this->mass = mass;
}

float LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::getMassRnd()
{
	return massRnd;
}

void LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::setMassRnd(float massRnd)
{
	this->massRnd = massRnd;
}

float LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::getVelocity()
{
	return velocity;
}

void LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::setVelocity(float velocity)
{
	this->velocity = velocity;
}

float LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::getVelocityRnd()
{
	return velocityRnd;
}

void LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::setVelocityRnd(float velocityRnd)
{
	this->velocityRnd = velocityRnd;
}

Color4* LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::getColorStart()
{
	return &colorStart;
}

Color4* LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::getColorEnd()
{
	return &colorEnd;
}

Vector3* LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::getCenter()
{
	return &center;
}

float LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::getRadius()
{
	return radius;
}

void LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::setRadius(float radius)
{
	this->radius = radius;
}

Vector3* LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::getAxis0()
{
	return &axis0;
}

Vector3* LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity::getAxis1()
{
	return &axis1;
}
