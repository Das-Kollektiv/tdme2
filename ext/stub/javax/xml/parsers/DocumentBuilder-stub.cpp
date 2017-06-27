// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <javax/xml/parsers/DocumentBuilder.h>

using javax::xml::parsers::DocumentBuilder;
extern void unimplemented_(const char16_t* name);
javax::xml::parsers::DocumentBuilder::DocumentBuilder(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

javax::xml::parsers::DocumentBuilder::DocumentBuilder()
	: DocumentBuilder(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}


void DocumentBuilder::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void DocumentBuilder::ctor()");
}

Schema* DocumentBuilder::getSchema()
{ /* stub */
	unimplemented_(u"Schema* DocumentBuilder::getSchema()");
	return 0;
}

bool DocumentBuilder::isXIncludeAware()
{ /* stub */
	unimplemented_(u"bool DocumentBuilder::isXIncludeAware()");
	return 0;
}

Document* DocumentBuilder::parse(InputStream* arg0)
{ /* stub */
	unimplemented_(u"Document* DocumentBuilder::parse(InputStream* arg0)");
	return 0;
}

Document* DocumentBuilder::parse(String* arg0)
{ /* stub */
	unimplemented_(u"Document* DocumentBuilder::parse(String* arg0)");
	return 0;
}

Document* DocumentBuilder::parse(File* arg0)
{ /* stub */
	unimplemented_(u"Document* DocumentBuilder::parse(File* arg0)");
	return 0;
}

Document* DocumentBuilder::parse(InputStream* arg0, String* arg1)
{ /* stub */
	unimplemented_(u"Document* DocumentBuilder::parse(InputStream* arg0, String* arg1)");
	return 0;
}

void DocumentBuilder::reset()
{ /* stub */
	unimplemented_(u"void DocumentBuilder::reset()");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* DocumentBuilder::class_()
{
    static ::java::lang::Class* c = ::class_(u"javax.xml.parsers.DocumentBuilder", 33);
    return c;
}

java::lang::Class* DocumentBuilder::getClass0()
{
	return class_();
}

