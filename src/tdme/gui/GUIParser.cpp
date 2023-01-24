#include <tdme/gui/GUIParser.h>

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/gui/effects/GUIColorEffect.h>
#include <tdme/gui/effects/GUIPositionEffect.h>
#include <tdme/gui/elements/GUIButton.h>
#include <tdme/gui/elements/GUICheckbox.h>
#include <tdme/gui/elements/GUIContextMenu.h>
#include <tdme/gui/elements/GUIContextMenuItem.h>
#include <tdme/gui/elements/GUIDropDown.h>
#include <tdme/gui/elements/GUIDropDownOption.h>
#include <tdme/gui/elements/GUIElement.h>
#include <tdme/gui/elements/GUIImageButton.h>
#include <tdme/gui/elements/GUIInput.h>
#include <tdme/gui/elements/GUIKnob.h>
#include <tdme/gui/elements/GUIMenuHeader.h>
#include <tdme/gui/elements/GUIMenuHeaderItem.h>
#include <tdme/gui/elements/GUIMenuItem.h>
#include <tdme/gui/elements/GUIMenuSeparator.h>
#include <tdme/gui/elements/GUIMoveable.h>
#include <tdme/gui/elements/GUIProgressBar.h>
#include <tdme/gui/elements/GUIRadioButton.h>
#include <tdme/gui/elements/GUIScrollArea.h>
#include <tdme/gui/elements/GUISelectorH.h>
#include <tdme/gui/elements/GUISelectorHOption.h>
#include <tdme/gui/elements/GUISelectBox.h>
#include <tdme/gui/elements/GUISelectBoxOption.h>
#include <tdme/gui/elements/GUISelectBoxParentOption.h>
#include <tdme/gui/elements/GUISliderH.h>
#include <tdme/gui/elements/GUISliderV.h>
#include <tdme/gui/elements/GUIStyledInput.h>
#include <tdme/gui/elements/GUITab.h>
#include <tdme/gui/elements/GUITabs.h>
#include <tdme/gui/elements/GUITabsContent.h>
#include <tdme/gui/elements/GUITabsHeader.h>
#include <tdme/gui/elements/GUITabContent.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIGradientNode.h>
#include <tdme/gui/nodes/GUIHorizontalScrollbarInternalNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUIInputInternalNode.h>
#include <tdme/gui/nodes/GUILayerNode.h>
#include <tdme/gui/nodes/GUILayoutNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINode_Alignments.h>
#include <tdme/gui/nodes/GUINode_AlignmentHorizontal.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIPanelNode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUISpaceNode.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/nodes/GUIStyledTextNodeController.h>
#include <tdme/gui/nodes/GUITableCellNode.h>
#include <tdme/gui/nodes/GUITableNode.h>
#include <tdme/gui/nodes/GUITableRowNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/nodes/GUIVerticalScrollbarInternalNode.h>
#include <tdme/gui/nodes/GUIVideoNode.h>
#include <tdme/gui/GUIParserException.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTools.h>

#include <ext/tinyxml/tinyxml.h>

using std::string;
using std::to_string;
using std::unordered_map;

using tdme::gui::effects::GUIColorEffect;
using tdme::gui::effects::GUIPositionEffect;
using tdme::gui::elements::GUIButton;
using tdme::gui::elements::GUICheckbox;
using tdme::gui::elements::GUIContextMenu;
using tdme::gui::elements::GUIContextMenuItem;
using tdme::gui::elements::GUIDropDown;
using tdme::gui::elements::GUIDropDownOption;
using tdme::gui::elements::GUIElement;
using tdme::gui::elements::GUIImageButton;
using tdme::gui::elements::GUIInput;
using tdme::gui::elements::GUIKnob;
using tdme::gui::elements::GUIMenuHeader;
using tdme::gui::elements::GUIMenuHeaderItem;
using tdme::gui::elements::GUIMenuItem;
using tdme::gui::elements::GUIMenuSeparator;
using tdme::gui::elements::GUIMoveable;
using tdme::gui::elements::GUIProgressBar;
using tdme::gui::elements::GUIRadioButton;
using tdme::gui::elements::GUIScrollArea;
using tdme::gui::elements::GUISelectorH;
using tdme::gui::elements::GUISelectorHOption;
using tdme::gui::elements::GUISelectBox;
using tdme::gui::elements::GUISelectBoxOption;
using tdme::gui::elements::GUISelectBoxParentOption;
using tdme::gui::elements::GUISliderH;
using tdme::gui::elements::GUISliderV;
using tdme::gui::elements::GUIStyledInput;
using tdme::gui::elements::GUITab;
using tdme::gui::elements::GUITabs;
using tdme::gui::elements::GUITabsContent;
using tdme::gui::elements::GUITabsHeader;
using tdme::gui::elements::GUITabContent;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIGradientNode;
using tdme::gui::nodes::GUIHorizontalScrollbarInternalNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUIInputInternalNode;
using tdme::gui::nodes::GUILayerNode;
using tdme::gui::nodes::GUILayoutNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIPanelNode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUISpaceNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUIStyledTextNodeController;
using tdme::gui::nodes::GUITableCellNode;
using tdme::gui::nodes::GUITableNode;
using tdme::gui::nodes::GUITableRowNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::nodes::GUIVerticalScrollbarInternalNode;
using tdme::gui::nodes::GUIVideoNode;
using tdme::gui::GUIParser;
using tdme::gui::GUIParserException;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::misc::Tools;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::Properties;
using tdme::utilities::StringTools;

