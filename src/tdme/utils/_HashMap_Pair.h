
#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::utils::_HashMap_KeysIterator;
using tdme::utils::_HashMap_ValuesIterator;
using tdme::utils::_HashMap;


struct default_init_tag;

/** 
 * @author Andreas Drewke
 * @param<K>
 * @param<V>
 */
class tdme::utils::_HashMap_Pair final
	: public Object
{

public:
	typedef Object super;

private:
	Object* key {  };
	Object* value {  };

	// Generated

public:
	_HashMap_Pair();
protected:
	_HashMap_Pair(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class _HashMap;
	friend class _HashMap_ValuesIterator;
	friend class _HashMap_KeysIterator;
	friend class _HashMap_1;
};
