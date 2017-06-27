// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/io/File_LazyInitialization.h>

using java::io::File_LazyInitialization;
extern void unimplemented_(const char16_t* name);
java::io::File_LazyInitialization::File_LazyInitialization(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

SecureRandom* java::io::File_LazyInitialization::random;
String* java::io::File_LazyInitialization::temporaryDirectory_;

/* private: void File_LazyInitialization::ctor() */
String* File_LazyInitialization::temporaryDirectory()
{ /* stub */
	clinit();
	unimplemented_(u"String* File_LazyInitialization::temporaryDirectory()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* File_LazyInitialization::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.io.File.LazyInitialization", 31);
    return c;
}

java::lang::Class* File_LazyInitialization::getClass0()
{
	return class_();
}

