// Generated from /tdme/src/tdme/gui/GUIParser.java
#include <tdme/gui/GUIParser.h>

#include <java/lang/CharSequence.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Exception.h>
#include <java/lang/NullPointerException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Iterator.h>
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
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_HashMap_KeysIterator.h>
#include <tdme/utils/_HashMap.h>

#include <ext/tinyxml/tinyxml.h>

using tdme::gui::GUIParser;
using java::lang::CharSequence;
using java::lang::ClassCastException;
using java::lang::Exception;
using java::lang::NullPointerException;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Iterator;
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
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::MutableString;
using tdme::utils::StringConverter;
using tdme::utils::_ArrayList;
using tdme::utils::_Console;
using tdme::utils::_HashMap_KeysIterator;
using tdme::utils::_HashMap;

using tdme::ext::tinyxml::TiXmlDocument;
using tdme::ext::tinyxml::TiXmlElement;
using tdme::ext::tinyxml::TiXmlAttribute;

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

GUIParser::GUIParser(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIParser::GUIParser()
	: GUIParser(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

_HashMap* GUIParser::elements;

GUIScreenNode* GUIParser::parse(String* pathName, String* fileName) /* throws(Exception) */
{
	clinit();
	return parse(new String(_FileSystem::getInstance()->getContent(pathName, fileName)));
}

GUIScreenNode* GUIParser::parse(String* xml) /* throws(Exception) */
{
	clinit();

	TiXmlDocument xmlDocument;
	xmlDocument.Parse(StringConverter::toString(xml->getCPPWString()).c_str());
	if (xmlDocument.Error() == true) {
		_Console::println(string("GUIParser::parse():: Could not parse XML. Error='") + xmlDocument.ErrorDesc() + string("'. Exiting.\n"));
		exit(1);
	}
	TiXmlElement* xmlRoot = xmlDocument.RootElement();
	GUIScreenNode* guiScreenNode = nullptr;
	if (string(xmlRoot->Value()) != string("screen")) {
		throw new GUIParserException(u"XML root node must be <screen>"_j);
	}

	String* tmpString = nullptr;
	guiScreenNode = new GUIScreenNode(
		new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("id")))),
		GUINode::createFlow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("flow"))))),
		GUIParentNode::createOverflow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("overflow-x"))))),
		GUIParentNode::createOverflow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("overflow-y"))))),
		GUINode::createAlignments(
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("horizontal-align")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("vertical-align"))))
		),
		GUINode::createRequestedConstraints(
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("left")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("top")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("width")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("height"))))
		),
		GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("background-color")))), GUIColor::TRANSPARENT),
		GUINode::createBorder(
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-left")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-top")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-right")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-bottom")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-color")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-color-left")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-color-top")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-color-right")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("border-color-bottom"))))
		),
		GUINode::createPadding(
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("padding")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("padding-left")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("padding-top")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("padding-right")))),
			new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("padding-bottom"))))
		),
		GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("show-on"))))),
		GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("hide-on"))))),
		(tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("scrollable")))))->trim()->equalsIgnoreCase(u"true"_j),
		(tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(xmlRoot->Attribute("popup")))))->trim()->equalsIgnoreCase(u"true"_j)
	);
	parseGUINode(guiScreenNode, xmlRoot, nullptr);
	return guiScreenNode;
}

void GUIParser::parse(GUIParentNode* parentNode, String* pathName, String* fileName) /* throws(Exception) */
{
	String* xml = new String(_FileSystem::getInstance()->getContent(pathName, fileName));
	parse(parentNode, xml);
}

void GUIParser::parse(GUIParentNode* parentNode, String* xml) /* throws(Exception) */
{
	clinit();
	TiXmlDocument xmlDocument;
	xmlDocument.Parse(StringConverter::toString(wstring(L"<gui-element>") + xml->getCPPWString() + wstring(L"</gui-element>")).c_str());
	if (xmlDocument.Error() == true) {
		_Console::println(string("GUIParser::parse():: Could not parse XML. Error='") + xmlDocument.ErrorDesc() + string("'. Exiting.\n"));
		exit(1);
	}
	TiXmlElement* xmlNode = xmlDocument.RootElement();

	parseGUINode(parentNode, xmlNode, nullptr);
}

