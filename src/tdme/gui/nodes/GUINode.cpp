// Generated from /tdme/src/tdme/gui/nodes/GUINode.java
#include <tdme/gui/nodes/GUINode.h>

#include <java/lang/Integer.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/StringTokenizer.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode_AlignmentHorizontal.h>
#include <tdme/gui/nodes/GUINode_AlignmentVertical.h>
#include <tdme/gui/nodes/GUINode_Alignments.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Flow.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode_Overflow.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <Array.h>

using tdme::gui::nodes::GUINode;
using java::lang::Integer;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::StringTokenizer;
using tdme::gui::GUI;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIRenderer;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUINode::GUINode(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUINode::GUINode(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn) 
	: GUINode(*static_cast< ::default_init_tag* >(0))
{
	ctor(screenNode,parentNode,id,flow,alignments,requestedConstraints,backgroundColor,border,padding,showOn,hideOn);
}

void GUINode::ctor(GUIScreenNode* screenNode, GUIParentNode* parentNode, String* id, GUINode_Flow* flow, GUINode_Alignments* alignments, GUINode_RequestedConstraints* requestedConstraints, GUIColor* backgroundColor, GUINode_Border* border, GUINode_Padding* padding, GUINodeConditions* showOn, GUINodeConditions* hideOn)
{
	super::ctor();
	this->screenNode = screenNode;
	this->parentNode = parentNode;
	this->id = id;
	this->flow = flow;
	this->alignments = alignments;
	this->requestedConstraints = requestedConstraints;
	this->computedConstraints = new GUINode_ComputedConstraints();
	this->computedConstraints->alignmentLeft = 0;
	this->computedConstraints->alignmentTop = 0;
	this->computedConstraints->contentAlignmentLeft = 0;
	this->computedConstraints->contentAlignmentTop = 0;
	this->backgroundColor = backgroundColor;
	this->border = border;
	this->padding = padding;
	this->showOn = showOn;
	this->hideOn = hideOn;
	this->controller = nullptr;
	this->conditionsMet = false;
}

GUIScreenNode* GUINode::getScreenNode()
{
	return screenNode;
}

GUIParentNode* GUINode::getParentNode()
{
	return parentNode;
}

String* GUINode::getId()
{
	return id;
}

int32_t GUINode::getAutoWidth()
{
	if (requestedConstraints->widthType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		return getContentWidth();
	} else {
		return computedConstraints->width;
	}
}

int32_t GUINode::getAutoHeight()
{
	if (requestedConstraints->heightType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		return getContentHeight();
	} else {
		return computedConstraints->height;
	}
}

GUINode_Border* GUINode::getBorder()
{
	return border;
}

GUINode_RequestedConstraints* GUINode::getRequestsConstraints()
{
	return requestedConstraints;
}

GUINode_ComputedConstraints* GUINode::getComputedConstraints()
{
	return computedConstraints;
}

void GUINode::setLeft(int32_t left)
{
	computedConstraints->left = left;
}

void GUINode::setTop(int32_t top)
{
	computedConstraints->top = top;
}

void GUINode::layout()
{
	auto parentNodeContentWidth = parentNode->computedConstraints->width - parentNode->border->left - parentNode->border->right- parentNode->padding->left- parentNode->padding->right;
	auto parentNodeContentHeight = parentNode->computedConstraints->height - parentNode->border->top - parentNode->border->bottom- parentNode->padding->top- parentNode->padding->bottom;
	computedConstraints->left = parentNode->computedConstraints->left + layoutConstraintPixel(requestedConstraints->leftType, 0, parentNodeContentWidth, requestedConstraints->left);
	computedConstraints->top = parentNode->computedConstraints->top + layoutConstraintPixel(requestedConstraints->topType, 0, parentNodeContentHeight, requestedConstraints->top);
	computedConstraints->width = layoutConstraintPixel(requestedConstraints->widthType, getAutoWidth(), parentNodeContentWidth, requestedConstraints->width);
	computedConstraints->height = layoutConstraintPixel(requestedConstraints->heightType, getAutoHeight(), parentNodeContentHeight, requestedConstraints->height);
	computeContentAlignment();
}

void GUINode::computeContentAlignment()
{
	if (isContentNode() == true) {
		{
			auto v = alignments->horizontal;
			if ((v == GUINode_AlignmentHorizontal::LEFT)) {
{
					computedConstraints->contentAlignmentLeft = border->left + padding->left;
					goto end_switch0;;
				}			}
			if ((v == GUINode_AlignmentHorizontal::LEFT) || (v == GUINode_AlignmentHorizontal::CENTER)) {
{
					computedConstraints->contentAlignmentLeft = (computedConstraints->width - getContentWidth()) / 2 + border->left + padding->left;
					goto end_switch0;;
				}			}
			if ((v == GUINode_AlignmentHorizontal::LEFT) || (v == GUINode_AlignmentHorizontal::CENTER) || (v == GUINode_AlignmentHorizontal::RIGHT)) {
{
{
						computedConstraints->contentAlignmentLeft = computedConstraints->width - getContentWidth() + border->left + padding->left;
						goto end_switch0;;
					}
				}			}
end_switch0:;
		}

		{
			auto v = alignments->vertical;
			if ((v == GUINode_AlignmentVertical::TOP)) {
{
					computedConstraints->contentAlignmentTop = border->top + padding->top;
					goto end_switch1;;
				}			}
			if ((v == GUINode_AlignmentVertical::TOP) || (v == GUINode_AlignmentVertical::CENTER)) {
{
					computedConstraints->contentAlignmentTop = (computedConstraints->height - getContentHeight()) / 2 + border->top + padding->top;
					goto end_switch1;;
				}			}
			if ((v == GUINode_AlignmentVertical::TOP) || (v == GUINode_AlignmentVertical::CENTER) || (v == GUINode_AlignmentVertical::BOTTOM)) {
{
{
						computedConstraints->contentAlignmentTop = computedConstraints->height - getContentHeight() + border->left + padding->left;
						goto end_switch1;;
					}
				}			}
end_switch1:;
		}

	}
}

int32_t GUINode::layoutConstraintPixel(GUINode_RequestedConstraints_RequestedConstraintsType* type, int32_t autoValue, int32_t parentValue, int32_t value)
{
	if (type->equals(GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL)) {
		return value;
	} else if (type->equals(GUINode_RequestedConstraints_RequestedConstraintsType::PERCENT)) {
		return static_cast< int32_t >((parentValue / 100.0 * value));
	} else if (type->equals(GUINode_RequestedConstraints_RequestedConstraintsType::AUTO)) {
		return autoValue;
	}
	return -1;
}

GUINode_Alignments* GUINode::createAlignments(String* horizontal, String* vertical)
{
	clinit();
	auto alignments = new GUINode_Alignments();
	alignments->horizontal = GUINode_AlignmentHorizontal::valueOf(horizontal != nullptr && horizontal->length() > 0 ? horizontal->toUpperCase()->getCPPWString() : L"LEFT");
	alignments->vertical = GUINode_AlignmentVertical::valueOf(vertical != nullptr && vertical->length() > 0 ? vertical->toUpperCase()->getCPPWString() : L"TOP");
	return alignments;
}

GUINode_RequestedConstraints* GUINode::createRequestedConstraints(String* left, String* top, String* width, String* height)
{
	clinit();
	auto constraints = new GUINode_RequestedConstraints();
	constraints->leftType = getRequestedConstraintsType(left->trim(), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints->left = getRequestedConstraintsValue(left->trim(), 0);
	constraints->topType = getRequestedConstraintsType(top->trim(), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints->top = getRequestedConstraintsValue(top->trim(), 0);
	constraints->widthType = getRequestedConstraintsType(width->trim(), GUINode_RequestedConstraints_RequestedConstraintsType::AUTO);
	constraints->width = getRequestedConstraintsValue(width->trim(), -1);
	constraints->heightType = getRequestedConstraintsType(height->trim(), GUINode_RequestedConstraints_RequestedConstraintsType::AUTO);
	constraints->height = getRequestedConstraintsValue(height->trim(), -1);
	return constraints;
}

GUINode_RequestedConstraints_RequestedConstraintsType* GUINode::getRequestedConstraintsType(String* constraint, GUINode_RequestedConstraints_RequestedConstraintsType* defaultConstraintsType)
{
	clinit();
	if (constraint == nullptr || constraint->length() == 0) {
		return defaultConstraintsType;
	} else if (constraint->equals(u"auto"_j)) {
		return GUINode_RequestedConstraints_RequestedConstraintsType::AUTO;
	} else if (constraint->equals(u"*"_j)) {
		return GUINode_RequestedConstraints_RequestedConstraintsType::STAR;
	} else if (constraint->endsWith(u"%"_j)) {
		return GUINode_RequestedConstraints_RequestedConstraintsType::PERCENT;
	} else {
		return GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	}
}

int32_t GUINode::getRequestedConstraintsValue(String* constraint, int32_t defaultConstraintsValue)
{
	clinit();
	if (constraint == nullptr || constraint->length() == 0) {
		return defaultConstraintsValue;
	} else if (constraint->equals(u"auto"_j)) {
		return -1;
	} else if (constraint->equals(u"*"_j)) {
		return -1;
	} else if (constraint->endsWith(u"%"_j)) {
		return (Integer::valueOf(constraint->substring(0, constraint->length() - 1)))->intValue();
	} else {
		return (Integer::valueOf(constraint))->intValue();
	}
}

int32_t GUINode::getRequestedPixelValue(String* value, int32_t defaultValue)
{
	clinit();
	if (value == nullptr || value->length() == 0) {
		return defaultValue;
	} else {
		return (Integer::valueOf(value))->intValue();
	}
}

GUIColor* GUINode::getRequestedColor(String* color, GUIColor* defaultColor) /* throws(GUIParserException) */
{
	clinit();
	if (color == nullptr || color->length() == 0) {
		return defaultColor;
	} else {
		return new GUIColor(color);
	}
}

GUINode_Flow* GUINode::createFlow(String* flow)
{
	clinit();
	return GUINode_Flow::valueOf(flow != nullptr && flow->length() > 0 ? flow->toUpperCase()->getCPPWString() : L"INTEGRATED");
}

GUINode_Border* GUINode::createBorder(String* allBorder, String* left, String* top, String* right, String* bottom, String* allBorderColor, String* leftColor, String* topColor, String* rightColor, String* bottomColor) /* throws(GUIParserException) */
{
	clinit();
	auto border = new GUINode_Border();
	border->left = getRequestedPixelValue(allBorder, 0);
	border->top = getRequestedPixelValue(allBorder, 0);
	border->right = getRequestedPixelValue(allBorder, 0);
	border->bottom = getRequestedPixelValue(allBorder, 0);
	border->left = getRequestedPixelValue(left, border->left);
	border->top = getRequestedPixelValue(top, border->top);
	border->right = getRequestedPixelValue(right, border->right);
	border->bottom = getRequestedPixelValue(bottom, border->bottom);
	border->leftColor = getRequestedColor(allBorderColor, GUIColor::BLACK);
	border->topColor = getRequestedColor(allBorderColor, GUIColor::BLACK);
	border->rightColor = getRequestedColor(allBorderColor, GUIColor::BLACK);
	border->bottomColor = getRequestedColor(allBorderColor, GUIColor::BLACK);
	border->leftColor = getRequestedColor(leftColor, border->leftColor);
	border->topColor = getRequestedColor(topColor, border->topColor);
	border->rightColor = getRequestedColor(rightColor, border->rightColor);
	border->bottomColor = getRequestedColor(bottomColor, border->bottomColor);
	return border;
}

GUINode_Padding* GUINode::createPadding(String* allPadding, String* left, String* top, String* right, String* bottom) /* throws(GUIParserException) */
{
	clinit();
	auto padding = new GUINode_Padding();
	padding->left = getRequestedPixelValue(allPadding, 0);
	padding->top = getRequestedPixelValue(allPadding, 0);
	padding->right = getRequestedPixelValue(allPadding, 0);
	padding->bottom = getRequestedPixelValue(allPadding, 0);
	padding->left = getRequestedPixelValue(left, padding->left);
	padding->top = getRequestedPixelValue(top, padding->top);
	padding->right = getRequestedPixelValue(right, padding->right);
	padding->bottom = getRequestedPixelValue(bottom, padding->bottom);
	return padding;
}

GUINodeConditions* GUINode::createConditions(String* conditions)
{
	clinit();
	auto guiNodeConditions = new GUINodeConditions();
	auto t = new StringTokenizer(conditions, u","_j);
	while (t->hasMoreTokens()) {
		guiNodeConditions->add(t->nextToken()->trim());
	}
	return guiNodeConditions;
}

bool GUINode::checkConditions()
{
	auto showOn = this->showOn->conditions;
	auto hideOn = this->hideOn->conditions;

	for (auto i = 0; i < showOn.size(); i++) {
		if (java_cast< String* >(showOn.at(i))->equals(GUIElementNode::CONDITION_ALWAYS))
			return true;

	}
	for (auto i = 0; i < hideOn.size(); i++) {
		if (java_cast< String* >(hideOn.at(i))->equals(GUIElementNode::CONDITION_ALWAYS))
			return false;

	}
	GUINode* node = parentNode;
	while (node != nullptr && dynamic_cast< GUIElementNode* >(node) != nullptr == false) {
		node = node->parentNode;
	}
	if (node == nullptr) {
		return true;
	}
	auto elementNode = java_cast< GUIElementNode* >(node);
	for (auto i = 0; i < hideOn.size(); i++) {
		for (auto j = 0; j < elementNode->activeConditions->conditions.size(); j++) {
			if (java_cast< String* >(hideOn.at(i))->equals(java_cast< String* >(elementNode->activeConditions->conditions.at(j))))
				return false;

		}
	}
	for (auto i = 0; i < showOn.size(); i++) {
		for (auto j = 0; j < elementNode->activeConditions->conditions.size(); j++) {
			if (java_cast< String* >(showOn.at(i))->equals(java_cast< String* >(elementNode->activeConditions->conditions.at(j))))
				return true;

		}
	}
	return showOn.size() == 0;
}

void GUINode::dispose()
{
	if (controller != nullptr)
		controller->dispose();

}

void GUINode::setConditionsMet()
{
	conditionsMet = checkConditions();
}

void GUINode::render(GUIRenderer* guiRenderer, vector<GUINode*>* floatingNodes)
{
	if (conditionsMet == false)
		return;

	float screenWidth = guiRenderer->getGUI()->getWidth();
	float screenHeight = guiRenderer->getGUI()->getHeight();
	if (backgroundColor != GUIColor::TRANSPARENT) {
		float left = computedConstraints->left + computedConstraints->alignmentLeft + border->left;
		float top = computedConstraints->top + computedConstraints->alignmentTop + border->top;
		float width = computedConstraints->width - border->left - border->right;
		float height = computedConstraints->height - border->top - border->bottom;
		auto bgColorData = backgroundColor->getArray();
		guiRenderer->bindTexture(0);
		guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*bgColorData)[0], (*bgColorData)[1], (*bgColorData)[2], (*bgColorData)[3], 0.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*bgColorData)[0], (*bgColorData)[1], (*bgColorData)[2], (*bgColorData)[3], 1.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*bgColorData)[0], (*bgColorData)[1], (*bgColorData)[2], (*bgColorData)[3], 1.0f, 0.0f, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*bgColorData)[0], (*bgColorData)[1], (*bgColorData)[2], (*bgColorData)[3], 0.0f, 0.0f);
		guiRenderer->render();
	}
	if (border != nullptr) {
		guiRenderer->bindTexture(0);
		if (border->top > 0) {
			float left = computedConstraints->left + computedConstraints->alignmentLeft;
			float top = computedConstraints->top + computedConstraints->alignmentTop;
			float width = computedConstraints->width;
			float height = border->top;
			auto borderColorData = border->topColor->getArray();
			guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 0.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 1.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 1.0f, 0.0f, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 0.0f, 0.0f);
		}
		if (border->bottom > 0) {
			float left = computedConstraints->left + computedConstraints->alignmentLeft;
			float top = computedConstraints->top + computedConstraints->alignmentTop + computedConstraints->height - border->bottom;
			float width = computedConstraints->width;
			float height = border->bottom;
			auto borderColorData = border->bottomColor->getArray();
			guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 0.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 1.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 1.0f, 0.0f, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 0.0f, 0.0f);
		}
		if (border->left > 0) {
			float left = computedConstraints->left + computedConstraints->alignmentLeft;
			float top = computedConstraints->top + computedConstraints->alignmentTop;
			float width = border->left;
			float height = computedConstraints->height;
			auto borderColorData = border->leftColor->getArray();
			guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 0.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 1.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 1.0f, 0.0f, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 0.0f, 0.0f);
		}
		if (border->right > 0) {
			float left = computedConstraints->left + computedConstraints->alignmentLeft + computedConstraints->width - border->right;
			float top = computedConstraints->top + computedConstraints->alignmentTop;
			float width = border->right;
			float height = computedConstraints->height;
			auto borderColorData = border->rightColor->getArray();
			guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 0.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 1.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 1.0f, 0.0f, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, (*borderColorData)[0], (*borderColorData)[1], (*borderColorData)[2], (*borderColorData)[3], 0.0f, 0.0f);
		}
		guiRenderer->render();
	}
}

