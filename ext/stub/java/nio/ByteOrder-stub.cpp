// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/nio/ByteOrder.h>

using java::nio::ByteOrder;
extern void unimplemented_(const char16_t* name);
java::nio::ByteOrder::ByteOrder(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ByteOrder* java::nio::ByteOrder::BIG_ENDIAN_;
ByteOrder* java::nio::ByteOrder::LITTLE_ENDIAN_;

/* private: void ByteOrder::ctor(String* arg0) */
ByteOrder* ByteOrder::nativeOrder()
{ /* stub */
	clinit();
	unimplemented_(u"ByteOrder* ByteOrder::nativeOrder()");
	return 0;
}

String* ByteOrder::toString()
{ /* stub */
	unimplemented_(u"String* ByteOrder::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ByteOrder::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.nio.ByteOrder", 18);
    return c;
}

java::lang::Class* ByteOrder::getClass0()
{
	return class_();
}

