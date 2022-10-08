#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Vector3.h>

using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;

/**
 * Sphere physics primitive
 * @author Andreas Drewke
 */
class tdme::engine::primitives::Sphere final
	: public BoundingVolume
{
private:
	float radius;

	// overriden methods
	void createCollisionShape(World* world) override;

public:
	/**
	 * Public constructor
	 */
	Sphere();

	/**
	 * Public constructor
	 * @param center center
	 * @param radius radius
	 * @param scale scale
	 */
	Sphere(const Vector3& center, float radius, const Vector3& scale = Vector3(1.0f, 1.0f, 1.0f));

	/**
	 * @return float radius
	 */
	float getRadius() const;

	// overrides
	void setScale(const Vector3& scale) override;
	BoundingVolume* clone() const override;

};
