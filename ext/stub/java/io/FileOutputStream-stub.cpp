// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/io/FileOutputStream.h>

using java::io::FileOutputStream;
extern void unimplemented_(const char16_t* name);
java::io::FileOutputStream::FileOutputStream(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::io::FileOutputStream::FileOutputStream(String* arg0)
	: FileOutputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::io::FileOutputStream::FileOutputStream(File* arg0)
	: FileOutputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::io::FileOutputStream::FileOutputStream(FileDescriptor* arg0)
	: FileOutputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::io::FileOutputStream::FileOutputStream(String* arg0, bool arg1)
	: FileOutputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

java::io::FileOutputStream::FileOutputStream(File* arg0, bool arg1)
	: FileOutputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

ThreadLocal* java::io::FileOutputStream::runningFinalize;

void FileOutputStream::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FileOutputStream::ctor(String* arg0)");
}

void FileOutputStream::ctor(File* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FileOutputStream::ctor(File* arg0)");
}

void FileOutputStream::ctor(FileDescriptor* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FileOutputStream::ctor(FileDescriptor* arg0)");
}

void FileOutputStream::ctor(String* arg0, bool arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FileOutputStream::ctor(String* arg0, bool arg1)");
}

void FileOutputStream::ctor(File* arg0, bool arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FileOutputStream::ctor(File* arg0, bool arg1)");
}

void FileOutputStream::close()
{ /* stub */
	unimplemented_(u"void FileOutputStream::close()");
}

void FileOutputStream::finalize()
{ /* stub */
	unimplemented_(u"void FileOutputStream::finalize()");
}

FileChannel* FileOutputStream::getChannel()
{ /* stub */
return channel ; /* getter */
}

FileDescriptor* FileOutputStream::getFD()
{ /* stub */
	unimplemented_(u"FileDescriptor* FileOutputStream::getFD()");
	return 0;
}

/* private: bool FileOutputStream::isRunningFinalize() */
void FileOutputStream::write(int8_tArray* arg0)
{ /* stub */
	unimplemented_(u"void FileOutputStream::write(int8_tArray* arg0)");
}

void FileOutputStream::write(int8_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"void FileOutputStream::write(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* FileOutputStream::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.io.FileOutputStream", 24);
    return c;
}

java::lang::Class* FileOutputStream::getClass0()
{
	return class_();
}