using tinyxml::TiXmlAttribute;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

map<string, GUIElement*>* GUIParser::elements = new map<string, GUIElement*>();
Properties* GUIParser::engineThemeProperties = new Properties();
Properties* GUIParser::projectThemeProperties = new Properties();

const string GUIParser::getRootNode(const string& pathName, const string& fileName) {
	return getRootNode(FileSystem::getInstance()->getContentAsString(pathName, fileName));
}

const string GUIParser::getRootNode(const string& xml) {
	//
	TiXmlDocument xmlDocument;
	xmlDocument.Parse(xml.c_str());
	if (xmlDocument.Error() == true) {
		string message = string("GUIParser::getRootNode(): Could not parse XML. Error='") + string(xmlDocument.ErrorDesc()) + "':\n\n" + xml;
		Console::println(message);
		throw GUIParserException(message);
	}
	//
	TiXmlElement* xmlRoot = xmlDocument.RootElement();
	return string(xmlRoot->Value());
}


GUIScreenNode* GUIParser::parse(const string& pathName, const string& fileName, const unordered_map<string, string>& parameters)
{
	return parse(FileSystem::getInstance()->getContentAsString(pathName, fileName), parameters, pathName, fileName);
}

GUIScreenNode* GUIParser::parse(const string& xml, const unordered_map<string, string>& parameters, const string& pathName, const string& fileName)
{
	auto applicationRootPath = Tools::getApplicationRootPathName(pathName);
	auto applicationSubPathName = Tools::getApplicationSubPathName(pathName);
	auto themeProperties = applicationSubPathName == "project"?projectThemeProperties:engineThemeProperties;

	// replace with parameters
	auto newXML = xml;
	for (auto& parameterIt: parameters) {
		newXML = StringTools::replace(newXML, "{$" + parameterIt.first + "}", escapeQuotes(parameterIt.second));
	}
	// replace with theme properties
	for (auto& themePropertyIt: themeProperties->getProperties()) {
		newXML = StringTools::replace(newXML, "{$" + themePropertyIt.first + "}", escapeQuotes(themePropertyIt.second));
	}

	//
	TiXmlDocument xmlDocument;
	xmlDocument.Parse(newXML.c_str());
	if (xmlDocument.Error() == true) {
		string message = string("GUIParser::parse(): Could not parse XML. Error='") + string(xmlDocument.ErrorDesc()) + "':\n\n" + newXML;
		Console::println(message);
		throw GUIParserException(message);
	}
	TiXmlElement* xmlRoot = xmlDocument.RootElement();
	GUIScreenNode* guiScreenNode = nullptr;
	if (string(xmlRoot->Value()) != string("screen")) {
		throw GUIParserException("XML root node must be <screen>");
	}

	//
	guiScreenNode = new GUIScreenNode(
		(pathName.empty() == false?pathName + "/":"") + fileName,
		applicationRootPath.empty() == true?".":FileSystem::getInstance()->getCanonicalPath(applicationRootPath, ""),
		applicationSubPathName,
		string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("id"))),
		GUINode::createFlow(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("flow")))),
		GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("overflow-x")))),
		GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("overflow-y")))),
		GUINode::createAlignments(
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("horizontal-align"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("vertical-align")))
		),
		GUINode::createRequestedConstraints(
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("left"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("top"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("width"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("height"))),
			parseFactor(nullptr, StringTools::trim(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("factor")))))
		),
		GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
		"",
		GUINode::createScale9Grid(
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-image-scale9"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-image-scale9-left"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-image-scale9-top"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-image-scale9-right"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-image-scale9-bottom")))
		),
		GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
		GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
		GUINode::createBorder(
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-left"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-top"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-right"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-bottom"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-color"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-color-left"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-color-top"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-color-right"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-color-bottom")))
		),
		GUINode::createPadding(
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("padding"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("padding-left"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("padding-top"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("padding-right"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("padding-bottom")))
		),
		GUIScreenNode::createSizeConstraints(
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("min-width"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("min-height"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("max-width"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("max-height")))
		),
		GUINode::createConditions(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("show-on")))),
		GUINode::createConditions(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("hide-on")))),
		unescapeQuotes(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("tooltip")))),
		StringTools::equalsIgnoreCase(StringTools::trim(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("scrollable")))), "true"),
		StringTools::equalsIgnoreCase(StringTools::trim(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("popup")))), "true")
	);
	// workaround for having GUINode constructor to be called before GUIScreenNode constructor
	// so GUIScreenNode::applicationRootPath is not available at GUIScreenNode::GUINode construction time
	guiScreenNode->setBackgroundImage(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-image"))));
	parseGUINode(guiScreenNode, string(), xmlRoot, nullptr);
	guiScreenNode->setConditionsMet();

	//
	vector<GUINode*> childControllerNodes;
	guiScreenNode->getChildControllerNodes(childControllerNodes);
	for (auto node: childControllerNodes) {
		node->getController()->onSubTreeChange();
	}

	//
	return guiScreenNode;
}

