// Generated from /tdme/src/tdme/engine/physics/Matrix6x6.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::physics::Vector6;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Matrix 6x6
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::Matrix6x6 final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	floatArray* data {  };
protected:
	void ctor();

public: /* protected */

	/** 
	 * Fills the Vector with given value
	 * @param value
	 */
	void fill(float value);

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
	 * Set up vector as value
	 * @param this matrix start idx
	 * @param vector 3
	 */
	void setValue(int32_t i, int32_t j, float value);

	/** 
	 * @return data array
	 */
	floatArray* getArray();

	/** 
	 * Multiplies this matrix 6x6 with given vector 6
	 * @param vector 6
	 * @param destination vector
	 * @return destination vector
	 */
	Vector6* multiply(Vector6* vector6, Vector6* dest);

public:
	String* toString() override;

	// Generated

public: /* protected */
	Matrix6x6();
protected:
	Matrix6x6(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
