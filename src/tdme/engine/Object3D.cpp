#include <tdme/engine/Object3D.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/Partition.h>

using std::string;

using tdme::engine::Object3D;
using tdme::engine::Engine;
using tdme::engine::Partition;
using tdme::engine::Transformations;

Object3D::Object3D(const string& id, Model* model) :
	Object3DInternal(id, model)
{
}

void Object3D::setEngine(Engine* engine)
{
	this->engine = engine;
}

void Object3D::setRenderer(GLRenderer* renderer)
{
}

void Object3D::fromTransformations(const Transformations& transformations)
{
	Object3DInternal::fromTransformations(transformations);
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void Object3D::update()
{
	Object3DInternal::update();
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void Object3D::setEnabled(bool enabled)
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
	Object3DInternal::setEnabled(enabled);
}

bool Object3D::isFrustumCulling() {
	return frustumCulling;
}

void Object3D::setFrustumCulling(bool frustumCulling) {
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
	// delegate change to engine
	if (engine != nullptr) engine->updateEntity(this);
}

void Object3D::dispose()
{
	Object3DInternal::dispose();
}

void Object3D::initialize()
{
	Object3DInternal::initialize();
}

void Object3D::setDynamicShadowingEnabled(bool dynamicShadowing)
{
	Object3DInternal::setDynamicShadowingEnabled(dynamicShadowing);
}

void Object3D::setPickable(bool pickable)
{
	Object3DInternal::setPickable(pickable);
}

Matrix4x4* Object3D::getTransformationsMatrix(const string& id)
{
	return Object3DInternal::getTransformationsMatrix(id);
}

const Vector3& Object3D::getTranslation() const {
	return Transformations::getTranslation();
}

void Object3D::setTranslation(const Vector3& translation) {
	Transformations::setTranslation(translation);
}

const Vector3& Object3D::getScale() const {
	return Transformations::getScale();
}

void Object3D::setScale(const Vector3& scale) {
	Transformations::setScale(scale);
}

const Vector3& Object3D::getPivot() const {
	return Transformations::getPivot();
}

void Object3D::setPivot(const Vector3& pivot) {
	Transformations::setPivot(pivot);
}

const int Object3D::getRotationCount() const {
	return Transformations::getRotationCount();
}

Rotation& Object3D::getRotation(int idx) {
	return Transformations::getRotation(idx);
}

void Object3D::addRotation(const Vector3& axis, const float angle) {
	Transformations::addRotation(axis, angle);
}

void Object3D::removeRotation(const int idx) {
	Transformations::removeRotation(idx);
}

const Vector3& Object3D::getRotationAxis(const int idx) const {
	return Transformations::getRotationAxis(idx);
}

void Object3D::setRotationAxis(const int idx, const Vector3& axis) {
	Transformations::setRotationAxis(idx, axis);
}

const float Object3D::getRotationAngle(const int idx) const {
	return Transformations::getRotationAngle(idx);
}

void Object3D::setRotationAngle(const int idx, const float angle) {
	Transformations::setRotationAngle(idx, angle);
}

const Quaternion& Object3D::getRotationsQuaternion() const {
	return Transformations::getRotationsQuaternion();
}