void GUIParser::parse(GUIParentNode* parentNode, const string& pathName, const string& fileName)
{
	string xml = FileSystem::getInstance()->getContentAsString(pathName, fileName);
	parse(parentNode, xml);
}

void GUIParser::parse(GUIParentNode* parentNode, const string& xml)
{
	//
	auto themeProperties = parentNode->getScreenNode()->getApplicationSubPathName() == "project"?projectThemeProperties:engineThemeProperties;
	// replace with parameters
	auto newXML = xml;
	// replace with theme properties
	for (auto& themePropertyIt: themeProperties->getProperties()) {
		newXML = StringTools::replace(newXML, "{$" + themePropertyIt.first + "}", escapeQuotes(themePropertyIt.second));
	}

	TiXmlDocument xmlDocument;
	xmlDocument.Parse((string("<gui-element>") + newXML + string("</gui-element>")).c_str());
	if (xmlDocument.Error() == true) {
		auto message = "GUIParser::parse(): Could not parse XML. Error='" + string(xmlDocument.ErrorDesc()) + "':\n\n" + newXML;
		Console::println(message);
		throw GUIParserException(message);
	}
	TiXmlElement* xmlNode = xmlDocument.RootElement();
	parseGUINode(parentNode, string(), xmlNode, nullptr);
}

void GUIParser::parseEffect(GUINode* guiNode, const string& effectPrefix, bool requiresCondition, TiXmlElement* node) {
	GUIEffect* effect = nullptr;
	auto type = string(AVOID_NULLPTR_STRING(node->Attribute("type")));
	if (type == "color") {
		effect = new GUIColorEffect(guiNode);
		static_cast<GUIColorEffect*>(effect)->setPersistant(StringTools::equalsIgnoreCase(StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("persistant")))), "true"));
		static_cast<GUIColorEffect*>(effect)->setColorMul(GUIColor(AVOID_NULLPTR_STRING(node->Attribute("effect-color-mul"))));
		static_cast<GUIColorEffect*>(effect)->setColorAdd(GUIColor(AVOID_NULLPTR_STRING(node->Attribute("effect-color-add"))));
		static_cast<GUIColorEffect*>(effect)->setStartColorMul(GUIColor(AVOID_NULLPTR_STRING(node->Attribute("start-effect-color-mul"))));
		static_cast<GUIColorEffect*>(effect)->setStartColorAdd(GUIColor(AVOID_NULLPTR_STRING(node->Attribute("start-effect-color-add"))));
		static_cast<GUIColorEffect*>(effect)->setTimeTotal(Float::parse(node->Attribute("time")));
		static_cast<GUIColorEffect*>(effect)->setRepeat(node->Attribute("repeat") == nullptr?0:Integer::parse(node->Attribute("repeat")));
		static_cast<GUIColorEffect*>(effect)->setYoyo(node->Attribute("yoyo") == nullptr?false:StringTools::toLowerCase(StringTools::trim(node->Attribute("yoyo"))) == "true");
		guiNode->addEffect(
			effectPrefix + (requiresCondition == true?string(".") + type + ".on." + AVOID_NULLPTR_STRING(node->Attribute("on")):string()),
			effect
		);
	} else
	if (type == "position") {
		effect = new GUIPositionEffect(guiNode);
		static_cast<GUIPositionEffect*>(effect)->setPersistant(StringTools::equalsIgnoreCase(StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("persistant")))), "true"));
		static_cast<GUIPositionEffect*>(effect)->setPositionX(Integer::parse(AVOID_NULLPTR_STRING(node->Attribute("effect-position-x"))));
		static_cast<GUIPositionEffect*>(effect)->setPositionY(Integer::parse(AVOID_NULLPTR_STRING(node->Attribute("effect-position-y"))));
		static_cast<GUIPositionEffect*>(effect)->setStartPositionX(Integer::parse(AVOID_NULLPTR_STRING(node->Attribute("start-effect-position-x"))));
		static_cast<GUIPositionEffect*>(effect)->setStartPositionY(Integer::parse(AVOID_NULLPTR_STRING(node->Attribute("start-effect-position-y"))));
		static_cast<GUIPositionEffect*>(effect)->setTimeTotal(Float::parse(node->Attribute("time")));
		static_cast<GUIPositionEffect*>(effect)->setRepeat(node->Attribute("repeat") == nullptr?0:Integer::parse(node->Attribute("repeat")));
		static_cast<GUIPositionEffect*>(effect)->setYoyo(node->Attribute("yoyo") == nullptr?false:StringTools::toLowerCase(StringTools::trim(node->Attribute("yoyo"))) == "true");
		guiNode->addEffect(
			effectPrefix + (requiresCondition == true?string(".") + type + ".on." + AVOID_NULLPTR_STRING(node->Attribute("on")):string()),
			effect
		);
	}
	auto action = string(AVOID_NULLPTR_STRING(node->Attribute("action")));
	if (effect != nullptr && action.empty() == false) {
		class EffectAction: public virtual Action
		{
		public:
			EffectAction(GUIScreenNode* guiScreenNode, const string& expression): guiScreenNode(guiScreenNode), expression(expression) {
			}
			void performAction() override {
				GUIElementNode::executeExpression(guiScreenNode, expression);
			}
		private:
			GUIScreenNode* guiScreenNode;
			string expression;
		};
		effect->setAction(new EffectAction(guiNode->getScreenNode(), action));
	}
}

