// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/zip/ZipInputStream.h>

using java::util::zip::ZipInputStream;
extern void unimplemented_(const char16_t* name);
java::util::zip::ZipInputStream::ZipInputStream(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::zip::ZipInputStream::ZipInputStream(InputStream* arg0)
	: ZipInputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

constexpr int32_t java::util::zip::ZipInputStream::DEFLATED;
constexpr int32_t java::util::zip::ZipInputStream::STORED;
String* java::util::zip::ZipInputStream::fileEncoding;

void ZipInputStream::ctor(InputStream* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ZipInputStream::ctor(InputStream* arg0)");
}

int32_t ZipInputStream::available()
{ /* stub */
	unimplemented_(u"int32_t ZipInputStream::available()");
	return 0;
}

void ZipInputStream::close()
{ /* stub */
	unimplemented_(u"void ZipInputStream::close()");
}

void ZipInputStream::closeEntry()
{ /* stub */
	unimplemented_(u"void ZipInputStream::closeEntry()");
}

ZipEntry* ZipInputStream::createZipEntry(String* arg0)
{ /* stub */
	unimplemented_(u"ZipEntry* ZipInputStream::createZipEntry(String* arg0)");
	return 0;
}

/* private: void ZipInputStream::ensureOpen() */
/* private: int32_t ZipInputStream::get16(int8_tArray* arg0, int32_t arg1) */
/* private: int64_t ZipInputStream::get32(int8_tArray* arg0, int32_t arg1) */
/* private: String* ZipInputStream::getFileName(int8_tArray* arg0, int32_t arg1) */
ZipEntry* ZipInputStream::getNextEntry()
{ /* stub */
	unimplemented_(u"ZipEntry* ZipInputStream::getNextEntry()");
	return 0;
}

/* private: String* ZipInputStream::getUTF8String(int8_tArray* arg0, int32_t arg1, int32_t arg2) */
int32_t ZipInputStream::read(int8_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"int32_t ZipInputStream::read(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

/* private: void ZipInputStream::readEnd(ZipEntry* arg0) */
/* private: void ZipInputStream::readFully(int8_tArray* arg0, int32_t arg1, int32_t arg2) */
/* private: ZipEntry* ZipInputStream::readLOC() */
int64_t ZipInputStream::skip(int64_t arg0)
{ /* stub */
	unimplemented_(u"int64_t ZipInputStream::skip(int64_t arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ZipInputStream::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.zip.ZipInputStream", 28);
    return c;
}

int32_t ZipInputStream::read()
{
	return super::read();
}

int32_t ZipInputStream::read(int8_tArray* arg0)
{
	return super::read(arg0);
}

java::lang::Class* ZipInputStream::getClass0()
{
	return class_();
}

