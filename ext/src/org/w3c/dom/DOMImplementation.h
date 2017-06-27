// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <org/w3c/dom/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using org::w3c::dom::Document;
using org::w3c::dom::DocumentType;


struct org::w3c::dom::DOMImplementation
	: public virtual Object
{

	virtual Document* createDocument(String* arg0, String* arg1, DocumentType* arg2) = 0;
	virtual DocumentType* createDocumentType(String* arg0, String* arg1, String* arg2) = 0;
	virtual Object* getFeature(String* arg0, String* arg1) = 0;
	virtual bool hasFeature(String* arg0, String* arg1) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