void GUIParser::parseEffects(GUINode* guiNode, TiXmlElement* xmlParentNode) {
	for (auto node = xmlParentNode->FirstChildElement(); node != nullptr; node = node->NextSiblingElement()) {
		string nodeTagName = string(node->Value());
		if (nodeTagName == "effect-in") {
			parseEffect(guiNode, "tdme.xmleffect.in", true, node);
		} else
		if (nodeTagName == "effect-out") {
			parseEffect(guiNode, "tdme.xmleffect.out", true, node);
		} else
		if (nodeTagName == "effect-default") {
			parseEffect(guiNode, "tdme.xmleffect.default", false, node);
		}
	}
}

void GUIParser::parseGUINode(GUIParentNode* guiParentNode, const string& parentElementId, TiXmlElement* xmlParentNode, GUIElement* guiElement)
{
	auto themeProperties = guiParentNode->getScreenNode()->getApplicationSubPathName() == "project"?projectThemeProperties:engineThemeProperties;
	GUINodeController* guiElementController = nullptr;
	auto guiElementControllerInstalled = false;
	parseEffects(guiParentNode, xmlParentNode);
	for (auto node = xmlParentNode->FirstChildElement(); node != nullptr; node = node->NextSiblingElement()) {
		{
			string nodeTagName = string(node->Value());
			if (nodeTagName == "defaults") {
				// no op
			} else
			if (nodeTagName == "effect-in") {
				parseEffect(guiParentNode, "tdme.xmleffect.in", true, node);
			} else
			if (nodeTagName == "effect-out") {
				parseEffect(guiParentNode, "tdme.xmleffect.out", true, node);
			} else
			if (nodeTagName == "effect-default") {
				parseEffect(guiParentNode, "tdme.xmleffect.default", false, node);
			} else
			if (nodeTagName == "panel") {
				auto guiPanelNode = new GUIPanelNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(node->Attribute("overflow-x")))),
					GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(node->Attribute("overflow-y")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor(themeProperties->get("color.panel", "#F0F0F0"))),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip")))),
					GUILayoutNode::createAlignment(string(AVOID_NULLPTR_STRING(node->Attribute("alignment"))))
				);
				guiParentNode->addSubNode(guiPanelNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiPanelNode);
					if (guiElementController != nullptr) {
						guiPanelNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseGUINode(guiPanelNode, string(), node, nullptr);
			} else
			if (nodeTagName == "layer") {
				auto guiLayerNode = new GUILayerNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(node->Attribute("overflow-x")))),
					GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(node->Attribute("overflow-y")))),
					GUIElementNode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip"))))
				);
				guiParentNode->addSubNode(guiLayerNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiLayerNode);
					if (guiElementController != nullptr) {
						guiLayerNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseGUINode(guiLayerNode, string(), node, nullptr);
			} else
			if (nodeTagName == "layout") {
				auto guiLayoutNode = new GUILayoutNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(node->Attribute("overflow-x")))),
					GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(node->Attribute("overflow-y")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip")))),
					GUILayoutNode::createAlignment(string(AVOID_NULLPTR_STRING(node->Attribute("alignment"))))
				);
				guiParentNode->addSubNode(guiLayoutNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiLayoutNode);
					if (guiElementController != nullptr) {
						guiLayoutNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseGUINode(guiLayoutNode, string(), node, nullptr);
			} else
			if (nodeTagName == "space") {
				auto guiSpaceNode = new GUISpaceNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip"))))
				);
				guiParentNode->addSubNode(guiSpaceNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiSpaceNode);
					if (guiElementController != nullptr) {
						guiSpaceNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseEffects(guiSpaceNode, node);
			} else
			if (nodeTagName == "element") {
				auto guiElementNode = new GUIElementNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(node->Attribute("overflow-x")))),
					GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(node->Attribute("overflow-y")))),
					GUIElementNode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("name")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("value")))),
					StringTools::equalsIgnoreCase(StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("selected")))), "true"),
					StringTools::equalsIgnoreCase(StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("disabled")))), "true"),
					StringTools::equalsIgnoreCase(StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("focusable")))), "true"),
					StringTools::equalsIgnoreCase(StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("ignore-events")))), "true"),
					string(AVOID_NULLPTR_STRING(node->Attribute("on-initialize"))),
					string(AVOID_NULLPTR_STRING(node->Attribute("on-mouse-click"))),
					string(AVOID_NULLPTR_STRING(node->Attribute("on-mouse-doubleclick"))),
					string(AVOID_NULLPTR_STRING(node->Attribute("on-mouse-over"))),
					string(AVOID_NULLPTR_STRING(node->Attribute("on-mouse-out"))),
					string(AVOID_NULLPTR_STRING(node->Attribute("on-change"))),
					parentElementId,
					string(AVOID_NULLPTR_STRING(node->Attribute("options")))
				);
				guiParentNode->addSubNode(guiElementNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiElementNode);
					if (guiElementController != nullptr) {
						guiElementNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseGUINode(guiElementNode, guiElementNode->getId(), node, nullptr);
			} else
			if (nodeTagName == "image") {
				auto guiImageNode = new GUIImageNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip")))),
					StringTools::trim(unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("src"))))),
					GUIImageNode::createRequestedDimensionConstraints(
						StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-scale")))),
						StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("vertical-scale"))))
					),
					node->Attribute("mirror-x") == nullptr?false:StringTools::toLowerCase(StringTools::trim(node->Attribute("mirror-x"))) == "true",
					node->Attribute("mirror-y") == nullptr?false:StringTools::toLowerCase(StringTools::trim(node->Attribute("mirror-y"))) == "true",
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("scale9-bottom")))
					),
					GUIImageNode::createClipping(
						string(AVOID_NULLPTR_STRING(node->Attribute("clipping"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("clipping-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("clipping-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("clipping-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("clipping-bottom")))
					),
					StringTools::trim(unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("mask"))))),
					Float::parse(string(AVOID_NULLPTR_STRING(node->Attribute("mask-max-value")))),
					node->Attribute("rotation") != nullptr?Float::parse(node->Attribute("rotation")):0.0f
				);
				guiParentNode->addSubNode(guiImageNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiImageNode);
					if (guiElementController != nullptr) {
						guiImageNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseEffects(guiImageNode, node);
			} else
			if (nodeTagName == "video") {
				auto guiVideoNode = new GUIVideoNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip")))),
					StringTools::trim(unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("src"))))),
					GUIImageNode::createRequestedDimensionConstraints(
						StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-scale")))),
						StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("vertical-scale"))))
					),
					node->Attribute("mirror-x") == nullptr?false:StringTools::toLowerCase(StringTools::trim(node->Attribute("mirror-x"))) == "true",
					node->Attribute("mirror-y") == nullptr?false:StringTools::toLowerCase(StringTools::trim(node->Attribute("mirror-y"))) == "true",
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("scale9-bottom")))
					),
					GUIImageNode::createClipping(
						string(AVOID_NULLPTR_STRING(node->Attribute("clipping"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("clipping-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("clipping-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("clipping-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("clipping-bottom")))
					),
					StringTools::trim(unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("mask"))))),
					Float::parse(string(AVOID_NULLPTR_STRING(node->Attribute("mask-max-value"))))
				);
				guiParentNode->addSubNode(guiVideoNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiVideoNode);
					if (guiElementController != nullptr) {
						guiVideoNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseEffects(guiVideoNode, node);
			} else
			if (nodeTagName == "gradient") {
				auto guiGradientNode = new GUIGradientNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip")))),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUIGradientNode::createClipping(
						string(AVOID_NULLPTR_STRING(node->Attribute("clipping"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("clipping-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("clipping-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("clipping-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("clipping-bottom")))
					),
					StringTools::trim(unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("mask"))))),
					Float::parse(string(AVOID_NULLPTR_STRING(node->Attribute("mask-max-value")))),
					GUIGradientNode::createGradient(string(AVOID_NULLPTR_STRING(node->Attribute("colors"))), string(AVOID_NULLPTR_STRING(node->Attribute("rotation"))))
				);
				guiParentNode->addSubNode(guiGradientNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiGradientNode);
					if (guiElementController != nullptr) {
						guiGradientNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseEffects(guiGradientNode, node);
			} else
			if (nodeTagName == "text") {
				auto guiTextNode = new GUITextNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip")))),
					StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("font")))),
					parseInteger(StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("size")))), FONTSIZE_FALLBACK),
					string(AVOID_NULLPTR_STRING(node->Attribute("color"))),
					MutableString(unescapeQuotes(string(StringTools::trim(AVOID_NULLPTR_STRING(node->Attribute("text"))))))
				);
				guiParentNode->addSubNode(guiTextNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiTextNode);
					if (guiElementController != nullptr) {
						guiTextNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseEffects(guiTextNode, node);
			} else
			if (nodeTagName == "styled-text") {
				auto guiStyledTextNode = new GUIStyledTextNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip")))),
					node->Attribute("preformatted") == nullptr?false:StringTools::toLowerCase(StringTools::trim(node->Attribute("preformatted"))) == "true",
					StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("font")))),
					parseInteger(StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("size")))), FONTSIZE_FALLBACK),
					string(AVOID_NULLPTR_STRING(node->Attribute("color"))),
					MutableString(unescapeQuotes(StringTools::trim(AVOID_NULLPTR_STRING(node->GetText()))))
				);
				guiParentNode->addSubNode(guiStyledTextNode);
				// TODO: we dont support element controllers here, actually later element controllers should
				//	only be attachable to element nodes
				//	here we attach the StyledText controller
				guiStyledTextNode->setController(new GUIStyledTextNodeController(guiStyledTextNode));
				guiStyledTextNode->getController()->initialize();
				parseEffects(guiStyledTextNode, node);
			} else
			if (nodeTagName == "table") {
				auto guiTableNode = new GUITableNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(node->Attribute("overflow-x")))),
					GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(node->Attribute("overflow-y")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip"))))
				);
				guiParentNode->addSubNode(guiTableNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiTableNode);
					if (guiElementController != nullptr) {
						guiTableNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseGUINode(guiTableNode, string(), node, nullptr);
			} else
			if (nodeTagName == "table-cell") {
				auto guiTableCellNode = new GUITableCellNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(node->Attribute("overflow-x")))),
					GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(node->Attribute("overflow-y")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUITableCellNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip")))),
					GUILayoutNode::createAlignment(string(AVOID_NULLPTR_STRING(node->Attribute("alignment"))))
				);
				guiParentNode->addSubNode(guiTableCellNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiTableCellNode);
					if (guiElementController != nullptr) {
						guiTableCellNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseGUINode(guiTableCellNode, string(), node, nullptr);
			} else
			if (nodeTagName == "table-row") {
				auto guiTableRowNode = new GUITableRowNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(node->Attribute("overflow-x")))),
					GUIParentNode::createOverflow(string(AVOID_NULLPTR_STRING(node->Attribute("overflow-y")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUITableRowNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip"))))
				);
				guiParentNode->addSubNode(guiTableRowNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiTableRowNode);
					if (guiElementController != nullptr) {
						guiTableRowNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseGUINode(guiTableRowNode, string(), node, nullptr);
			} else
			if (nodeTagName == "input-internal") {
				auto guiInputInternalNode = new GUIInputInternalNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip")))),
					StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("font")))),
					parseInteger(StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("size")))), FONTSIZE_FALLBACK),
					string(AVOID_NULLPTR_STRING(node->Attribute("color"))),
					string(AVOID_NULLPTR_STRING(node->Attribute("color-disabled"))),
					MutableString(unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("text"))))),
					GUIInputInternalNode::createMaxLength(string(AVOID_NULLPTR_STRING(node->Attribute("maxlength"))))
				);
				guiParentNode->addSubNode(guiInputInternalNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiInputInternalNode);
					if (guiElementController != nullptr) {
						guiInputInternalNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseEffects(guiInputInternalNode, node);
			} else
			if (nodeTagName == "vertical-scrollbar-internal") {
				auto guiVerticalScrollbarInternalNode = new GUIVerticalScrollbarInternalNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip")))),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("color-none"))), GUIColor::GUICOLOR_BLACK),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("color-mouseover"))), GUIColor::GUICOLOR_BLACK),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("color-dragging"))), GUIColor::GUICOLOR_BLACK)
				);
				guiParentNode->addSubNode(guiVerticalScrollbarInternalNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiVerticalScrollbarInternalNode);
					if (guiElementController != nullptr) {
						guiVerticalScrollbarInternalNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseEffects(guiVerticalScrollbarInternalNode, node);
			} else
			if (nodeTagName == "horizontal-scrollbar-internal") {
				auto guiHorizontalScrollbarInternalNode = new GUIHorizontalScrollbarInternalNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(node->Attribute("id") == nullptr?guiParentNode->getScreenNode()->allocateNodeId():node->Attribute("id")),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height"))),
						parseFactor(guiParentNode, StringTools::trim(string(AVOID_NULLPTR_STRING(node->Attribute("factor")))))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-mul"))), GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-image-effect-color-add"))), GUIColor::GUICOLOR_EFFECT_COLOR_ADD),
					GUINode::createBorder(
						string(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						string(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("tooltip")))),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("color-none"))), GUIColor::GUICOLOR_BLACK),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("color-mouseover"))), GUIColor::GUICOLOR_BLACK),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("color-dragging"))), GUIColor::GUICOLOR_BLACK)
				);
				guiParentNode->addSubNode(guiHorizontalScrollbarInternalNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiHorizontalScrollbarInternalNode);
					if (guiElementController != nullptr) {
						guiHorizontalScrollbarInternalNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseEffects(guiHorizontalScrollbarInternalNode, node);
			} else
			if (nodeTagName == "inner-xml") {
				unordered_map<string, string> attributes;
				parseInnerXML(
					guiParentNode,
					parentElementId,
					node,
					node->GetText(),
					attributes,
					nullptr
				);
			} else
			if (nodeTagName == "template") {
				auto src = string(AVOID_NULLPTR_STRING(node->Attribute("src")));
				unordered_map<string, string> attributes;
				parseTemplate(
					guiParentNode,
					parentElementId,
					node,
					FileSystem::getInstance()->getContentAsString(
						guiParentNode->getScreenNode()->getApplicationRootPathName() + "/" +
						FileSystem::getInstance()->getPathName(src),
						FileSystem::getInstance()->getFileName(src)
					),
					attributes,
					nullptr
				);
			} else {
				auto nodeTagNameString = nodeTagName;
				const auto guiElementIt = elements->find(nodeTagNameString);
				if (guiElementIt == elements->end()) {
					throw GUIParserException(
						"Unknown element '" +
						(nodeTagNameString) +
						"'"
					);
				}
				parseTemplate(
					guiParentNode,
					parentElementId,
					node,
					guiElementIt->second->getTemplate(
						guiParentNode->getScreenNode()->getApplicationRootPathName(),
						guiParentNode->getScreenNode()->getApplicationSubPathName(),
						AVOID_NULLPTR_STRING(node->Attribute("template"))
					),
					guiElementIt->second->getAttributes(guiParentNode->screenNode),
					guiElementIt->second
				);
			}
		}
	}
	if (guiElementController != nullptr) {
		guiElementController->initialize();
	}
}