void GUIParser::parseGUINode(GUIParentNode* guiParentNode, TiXmlElement* xmlParentNode, GUIElement* guiElement) /* throws(Exception) */
{
	clinit();
	String* tmpString = nullptr;
	GUINodeController* guiElementController = nullptr;
	auto guiElementControllerInstalled = false;
	for (auto *node = xmlParentNode->FirstChildElement(); node != nullptr; node = node->NextSiblingElement()) {
		{
			string nodeTagName = node->Value();
			if (nodeTagName == string("panel")) {
				auto guiPanelNode = new GUIPanelNode(
					guiParentNode->getScreenNode(),
					guiParentNode,
					new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id")))),
					GUINode::createFlow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow"))))),
					GUIParentNode::createOverflow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("overflow-x"))))),
					GUIParentNode::createOverflow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("overflow-y"))))),
					GUINode::createAlignments(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align"))))
					),
					GUIParentNode::createRequestedConstraints(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height"))))
					),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color")))), new GUIColor(u"#F0F0F0"_j)),
					GUINode::createBorder(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom"))))
					),
					GUINode::createPadding(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom"))))
					),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on"))))),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on"))))),
					GUILayoutNode::createAlignment(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("alignment")))))
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
					new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id")))),
					GUINode::createFlow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow"))))),
					GUIParentNode::createOverflow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("overflow-x"))))),
					GUIParentNode::createOverflow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("overflow-y"))))),
					GUINode::createAlignments(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align"))))
					),
					GUIParentNode::createRequestedConstraints(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height"))))
					),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color")))), GUIColor::TRANSPARENT),
					GUINode::createBorder(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom"))))
					),
					GUINode::createPadding(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom"))))
					),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on"))))),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on"))))),
					GUILayoutNode::createAlignment(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("alignment")))))
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
					new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id")))),
					GUINode::createFlow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow"))))),
					GUINode::createAlignments(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align"))))
					),
					GUIParentNode::createRequestedConstraints(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height"))))
					),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color")))), GUIColor::TRANSPARENT),
					GUINode::createBorder(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom"))))
					),
					GUINode::createPadding(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom"))))
					),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on"))))),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on")))))
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
					new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id")))),
					GUINode::createFlow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow"))))),
					GUIParentNode::createOverflow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("overflow-x"))))),
					GUIParentNode::createOverflow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("overflow-y"))))),
					GUINode::createAlignments(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align"))))
					),
					GUIParentNode::createRequestedConstraints(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height"))))
					),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color")))), GUIColor::TRANSPARENT),
					GUINode::createBorder(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom"))))
					),
					GUINode::createPadding(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom"))))
					),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on"))))),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on"))))),
					unescapeQuotes(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("name"))))),
					unescapeQuotes(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("value"))))),
					(tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("selected")))))->trim()->equalsIgnoreCase(u"true"_j),
					(tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("disabled")))))->trim()->equalsIgnoreCase(u"true"_j),
					(tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("focusable")))))->trim()->equalsIgnoreCase(u"true"_j),
					(tmpString = new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("ignore-events")))))->trim()->equalsIgnoreCase(u"true"_j)
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
					new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id")))),
					GUINode::createFlow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow"))))),
					GUINode::createAlignments(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align"))))
					),
					GUIParentNode::createRequestedConstraints(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height"))))
					),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color")))), GUIColor::TRANSPARENT),
					GUINode::createBorder(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom"))))
					),
					GUINode::createPadding(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom"))))
					),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on"))))),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on"))))),
					unescapeQuotes(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("src"))))),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("effect-color-mul")))), GUIColor::EFFECT_COLOR_MUL),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("effect-color-add")))), GUIColor::EFFECT_COLOR_ADD)
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
					new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id")))),
					GUINode::createFlow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow"))))),
					GUINode::createAlignments(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align"))))
					),
					GUIParentNode::createRequestedConstraints(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height"))))
					),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color")))), GUIColor::TRANSPARENT),
					GUINode::createBorder(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom"))))
					),
					GUINode::createPadding(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom"))))
					),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on"))))),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on"))))),
					new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("font")))),
					new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color")))),
					new MutableString(unescapeQuotes(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("text"))))))
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
					new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id")))),
					GUINode::createFlow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow"))))),
					GUINode::createAlignments(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align"))))
					),
					GUIParentNode::createRequestedConstraints(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height"))))
					),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color")))), GUIColor::TRANSPARENT),
					GUINode::createBorder(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom"))))
					),
					GUINode::createPadding(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom"))))
					),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on"))))),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on"))))),
					new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("font")))),
					new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color")))),
					new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color-disabled")))),
					new MutableString(unescapeQuotes(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("text")))))),
					GUIInputInternalNode::createMaxLength(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("maxlength")))))
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
					new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id")))),
					GUINode::createFlow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow"))))),
					GUINode::createAlignments(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align"))))
					),
					GUIParentNode::createRequestedConstraints(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height"))))
					),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color")))), GUIColor::TRANSPARENT),
					GUINode::createBorder(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom"))))
					),
					GUINode::createPadding(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom"))))
					),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on"))))),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on"))))),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color-none")))), GUIColor::BLACK),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color-mouseover")))), GUIColor::BLACK),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color-dragging")))), GUIColor::BLACK));
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
					new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("id")))),
					GUINode::createFlow(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("flow"))))),
					GUINode::createAlignments(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("horizontal-align")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("vertical-align"))))
					),
					GUIParentNode::createRequestedConstraints(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("width")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("height"))))
					),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("background-color")))), GUIColor::TRANSPARENT),
					GUINode::createBorder(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-bottom")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("border-color-bottom"))))
					),
					GUINode::createPadding(
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-left")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-top")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-right")))),
						new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("padding-bottom"))))
					),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("show-on"))))),
					GUINode::createConditions(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("hide-on"))))),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color-none")))), GUIColor::BLACK),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color-mouseover")))), GUIColor::BLACK),
					GUINode::getRequestedColor(new String(StringConverter::toWideString(AVOID_NULLPTR_STRING(node->Attribute("color-dragging")))), GUIColor::BLACK)
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
				String* nodeTagNameString = new String(StringConverter::toWideString(nodeTagName));
				auto newGuiElement = java_cast< GUIElement* >(elements->get(nodeTagNameString));
				if (newGuiElement == nullptr) {
					throw new GUIParserException(::java::lang::StringBuilder().append(u"Unknown element '"_j)->append(nodeTagNameString)
						->append(u"'"_j)->toString());
				}
				auto newGuiElementTemplate = newGuiElement->getTemplate();
				for (TiXmlAttribute* attribute = node->FirstAttribute(); attribute != nullptr; attribute = attribute->Next()) {
					String* attributeKey = new String(StringConverter::toWideString(attribute->Name()));
					String* attributeValue =  new String(StringConverter::toWideString(attribute->Value()));
					newGuiElementTemplate =
						newGuiElementTemplate->replace(
							static_cast< CharSequence* >(
								::java::lang::StringBuilder().
								 append(u"{$"_j)->
								 append(attributeKey)->
								 append(u"}"_j)->
								 toString()
							),
							static_cast< CharSequence* >(
								escapeQuotes(
									attributeValue
								)
							)
						);
				}

				auto newGuiElementAttributes = newGuiElement->getAttributes(guiParentNode->getScreenNode());
				for (auto _i = newGuiElementAttributes->getKeysIterator()->iterator(); _i->hasNext(); ) {
					String* newGuiElementAttributeKey = java_cast< String* >(_i->next());
					{
						auto guiElementAttributeValue = escapeQuotes(java_cast< String* >(newGuiElementAttributes->get(newGuiElementAttributeKey)));
						newGuiElementTemplate = newGuiElementTemplate->replace(static_cast< CharSequence* >(::java::lang::StringBuilder().append(u"{$"_j)->append(newGuiElementAttributeKey)
							->append(u"}"_j)->toString()), static_cast< CharSequence* >(guiElementAttributeValue));
					}
				}

				newGuiElementTemplate = newGuiElementTemplate->replace(
					static_cast< CharSequence* >(u"{$innerXml}"_j),
					static_cast< CharSequence* >(getInnerXml(node))
				);
				String* newGuiElementDocumentXML =
					new String(::java::lang::StringBuilder().
						append(u"<gui-element>\n"_j)->
						append(newGuiElementTemplate)->
						append(u"</gui-element>\n"_j)->
						toString()
					);

				TiXmlDocument newGuiElementDocument;
				newGuiElementDocument.Parse(StringConverter::toString(newGuiElementDocumentXML->getCPPWString()).c_str());
				if (newGuiElementDocument.Error() == true) {
					_Console::println(string("GUIParser::parse():: Could not parse XML. Error='") + newGuiElementDocument.ErrorDesc() + string("'. Exiting.\n"));
					exit(1);
				}
				parseGUINode(guiParentNode, newGuiElementDocument.RootElement(), newGuiElement);
			}
		}
	}
	if (guiElementController != nullptr) {
		guiElementController->initialize();
	}
}