float GUINode::computeParentChildrenRenderOffsetXTotal()
{
	auto childrenRenderOffSetX = 0.0f;
	auto parentNode = this->parentNode;
	while (parentNode != nullptr) {
		childrenRenderOffSetX += parentNode->childrenRenderOffsetX;
		parentNode = parentNode->parentNode;
	}
	return childrenRenderOffSetX;
}

float GUINode::computeParentChildrenRenderOffsetYTotal()
{
	auto childrenRenderOffSetY = 0.0f;
	auto parentNode = this->parentNode;
	while (parentNode != nullptr) {
		childrenRenderOffSetY += parentNode->childrenRenderOffsetY;
		parentNode = parentNode->parentNode;
	}
	return childrenRenderOffSetY;
}

bool GUINode::isEventBelongingToNode(GUIMouseEvent* event, int32_tArray* position)
{
	auto eventXScreen = event->getX();
	auto eventYScreen = event->getY();
	auto parentNode = this->parentNode;
	while (parentNode != nullptr) {
		if (parentNode->flow == GUINode_Flow::FLOATING)
			break;

		auto eventX = eventXScreen + parentNode->computeParentChildrenRenderOffsetXTotal();
		auto eventY = eventYScreen + parentNode->computeParentChildrenRenderOffsetYTotal();
		if ((eventX >= parentNode->computedConstraints->left + parentNode->computedConstraints->alignmentLeft && eventX < parentNode->computedConstraints->left + parentNode->computedConstraints->alignmentLeft + parentNode->computedConstraints->width && eventY >= parentNode->computedConstraints->top + parentNode->computedConstraints->alignmentTop && eventY < parentNode->computedConstraints->top + parentNode->computedConstraints->alignmentTop + parentNode->computedConstraints->height) == false) {
			return false;
		}
		parentNode = parentNode->parentNode;
	}
	auto eventX = eventXScreen + computeParentChildrenRenderOffsetXTotal();
	auto eventY = eventYScreen + computeParentChildrenRenderOffsetYTotal();
	auto belongsToElement = eventX >= computedConstraints->left + computedConstraints->alignmentLeft && eventX < computedConstraints->left + computedConstraints->alignmentLeft + computedConstraints->width && eventY >= computedConstraints->top + computedConstraints->alignmentTop && eventY < computedConstraints->top + computedConstraints->alignmentTop + computedConstraints->height;
	if (belongsToElement == true && position != nullptr) {
		(*position)[0] = static_cast< int32_t >((eventX - (computedConstraints->left + computedConstraints->alignmentLeft)));
		(*position)[1] = static_cast< int32_t >((eventY - (computedConstraints->top + computedConstraints->alignmentTop)));
	}
	return belongsToElement;
}