void GUIParser::parseTemplate(GUIParentNode* parentNode, const string& parentElementId, TiXmlElement* node, const string& templateXML, const unordered_map<string, string>& attributes, GUIElement* guiElement) {
	//
	auto templateAttributes = attributes;
	{
		// parse defaults
		TiXmlDocument newTemplateDocument;
		newTemplateDocument.Parse(("<template>\n" + templateXML + "</template>\n").c_str());
		if (newTemplateDocument.Error() == true) {
			string message = "GUIParser::parseTemplate(): Could not parse XML. Error='" + string(newTemplateDocument.ErrorDesc()) + ":\n\n" + templateXML;
			Console::println(message);
			throw GUIParserException(message);
		}
		auto defaultsNodes = getChildrenByTagName(newTemplateDocument.RootElement(), "defaults");
		for (auto defaultsNode: defaultsNodes) {
			for (auto node = defaultsNode->FirstChildElement(); node != nullptr; node = node->NextSiblingElement()) {
				auto nodeTagName = string(node->Value());
				if (nodeTagName == "attribute") {
					auto name =	string(AVOID_NULLPTR_STRING(node->Attribute("name")));
					auto value = string(AVOID_NULLPTR_STRING(node->Attribute("value")));
					if (templateAttributes.find(name) == templateAttributes.end()) {
						templateAttributes[name] = value;
					}
				} else {
					Console::println("GUIParser::parseTemplate(): unknown defaults node: " + nodeTagName);
				}
			}
		}
	}

	//
	auto newTemplateXML = templateXML;

	//
	auto themeProperties = parentNode->getScreenNode()->getApplicationSubPathName() == "project"?projectThemeProperties:engineThemeProperties;

	// replace with theme properties
	for (auto& themePropertyIt: themeProperties->getProperties()) {
		newTemplateXML = StringTools::replace(newTemplateXML, "{$" + themePropertyIt.first + "}", escapeQuotes(themePropertyIt.second));
	}

	// replace attributes given
	for (TiXmlAttribute* attribute = node->FirstAttribute(); attribute != nullptr; attribute = attribute->Next()) {
		auto attributeKey = string(attribute->Name());
		auto attributeValue = string(attribute->Value());
		newTemplateXML = StringTools::replace(newTemplateXML, "{$" + attributeKey + "}", escapeQuotes(attributeValue));
	}

	// replace attributes from element
	for (auto newGuiElementAttributesIt : templateAttributes) {
		auto guiElementAttributeValue = escapeQuotes(newGuiElementAttributesIt.second);
		newTemplateXML = StringTools::replace(newTemplateXML, "{$" + newGuiElementAttributesIt.first + "}", guiElementAttributeValue);
	}

	// replace remaining unset parameters with empty spaces
	newTemplateXML = StringTools::regexReplace(newTemplateXML, "\\{\\$[a-zA-Z\\-_0-9]{1,}\\}", "");

	// replace inner XML
	newTemplateXML = StringTools::replace(newTemplateXML, "{__InnerXML__}", getInnerXml(node));

	// add root tag
	if (guiElement != nullptr) {
		newTemplateXML =  "<" + guiElement->getName() + ">\n" + newTemplateXML + "</" + guiElement->getName() + ">\n";
	} else {
		newTemplateXML =  "<template>\n" + newTemplateXML + "</template>\n";
	}

	// parse
	TiXmlDocument newTemplateDocument;
	newTemplateDocument.Parse(newTemplateXML.c_str());
	if (newTemplateDocument.Error() == true) {
		string message = "GUIParser::parseTemplate(): Could not parse XML. Error='" + string(newTemplateDocument.ErrorDesc()) + ":\n\n" + newTemplateXML;
		Console::println(message);
		throw GUIParserException(message);
	}
	parseGUINode(parentNode, parentElementId, newTemplateDocument.RootElement(), guiElement);
}

