#include <tdme/engine/PointsParticleSystemEntity.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/BoundingBox.h>

using std::string;

using tdme::engine::PointsParticleSystemEntity;
using tdme::engine::Engine;
using tdme::engine::Partition;
using tdme::engine::Transformations;
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

void PointsParticleSystemEntity::fromTransformations(const Transformations& transformations)
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

const Vector3& PointsParticleSystemEntity::getTranslation() const {
	return Transformations::getTranslation();
}

void PointsParticleSystemEntity::setTranslation(const Vector3& translation) {
	Transformations::setTranslation(translation);
}

const Vector3& PointsParticleSystemEntity::getScale() const {
	return Transformations::getScale();
}

void PointsParticleSystemEntity::setScale(const Vector3& scale) {
	Transformations::setScale(scale);
}

const Vector3& PointsParticleSystemEntity::getPivot() const {
	return Transformations::getPivot();
}

void PointsParticleSystemEntity::setPivot(const Vector3& pivot) {
	Transformations::setPivot(pivot);
}

const int PointsParticleSystemEntity::getRotationCount() const {
	return Transformations::getRotationCount();
}

Rotation& PointsParticleSystemEntity::getRotation(int idx) {
	return Transformations::getRotation(idx);
}

void PointsParticleSystemEntity::addRotation(const Vector3& axis, const float angle) {
	Transformations::addRotation(axis, angle);
}

void PointsParticleSystemEntity::removeRotation(const int idx) {
	Transformations::removeRotation(idx);
}

const Vector3& PointsParticleSystemEntity::getRotationAxis(const int idx) const {
	return Transformations::getRotationAxis(idx);
}

void PointsParticleSystemEntity::setRotationAxis(const int idx, const Vector3& axis) {
	Transformations::setRotationAxis(idx, axis);
}

const float PointsParticleSystemEntity::getRotationAngle(const int idx) const {
	return Transformations::getRotationAngle(idx);
}

void PointsParticleSystemEntity::setRotationAngle(const int idx, const float angle) {
	Transformations::setRotationAngle(idx, angle);
}

const Quaternion& PointsParticleSystemEntity::getRotationsQuaternion() const {
	return Transformations::getRotationsQuaternion();
}

const Matrix4x4& PointsParticleSystemEntity::getTransformationsMatrix() const {
	return Transformations::getTransformationsMatrix();
}

const Transformations& PointsParticleSystemEntity::getTransformations() const {
	return *this;
}
