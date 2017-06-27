// Generated from /tdme/src/tdme/gui/GUIParser.java
#include <tdme/gui/GUIParser.h>

#include <java/io/ByteArrayInputStream.h>
#include <java/io/InputStream.h>
#include <java/lang/CharSequence.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Exception.h>
#include <java/lang/NullPointerException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Iterator.h>
#include <javax/xml/parsers/DocumentBuilder.h>
#include <javax/xml/parsers/DocumentBuilderFactory.h>
#include <org/w3c/dom/DOMImplementation.h>
#include <org/w3c/dom/Document.h>
#include <org/w3c/dom/Element.h>
#include <org/w3c/dom/NamedNodeMap.h>
#include <org/w3c/dom/Node.h>
#include <org/w3c/dom/NodeList.h>
#include <org/w3c/dom/ls/DOMImplementationLS.h>
#include <org/w3c/dom/ls/LSSerializer.h>
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
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_HashMap_KeysIterator.h>
#include <tdme/utils/_HashMap.h>

using tdme::gui::GUIParser;
using java::io::ByteArrayInputStream;
using java::io::InputStream;
using java::lang::CharSequence;
using java::lang::ClassCastException;
using java::lang::Exception;
using java::lang::NullPointerException;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Iterator;
using javax::xml::parsers::DocumentBuilder;
using javax::xml::parsers::DocumentBuilderFactory;
using org::w3c::dom::DOMImplementation;
using org::w3c::dom::Document;
using org::w3c::dom::Element;
using org::w3c::dom::NamedNodeMap;
using org::w3c::dom::Node;
using org::w3c::dom::NodeList;
using org::w3c::dom::ls::DOMImplementationLS;
using org::w3c::dom::ls::LSSerializer;
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
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap_KeysIterator;
using tdme::utils::_HashMap;

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
	return parse(_FileSystem::getInstance()->getContent(pathName, fileName));
}

GUIScreenNode* GUIParser::parse(String* xml) /* throws(Exception) */
{
	clinit();
	auto builder = DocumentBuilderFactory::newInstance()->newDocumentBuilder();
	auto document = builder->parse(static_cast< InputStream* >(new ByteArrayInputStream((new String(xml))->getBytes())));
	auto xmlRoot = document->getDocumentElement();
	GUIScreenNode* guiScreenNode = nullptr;
	if (xmlRoot->getNodeName()->equals(u"screen"_j) == false) {
		throw new GUIParserException(u"XML root node must be <screen>"_j);
	}
	guiScreenNode = new GUIScreenNode(xmlRoot->getAttribute(u"id"_j), GUINode::createFlow(xmlRoot->getAttribute(u"flow"_j)), GUIParentNode::createOverflow(xmlRoot->getAttribute(u"overflow-x"_j)), GUIParentNode::createOverflow(xmlRoot->getAttribute(u"overflow-y"_j)), GUINode::createAlignments(xmlRoot->getAttribute(u"horizontal-align"_j), xmlRoot->getAttribute(u"vertical-align"_j)), GUINode::createRequestedConstraints(xmlRoot->getAttribute(u"left"_j), xmlRoot->getAttribute(u"top"_j), xmlRoot->getAttribute(u"width"_j), xmlRoot->getAttribute(u"height"_j)), GUINode::getRequestedColor(xmlRoot->getAttribute(u"background-color"_j), GUIColor::TRANSPARENT), GUINode::createBorder(xmlRoot->getAttribute(u"border"_j), xmlRoot->getAttribute(u"border-left"_j), xmlRoot->getAttribute(u"border-top"_j), xmlRoot->getAttribute(u"border-right"_j), xmlRoot->getAttribute(u"border-bottom"_j), xmlRoot->getAttribute(u"border-color"_j), xmlRoot->getAttribute(u"border-color-left"_j), xmlRoot->getAttribute(u"border-color-top"_j), xmlRoot->getAttribute(u"border-color-right"_j), xmlRoot->getAttribute(u"border-color-bottom"_j)), GUINode::createPadding(xmlRoot->getAttribute(u"padding"_j), xmlRoot->getAttribute(u"padding-left"_j), xmlRoot->getAttribute(u"padding-top"_j), xmlRoot->getAttribute(u"padding-right"_j), xmlRoot->getAttribute(u"padding-bottom"_j)), GUINode::createConditions(xmlRoot->getAttribute(u"show-on"_j)), GUINode::createConditions(xmlRoot->getAttribute(u"hide-on"_j)), xmlRoot->getAttribute(u"scrollable"_j)->trim()->equalsIgnoreCase(u"true"_j), xmlRoot->getAttribute(u"popup"_j)->trim()->equalsIgnoreCase(u"true"_j));
	parseGUINode(guiScreenNode, xmlRoot, nullptr);
	return guiScreenNode;
}

