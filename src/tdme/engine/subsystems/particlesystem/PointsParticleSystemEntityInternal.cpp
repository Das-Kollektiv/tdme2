#include <tdme/engine/subsystems/particlesystem/PointsParticleSystemEntityInternal.h>

#include <string>
#include <vector>

#include <tdme/math/Math.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureLoader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPointsPool.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/engine/subsystems/particlesystem/ParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemEntity.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::string;
using std::vector;

using tdme::engine::subsystems::particlesystem::PointsParticleSystemEntityInternal;
using tdme::math::Math;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Partition;
using tdme::engine::Timing;
using tdme::engine::Transformations;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureLoader;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::particlesystem::ParticleSystemEntity;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

PointsParticleSystemEntityInternal::PointsParticleSystemEntityInternal(const string& id, bool doCollisionTests, ParticleEmitter* emitter, int32_t maxPoints, float pointSize, bool autoEmit, Texture* texture)
{
	this->id = id;
	this->enabled = true;
	this->doCollisionTests = doCollisionTests;
	// will be activated on emit and auto unactivated if no more active particles
	this->active = false;
	this->emitter = emitter;
	particles.resize(maxPoints);
	this->maxPoints = maxPoints;
	boundingBox = new BoundingBox();
	boundingBoxTransformed = new BoundingBox();
	this->effectColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
	this->pickable = false;
	this->pointSize = pointSize;
	this->autoEmit = autoEmit;
	this->particlesToSpawnRemainder = 0.0f;
	this->pointsRenderPool = nullptr;
	this->texture = texture;
	this->textureId = this->texture == nullptr?engine->getTextureManager()->addTexture(this->texture = TextureLoader::loadTexture("resources/textures", "point.png")):engine->getTextureManager()->addTexture(this->texture);
}

PointsParticleSystemEntityInternal::~PointsParticleSystemEntityInternal() {
	delete emitter;
	delete boundingBox;
	delete boundingBoxTransformed;
	if (pointsRenderPool != nullptr) delete pointsRenderPool;
	engine->getTextureManager()->removeTexture(texture->getId());
}

const string& PointsParticleSystemEntityInternal::getId()
{
	return id;
}

void PointsParticleSystemEntityInternal::setRenderer(GLRenderer* renderer)
{
	this->renderer = renderer;
	this->pointsRenderPool = new TransparentRenderPointsPool(maxPoints);
}

void PointsParticleSystemEntityInternal::setEngine(Engine* engine)
{
	this->engine = engine;
}

bool PointsParticleSystemEntityInternal::isEnabled()
{
	return enabled;
}

bool PointsParticleSystemEntityInternal::isActive()
{
	return active;
}

void PointsParticleSystemEntityInternal::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

const Color4& PointsParticleSystemEntityInternal::getEffectColorMul() const
{
	return effectColorMul;
}

void PointsParticleSystemEntityInternal::setEffectColorMul(const Color4& effectColorMul)
{
	this->effectColorMul = effectColorMul;
}

const Color4& PointsParticleSystemEntityInternal::getEffectColorAdd() const
{
	return effectColorAdd;
}

void PointsParticleSystemEntityInternal::setEffectColorAdd(const Color4& effectColorAdd)
{
	this->effectColorAdd = effectColorAdd;
}

bool PointsParticleSystemEntityInternal::isPickable()
{
	return pickable;
}

void PointsParticleSystemEntityInternal::setPickable(bool pickable)
{
	this->pickable = pickable;
}

bool PointsParticleSystemEntityInternal::isAutoEmit()
{
	return autoEmit;
}

void PointsParticleSystemEntityInternal::setAutoEmit(bool autoEmit)
{
	this->autoEmit = autoEmit;
}

bool PointsParticleSystemEntityInternal::isDynamicShadowingEnabled()
{
	return false;
}

void PointsParticleSystemEntityInternal::setDynamicShadowingEnabled(bool dynamicShadowing)
{
}

float PointsParticleSystemEntityInternal::getPointSize() {
	return pointSize;
}

int32_t PointsParticleSystemEntityInternal::getTextureId() {
	return textureId;
}

void PointsParticleSystemEntityInternal::update()
{
	Transformations::update();
	emitter->fromTransformations(*this);
	inverseTransformation.fromTransformations(*this);
	inverseTransformation.invert();
}

void PointsParticleSystemEntityInternal::fromTransformations(const Transformations& transformations)
{
	Transformations::fromTransformations(transformations);
	emitter->fromTransformations(transformations);
	inverseTransformation.fromTransformations(transformations);
	inverseTransformation.invert();
}

