#include <tdme/engine/Decal.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/Transform.h>

using std::string;

using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::Decal;
using tdme::engine::Engine;
using tdme::engine::Partition;
using tdme::engine::Transform;

Decal::Decal(const string& id, OrientedBoundingBox* obb, Texture* texture):
	DecalInternal(id, obb, texture)
{
}

void Decal::setEngine(Engine* engine) {
	if (this->engine != nullptr) this->engine->deregisterEntity(this);
	this->engine = engine;
	if (engine != nullptr) engine->registerEntity(this);
	DecalInternal::setEngine(engine);
}

void Decal::setTransform(const Transform& transform)
{
	DecalInternal::setTransform(transform);
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
	auto entityTransform = parentTransform * (*this);
	transformMatrix = entityTransform.getTransformMatrix();
}

void Decal::update()
{
	DecalInternal::update();
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
	auto entityTransform = parentTransform * (*this);
	transformMatrix = entityTransform.getTransformMatrix();
}

void Decal::setEnabled(bool enabled)
{
	// return if enable state has not changed
	if (this->enabled == enabled) return;

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
	// call parent class::setEnabled()
	DecalInternal::setEnabled(enabled);
}

void Decal::setFrustumCulling(bool frustumCulling) {
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
	if (engine != nullptr) engine->updateEntityRegistration(this);
}

