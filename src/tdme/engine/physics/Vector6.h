// Generated from /tdme/src/tdme/engine/physics/Vector6.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Vector6
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::Vector6 final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	floatArray* data {  };
protected:

	/** 
	 * Constructor
	 */
	void ctor();

public: /* protected */

	/** 
	 * Fills the Vector with given value
	 * @param value
	 */
	void fill(float value);

	/** 
	 * Set up vector from vector
	 * @param vector 6
	 * @return this vector
	 */
	Vector6* set(Vector6* vector6);

	/** 
	 * Set up matrix value at given idx
	 * @param idx
	 * @param value
	 */
	void setValue(int32_t idx, float value);

	/** 
	 * Set up vector as value
	 * @param this matrix start idx
	 * @param vector 3
	 */
	void setValue(int32_t startIdx, Vector3* vector3);

	/** 
	 * Adds this vector to given vector6 into dest vector6
	 * @param vector 6
	 * @param this vector 6
	 */
	Vector6* add(Vector6* vector6);

	/** 
	 * Subtracts given vector 6 from this vector 6
	 * @param vector 6
	 * @param this vector 6
	 */
	Vector6* sub(Vector6* vector6);

	/** 
	 * Scales this vector6 with given float value
	 * @param value
	 * @return this vector 6 
	 */
	Vector6* scale(float value);

	/** 
	 * @return data array
	 */
	floatArray* getArray();

public:
	String* toString() override;

	// Generated

public: /* protected */
	Vector6();
protected:
	Vector6(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
