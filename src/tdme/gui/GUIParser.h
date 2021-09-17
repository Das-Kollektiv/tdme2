#pragma once

#include <map>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/GUIParserException.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/utilities/fwd-tdme.h>

#include <ext/tinyxml/tinyxml.h>

using std::map;
using std::unordered_map;
using std::vector;

using tdme::gui::elements::GUIElement;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUIParserException;
using tdme::os::filesystem::FileSystemException;
using tdme::utilities::Properties;

using tinyxml::TiXmlElement;

/**
 * GUI parser
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::GUIParser final
{

private:
	static map<string, GUIElement*>* elements;
	static Properties* themeProperties;

public:

	/**
	 * Parses a GUI XML file
	 * @param pathName path name
	 * @param fileName file name
	 * @param parameters parameters aka key value paris for substitution
	 * @return GUI screen node
	 * @throws tdme::gui::GUIParserException
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static GUIScreenNode* parse(const string& pathName, const string& fileName, const unordered_map<string, string>& parameters = unordered_map<string, string>());

	/**
	 * Parses a GUI XML content
	 * @param xml xml
	 * @param parameters parameters aka key value paris for substitution
	 * @param pathName path name
	 * @param fileName file name
	 * @return GUI screen node
	 * @throws tdme::gui::GUIParserException
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static GUIScreenNode* parse(const string& xml, const unordered_map<string, string>& parameters = unordered_map<string, string>(), const string& pathName = string(), const string& fileName = string());

	/**
	 * Parses a GUI XML file into parent node
	 * @param parentNode parent node
	 * @param pathName path name
	 * @param fileName file name
	 * @throws tdme::gui::GUIParserException
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void parse(GUIParentNode* parentNode, const string& pathName, const string& fileName);

	/**
	 * Parses a GUI XML content into parent node
	 * @param parentNode parent node
	 * @param xml xml
	 * @throws tdme::gui::GUIParserException
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void parse(GUIParentNode* parentNode, const string& xml);

private:

	/**
	 * Parse GUI node
	 * @param guiParentNode gui parent node
	 * @param parentElementId parent element id
	 * @param xmlParentNode xml parent node
	 * @param guiElement gui element
	 * @throws tdme::gui::GUIParserException
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void parseGUINode(GUIParentNode* guiParentNode, const string& parentElementId, TiXmlElement* xmlParentNode, GUIElement* guiElement);

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
	 * @param parentElementId parent element id
	 * @param node template xml node
	 * @param _template template
	 * @param attributes attributes
	 * @param guiElement GUI element
	 */
	static void parseTemplate(GUIParentNode* guiParentNode, const string& parentElementId, TiXmlElement* node, const string& _template, const unordered_map<string, string>& attributes, GUIElement* guiElement);

	/**
	 * Parse inner XML
	 * @param guiParentNode GUI parent node
	 * @param parentElementId parent element id
	 * @param node template xml node
	 * @param _template template
	 * @param attributes attributes
	 * @param guiElement GUI element
	 */
	static void parseInnerXML(GUIParentNode* guiParentNode, const string& parentElementId, TiXmlElement* node, const string& _template, const unordered_map<string, string>& attributes, GUIElement* guiElement);

	/**
	 * Parse factor
	 * @param guiParentNode gui parent node
	 * @param factor factor
	 * @return factor
	 */
	static int parseFactor(GUIParentNode* guiParentNode, const string& factor);

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
	 * @throws tdme::gui::GUIParserException
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static void addElement(GUIElement* guiElement);

	/**
	 * Initialize GUI elements
	 */
	static void initialize();

	/**
	 * Dispose GUI elements
	 */
	static void dispose();
};
