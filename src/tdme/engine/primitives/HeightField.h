#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>

using tdme::engine::primitives::BoundingVolume;

/** 
 * Height field, not yet tested with reactphysics3d-develop
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::HeightField final
	: public BoundingVolume
{
private:
	float* heightMap;

public:
	// overrides
	void fromTransformations(Transformations* transformations);
	BoundingVolume* clone() const override;

	/**
	 * Public constructor
	 * @param model
	 * @param transformations
	 */
	HeightField(Object3DModel* model, Transformations* transformations = nullptr);

	/**
	 * Public destructor
	 */
	~HeightField();

};
