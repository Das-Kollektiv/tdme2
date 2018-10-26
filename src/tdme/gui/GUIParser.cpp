#include <tdme/gui/GUIParser.h>

#include <map>
#include <string>

#include <tdme/gui/GUIParserException.h>
#include <tdme/gui/elements/GUIButton.h>
#include <tdme/gui/elements/GUICheckbox.h>
#include <tdme/gui/elements/GUIDropDown.h>
#include <tdme/gui/elements/GUIDropDownOption.h>
#include <tdme/gui/elements/GUIElement.h>
#include <tdme/gui/elements/GUIImageButton.h>
#include <tdme/gui/elements/GUIInput.h>
#include <tdme/gui/elements/GUIKnob.h>
#include <tdme/gui/elements/GUIProgressBar.h>
#include <tdme/gui/elements/GUIRadioButton.h>
#include <tdme/gui/elements/GUIScrollArea.h>
#include <tdme/gui/elements/GUIScrollAreaHorizontal.h>
#include <tdme/gui/elements/GUIScrollAreaVertical.h>
#include <tdme/gui/elements/GUISelectBox.h>
#include <tdme/gui/elements/GUISelectBoxMultiple.h>
#include <tdme/gui/elements/GUISelectBoxMultipleOption.h>
#include <tdme/gui/elements/GUISelectBoxOption.h>
#include <tdme/gui/elements/GUISliderH.h>
#include <tdme/gui/elements/GUISliderV.h>
#include <tdme/gui/elements/GUITab.h>
#include <tdme/gui/elements/GUITabContent.h>
#include <tdme/gui/elements/GUITabs.h>
#include <tdme/gui/elements/GUITabsContent.h>
#include <tdme/gui/elements/GUITabsHeader.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIHorizontalScrollbarInternalNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUIInputInternalNode.h>
#include <tdme/gui/nodes/GUILayoutNode.h>
#include <tdme/gui/nodes/GUIMultilineTextNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINode_Alignments.h>
#include <tdme/gui/nodes/GUINode_AlignmentHorizontal.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIPanelNode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUISpaceNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/nodes/GUIVerticalScrollbarInternalNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

#include <ext/tinyxml/tinyxml.h>

using std::map;
using std::string;

using tdme::gui::GUIParser;
using tdme::gui::GUIParserException;
using tdme::gui::elements::GUIButton;
using tdme::gui::elements::GUICheckbox;
using tdme::gui::elements::GUIDropDown;
using tdme::gui::elements::GUIDropDownOption;
using tdme::gui::elements::GUIElement;
using tdme::gui::elements::GUIImageButton;
using tdme::gui::elements::GUIInput;
using tdme::gui::elements::GUIKnob;
using tdme::gui::elements::GUIProgressBar;
using tdme::gui::elements::GUIRadioButton;
using tdme::gui::elements::GUIScrollArea;
using tdme::gui::elements::GUIScrollAreaHorizontal;
using tdme::gui::elements::GUIScrollAreaVertical;
using tdme::gui::elements::GUISelectBox;
using tdme::gui::elements::GUISelectBoxMultiple;
using tdme::gui::elements::GUISelectBoxMultipleOption;
using tdme::gui::elements::GUISelectBoxOption;
using tdme::gui::elements::GUISliderH;
using tdme::gui::elements::GUISliderV;
using tdme::gui::elements::GUITab;
using tdme::gui::elements::GUITabContent;
using tdme::gui::elements::GUITabs;
using tdme::gui::elements::GUITabsContent;
using tdme::gui::elements::GUITabsHeader;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIHorizontalScrollbarInternalNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUIInputInternalNode;
using tdme::gui::nodes::GUILayoutNode;
using tdme::gui::nodes::GUIMultilineTextNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIPanelNode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUISpaceNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::nodes::GUIVerticalScrollbarInternalNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::MutableString;
using tdme::utils::StringUtils;
using tdme::utils::Console;
using tdme::utils::Exception;

using tdme::ext::tinyxml::TiXmlDocument;
using tdme::ext::tinyxml::TiXmlElement;
using tdme::ext::tinyxml::TiXmlAttribute;

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

map<string, GUIElement*> GUIParser::elements;

