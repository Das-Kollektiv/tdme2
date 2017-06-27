// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <org/w3c/dom/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using org::w3c::dom::Document;
using org::w3c::dom::NamedNodeMap;
using org::w3c::dom::NodeList;
using org::w3c::dom::UserDataHandler;


struct org::w3c::dom::Node
	: public virtual Object
{
	static constexpr int16_t ATTRIBUTE_NODE { 2 };
	static constexpr int16_t CDATA_SECTION_NODE { 4 };
	static constexpr int16_t COMMENT_NODE { 8 };
	static constexpr int16_t DOCUMENT_FRAGMENT_NODE { 11 };
	static constexpr int16_t DOCUMENT_NODE { 9 };
	static constexpr int16_t DOCUMENT_POSITION_CONTAINED_BY { 16 };
	static constexpr int16_t DOCUMENT_POSITION_CONTAINS { 8 };
	static constexpr int16_t DOCUMENT_POSITION_DISCONNECTED { 1 };
	static constexpr int16_t DOCUMENT_POSITION_FOLLOWING { 4 };
	static constexpr int16_t DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC { 32 };
	static constexpr int16_t DOCUMENT_POSITION_PRECEDING { 2 };
	static constexpr int16_t DOCUMENT_TYPE_NODE { 10 };
	static constexpr int16_t ELEMENT_NODE { 1 };
	static constexpr int16_t ENTITY_NODE { 6 };
	static constexpr int16_t ENTITY_REFERENCE_NODE { 5 };
	static constexpr int16_t NOTATION_NODE { 12 };
	static constexpr int16_t PROCESSING_INSTRUCTION_NODE { 7 };
	static constexpr int16_t TEXT_NODE { 3 };

	virtual Node* appendChild(Node* arg0) = 0;
	virtual Node* cloneNode(bool arg0) = 0;
	virtual int16_t compareDocumentPosition(Node* arg0) = 0;
	virtual NamedNodeMap* getAttributes() = 0;
	virtual String* getBaseURI() = 0;
	virtual NodeList* getChildNodes() = 0;
	virtual Object* getFeature(String* arg0, String* arg1) = 0;
	virtual Node* getFirstChild() = 0;
	virtual Node* getLastChild() = 0;
	virtual String* getLocalName() = 0;
	virtual String* getNamespaceURI() = 0;
	virtual Node* getNextSibling() = 0;
	virtual String* getNodeName() = 0;
	virtual int16_t getNodeType() = 0;
	virtual String* getNodeValue() = 0;
	virtual Document* getOwnerDocument() = 0;
	virtual Node* getParentNode() = 0;
	virtual String* getPrefix() = 0;
	virtual Node* getPreviousSibling() = 0;
	virtual String* getTextContent() = 0;
	virtual Object* getUserData(String* arg0) = 0;
	virtual bool hasAttributes() = 0;
	virtual bool hasChildNodes() = 0;
	virtual Node* insertBefore(Node* arg0, Node* arg1) = 0;
	virtual bool isDefaultNamespace(String* arg0) = 0;
	virtual bool isEqualNode(Node* arg0) = 0;
	virtual bool isSameNode(Node* arg0) = 0;
	virtual bool isSupported(String* arg0, String* arg1) = 0;
	virtual String* lookupNamespaceURI(String* arg0) = 0;
	virtual String* lookupPrefix(String* arg0) = 0;
	virtual void normalize() = 0;
	virtual Node* removeChild(Node* arg0) = 0;
	virtual Node* replaceChild(Node* arg0, Node* arg1) = 0;
	virtual void setNodeValue(String* arg0) = 0;
	virtual void setPrefix(String* arg0) = 0;
	virtual void setTextContent(String* arg0) = 0;
	virtual Object* setUserData(String* arg0, Object* arg1, UserDataHandler* arg2) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
