#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleSystem.h>

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem;

LevelEditorEntityParticleSystem_PointParticleSystem::LevelEditorEntityParticleSystem_PointParticleSystem() 
{
	maxPoints = 4000;
	autoEmit = true;
}

int32_t LevelEditorEntityParticleSystem_PointParticleSystem::getMaxPoints()
{
	return maxPoints;
}

void LevelEditorEntityParticleSystem_PointParticleSystem::setMaxPoints(int32_t maxPoints)
{
	this->maxPoints = maxPoints;
}

bool LevelEditorEntityParticleSystem_PointParticleSystem::isAutoEmit()
{
	return autoEmit;
}

void LevelEditorEntityParticleSystem_PointParticleSystem::setAutoEmit(bool autoEmit)
{
	this->autoEmit = autoEmit;
}