bool GUINode::isEventBelongingToNode(GUIMouseEvent* event)
{
	return isEventBelongingToNode(event, nullptr);
}

void GUINode::getEventOffNodeRelativePosition(GUIMouseEvent* event, int32_tArray* position)
{
	auto eventXScreen = event->getX();
	auto eventYScreen = event->getY();
	auto eventX = eventXScreen + computeParentChildrenRenderOffsetXTotal();
	auto eventY = eventYScreen + computeParentChildrenRenderOffsetYTotal();
	float left = computedConstraints->left + computedConstraints->alignmentLeft;
	float right = computedConstraints->left + computedConstraints->alignmentLeft + computedConstraints->width;
	float top = computedConstraints->top + computedConstraints->alignmentTop;
	float bottom = computedConstraints->top + computedConstraints->alignmentTop + computedConstraints->height;
	if (eventX < left) {
		(*position)[0] = static_cast< int32_t >((eventX - left));
	} else if (eventX > right) {
		(*position)[0] = static_cast< int32_t >((eventX - right));
	} else {
		(*position)[0] = 0;
	}
	if (eventY < top) {
		(*position)[1] = static_cast< int32_t >((eventY - top));
	} else if (eventY > bottom) {
		(*position)[1] = static_cast< int32_t >((eventY - bottom));
	} else {
		(*position)[1] = 0;
	}
}

