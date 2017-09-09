// Generated from /tdme/src/tdme/gui/nodes/GUIParentNode.java
#include <tdme/gui/nodes/GUIParentNode.h>

#include <string>
#include <vector>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/GUIParserException.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUINode_AlignmentHorizontal.h>
#include <tdme/gui/nodes/GUINode_AlignmentVertical.h>
#include <tdme/gui/nodes/GUINode_Alignments.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Flow.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode_Overflow.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/utils/StringConverter.h>

using std::vector;
using std::wstring;

using tdme::gui::nodes::GUIParentNode;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::gui::GUIParserException;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIRenderer;
using tdme::utils::StringConverter;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUIParentNode::GUIParentNode(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIParentNode::GUIParentNode(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn)  /* throws(GUIParserException) */
	: GUIParentNode(*static_cast< ::default_init_tag* >(0))
{
	ctor(screenNode,parentNode,id,flow,overflowX,overflowY,alignments,requestedConstraints,backgroundColor,border,padding,showOn,hideOn);
}

void GUIParentNode::ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, const wstring& id, GUINode_Flow* flow, GUIParentNode_Overflow* overflowX, GUIParentNode_Overflow* overflowY, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn) /* throws(GUIParserException) */
{
	super::ctor(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, border, padding, showOn, hideOn);
	this->overflowX = overflowX;
	this->overflowY = overflowY;
	this->childrenRenderOffsetX = 0.0f;
	this->childrenRenderOffsetY = 0.0f;
}

void GUIParentNode::clearSubNodes()
{
	childrenRenderOffsetX = 0.0f;
	childrenRenderOffsetY = 0.0f;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto node = subNodes.at(i);
		screenNode->removeNode(node);
		node->dispose();
	}
	subNodes.clear();
}

void GUIParentNode::replaceSubNodes(String* xml, bool resetScrollOffsets) /* throws(Exception) */
{
	if (resetScrollOffsets == true) {
		childrenRenderOffsetX = 0.0f;
		childrenRenderOffsetY = 0.0f;
	}
	for (auto i = 0; i < subNodes.size(); i++) {
		auto node = subNodes.at(i);
		screenNode->removeNode(node);
		node->dispose();
	}
	subNodes.clear();
	GUIParser::parse(this, xml);
	screenNode->layout(this);
	float elementWidth = computedConstraints->width;
	float contentWidth = getContentWidth();
	auto scrollableWidth = contentWidth - elementWidth;
	if (childrenRenderOffsetX < 0)
		childrenRenderOffsetX = 0;

	if (childrenRenderOffsetX > scrollableWidth)
		childrenRenderOffsetX = scrollableWidth;

	float elementHeight = computedConstraints->height;
	float contentHeight = getContentHeight();
	auto scrollableHeight = contentHeight - elementHeight;
	if (childrenRenderOffsetY < 0)
		childrenRenderOffsetY = 0;

	if (childrenRenderOffsetY > scrollableHeight)
		childrenRenderOffsetY = scrollableHeight;

}

void GUIParentNode::addSubNode(GUINode* node) throw (GUIParserException)
{
	if (screenNode->addNode(node) == false) {
		throw GUIParserException(
			"Screen '" +
			StringConverter::toString(screenNode->id) +
			"' already has a node attached with given node id '" +
			StringConverter::toString(node->id) +
			"'"
		);
	}
	subNodes.push_back(node);
}

GUIParentNode_Overflow* GUIParentNode::getOverflowX()
{
	return overflowX;
}

GUIParentNode_Overflow* GUIParentNode::getOverflowY()
{
	return overflowY;
}

GUIParentNode_Overflow* GUIParentNode::createOverflow(String* overflow) throw (GUIParserException)
{
	clinit();
	if (overflow->trim()->equalsIgnoreCase(u"hidden"_j) == true) {
		return GUIParentNode_Overflow::HIDDEN;
	} else
	if (overflow->trim()->equalsIgnoreCase(u"downsize-children"_j) == true) {
		return GUIParentNode_Overflow::DOWNSIZE_CHILDREN;
	} else
	if (overflow->trim()->equalsIgnoreCase(u"scroll"_j) == true) {
		return GUIParentNode_Overflow::SCROLL;
	} else
	if (overflow == nullptr || overflow->trim()->length() == 0) {
		return GUIParentNode_Overflow::HIDDEN;
	} else {
		throw GUIParserException(
			"Unknown overflow '" +
			StringConverter::toString(overflow->toString()->getCPPWString()) +
			"'"
		);
	}
}

float GUIParentNode::getChildrenRenderOffsetX()
{
	return childrenRenderOffsetX;
}

