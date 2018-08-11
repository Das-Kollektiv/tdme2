#include <tdme/gui/nodes/GUIElementNode.h>

#include <set>

#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUIElementIgnoreEventsController.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode_Overflow.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>

using std::set;

using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementIgnoreEventsController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;

GUIElementNode::GUIElementNode(
	GUIScreenNode* screenNode,
	GUIParentNode* parentNode,
	const string& id,
	GUINode_Flow* flow,
	GUIParentNode_Overflow* overflowX,
	GUIParentNode_Overflow* overflowY,
	const GUINode_Alignments& alignments,
	const GUINode_RequestedConstraints& requestedConstraints,
	const GUIColor& backgroundColor,
	const string& backgroundImage,
	const GUINode_Scale9Grid& backgroundImageScaleGrid,
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn,
	const string& name,
	const string& value,
	bool selected,
	bool disabled,
	bool focusable,
	bool ignoreEvents,
	const string& onInitializeExpression,
	const string& onMouseClickExpression,
	const string& onMouseOverExpression,
	const string& onMouseOutExpression)
	throw (GUIParserException) :
	GUIParentNode(screenNode, parentNode, id, flow, overflowX, overflowY, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScaleGrid, border, padding, showOn, hideOn),
	activeConditions(this)
{
	init();
	this->name = name;
	this->value = value;
	this->selected = selected;
	this->disabled = disabled;
	this->focusable = focusable;
	this->ignoreEvents = ignoreEvents;
	this->onInitializeExpression = onInitializeExpression;
	this->onMouseClickExpression = onMouseClickExpression;
	this->onMouseOverExpression = onMouseOverExpression;
	this->onMouseOutExpression = onMouseOutExpression;
	this->controller = ignoreEvents == true ? static_cast< GUINodeController* >(new GUIElementIgnoreEventsController(this)) : static_cast< GUINodeController* >(new GUIElementController(this));
	this->controller->initialize();
}

void GUIElementNode::init()
{
}

string GUIElementNode::CONDITION_ALWAYS = "always";
string GUIElementNode::CONDITION_ONMOUSEOVER = "mouseover";
string GUIElementNode::CONDITION_CLICK = "click";
string GUIElementNode::CONDITION_FOCUS = "focus";

const string GUIElementNode::getNodeType()
{
	return "element";
}

bool GUIElementNode::isContentNode()
{
	return false;
}

int32_t GUIElementNode::getContentWidth()
{
	auto width = 0;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		auto contentWidth = guiSubNode->getAutoWidth();
		if (contentWidth > width) {
			width = contentWidth;
		}
	}
	width += border.left + border.right;
	width += padding.left + padding.right;
	return width;
}

int32_t GUIElementNode::getContentHeight()
{
	auto height = 0;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		auto contentHeight = guiSubNode->getAutoHeight();
		if (contentHeight > height) {
			height = contentHeight;
		}
	}
	height += border.top + border.bottom;
	height += padding.top + padding.bottom;
	return height;
}

bool GUIElementNode::isFocusable()
{
	return focusable;
}

void GUIElementNode::setTop(int32_t top)
{
	GUIParentNode::setTop(top);
	top += computedConstraints.alignmentTop;
	for (auto i = 0; i < subNodes.size(); i++) {
		subNodes[i]->setTop(top);
	}
}

void GUIElementNode::setLeft(int32_t left)
{
	GUIParentNode::setLeft(left);
	left += computedConstraints.alignmentLeft;
	for (auto i = 0; i < subNodes.size(); i++) {
		subNodes[i]->setLeft(left);
	}
}

