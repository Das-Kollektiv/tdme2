#include <tdme/engine/ParticleSystemGroup.h>

#include <vector>
#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/ObjectParticleSystem.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/PointsParticleSystem.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/BoundingBox.h>

using std::vector;
using std::string;

using tdme::engine::ParticleSystemGroup;
using tdme::engine::Engine;
using tdme::engine::Object3D;
using tdme::engine::ObjectParticleSystem;
using tdme::engine::Partition;
using tdme::engine::PointsParticleSystem;
using tdme::engine::Transformations;
using tdme::engine::primitives::BoundingBox;

ParticleSystemGroup::ParticleSystemGroup(const string& id, bool autoEmit, bool enableDynamicShadows, const vector<ParticleSystemEntity*>& particleSystems) :
	id(id), autoEmit(autoEmit), enableDynamicShadows(enableDynamicShadows), particleSystems(particleSystems)
{
	this->enabled = true;
	this->pickable = false;
	this->effectColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
	// TODO: put parent entity into a interface
	for (auto particleSystem: particleSystems) {
		auto ops = dynamic_cast<ObjectParticleSystem*>(particleSystem);
		if (ops != nullptr) ops->setParentEntity(this);
		auto pps = dynamic_cast<PointsParticleSystem*>(particleSystem);
		if (pps != nullptr) pps->setParentEntity(this);
	}
}

ParticleSystemGroup::~ParticleSystemGroup() {
	for (auto particleSystem: particleSystems) delete particleSystem;
}

void ParticleSystemGroup::initialize()
{
	for (auto particleSystem: particleSystems) dynamic_cast<Entity*>(particleSystem)->initialize();
}

void ParticleSystemGroup::fromTransformations(const Transformations& transformations)
{
	Transformations::fromTransformations(transformations);
	//
	for (auto particleSystem: particleSystems) dynamic_cast<Entity*>(particleSystem)->fromTransformations(transformations);
	// update bounding box transformed
	boundingBoxTransformed.fromBoundingVolumeWithTransformations(&boundingBox, *this);
	// update object
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void ParticleSystemGroup::update()
{
	Transformations::update();
	//
	for (auto particleSystem: particleSystems) dynamic_cast<Entity*>(particleSystem)->fromTransformations(*this);
	// update bounding box transformed
	boundingBoxTransformed.fromBoundingVolumeWithTransformations(&boundingBox, *this);
	// update object
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void ParticleSystemGroup::setEnabled(bool enabled)
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
	//
	this->enabled = enabled;
}

void ParticleSystemGroup::updateParticles()
{
	// skip if no ps attached
	if (particleSystems.size() == 0) return;

	// update particles
	for (auto particleSystem: particleSystems) particleSystem->updateParticles();

	// compute new bounding box
	boundingBox.fromBoundingVolume(dynamic_cast<Entity*>(particleSystems[0])->getBoundingBox());
	for (auto i = 1; i < particleSystems.size(); i++) {
		auto psAdditionalBoundingBox = dynamic_cast<Entity*>(particleSystems[i])->getBoundingBox();
		for (auto j = 0; j < 3; j++) {
			if (psAdditionalBoundingBox->getMin()[j] < boundingBox.getMin()[j]) boundingBox.getMin()[j] = psAdditionalBoundingBox->getMin()[j];
			if (psAdditionalBoundingBox->getMax()[j] > boundingBox.getMax()[j]) boundingBox.getMax()[j] = psAdditionalBoundingBox->getMax()[j];
		}
	}
	boundingBox.update();

	// update bounding box transformed
	boundingBoxTransformed.fromBoundingVolumeWithTransformations(&boundingBox, *this);

	//
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void ParticleSystemGroup::setFrustumCulling(bool frustumCulling) {
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

void ParticleSystemGroup::setAutoEmit(bool autoEmit) {
	// delegate to sub particle systems
	for (auto particleSystem: particleSystems) particleSystem->setAutoEmit(autoEmit);
	this->autoEmit = autoEmit;
	// delegate change to engine
	if (engine != nullptr) engine->updateEntity(this);
}

void ParticleSystemGroup::dispose()
{
	for (auto particleSystem: particleSystems) dynamic_cast<Entity*>(particleSystem)->dispose();
}

void ParticleSystemGroup::setEngine(Engine* engine)
{
	this->engine = engine;
	for (auto particleSystem: particleSystems) dynamic_cast<Entity*>(particleSystem)->setEngine(engine);
}

void ParticleSystemGroup::setRenderer(GLRenderer* renderer)
{
	for (auto particleSystem: particleSystems) dynamic_cast<Entity*>(particleSystem)->setRenderer(renderer);
}

