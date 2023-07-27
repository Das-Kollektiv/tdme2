#include <tdme/engine/subsystems/particlesystem/BoundingBoxParticleEmitter.h>

#include <tdme/tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>

using tdme::engine::Color4;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::subsystems::particlesystem::BoundingBoxParticleEmitter;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Vector3;

BoundingBoxParticleEmitter::BoundingBoxParticleEmitter(int32_t count, int64_t lifeTime, int64_t lifeTimeRnd, float mass, float massRnd, OrientedBoundingBox* obb, const Vector3& velocity, const Vector3& velocityRnd, const Color4& colorStart, const Color4& colorEnd)
{
	this->count = count;
	this->lifeTime = lifeTime;
	this->lifeTimeRnd = lifeTimeRnd;
	this->mass = mass;
	this->massRnd = massRnd;
	this->obb = obb;
	this->velocity.set(velocity);
	this->velocityRnd.set(velocityRnd);
	this->colorStart.set(colorStart);
	this->colorEnd.set(colorEnd);
	this->worldObb = static_cast<OrientedBoundingBox*>(obb->clone());
}

BoundingBoxParticleEmitter::~BoundingBoxParticleEmitter() {
	delete obb;
	delete worldObb;
}

void BoundingBoxParticleEmitter::emit(Particle* particle)
{
	Vector3 tmpAxis;
	// set up particle
	particle->active = true;
	particle->spriteIndex = 0.0f;
	auto obbAxes = worldObb->getAxes();
	auto& obbHalfExtensionXYZ = worldObb->getHalfExtension().getArray();
	// emit particle in oriented bounding box
	particle->position.set(0.0f, 0.0f, 0.0f);
	particle->position.add(tmpAxis.set(obbAxes[0]).scale((static_cast<float>(Math::random()) * obbHalfExtensionXYZ[0] * 2.0f) - obbHalfExtensionXYZ[0]));
	particle->position.add(tmpAxis.set(obbAxes[1]).scale((static_cast<float>(Math::random()) * obbHalfExtensionXYZ[1] * 2.0f) - obbHalfExtensionXYZ[1]));
	particle->position.add(tmpAxis.set(obbAxes[2]).scale((static_cast<float>(Math::random()) * obbHalfExtensionXYZ[2] * 2.0f) - obbHalfExtensionXYZ[2]));
	// compute velocity
	particle->velocity.set(
		velocity[0] + (Math::random() * velocityRnd[0] * (Math::random() > 0.5 ? +1.0f : -1.0f)),
		velocity[1] + (Math::random() * velocityRnd[1] * (Math::random() > 0.5 ? +1.0f : -1.0f)),
		velocity[2] + (Math::random() * velocityRnd[2] * (Math::random() > 0.5 ? +1.0f : -1.0f))
	);
	// mass
	particle->mass = mass + (Math::random() * (massRnd));
	// life time
	particle->lifeTimeMax = lifeTime + (Math::random() * lifeTimeRnd);
	particle->lifeTimeCurrent = 0LL;
	// color
	particle->color.set(colorStart);
	particle->colorAdd.set(
		(colorEnd.getRed() - colorStart.getRed()) / particle->lifeTimeMax,
		(colorEnd.getGreen() - colorStart.getGreen()) / particle->lifeTimeMax,
		(colorEnd.getBlue() - colorStart.getBlue()) / particle->lifeTimeMax,
		(colorEnd.getAlpha() - colorStart.getAlpha()) / particle->lifeTimeMax);
}

void BoundingBoxParticleEmitter::setTransform(const Transform& transform)
{
	Vector3 worldCenter;
	Vector3 worldScale;
	array<Vector3, 3> worldAxes;
	array<Vector3, 3> worldAxesUnnormalized;
	Vector3 worldHalfExtension;
	auto& transformMatrix = transform.getTransformMatrix();
	// apply rotation, scale, translation
	worldCenter = transformMatrix.multiply(obb->getCenter());
	// apply transform rotation to axis
	worldAxesUnnormalized[0] = transformMatrix.multiplyNoTranslation(obb->getAxes()[0]);
	worldAxesUnnormalized[1] = transformMatrix.multiplyNoTranslation(obb->getAxes()[1]);
	worldAxesUnnormalized[2] = transformMatrix.multiplyNoTranslation(obb->getAxes()[2]);
	// scale
	worldScale.set(
		worldAxesUnnormalized[0].computeLength(),
		worldAxesUnnormalized[1].computeLength(),
		worldAxesUnnormalized[2].computeLength()
	);
	// set up axes
	worldAxes[0].set(worldAxesUnnormalized[0]).normalize();
	worldAxes[1].set(worldAxesUnnormalized[1]).normalize();
	worldAxes[2].set(worldAxesUnnormalized[2]).normalize();
	// apply scale to half extension
	worldHalfExtension.set(obb->getHalfExtension());
	worldHalfExtension.scale(worldScale);
	delete worldObb;
	worldObb = new OrientedBoundingBox(worldCenter, worldAxes[0], worldAxes[1], worldAxes[2], worldHalfExtension);
}
