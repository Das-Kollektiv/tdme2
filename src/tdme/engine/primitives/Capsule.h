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
 * Capsule physics primitive
 * @author Andreas Drewke
 */
class tdme::engine::primitives::Capsule final
	: public BoundingVolume
{
private:
	// overridden methods
	void destroyCollisionShape() override;
	void createCollisionShape(World* world) override;

public:
	// forbid class copy
	FORBID_CLASS_COPY(Capsule)

	/**
	 * Public constructor
	 * @param a a
	 * @param b b
	 * @param radius radius
	 * @param scale scale
	 */
	Capsule(const Vector3& a, const Vector3& b, float radius, const Vector3& scale = Vector3(1.0f, 1.0f, 1.0f));

	/**
	 * Public destructor
	 */
	~Capsule();

	/**
	 * @returns radius
	 */
	float getRadius() const;

	/**
	 * @returns line segment point a
	 */
	const Vector3& getA() const;

	/**
	 * @returns line segment point b
	 */
	const Vector3& getB() const;


	// overrides
	void setScale(const Vector3& scale) override;
	BoundingVolume* clone() const override;

private:
	//
	Vector3 a;
	Vector3 b;
	float radius;
};
