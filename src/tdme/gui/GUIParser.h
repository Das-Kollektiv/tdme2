#pragma once

#include <map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/GUIParserException.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/utils/fwd-tdme.h>


#include <ext/tinyxml/tinyxml.h>

using std::map;
using std::vector;

using tdme::gui::elements::GUIElement;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUIParserException;
using tdme::ext::tinyxml::TiXmlElement;
using tdme::os::filesystem::FileSystemException;

/** 
 * GUI parser 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::GUIParser final
{

private:
	static map<string, GUIElement*> elements;

public:

	/** 
	 * Parses a GUI XML file
	 * @param pathName path name
	 * @param fileName file name
	 * @return GUI screen node
	 * @throws GUIParserException
	 * @throws FileSystemException
	 */
	static GUIScreenNode* parse(const string& pathName, const string& fileName) throw (GUIParserException, FileSystemException);

	/** 
	 * Parses a GUI XML content
	 * @param xml xml
	 * @return GUI screen node
	 * @throws GUIParserException
	 * @throws FileSystemException
	 */
	static GUIScreenNode* parse(const string& xml) throw (GUIParserException, FileSystemException);

	/** 
	 * Parses a GUI XML file into parent node
	 * @param parentNode parent node
	 * @param pathName path name
	 * @param fileName file name
	 * @throws GUIParserException
	 * @throws FileSystemException
	 */
	static void parse(GUIParentNode* parentNode, const string& pathName, const string& fileName) throw (GUIParserException, FileSystemException);

	/** 
	 * Parses a GUI XML content into parent node
	 * @param parentNode parent node
	 * @param xml xml
	 * @throws GUIParserException
	 * @throws FileSystemException
	 */
	static void parse(GUIParentNode* parentNode, const string& xml) throw (GUIParserException, FileSystemException);

private:

	/** 
	 * Parse GUI node
	 * @param guiParentNode gui parent node
	 * @param xmlParentNode xml parent node
	 * @param guiElement gui element
	 * @throws GUIParserException
	 * @throws FileSystemException
	 */
	static void parseGUINode(GUIParentNode* guiParentNode, TiXmlElement* xmlParentNode, GUIElement* guiElement) throw (GUIParserException, FileSystemException);

	/** 
	 * Returns immediate children tags
	 * @param parent parent
	 * @param name name
	 * @return children of parent node with given name
	 */
	static const vector<TiXmlElement*> getChildrenByTagName(TiXmlElement* parent, const char* name);

	/** 
	 * Get inner XML
	 * @param node node
	 * @return string
	 */
	static const string getInnerXml(TiXmlElement* node);

	/**
	 * Parse template
	 * @param guiParentNode GUI parent node
	 * @param node template xml node
	 * @param _template template
	 * @param attributes attributes
	 * @param guiElement GUI element
	 */
	static void parseTemplate(GUIParentNode* guiParentNode, TiXmlElement* node, const string& _template, map<string, string>& attributes, GUIElement* guiElement);

public:

	/** 
	 * Unescape quotes
	 * @param str string
	 * @return string with unescaped quotes
	 */
	static const string unescapeQuotes(const string& str);

	/**
	 * Escape quotes
	 * @param str string
	 * @return string with escaped quotes
	 */
	static const string escapeQuotes(const string& str);

	/** 
	 * Add GUI element
	 * @param guiElement guiElement
	 * @throws GUIParserException
	 * @throws FileSystemException
	 */
	static void addElement(GUIElement* guiElement) throw (GUIParserException, FileSystemException);

	/**
	 * Initialize GUI elements
	 */
	static void initialize();
};
