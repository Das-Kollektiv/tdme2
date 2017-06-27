// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/Properties.h>

using java::util::Properties;
extern void unimplemented_(const char16_t* name);
java::util::Properties::Properties(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::Properties::Properties()
	: Properties(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::util::Properties::Properties(Properties* arg0)
	: Properties(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

char16_tArray* java::util::Properties::hexDigit;
constexpr int64_t java::util::Properties::serialVersionUID;

void Properties::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Properties::ctor()");
}

void Properties::ctor(Properties* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Properties::ctor(Properties* arg0)");
}

/* private: void Properties::enumerate(Hashtable* arg0) */
/* private: void Properties::enumerateStringProperties(Hashtable* arg0) */
String* Properties::getProperty(String* arg0)
{ /* stub */
	unimplemented_(u"String* Properties::getProperty(String* arg0)");
	return 0;
}

String* Properties::getProperty(String* arg0, String* arg1)
{ /* stub */
	unimplemented_(u"String* Properties::getProperty(String* arg0, String* arg1)");
	return 0;
}

void Properties::list(PrintStream* arg0)
{ /* stub */
	unimplemented_(u"void Properties::list(PrintStream* arg0)");
}

void Properties::list(PrintWriter* arg0)
{ /* stub */
	unimplemented_(u"void Properties::list(PrintWriter* arg0)");
}

void Properties::load(Reader* arg0)
{ /* stub */
	unimplemented_(u"void Properties::load(Reader* arg0)");
}

void Properties::load(InputStream* arg0)
{ /* stub */
	unimplemented_(u"void Properties::load(InputStream* arg0)");
}

/* private: void Properties::load0(Properties_LineReader* arg0) */
/* private: String* Properties::loadConvert(char16_tArray* arg0, int32_t arg1, int32_t arg2, char16_tArray* arg3) */
void Properties::loadFromXML(InputStream* arg0)
{ /* stub */
	unimplemented_(u"void Properties::loadFromXML(InputStream* arg0)");
}

Enumeration* Properties::propertyNames()
{ /* stub */
	unimplemented_(u"Enumeration* Properties::propertyNames()");
	return 0;
}

void Properties::save(OutputStream* arg0, String* arg1)
{ /* stub */
	unimplemented_(u"void Properties::save(OutputStream* arg0, String* arg1)");
}

/* private: String* Properties::saveConvert(String* arg0, bool arg1, bool arg2) */
Object* Properties::setProperty(String* arg0, String* arg1)
{ /* stub */
	unimplemented_(u"Object* Properties::setProperty(String* arg0, String* arg1)");
	return 0;
}

void Properties::store(Writer* arg0, String* arg1)
{ /* stub */
	unimplemented_(u"void Properties::store(Writer* arg0, String* arg1)");
}

void Properties::store(OutputStream* arg0, String* arg1)
{ /* stub */
	unimplemented_(u"void Properties::store(OutputStream* arg0, String* arg1)");
}

/* private: void Properties::store0(BufferedWriter* arg0, String* arg1, bool arg2) */
void Properties::storeToXML(OutputStream* arg0, String* arg1)
{ /* stub */
	unimplemented_(u"void Properties::storeToXML(OutputStream* arg0, String* arg1)");
}

void Properties::storeToXML(OutputStream* arg0, String* arg1, String* arg2)
{ /* stub */
	unimplemented_(u"void Properties::storeToXML(OutputStream* arg0, String* arg1, String* arg2)");
}

Set* Properties::stringPropertyNames()
{ /* stub */
	unimplemented_(u"Set* Properties::stringPropertyNames()");
	return 0;
}

/* private: char16_t Properties::toHex(int32_t arg0) */
/* private: void Properties::writeComments(BufferedWriter* arg0, String* arg1) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Properties::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.Properties", 20);
    return c;
}

java::lang::Class* Properties::getClass0()
{
	return class_();
}

