#include <tdme/gui/GUIParser.h>

#include <map>
#include <string>

#include <tdme/gui/GUIParserException.h>
#include <tdme/gui/elements/GUIButton.h>
#include <tdme/gui/elements/GUICheckbox.h>
#include <tdme/gui/elements/GUIDropDown.h>
#include <tdme/gui/elements/GUIDropDownOption.h>
#include <tdme/gui/elements/GUIElement.h>
#include <tdme/gui/elements/GUIInput.h>
#include <tdme/gui/elements/GUIRadioButton.h>
#include <tdme/gui/elements/GUIScrollArea.h>
#include <tdme/gui/elements/GUIScrollAreaHorizontal.h>
#include <tdme/gui/elements/GUIScrollAreaVertical.h>
#include <tdme/gui/elements/GUISelectBox.h>
#include <tdme/gui/elements/GUISelectBoxMultiple.h>
#include <tdme/gui/elements/GUISelectBoxMultipleOption.h>
#include <tdme/gui/elements/GUISelectBoxOption.h>
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
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIPanelNode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUISpaceNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/nodes/GUIVerticalScrollbarInternalNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

#include <ext/tinyxml/tinyxml.h>

using std::map;
using std::wstring;

using tdme::gui::GUIParser;
using tdme::gui::GUIParserException;
using tdme::gui::elements::GUIButton;
using tdme::gui::elements::GUICheckbox;
using tdme::gui::elements::GUIDropDown;
using tdme::gui::elements::GUIDropDownOption;
using tdme::gui::elements::GUIElement;
using tdme::gui::elements::GUIInput;
using tdme::gui::elements::GUIRadioButton;
using tdme::gui::elements::GUIScrollArea;
using tdme::gui::elements::GUIScrollAreaHorizontal;
using tdme::gui::elements::GUIScrollAreaVertical;
using tdme::gui::elements::GUISelectBox;
using tdme::gui::elements::GUISelectBoxMultiple;
using tdme::gui::elements::GUISelectBoxMultipleOption;
using tdme::gui::elements::GUISelectBoxOption;
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
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIPanelNode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUISpaceNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::nodes::GUIVerticalScrollbarInternalNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::MutableString;
using tdme::utils::StringConverter;
using tdme::utils::StringUtils;
using tdme::utils::Console;
using tdme::utils::Exception;

using tdme::ext::tinyxml::TiXmlDocument;
using tdme::ext::tinyxml::TiXmlElement;
using tdme::ext::tinyxml::TiXmlAttribute;

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

map<wstring, GUIElement*> GUIParser::elements;

GUIScreenNode* GUIParser::parse(const wstring& pathName, const wstring& fileName) throw (GUIParserException)
{
	return parse(FileSystem::getInstance()->getContentAsString(pathName, fileName));
}

GUIScreenNode* GUIParser::parse(const wstring& xml) throw (GUIParserException)
{
	TiXmlDocument xmlDocument;
	xmlDocument.Parse(StringConverter::toString(xml).c_str());
	if (xmlDocument.Error() == true) {
		throw GUIParserException(
			"GUIParser::parse():: Could not parse XML. Error='" + string(xmlDocument.ErrorDesc())
		);
	}
	TiXmlElement* xmlRoot = xmlDocument.RootElement();
	GUIScreenNode* guiScreenNode = nullptr;
	if (string(xmlRoot->Value()) != string("screen")) {
		throw GUIParserException("XML root node must be <screen>");
	}

	guiScreenNode = new GUIScreenNode(
		StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("id"))),
		GUINode::createFlow(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("flow")))),
		GUIParentNode::createOverflow(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("overflow-x")))),
		GUIParentNode::createOverflow(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("overflow-y")))),
		GUINode::createAlignments(
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("horizontal-align"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("vertical-align")))
		),
		GUINode::createRequestedConstraints(
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("left"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("top"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("width"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("height")))
		),
		GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-color"))), &GUIColor::GUICOLOR_TRANSPARENT),
		GUINode::createBorder(
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-left"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-top"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-right"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-bottom"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-color"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-color-left"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-color-top"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-color-right"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-color-bottom")))
		),
		GUINode::createPadding(
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("padding"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("padding-left"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("padding-top"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("padding-right"))),
			StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("padding-bottom")))
		),
		GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("show-on")))),
		GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("hide-on")))),
		StringUtils::equalsIgnoreCase(StringUtils::trim(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("scrollable")))), L"true"),
		StringUtils::equalsIgnoreCase(StringUtils::trim(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("popup")))), L"true")
	);
	parseGUINode(guiScreenNode, xmlRoot, nullptr);
	return guiScreenNode;
}

