// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <javax/xml/parsers/fwd-tdme.h>
#include <javax/xml/validation/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::ClassLoader;
using java::lang::String;
using javax::xml::parsers::DocumentBuilder;
using javax::xml::validation::Schema;


struct default_init_tag;
class javax::xml::parsers::DocumentBuilderFactory
	: public virtual Object
{

public:
	typedef Object super;

private:
	static String* DEFAULT_PROPERTY_NAME;
	bool canonicalState {  };
	bool coalescing {  };
	bool expandEntityRef {  };
	bool ignoreComments {  };
	bool namespaceAware {  };
	bool validating {  };
	bool whitespace {  };

protected:
	void ctor();

public:
	virtual Object* getAttribute(String* arg0) = 0;
	virtual bool getFeature(String* arg0) = 0;
	virtual Schema* getSchema();
	virtual bool isCoalescing();
	virtual bool isExpandEntityReferences();
	virtual bool isIgnoringComments();
	virtual bool isIgnoringElementContentWhitespace();
	virtual bool isNamespaceAware();
	virtual bool isValidating();
	virtual bool isXIncludeAware();
	virtual DocumentBuilder* newDocumentBuilder() = 0;
	static DocumentBuilderFactory* newInstance();
	static DocumentBuilderFactory* newInstance(String* arg0, ClassLoader* arg1);
	virtual void setAttribute(String* arg0, Object* arg1) = 0;
	virtual void setCoalescing(bool arg0);
	virtual void setExpandEntityReferences(bool arg0);
	virtual void setFeature(String* arg0, bool arg1) = 0;
	virtual void setIgnoringComments(bool arg0);
	virtual void setIgnoringElementContentWhitespace(bool arg0);
	virtual void setNamespaceAware(bool arg0);
	virtual void setSchema(Schema* arg0);
	virtual void setValidating(bool arg0);
	virtual void setXIncludeAware(bool arg0);

	// Generated

public: /* protected */
	DocumentBuilderFactory();
protected:
	DocumentBuilderFactory(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
