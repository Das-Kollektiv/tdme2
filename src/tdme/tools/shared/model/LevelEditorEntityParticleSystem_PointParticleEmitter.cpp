#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleEmitter.h>

#include <tdme/engine/model/Color4.h>
#include <tdme/math/Vector3.h>

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter;
using tdme::engine::model::Color4;
using tdme::math::Vector3;

LevelEditorEntityParticleSystem_PointParticleEmitter::LevelEditorEntityParticleSystem_PointParticleEmitter() 
{
	count = 2000;
	lifeTime = 1500;
	lifeTimeRnd = 500;
	mass = 0.0f;
	massRnd = 0.0f;
	position.set(0.0f, 0.0f, 0.0f);
	velocity.set(0.0f, 1.0f, 0.0f);
	velocityRnd.set(0.0f, 0.5f, 0.0f);
	colorStart.set(0.5f, 0.5f, 0.5f, 0.5f);
	colorEnd.set(1.0f, 1.0f, 1.0f, 0.5f);
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
	return &position;
}

Vector3* LevelEditorEntityParticleSystem_PointParticleEmitter::getVelocity()
{
	return &velocity;
}

Vector3* LevelEditorEntityParticleSystem_PointParticleEmitter::getVelocityRnd()
{
	return &velocityRnd;
}

Color4* LevelEditorEntityParticleSystem_PointParticleEmitter::getColorStart()
{
	return &colorStart;
}

Color4* LevelEditorEntityParticleSystem_PointParticleEmitter::getColorEnd()
{
	return &colorEnd;
}

