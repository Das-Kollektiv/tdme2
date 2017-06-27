// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/zip/ZipEntry.h>

using java::util::zip::ZipEntry;
extern void unimplemented_(const char16_t* name);
java::util::zip::ZipEntry::ZipEntry(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::zip::ZipEntry::ZipEntry(String* arg0)
	: ZipEntry(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::util::zip::ZipEntry::ZipEntry(ZipEntry* arg0)
	: ZipEntry(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::util::zip::ZipEntry::ZipEntry(int64_t arg0)
	: ZipEntry(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::util::zip::ZipEntry::ZipEntry(String* arg0, int64_t arg1)
	: ZipEntry(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

constexpr int32_t java::util::zip::ZipEntry::DEFLATED;
constexpr int32_t java::util::zip::ZipEntry::STORED;

void ZipEntry::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ZipEntry::ctor(String* arg0)");
}

void ZipEntry::ctor(ZipEntry* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ZipEntry::ctor(ZipEntry* arg0)");
}

void ZipEntry::ctor(int64_t arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ZipEntry::ctor(int64_t arg0)");
}

void ZipEntry::ctor(String* arg0, int64_t arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ZipEntry::ctor(String* arg0, int64_t arg1)");
}

Object* ZipEntry::clone()
{ /* stub */
	unimplemented_(u"Object* ZipEntry::clone()");
	return 0;
}

/* private: int64_t ZipEntry::dosToJavaTime(int64_t arg0) */
String* ZipEntry::getComment()
{ /* stub */
return comment ; /* getter */
}

int64_t ZipEntry::getCompressedSize()
{ /* stub */
	unimplemented_(u"int64_t ZipEntry::getCompressedSize()");
	return 0;
}

int64_t ZipEntry::getCrc()
{ /* stub */
return crc ; /* getter */
}

int8_tArray* ZipEntry::getExtra()
{ /* stub */
return extra ; /* getter */
}

int32_t ZipEntry::getMethod()
{ /* stub */
return method ; /* getter */
}

String* ZipEntry::getName()
{ /* stub */
return name ; /* getter */
}

int64_t ZipEntry::getSize()
{ /* stub */
return size ; /* getter */
}

int64_t ZipEntry::getTime()
{ /* stub */
return time ; /* getter */
}

int32_t ZipEntry::hashCode()
{ /* stub */
	unimplemented_(u"int32_t ZipEntry::hashCode()");
	return 0;
}

bool ZipEntry::isDirectory()
{ /* stub */
	unimplemented_(u"bool ZipEntry::isDirectory()");
	return 0;
}

/* private: int64_t ZipEntry::javaToDosTime(int64_t arg0) */
void ZipEntry::setComment(String* arg0)
{ /* stub */
	this->comment = arg0; /* setter */
}

void ZipEntry::setCompressedSize(int64_t arg0)
{ /* stub */
	unimplemented_(u"void ZipEntry::setCompressedSize(int64_t arg0)");
}

void ZipEntry::setCrc(int64_t arg0)
{ /* stub */
	this->crc = arg0; /* setter */
}

void ZipEntry::setExtra(int8_tArray* arg0)
{ /* stub */
	this->extra = arg0; /* setter */
}

void ZipEntry::setMethod(int32_t arg0)
{ /* stub */
	this->method = arg0; /* setter */
}

void ZipEntry::setSize(int64_t arg0)
{ /* stub */
	this->size = arg0; /* setter */
}

void ZipEntry::setTime(int64_t arg0)
{ /* stub */
	this->time = arg0; /* setter */
}

String* ZipEntry::toString()
{ /* stub */
	unimplemented_(u"String* ZipEntry::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ZipEntry::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.zip.ZipEntry", 22);
    return c;
}

java::lang::Class* ZipEntry::getClass0()
{
	return class_();
}