void GUIParser::parseInnerXML(GUIParentNode* parentNode, const string& parentElementId, TiXmlElement* node, const string& innerXML, const unordered_map<string, string>& attributes, GUIElement* guiElement) {
	auto newInnerXML = innerXML;
	auto newParentElementId = parentElementId;

	//
	auto themeProperties = parentNode->getScreenNode()->getApplicationSubPathName() == "project"?projectThemeProperties:engineThemeProperties;

	// replace with theme properties
	for (auto& themePropertyIt: themeProperties->getProperties()) {
		newInnerXML = StringTools::replace(newInnerXML, "{$" + themePropertyIt.first + "}", escapeQuotes(themePropertyIt.second));
	}

	// replace attributes given
	for (TiXmlAttribute* attribute = node->FirstAttribute(); attribute != nullptr; attribute = attribute->Next()) {
		auto attributeKey = string(attribute->Name());
		auto attributeValue = string(attribute->Value());
		newInnerXML = StringTools::replace(newInnerXML, "{$" + attributeKey + "}", escapeQuotes(attributeValue));
		// also store parent-id as such if given
		if (attributeKey == "parent-id") newParentElementId = attributeValue;
	}

	// replace attributes from element
	for (auto newGuiElementAttributesIt: attributes) {
		auto guiElementAttributeValue = escapeQuotes(newGuiElementAttributesIt.second);
		newInnerXML = StringTools::replace(newInnerXML, "{$" + newGuiElementAttributesIt.first + "}", guiElementAttributeValue);
	}

	// replace remaining unset parameters with empty spaces
	newInnerXML = StringTools::regexReplace(newInnerXML, "\\{\\$[a-zA-Z\\-_0-9]{1,}\\}", "");

	// replace inner XML
	newInnerXML = StringTools::replace(newInnerXML, "{__InnerXML__}", getInnerXml(node));

	// add root tag
	newInnerXML =  "<inner-xml>\n" + newInnerXML + "</inner-xml>\n";

	// parse
	TiXmlDocument newInnerXMLDocument;
	newInnerXMLDocument.Parse(newInnerXML.c_str());
	if (newInnerXMLDocument.Error() == true) {
		auto message = "GUIParser::parseInnerXML(): Could not parse XML. Error='" + string(newInnerXMLDocument.ErrorDesc()) + ":\n\n" + newInnerXML;
		throw GUIParserException(message);
	}
	parseGUINode(parentNode, newParentElementId, newInnerXMLDocument.RootElement(), guiElement);
}

