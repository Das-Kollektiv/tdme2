// Generated from /tdme/src/tdme/utils/_HashMap.java

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
using tdme::utils::_HashMap_KeysIterator;
using tdme::utils::_HashMap_Pair;
using tdme::utils::_HashMap;


struct default_init_tag;

/** 
 * Values Iterator 
 * @author Andreas Drewke
 * @param<K>
 * @param<V>
 */
class tdme::utils::_HashMap_ValuesIterator final
	: public virtual Object
	, public Iterator
	, public Iterable
{

public:
	typedef Object super;

private:
	_HashMap* hashMap {  };
	int32_t bucketIdx {  };
	int32_t keyValuePairIdx {  };
	int32_t elementIdx {  };
protected:

	/** 
	 * Public constructor
	 * @param hashmap
	 */
	void ctor(_HashMap* hashmap);

public:

	/** 
	 * Reset
	 * @return this iterator
	 */
	Iterator* reset();
	Iterator* iterator() override;
	bool hasNext() override;
	Object* next() override;
	void remove() override;

	// Generated
	_HashMap_ValuesIterator(_HashMap* hashmap);
protected:
	_HashMap_ValuesIterator(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class _HashMap;
	friend class _HashMap_KeysIterator;
	friend class _HashMap_Pair;
	friend class _HashMap_1;
};
