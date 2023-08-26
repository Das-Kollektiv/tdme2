#pragma once

#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/gui/effects/fwd-tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/GUIParserException.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/Properties.h>

#include <ext/tinyxml/tinyxml.h>

using std::unordered_map;
using std::vector;

using tdme::engine::logics::Context;
using tdme::gui::effects::GUIEffect;
using tdme::gui::elements::GUIElement;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUIParserException;
using tdme::os::filesystem::FileSystemException;
using tdme::utilities::MiniScript;
using tdme::utilities::Properties;

using tinyxml::TiXmlElement;

/**
 * GUI parser
 * @author Andreas Drewke
 */
class tdme::gui::GUIParser final
{

private:
	STATIC_DLL_IMPEXT static unordered_map<string, GUIElement*>* elements;
	STATIC_DLL_IMPEXT static Properties* engineThemeProperties;
	STATIC_DLL_IMPEXT static Properties* projectThemeProperties;

	static constexpr int FONTSIZE_FALLBACK { 14 };

public:

	/**
	 * @return engine theme properties
	 */
	inline static const Properties* getEngineThemeProperties() {
		return engineThemeProperties;
	}

	/**
	 * @return project theme properties
	 */
	inline static const Properties* getProjectThemeProperties() {
		return projectThemeProperties;
	}

	/**
	 * Parses a XML file and returns root node as string
	 * @param pathName path name
	 * @param fileName file name
	 * @throws tdme::gui::GUIParserException
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static const string getRootNode(const string& pathName, const string& fileName);

	/**
	 * Parses a XML string and returns root node as string
	 * @param xml xml
	 * @throws tdme::gui::GUIParserException
	 */
	static const string getRootNode(const string& xml);

	/**
	 * Parses a GUI XML file
	 * @param pathName path name
	 * @param fileName file name
	 * @param variables variables
	 * @param miniScriptArguments mini script arguments
	 * @param context application logic context
	 * @return GUI screen node
	 * @throws tdme::gui::GUIParserException
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static GUIScreenNode* parse(const string& pathName, const string& fileName, const unordered_map<string, string>& variables = {}, const MiniScript::ScriptVariable& miniScriptArguments = MiniScript::ScriptVariable(), Context* context = nullptr);

	/**
	 * Parses a GUI XML content
	 * @param xml xml
	 * @param variables variables
	 * @param pathName path name
	 * @param fileName file name
	 * @param miniScriptArguments mini script arguments
	 * @param context application logic context
	 * @return GUI screen node
	 * @throws tdme::gui::GUIParserException
	 * @throws tdme::os::filesystem::FileSystemException
	 */
	static GUIScreenNode* parse(const string& xml, const unordered_map<string, string>& variables = {}, const string& pathName = string(), const string& fileName = string(), const MiniScript::ScriptVariable& miniScriptArguments = MiniScript::ScriptVariable(), Context* context = nullptr);

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
	 * Parse GUI effect
	 * @param guiNode GUI node
	 * @param effectPrefix effect prefix
	 * @param requiresCondition requires condition
	 * @param node node
	 */
	static void parseEffect(GUINode* guiNode, const string& effectPrefix, bool requiresCondition, TiXmlElement* node);

	/**
	 * Parse GUI effect
	 * @param guiNode GUI node
	 * @param xmlParentNode xml parent node
	 */
	static void parseEffects(GUINode* guiNode, TiXmlElement* xmlParentNode);

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
	 * @param templateXML template xml
	 * @param attributes attributes
	 * @param guiElement GUI element
	 */
	static void parseTemplate(GUIParentNode* guiParentNode, const string& parentElementId, TiXmlElement* node, const string& templateXML, const unordered_map<string, string>& attributes, GUIElement* guiElement);

	/**
	 * Parse inner XML
	 * @param guiParentNode GUI parent node
	 * @param parentElementId parent element id
	 * @param node template xml node
	 * @param innerXML inner xml
	 * @param attributes attributes
	 * @param guiElement GUI element
	 */
	static void parseInnerXML(GUIParentNode* guiParentNode, const string& parentElementId, TiXmlElement* node, const string& innerXML, const unordered_map<string, string>& attributes, GUIElement* guiElement);

	/**
	 * Parse factor
	 * @param guiParentNode gui parent node
	 * @param factor factor
	 * @return factor
	 */
	static int parseFactor(GUIParentNode* guiParentNode, const string& factor);

	/**
	 * Parse integer
	 * @param value value
	 * @param defaultValue default value
	 * @return size
	 */
	static int parseInteger(const string& value, int defaultValue);

public:
	/**
	 * Parse template attributes
	 * @param templateXML template xml
	 * @param guiElement GUI element
	 * @return parsed template attributes
	 */
	static unordered_map<string, string> parseTemplateAttributes(const string& templateXML);

	/**
	 * Get inner XML from XML string
	 * @param xml xml
	 * @return string
	 */
	static const string getInnerXml(const string& xml);

	/**
	 * Unescape quotes and other special html characters
	 * @param str string
	 * @return string with unescaped quotes
	 */
	static const string unescape(const string& str);

	/**
	 * Escape quotes and other special html characters
	 * @param str string
	 * @return string with escaped quotes
	 */
	static const string escape(const string& str);

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

	/**
	 * Load project theme properties
	 * @param pathName path name
	 */
	static void loadProjectThemeProperties(const string& pathName);

};
