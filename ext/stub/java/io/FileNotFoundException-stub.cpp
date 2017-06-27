// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/io/FileNotFoundException.h>

using java::io::FileNotFoundException;
extern void unimplemented_(const char16_t* name);
java::io::FileNotFoundException::FileNotFoundException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::io::FileNotFoundException::FileNotFoundException()
	: FileNotFoundException(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::io::FileNotFoundException::FileNotFoundException(String* arg0)
	: FileNotFoundException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}


void FileNotFoundException::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FileNotFoundException::ctor()");
}

void FileNotFoundException::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FileNotFoundException::ctor(String* arg0)");
}

/* private: void FileNotFoundException::ctor(String* arg0, String* arg1) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* FileNotFoundException::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.io.FileNotFoundException", 29);
    return c;
}

java::lang::Class* FileNotFoundException::getClass0()
{
	return class_();
}

