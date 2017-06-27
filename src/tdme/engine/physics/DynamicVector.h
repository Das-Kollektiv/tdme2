// Generated from /tdme/src/tdme/engine/physics/DynamicVector.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct default_init_tag;

/** 
 * Dynamic Vector
 * @author Andreas Drewke
 * @versioN $Id$
 */
class tdme::engine::physics::DynamicVector final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	floatArray* data {  };
protected:

	/** 
	 * Protected constructor
	 */
	void ctor(int32_t size);

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

public:
	String* toString() override;

	// Generated

public: /* protected */
	DynamicVector(int32_t size);
protected:
	DynamicVector(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