void GUIParser::parse(GUIParentNode* parentNode, const wstring& pathName, const wstring& fileName) throw (GUIParserException)
{
	wstring xml = FileSystem::getInstance()->getContentAsString(pathName, fileName);
	parse(parentNode, xml);
}

void GUIParser::parse(GUIParentNode* parentNode, const wstring& xml) throw (GUIParserException)
{
	TiXmlDocument xmlDocument;
	xmlDocument.Parse(StringConverter::toString(wstring(L"<gui-element>") + xml + wstring(L"</gui-element>")).c_str());
	if (xmlDocument.Error() == true) {
		throw GUIParserException(
			"GUIParser::parse():: Could not parse XML. Error='" + string(xmlDocument.ErrorDesc())
		);
	}
	TiXmlElement* xmlNode = xmlDocument.RootElement();
	parseGUINode(parentNode, xmlNode, nullptr);
}

void GUIParser::parseGUINode(GUIParentNode* guiParentNode, TiXmlElement* xmlParentNode, GUIElement* guiElement) throw (GUIParserException)
{
	GUINodeController* guiElementController = nullptr;
	auto guiElementControllerInstalled = false;
	for (auto *node = xmlParentNode->FirstChildElement(); node != nullptr; node = node->NextSiblingElement()) {
		{
			string nodeTagName = node->Value();
			if (nodeTagName == string("panel")) {
				auto guiPanelNode = new GUIPanelNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUIParentNode::createOverflow(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("overflow-x")))),
					GUIParentNode::createOverflow(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("overflow-y")))),
					GUINode::createAlignments(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height")))
					),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), new GUIColor(L"#F0F0F0")),
					GUINode::createBorder(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					GUILayoutNode::createAlignment(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("alignment"))))
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
			if (nodeTagName == string("layout")) {
				auto guiLayoutNode = new GUILayoutNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUIParentNode::createOverflow(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("overflow-x")))),
					GUIParentNode::createOverflow(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("overflow-y")))),
					GUINode::createAlignments(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height")))
					),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), &GUIColor::GUICOLOR_TRANSPARENT),
					GUINode::createBorder(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					GUILayoutNode::createAlignment(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("alignment"))))
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
			if (nodeTagName == string("space")) {
				auto guiSpaceNode = new GUISpaceNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height")))
					),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), &GUIColor::GUICOLOR_TRANSPARENT),
					GUINode::createBorder(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on"))))
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
			if (nodeTagName == string("element")) {
				auto guiElementNode = new GUIElementNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUIParentNode::createOverflow(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("overflow-x")))),
					GUIParentNode::createOverflow(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("overflow-y")))),
					GUINode::createAlignments(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height")))
					),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), &GUIColor::GUICOLOR_TRANSPARENT),
					GUINode::createBorder(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("name")))),
					unescapeQuotes(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("value")))),
					StringUtils::equalsIgnoreCase(StringUtils::trim(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("selected")))), L"true"),
					StringUtils::equalsIgnoreCase(StringUtils::trim(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("disabled")))), L"true"),
					StringUtils::equalsIgnoreCase(StringUtils::trim(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("focusable")))), L"true"),
					StringUtils::equalsIgnoreCase(StringUtils::trim(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("ignore-events")))), L"true")
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
			if (nodeTagName == string("image")) {
				auto guiImageNode = new GUIImageNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height")))
					),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), &GUIColor::GUICOLOR_TRANSPARENT),
					GUINode::createBorder(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					unescapeQuotes(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("src")))),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("effect-color-mul"))), &GUIColor::GUICOLOR_EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("effect-color-add"))), &GUIColor::GUICOLOR_EFFECT_COLOR_ADD)
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
			if (nodeTagName == string("text")) {
				auto guiTextNode = new GUITextNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height")))
					),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), &GUIColor::GUICOLOR_TRANSPARENT),
					GUINode::createBorder(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("font"))),
					StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color"))),
					new MutableString(unescapeQuotes(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("text")))))
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
			if (nodeTagName == string("input-internal")) {
				auto guiInputInternalNode = new GUIInputInternalNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height")))
					),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), &GUIColor::GUICOLOR_TRANSPARENT),
					GUINode::createBorder(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("font"))),
					StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color"))),
					StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color-disabled"))),
					new MutableString(unescapeQuotes(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("text"))))),
					GUIInputInternalNode::createMaxLength(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("maxlength"))))
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
			if (nodeTagName == string("vertical-scrollbar-internal")) {
				auto guiVerticalScrollbarInternalNode = new GUIVerticalScrollbarInternalNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height")))
					),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), &GUIColor::GUICOLOR_TRANSPARENT),
					GUINode::createBorder(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color-none"))), &GUIColor::GUICOLOR_BLACK),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color-mouseover"))), &GUIColor::GUICOLOR_BLACK),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color-dragging"))), &GUIColor::GUICOLOR_BLACK)
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
			if (nodeTagName == string("horizontal-scrollbar-internal")) {
				auto guiHorizontalScrollbarInternalNode = new GUIHorizontalScrollbarInternalNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id"))),
					GUINode::createFlow(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow")))),
					GUINode::createAlignments(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align")))
					),
					GUIParentNode::createRequestedConstraints(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height")))
					),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color"))), &GUIColor::GUICOLOR_TRANSPARENT),
					GUINode::createBorder(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom")))
					),
					GUINode::createPadding(
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right"))),
						StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom")))
					),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on")))),
					GUINode::createConditions(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color-none"))), &GUIColor::GUICOLOR_BLACK),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color-mouseover"))), &GUIColor::GUICOLOR_BLACK),
					GUINode::getRequestedColor(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color-dragging"))), &GUIColor::GUICOLOR_BLACK)
				);
				guiParentNode->addSubNode(guiHorizontalScrollbarInternalNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiHorizontalScrollbarInternalNode);
					if (guiElementController != nullptr) {
						guiHorizontalScrollbarInternalNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
			} else {
				auto nodeTagNameString = StringConverter::toWideString(nodeTagName);
				const auto guiElementIt = elements.find(nodeTagNameString);
				if (guiElementIt == elements.end()) {
					throw GUIParserException(
						"Unknown element '" +
						StringConverter::toString(nodeTagNameString) +
						"'"
					);
				}
				auto newGuiElementTemplate = guiElementIt->second->getTemplate();
				for (TiXmlAttribute* attribute = node->FirstAttribute(); attribute != nullptr; attribute = attribute->Next()) {
					auto attributeKey = StringConverter::toWideString(attribute->Name());
					auto attributeValue = StringConverter::toWideString(attribute->Value());
					newGuiElementTemplate = StringUtils::replace(newGuiElementTemplate, L"{$" + attributeKey + L"}", escapeQuotes(attributeValue));
				}

				auto newGuiElementAttributes = guiElementIt->second->getAttributes(guiParentNode->getScreenNode());
				for (auto newGuiElementAttributesIt : *newGuiElementAttributes) {
					auto guiElementAttributeValue = escapeQuotes(newGuiElementAttributesIt.second);
					newGuiElementTemplate = StringUtils::replace(newGuiElementTemplate, L"{$" + newGuiElementAttributesIt.first + L"}", guiElementAttributeValue);
				}

				newGuiElementTemplate = StringUtils::replace(newGuiElementTemplate, L"{$innerXml}", getInnerXml(node));
				auto newGuiElementDocumentXML =  L"<gui-element>\n" + newGuiElementTemplate + L"</gui-element>\n";

				TiXmlDocument newGuiElementDocument;
				newGuiElementDocument.Parse(StringConverter::toString(newGuiElementDocumentXML).c_str());
				if (newGuiElementDocument.Error() == true) {
					throw GUIParserException(
						"GUIParser::parse():: Could not parse XML. Error='" + string(newGuiElementDocument.ErrorDesc())
					);
				}
				parseGUINode(guiParentNode, newGuiElementDocument.RootElement(), guiElementIt->second);
			}
		}
	}
	if (guiElementController != nullptr) {
		guiElementController->initialize();
	}
}

const vector<TiXmlElement*> GUIParser::getChildrenByTagName(TiXmlElement* parent, const char* name)
{
	vector<TiXmlElement*> elementList;
	for (auto *child = parent->FirstChildElement(name); child != nullptr; child = child->NextSiblingElement(name)) {
		elementList.push_back(child);
	}
	return elementList;
}

const wstring GUIParser::getInnerXml(TiXmlElement* node)
{
	std::stringstream ss;
	for (auto *childNode = node->FirstChildElement(); childNode != nullptr; childNode = childNode->NextSiblingElement()) {
		ss << (*childNode);
	}
	return StringConverter::toWideString(ss.str());
}

const wstring GUIParser::unescapeQuotes(const wstring& string)
{
	return StringUtils::replace(string, L"&quot;", L"\"");
}

const wstring GUIParser::escapeQuotes(const wstring& string)
{
	return StringUtils::replace(string, L"\"", L"&quot;");
}

void GUIParser::addElement(GUIElement* guiElement) throw (GUIParserException)
{
	if (elements.find(guiElement->getName()) != elements.end()) {
		throw GUIParserException(
			"Element with given name '" +
			StringConverter::toString(guiElement->getName()) +
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
}
