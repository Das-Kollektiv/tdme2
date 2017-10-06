
#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/Iterator.h>
#include <java/lang/Iterable.h>

using java::lang::Object;
using java::util::Iterator;
using java::lang::Iterable;
using java::lang::String;

using java::lang::ObjectArray;

struct default_init_tag;

/** 
 * Array list implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::_ArrayList final
	: public virtual Object
	, public Iterator
	, public Iterable
{

public:
	typedef Object super;

private:
	int32_t capacity_ {  };
	int32_t size_ {  };
	ObjectArray* elements {  };
	int32_t iteratorIdx {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

	/** 
	 * Public constructor
	 */
	void ctor(ObjectArray* values);

private:

	/** 
	 * Grow
	 */
	void grow();

public:

	/** 
	 * @return is empty
	 */
	bool isEmpty();

	/** 
	 * @return size or number of stored elements
	 */
	int32_t size();

	/** 
	 * @return capacity
	 */
	int32_t capacity();

	/** 
	 * Clear
	 */
	void clear();

	/** 
	 * Add a value
	 * @param value
	 */
	void add(Object* value);

	/** 
	 * Add all elements from given array list
	 * @param values
	 */
	void addAll(_ArrayList* values);

	/** 
	 * Set value at given index
	 * @param idx
	 * @param value
	 */
	Object* set(int32_t idx, Object* value);

	/** 
	 * Remove by index
	 * @param idx
	 * @return removed value
	 */
	Object* remove(int32_t idx);

	/** 
	 * Remove by value
	 * @param value
	 * @return if element has been removed
	 */
	bool remove(Object* value);

	/** 
	 * Gets an element
	 * @param idx
	 * @return value
	 */
	Object* get(int32_t idx);

	/** 
	 * Check if value is contained in array
	 * @param value
	 * @return array list contains value
	 */
	bool contains(Object* value);

	/** 
	 * Fill given array with data from this array list
	 * @param array
	 * @return array
	 */
	ObjectArray* toArray(ObjectArray* array);
	Iterator* iterator() override;
	bool hasNext() override;
	Object* next() override;
	void remove() override;

	/** 
	 * Clones this array list
	 */
	_ArrayList* clone() override;
	String* toString() override;

	// Generated
	_ArrayList();
	_ArrayList(ObjectArray* values);
protected:
	_ArrayList(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