void GUIElementNode::layoutSubNodes()
{
	GUIParentNode::layoutSubNodes();
	auto height = computedConstraints.height - border.top - border.bottom - padding.top - padding.bottom;
	auto width = computedConstraints.width - border.left - border.right - padding.left - padding.right;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		auto doLayoutSubNodes = false;
		if (guiSubNode->requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR) {
			guiSubNode->computedConstraints.height = height;
			doLayoutSubNodes = true;
		} else if (guiSubNode->requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR) {
			guiSubNode->computedConstraints.width = width;
			doLayoutSubNodes = true;
		}
		if (dynamic_cast< GUIParentNode* >(guiSubNode) != nullptr && doLayoutSubNodes == true) {
			(dynamic_cast< GUIParentNode* >(guiSubNode))->layoutSubNodes();
		}
	}
}

void GUIElementNode::layout()
{
	if (requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) {
		auto subNodesHeight = requestedConstraints.height - border.top - border.bottom - padding.top - padding.bottom;
		for (auto i = 0; i < subNodes.size(); i++) {
			auto subNode = subNodes[i];
			if (overflowY == GUIParentNode_Overflow::DOWNSIZE_CHILDREN && subNode->requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL && subNode->requestedConstraints.height > subNodesHeight) {
				subNode->requestedConstraints.height = subNodesHeight;
			}
		}
	}
	if (requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) {
		auto subNodesWidth = requestedConstraints.width - border.left - border.right- padding.left - padding.right;
		for (auto i = 0; i < subNodes.size(); i++) {
			auto subNode = subNodes[i];
			if (overflowY == GUIParentNode_Overflow::DOWNSIZE_CHILDREN && subNode->requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL && subNode->requestedConstraints.width > subNodesWidth) {
				subNode->requestedConstraints.width = subNodesWidth;
			}
		}
	}
	GUIParentNode::layout();
	setTop(computedConstraints.top);
	setLeft(computedConstraints.left);
	computeHorizontalChildrenAlignment();
	computeVerticalChildrenAlignment();
}

const string& GUIElementNode::getName()
{
	return name;
}

const string& GUIElementNode::getValue()
{
	return value;
}

bool GUIElementNode::isSelected()
{
	return selected;
}

bool GUIElementNode::isDisabled()
{
	return disabled;
}

const string& GUIElementNode::getOnInitializeExpression() {
	return onInitializeExpression;
}

const string& GUIElementNode::getOnMouseClickExpression() {
	return onMouseClickExpression;
}

const string& GUIElementNode::getOnMouseOverExpression() {
	return onMouseOverExpression;
}

const string& GUIElementNode::getOnMouseOutExpression() {
	return onMouseOutExpression;
}

GUINodeConditions& GUIElementNode::getActiveConditions()
{
	return activeConditions;
}

void GUIElementNode::determineMouseEventNodes(GUIMouseEvent* event, set<string>& eventNodeIds)
{
	if (conditionsMet == false)
		return;

	activeConditions.remove(CONDITION_ONMOUSEOVER);
	activeConditions.remove(CONDITION_CLICK);
	if (screenNode->mouseEventProcessedByFloatingNode == true)
		return;

	if (isEventBelongingToNode(event)) {
		{
			auto v = event->getType();
			if (v == GUIMouseEvent_Type::MOUSEEVENT_MOVED) {
				activeConditions.add(CONDITION_ONMOUSEOVER);
				if (ignoreEvents == false) event->setProcessed(true);
			} else
			if (v == GUIMouseEvent_Type::MOUSEEVENT_PRESSED ||
				v == GUIMouseEvent_Type::MOUSEEVENT_DRAGGED) {
				activeConditions.add(CONDITION_CLICK);
				if (ignoreEvents == false) event->setProcessed(true);
			}
		}
	}

	GUIParentNode::determineMouseEventNodes(event, eventNodeIds);
}

void GUIElementNode::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	if (ignoreEvents == true)
		return;

	if (conditionsMet == false)
		return;

	for (auto i = 0; i < subNodes.size(); i++) {
		auto subNode = subNodes[i];
		subNode->handleKeyboardEvent(event);
	}
	GUIParentNode::handleKeyboardEvent(event);
}

