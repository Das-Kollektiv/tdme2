#include <tdme/engine/ObjectParticleSystemEntity.h>

#include <vector>
#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/primitives/BoundingBox.h>

using std::vector;
using std::wstring;

using tdme::engine::ObjectParticleSystemEntity;
using tdme::engine::Engine;
using tdme::engine::Partition;
using tdme::engine::primitives::BoundingBox;

ObjectParticleSystemEntity::ObjectParticleSystemEntity(const wstring& id, Model* model, Vector3* scale, bool autoEmit, bool enableDynamicShadows, int32_t maxCount, ParticleEmitter* emitter) :
	ObjectParticleSystemEntityInternal(id, model, scale, autoEmit, enableDynamicShadows, maxCount, emitter)
{
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

const vector<Object3D*>* ObjectParticleSystemEntity::getEnabledObjects()
{
	return &enabledObjects;
}

void ObjectParticleSystemEntity::fromTransformations(Transformations* transformations)
{
	ObjectParticleSystemEntityInternal::fromTransformations(transformations);
	if (engine != nullptr && enabled == true)
		engine->partition->updateEntity(this);

}

void ObjectParticleSystemEntity::update()
{
	ObjectParticleSystemEntityInternal::update();
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
	ObjectParticleSystemEntityInternal::setEnabled(enabled);
}

void ObjectParticleSystemEntity::updateParticles()
{
	ObjectParticleSystemEntityInternal::updateParticles();
	if (engine != nullptr && enabled == true)
		engine->partition->updateEntity(this);

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

const wstring& ObjectParticleSystemEntity::getId()
{
	return ObjectParticleSystemEntityInternal::getId();
}

Vector3& ObjectParticleSystemEntity::getPivot()
{
	return Transformations::getPivot();
}

Rotations* ObjectParticleSystemEntity::getRotations()
{
	return Transformations::getRotations();
}

Vector3& ObjectParticleSystemEntity::getScale()
{
	return Transformations::getScale();
}

Matrix4x4& ObjectParticleSystemEntity::getTransformationsMatrix()
{
	return Transformations::getTransformationsMatrix();
}

Vector3& ObjectParticleSystemEntity::getTranslation()
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

