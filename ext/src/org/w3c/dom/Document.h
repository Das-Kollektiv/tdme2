// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <org/w3c/dom/fwd-tdme.h>
#include <org/w3c/dom/Node.h>

using org::w3c::dom::Node;
using java::lang::String;
using org::w3c::dom::Attr;
using org::w3c::dom::CDATASection;
using org::w3c::dom::Comment;
using org::w3c::dom::DOMConfiguration;
using org::w3c::dom::DOMImplementation;
using org::w3c::dom::DocumentFragment;
using org::w3c::dom::DocumentType;
using org::w3c::dom::Element;
using org::w3c::dom::EntityReference;
using org::w3c::dom::NodeList;
using org::w3c::dom::ProcessingInstruction;
using org::w3c::dom::Text;


struct org::w3c::dom::Document
	: public virtual Node
{

	virtual Node* adoptNode(Node* arg0) = 0;
	virtual Attr* createAttribute(String* arg0) = 0;
	virtual Attr* createAttributeNS(String* arg0, String* arg1) = 0;
	virtual CDATASection* createCDATASection(String* arg0) = 0;
	virtual Comment* createComment(String* arg0) = 0;
	virtual DocumentFragment* createDocumentFragment() = 0;
	virtual Element* createElement(String* arg0) = 0;
	virtual Element* createElementNS(String* arg0, String* arg1) = 0;
	virtual EntityReference* createEntityReference(String* arg0) = 0;
	virtual ProcessingInstruction* createProcessingInstruction(String* arg0, String* arg1) = 0;
	virtual Text* createTextNode(String* arg0) = 0;
	virtual DocumentType* getDoctype() = 0;
	virtual Element* getDocumentElement() = 0;
	virtual String* getDocumentURI() = 0;
	virtual DOMConfiguration* getDomConfig() = 0;
	virtual Element* getElementById(String* arg0) = 0;
	virtual NodeList* getElementsByTagName(String* arg0) = 0;
	virtual NodeList* getElementsByTagNameNS(String* arg0, String* arg1) = 0;
	virtual DOMImplementation* getImplementation() = 0;
	virtual String* getInputEncoding() = 0;
	virtual bool getStrictErrorChecking() = 0;
	virtual String* getXmlEncoding() = 0;
	virtual bool getXmlStandalone() = 0;
	virtual String* getXmlVersion() = 0;
	virtual Node* importNode(Node* arg0, bool arg1) = 0;
	virtual void normalizeDocument() = 0;
	virtual Node* renameNode(Node* arg0, String* arg1, String* arg2) = 0;
	virtual void setDocumentURI(String* arg0) = 0;
	virtual void setStrictErrorChecking(bool arg0) = 0;
	virtual void setXmlStandalone(bool arg0) = 0;
	virtual void setXmlVersion(String* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
