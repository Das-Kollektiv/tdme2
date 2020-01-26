#include <tdme/engine/subsystems/particlesystem/FogParticleSystemInternal.h>

#include <string>
#include <vector>

#include <tdme/math/Math.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPointsPool.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/engine/subsystems/particlesystem/ParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemEntityInternal.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::string;
using std::vector;

using tdme::engine::subsystems::particlesystem::FogParticleSystemInternal;
using tdme::math::Math;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::engine::Transformations;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::particlesystem::ParticleSystemEntityInternal;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

FogParticleSystemInternal::FogParticleSystemInternal(const string& id, ParticleEmitter* emitter, int32_t maxPoints, float pointSize, Texture* texture, int32_t textureHorizontalSprites, int32_t textureVerticalSprites, float fps)
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
	this->pointsRenderPool = nullptr;
	this->texture = texture;
	this->textureId = 0;
	this->textureHorizontalSprites = textureHorizontalSprites;
	this->textureVerticalSprites = textureVerticalSprites;
	this->fps = fps;
}

FogParticleSystemInternal::~FogParticleSystemInternal() {
	delete emitter;
}

void FogParticleSystemInternal::initialize() {
	this->textureId = this->texture == nullptr?engine->getTextureManager()->addTexture(this->texture = TextureReader::read("resources/engine/textures", "point.png"), renderer->getDefaultContext()):engine->getTextureManager()->addTexture(this->texture, renderer->getDefaultContext());
	this->pointsRenderPool = new TransparentRenderPointsPool(maxPoints);

	//
	// enable particle system
	active = true;
	// emit particles
	for (auto i = 0; i < particles.size(); i++) {
		// emit particle
		emitter->emit(&particles[i]);
	}

	// bounding box transformed min, max xyz
	auto& bbMinXYZ = boundingBox.getMin().getArray();
	auto& bbMaxXYZ = boundingBox.getMax().getArray();
	//
	auto haveBoundingBox = false;
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
		auto& color = particle.color.getArray();
		auto& colorAdd = particle.colorAdd.getArray();
		color[0] += colorAdd[0] * static_cast< float >(timeRnd);
		color[1] += colorAdd[1] * static_cast< float >(timeRnd);
		color[2] += colorAdd[2] * static_cast< float >(timeRnd);
		color[3] += colorAdd[3] * static_cast< float >(timeRnd);

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
	}

	// auto disable particle system if no more active particles
	if (activeParticles == 0) {
		active = false;
		return;
	}
	// scale a bit up to make picking work better
	// compute bounding boxes
	boundingBox.update();
	boundingBoxTransformed.fromBoundingVolumeWithTransformations(&boundingBox, *this);
	boundingBoxTransformed.getMin().sub(0.05f);
	boundingBoxTransformed.getMax().add(0.05f);
	boundingBoxTransformed.update();
}

void FogParticleSystemInternal::fromTransformations(const Transformations& transformations)
{
	Transformations::fromTransformations(transformations);
	updateInternal();
}

void FogParticleSystemInternal::update()
{
	Transformations::update();
	updateInternal();
}

void FogParticleSystemInternal::updateParticles()
{
	if (enabled == false || active == false) return;

	//
	Vector3 point;
	// bounding box transformed min, max xyz
	auto& bbMinXYZ = boundingBox.getMin().getArray();
	auto& bbMaxXYZ = boundingBox.getMax().getArray();
	//
	auto haveBoundingBox = false;
	// points are stored in camera space in points render pool
	auto& modelMatrix = getTransformationsMatrix();
	// process particles
	pointsRenderPool->reset();
	auto activeParticles = 0;
	auto timeDelta = engine->getTiming()->getDeltaTime();
	for (auto i = 0; i < particles.size(); i++) {
		auto& particle = particles[i];
		if (particle.active == false) continue;
		// sprite index
		particle.spriteIndex+= (static_cast<float>(timeDelta) / 1000.0f) * fps;
		// transform particle position to camera space
		modelMatrix.multiply(particle.position, point);
		//
		activeParticles++;
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
		pointsRenderPool->addPoint(point, static_cast<uint16_t>(particle.spriteIndex) % (textureHorizontalSprites * textureVerticalSprites), particle.color, 1, this);
	}
	// auto disable particle system if no more active particles
	if (activeParticles == 0) {
		active = false;
		return;
	}
	// scale a bit up to make picking work better
	boundingBox.update();
	boundingBoxTransformed.fromBoundingVolumeWithTransformations(&boundingBox, *this);
	boundingBoxTransformed.getMin().sub(0.05f);
	boundingBoxTransformed.getMax().add(0.05f);
	boundingBoxTransformed.update();
}

void FogParticleSystemInternal::dispose()
{
	if (pointsRenderPool != nullptr) delete pointsRenderPool;
	pointsRenderPool = nullptr;
	engine->getTextureManager()->removeTexture(texture->getId());
}

