// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/ObjectParticleSystemEntityInternal.java
#include <tdme/engine/subsystems/particlesystem/ObjectParticleSystemEntityInternal.h>

#include <algorithm>
#include <string>
#include <vector>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Arrays.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/object/Object3DBase.h>
#include <tdme/engine/subsystems/object/Object3DInternal.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/engine/subsystems/particlesystem/ParticleEmitter.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using std::vector;
using std::remove;
using std::wstring;
using std::to_wstring;

using tdme::engine::subsystems::particlesystem::ObjectParticleSystemEntityInternal;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Object3D;
using tdme::engine::Timing;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::object::Object3DBase;
using tdme::engine::subsystems::object::Object3DInternal;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::math::MathTools;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

ObjectParticleSystemEntityInternal::ObjectParticleSystemEntityInternal(const wstring& id, Model* model, Vector3* scale, bool autoEmit, bool enableDynamicShadows, int32_t maxCount, ParticleEmitter* emitter)
{
	this->id = id;
	this->enabled = true;
	this->model = model;
	this->autoEmit = autoEmit;
	this->enableDynamicShadows = enableDynamicShadows;
	particles.resize(maxCount);
	for (auto i = 0; i < particles.size(); i++) {
		particles[i] = new Particle();
	}
	objects.resize(maxCount);
	for (auto i = 0; i < objects.size(); i++) {
		objects[i] = new Object3D(
			L"tdme.opse." +
				id +
				L":" +
				to_wstring(i),
			model
		);
		objects[i]->setEnabled(false);
		objects[i]->getScale()->set(scale);
		objects[i]->setDynamicShadowingEnabled(enableDynamicShadows);
		objects[i]->setPickable(false);
	}
	this->boundingBox = new BoundingBox();
	this->boundingBoxTransformed = new BoundingBox();
	this->inverseTransformation = new Transformations();
	this->emitter = emitter;
	this->effectColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
	this->pickable = false;
	this->particlesToSpawnRemainder = 0.0f;
}

const wstring& ObjectParticleSystemEntityInternal::getId()
{
	return id;
}

void ObjectParticleSystemEntityInternal::setEngine(Engine* engine)
{
	this->engine = engine;
}

void ObjectParticleSystemEntityInternal::setRenderer(GLRenderer* renderer)
{
}

bool ObjectParticleSystemEntityInternal::isEnabled()
{
	return enabled;
}

bool ObjectParticleSystemEntityInternal::isActive()
{
	return enabledObjects.size() > 0;
}

void ObjectParticleSystemEntityInternal::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

Color4* ObjectParticleSystemEntityInternal::getEffectColorMul()
{
	return &effectColorMul;
}

Color4* ObjectParticleSystemEntityInternal::getEffectColorAdd()
{
	return &effectColorAdd;
}

bool ObjectParticleSystemEntityInternal::isPickable()
{
	return pickable;
}

void ObjectParticleSystemEntityInternal::setPickable(bool pickable)
{
	this->pickable = pickable;
}

bool ObjectParticleSystemEntityInternal::isAutoEmit()
{
	return autoEmit;
}

void ObjectParticleSystemEntityInternal::setAutoEmit(bool autoEmit)
{
	this->autoEmit = autoEmit;
}

bool ObjectParticleSystemEntityInternal::isDynamicShadowingEnabled()
{
	return enableDynamicShadows;
}

void ObjectParticleSystemEntityInternal::setDynamicShadowingEnabled(bool dynamicShadowing)
{
	enableDynamicShadows = dynamicShadowing;
	for (auto i = 0; i < objects.size(); i++) {
		objects[i]->setDynamicShadowingEnabled(enableDynamicShadows);
	}
}

void ObjectParticleSystemEntityInternal::update()
{
	Transformations::update();
	emitter->fromTransformations(this);
	inverseTransformation->getTransformationsMatrix()->set(this->getTransformationsMatrix())->invert();
}

void ObjectParticleSystemEntityInternal::fromTransformations(Transformations* transformations)
{
	Transformations::fromTransformations(transformations);
	emitter->fromTransformations(transformations);
	inverseTransformation->getTransformationsMatrix()->set(this->getTransformationsMatrix())->invert();
}

ParticleEmitter* ObjectParticleSystemEntityInternal::getParticleEmitter()
{
	return emitter;
}

