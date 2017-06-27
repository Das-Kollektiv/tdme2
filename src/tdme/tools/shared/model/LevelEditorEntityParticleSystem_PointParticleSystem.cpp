// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.java
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleSystem.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem;
using java::lang::String;
using java::lang::StringBuilder;

LevelEditorEntityParticleSystem_PointParticleSystem::LevelEditorEntityParticleSystem_PointParticleSystem(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelEditorEntityParticleSystem_PointParticleSystem::LevelEditorEntityParticleSystem_PointParticleSystem() 
	: LevelEditorEntityParticleSystem_PointParticleSystem(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void LevelEditorEntityParticleSystem_PointParticleSystem::ctor()
{
	super::ctor();
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

String* LevelEditorEntityParticleSystem_PointParticleSystem::toString()
{
	return ::java::lang::StringBuilder().append(u"PointParticleSystem [maxPoints="_j)->append(maxPoints)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorEntityParticleSystem_PointParticleSystem::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.LevelEditorEntityParticleSystem.PointParticleSystem", 75);
    return c;
}

java::lang::Class* LevelEditorEntityParticleSystem_PointParticleSystem::getClass0()
{
	return class_();
}

