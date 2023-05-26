#include <tdme/engine/subsystems/particlesystem/PointsParticleSystemInternal.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/engine/subsystems/particlesystem/ParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemInternal.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPointsPool.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::vector;

using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::particlesystem::ParticleSystemInternal;
using tdme::engine::subsystems::particlesystem::PointsParticleSystemInternal;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::Console;

PointsParticleSystemInternal::PointsParticleSystemInternal(const string& id, ParticleEmitter* emitter, int32_t maxPoints, float pointSize, bool autoEmit, Texture* texture, int32_t textureHorizontalSprites, int32_t textureVerticalSprites, float fps)
{
	this->id = id;
	this->enabled = true;
	// will be activated on emit and auto unactivated if no more active particles
	this->active = false;
	this->emitter = emitter;
	particles.resize(maxPoints);
	this->maxPoints = maxPoints;
	this->effectColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
	this->pickable = false;
	this->pointSize = pointSize;
	this->pointSizeScale = 1.0f;
	this->autoEmit = autoEmit;
	this->particlesToSpawnRemainder = 0.0f;
	this->pointsRenderPool = nullptr;
	this->texture = texture;
	this->textureHorizontalSprites = textureHorizontalSprites;
	this->textureVerticalSprites = textureVerticalSprites;
	this->fps = fps;
	this->pointsRenderPool = new TransparentRenderPointsPool(maxPoints);
	if (texture != nullptr) texture->acquireReference();
	this->texture = texture != nullptr?texture:TextureReader::read("resources/engine/textures", "point.png");
	this->entityTransformMatrix.identity();
}

PointsParticleSystemInternal::~PointsParticleSystemInternal() {
	delete emitter;
	if (pointsRenderPool != nullptr) delete pointsRenderPool;
	if (texture != nullptr) texture->releaseReference();
}

void PointsParticleSystemInternal::initialize() {
}

void PointsParticleSystemInternal::update()
{
	Transform::update();
	//
	auto entityTransform = parentTransform * (*this);
	entityTransformMatrix = entityTransform.getTransformMatrix();
	//
	updateInternal();
}

void PointsParticleSystemInternal::setTransform(const Transform& transform)
{
	Transform::setTransform(transform);
	//
	auto entityTransform = parentTransform * (*this);
	entityTransformMatrix = entityTransform.getTransformMatrix();
	//
	updateInternal();
}

void PointsParticleSystemInternal::updateParticles()
{
	if (enabled == false || active == false)
		return;

	//
	Vector3 center;
	auto& localTransformMatrix = localTransform.getTransformMatrix();
	localTransformMatrix.getTranslation(center);
	center.add(emitter->getCenter());
	//
	Vector3 point;
	Vector3 velocityForTime;
	//
	auto first = false;
	// compute distance from camera
	float distanceFromCamera;
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
		// sprite index
		particle.spriteIndex+= (static_cast<float>(timeDelta) / 1000.0f) * fps;
		// add gravity if our particle have a noticeable mass
		if (particle.mass > Math::EPSILON)
			particle.velocity.sub(Vector3(0.0f, 0.5f * Math::G * static_cast<float>(timeDelta) / 1000.0f, 0.0f));
		// TODO:
		//	maybe take air resistance into account like a huge paper needs more time to fall than a sphere of paper
		//	or heat for smoke or fire, whereas having no mass for those particles works around this problem for now
		// translation
		particle.position.add(velocityForTime.set(particle.velocity).scale(static_cast<float>(timeDelta) / 1000.0f));
		// color
		auto& color = particle.color.getArray();
		auto& colorAdd = particle.colorAdd.getArray();
		color[0] += colorAdd[0] * static_cast<float>(timeDelta);
		color[1] += colorAdd[1] * static_cast<float>(timeDelta);
		color[2] += colorAdd[2] * static_cast<float>(timeDelta);
		color[3] += colorAdd[3] * static_cast<float>(timeDelta);
		//
		activeParticles++;
		// set up bounding box
		point = localTransformMatrix.multiply(particle.position);
		point.add(center);
		//
		if (first == false) {
			boundingBox.getMin().set(point);
			boundingBox.getMax().set(point);
			first = true;
		} else {
			boundingBox.extend(point);
		}
		// transform particle according to its transform
		point = entityTransformMatrix.multiply(point);
		// add to render points pool
		pointsRenderPool->addPoint(point, static_cast<uint16_t>(particle.spriteIndex) % (textureHorizontalSprites * textureVerticalSprites), color, 0, this);
	}
	// auto disable particle system if no more active particles
	if (activeParticles == 0) {
		active = false;
		return;
	}
	// scale a bit up to make picking work better
	boundingBox.update();
	worldBoundingBox.fromBoundingVolumeWithTransformMatrix(&boundingBox, entityTransformMatrix);
	worldBoundingBox.getMin().sub(0.05f + pointSize * pointSizeScale);
	worldBoundingBox.getMax().add(0.05f + pointSize * pointSizeScale);
	worldBoundingBox.update();
}

void PointsParticleSystemInternal::dispose()
{
}

int32_t PointsParticleSystemInternal::emitParticles()
{
	// enable particle system
	active = true;
	// delta time
	auto timeDelta = engine->getTiming()->getDeltaTime();
	// determine particles to spawn
	auto particlesToSpawn = 0;
	{
		if (autoEmit == true) {
			auto particlesToSpawnWithFraction = emitter->getCount() * engine->getTiming()->getDeltaTime() / 1000.0f;
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
	//
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
		auto timeDeltaRnd = static_cast<int64_t>((Math::random() * timeDelta));
		if (particle.mass > Math::EPSILON)
			particle.velocity.sub(Vector3(0.0f, 0.5f * Math::G * static_cast<float>(timeDeltaRnd) / 1000.0f, 0.0f));
		particle.position.add(velocityForTime.set(particle.velocity).scale(timeDeltaRnd / 1000.0f));
		//
		particlesSpawned++;
		// finished?
		if (particlesSpawned == particlesToSpawn) break;

	}
	return particlesSpawned;
}

TransparentRenderPointsPool* PointsParticleSystemInternal::getRenderPointsPool()
{
	return pointsRenderPool;
}
