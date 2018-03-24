#include <tdme/engine/ObjectParticleSystemEntity.h>

#include <vector>
#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/BoundingBox.h>

using std::vector;
using std::string;

using tdme::engine::ObjectParticleSystemEntity;
using tdme::engine::Engine;
using tdme::engine::Partition;
using tdme::engine::Transformations;
using tdme::engine::primitives::BoundingBox;

ObjectParticleSystemEntity::ObjectParticleSystemEntity(const string& id, Model* model, const Vector3& scale, bool autoEmit, bool enableDynamicShadows, int32_t maxCount, ParticleEmitter* emitter) :
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

void ObjectParticleSystemEntity::fromTransformations(const Transformations& transformations)
{
	ObjectParticleSystemEntityInternal::fromTransformations(transformations);
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void ObjectParticleSystemEntity::update()
{
	ObjectParticleSystemEntityInternal::update();
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void ObjectParticleSystemEntity::setEnabled(bool enabled)
{
	// return if enable state has not changed
	if (this->enabled == enabled) return;
	// frustum culling enabled?
	if (frustumCulling == true) {
		// yeo, add or remove from partition
		if (enabled == true) {
			if (engine != nullptr) engine->partition->addEntity(this);
		} else {
			if (engine != nullptr) engine->partition->removeEntity(this);
		}
	}
	// call parent class::setEnabled()
	ObjectParticleSystemEntityInternal::setEnabled(enabled);
}

void ObjectParticleSystemEntity::updateParticles()
{
	ObjectParticleSystemEntityInternal::updateParticles();
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

bool ObjectParticleSystemEntity::isFrustumCulling() {
	return frustumCulling;
}

void ObjectParticleSystemEntity::setFrustumCulling(bool frustumCulling) {
	// check if enabled and engine attached
	if (enabled == true && engine != nullptr) {
		// had frustum culling
		if (this->frustumCulling == true) {
			// yep, remove if set to false now
			if (frustumCulling == false) engine->partition->removeEntity(this);
		} else {
			// yep, add if set to true now
			if (frustumCulling == true) engine->partition->addEntity(this);
		}
	}
	this->frustumCulling = frustumCulling;
}

void ObjectParticleSystemEntity::dispose()
{
	ObjectParticleSystemEntityInternal::dispose();
}

Color4& ObjectParticleSystemEntity::getEffectColorAdd()
{
	return ObjectParticleSystemEntityInternal::getEffectColorAdd();
}

Color4& ObjectParticleSystemEntity::getEffectColorMul()
{
	return ObjectParticleSystemEntityInternal::getEffectColorMul();
}

const string& ObjectParticleSystemEntity::getId()
{
	return ObjectParticleSystemEntityInternal::getId();
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

const Vector3& ObjectParticleSystemEntity::getTranslation() const {
	return Transformations::getTranslation();
}

void ObjectParticleSystemEntity::setTranslation(const Vector3& translation) {
	Transformations::setTranslation(translation);
}

const Vector3& ObjectParticleSystemEntity::getScale() const {
	return Transformations::getScale();
}

void ObjectParticleSystemEntity::setScale(const Vector3& scale) {
	Transformations::setScale(scale);
}

const Vector3& ObjectParticleSystemEntity::getPivot() const {
	return Transformations::getPivot();
}

void ObjectParticleSystemEntity::setPivot(const Vector3& pivot) {
	Transformations::setPivot(pivot);
}

const int ObjectParticleSystemEntity::getRotationCount() const {
	return Transformations::getRotationCount();
}

Rotation& ObjectParticleSystemEntity::getRotation(int idx) {
	return Transformations::getRotation(idx);
}

void ObjectParticleSystemEntity::addRotation(const Vector3& axis, const float angle) {
	Transformations::addRotation(axis, angle);
}

void ObjectParticleSystemEntity::removeRotation(const int idx) {
	Transformations::removeRotation(idx);
}

const Vector3& ObjectParticleSystemEntity::getRotationAxis(const int idx) const {
	Transformations::getRotationAxis(idx);
}

void ObjectParticleSystemEntity::setRotationAxis(const int idx, const Vector3& axis) {
	Transformations::setRotationAxis(idx, axis);
}

const float ObjectParticleSystemEntity::getRotationAngle(const int idx) const {
	return Transformations::getRotationAngle(idx);
}

void ObjectParticleSystemEntity::setRotationAngle(const int idx, const float angle) {
	Transformations::setRotationAngle(idx, angle);
}

const Quaternion& ObjectParticleSystemEntity::getRotationsQuaternion() const {
	return Transformations::getRotationsQuaternion();
}

const Matrix4x4& ObjectParticleSystemEntity::getTransformationsMatrix() const {
	return Transformations::getTransformationsMatrix();
}

const Transformations& ObjectParticleSystemEntity::getTransformations() const {
	return *this;
}