void GUIParser::parse(GUIParentNode* parentNode, String* pathName, String* fileName) /* throws(Exception) */
{
	clinit();
	auto builder = DocumentBuilderFactory::newInstance()->newDocumentBuilder();
	auto document = builder->parse(static_cast< InputStream* >(new ByteArrayInputStream((new String(::java::lang::StringBuilder().append(u"<children>"_j)->append(_FileSystem::getInstance()->getContent(pathName, fileName))
		->append(u"</children>"_j)->toString()))->getBytes())));
	auto xmlNode = document->getDocumentElement();
	parseGUINode(parentNode, xmlNode, nullptr);
}

void GUIParser::parse(GUIParentNode* parentNode, String* xml) /* throws(Exception) */
{
	clinit();
	auto builder = DocumentBuilderFactory::newInstance()->newDocumentBuilder();
	auto document = builder->parse(static_cast< InputStream* >(new ByteArrayInputStream((new String(::java::lang::StringBuilder().append(u"<children>"_j)->append(xml)
		->append(u"</children>"_j)->toString()))->getBytes())));
	auto xmlNode = document->getDocumentElement();
	parseGUINode(parentNode, xmlNode, nullptr);
}

void GUIParser::parseGUINode(GUIParentNode* guiParentNode, Element* xmlParentNode, GUIElement* guiElement) /* throws(Exception) */
{
	clinit();
	GUINodeController* guiElementController = nullptr;
	auto guiElementControllerInstalled = false;
	for (auto _i = getChildrenTags(xmlParentNode)->iterator(); _i->hasNext(); ) {
		Element* node = java_cast< Element* >(_i->next());
		{
			if (node->getNodeName()->equals(u"panel"_j)) {
				auto guiPanelNode = new GUIPanelNode(guiParentNode->getScreenNode(), guiParentNode, node->getAttribute(u"id"_j), GUINode::createFlow(node->getAttribute(u"flow"_j)), GUIParentNode::createOverflow(node->getAttribute(u"overflow-x"_j)), GUIParentNode::createOverflow(node->getAttribute(u"overflow-y"_j)), GUINode::createAlignments(node->getAttribute(u"horizontal-align"_j), node->getAttribute(u"vertical-align"_j)), GUIParentNode::createRequestedConstraints(node->getAttribute(u"left"_j), node->getAttribute(u"top"_j), node->getAttribute(u"width"_j), node->getAttribute(u"height"_j)), GUINode::getRequestedColor(node->getAttribute(u"background-color"_j), new GUIColor(u"#F0F0F0"_j)), GUINode::createBorder(node->getAttribute(u"border"_j), node->getAttribute(u"border-left"_j), node->getAttribute(u"border-top"_j), node->getAttribute(u"border-right"_j), node->getAttribute(u"border-bottom"_j), node->getAttribute(u"border-color"_j), node->getAttribute(u"border-color-left"_j), node->getAttribute(u"border-color-top"_j), node->getAttribute(u"border-color-right"_j), node->getAttribute(u"border-color-bottom"_j)), GUINode::createPadding(node->getAttribute(u"padding"_j), node->getAttribute(u"padding-left"_j), node->getAttribute(u"padding-top"_j), node->getAttribute(u"padding-right"_j), node->getAttribute(u"padding-bottom"_j)), GUINode::createConditions(node->getAttribute(u"show-on"_j)), GUINode::createConditions(node->getAttribute(u"hide-on"_j)), GUILayoutNode::createAlignment(node->getAttribute(u"alignment"_j)));
				guiParentNode->addSubNode(guiPanelNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiPanelNode);
					if (guiElementController != nullptr) {
						guiPanelNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseGUINode(guiPanelNode, node, nullptr);
			} else if (node->getNodeName()->equals(u"layout"_j)) {
				auto guiLayoutNode = new GUILayoutNode(guiParentNode->getScreenNode(), guiParentNode, node->getAttribute(u"id"_j), GUINode::createFlow(node->getAttribute(u"flow"_j)), GUIParentNode::createOverflow(node->getAttribute(u"overflow-x"_j)), GUIParentNode::createOverflow(node->getAttribute(u"overflow-y"_j)), GUINode::createAlignments(node->getAttribute(u"horizontal-align"_j), node->getAttribute(u"vertical-align"_j)), GUIParentNode::createRequestedConstraints(node->getAttribute(u"left"_j), node->getAttribute(u"top"_j), node->getAttribute(u"width"_j), node->getAttribute(u"height"_j)), GUINode::getRequestedColor(node->getAttribute(u"background-color"_j), GUIColor::TRANSPARENT), GUINode::createBorder(node->getAttribute(u"border"_j), node->getAttribute(u"border-left"_j), node->getAttribute(u"border-top"_j), node->getAttribute(u"border-right"_j), node->getAttribute(u"border-bottom"_j), node->getAttribute(u"border-color"_j), node->getAttribute(u"border-color-left"_j), node->getAttribute(u"border-color-top"_j), node->getAttribute(u"border-color-right"_j), node->getAttribute(u"border-color-bottom"_j)), GUINode::createPadding(node->getAttribute(u"padding"_j), node->getAttribute(u"padding-left"_j), node->getAttribute(u"padding-top"_j), node->getAttribute(u"padding-right"_j), node->getAttribute(u"padding-bottom"_j)), GUINode::createConditions(node->getAttribute(u"show-on"_j)), GUINode::createConditions(node->getAttribute(u"hide-on"_j)), GUILayoutNode::createAlignment(node->getAttribute(u"alignment"_j)));
				guiParentNode->addSubNode(guiLayoutNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiLayoutNode);
					if (guiElementController != nullptr) {
						guiLayoutNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseGUINode(guiLayoutNode, node, nullptr);
			} else if (node->getNodeName()->equals(u"space"_j)) {
				auto guiSpaceNode = new GUISpaceNode(guiParentNode->getScreenNode(), guiParentNode, node->getAttribute(u"id"_j), GUINode::createFlow(node->getAttribute(u"flow"_j)), GUINode::createAlignments(node->getAttribute(u"horizontal-align"_j), node->getAttribute(u"vertical-align"_j)), GUISpaceNode::createRequestedConstraints(node->getAttribute(u"left"_j), node->getAttribute(u"top"_j), node->getAttribute(u"width"_j), node->getAttribute(u"height"_j)), GUINode::getRequestedColor(node->getAttribute(u"background-color"_j), GUIColor::TRANSPARENT), GUINode::createBorder(node->getAttribute(u"border"_j), node->getAttribute(u"border-left"_j), node->getAttribute(u"border-top"_j), node->getAttribute(u"border-right"_j), node->getAttribute(u"border-bottom"_j), node->getAttribute(u"border-color"_j), node->getAttribute(u"border-color-left"_j), node->getAttribute(u"border-color-top"_j), node->getAttribute(u"border-color-right"_j), node->getAttribute(u"border-color-bottom"_j)), GUINode::createPadding(node->getAttribute(u"padding"_j), node->getAttribute(u"padding-left"_j), node->getAttribute(u"padding-top"_j), node->getAttribute(u"padding-right"_j), node->getAttribute(u"padding-bottom"_j)), GUINode::createConditions(node->getAttribute(u"show-on"_j)), GUINode::createConditions(node->getAttribute(u"hide-on"_j)));
				guiParentNode->addSubNode(guiSpaceNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiSpaceNode);
					if (guiElementController != nullptr) {
						guiSpaceNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
			} else if (node->getNodeName()->equals(u"element"_j)) {
				auto guiElementNode = new GUIElementNode(guiParentNode->getScreenNode(), guiParentNode, node->getAttribute(u"id"_j), GUINode::createFlow(node->getAttribute(u"flow"_j)), GUIParentNode::createOverflow(node->getAttribute(u"overflow-x"_j)), GUIParentNode::createOverflow(node->getAttribute(u"overflow-y"_j)), GUINode::createAlignments(node->getAttribute(u"horizontal-align"_j), node->getAttribute(u"vertical-align"_j)), GUINode::createRequestedConstraints(node->getAttribute(u"left"_j), node->getAttribute(u"top"_j), node->getAttribute(u"width"_j), node->getAttribute(u"height"_j)), GUINode::getRequestedColor(node->getAttribute(u"background-color"_j), GUIColor::TRANSPARENT), GUINode::createBorder(node->getAttribute(u"border"_j), node->getAttribute(u"border-left"_j), node->getAttribute(u"border-top"_j), node->getAttribute(u"border-right"_j), node->getAttribute(u"border-bottom"_j), node->getAttribute(u"border-color"_j), node->getAttribute(u"border-color-left"_j), node->getAttribute(u"border-color-top"_j), node->getAttribute(u"border-color-right"_j), node->getAttribute(u"border-color-bottom"_j)), GUINode::createPadding(node->getAttribute(u"padding"_j), node->getAttribute(u"padding-left"_j), node->getAttribute(u"padding-top"_j), node->getAttribute(u"padding-right"_j), node->getAttribute(u"padding-bottom"_j)), GUINode::createConditions(node->getAttribute(u"show-on"_j)), GUINode::createConditions(node->getAttribute(u"hide-on"_j)), unescapeQuotes(node->getAttribute(u"name"_j)), unescapeQuotes(node->getAttribute(u"value"_j)), node->getAttribute(u"selected"_j)->trim()->equalsIgnoreCase(u"true"_j), node->getAttribute(u"disabled"_j)->trim()->equalsIgnoreCase(u"true"_j), node->getAttribute(u"focusable"_j)->trim()->equalsIgnoreCase(u"true"_j), node->getAttribute(u"ignore-events"_j)->trim()->equalsIgnoreCase(u"true"_j));
				guiParentNode->addSubNode(guiElementNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiElementNode);
					if (guiElementController != nullptr) {
						guiElementNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
				parseGUINode(guiElementNode, node, nullptr);
			} else if (node->getNodeName()->equals(u"image"_j)) {
				auto guiImageNode = new GUIImageNode(guiParentNode->getScreenNode(), guiParentNode, node->getAttribute(u"id"_j), GUINode::createFlow(node->getAttribute(u"flow"_j)), GUINode::createAlignments(node->getAttribute(u"horizontal-align"_j), node->getAttribute(u"vertical-align"_j)), GUINode::createRequestedConstraints(node->getAttribute(u"left"_j), node->getAttribute(u"top"_j), node->getAttribute(u"width"_j), node->getAttribute(u"height"_j)), GUINode::getRequestedColor(node->getAttribute(u"background-color"_j), GUIColor::TRANSPARENT), GUINode::createBorder(node->getAttribute(u"border"_j), node->getAttribute(u"border-left"_j), node->getAttribute(u"border-top"_j), node->getAttribute(u"border-right"_j), node->getAttribute(u"border-bottom"_j), node->getAttribute(u"border-color"_j), node->getAttribute(u"border-color-left"_j), node->getAttribute(u"border-color-top"_j), node->getAttribute(u"border-color-right"_j), node->getAttribute(u"border-color-bottom"_j)), GUINode::createPadding(node->getAttribute(u"padding"_j), node->getAttribute(u"padding-left"_j), node->getAttribute(u"padding-top"_j), node->getAttribute(u"padding-right"_j), node->getAttribute(u"padding-bottom"_j)), GUINode::createConditions(node->getAttribute(u"show-on"_j)), GUINode::createConditions(node->getAttribute(u"hide-on"_j)), unescapeQuotes(node->getAttribute(u"src"_j)), GUINode::getRequestedColor(node->getAttribute(u"effect-color-mul"_j), GUIColor::EFFECT_COLOR_MUL), GUINode::getRequestedColor(node->getAttribute(u"effect-color-add"_j), GUIColor::EFFECT_COLOR_ADD));
				guiParentNode->addSubNode(guiImageNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiImageNode);
					if (guiElementController != nullptr) {
						guiImageNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
			} else if (node->getNodeName()->equals(u"text"_j)) {
				auto guiTextNode = new GUITextNode(guiParentNode->getScreenNode(), guiParentNode, node->getAttribute(u"id"_j), GUINode::createFlow(node->getAttribute(u"flow"_j)), GUINode::createAlignments(node->getAttribute(u"horizontal-align"_j), node->getAttribute(u"vertical-align"_j)), GUINode::createRequestedConstraints(node->getAttribute(u"left"_j), node->getAttribute(u"top"_j), node->getAttribute(u"width"_j), node->getAttribute(u"height"_j)), GUINode::getRequestedColor(node->getAttribute(u"background-color"_j), GUIColor::TRANSPARENT), GUINode::createBorder(node->getAttribute(u"border"_j), node->getAttribute(u"border-left"_j), node->getAttribute(u"border-top"_j), node->getAttribute(u"border-right"_j), node->getAttribute(u"border-bottom"_j), node->getAttribute(u"border-color"_j), node->getAttribute(u"border-color-left"_j), node->getAttribute(u"border-color-top"_j), node->getAttribute(u"border-color-right"_j), node->getAttribute(u"border-color-bottom"_j)), GUINode::createPadding(node->getAttribute(u"padding"_j), node->getAttribute(u"padding-left"_j), node->getAttribute(u"padding-top"_j), node->getAttribute(u"padding-right"_j), node->getAttribute(u"padding-bottom"_j)), GUINode::createConditions(node->getAttribute(u"show-on"_j)), GUINode::createConditions(node->getAttribute(u"hide-on"_j)), node->getAttribute(u"font"_j), node->getAttribute(u"color"_j), new MutableString(unescapeQuotes(node->getAttribute(u"text"_j))));
				guiParentNode->addSubNode(guiTextNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiTextNode);
					if (guiElementController != nullptr) {
						guiTextNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
			} else if (node->getNodeName()->equals(u"input-internal"_j)) {
				auto guiInputInternalNode = new GUIInputInternalNode(guiParentNode->getScreenNode(), guiParentNode, node->getAttribute(u"id"_j), GUINode::createFlow(node->getAttribute(u"flow"_j)), GUINode::createAlignments(node->getAttribute(u"horizontal-align"_j), node->getAttribute(u"vertical-align"_j)), GUINode::createRequestedConstraints(node->getAttribute(u"left"_j), node->getAttribute(u"top"_j), node->getAttribute(u"width"_j), node->getAttribute(u"height"_j)), GUINode::getRequestedColor(node->getAttribute(u"background-color"_j), GUIColor::TRANSPARENT), GUINode::createBorder(node->getAttribute(u"border"_j), node->getAttribute(u"border-left"_j), node->getAttribute(u"border-top"_j), node->getAttribute(u"border-right"_j), node->getAttribute(u"border-bottom"_j), node->getAttribute(u"border-color"_j), node->getAttribute(u"border-color-left"_j), node->getAttribute(u"border-color-top"_j), node->getAttribute(u"border-color-right"_j), node->getAttribute(u"border-color-bottom"_j)), GUINode::createPadding(node->getAttribute(u"padding"_j), node->getAttribute(u"padding-left"_j), node->getAttribute(u"padding-top"_j), node->getAttribute(u"padding-right"_j), node->getAttribute(u"padding-bottom"_j)), GUINode::createConditions(node->getAttribute(u"show-on"_j)), GUINode::createConditions(node->getAttribute(u"hide-on"_j)), node->getAttribute(u"font"_j), node->getAttribute(u"color"_j), node->getAttribute(u"color-disabled"_j), new MutableString(unescapeQuotes(node->getAttribute(u"text"_j))), GUIInputInternalNode::createMaxLength(node->getAttribute(u"maxlength"_j)));
				guiParentNode->addSubNode(guiInputInternalNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiInputInternalNode);
					if (guiElementController != nullptr) {
						guiInputInternalNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
			} else if (node->getNodeName()->equals(u"vertical-scrollbar-internal"_j)) {
				auto guiVerticalScrollbarInternalNode = new GUIVerticalScrollbarInternalNode(guiParentNode->getScreenNode(), guiParentNode, node->getAttribute(u"id"_j), GUINode::createFlow(node->getAttribute(u"flow"_j)), GUINode::createAlignments(node->getAttribute(u"horizontal-align"_j), node->getAttribute(u"vertical-align"_j)), GUINode::createRequestedConstraints(node->getAttribute(u"left"_j), node->getAttribute(u"top"_j), node->getAttribute(u"width"_j), node->getAttribute(u"height"_j)), GUINode::getRequestedColor(node->getAttribute(u"background-color"_j), GUIColor::TRANSPARENT), GUINode::createBorder(node->getAttribute(u"border"_j), node->getAttribute(u"border-left"_j), node->getAttribute(u"border-top"_j), node->getAttribute(u"border-right"_j), node->getAttribute(u"border-bottom"_j), node->getAttribute(u"border-color"_j), node->getAttribute(u"border-color-left"_j), node->getAttribute(u"border-color-top"_j), node->getAttribute(u"border-color-right"_j), node->getAttribute(u"border-color-bottom"_j)), GUINode::createPadding(node->getAttribute(u"padding"_j), node->getAttribute(u"padding-left"_j), node->getAttribute(u"padding-top"_j), node->getAttribute(u"padding-right"_j), node->getAttribute(u"padding-bottom"_j)), GUINode::createConditions(node->getAttribute(u"show-on"_j)), GUINode::createConditions(node->getAttribute(u"hide-on"_j)), GUINode::getRequestedColor(node->getAttribute(u"color-none"_j), GUIColor::BLACK), GUINode::getRequestedColor(node->getAttribute(u"color-mouseover"_j), GUIColor::BLACK), GUINode::getRequestedColor(node->getAttribute(u"color-dragging"_j), GUIColor::BLACK));
				guiParentNode->addSubNode(guiVerticalScrollbarInternalNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiVerticalScrollbarInternalNode);
					if (guiElementController != nullptr) {
						guiVerticalScrollbarInternalNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
			} else if (node->getNodeName()->equals(u"horizontal-scrollbar-internal"_j)) {
				auto guiHorizontalScrollbarInternalNode = new GUIHorizontalScrollbarInternalNode(guiParentNode->getScreenNode(), guiParentNode, node->getAttribute(u"id"_j), GUINode::createFlow(node->getAttribute(u"flow"_j)), GUINode::createAlignments(node->getAttribute(u"horizontal-align"_j), node->getAttribute(u"vertical-align"_j)), GUINode::createRequestedConstraints(node->getAttribute(u"left"_j), node->getAttribute(u"top"_j), node->getAttribute(u"width"_j), node->getAttribute(u"height"_j)), GUINode::getRequestedColor(node->getAttribute(u"background-color"_j), GUIColor::TRANSPARENT), GUINode::createBorder(node->getAttribute(u"border"_j), node->getAttribute(u"border-left"_j), node->getAttribute(u"border-top"_j), node->getAttribute(u"border-right"_j), node->getAttribute(u"border-bottom"_j), node->getAttribute(u"border-color"_j), node->getAttribute(u"border-color-left"_j), node->getAttribute(u"border-color-top"_j), node->getAttribute(u"border-color-right"_j), node->getAttribute(u"border-color-bottom"_j)), GUINode::createPadding(node->getAttribute(u"padding"_j), node->getAttribute(u"padding-left"_j), node->getAttribute(u"padding-top"_j), node->getAttribute(u"padding-right"_j), node->getAttribute(u"padding-bottom"_j)), GUINode::createConditions(node->getAttribute(u"show-on"_j)), GUINode::createConditions(node->getAttribute(u"hide-on"_j)), GUINode::getRequestedColor(node->getAttribute(u"color-none"_j), GUIColor::BLACK), GUINode::getRequestedColor(node->getAttribute(u"color-mouseover"_j), GUIColor::BLACK), GUINode::getRequestedColor(node->getAttribute(u"color-dragging"_j), GUIColor::BLACK));
				guiParentNode->addSubNode(guiHorizontalScrollbarInternalNode);
				if (guiElement != nullptr && guiElementControllerInstalled == false) {
					guiElementController = guiElement->createController(guiHorizontalScrollbarInternalNode);
					if (guiElementController != nullptr) {
						guiHorizontalScrollbarInternalNode->setController(guiElementController);
					}
					guiElementControllerInstalled = true;
				}
			} else {
				auto newGuiElement = java_cast< GUIElement* >(elements->get(node->getNodeName()));
				if (newGuiElement == nullptr) {
					throw new GUIParserException(::java::lang::StringBuilder().append(u"Unknown element '"_j)->append(node->getNodeName())
						->append(u"'"_j)->toString());
				}
				auto newGuiElementTemplate = newGuiElement->getTemplate();
				for (auto i = 0; i < node->getAttributes()->getLength(); i++) {
					auto attribute = node->getAttributes()->item(i);
					newGuiElementTemplate = newGuiElementTemplate->replace(static_cast< CharSequence* >(::java::lang::StringBuilder().append(u"{$"_j)->append(attribute->getNodeName())
						->append(u"}"_j)->toString()), static_cast< CharSequence* >(escapeQuotes(attribute->getNodeValue())));
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
				newGuiElementTemplate = newGuiElementTemplate->replace(static_cast< CharSequence* >(u"{$innerXml}"_j), static_cast< CharSequence* >(getInnerXml(node)));
				auto newGuiElementBuilder = DocumentBuilderFactory::newInstance()->newDocumentBuilder();
				auto newGuiElementDocument = newGuiElementBuilder->parse(static_cast< InputStream* >(new ByteArrayInputStream((new String(::java::lang::StringBuilder().append(u"<gui-element>\n"_j)->append(newGuiElementTemplate)
					->append(u"</gui-element>\n"_j)->toString()))->getBytes())));
				parseGUINode(guiParentNode, newGuiElementDocument->getDocumentElement(), newGuiElement);
			}
		}
	}
	if (guiElementController != nullptr) {
		guiElementController->initialize();
	}
}

_ArrayList* GUIParser::getChildrenTags(Element* parent)
{
	clinit();
	auto nodeList = new _ArrayList();
	for (auto *child = parent->getFirstChild(); child != nullptr; child = child->getNextSibling()) {
		if (child->getNodeType() == Node::ELEMENT_NODE) {
			nodeList->add(java_cast< Element* >(child));
		}
	}
	return nodeList;
}

String* GUIParser::getInnerXml(Node* node)
{
	clinit();
	auto lsImpl = java_cast< DOMImplementationLS* >(node->getOwnerDocument()->getImplementation()->getFeature(u"LS"_j, u"3.0"_j));
	auto lsSerializer = lsImpl->createLSSerializer();
	auto childNodes = node->getChildNodes();
	auto sb = new StringBuilder();
	for (auto i = 0; i < childNodes->getLength(); i++) {
		sb->append(lsSerializer->writeToString(childNodes->item(i)));
	}
	auto result = sb->toString();
	result = result->replace(static_cast< CharSequence* >(u"<?xml version=\"1.0\" encoding=\"UTF-16\"?>"_j), static_cast< CharSequence* >(u""_j));
	return result;
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
				GUIElement* guiElement = new GUICheckbox();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUIRadioButton();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUISelectBox();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUISelectBoxOption();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUISelectBoxMultiple();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUISelectBoxMultipleOption();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUIDropDown();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUIDropDownOption();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUITabs();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUITabsHeader();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUITab();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUITabsContent();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUITabContent();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUIButton();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUIInput();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUIScrollAreaVertical();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
				GUIElement* guiElement = new GUIScrollAreaHorizontal();
				addElement(guiElement);
			} catch (Exception* e) {
				e->printStackTrace();
			}
			try {
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

