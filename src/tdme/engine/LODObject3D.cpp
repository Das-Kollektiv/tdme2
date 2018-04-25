#include <tdme/engine/LODObject3D.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/Partition.h>
#include <tdme/utils/Console.h>

using std::string;

using tdme::engine::LODObject3D;
using tdme::engine::Engine;
using tdme::engine::Object3D;
using tdme::engine::Partition;
using tdme::engine::Transformations;
using tdme::utils::Console;

LODObject3D::LODObject3D(
	const string& id,
	Model* modelLOD1,
	LODLevelType levelTypeLOD2,
	float modelLOD2MinDistance,
	Model* modelLOD2,
	LODLevelType levelTypeLOD3,
	float modelLOD3MinDistance,
	Model* modelLOD3,
	float planeRotationYLOD2,
	float planeRotationYLOD3
):
	id(id),
	modelLOD1(modelLOD1),
	levelTypeLOD2(levelTypeLOD2),
	modelLOD2MinDistance(modelLOD2MinDistance),
	modelLOD2(modelLOD2),
	levelTypeLOD3(levelTypeLOD3),
	modelLOD3MinDistance(modelLOD3MinDistance),
	modelLOD3(modelLOD3),
	planeRotationYLOD2(planeRotationYLOD2),
	planeRotationYLOD3(planeRotationYLOD3)
{
	this->enabled = true;
	this->pickable = false;
	this->dynamicShadowing = false;
	this->effectColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
	this->effectColorMulLOD2.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAddLOD2.set(0.0f, 0.0f, 0.0f, 0.0f);
	this->effectColorMulLOD3.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAddLOD3.set(0.0f, 0.0f, 0.0f, 0.0f);
	transformationsRotationYIndex = -1;

	if (modelLOD1 != nullptr) objectLOD1 = new Object3D(id + ".lod1", modelLOD1);
	if (modelLOD2 != nullptr) objectLOD2 = new Object3D(id + ".lod2", modelLOD2);
	if (modelLOD3 != nullptr) objectLOD3 = new Object3D(id + ".lod3", modelLOD3);
	levelLOD = 1;
}

void LODObject3D::setEngine(Engine* engine)
{
	this->engine = engine;
}

void LODObject3D::setRenderer(GLRenderer* renderer)
{
}

void LODObject3D::fromTransformations(const Transformations& transformations)
{
	Transformations::fromTransformations(transformations);
	// determine y axis if required
	if (levelTypeLOD2 == LODLEVELTYPE_PLANE || levelTypeLOD3 == LODLEVELTYPE_PLANE) {
		transformationsRotationYIndex = -1;
		for (auto i = 0; i < this->getRotationCount(); i++) {
			if (this->getRotationAxis(i).equals(Rotation::Y_AXIS) == true) {
				transformationsRotationYIndex = i;
				break;
			}
		}
	}
	// delegate to LOD objects
	if (objectLOD1 != nullptr) objectLOD1->fromTransformations(*this);
	if (objectLOD2 != nullptr) objectLOD2->fromTransformations(*this);
	if (objectLOD3 != nullptr) objectLOD3->fromTransformations(*this);
	// update entity
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
	// reset current LOD object
	objectLOD = nullptr;
}

void LODObject3D::update()
{
	Transformations::update();
	// determine y axis if required
	if (levelTypeLOD2 == LODLEVELTYPE_PLANE || levelTypeLOD3 == LODLEVELTYPE_PLANE) {
		transformationsRotationYIndex = -1;
		for (auto i = 0; i < this->getRotationCount(); i++) {
			if (this->getRotationAxis(i).equals(Rotation::Y_AXIS) == true) {
				transformationsRotationYIndex = i;
				break;
			}
		}
	}
	// delegate to LOD objects
	if (objectLOD1 != nullptr) objectLOD1->fromTransformations(*this);
	if (objectLOD2 != nullptr) objectLOD2->fromTransformations(*this);
	if (objectLOD3 != nullptr) objectLOD3->fromTransformations(*this);
	// update entity
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
	// reset current LOD object
	objectLOD = nullptr;
}

void LODObject3D::setEnabled(bool enabled)
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
	// reset current LOD object
	objectLOD = nullptr;
}

bool LODObject3D::isFrustumCulling() {
	return frustumCulling;
}

void LODObject3D::setFrustumCulling(bool frustumCulling) {
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

void LODObject3D::dispose()
{
	// delegate to LOD objects
	if (objectLOD1 != nullptr) objectLOD1->dispose();
	if (objectLOD2 != nullptr) objectLOD2->dispose();
	if (objectLOD3 != nullptr) objectLOD3->dispose();
}

void LODObject3D::initialize()
{
	// delegate to LOD objects
	if (objectLOD1 != nullptr) objectLOD1->initialize();
	if (objectLOD2 != nullptr) objectLOD2->initialize();
	if (objectLOD3 != nullptr) objectLOD3->initialize();
}

void LODObject3D::setDynamicShadowingEnabled(bool dynamicShadowing)
{
	this->dynamicShadowing = dynamicShadowing;
}

void LODObject3D::setPickable(bool pickable)
{
	this->pickable = pickable;
}

Matrix4x4* LODObject3D::getTransformationsMatrix(const string& id)
{
	// TODO: check if this makes sense this way
	return objectLOD1->getTransformationsMatrix(id);
}

const Vector3& LODObject3D::getTranslation() const {
	return Transformations::getTranslation();
}

void LODObject3D::setTranslation(const Vector3& translation) {
	Transformations::setTranslation(translation);
}

const Vector3& LODObject3D::getScale() const {
	return Transformations::getScale();
}

void LODObject3D::setScale(const Vector3& scale) {
	Transformations::setScale(scale);
}

const Vector3& LODObject3D::getPivot() const {
	return Transformations::getPivot();
}

void LODObject3D::setPivot(const Vector3& pivot) {
	Transformations::setPivot(pivot);
}

const int LODObject3D::getRotationCount() const {
	return Transformations::getRotationCount();
}

Rotation& LODObject3D::getRotation(int idx) {
	return Transformations::getRotation(idx);
}

void LODObject3D::addRotation(const Vector3& axis, const float angle) {
	Transformations::addRotation(axis, angle);
}

void LODObject3D::removeRotation(const int idx) {
	Transformations::removeRotation(idx);
}

const Vector3& LODObject3D::getRotationAxis(const int idx) const {
	return Transformations::getRotationAxis(idx);
}

void LODObject3D::setRotationAxis(const int idx, const Vector3& axis) {
	Transformations::setRotationAxis(idx, axis);
}

const float LODObject3D::getRotationAngle(const int idx) const {
	return Transformations::getRotationAngle(idx);
}

void LODObject3D::setRotationAngle(const int idx, const float angle) {
	Transformations::setRotationAngle(idx, angle);
}

const Quaternion& LODObject3D::getRotationsQuaternion() const {
	return Transformations::getRotationsQuaternion();
}
