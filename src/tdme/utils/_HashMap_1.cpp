#include <tdme/utils/_HashMap_1.h>

#include <tdme/utils/_HashMap_Pair.h>
#include <tdme/utils/_HashMap.h>

using tdme::utils::_HashMap_1;
using tdme::utils::_HashMap_Pair;
using tdme::utils::_HashMap;

_HashMap_1::_HashMap_1(_HashMap *_HashMap_this)
	: super()
	, _HashMap_this(_HashMap_this)
{
}

_HashMap_Pair* _HashMap_1::instantiate()
{
	return new _HashMap_Pair();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* _HashMap_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* _HashMap_1::getClass0()
{
	return class_();
}

