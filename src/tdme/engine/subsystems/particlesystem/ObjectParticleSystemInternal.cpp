#include <tdme/engine/subsystems/particlesystem/ObjectParticleSystemInternal.h>

#include <algorithm>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/engine/subsystems/particlesystem/ParticleEmitter.h>
#include <tdme/engine/subsystems/rendering/ObjectBase.h>
#include <tdme/engine/subsystems/rendering/ObjectInternal.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::remove;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::particlesystem::ObjectParticleSystemInternal;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::rendering::ObjectBase;
using tdme::engine::subsystems::rendering::ObjectInternal;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Object;
using tdme::engine::Timing;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

ObjectParticleSystemInternal::ObjectParticleSystemInternal(const string& id, Model* model, const Vector3& scale, bool autoEmit, bool contributesShadows, bool receivesShadows, int32_t maxCount, ParticleEmitter* emitter)
{
	this->id = id;
	this->enabled = true;
	this->model = model;
	this->objectScale = scale;
	this->autoEmit = autoEmit;
	this->contributesShadows = contributesShadows;
	this->receivesShadows = receivesShadows;
	particles.resize(maxCount);
	objects.resize(maxCount);
	for (auto i = 0; i < objects.size(); i++) {
		objects[i] = new Object(
			"tdme.opse." +
				id +
				":" +
				to_string(i),
			model
		);
		objects[i]->setEnabled(false);
		objects[i]->setScale(objectScale);
		objects[i]->setContributesShadows(contributesShadows);
		objects[i]->setReceivesShadows(receivesShadows);
		objects[i]->setPickable(false);
	}
	this->boundingBox = new BoundingBox();
	this->worldBoundingBox = new BoundingBox();
	this->emitter = emitter;
	this->effectColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
	this->pickable = false;
	this->particlesToSpawnRemainder = 0.0f;
}

ObjectParticleSystemInternal::~ObjectParticleSystemInternal() {
	delete emitter;
	for (auto i = 0; i < objects.size(); i++) delete objects[i];
}

const string& ObjectParticleSystemInternal::getId()
{
	return id;
}

void ObjectParticleSystemInternal::setEngine(Engine* engine)
{
	this->engine = engine;
	for (auto i = 0; i < objects.size(); i++) {
		objects[i]->setEngine(engine);
	}
}

void ObjectParticleSystemInternal::setRenderer(Renderer* renderer)
{
	this->renderer = renderer;
	for (auto i = 0; i < objects.size(); i++) {
		objects[i]->setRenderer(renderer);
	}
}

void ObjectParticleSystemInternal::update()
{
	Transform::update();
	//
	auto entityTransform = parentTransform * (*this);
	entityTransformMatrix = entityTransform.getTransformMatrix();
	//
	updateInternal();
}

void ObjectParticleSystemInternal::setTransform(const Transform& transform)
{
	Transform::setTransform(transform);
	//
	auto entityTransform = parentTransform * (*this);
	entityTransformMatrix = entityTransform.getTransformMatrix();
	//
	updateInternal();
}

int32_t ObjectParticleSystemInternal::emitParticles()
{
	// particles to spawn
	auto particlesToSpawn = 0;
	{
		auto particlesToSpawnWithFraction = emitter->getCount() * engine->getTiming()->getDeltaTime() / 1000.0f;
		if (autoEmit == true) {
			particlesToSpawn = static_cast<int32_t>(particlesToSpawnWithFraction);
			particlesToSpawnRemainder += particlesToSpawnWithFraction - particlesToSpawn;
			if (particlesToSpawnRemainder > 1.0f) {
				particlesToSpawn++;
				particlesToSpawnRemainder -= 1.0f;
			}
		} else {
			particlesToSpawn = emitter->getCount();
		}
	}
	// skip if nothing to spawn
	if (particlesToSpawn == 0) return 0;
	// spawn
	auto particlesSpawned = 0;
	for (auto i = 0; i < particles.size(); i++) {
		auto& particle = particles[i];
		if (particle.active == true) continue;
		// emit particle
		emitter->emit(&particle);
		// enable object
		auto object = objects[i];
		object->setTranslation(particle.position);
		object->update();
		object->setEnabled(true);
		object->setEffectColorAdd(effectColorAdd);
		object->setEffectColorMul(effectColorMul);
		enabledObjects.push_back(object);
		// all particles spawned?
		particlesSpawned++;
		if (particlesSpawned == particlesToSpawn) break;
	}
	// done
	return particlesSpawned;
}

void ObjectParticleSystemInternal::updateParticles()
{
	//
	Vector3 center;
	auto& localTransformMatrix = localTransform.getTransformMatrix();
	localTransformMatrix.getTranslation(center);
	center.add(emitter->getCenter());
	//
	Vector3 point;
	Vector3 velocityForTime;
	auto first = true;
	auto timeDelta = engine->getTiming()->getDeltaTime();
	for (auto i = 0; i < particles.size(); i++) {
		auto& particle = particles[i];
		if (particle.active == false)
			continue;

		auto object = objects[i];
		// life time
		particle.lifeTimeCurrent += timeDelta;
		if (particle.lifeTimeCurrent >= particle.lifeTimeMax) {
			particle.active = false;
			object->setEnabled(false);
			enabledObjects.erase(remove(enabledObjects.begin(), enabledObjects.end(), object), enabledObjects.end());
			continue;
		}
		// add gravity if our particle have a noticable mass
		if (particle.mass > Math::EPSILON)
			particle.velocity.sub(Vector3(0.0f, 0.5f * Math::G * static_cast<float>(timeDelta) / 1000.0f, 0.0f));
		// TODO:
		//	maybe take air resistance into account like a huge paper needs more time to fall than a sphere of paper
		//	or heat for smoke or fire, whereas having no mass for those particles works around this problem for now
		// translation
		particle.position.add(velocityForTime.set(particle.velocity).scale(static_cast<float>(timeDelta) / 1000.0f));
		// update up effect colors
		object->setEffectColorAdd(effectColorAdd);
		object->setEffectColorMul(effectColorMul);
		// translation
		point = localTransformMatrix.multiply(particle.position);
		point.add(center);
		// transform particle according to its transform
		point = entityTransformMatrix.multiply(point);
		// apply to object
		object->setTranslation(point);
		object->update();
		if (first == true) {
			worldBoundingBox = *object->getWorldBoundingBox();
			first = false;
		} else {
			worldBoundingBox.extend(object->getWorldBoundingBox());
		}
	}
	// compute bounding boxes
	worldBoundingBox.update();
	boundingBox.fromBoundingVolumeWithTransformMatrix(&worldBoundingBox, inverseTransformMatrix);
}

void ObjectParticleSystemInternal::dispose()
{
	for (auto i = 0; i < objects.size(); i++) {
		objects[i]->dispose();
	}
}

