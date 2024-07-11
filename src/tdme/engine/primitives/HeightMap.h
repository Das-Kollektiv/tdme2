#pragma once

#include <reactphysics3d/collision/HeightField.h>

#include <tdme/tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Vector3.h>

using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;

/**
 * Height map physics primitive
 * @author Andreas Drewke
 */
class tdme::engine::primitives::HeightMap final
	: public BoundingVolume
{
private:
	int columns;
	int rows;
	float* heightValues;
	reactphysics3d::HeightField* heightField { nullptr };

	// overridden methods
	void destroyCollisionShape() override;
	void createCollisionShape(World* world) override;

public:
	// forbid class copy
	FORBID_CLASS_COPY(HeightMap)

	/**
	 * Public constructor
	 * @param colums columns
	 * @param rows rows
	 * @param heightValues height values which will not be copied
	 * @param scale scale
	 */
	HeightMap(
		int columns,
		int rows,
		float* heightValues,
		const Vector3& scale = Vector3(1.0f, 1.0f, 1.0f)
	);

	/**
	 * Public destructor
	 */
	~HeightMap();

	// overrides
	void setScale(const Vector3& scale) override;
	BoundingVolume* clone() const override;

};