void PointsParticleSystemEntityInternal::updateParticles()
{
	if (enabled == false || active == false)
		return;

	Vector3 velocityForTime;
	Vector3 point;
	// bounding box transformed min, max xyz
	auto& bbMinXYZ = boundingBoxTransformed->getMin().getArray();
	auto& bbMaxXYZ = boundingBoxTransformed->getMax().getArray();
	//
	auto haveBoundingBox = false;
	// compute distance from camera
	float distanceFromCamera;
	auto modelViewMatrix = renderer->getModelViewMatrix();
	// process particles
	pointsRenderPool->reset();
	auto activeParticles = 0;
	auto timeDelta = engine->getTiming()->getDeltaTime();
	for (auto i = 0; i < particles.size(); i++) {
		auto& particle = particles[i];
		if (particle.active == false)
			continue;

		// life time
		particle.lifeTimeCurrent += timeDelta;
		// crop to max life time
		if (particle.lifeTimeCurrent >= particle.lifeTimeMax) {
			particle.active = false;
			continue;
		}
		// add gravity if our particle have a noticeable mass
		if (particle.mass > Math::EPSILON)
			particle.velocity.subY(0.5f * Math::g * static_cast< float >(timeDelta) / 1000.0f);
		// TODO:
		//	maybe take air resistance into account like a huge paper needs more time to fall than a sphere of paper
		//	or heat for smoke or fire, whereas having no mass for those particles works around this problem for now
		// translation
		particle.position.add(velocityForTime.set(particle.velocity).scale(static_cast< float >(timeDelta) / 1000.0f));
		// color
		auto& color = particle.color.getArray();
		auto& colorAdd = particle.colorAdd.getArray();
		color[0] += colorAdd[0] * static_cast< float >(timeDelta);
		color[1] += colorAdd[1] * static_cast< float >(timeDelta);
		color[2] += colorAdd[2] * static_cast< float >(timeDelta);
		color[3] += colorAdd[3] * static_cast< float >(timeDelta);
		// transform particle position to camera space
		modelViewMatrix.multiply(particle.position, point);
		/*
		// TODO: remove me completely
		// check for collision
		if (doCollisionTests == true) {
			for (auto _i = engine->getPartition()->getObjectsNearTo(particle.position)->iterator(); _i->hasNext(); ) {
				Entity* entity = dynamic_cast< Entity* >(_i->next());
				{
					// skip on our self
					if (static_cast< void* >(entity) == static_cast< void* >(this))
						continue;
					// skip on other particle systems
					if (dynamic_cast< ParticleSystemEntity* >(entity) != nullptr)
						continue;
					// do we have a collision?
					if (entity->getBoundingBoxTransformed()->containsPoint(particle.position)) {
						particle.active = false;
						continue;
					}
				}
			}
		}
		*/
		//
		activeParticles++;
		// compute distance from camera
		distanceFromCamera = -point.getZ();
		// set up bounding box
		auto& positionXYZ = particle.position.getArray();
		if (haveBoundingBox == false) {
			bbMinXYZ = positionXYZ;
			bbMaxXYZ = positionXYZ;
			haveBoundingBox = true;
		} else {
			if (positionXYZ[0] < bbMinXYZ[0]) bbMinXYZ[0] = positionXYZ[0];
			if (positionXYZ[1] < bbMinXYZ[1]) bbMinXYZ[1] = positionXYZ[1];
			if (positionXYZ[2] < bbMinXYZ[2]) bbMinXYZ[2] = positionXYZ[2];
			if (positionXYZ[0] > bbMaxXYZ[0]) bbMaxXYZ[0] = positionXYZ[0];
			if (positionXYZ[1] > bbMaxXYZ[1]) bbMaxXYZ[1] = positionXYZ[1];
			if (positionXYZ[2] > bbMaxXYZ[2]) bbMaxXYZ[2] = positionXYZ[2];
		}
		//
		pointsRenderPool->addPoint(point, particle.color, distanceFromCamera);
	}
	// auto disable particle system if no more active particles
	if (activeParticles == 0) {
		active = false;
		return;
	}
	// scale a bit up to make picking work better
	boundingBoxTransformed->getMin().sub(0.05f);
	boundingBoxTransformed->getMax().add(0.05f);
	// compute bounding boxes
	boundingBoxTransformed->update();
	boundingBox->fromBoundingVolumeWithTransformations(boundingBoxTransformed, inverseTransformation);
}

void PointsParticleSystemEntityInternal::dispose()
{
}

ParticleEmitter* PointsParticleSystemEntityInternal::getParticleEmitter()
{
	return emitter;
}

int32_t PointsParticleSystemEntityInternal::emitParticles()
{
	// enable particle system
	active = true;
	// delta time
	auto timeDelta = engine->getTiming()->getDeltaTime();
	// determine particles to spawn
	auto particlesToSpawnInteger = 0;
	if (autoEmit == true) {
		auto particlesToSpawn = emitter->getCount() * engine->getTiming()->getDeltaTime() / 1000.0f;
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
	// skip if nothing to spawn
	if (particlesToSpawnInteger == 0)
		return 0;

	Vector3 velocityForTime;
	// spawn
	auto particlesSpawned = 0;
	for (auto i = 0; i < particles.size(); i++) {
		auto& particle = particles[i];
		if (particle.active == true)
			continue;
		// emit particle
		emitter->emit(&particle);
		// add gravity if our particle have a noticable mass, add translation
		// add some movement with a min of 0 time delta and a max of engine time delta
		auto timeDeltaRnd = static_cast< int64_t >((Math::random() * timeDelta));
		if (particle.mass > Math::EPSILON)
			particle.velocity.subY(0.5f * Math::g * static_cast< float >(timeDeltaRnd) / 1000.0f);
		particle.position.add(velocityForTime.set(particle.velocity).scale(timeDeltaRnd / 1000.0f));
		//
		particlesSpawned++;
		if (particlesSpawned == particlesToSpawnInteger)
			break;

	}
	return particlesSpawned;
}

TransparentRenderPointsPool* PointsParticleSystemEntityInternal::getRenderPointsPool()
{
	return pointsRenderPool;
}
