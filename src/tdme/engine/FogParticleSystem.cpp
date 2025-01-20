#include <tdme/engine/FogParticleSystem.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/Transform.h>

using std::string;

using tdme::engine::primitives::BoundingBox;
using tdme::engine::Engine;
using tdme::engine::FogParticleSystem;
using tdme::engine::Partition;
using tdme::engine::Texture;
using tdme::engine::Transform;

FogParticleSystem::FogParticleSystem(const string& id, ParticleEmitter* emitter, int32_t maxPoints, float pointSize, Texture* texture, int32_t textureHorizontalSprites, int32_t textureVerticalSprites, float fps):
	FogParticleSystemInternal(id, emitter, maxPoints, pointSize, texture, textureHorizontalSprites, textureVerticalSprites, fps)
{
}

void FogParticleSystem::initialize()
{
	FogParticleSystemInternal::initialize();
}

void FogParticleSystem::setTransform(const Transform& transform)
{
	FogParticleSystemInternal::setTransform(transform);
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
	if (engine != nullptr) engine->updateEntityRegistration(this);
}

void FogParticleSystem::setAutoEmit(bool autoEmit) {
	if (this->isAutoEmit() == autoEmit) return;
	// delegate to base class
	FogParticleSystemInternal::setAutoEmit(autoEmit);
	// delegate change to engine
	if (engine != nullptr) engine->updateEntityRegistration(this);
}

void FogParticleSystem::dispose()
{
	FogParticleSystemInternal::dispose();
}

void FogParticleSystem::setEngine(Engine* engine)
{
	if (this->engine != nullptr) this->engine->deregisterEntity(this);
	this->engine = engine;
	if (engine != nullptr) engine->registerEntity(this);
	FogParticleSystemInternal::setEngine(engine);
}

void FogParticleSystem::setRenderer(RendererBackend* rendererBackend)
{
	FogParticleSystemInternal::setRenderer(rendererBackend);
}