const vector<TiXmlElement*> GUIParser::getChildrenByTagName(TiXmlElement* parent, const char* name)
{
	clinit();
	vector<TiXmlElement*> elementList;
	for (auto *child = parent->FirstChildElement(name); child != nullptr; child = child->NextSiblingElement(name)) {
		elementList.push_back(child);
	}
	return elementList;
}

String* GUIParser::getInnerXml(TiXmlElement* node)
{
	clinit();
	std::stringstream ss;
	for (auto *childNode = node->FirstChildElement(); childNode != nullptr; childNode = childNode->NextSiblingElement()) {
		ss << (*childNode);
	}
	return new String(StringConverter::toWideString(ss.str()));
}

String* GUIParser::unescapeQuotes(String* string)
{
	clinit();
	return string->replace(static_cast< CharSequence* >(u"&quot;"_j), static_cast< CharSequence* >(u"\""_j));
}

String* GUIParser::escapeQuotes(String* string)
{
	clinit();
	return string->replace(static_cast< CharSequence* >(u"\""_j), static_cast< CharSequence* >(u"&quot;"_j));
}

void GUIParser::addElement(GUIElement* guiElement) /* throws(GUIParserException) */
{
	clinit();
	if (java_cast< GUIElement* >(elements->get(guiElement->getName())) != nullptr) {
		throw new GUIParserException(::java::lang::StringBuilder().append(u"Element with given name '"_j)->append(guiElement->getName())
			->append(u"' already exists"_j)->toString());
	}
	elements->put(guiElement->getName(), guiElement);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIParser::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.GUIParser", 18);
    return c;
}