GUIParentNode* GUINode::getParentControllerNode()
{
	auto node = this->parentNode;
	while (node != nullptr && node->controller == nullptr) {
		node = node->parentNode;
	}
	return node;
}

void GUINode::handleMouseEvent(GUIMouseEvent* event)
{
	if (conditionsMet == false)
		return;

	if (screenNode->mouseEventProcessedByFloatingNode == true)
		return;

	auto node = this;
	if (node->controller == nullptr) {
		node = getParentControllerNode();
	}
	if (node == nullptr) {
		return;
	}
	node->controller->handleMouseEvent(this, event);
}

void GUINode::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	if (conditionsMet == false)
		return;

	auto node = this;
	if (node->controller == nullptr) {
		node = getParentControllerNode();
	}
	if (node == nullptr) {
		return;
	}
	node->controller->handleKeyboardEvent(this, event);
}

void GUINode::tick()
{
	if (conditionsMet == false)
		return;

	if (controller != nullptr)
		controller->tick();

}

GUINodeController* GUINode::getController()
{
	return controller;
}

void GUINode::setController(GUINodeController* controller)
{
	this->controller = controller;
}

void GUINode::scrollToNodeY()
{
	scrollToNodeY(nullptr);
}

void GUINode::scrollToNodeY(GUIParentNode* toNode)
{
	auto scrollYParentNode = this->parentNode;
	while (true == true) {
		if (scrollYParentNode == toNode || scrollYParentNode == nullptr)
			return;

		if (scrollYParentNode->overflowY == GUIParentNode_Overflow::SCROLL) {
			break;
		}
		scrollYParentNode = scrollYParentNode->parentNode;
		if (scrollYParentNode == nullptr)
			return;

	}
	if (computedConstraints->top < scrollYParentNode->childrenRenderOffsetY + scrollYParentNode->computedConstraints->top) {
		scrollYParentNode->childrenRenderOffsetY = computedConstraints->top - scrollYParentNode->computedConstraints->top;
	}
	if (computedConstraints->top + computedConstraints->height > scrollYParentNode->childrenRenderOffsetY + scrollYParentNode->computedConstraints->top + scrollYParentNode->computedConstraints->height) {
		scrollYParentNode->childrenRenderOffsetY = computedConstraints->top + computedConstraints->height - scrollYParentNode->computedConstraints->top - scrollYParentNode->computedConstraints->height;
	}
	scrollYParentNode->scrollToNodeY(toNode);
}