GUIScreenNode* GUIParser::parse(const string& pathName, const string& fileName) throw (GUIParserException, FileSystemException)
{
	return parse(FileSystem::getInstance()->getContentAsString(pathName, fileName));
}

GUIScreenNode* GUIParser::parse(const string& xml) throw (GUIParserException, FileSystemException)
{
	TiXmlDocument xmlDocument;
	xmlDocument.Parse(xml.c_str());
	if (xmlDocument.Error() == true) {
		throw GUIParserException(
			string("GUIParser::parse():: Could not parse XML. Error='") + string(xmlDocument.ErrorDesc()) + "': \n\n" + xml
		);
	}
	TiXmlElement* xmlRoot = xmlDocument.RootElement();
	GUIScreenNode* guiScreenNode = nullptr;
	if (string(xmlRoot->Value()) != string("screen")) {
		throw GUIParserException("XML root node must be <screen>");
	}

	guiScreenNode = new GUIScreenNode(
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
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("height")))
		),
		GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-color"))), GUIColor::GUICOLOR_TRANSPARENT),
		string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-image"))),
		GUINode::createScale9Grid(
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-image-scale9"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-image-scale9-left"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-image-scale9-top"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-image-scale9-right"))),
			string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-image-scale9-bottom")))
		),
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
		StringUtils::equalsIgnoreCase(StringUtils::trim(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("scrollable")))), "true"),
		StringUtils::equalsIgnoreCase(StringUtils::trim(string(AVOID_NULLPTR_STRING(xmlRoot->Attribute("popup")))), "true")
	);
	parseGUINode(guiScreenNode, xmlRoot, nullptr);
	return guiScreenNode;
}

void GUIParser::parse(GUIParentNode* parentNode, const string& pathName, const string& fileName) throw (GUIParserException, FileSystemException)
{
	string xml = FileSystem::getInstance()->getContentAsString(pathName, fileName);
	parse(parentNode, xml);
}

void GUIParser::parse(GUIParentNode* parentNode, const string& xml) throw (GUIParserException, FileSystemException)
{
	TiXmlDocument xmlDocument;
	xmlDocument.Parse((string("<gui-element>") + xml + string("</gui-element>")).c_str());
	if (xmlDocument.Error() == true) {
		throw GUIParserException(
			"GUIParser::parse():: Could not parse XML. Error='" + string(xmlDocument.ErrorDesc()) + "': \n\n" + xml
		);
	}
	TiXmlElement* xmlNode = xmlDocument.RootElement();
	parseGUINode(parentNode, xmlNode, nullptr);
}