void GUIParentNode::setChildrenRenderOffsetX(float childrenRenderOffSetX)
{
	this->childrenRenderOffsetX = childrenRenderOffSetX;
}

float GUIParentNode::getChildrenRenderOffsetY()
{
	return childrenRenderOffsetY;
}

void GUIParentNode::setChildrenRenderOffsetY(float childrenRenderOffSetY)
{
	this->childrenRenderOffsetY = childrenRenderOffSetY;
}

GUINode_RequestedConstraints* GUIParentNode::createRequestedConstraints(String* left, String* top, String* width, String* height)
{
	clinit();
	auto constraints = new GUINode_RequestedConstraints();
	constraints->leftType = getRequestedConstraintsType(left->trim()->getCPPWString(), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints->left = getRequestedConstraintsValue(left->trim()->getCPPWString(), 0);
	constraints->topType = getRequestedConstraintsType(top->trim()->getCPPWString(), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints->top = getRequestedConstraintsValue(top->trim()->getCPPWString(), 0);
	constraints->widthType = getRequestedConstraintsType(width->trim()->getCPPWString(), GUINode_RequestedConstraints_RequestedConstraintsType::AUTO);
	constraints->width = getRequestedConstraintsValue(width->trim()->getCPPWString(), -1);
	constraints->heightType = getRequestedConstraintsType(height->trim()->getCPPWString(), GUINode_RequestedConstraints_RequestedConstraintsType::AUTO);
	constraints->height = getRequestedConstraintsValue(height->trim()->getCPPWString(), -1);
	return constraints;
}

void GUIParentNode::layout()
{
	super::layout();
	layoutSubNodes();
}

void GUIParentNode::layoutSubNodes()
{
	for (auto i = 0; i < subNodes.size(); i++) {
		subNodes.at(i)->layout();
	}
}

void GUIParentNode::computeHorizontalChildrenAlignment()
{
	{
		auto v = alignments->horizontal;
		if ((v == GUINode_AlignmentHorizontal::LEFT)) {
{
				for (auto i = 0; i < subNodes.size(); i++) {
					auto guiSubNode = subNodes.at(i);
					guiSubNode->computedConstraints->alignmentLeft = border->left + padding->left;
				}
				goto end_switch0;;
			}		}
		if ((v == GUINode_AlignmentHorizontal::LEFT) || (v == GUINode_AlignmentHorizontal::CENTER)) {
{
				for (auto i = 0; i < subNodes.size(); i++) {
					auto guiSubNode = subNodes.at(i);
					guiSubNode->computedConstraints->alignmentLeft = (computedConstraints->width - guiSubNode->computedConstraints->width) / 2;
				}
				goto end_switch0;;
			}		}
		if ((v == GUINode_AlignmentHorizontal::LEFT) || (v == GUINode_AlignmentHorizontal::CENTER) || (v == GUINode_AlignmentHorizontal::RIGHT)) {
{
{
					for (auto i = 0; i < subNodes.size(); i++) {
						auto guiSubNode = subNodes.at(i);
						guiSubNode->computedConstraints->alignmentLeft = (computedConstraints->width - guiSubNode->computedConstraints->width - border->right- padding->right);
					}
					goto end_switch0;;
				}
			}		}
end_switch0:;
	}

}

void GUIParentNode::computeVerticalChildrenAlignment()
{
	{
		auto v = alignments->vertical;
		if ((v == GUINode_AlignmentVertical::TOP)) {
{
				for (auto i = 0; i < subNodes.size(); i++) {
					auto guiSubNode = subNodes.at(i);
					guiSubNode->computedConstraints->alignmentTop = border->top + padding->top;
				}
				goto end_switch1;;
			}		}
		if ((v == GUINode_AlignmentVertical::TOP) || (v == GUINode_AlignmentVertical::CENTER)) {
{
				for (auto i = 0; i < subNodes.size(); i++) {
					auto guiSubNode = subNodes.at(i);
					guiSubNode->computedConstraints->alignmentTop = (computedConstraints->height - guiSubNode->computedConstraints->height) / 2;
				}
				goto end_switch1;;
			}		}
		if ((v == GUINode_AlignmentVertical::TOP) || (v == GUINode_AlignmentVertical::CENTER) || (v == GUINode_AlignmentVertical::BOTTOM)) {
{
{
					for (auto i = 0; i < subNodes.size(); i++) {
						auto guiSubNode = subNodes.at(i);
						guiSubNode->computedConstraints->alignmentTop = (computedConstraints->height - guiSubNode->computedConstraints->height - border->bottom- padding->bottom);
					}
					goto end_switch1;;
				}
			}		}
end_switch1:;
	}

}

void GUIParentNode::getChildControllerNodesInternal(vector<GUINode*>* childControllerNodes)
{
	for (auto i = 0; i < subNodes.size(); i++) {
		auto node = subNodes.at(i);
		if (node->controller != nullptr) {
			childControllerNodes->push_back(node);
		}
		if (dynamic_cast< GUIParentNode* >(node) != nullptr) {
			(java_cast< GUIParentNode* >(node))->getChildControllerNodesInternal(childControllerNodes);
		}
	}
}

void GUIParentNode::getChildControllerNodes(vector<GUINode*>*childControllerNodes)
{
	childControllerNodes->clear();
	getChildControllerNodesInternal(childControllerNodes);
}

void GUIParentNode::dispose()
{
	for (auto i = 0; i < subNodes.size(); i++) {
		subNodes.at(i)->dispose();
	}
	super::dispose();
}

void GUIParentNode::setConditionsMet()
{
	conditionsMet = checkConditions();
	if (conditionsMet == false)
		return;

	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes.at(i);
		guiSubNode->setConditionsMet();
	}
}

void GUIParentNode::render(GUIRenderer* guiRenderer, vector<GUINode*>* floatingNodes)
{
	if (conditionsMet == false)
		return;

	auto renderAreaLeftCurrent = guiRenderer->getRenderAreaLeft();
	auto renderAreaTopCurrent = guiRenderer->getRenderAreaTop();
	auto renderAreaRightCurrent = guiRenderer->getRenderAreaRight();
	auto renderAreaBottomCurrent = guiRenderer->getRenderAreaBottom();
	float screenWidth = guiRenderer->getGUI()->getWidth();
	float screenHeight = guiRenderer->getGUI()->getHeight();
	float left = computedConstraints->left + computedConstraints->alignmentLeft;
	float top = computedConstraints->top + computedConstraints->alignmentTop;
	float width = computedConstraints->width;
	float height = computedConstraints->height;
	auto renderOffsetXCurrent = guiRenderer->getRenderOffsetX();
	auto renderOffsetYCurrent = guiRenderer->getRenderOffsetY();
	auto renderOffsetXPixel = 0.0f;
	auto renderOffsetYPixel = 0.0f;
	for (auto *parentNode = this; parentNode != nullptr; parentNode = parentNode->parentNode) {
		renderOffsetXPixel += parentNode->childrenRenderOffsetX;
		renderOffsetYPixel += parentNode->childrenRenderOffsetY;
	}
	auto renderOffsetX = renderOffsetXPixel / (screenWidth / 2.0f);
	auto renderOffsetY = renderOffsetYPixel / (screenHeight / 2.0f);
	auto renderAreaLeft = ((left) / (screenWidth / 2.0f)) - 1.0f;
	auto renderAreaTop = ((screenHeight - top) / (screenHeight / 2.0f)) + renderOffsetYCurrent - 1.0f;
	auto renderAreaRight = ((left + width) / (screenWidth / 2.0f)) - 1.0f;
	auto renderAreaBottom = ((screenHeight - top - height) / (screenHeight / 2.0f)) + renderOffsetYCurrent - 1.0f;
	guiRenderer->setSubRenderAreaLeft(renderAreaLeft);
	guiRenderer->setSubRenderAreaTop(renderAreaTop);
	guiRenderer->setSubRenderAreaRight(renderAreaRight);
	guiRenderer->setSubRenderAreaBottom(renderAreaBottom);
	guiRenderer->setRenderOffsetX(renderOffsetX);
	guiRenderer->setRenderOffsetY(renderOffsetY);
	super::render(guiRenderer, floatingNodes);
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = java_cast< GUINode* >(subNodes.at(i));
		if (guiSubNode->flow == GUINode_Flow::FLOATING) {
			floatingNodes->push_back(guiSubNode);
			continue;
		}
		guiRenderer->setRenderAreaLeft(renderAreaLeftCurrent);
		guiRenderer->setRenderAreaTop(renderAreaTopCurrent);
		guiRenderer->setRenderAreaRight(renderAreaRightCurrent);
		guiRenderer->setRenderAreaBottom(renderAreaBottomCurrent);
		guiRenderer->setSubRenderAreaLeft(renderAreaLeft);
		guiRenderer->setSubRenderAreaTop(renderAreaTop);
		guiRenderer->setSubRenderAreaRight(renderAreaRight);
		guiRenderer->setSubRenderAreaBottom(renderAreaBottom);
		guiRenderer->setRenderOffsetX(renderOffsetX);
		guiRenderer->setRenderOffsetY(renderOffsetY);
		guiSubNode->render(guiRenderer, floatingNodes);
	}
	guiRenderer->setRenderOffsetX(renderOffsetXCurrent);
	guiRenderer->setRenderOffsetY(renderOffsetYCurrent);
	guiRenderer->setRenderAreaLeft(renderAreaLeftCurrent);
	guiRenderer->setRenderAreaTop(renderAreaTopCurrent);
	guiRenderer->setRenderAreaRight(renderAreaRightCurrent);
	guiRenderer->setRenderAreaBottom(renderAreaBottomCurrent);
}

