// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/ArrayStoreException.h>

using java::lang::ArrayStoreException;
extern void unimplemented_(const char16_t* name);
java::lang::ArrayStoreException::ArrayStoreException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::ArrayStoreException::ArrayStoreException()
	: ArrayStoreException(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::lang::ArrayStoreException::ArrayStoreException(String* arg0)
	: ArrayStoreException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}


void ArrayStoreException::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ArrayStoreException::ctor()");
}

void ArrayStoreException::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ArrayStoreException::ctor(String* arg0)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ArrayStoreException::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.ArrayStoreException", 29);
    return c;
}

java::lang::Class* ArrayStoreException::getClass0()
{
	return class_();
}