int GUIParser::parseFactor(GUIParentNode* guiParentNode, const string& factor) {
	if (factor.empty() == true) {
		return 1;
	} else
	if (factor == "{__TreeDepth__}") {
		GUIElementNode* parentElementNode = nullptr;
		auto _guiParentNode = guiParentNode;
		while (_guiParentNode != nullptr) {
			parentElementNode = dynamic_cast<GUIElementNode*>(_guiParentNode);
			if (parentElementNode != nullptr) break;
			_guiParentNode = _guiParentNode->getParentNode();
		}
		auto childIdx = 0;
		while (parentElementNode != nullptr && parentElementNode->getParentElementNodeId().empty() == false) {
			parentElementNode = dynamic_cast<GUIElementNode*>(guiParentNode->getScreenNode()->getNodeById(parentElementNode->getParentElementNodeId()));
			if (parentElementNode != nullptr) {
				childIdx++;
			}
		}
		return childIdx;
	} else {
		return Integer::parse(factor);
	}
}

int GUIParser::parseInteger(const string& value, int defaultValue) {
	try {
		return Integer::parse(value);
	} catch (Exception& exception) {
		Console::println("GUIParser::parseInteger(): Unknown integer value: '" + value + "': using default value: " + to_string(defaultValue));
		return defaultValue;
	}
}