void GUIParentNode::handleMouseEvent(GUIMouseEvent* event)
{
	if (conditionsMet == false)
		return;

	if (screenNode->mouseEventProcessedByFloatingNode == true)
		return;

	if (isEventBelongingToNode(event) == true && event->getType() == GUIMouseEvent_Type::MOUSE_WHEEL_MOVED) {
		if (event->getWheelX() != 0.0f && overflowX == GUIParentNode_Overflow::SCROLL) {
			childrenRenderOffsetX -= event->getWheelX();
			float elementWidth = this->computedConstraints->width;
			float contentWidth = this->getContentWidth();
			auto scrollableWidth = contentWidth - elementWidth;
			if (childrenRenderOffsetX < 0)
				childrenRenderOffsetX = 0;

			if (childrenRenderOffsetX > scrollableWidth)
				childrenRenderOffsetX = scrollableWidth;

			event->setProcessed(true);
			return;
		}
		if (event->getWheelY() != 0.0f && overflowY == GUIParentNode_Overflow::SCROLL) {
			childrenRenderOffsetY -= event->getWheelY();
			float elementHeight = this->computedConstraints->height;
			float contentHeight = this->getContentHeight();
			auto scrollableHeight = contentHeight - elementHeight;
			if (childrenRenderOffsetY < 0)
				childrenRenderOffsetY = 0;

			if (childrenRenderOffsetY > scrollableHeight)
				childrenRenderOffsetY = scrollableHeight;

			event->setProcessed(true);
			return;
		}
	}
	for (auto i = 0; i < subNodes.size(); i++) {
		auto subNode = java_cast< GUINode* >(subNodes.at(i));
		if (subNode->flow == GUINode_Flow::FLOATING) {
			continue;
		}
		subNode->handleMouseEvent(event);
	}
	super::handleMouseEvent(event);
	if (flow == GUINode_Flow::FLOATING && event->isProcessed() == true) {
		screenNode->mouseEventProcessedByFloatingNode = true;
	}
}

