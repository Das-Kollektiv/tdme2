// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <org/w3c/dom/fwd-tdme.h>
#include <org/w3c/dom/Node.h>

using org::w3c::dom::Node;
using java::lang::String;
using org::w3c::dom::Attr;
using org::w3c::dom::NodeList;
using org::w3c::dom::TypeInfo;


struct org::w3c::dom::Element
	: public virtual Node
{

	virtual String* getAttribute(String* arg0) = 0;
	virtual String* getAttributeNS(String* arg0, String* arg1) = 0;
	virtual Attr* getAttributeNode(String* arg0) = 0;
	virtual Attr* getAttributeNodeNS(String* arg0, String* arg1) = 0;
	virtual NodeList* getElementsByTagName(String* arg0) = 0;
	virtual NodeList* getElementsByTagNameNS(String* arg0, String* arg1) = 0;
	virtual TypeInfo* getSchemaTypeInfo() = 0;
	virtual String* getTagName() = 0;
	virtual bool hasAttribute(String* arg0) = 0;
	virtual bool hasAttributeNS(String* arg0, String* arg1) = 0;
	virtual void removeAttribute(String* arg0) = 0;
	virtual void removeAttributeNS(String* arg0, String* arg1) = 0;
	virtual Attr* removeAttributeNode(Attr* arg0) = 0;
	virtual void setAttribute(String* arg0, String* arg1) = 0;
	virtual void setAttributeNS(String* arg0, String* arg1, String* arg2) = 0;
	virtual Attr* setAttributeNode(Attr* arg0) = 0;
	virtual Attr* setAttributeNodeNS(Attr* arg0) = 0;
	virtual void setIdAttribute(String* arg0, bool arg1) = 0;
	virtual void setIdAttributeNS(String* arg0, String* arg1, bool arg2) = 0;
	virtual void setIdAttributeNode(Attr* arg0, bool arg1) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
