#include <tdme/engine/subsystems/particlesystem/FogParticleSystemInternal.h>

#include <memory>
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

using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::particlesystem::FogParticleSystemInternal;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::particlesystem::ParticleSystemInternal;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

FogParticleSystemInternal::FogParticleSystemInternal(const string& id, ParticleEmitter* emitter, int32_t maxPoints, float pointSize, Texture* texture, int32_t textureHorizontalSprites, int32_t textureVerticalSprites, float fps)
{
	this->id = id;
	this->enabled = true;
	// will be activated on emit and auto unactivated if no more active particles
	this->active = false;
	this->emitter = unique_ptr<ParticleEmitter>(emitter);
	particles.resize(maxPoints);
	this->maxPoints = maxPoints;
	this->effectColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
	this->pickable = false;
	this->pointSize = pointSize;
	this->pointSizeScale = 1.0f;
	this->pointsRenderPool = nullptr;
	this->textureHorizontalSprites = textureHorizontalSprites;
	this->textureVerticalSprites = textureVerticalSprites;
	this->fps = fps;
	this->texture = texture != nullptr?texture:TextureReader::read("resources/engine/textures", "point.png");
	this->entityTransformMatrix.identity();
}

FogParticleSystemInternal::~FogParticleSystemInternal() {
	if (texture != nullptr) texture->releaseReference();
}

void FogParticleSystemInternal::initialize() {
	this->pointsRenderPool = make_unique<TransparentRenderPointsPool>(maxPoints);

	//
	Vector3 center;
	const auto& localTransformMatrix = localTransform.getTransformMatrix();
	localTransformMatrix.getTranslation(center);
	center.add(emitter->getCenter());

	//
	Vector3 point;

	// enable particle system
	active = true;
	// emit particles
	for (auto i = 0; i < particles.size(); i++) {
		// emit particle
		emitter->emit(&particles[i]);
	}

	//
	auto first = false;
	// compute distance from camera
	float distanceFromCamera;
	// process particles
	pointsRenderPool->reset();
	//
	auto activeParticles = 0;
	for (auto i = 0; i < particles.size(); i++) {
		auto& particle = particles[i];
		if (particle.active == false) continue;

		//
		activeParticles++;

		// color
		int64_t timeRnd = (int64_t)(Math::random() * (float)particle.lifeTimeMax);
		auto& color = particle.color;
		const auto& colorAdd = particle.colorAdd;
		color[0] += colorAdd[0] * static_cast<float>(timeRnd);
		color[1] += colorAdd[1] * static_cast<float>(timeRnd);
		color[2] += colorAdd[2] * static_cast<float>(timeRnd);
		color[3] += colorAdd[3] * static_cast<float>(timeRnd);

		// set up bounding box
		point = localTransformMatrix.multiply(particle.position);
		point.add(center);

		// set up bounding box
		if (first == false) {
			boundingBox.getMin().set(point);
			boundingBox.getMax().set(point);
			first = true;
		} else {
			boundingBox.extend(point);
		}
	}

	// auto disable particle system if no more active particles
	if (activeParticles == 0) {
		active = false;
		return;
	}
	// scale a bit up to make picking work better
	// compute bounding boxes
	boundingBox.update();
	worldBoundingBox.fromBoundingVolumeWithTransformMatrix(&boundingBox, entityTransformMatrix);
	worldBoundingBox.getMin().sub(0.05f + pointSize * pointSizeScale);
	worldBoundingBox.getMax().add(0.05f + pointSize * pointSizeScale);
	worldBoundingBox.update();
}

void FogParticleSystemInternal::setTransform(const Transform& transform)
{
	Transform::setTransform(transform);
	//
	auto entityTransform = parentTransform * (*this);
	entityTransformMatrix = entityTransform.getTransformMatrix();
	//
	updateInternal();
}

void FogParticleSystemInternal::update()
{
	Transform::update();
	//
	auto entityTransform = parentTransform * (*this);
	entityTransformMatrix = entityTransform.getTransformMatrix();
	//
	updateInternal();
}

void FogParticleSystemInternal::updateParticles()
{
	if (enabled == false || active == false) return;

	//
	Vector3 center;
	const auto& localTransformMatrix = localTransform.getTransformMatrix();
	localTransformMatrix.getTranslation(center);
	center.add(emitter->getCenter());
	//
	Vector3 point;
	//
	auto first = false;
	// process particles
	pointsRenderPool->reset();
	auto activeParticles = 0;
	auto timeDelta = engine->getTiming()->getDeltaTime();
	for (auto i = 0; i < particles.size(); i++) {
		auto& particle = particles[i];
		if (particle.active == false) continue;
		// sprite index
		particle.spriteIndex+= (static_cast<float>(timeDelta) / 1000.0f) * fps;
		//
		activeParticles++;
		// set up bounding box
		point = localTransformMatrix.multiply(particle.position);
		point.add(center);
		//
		// set up bounding box
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
		pointsRenderPool->addPoint(point, static_cast<uint16_t>(particle.spriteIndex) % (textureHorizontalSprites * textureVerticalSprites), particle.color, 1, this);
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

void FogParticleSystemInternal::dispose()
{
	pointsRenderPool = nullptr;
}