void GUIParser::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		elements = new _HashMap();
		{
			try {
				GUICheckbox::clinit();
				GUIElement* guiElement = new GUICheckbox();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIRadioButton::clinit();
				GUIElement* guiElement = new GUIRadioButton();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUISelectBox::clinit();
				GUIElement* guiElement = new GUISelectBox();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUISelectBoxOption::clinit();
				GUIElement* guiElement = new GUISelectBoxOption();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUISelectBoxMultiple::clinit();
				GUIElement* guiElement = new GUISelectBoxMultiple();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUISelectBoxMultipleOption::clinit();
				GUIElement* guiElement = new GUISelectBoxMultipleOption();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIDropDown::clinit();
				GUIElement* guiElement = new GUIDropDown();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIDropDownOption::clinit();
				GUIElement* guiElement = new GUIDropDownOption();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUITabs::clinit();
				GUIElement* guiElement = new GUITabs();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUITabsHeader::clinit();
				GUIElement* guiElement = new GUITabsHeader();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUITab::clinit();
				GUIElement* guiElement = new GUITab();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUITabsContent::clinit();
				GUIElement* guiElement = new GUITabsContent();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUITabContent::clinit();
				GUIElement* guiElement = new GUITabContent();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIButton::clinit();
				GUIElement* guiElement = new GUIButton();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIInput::clinit();
				GUIElement* guiElement = new GUIInput();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIScrollAreaVertical::clinit();
				GUIElement* guiElement = new GUIScrollAreaVertical();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIScrollAreaHorizontal::clinit();
				GUIElement* guiElement = new GUIScrollAreaHorizontal();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIScrollArea::clinit();
				GUIElement* guiElement = new GUIScrollArea();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
		}
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* GUIParser::getClass0()
{
	return class_();
}

