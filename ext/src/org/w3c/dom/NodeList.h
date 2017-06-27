// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <org/w3c/dom/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using org::w3c::dom::Node;


struct org::w3c::dom::NodeList
	: public virtual Object
{

	virtual int32_t getLength() = 0;
	virtual Node* item(int32_t arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
