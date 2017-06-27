// Generated from /tdme/src/tdme/gui/GUIParser.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <org/w3c/dom/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using org::w3c::dom::Element;
using org::w3c::dom::Node;
using tdme::gui::elements::GUIElement;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap;


struct default_init_tag;

/** 
 * GUI parser 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::GUIParser final
	: public Object
{

public:
	typedef Object super;

private:
	static _HashMap* elements;

public:

	/** 
	 * Parses a GUI XML file
	 * @param path name
	 * @param file name
	 * @return GUI screen node
	 * @throws IOException
	 */
	static GUIScreenNode* parse(String* pathName, String* fileName) /* throws(Exception) */;

	/** 
	 * Parses a GUI XML content
	 * @param xml
	 * @return GUI screen node
	 * @throws IOException
	 */
	static GUIScreenNode* parse(String* xml) /* throws(Exception) */;

	/** 
	 * Parses a GUI XML file into parent node
	 * @param parent node
	 * @param path name
	 * @param file name
	 * @throws IOException
	 */
	static void parse(GUIParentNode* parentNode, String* pathName, String* fileName) /* throws(Exception) */;

	/** 
	 * Parses a GUI XML content into parent node
	 * @param parent node
	 * @param xml
	 * @throws IOException
	 */
	static void parse(GUIParentNode* parentNode, String* xml) /* throws(Exception) */;

private:

	/** 
	 * Parse GUI node
	 * @param gui parent node
	 * @param xml parent node
	 * @param gui element
	 * @throws Exception
	 */
	static void parseGUINode(GUIParentNode* guiParentNode, Element* xmlParentNode, GUIElement* guiElement) /* throws(Exception) */;

	/** 
	 * Returns immediate children tags
	 * @param parent
	 * @return children
	 */
	static _ArrayList* getChildrenTags(Element* parent);

	/** 
	 * Get inner XML
	 * see: http://stackoverflow.com/questions/3300839/get-a-nodes-inner-xml-as-string-in-java-dom
	 * @param node
	 * @return string
	 */
	static String* getInnerXml(Node* node);

public:

	/** 
	 * Unescape quotes
	 * @param string
	 * @return string with unescaped quotes
	 */
	static String* unescapeQuotes(String* string);

	/** 
	 * Escape quotes
	 * @param string
	 * @return string with escaped quotes
	 */
	static String* escapeQuotes(String* string);

	/** 
	 * Add GUI element
	 * @param guiElement
	 * @throws GUIParserException
	 */
	static void addElement(GUIElement* guiElement) /* throws(GUIParserException) */;

	// Generated
	GUIParser();
protected:
	GUIParser(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
};
