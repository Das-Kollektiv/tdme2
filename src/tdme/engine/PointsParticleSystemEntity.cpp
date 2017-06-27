// Generated from /tdme/src/tdme/engine/PointsParticleSystemEntity.java
#include <tdme/engine/PointsParticleSystemEntity.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/primitives/BoundingBox.h>

using tdme::engine::PointsParticleSystemEntity;
using tdme::engine::Engine;
using tdme::engine::Partition;
using tdme::engine::primitives::BoundingBox;

PointsParticleSystemEntity::PointsParticleSystemEntity(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

PointsParticleSystemEntity::PointsParticleSystemEntity(String* id, bool doCollisionTests, ParticleEmitter* emitter, int32_t maxPoints, bool autoEmit) 
	: PointsParticleSystemEntity(*static_cast< ::default_init_tag* >(0))
{
	ctor(id,doCollisionTests,emitter,maxPoints,autoEmit);
}

void PointsParticleSystemEntity::ctor(String* id, bool doCollisionTests, ParticleEmitter* emitter, int32_t maxPoints, bool autoEmit)
{
	super::ctor(id, doCollisionTests, emitter, maxPoints, autoEmit);
}

void PointsParticleSystemEntity::initialize()
{
}

BoundingBox* PointsParticleSystemEntity::getBoundingBox()
{
	return boundingBox;
}

BoundingBox* PointsParticleSystemEntity::getBoundingBoxTransformed()
{
	return boundingBoxTransformed;
}

void PointsParticleSystemEntity::fromTransformations(Transformations* transformations)
{
	super::fromTransformations(transformations);
	if (engine != nullptr && enabled == true)
		engine->partition->updateEntity(this);

}

void PointsParticleSystemEntity::update()
{
	super::update();
	if (engine != nullptr && enabled == true)
		engine->partition->updateEntity(this);

}

void PointsParticleSystemEntity::setEnabled(bool enabled)
{
	if (this->enabled == enabled)
		return;

	if (enabled == true) {
		if (engine != nullptr)
			engine->partition->addEntity(this);

	} else {
		if (engine != nullptr)
			engine->partition->removeEntity(this);

	}
	super::setEnabled(enabled);
}

void PointsParticleSystemEntity::updateParticles()
{
	super::updateParticles();
	if (engine != nullptr && enabled == true)
		engine->partition->updateEntity(this);

}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PointsParticleSystemEntity::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.PointsParticleSystemEntity", 38);
    return c;
}

void PointsParticleSystemEntity::dispose()
{
	PointsParticleSystemEntityInternal::dispose();
}

Color4* PointsParticleSystemEntity::getEffectColorAdd()
{
	return PointsParticleSystemEntityInternal::getEffectColorAdd();
}

Color4* PointsParticleSystemEntity::getEffectColorMul()
{
	return PointsParticleSystemEntityInternal::getEffectColorMul();
}

String* PointsParticleSystemEntity::getId()
{
	return PointsParticleSystemEntityInternal::getId();
}

Vector3* PointsParticleSystemEntity::getPivot()
{
	return Transformations::getPivot();
}

Rotations* PointsParticleSystemEntity::getRotations()
{
	return Transformations::getRotations();
}

Vector3* PointsParticleSystemEntity::getScale()
{
	return Transformations::getScale();
}

Matrix4x4* PointsParticleSystemEntity::getTransformationsMatrix()
{
	return Transformations::getTransformationsMatrix();
}

Vector3* PointsParticleSystemEntity::getTranslation()
{
	return Transformations::getTranslation();
}

bool PointsParticleSystemEntity::isDynamicShadowingEnabled()
{
	return PointsParticleSystemEntityInternal::isDynamicShadowingEnabled();
}

bool PointsParticleSystemEntity::isEnabled()
{
	return PointsParticleSystemEntityInternal::isEnabled();
}

bool PointsParticleSystemEntity::isPickable()
{
	return PointsParticleSystemEntityInternal::isPickable();
}

void PointsParticleSystemEntity::setDynamicShadowingEnabled(bool dynamicShadowing)
{
	PointsParticleSystemEntityInternal::setDynamicShadowingEnabled(dynamicShadowing);
}

void PointsParticleSystemEntity::setEngine(Engine* engine)
{
	PointsParticleSystemEntityInternal::setEngine(engine);
}

void PointsParticleSystemEntity::setPickable(bool pickable)
{
	PointsParticleSystemEntityInternal::setPickable(pickable);
}

void PointsParticleSystemEntity::setRenderer(GLRenderer* renderer)
{
	PointsParticleSystemEntityInternal::setRenderer(renderer);
}

java::lang::Class* PointsParticleSystemEntity::getClass0()
{
	return class_();
}

