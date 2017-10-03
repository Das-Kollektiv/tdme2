#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter.h>

#include <tdme/engine/model/Color4.h>
#include <tdme/math/Vector3.h>

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
using tdme::engine::model::Color4;
using tdme::math::Vector3;

LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter() 
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
	obbCenter.set(0.0f, 0.5f, 0.0f);
	obbHalfextension.set(0.5f, 0.5f, 0.5f);
	obbAxis0.set(1.0f, 0.0f, 0.0f);
	obbAxis1.set(0.0f, 1.0f, 0.0f);
	obbAxis2.set(0.0f, 0.0f, 1.0f);
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

Vector3& LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getVelocity()
{
	return velocity;
}

Vector3& LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getVelocityRnd()
{
	return velocityRnd;
}

Color4* LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getColorStart()
{
	return &colorStart;
}

Color4* LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getColorEnd()
{
	return &colorEnd;
}

Vector3& LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getObbCenter()
{
	return obbCenter;
}

Vector3& LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getObbHalfextension()
{
	return obbHalfextension;
}

Vector3& LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getObbAxis0()
{
	return obbAxis0;
}

Vector3& LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getObbAxis1()
{
	return obbAxis1;
}

Vector3& LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter::getObbAxis2()
{
	return obbAxis2;
}
