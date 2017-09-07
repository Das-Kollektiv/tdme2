// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.java
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_CircleParticleEmitter.h>

#include <tdme/engine/model/Color4.h>
#include <tdme/math/Vector3.h>

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using tdme::engine::model::Color4;
using tdme::math::Vector3;

LevelEditorEntityParticleSystem_CircleParticleEmitter::LevelEditorEntityParticleSystem_CircleParticleEmitter() 
{
	count = 2000;
	lifeTime = 1500;
	lifeTimeRnd = 500;
	mass = 0.0f;
	massRnd = 0.0f;
	velocity.set(0.0f, 1.0f, 0.0f);
	velocityRnd.set(0.0f, 0.5f, 0.0f);
	colorStart.set(0.5f, 0.5f, 0.5f, 0.5f);
	colorEnd.set(1.0f, 1.0f, 1.0f, 0.5f);
	center.set(0.0f, 0.0f, 0.0f);
	radius = 0.5f;
	axis0.set(1.0f, 0.0f, 0.0f);
	axis1.set(0.0f, 0.0f, 1.0f);
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
	return &velocity;
}

Vector3* LevelEditorEntityParticleSystem_CircleParticleEmitter::getVelocityRnd()
{
	return &velocityRnd;
}

Color4* LevelEditorEntityParticleSystem_CircleParticleEmitter::getColorStart()
{
	return &colorStart;
}

Color4* LevelEditorEntityParticleSystem_CircleParticleEmitter::getColorEnd()
{
	return &colorEnd;
}

Vector3* LevelEditorEntityParticleSystem_CircleParticleEmitter::getCenter()
{
	return &center;
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
	return &axis0;
}

Vector3* LevelEditorEntityParticleSystem_CircleParticleEmitter::getAxis1()
{
	return &axis1;
}