int32_t ObjectParticleSystemEntityInternal::emitParticles()
{
	auto particlesToSpawn = emitter->getCount() * engine->getTiming()->getDeltaTime() / 1000.0f;
	auto particlesToSpawnInteger = 0;
	if (autoEmit == true) {
		particlesToSpawnInteger = static_cast< int32_t >(particlesToSpawn);
		particlesToSpawnRemainder += particlesToSpawn - particlesToSpawnInteger;
		if (particlesToSpawnRemainder > 1.0f) {
			particlesToSpawn += 1.0f;
			particlesToSpawnInteger++;
			particlesToSpawnRemainder -= 1.0f;
		}
	} else {
		particlesToSpawnInteger = emitter->getCount();
	}
	if (particlesToSpawnInteger == 0)
		return 0;

	auto particlesSpawned = 0;
	for (auto i = 0; i < particles.size(); i++) {
		auto particle = particles[i];
		if (particle->active == true)
			continue;

		emitter->emit(particle);
		auto object = objects[i];
		object->getTranslation()->set(particle->position);
		object->update();
		object->setEnabled(true);
		object->getEffectColorAdd()->set(&effectColorAdd);
		object->getEffectColorMul()->set(&effectColorMul);
		enabledObjects.push_back(object);
		particlesSpawned++;
		if (particlesSpawned == particlesToSpawnInteger)
			break;

	}
	return particlesSpawned;
}

void ObjectParticleSystemEntityInternal::updateParticles()
{
	Vector3 velocityForTime;
	auto first = true;
	auto bbMinXYZ = boundingBoxTransformed->getMin()->getArray();
	auto bbMaxXYZ = boundingBoxTransformed->getMax()->getArray();
	auto timeDelta = engine->getTiming()->getDeltaTime();
	for (auto i = 0; i < particles.size(); i++) {
		auto particle = particles[i];
		if (particle->active == false)
			continue;

		auto object = objects[i];
		particle->lifeTimeCurrent += timeDelta;
		if (particle->lifeTimeCurrent >= particle->lifeTimeMax) {
			particle->active = false;
			object->setEnabled(false);
			enabledObjects.erase(remove(enabledObjects.begin(), enabledObjects.end(), object), enabledObjects.end());
			continue;
		}
		if (particle->mass > MathTools::EPSILON)
			particle->velocity->subY(0.5f * MathTools::g * static_cast< float >(timeDelta) / 1000.0f);

		object->getEffectColorAdd()->set(&effectColorAdd);
		object->getEffectColorMul()->set(&effectColorMul);
		object->getTranslation()->add(velocityForTime.set(particle->velocity)->scale(static_cast< float >(timeDelta) / 1000.0f));
		object->update();
		if (first == true) {
			boundingBoxTransformed->getMin()->set(object->getBoundingBoxTransformed()->getMin());
			boundingBoxTransformed->getMax()->set(object->getBoundingBoxTransformed()->getMax());
			first = false;
		} else {
			auto objBbMinXYZ = object->getBoundingBoxTransformed()->getMin()->getArray();
			auto objBbMaxXYZ = object->getBoundingBoxTransformed()->getMax()->getArray();
			if ((*objBbMinXYZ)[0] < (*bbMinXYZ)[0]) (*bbMinXYZ)[0] = (*objBbMinXYZ)[0];
			if ((*objBbMinXYZ)[1] < (*bbMinXYZ)[1]) (*bbMinXYZ)[1] = (*objBbMinXYZ)[1];
			if ((*objBbMinXYZ)[2] < (*bbMinXYZ)[2]) (*bbMinXYZ)[2] = (*objBbMinXYZ)[2];
			if ((*objBbMaxXYZ)[0] > (*bbMaxXYZ)[0]) (*bbMaxXYZ)[0] = (*objBbMaxXYZ)[0];
			if ((*objBbMaxXYZ)[1] > (*bbMaxXYZ)[1]) (*bbMaxXYZ)[1] = (*objBbMaxXYZ)[1];
			if ((*objBbMaxXYZ)[2] > (*bbMaxXYZ)[2]) (*bbMaxXYZ)[2] = (*objBbMaxXYZ)[2];
		}
	}
	boundingBoxTransformed->update();
	boundingBox->fromBoundingVolumeWithTransformations(boundingBoxTransformed, inverseTransformation);
}

void ObjectParticleSystemEntityInternal::dispose()
{
	for (auto i = 0; i < objects.size(); i++) {
		objects[i]->dispose();
	}
}

