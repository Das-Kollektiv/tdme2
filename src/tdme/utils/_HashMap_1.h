// Generated from /tdme/src/tdme/utils/_HashMap.java

#pragma once

#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/utils/_HashMap_Pair.h>

using tdme::utils::Pool;
using tdme::utils::_HashMap_KeysIterator;
using tdme::utils::_HashMap_Pair;
using tdme::utils::_HashMap_ValuesIterator;
using tdme::utils::_HashMap;


struct default_init_tag;
class tdme::utils::_HashMap_1
	: public Pool
{

public:
	typedef Pool super;

public: /* protected */
	_HashMap_Pair* instantiate() override;

	// Generated

public:
	_HashMap_1(_HashMap *_HashMap_this);
	static ::java::lang::Class *class_();
	_HashMap *_HashMap_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class _HashMap;
	friend class _HashMap_ValuesIterator;
	friend class _HashMap_KeysIterator;
	friend class _HashMap_Pair;
};
