#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_SphereParticleEmitter.h>

#include <tdme/engine/model/Color4.h>
#include <tdme/math/Vector3.h>

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using tdme::engine::model::Color4;
using tdme::math::Vector3;

LevelEditorEntityParticleSystem_SphereParticleEmitter::LevelEditorEntityParticleSystem_SphereParticleEmitter() 
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
	center.set(0.0f, 0.5f, 0.0f);
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
	return &velocity;
}

Vector3* LevelEditorEntityParticleSystem_SphereParticleEmitter::getVelocityRnd()
{
	return &velocityRnd;
}

Color4* LevelEditorEntityParticleSystem_SphereParticleEmitter::getColorStart()
{
	return &colorStart;
}

Color4* LevelEditorEntityParticleSystem_SphereParticleEmitter::getColorEnd()
{
	return &colorEnd;
}

Vector3* LevelEditorEntityParticleSystem_SphereParticleEmitter::getCenter()
{
	return &center;
}

float LevelEditorEntityParticleSystem_SphereParticleEmitter::getRadius()
{
	return radius;
}

void LevelEditorEntityParticleSystem_SphereParticleEmitter::setRadius(float radius)
{
	this->radius = radius;
}

