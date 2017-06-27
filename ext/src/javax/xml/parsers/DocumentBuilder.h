// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <javax/xml/parsers/fwd-tdme.h>
#include <javax/xml/validation/fwd-tdme.h>
#include <org/w3c/dom/fwd-tdme.h>
#include <org/xml/sax/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::File;
using java::io::InputStream;
using java::lang::String;
using javax::xml::validation::Schema;
using org::w3c::dom::DOMImplementation;
using org::w3c::dom::Document;
using org::xml::sax::EntityResolver;
using org::xml::sax::ErrorHandler;
using org::xml::sax::InputSource;


struct default_init_tag;
class javax::xml::parsers::DocumentBuilder
	: public virtual Object
{

public:
	typedef Object super;

protected:
	void ctor();

public:
	virtual DOMImplementation* getDOMImplementation() = 0;
	virtual Schema* getSchema();
	virtual bool isNamespaceAware() = 0;
	virtual bool isValidating() = 0;
	virtual bool isXIncludeAware();
	virtual Document* newDocument() = 0;
	virtual Document* parse(InputStream* arg0);
	virtual Document* parse(String* arg0);
	virtual Document* parse(File* arg0);
	virtual Document* parse(InputSource* arg0) = 0;
	virtual Document* parse(InputStream* arg0, String* arg1);
	virtual void reset();
	virtual void setEntityResolver(EntityResolver* arg0) = 0;
	virtual void setErrorHandler(ErrorHandler* arg0) = 0;

	// Generated

public: /* protected */
	DocumentBuilder();
protected:
	DocumentBuilder(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
