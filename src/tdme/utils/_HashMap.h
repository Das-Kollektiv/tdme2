// Generated from /tdme/src/tdme/utils/_HashMap.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::utils::Pool;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap_KeysIterator;
using tdme::utils::_HashMap_Pair;
using tdme::utils::_HashMap_ValuesIterator;


struct default_init_tag;

/** 
 * Hashmap which keeps track of keys and values in a array list
 * @author Andreas Drewke
 * @param<K>
 * @param<V>
 */
class tdme::utils::_HashMap final
	: public Object
{

public:
	typedef Object super;

private:
	int32_t capacity {  };
	int32_t elements {  };
	_ArrayList* buckets {  };
	_HashMap_ValuesIterator* valuesIterator {  };
	_HashMap_KeysIterator* keysIterator {  };
	Pool* pairPool {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

public:

	/** 
	 * Clears this hash table
	 */
	void clear();

private:

	/** 
	 * Grow hash map
	 */
	void grow();

public:

	/** 
	 * Get the associated value of given object / key
	 */
	Object* get(Object* key);

	/** 
	 * Removes associated value of given object / key
	 */
	Object* remove(Object* key);

	/** 
	 * Get the key of given object / key
	 */
	Object* getKey(Object* key);

	/** 
	 * Put given value with associated key into this hash map
	 */
	Object* put(Object* key, Object* value);

	/** 
	 * @return number of elements
	 */
	int32_t size();

	/** 
	 * @return Values Iterator
	 */
	_HashMap_ValuesIterator* getValuesIterator();

	/** 
	 * @return Keys Iterator
	 */
	_HashMap_KeysIterator* getKeysIterator();
	String* toString() override;

	// Generated
	_HashMap();
protected:
	_HashMap(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
	friend class _HashMap_ValuesIterator;
	friend class _HashMap_KeysIterator;
	friend class _HashMap_Pair;
	friend class _HashMap_1;
};
