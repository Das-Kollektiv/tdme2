#include <tdme/engine/SkinnedObject3DRenderGroup.h>

#include <string>
#include <vector>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/rendering/Object3DAnimation.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Matrix4x4.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::SkinnedObject3DRenderGroup;
using tdme::engine::Engine;
using tdme::engine::LODObject3D;
using tdme::engine::Object3D;
using tdme::engine::Partition;
using tdme::engine::Transformations;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::rendering::Object3DAnimation;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Matrix4x4;

SkinnedObject3DRenderGroup::SkinnedObject3DRenderGroup(
	const string& id,
	Model* model,
	int objectCount
):
	id(id),
	objectCount(objectCount)
{
	setModel(model);
	objectTransformations.resize(objectCount);
	objectAnimations.resize(objectCount);
	for (auto i = 0; i < objectCount; i++) {
		objectAnimations[i] = new Object3DAnimation(model, Engine::animationProcessingTarget);
	} 
}

SkinnedObject3DRenderGroup::~SkinnedObject3DRenderGroup() {
	delete object;
}

void SkinnedObject3DRenderGroup::setModel(Model* model) {
	// dispose old object and combined model
	if (object != nullptr) {
		object->dispose();
		delete object;
	}

	// set up new model
	this->model = model;

	//
	object = new Object3D(id, model, objectCount);
}

void SkinnedObject3DRenderGroup::updateBoundingBox() {
	BoundingBox objectBoundingBox;
	boundingBox.fromBoundingVolumeWithTransformations(model->getBoundingBox(), objectTransformations[0]);
	for (auto i = 1; i < objectCount; i++) {
		objectBoundingBox.fromBoundingVolumeWithTransformations(model->getBoundingBox(), objectTransformations[i]);
		boundingBox.extend(&objectBoundingBox);
	}
	boundingBoxTransformed.fromBoundingVolumeWithTransformations(&boundingBox, *this);
}

void SkinnedObject3DRenderGroup::updateRenderGroup() {
	updateBoundingBox();
}

void SkinnedObject3DRenderGroup::fromTransformations(const Transformations& transformations)
{
	Transformations::fromTransformations(transformations);
	// update bounding box transformed
	boundingBoxTransformed.fromBoundingVolumeWithTransformations(&boundingBox, *this);
	// update object
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && object->isEnabled() == true) engine->partition->updateEntity(this);
}

void SkinnedObject3DRenderGroup::update()
{
	Transformations::update();
	// update bounding box transformed
	boundingBoxTransformed.fromBoundingVolumeWithTransformations(&boundingBox, *this);
	// update object
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && object->isEnabled() == true) engine->partition->updateEntity(this);
}

void SkinnedObject3DRenderGroup::setEnabled(bool enabled)
{
	// return if enable state has not changed
	if (object->isEnabled() == enabled) return;

	// frustum if root entity
	if (parentEntity == nullptr) {
		// frustum culling enabled?
		if (frustumCulling == true) {
			// yeo, add or remove from partition
			if (enabled == true) {
				if (engine != nullptr) engine->partition->addEntity(this);
			} else {
				if (engine != nullptr) engine->partition->removeEntity(this);
			}
		}
	}

	//
	object->setEnabled(enabled);
}

bool SkinnedObject3DRenderGroup::isFrustumCulling() {
	return frustumCulling;
}

void SkinnedObject3DRenderGroup::setFrustumCulling(bool frustumCulling) {
	// check if enabled and engine attached
	if (object->isEnabled() == true && engine != nullptr) {
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
	if (engine != nullptr) engine->registerEntity(this);
}

void SkinnedObject3DRenderGroup::dispose()
{
	object->dispose();
}

void SkinnedObject3DRenderGroup::initialize()
{
	object->initialize();
}

