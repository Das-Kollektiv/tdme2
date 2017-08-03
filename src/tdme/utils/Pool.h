// Generated from /tdme/src/tdme/utils/Pool.java

#pragma once

#include <vector>

#include <java/lang/fwd-tdme.h>

#include <fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;

using java::lang::Object;

/** 
 * Pool 
 * @author Andreas Drewke
 * @version $Id$
 * @param<E>
 */
class tdme::utils::Pool
{
private:
	vector<Object*> freeElements;
	vector<Object*> usedElements;

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

	/**
	 * Public constructor
	 */
	Pool();
};
