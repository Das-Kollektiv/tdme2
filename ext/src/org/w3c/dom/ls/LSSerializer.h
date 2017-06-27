// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <org/w3c/dom/fwd-tdme.h>
#include <org/w3c/dom/ls/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using org::w3c::dom::DOMConfiguration;
using org::w3c::dom::Node;
using org::w3c::dom::ls::LSOutput;
using org::w3c::dom::ls::LSSerializerFilter;


struct org::w3c::dom::ls::LSSerializer
	: public virtual Object
{

	virtual DOMConfiguration* getDomConfig() = 0;
	virtual LSSerializerFilter* getFilter() = 0;
	virtual String* getNewLine() = 0;
	virtual void setFilter(LSSerializerFilter* arg0) = 0;
	virtual void setNewLine(String* arg0) = 0;
	virtual bool write(Node* arg0, LSOutput* arg1) = 0;
	virtual String* writeToString(Node* arg0) = 0;
	virtual bool writeToURI(Node* arg0, String* arg1) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