void GUINode::scrollToNodeX()
{
	scrollToNodeX(nullptr);
}

void GUINode::scrollToNodeX(GUIParentNode* toNode)
{
	auto scrollXParentNode = this->parentNode;
	while (true == true) {
		if (scrollXParentNode == toNode || scrollXParentNode == nullptr)
			return;

		if (scrollXParentNode->overflowX == GUIParentNode_Overflow::SCROLL) {
			break;
		}
		scrollXParentNode = scrollXParentNode->parentNode;
	}
	if (computedConstraints->left < scrollXParentNode->childrenRenderOffsetX + scrollXParentNode->computedConstraints->left) {
		scrollXParentNode->childrenRenderOffsetX = computedConstraints->left - scrollXParentNode->computedConstraints->left;
	}
	if (computedConstraints->left + computedConstraints->width > scrollXParentNode->childrenRenderOffsetX + scrollXParentNode->computedConstraints->left + scrollXParentNode->computedConstraints->width) {
		scrollXParentNode->childrenRenderOffsetX = computedConstraints->left + computedConstraints->width - scrollXParentNode->computedConstraints->left - scrollXParentNode->computedConstraints->width;
	}
	scrollXParentNode->scrollToNodeX(toNode);
}

String* GUINode::indent(int32_t indent)
{
	auto tmp = u""_j;
	for (auto i = 0; i < indent; i++) 
				tmp = ::java::lang::StringBuilder(tmp).append(u"\t"_j)->toString();

	return tmp;
}

String* GUINode::toString()
{
	return ::java::lang::StringBuilder().append(u"GUINode [id="_j)->append(id)
		->append(u", alignments="_j)
		->append(static_cast< Object* >(alignments))
		->append(u", requestedConstraints="_j)
		->append(static_cast< Object* >(requestedConstraints))
		->append(u", computedConstraints="_j)
		->append(static_cast< Object* >(computedConstraints))
		->append(u"]"_j)->toString();
}

String* GUINode::toString(int32_t indent)
{
	return ::java::lang::StringBuilder().append(this->indent(indent))->append(u"GUINode [type="_j)
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
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUINode::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUINode", 22);
    return c;
}

java::lang::Class* GUINode::getClass0()
{
	return class_();
}

