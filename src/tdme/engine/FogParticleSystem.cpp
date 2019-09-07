#include <tdme/engine/FogParticleSystem.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>

using std::string;

using tdme::engine::FogParticleSystem;
using tdme::engine::Engine;
using tdme::engine::Partition;
using tdme::engine::Transformations;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::primitives::BoundingBox;

FogParticleSystem::FogParticleSystem(const string& id, ParticleEmitter* emitter, int32_t maxPoints, float pointSize, Texture* texture) :
	FogParticleSystemInternal(id, emitter, maxPoints, pointSize, texture)
{
}

void FogParticleSystem::initialize()
{
	FogParticleSystemInternal::initialize();
}

void FogParticleSystem::fromTransformations(const Transformations& transformations)
{
	FogParticleSystemInternal::fromTransformations(transformations);
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void FogParticleSystem::update()
{
	FogParticleSystemInternal::update();
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void FogParticleSystem::setEnabled(bool enabled)
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
	FogParticleSystemInternal::setEnabled(enabled);
}

void FogParticleSystem::updateParticles()
{
	FogParticleSystemInternal::updateParticles();
	if (parentEntity == nullptr && frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

bool FogParticleSystem::isFrustumCulling() {
	return frustumCulling;
}

void FogParticleSystem::setFrustumCulling(bool frustumCulling) {
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
	if (parentEntity == nullptr && engine != nullptr) engine->updateEntity(this);
}

void FogParticleSystem::setAutoEmit(bool autoEmit) {
	// delegate to base class
	FogParticleSystemInternal::setAutoEmit(autoEmit);
	// delegate change to engine
	if (parentEntity == nullptr && engine != nullptr) engine->updateEntity(this);
}

void FogParticleSystem::dispose()
{
	FogParticleSystemInternal::dispose();
}

void FogParticleSystem::setEngine(Engine* engine)
{
	FogParticleSystemInternal::setEngine(engine);
}

void FogParticleSystem::setRenderer(Renderer* renderer)
{
	FogParticleSystemInternal::setRenderer(renderer);
}

