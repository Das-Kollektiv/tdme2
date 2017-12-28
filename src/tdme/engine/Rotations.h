#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Quaternion.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;

using tdme::engine::Rotation;
using tdme::math::Quaternion;

/** 
 * Rotations
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Rotations final
{
	friend class Transformations;

private:
	Quaternion quaternion {  };
	vector<Rotation*> rotations {  };

public:
	/** 
	 * @return number of rotations
	 */
	int32_t size();

	/** 
	 * Get rotation at given index
	 * @param index
	 * @return rotation
	 */
	Rotation* get(int32_t index);

	/** 
	 * Add rotation
	 * @param e
	 * @return
	 */
	void add(Rotation* rotation);

	/** 
	 * Set up a rotation at given index
	 * @param index
	 * @param element
	 * @return rotation
	 */
	void set(int32_t index, Rotation* rotation);

	/** 
	 * Remove rotation at given index
	 * @param index
	 * @return rotation
	 */
	void remove(int32_t index);

	/** 
	 * @return rotation quaternion
	 */
	Quaternion& getQuaternion();

	/** 
	 * Set up this transformations from given transformations
	 * @param transformations
	 */
	void fromRotations(Rotations* transformations);

	/** 
	 * Update rotation quaternion
	 */
	void update();

	/**
	 * Public constructor
	 */
	Rotations();

	/**
	 * Destructor
	 */
	~Rotations();
};