void GUIParentNode::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	if (conditionsMet == false)
		return;

	super::handleKeyboardEvent(event);
}

void GUIParentNode::tick()
{
	if (conditionsMet == false)
		return;

	for (auto i = 0; i < subNodes.size(); i++) {
		auto subNode = java_cast< GUINode* >(subNodes.at(i));
		subNode->tick();
	}
	super::tick();
}

String* GUIParentNode::toString()
{
	return toString(0);
}

String* GUIParentNode::toString(int32_t indent)
{
	auto tmp = ::java::lang::StringBuilder().append(static_cast< GUINode* >(this)->indent(indent))->append(u"GUIParentNode ["_j)
		->append(u"type="_j)
		->append(getNodeType())
		->append(u", id="_j)
		->append(id)
		->append(u", alignments="_j)
		->append(static_cast< Object* >(alignments))
		->append(u", requestedConstraints="_j)
		->append(static_cast< Object* >(requestedConstraints))
		->append(u", computedConstraints="_j)
		->append(static_cast< Object* >(computedConstraints))
		->append(u", border="_j)
		->append(static_cast< Object* >(border))
		->append(u", padding="_j)
		->append(static_cast< Object* >(padding))
		->append(u", controller="_j)
		->append((this->controller != nullptr ? u"yes"_j : u"no"_j))
		->append(u"]"_j)
		->append(u"\n"_j)->toString();
	for (auto i = 0; i < subNodes.size(); i++) {
		tmp = ::java::lang::StringBuilder(tmp).append(::java::lang::StringBuilder().append(java_cast< GUINode* >(subNodes.at(i))->toString(indent + 1))->append((i == subNodes.size() - 1 ? u""_j : u"\n"_j))->toString())->toString();
	}
	return tmp;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIParentNode::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIParentNode", 28);
    return c;
}

java::lang::Class* GUIParentNode::getClass0()
{
	return class_();
}

