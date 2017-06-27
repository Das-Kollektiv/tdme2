// Generated from /tdme/src/tdme/engine/ObjectParticleSystemEntity.java
#include <tdme/engine/ObjectParticleSystemEntity.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/utils/_ArrayList.h>

using tdme::engine::ObjectParticleSystemEntity;
using tdme::engine::Engine;
using tdme::engine::Partition;
using tdme::engine::primitives::BoundingBox;
using tdme::utils::_ArrayList;

ObjectParticleSystemEntity::ObjectParticleSystemEntity(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ObjectParticleSystemEntity::ObjectParticleSystemEntity(String* id, Model* model, Vector3* scale, bool autoEmit, bool enableDynamicShadows, int32_t maxCount, ParticleEmitter* emitter) 
	: ObjectParticleSystemEntity(*static_cast< ::default_init_tag* >(0))
{
	ctor(id,model,scale,autoEmit,enableDynamicShadows,maxCount,emitter);
}

void ObjectParticleSystemEntity::ctor(String* id, Model* model, Vector3* scale, bool autoEmit, bool enableDynamicShadows, int32_t maxCount, ParticleEmitter* emitter)
{
	super::ctor(id, model, scale, autoEmit, enableDynamicShadows, maxCount, emitter);
}

void ObjectParticleSystemEntity::initialize()
{
}

BoundingBox* ObjectParticleSystemEntity::getBoundingBox()
{
	return boundingBox;
}

BoundingBox* ObjectParticleSystemEntity::getBoundingBoxTransformed()
{
	return boundingBoxTransformed;
}

_ArrayList* ObjectParticleSystemEntity::getEnabledObjects()
{
	return enabledObjects;
}

void ObjectParticleSystemEntity::fromTransformations(Transformations* transformations)
{
	super::fromTransformations(transformations);
	if (engine != nullptr && enabled == true)
		engine->partition->updateEntity(this);

}

void ObjectParticleSystemEntity::update()
{
	super::update();
	if (engine != nullptr && enabled == true)
		engine->partition->updateEntity(this);

}

void ObjectParticleSystemEntity::setEnabled(bool enabled)
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

void ObjectParticleSystemEntity::updateParticles()
{
	super::updateParticles();
	if (engine != nullptr && enabled == true)
		engine->partition->updateEntity(this);

}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ObjectParticleSystemEntity::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.ObjectParticleSystemEntity", 38);
    return c;
}

void ObjectParticleSystemEntity::dispose()
{
	ObjectParticleSystemEntityInternal::dispose();
}

Color4* ObjectParticleSystemEntity::getEffectColorAdd()
{
	return ObjectParticleSystemEntityInternal::getEffectColorAdd();
}

Color4* ObjectParticleSystemEntity::getEffectColorMul()
{
	return ObjectParticleSystemEntityInternal::getEffectColorMul();
}

String* ObjectParticleSystemEntity::getId()
{
	return ObjectParticleSystemEntityInternal::getId();
}

Vector3* ObjectParticleSystemEntity::getPivot()
{
	return Transformations::getPivot();
}

Rotations* ObjectParticleSystemEntity::getRotations()
{
	return Transformations::getRotations();
}

Vector3* ObjectParticleSystemEntity::getScale()
{
	return Transformations::getScale();
}

Matrix4x4* ObjectParticleSystemEntity::getTransformationsMatrix()
{
	return Transformations::getTransformationsMatrix();
}

Vector3* ObjectParticleSystemEntity::getTranslation()
{
	return Transformations::getTranslation();
}

bool ObjectParticleSystemEntity::isDynamicShadowingEnabled()
{
	return ObjectParticleSystemEntityInternal::isDynamicShadowingEnabled();
}

bool ObjectParticleSystemEntity::isEnabled()
{
	return ObjectParticleSystemEntityInternal::isEnabled();
}

bool ObjectParticleSystemEntity::isPickable()
{
	return ObjectParticleSystemEntityInternal::isPickable();
}

void ObjectParticleSystemEntity::setDynamicShadowingEnabled(bool dynamicShadowing)
{
	ObjectParticleSystemEntityInternal::setDynamicShadowingEnabled(dynamicShadowing);
}

void ObjectParticleSystemEntity::setEngine(Engine* engine)
{
	ObjectParticleSystemEntityInternal::setEngine(engine);
}

void ObjectParticleSystemEntity::setPickable(bool pickable)
{
	ObjectParticleSystemEntityInternal::setPickable(pickable);
}

void ObjectParticleSystemEntity::setRenderer(GLRenderer* renderer)
{
	ObjectParticleSystemEntityInternal::setRenderer(renderer);
}

java::lang::Class* ObjectParticleSystemEntity::getClass0()
{
	return class_();
}