void GUIParser::parseGUINode(GUIParentNode* guiParentNode, TiXmlElement* xmlParentNode, GUIElement* guiElement) throw (GUIParserException, FileSystemException)
{
	GUINodeController* guiElementController = nullptr;
	auto guiElementControllerInstalled = false;
	for (auto *node = xmlParentNode->FirstChildElement(); node != nullptr; node = node->NextSiblingElement()) {
		{
			string nodeTagName = string(node->Value());
			if (nodeTagName == "panel") {
				auto guiPanelNode = new GUIPanelNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(AVOID_NULLPTR_STRING(node->Attribute("id"))),
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
						string(AVOID_NULLPTR_STRING(node->Attribute("height")))
					),
					GUINode::getRequestedColor(string(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), GUIColor("#F0F0F0")),
					string(AVOID_NULLPTR_STRING(node->Attribute("background-image"))),
					GUINode::createScale9Grid(
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-right"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("background-image-scale9-bottom")))
					),
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
				parseGUINode(guiPanelNode, node, nullptr);
			} else
			if (nodeTagName == "layout") {
				auto guiLayoutNode = new GUILayoutNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(AVOID_NULLPTR_STRING(node->Attribute("id"))),
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
						string(AVOID_NULLPTR_STRING(node->Attribute("height")))
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
				parseGUINode(guiLayoutNode, node, nullptr);
			} else
			if (nodeTagName == "space") {
				auto guiSpaceNode = new GUISpaceNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height")))
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
					GUINode::createConditions(string(AVOID_NULLPTR_STRING(node->Attribute("hide-on"))))
				);
				guiParentNode->addSubNode(guiSpaceNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiSpaceNode);
					if (guiElementController != nullptr) {
						guiSpaceNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
			} else
			if (nodeTagName == "element") {
				auto guiElementNode = new GUIElementNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(AVOID_NULLPTR_STRING(node->Attribute("id"))),
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
						string(AVOID_NULLPTR_STRING(node->Attribute("height")))
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
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("name")))),
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("value")))),
					StringUtils::equalsIgnoreCase(StringUtils::trim(string(AVOID_NULLPTR_STRING(node->Attribute("selected")))), "true"),
					StringUtils::equalsIgnoreCase(StringUtils::trim(string(AVOID_NULLPTR_STRING(node->Attribute("disabled")))), "true"),
					StringUtils::equalsIgnoreCase(StringUtils::trim(string(AVOID_NULLPTR_STRING(node->Attribute("focusable")))), "true"),
					StringUtils::equalsIgnoreCase(StringUtils::trim(string(AVOID_NULLPTR_STRING(node->Attribute("ignore-events")))), "true"),
					string(AVOID_NULLPTR_STRING(node->Attribute("on-initialize"))),
					string(AVOID_NULLPTR_STRING(node->Attribute("on-mouse-click"))),
					string(AVOID_NULLPTR_STRING(node->Attribute("on-mouse-over"))),
					string(AVOID_NULLPTR_STRING(node->Attribute("on-mouse-out")))
				);
				guiParentNode->addSubNode(guiElementNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiElementNode);
					if (guiElementController != nullptr) {
						guiElementNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseGUINode(guiElementNode, node, nullptr);
			} else
			if (nodeTagName == "image") {
				auto guiImageNode = new GUIImageNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height")))
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
					unescapeQuotes(string(AVOID_NULLPTR_STRING(node->Attribute("src")))),
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
					)
				);
				guiParentNode->addSubNode(guiImageNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiImageNode);
					if (guiElementController != nullptr) {
						guiImageNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
			} else
			if (nodeTagName == "text") {
				auto guiTextNode = new GUITextNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height")))
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
					string(AVOID_NULLPTR_STRING(node->Attribute("font"))),
					string(AVOID_NULLPTR_STRING(node->Attribute("color"))),
					MutableString(unescapeQuotes(string(StringUtils::trim(AVOID_NULLPTR_STRING(node->Attribute("text"))))))
				);
				guiParentNode->addSubNode(guiTextNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiTextNode);
					if (guiElementController != nullptr) {
						guiTextNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
			} else
			if (nodeTagName == "multiline-text") {
				auto guiTextNode = new GUIMultilineTextNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height")))
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
					string(AVOID_NULLPTR_STRING(node->Attribute("font"))),
					string(AVOID_NULLPTR_STRING(node->Attribute("color"))),
					MutableString(StringUtils::trim(AVOID_NULLPTR_STRING(node->GetText())))
				);
				guiParentNode->addSubNode(guiTextNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiTextNode);
					if (guiElementController != nullptr) {
						guiTextNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
			} else
			if (nodeTagName == "input-internal") {
				auto guiInputInternalNode = new GUIInputInternalNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height")))
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
					string(AVOID_NULLPTR_STRING(node->Attribute("font"))),
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
			} else
			if (nodeTagName == "vertical-scrollbar-internal") {
				auto guiVerticalScrollbarInternalNode = new GUIVerticalScrollbarInternalNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height")))
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
			} else
			if (nodeTagName == "horizontal-scrollbar-internal") {
				auto guiHorizontalScrollbarInternalNode = new GUIHorizontalScrollbarInternalNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					string(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(string(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						string(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						string(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						string(AVOID_NULLPTR_STRING(node->Attribute("height")))
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
			} else
			if (nodeTagName == "template") {
				auto src = string(AVOID_NULLPTR_STRING(node->Attribute("src")));
				map<string, string> attributes;
				parseTemplate(
					guiParentNode,
					node,
					FileSystem::getInstance()->getContentAsString(
						FileSystem::getInstance()->getPathName(src),
						FileSystem::getInstance()->getFileName(src)
					),
					attributes,
					nullptr
				);
			} else {
				auto nodeTagNameString = nodeTagName;
				const auto guiElementIt = elements.find(nodeTagNameString);
				if (guiElementIt == elements.end()) {
					throw GUIParserException(
						"Unknown element '" +
						(nodeTagNameString) +
						"'"
					);
				}
				parseTemplate(guiParentNode, node, guiElementIt->second->getTemplate(), *guiElementIt->second->getAttributes(guiParentNode->screenNode), guiElementIt->second);
			}
		}
	}
	if (guiElementController != nullptr) {
		guiElementController->initialize();
	}
}

void GUIParser::parseTemplate(GUIParentNode* parentNode, TiXmlElement* node, const string& _template, map<string, string>& attributes, GUIElement* guiElement) {
	auto newGuiElementTemplate = _template;
	for (TiXmlAttribute* attribute = node->FirstAttribute(); attribute != nullptr; attribute = attribute->Next()) {
		auto attributeKey = string(attribute->Name());
		auto attributeValue = string(attribute->Value());
		newGuiElementTemplate = StringUtils::replace(newGuiElementTemplate, "{$" + attributeKey + "}", escapeQuotes(attributeValue));
	}

	for (auto newGuiElementAttributesIt : attributes) {
		auto guiElementAttributeValue = escapeQuotes(newGuiElementAttributesIt.second);
		newGuiElementTemplate = StringUtils::replace(newGuiElementTemplate, "{$" + newGuiElementAttributesIt.first + "}", guiElementAttributeValue);
	}

	newGuiElementTemplate = StringUtils::replace(newGuiElementTemplate, "{$innerXml}", getInnerXml(node));
	auto newGuiElementDocumentXML =  "<gui-element>\n" + newGuiElementTemplate + "</gui-element>\n";

	TiXmlDocument newGuiElementDocument;
	newGuiElementDocument.Parse((newGuiElementDocumentXML).c_str());
	if (newGuiElementDocument.Error() == true) {
		throw GUIParserException(
			"GUIParser::parse():: Could not parse XML. Error='" + string(newGuiElementDocument.ErrorDesc())
		);
	}
	parseGUINode(parentNode, newGuiElementDocument.RootElement(), guiElement);
}

const vector<TiXmlElement*> GUIParser::getChildrenByTagName(TiXmlElement* parent, const char* name)
{
	vector<TiXmlElement*> elementList;
	for (auto *child = parent->FirstChildElement(name); child != nullptr; child = child->NextSiblingElement(name)) {
		elementList.push_back(child);
	}
	return elementList;
}

const string GUIParser::getInnerXml(TiXmlElement* node)
{
	std::stringstream ss;
	for (auto *childNode = node->FirstChildElement(); childNode != nullptr; childNode = childNode->NextSiblingElement()) {
		ss << (*childNode);
	}
	return ss.str();
}

const string GUIParser::unescapeQuotes(const string& str)
{
	return StringUtils::replace(str, "&quot;", "\"");
}

const string GUIParser::escapeQuotes(const string& str)
{
	return StringUtils::replace(str, "\"", "&quot;");
}

void GUIParser::addElement(GUIElement* guiElement) throw (GUIParserException, FileSystemException)
{
	if (elements.find(guiElement->getName()) != elements.end()) {
		throw GUIParserException(
			"Element with given name '" +
			(guiElement->getName()) +
			"' already exists"
		);
	}
	elements.emplace(guiElement->getName(), guiElement);
}

void GUIParser::initialize()
{
	try {
		GUIElement* guiElement = new GUICheckbox();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUIRadioButton();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUISelectBox();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUISelectBoxOption();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUISelectBoxMultiple();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUISelectBoxMultipleOption();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUIDropDown();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUIDropDownOption();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUITabs();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUITabsHeader();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUITab();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUITabsContent();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUITabContent();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUIButton();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUIInput();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUIScrollAreaVertical();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUIScrollAreaHorizontal();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUIScrollArea();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUISliderH();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUISliderV();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUIKnob();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUIImageButton();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	try {
		GUIElement* guiElement = new GUIProgressBar();
		addElement(guiElement);
	} catch (Exception& exception) {
		Console::print(string("GUIParser::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}
