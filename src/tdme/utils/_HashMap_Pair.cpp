#include <tdme/utils/_HashMap_Pair.h>

using tdme::utils::_HashMap_Pair;
_HashMap_Pair::_HashMap_Pair(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

_HashMap_Pair::_HashMap_Pair()
	: _HashMap_Pair(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* _HashMap_Pair::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.utils._HashMap.Pair", 24);
    return c;
}

java::lang::Class* _HashMap_Pair::getClass0()
{
	return class_();
}

