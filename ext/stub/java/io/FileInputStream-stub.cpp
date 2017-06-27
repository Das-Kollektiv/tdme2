// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/io/FileInputStream.h>

using java::io::FileInputStream;
extern void unimplemented_(const char16_t* name);
java::io::FileInputStream::FileInputStream(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::io::FileInputStream::FileInputStream(String* arg0)
	: FileInputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::io::FileInputStream::FileInputStream(File* arg0)
	: FileInputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::io::FileInputStream::FileInputStream(FileDescriptor* arg0)
	: FileInputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

ThreadLocal* java::io::FileInputStream::runningFinalize;

void FileInputStream::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FileInputStream::ctor(String* arg0)");
}

void FileInputStream::ctor(File* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FileInputStream::ctor(File* arg0)");
}

void FileInputStream::ctor(FileDescriptor* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FileInputStream::ctor(FileDescriptor* arg0)");
}

void FileInputStream::close()
{ /* stub */
	unimplemented_(u"void FileInputStream::close()");
}

void FileInputStream::finalize()
{ /* stub */
	unimplemented_(u"void FileInputStream::finalize()");
}

FileChannel* FileInputStream::getChannel()
{ /* stub */
return channel ; /* getter */
}

FileDescriptor* FileInputStream::getFD()
{ /* stub */
	unimplemented_(u"FileDescriptor* FileInputStream::getFD()");
	return 0;
}

/* private: bool FileInputStream::isRunningFinalize() */
int32_t FileInputStream::read(int8_tArray* arg0)
{ /* stub */
	unimplemented_(u"int32_t FileInputStream::read(int8_tArray* arg0)");
	return 0;
}

int32_t FileInputStream::read(int8_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"int32_t FileInputStream::read(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* FileInputStream::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.io.FileInputStream", 23);
    return c;
}

java::lang::Class* FileInputStream::getClass0()
{
	return class_();
}

