#pragma once

#include <unordered_map>
#include <vector>

#include <minitscript/minitscript/Library.h>
#include <minitscript/minitscript/MinitScript.h>

#include <agui/agui.h>
#include <agui/gui/effects/fwd-agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/GUIParserException.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/utilities/Properties.h>

#include <ext/tinyxml/tinyxml.h>

using std::unordered_map;
using std::vector;

// namespaces
namespace agui {
namespace gui {
	using ::minitscript::minitscript::Library;
	using ::minitscript::minitscript::MinitScript;

	using tinyxml::TiXmlElement;

	using ::agui::gui::effects::GUIEffect;
	using ::agui::gui::elements::GUIElement;
	using ::agui::gui::nodes::GUINode;
	using ::agui::gui::nodes::GUIParentNode;
	using ::agui::gui::nodes::GUIScreenNode;
	using ::agui::gui::GUIParserException;
	using ::agui::os::filesystem::FileSystemException;
	using ::agui::utilities::Properties;
}
}

/**
 * GUI parser
 * @author Andreas Drewke
 */
class agui::gui::GUIParser final
{

private:
	AGUI_STATIC_DLL_IMPEXT static unordered_map<string, GUIElement*> elements;
	AGUI_STATIC_DLL_IMPEXT static Properties aguiThemeProperties;
	AGUI_STATIC_DLL_IMPEXT static Properties engineThemeProperties;
	AGUI_STATIC_DLL_IMPEXT static Properties projectThemeProperties;

	static constexpr int FONTSIZE_FALLBACK { 14 };

public:
	/**
	 * Get application root path name
	 * @param fileName file name
	 * @return application root path name
	 */
	static const string getApplicationRootPathName(const string& fileName);

	/**
	 * Get application sub path name
	 * @param fileName application sub path name
	 * @return application sub path name
	 */
	static const string getApplicationSubPathName(const string& fileName);

	/**
	 * @return engine theme properties
	 */
	inline static const Properties* getEngineThemeProperties() {
		return &engineThemeProperties;
	}

	/**
	 * @return project theme properties
	 */
	inline static const Properties* getProjectThemeProperties() {
		return &projectThemeProperties;
	}

	/**
	 * Parses a XML file and returns root node as string
	 * @param pathName path name
	 * @param fileName file name
	 * @throws agui::gui::GUIParserException
	 * @throws agui::os::filesystem::FileSystemException
	 */
	static const string getRootNode(const string& pathName, const string& fileName);

	/**
	 * Parses a XML string and returns root node as string
	 * @param xml xml
	 * @throws agui::gui::GUIParserException
	 */
	static const string getRootNode(const string& xml);

	/**
	 * Parses a GUI XML file
	 * @param pathName path name
	 * @param fileName file name
	 * @param variables variables
	 * @param scriptLibrary script library
	 * @param scriptArguments script arguments
	 * @return GUI screen node
	 * @throws agui::gui::GUIParserException
	 * @throws agui::os::filesystem::FileSystemException
	 */
	static GUIScreenNode* parse(const string& pathName, const string& fileName, const unordered_map<string, string>& variables = {}, Library* scriptLibrary = nullptr, const MinitScript::Variable& scriptArguments = MinitScript::Variable());

	/**
	 * Parses a GUI XML content
	 * @param xml xml
	 * @param variables variables
	 * @param pathName path name
	 * @param fileName file name
	 * @param scriptLibrary script library
	 * @param scriptArguments script arguments
	 * @return GUI screen node
	 * @throws agui::gui::GUIParserException
	 * @throws agui::os::filesystem::FileSystemException
	 */
	static GUIScreenNode* parse(const string& xml, const unordered_map<string, string>& variables = {}, const string& pathName = string(), const string& fileName = string(), Library* scriptLibrary = nullptr, const MinitScript::Variable& scriptArguments = MinitScript::Variable());

	/**
	 * Parses a GUI XML file into parent node
	 * @param parentNode parent node
	 * @param pathName path name
	 * @param fileName file name
	 * @throws agui::gui::GUIParserException
	 * @throws agui::os::filesystem::FileSystemException
	 */
	static void parse(GUIParentNode* parentNode, const string& pathName, const string& fileName);

	/**
	 * Parses a GUI XML content into parent node
	 * @param parentNode parent node
	 * @param xml xml
	 * @throws agui::gui::GUIParserException
	 * @throws agui::os::filesystem::FileSystemException
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
	 * @throws agui::gui::GUIParserException
	 * @throws agui::os::filesystem::FileSystemException
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
	 * @throws agui::gui::GUIParserException
	 * @throws agui::os::filesystem::FileSystemException
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