const vector<TiXmlElement*> GUIParser::getChildrenByTagName(TiXmlElement* parent, const char* name)
{
	vector<TiXmlElement*> elementList;
	for (auto child = parent->FirstChildElement(name); child != nullptr; child = child->NextSiblingElement(name)) {
		elementList.push_back(child);
	}
	return elementList;
}

const string GUIParser::getInnerXml(TiXmlElement* node)
{
	std::stringstream ss;
	auto firstChildNode = node->FirstChildElement();
	if (firstChildNode == nullptr) {
		if (node->GetText() != nullptr) {
			ss << node->GetText();
		}
	} else {
		for (auto childNode = firstChildNode; childNode != nullptr; childNode = childNode->NextSiblingElement()) {
			ss << *childNode;
		}
	}
	return ss.str();
}

const string GUIParser::unescapeQuotes(const string& str)
{
	string result;
	result = StringTools::replace(str, "&quot;", "\"");
	result = StringTools::replace(result, "&#39;", "'");
	return result;
}

const string GUIParser::escapeQuotes(const string& str)
{
	string result;
	result = StringTools::replace(str, "\"", "&quot;");
	result = StringTools::replace(result, "'", "&#39;");
	return result;
}

void GUIParser::addElement(GUIElement* guiElement)
{
	if (elements->find(guiElement->getName()) != elements->end()) {
		throw GUIParserException(
			"Element with given name '" +
			(guiElement->getName()) +
			"' already exists"
		);
	}
	elements->emplace(guiElement->getName(), guiElement);
}

void GUIParser::initialize()
{
	try {
		engineThemeProperties->load("./resources/engine/gui/themes", "theme_default.properties");
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		projectThemeProperties->load("./resources/project/gui/themes", "theme_default.properties");
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUICheckbox();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIRadioButton();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUISelectBox();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUISelectBoxOption();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUISelectBoxParentOption();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIDropDown();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIDropDownOption();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUITabs();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUITabsHeader();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUITab();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUITabsContent();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUITabContent();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIButton();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIInput();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIScrollArea();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUISliderH();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUISliderV();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIKnob();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIImageButton();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIProgressBar();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIMenuHeader();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIMenuHeaderItem();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIMenuItem();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIMenuSeparator();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIContextMenu();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIContextMenuItem();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUISelectorH();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUISelectorHOption();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIStyledInput();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		auto guiElement = new GUIMoveable();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void GUIParser::dispose() {
	for (auto& elementIt: *elements) {
		delete elementIt.second;
	}
	elements->clear();
	delete elements;
}

void GUIParser::loadProjectThemeProperties(const string& pathName) {
	try {
		projectThemeProperties->load(pathName + "/resources/project/gui/themes", "theme_default.properties");
	} catch (Exception& exception) {
		Console::print(string("GUIParser::loadProjectThemeProperties(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}
