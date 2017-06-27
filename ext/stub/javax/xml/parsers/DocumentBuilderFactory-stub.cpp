// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <javax/xml/parsers/DocumentBuilderFactory.h>

using javax::xml::parsers::DocumentBuilderFactory;
extern void unimplemented_(const char16_t* name);
javax::xml::parsers::DocumentBuilderFactory::DocumentBuilderFactory(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

javax::xml::parsers::DocumentBuilderFactory::DocumentBuilderFactory()
	: DocumentBuilderFactory(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* javax::xml::parsers::DocumentBuilderFactory::DEFAULT_PROPERTY_NAME;

void DocumentBuilderFactory::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void DocumentBuilderFactory::ctor()");
}

Schema* DocumentBuilderFactory::getSchema()
{ /* stub */
	unimplemented_(u"Schema* DocumentBuilderFactory::getSchema()");
	return 0;
}

bool DocumentBuilderFactory::isCoalescing()
{ /* stub */
	unimplemented_(u"bool DocumentBuilderFactory::isCoalescing()");
	return 0;
}

bool DocumentBuilderFactory::isExpandEntityReferences()
{ /* stub */
	unimplemented_(u"bool DocumentBuilderFactory::isExpandEntityReferences()");
	return 0;
}

bool DocumentBuilderFactory::isIgnoringComments()
{ /* stub */
	unimplemented_(u"bool DocumentBuilderFactory::isIgnoringComments()");
	return 0;
}

bool DocumentBuilderFactory::isIgnoringElementContentWhitespace()
{ /* stub */
	unimplemented_(u"bool DocumentBuilderFactory::isIgnoringElementContentWhitespace()");
	return 0;
}

bool DocumentBuilderFactory::isNamespaceAware()
{ /* stub */
	unimplemented_(u"bool DocumentBuilderFactory::isNamespaceAware()");
	return 0;
}

bool DocumentBuilderFactory::isValidating()
{ /* stub */
	unimplemented_(u"bool DocumentBuilderFactory::isValidating()");
	return 0;
}

bool DocumentBuilderFactory::isXIncludeAware()
{ /* stub */
	unimplemented_(u"bool DocumentBuilderFactory::isXIncludeAware()");
	return 0;
}

DocumentBuilderFactory* DocumentBuilderFactory::newInstance()
{ /* stub */
	clinit();
	unimplemented_(u"DocumentBuilderFactory* DocumentBuilderFactory::newInstance()");
	return 0;
}

DocumentBuilderFactory* DocumentBuilderFactory::newInstance(String* arg0, ClassLoader* arg1)
{ /* stub */
	clinit();
	unimplemented_(u"DocumentBuilderFactory* DocumentBuilderFactory::newInstance(String* arg0, ClassLoader* arg1)");
	return 0;
}

void DocumentBuilderFactory::setCoalescing(bool arg0)
{ /* stub */
	this->coalescing = arg0; /* setter */
}

void DocumentBuilderFactory::setExpandEntityReferences(bool arg0)
{ /* stub */
	unimplemented_(u"void DocumentBuilderFactory::setExpandEntityReferences(bool arg0)");
}

void DocumentBuilderFactory::setIgnoringComments(bool arg0)
{ /* stub */
	unimplemented_(u"void DocumentBuilderFactory::setIgnoringComments(bool arg0)");
}

void DocumentBuilderFactory::setIgnoringElementContentWhitespace(bool arg0)
{ /* stub */
	unimplemented_(u"void DocumentBuilderFactory::setIgnoringElementContentWhitespace(bool arg0)");
}

void DocumentBuilderFactory::setNamespaceAware(bool arg0)
{ /* stub */
	this->namespaceAware = arg0; /* setter */
}

void DocumentBuilderFactory::setSchema(Schema* arg0)
{ /* stub */
	unimplemented_(u"void DocumentBuilderFactory::setSchema(Schema* arg0)");
}

void DocumentBuilderFactory::setValidating(bool arg0)
{ /* stub */
	this->validating = arg0; /* setter */
}

void DocumentBuilderFactory::setXIncludeAware(bool arg0)
{ /* stub */
	unimplemented_(u"void DocumentBuilderFactory::setXIncludeAware(bool arg0)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* DocumentBuilderFactory::class_()
{
    static ::java::lang::Class* c = ::class_(u"javax.xml.parsers.DocumentBuilderFactory", 40);
    return c;
}

java::lang::Class* DocumentBuilderFactory::getClass0()
{
	return class_();
}

