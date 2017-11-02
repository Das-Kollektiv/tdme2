#include <tdme/engine/PointsParticleSystemEntity.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/primitives/BoundingBox.h>

using std::string;

using tdme::engine::PointsParticleSystemEntity;
using tdme::engine::Engine;
using tdme::engine::Partition;
using tdme::engine::primitives::BoundingBox;

PointsParticleSystemEntity::PointsParticleSystemEntity(const string& id, bool doCollisionTests, ParticleEmitter* emitter, int32_t maxPoints, bool autoEmit) :
	PointsParticleSystemEntityInternal(id, doCollisionTests, emitter, maxPoints, autoEmit)
{
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
	PointsParticleSystemEntityInternal::fromTransformations(transformations);
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void PointsParticleSystemEntity::update()
{
	PointsParticleSystemEntityInternal::update();
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void PointsParticleSystemEntity::setEnabled(bool enabled)
{
	if (this->enabled == enabled) return;
	if (frustumCulling == true) {
		if (enabled == true) {
			if (engine != nullptr) engine->partition->addEntity(this);
		} else {
			if (engine != nullptr) engine->partition->removeEntity(this);
		}
	}
	PointsParticleSystemEntityInternal::setEnabled(enabled);
}

void PointsParticleSystemEntity::updateParticles()
{
	PointsParticleSystemEntityInternal::updateParticles();
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

bool PointsParticleSystemEntity::isFrustumCulling() {
	return frustumCulling;
}

void PointsParticleSystemEntity::setFrustumCulling(bool frustumCulling) {
	if (enabled == true && engine != nullptr) {
		if (this->frustumCulling == true) {
			if (frustumCulling == false) engine->partition->removeEntity(this);
		} else {
			if (frustumCulling == true) engine->partition->addEntity(this);
		}
	}
	this->frustumCulling = frustumCulling;
}

void PointsParticleSystemEntity::dispose()
{
	PointsParticleSystemEntityInternal::dispose();
}

Color4& PointsParticleSystemEntity::getEffectColorAdd()
{
	return PointsParticleSystemEntityInternal::getEffectColorAdd();
}

Color4& PointsParticleSystemEntity::getEffectColorMul()
{
	return PointsParticleSystemEntityInternal::getEffectColorMul();
}

const string& PointsParticleSystemEntity::getId()
{
	return PointsParticleSystemEntityInternal::getId();
}

Vector3& PointsParticleSystemEntity::getPivot()
{
	return Transformations::getPivot();
}

Rotations* PointsParticleSystemEntity::getRotations()
{
	return Transformations::getRotations();
}

Vector3& PointsParticleSystemEntity::getScale()
{
	return Transformations::getScale();
}

Matrix4x4& PointsParticleSystemEntity::getTransformationsMatrix()
{
	return Transformations::getTransformationsMatrix();
}

Vector3& PointsParticleSystemEntity::getTranslation()
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

