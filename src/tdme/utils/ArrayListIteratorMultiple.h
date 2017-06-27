// Generated from /tdme/src/tdme/utils/ArrayListIteratorMultiple.java

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
using tdme::utils::_ArrayList;


struct default_init_tag;

/** 
 * Array list iterator for multiple array lists
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::ArrayListIteratorMultiple final
	: public virtual Object
	, public Iterator
	, public Iterable
{

public:
	typedef Object super;

private:
	int32_t vectorIdx {  };
	int32_t elementIdx {  };
	int32_t length {  };
	_ArrayList* arrayLists {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

	/** 
	 * Public constructor
	 * @param array lists
	 */
	void ctor(_ArrayList* arrayLists);

public:

	/** 
	 * Clears list of array lists to iterate
	 */
	void clear();

	/** 
	 * Adds array lists to iterate
	 * @param array lists
	 */
	void addArrayList(_ArrayList* _arrayLists);

	/** 
	 * resets vector iterator for iterating
	 * @return this vector iterator
	 */
	ArrayListIteratorMultiple* reset();
	bool hasNext() override;
	Object* next() override;
	void remove() override;
	Iterator* iterator() override;

	/** 
	 * Clones this iterator
	 */
	ArrayListIteratorMultiple* clone() override;

	// Generated
	ArrayListIteratorMultiple();
	ArrayListIteratorMultiple(_ArrayList* arrayLists);
protected:
	ArrayListIteratorMultiple(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
