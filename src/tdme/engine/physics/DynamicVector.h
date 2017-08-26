// Generated from /tdme/src/tdme/engine/physics/DynamicVector.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>

using std::vector;

/** 
 * Dynamic Vector
 * @author Andreas Drewke
 * @versioN $Id$
 */
class tdme::engine::physics::DynamicVector final
{
public: /* protected */
	vector<float> data {  };

public: /* protected */

	/** 
	 * Change size
	 * @param size
	 */
	void setSize(int32_t size);

	/** 
	 * Set value
	 * @param idx
	 * @param value
	 */
	void setValue(int32_t idx, float value);

	/** 
	 * Retrieves value
	 * @param idx
	 * @return value
	 */
	float getValue(int32_t idx);

	/** 
	 * Scales this vector with given value into dest vector
	 * @param value
	 * @param dest
	 */
	void scale(float value, DynamicVector* dest);

	/**
	 * Constructor
	 */
	DynamicVector();

	/**
	 * Constructor
	 * @param size
	 */
	DynamicVector(int32_t size);
};
