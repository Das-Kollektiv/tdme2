// Generated from /tdme/src/tdme/utils/Pool.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::utils::_ArrayList;


struct default_init_tag;

/** 
 * Pool 
 * @author Andreas Drewke
 * @version $Id$
 * @param<E>
 */
class tdme::utils::Pool
	: public virtual Object
{

public:
	typedef Object super;

private:
	_ArrayList* freeElements {  };
	_ArrayList* usedElements {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

public:

	/** 
	 * Allocate a new element from pool
	 * @return element
	 */
	Object* allocate();

public: /* protected */

	/** 
	 * Instantiate element
	 */
	virtual Object* instantiate() = 0;

public:

	/** 
	 * Release element in pool for being reused
	 * @param element
	 */
	void release(Object* element);

	/** 
	 * @return element capacity
	 */
	int32_t capacity();

	/** 
	 * @return elements in use
	 */
	int32_t size();

	/** 
	 * Reset this pool
	 */
	void reset();
	String* toString() override;

	// Generated
	Pool();
protected:
	Pool(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
