// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <org/w3c/dom/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using org::w3c::dom::Node;


struct org::w3c::dom::NamedNodeMap
	: public virtual Object
{

	virtual int32_t getLength() = 0;
	virtual Node* getNamedItem(String* arg0) = 0;
	virtual Node* getNamedItemNS(String* arg0, String* arg1) = 0;
	virtual Node* item(int32_t arg0) = 0;
	virtual Node* removeNamedItem(String* arg0) = 0;
	virtual Node* removeNamedItemNS(String* arg0, String* arg1) = 0;
	virtual Node* setNamedItem(Node* arg0) = 0;
	virtual Node* setNamedItemNS(Node* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
