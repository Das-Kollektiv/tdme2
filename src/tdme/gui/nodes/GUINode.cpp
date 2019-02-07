#include <tdme/gui/nodes/GUINode.h>

#include <array>
#include <set>
#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
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
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode_Overflow.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Integer.h>
#include <tdme/utils/StringTokenizer.h>
#include <tdme/utils/StringUtils.h>

using std::array;
using std::set;
using std::string;
using std::to_string;

using tdme::gui::nodes::GUINode;

using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager;
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
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIRenderer;
using tdme::utils::Console;
using tdme::utils::Integer;
using tdme::utils::StringTokenizer;
using tdme::utils::StringUtils;

GUINode::GUINode(
	GUIScreenNode* screenNode,
	GUIParentNode* parentNode,
	const string& id,
	GUINode_Flow* flow,
	const GUINode_Alignments& alignments,
	const GUINode_RequestedConstraints& requestedConstraints,
	const GUIColor& backgroundColor,
	const string& backgroundImage,
	const GUINode_Scale9Grid& backgroundImageScale9Grid,
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn)
{
	this->screenNode = screenNode;
	this->parentNode = parentNode;
	this->id = id;
	this->flow = flow;
	this->alignments = alignments;
	this->requestedConstraints = requestedConstraints;
	this->computedConstraints.alignmentLeft = 0;
	this->computedConstraints.alignmentTop = 0;
	this->computedConstraints.contentAlignmentLeft = 0;
	this->computedConstraints.contentAlignmentTop = 0;
	this->backgroundColor = backgroundColor;
	this->backgroundTexture = nullptr;
	this->backgroundTextureId = 0;
	if (backgroundImage.length() > 0) {
		this->backgroundTexture = GUI::getImage(backgroundImage);
		this->backgroundTextureId = Engine::getInstance()->getTextureManager()->addTexture(backgroundTexture);
	}
	this->backgroundImageScale9Grid = backgroundImageScale9Grid;
	this->border = border;
	this->padding = padding;
	this->showOn = showOn;
	this->hideOn = hideOn;
	this->controller = nullptr;
	this->conditionsMet = false;
}

GUINode::~GUINode() {
	if (controller != nullptr) delete controller;
}

GUIScreenNode* GUINode::getScreenNode()
{
	return screenNode;
}

GUIParentNode* GUINode::getParentNode()
{
	return parentNode;
}

const string& GUINode::getId()
{
	return id;
}

int32_t GUINode::getAutoWidth()
{
	if (requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		return getContentWidth();
	} else {
		return computedConstraints.width;
	}
}

int32_t GUINode::getAutoHeight()
{
	if (requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::AUTO) {
		return getContentHeight();
	} else {
		return computedConstraints.height;
	}
}

GUINode_Border& GUINode::getBorder()
{
	return border;
}

GUINode_Padding& GUINode::getPadding()
{
	return padding;
}

GUINode_RequestedConstraints& GUINode::getRequestsConstraints()
{
	return requestedConstraints;
}

GUINode_ComputedConstraints& GUINode::getComputedConstraints()
{
	return computedConstraints;
}

void GUINode::setLeft(int32_t left)
{
	computedConstraints.left = left;
}

void GUINode::setTop(int32_t top)
{
	computedConstraints.top = top;
}

void GUINode::layout()
{
	auto parentNodeContentWidth = parentNode->computedConstraints.width - parentNode->border.left - parentNode->border.right - parentNode->padding.left - parentNode->padding.right;
	auto parentNodeContentHeight = parentNode->computedConstraints.height - parentNode->border.top - parentNode->border.bottom - parentNode->padding.top - parentNode->padding.bottom;
	computedConstraints.left = parentNode->computedConstraints.left + layoutConstraintPixel(requestedConstraints.leftType, 0, parentNodeContentWidth, requestedConstraints.left);
	computedConstraints.top = parentNode->computedConstraints.top + layoutConstraintPixel(requestedConstraints.topType, 0, parentNodeContentHeight, requestedConstraints.top);
	computedConstraints.width = layoutConstraintPixel(requestedConstraints.widthType, getAutoWidth(), parentNodeContentWidth, requestedConstraints.width);
	computedConstraints.height = layoutConstraintPixel(requestedConstraints.heightType, getAutoHeight(), parentNodeContentHeight, requestedConstraints.height);
	computeContentAlignment();
}

void GUINode::computeContentAlignment()
{
	if (isContentNode() == true) {
		{
			auto v = alignments.horizontal;
			if (v == GUINode_AlignmentHorizontal::LEFT) {
				computedConstraints.contentAlignmentLeft = border.left + padding.left;
			} else
			if (v == GUINode_AlignmentHorizontal::CENTER) {
				computedConstraints.contentAlignmentLeft = (computedConstraints.width - getContentWidth()) / 2 + border.left + padding.left;
			} else
			if (v == GUINode_AlignmentHorizontal::RIGHT) {
				computedConstraints.contentAlignmentLeft = computedConstraints.width - getContentWidth() + border.left + padding.left;
			}
		}

		{
			auto v = alignments.vertical;
			if (v == GUINode_AlignmentVertical::TOP) {
				computedConstraints.contentAlignmentTop = border.top + padding.top;
			} else
			if (v == GUINode_AlignmentVertical::CENTER) {
				computedConstraints.contentAlignmentTop = (computedConstraints.height - getContentHeight()) / 2 + border.top + padding.top;
			} else
			if (v == GUINode_AlignmentVertical::BOTTOM) {
				computedConstraints.contentAlignmentTop = computedConstraints.height - getContentHeight() + border.top + padding.top;
			}
		}

	}
}

int32_t GUINode::layoutConstraintPixel(GUINode_RequestedConstraints_RequestedConstraintsType* type, int32_t autoValue, int32_t parentValue, int32_t value)
{
	if (type->equals(GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL)) {
		return value;
	} else
	if (type->equals(GUINode_RequestedConstraints_RequestedConstraintsType::PERCENT)) {
		return static_cast< int32_t >((parentValue / 100.0 * value));
	} else
	if (type->equals(GUINode_RequestedConstraints_RequestedConstraintsType::AUTO)) {
		return autoValue;
	}
	return -1;
}

GUINode_Alignments GUINode::createAlignments(const string& horizontal, const string& vertical)
{
	GUINode_Alignments alignments;
	alignments.horizontal = GUINode_AlignmentHorizontal::valueOf(horizontal.empty() == false && horizontal.length() > 0 ? StringUtils::toUpperCase(horizontal) : "LEFT");
	alignments.vertical = GUINode_AlignmentVertical::valueOf(vertical.empty() == false && vertical.length() > 0 ? StringUtils::toUpperCase(vertical) : "TOP");
	return alignments;
}

GUINode_RequestedConstraints GUINode::createRequestedConstraints(const string& left, const string& top, const string& width, const string& height)
{
	GUINode_RequestedConstraints constraints;
	constraints.leftType = getRequestedConstraintsType(StringUtils::trim(left), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints.left = getRequestedConstraintsValue(StringUtils::trim(left), 0);
	constraints.topType = getRequestedConstraintsType(StringUtils::trim(top), GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL);
	constraints.top = getRequestedConstraintsValue(StringUtils::trim(top), 0);
	constraints.widthType = getRequestedConstraintsType(StringUtils::trim(width), GUINode_RequestedConstraints_RequestedConstraintsType::AUTO);
	constraints.width = getRequestedConstraintsValue(StringUtils::trim(width), -1);
	constraints.heightType = getRequestedConstraintsType(StringUtils::trim(height), GUINode_RequestedConstraints_RequestedConstraintsType::AUTO);
	constraints.height = getRequestedConstraintsValue(StringUtils::trim(height), -1);
	return constraints;
}

GUINode_RequestedConstraints_RequestedConstraintsType* GUINode::getRequestedConstraintsType(const string& constraint, GUINode_RequestedConstraints_RequestedConstraintsType* defaultConstraintsType)
{
	if (constraint.empty() == true || constraint.length() == 0) {
		return defaultConstraintsType;
	} else
	if (constraint.compare("auto") == 0) {
		return GUINode_RequestedConstraints_RequestedConstraintsType::AUTO;
	} else
	if (constraint.compare("*") == 0) {
		return GUINode_RequestedConstraints_RequestedConstraintsType::STAR;
	} else
	if (StringUtils::endsWith(constraint, "%")) {
		return GUINode_RequestedConstraints_RequestedConstraintsType::PERCENT;
	} else {
		return GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	}
}

int32_t GUINode::getRequestedConstraintsValue(const string& constraint, int32_t defaultConstraintsValue)
{
	if (constraint.empty() == true || constraint.length() == 0) {
		return defaultConstraintsValue;
	} else
	if (constraint.compare("auto") == 0) {
		return -1;
	} else
	if (constraint.compare("*") == 0) {
		return -1;
	} else
	if (StringUtils::endsWith(constraint, "%")) {
		return (Integer::parseInt(constraint.substr(0, constraint.length() - 1)));
	} else {
		return (Integer::parseInt(constraint));
	}
}

int32_t GUINode::getRequestedPixelValue(const string& value, int32_t defaultValue)
{
	if (value.empty() == true || value.length() == 0) {
		return defaultValue;
	} else {
		return (Integer::parseInt(value));
	}
}

GUIColor GUINode::getRequestedColor(const string& color, const GUIColor& defaultColor) throw(GUIParserException)
{
	if (color.empty() == true || color.length() == 0) {
		return defaultColor;
	} else {
		return GUIColor(color);
	}
}

GUINode_Flow* GUINode::createFlow(const string& flow)
{
	return GUINode_Flow::valueOf(flow.empty() == false && flow.length() > 0 ? StringUtils::toUpperCase(flow) : "INTEGRATED");
}

GUINode_Border GUINode::createBorder(const string& allBorder, const string& left, const string& top, const string& right, const string& bottom, const string& allBorderColor, const string& leftColor, const string& topColor, const string& rightColor, const string& bottomColor) throw(GUIParserException)
{
	GUINode_Border border;
	border.left = getRequestedPixelValue(allBorder, 0);
	border.top = getRequestedPixelValue(allBorder, 0);
	border.right = getRequestedPixelValue(allBorder, 0);
	border.bottom = getRequestedPixelValue(allBorder, 0);
	border.left = getRequestedPixelValue(left, border.left);
	border.top = getRequestedPixelValue(top, border.top);
	border.right = getRequestedPixelValue(right, border.right);
	border.bottom = getRequestedPixelValue(bottom, border.bottom);
	border.leftColor = getRequestedColor(allBorderColor, GUIColor::GUICOLOR_BLACK);
	border.topColor = getRequestedColor(allBorderColor, GUIColor::GUICOLOR_BLACK);
	border.rightColor = getRequestedColor(allBorderColor, GUIColor::GUICOLOR_BLACK);
	border.bottomColor = getRequestedColor(allBorderColor, GUIColor::GUICOLOR_BLACK);
	border.leftColor = getRequestedColor(leftColor, border.leftColor);
	border.topColor = getRequestedColor(topColor, border.topColor);
	border.rightColor = getRequestedColor(rightColor, border.rightColor);
	border.bottomColor = getRequestedColor(bottomColor, border.bottomColor);
	return border;
}

GUINode_Padding GUINode::createPadding(const string& allPadding, const string& left, const string& top, const string& right, const string& bottom) throw(GUIParserException)
{
	GUINode_Padding padding;
	padding.left = getRequestedPixelValue(allPadding, 0);
	padding.top = getRequestedPixelValue(allPadding, 0);
	padding.right = getRequestedPixelValue(allPadding, 0);
	padding.bottom = getRequestedPixelValue(allPadding, 0);
	padding.left = getRequestedPixelValue(left, padding.left);
	padding.top = getRequestedPixelValue(top, padding.top);
	padding.right = getRequestedPixelValue(right, padding.right);
	padding.bottom = getRequestedPixelValue(bottom, padding.bottom);
	return padding;
}

GUINode_Scale9Grid GUINode::createScale9Grid(const string& all, const string& left, const string& top, const string& right, const string& bottom) throw(GUIParserException)
{
	GUINode_Scale9Grid scale9Grid;
	scale9Grid.left = getRequestedPixelValue(all, 0);
	scale9Grid.top = getRequestedPixelValue(all, 0);
	scale9Grid.right = getRequestedPixelValue(all, 0);
	scale9Grid.bottom = getRequestedPixelValue(all, 0);
	scale9Grid.left = getRequestedPixelValue(left, scale9Grid.left);
	scale9Grid.top = getRequestedPixelValue(top, scale9Grid.top);
	scale9Grid.right = getRequestedPixelValue(right, scale9Grid.right);
	scale9Grid.bottom = getRequestedPixelValue(bottom, scale9Grid.bottom);
	return scale9Grid;
}

GUINodeConditions GUINode::createConditions(const string& conditions)
{
	GUINodeConditions guiNodeConditions;
	StringTokenizer strTokenizer;
	strTokenizer.tokenize(conditions, ",");
	while (strTokenizer.hasMoreTokens()) {
		guiNodeConditions.add(StringUtils::trim(strTokenizer.nextToken()));
	}
	return guiNodeConditions;
}

bool GUINode::checkConditions(GUIElementNode* elementNode)
{
	auto& showOn = this->showOn.conditions;
	auto& hideOn = this->hideOn.conditions;

	for (auto i = 0; i < showOn.size(); i++) {
		if (showOn[i] == GUIElementNode::CONDITION_ALWAYS)
			return true;

	}
	for (auto i = 0; i < hideOn.size(); i++) {
		if (hideOn[i] == GUIElementNode::CONDITION_ALWAYS)
			return false;

	}

	if (elementNode == nullptr) {
		for (GUINode* node = parentNode; node != nullptr && (elementNode = dynamic_cast< GUIElementNode* >(node)) == nullptr; node = node->parentNode);
		if (elementNode == nullptr) return true;
	}

	for (auto i = 0; i < hideOn.size(); i++) {
		for (auto j = 0; j < elementNode->activeConditions.conditions.size(); j++) {
			if (hideOn[i] == elementNode->activeConditions.conditions[j])
				return false;

		}
	}
	for (auto i = 0; i < showOn.size(); i++) {
		for (auto j = 0; j < elementNode->activeConditions.conditions.size(); j++) {
			if (showOn[i] == elementNode->activeConditions.conditions[j])
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

void GUINode::render(GUIRenderer* guiRenderer, vector<GUINode*>& floatingNodes)
{
	if (conditionsMet == false)
		return;

	auto screenWidth = screenNode->getScreenWidth();
	auto screenHeight = screenNode->getScreenHeight();
	float left = computedConstraints.left + computedConstraints.alignmentLeft + border.left;
	float top = computedConstraints.top + computedConstraints.alignmentTop + border.top;
	float width = computedConstraints.width - border.left - border.right;
	float height = computedConstraints.height - border.top - border.bottom;
	if (!backgroundColor.equals(GUIColor::GUICOLOR_TRANSPARENT)) {
		auto bgColorData = &backgroundColor.getArray();
		guiRenderer->addQuad(
			((left) / (screenWidth / 2.0f)) - 1.0f,
			((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
			(*bgColorData)[0],
			(*bgColorData)[1],
			(*bgColorData)[2],
			(*bgColorData)[3],
			0.0f,
			1.0f,
			((left + width) / (screenWidth / 2.0f)) - 1.0f,
			((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
			(*bgColorData)[0],
			(*bgColorData)[1],
			(*bgColorData)[2],
			(*bgColorData)[3],
			1.0f,
			1.0f,
			((left + width) / (screenWidth / 2.0f)) - 1.0f,
			((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
			(*bgColorData)[0],
			(*bgColorData)[1],
			(*bgColorData)[2],
			(*bgColorData)[3],
			1.0f,
			0.0f,
			((left) / (screenWidth / 2.0f)) - 1.0f,
			((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
			(*bgColorData)[0],
			(*bgColorData)[1],
			(*bgColorData)[2],
			(*bgColorData)[3],
			0.0f,
			0.0f
		);
		guiRenderer->render();
	}
	if (backgroundTexture != nullptr) {
		guiRenderer->bindTexture(backgroundTextureId);
		GUINode_Scale9Grid& scale9Grid = backgroundImageScale9Grid;
		if (scale9Grid.left == 0 &&
			scale9Grid.right == 0 &&
			scale9Grid.top == 0 &&
			scale9Grid.bottom == 0) {
			float left = computedConstraints.left + computedConstraints.alignmentLeft + border.left;
			float top = computedConstraints.top + computedConstraints.alignmentTop + border.top;
			float width = computedConstraints.width - border.left - border.right;
			float height = computedConstraints.height - border.top - border.bottom;
			guiRenderer->addQuad(
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0.0f,
				0.0f,
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f,
				0.0f,
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f,
				1.0f,
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0.0f,
				1.0f
			);
		} else {
			auto scaleX = 1.0f;
			auto scaleY = 1.0f;
			// we have a scale here, because we have a axis without "scale9grid"
			if (scale9Grid.top == 0 && scale9Grid.bottom == 0) {
				scaleY = (float)getContentHeight() / (float)backgroundTexture->getHeight();
				scaleX = scaleY;
			} else
			// we have a scale here, because we have a axis without "scale9grid"
			if (scale9Grid.left == 0 && scale9Grid.right == 0) {
				scaleX = (float)getContentWidth() / (float)backgroundTexture->getWidth();
				scaleY = scaleX;
			} else {
				// scale Y if content height is too small to fit scale 9 top and bottom
				if (getContentHeight() < scale9Grid.top + scale9Grid.bottom) {
					scaleY = getContentHeight() < Math::EPSILON?0.0f:(float)getContentHeight() / (float)(scale9Grid.top + scale9Grid.bottom);
				}
				// scale X if content width is too small to fit scale 9 left and top
				if (getContentWidth() < scale9Grid.left + scale9Grid.right) {
					scaleX = getContentWidth() < Math::EPSILON?0.0f:(float)getContentWidth() / (float)(scale9Grid.left + scale9Grid.right);
				}
			}
			// we have no certain scale, take original image size
			GUINode_Scale9Grid scaledScale9Grid;
			scaledScale9Grid.left = static_cast<int>(scale9Grid.left * scaleX);
			scaledScale9Grid.right = static_cast<int>(scale9Grid.right * scaleX);
			scaledScale9Grid.top = static_cast<int>(scale9Grid.top * scaleY);
			scaledScale9Grid.bottom = static_cast<int>(scale9Grid.bottom * scaleY);
			float imageScreenLeft = computedConstraints.left + computedConstraints.alignmentLeft + border.left;;
			float imageScreenTop = computedConstraints.top + computedConstraints.alignmentTop + border.top;;
			float imageScreenScale9Left = imageScreenLeft + scaledScale9Grid.left;
			float imageScreenScale9Top = imageScreenTop + scaledScale9Grid.top;
			float imageScreenWidth = computedConstraints.width - border.left - border.right;
			float imageScreenHeight = computedConstraints.height - border.top - border.bottom;
			float imageScreenScale9Right = imageScreenLeft + imageScreenWidth - scaledScale9Grid.right;
			float imageScreenScale9Bottom = imageScreenTop + imageScreenHeight - scaledScale9Grid.bottom;
			float imageTextureWidth = backgroundTexture->getWidth();
			float imageTextureHeight = backgroundTexture->getHeight();
			// left top
			if (scaledScale9Grid.left > 0 && scaledScale9Grid.top > 0) {
				float left = imageScreenLeft;
				float top = imageScreenTop;
				float width = scaledScale9Grid.left;
				float height = scaledScale9Grid.top;
				guiRenderer->addQuad(
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0.0f,
					0.0f,
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * scale9Grid.left,
					0.0f,
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * scale9Grid.left,
					1.0f / imageTextureHeight * scale9Grid.top,
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0.0f,
					1.0f / imageTextureHeight * scale9Grid.top
				);
			}
			// middle top
			if (scaledScale9Grid.top > 0) {
				float left = imageScreenScale9Left;
				float top = imageScreenTop;
				float width = imageScreenWidth - scaledScale9Grid.left - scaledScale9Grid.right;
				float height = scaledScale9Grid.top;
				guiRenderer->addQuad(
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * scale9Grid.left,
					0.0f,
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
					0.0f,
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
					1.0f / imageTextureHeight * scale9Grid.top,
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * scale9Grid.left,
					1.0f / imageTextureHeight * scale9Grid.top
				);
			}
			// right top
			if (scaledScale9Grid.right > 0 && scaledScale9Grid.top > 0) {
				float left = imageScreenScale9Right;
				float top = imageScreenTop;
				float width = scaledScale9Grid.right;
				float height = scaledScale9Grid.top;
				guiRenderer->addQuad(
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
					0.0f,
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f,
					0.0f,
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f,
					1.0f / imageTextureHeight * scale9Grid.top,
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
					1.0f / imageTextureHeight * scale9Grid.top
				);
			}
			// right bottom
			if (scaledScale9Grid.right > 0 && scaledScale9Grid.bottom > 0) {
				float left = imageScreenScale9Right;
				float top = imageScreenScale9Bottom;
				float width = scaledScale9Grid.right;
				float height = scaledScale9Grid.bottom;
				guiRenderer->addQuad(
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
					1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f,
					1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f,
					1.0f,
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
					1.0f
				);
			}
			// middle bottom
			if (scaledScale9Grid.bottom > 0) {
				float left = imageScreenScale9Left;
				float top = imageScreenScale9Bottom;
				float width = imageScreenWidth - scaledScale9Grid.left - scaledScale9Grid.right;
				float height = scaledScale9Grid.bottom;
				guiRenderer->addQuad(
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * scale9Grid.left,
					1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
					1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
					1.0f,
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * scale9Grid.left,
					1.0f
				);
			}
			// left bottom
			if (scaledScale9Grid.left > 0 && scaledScale9Grid.bottom > 0) {
				float left = imageScreenLeft;
				float top = imageScreenScale9Bottom;
				float width = scaledScale9Grid.left;
				float height = scaledScale9Grid.bottom;
				guiRenderer->addQuad(
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0.0f,
					1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * scale9Grid.left,
					1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * scale9Grid.left,
					1.0f,
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0.0f,
					1.0f
				);
			}
			// left middle
			if (scaledScale9Grid.left > 0) {
				float left = imageScreenLeft;
				float top = imageScreenScale9Top;
				float width = scaledScale9Grid.left;
				float height = imageScreenHeight - scaledScale9Grid.top - scaledScale9Grid.bottom;
				guiRenderer->addQuad(
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0.0f,
					1.0f / imageTextureHeight * scale9Grid.top,
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * scale9Grid.left,
					1.0f / imageTextureHeight * scale9Grid.top,
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * scale9Grid.left,
					1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0.0f,
					1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom)
				);
			}
			// right middle
			if (scaledScale9Grid.right > 0) {
				float left = imageScreenScale9Right;
				float top = imageScreenScale9Top;
				float width = scaledScale9Grid.right;
				float height = imageScreenHeight - scaledScale9Grid.top - scaledScale9Grid.bottom;
				guiRenderer->addQuad(
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
					1.0f / imageTextureHeight * scale9Grid.top,
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f,
					1.0f / imageTextureHeight * scale9Grid.top,
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f,
					1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
					1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom)
				);
			}
			// center
			{
				float left = imageScreenScale9Left;
				float top = imageScreenScale9Top;
				float width = imageScreenWidth - scaledScale9Grid.left - scaledScale9Grid.right;
				float height = imageScreenHeight - scaledScale9Grid.top - scaledScale9Grid.bottom;
				guiRenderer->addQuad(
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * scale9Grid.left,
					1.0f / imageTextureHeight * scale9Grid.top,
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
					1.0f / imageTextureHeight * scale9Grid.top,
					((left + width) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * (imageTextureWidth - scale9Grid.right),
					1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom),
					((left) / (screenWidth / 2.0f)) - 1.0f,
					((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f / imageTextureWidth * scale9Grid.left,
					1.0f / imageTextureHeight * (imageTextureHeight - scale9Grid.bottom)
				);
			}
		}
		guiRenderer->render();
		guiRenderer->bindTexture(0);
	}
	if (border.top > 0 || border.left > 0 || border.right > 0 || border.bottom > 0) {
		if (border.top > 0) {
			float left = computedConstraints.left + computedConstraints.alignmentLeft;
			float top = computedConstraints.top + computedConstraints.alignmentTop;
			float width = computedConstraints.width;
			float height = border.top;
			auto& borderColorData = border.topColor.getArray();
			guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 0.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 1.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 1.0f, 0.0f, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 0.0f, 0.0f);
		}
		if (border.bottom > 0) {
			float left = computedConstraints.left + computedConstraints.alignmentLeft;
			float top = computedConstraints.top + computedConstraints.alignmentTop + computedConstraints.height - border.bottom;
			float width = computedConstraints.width;
			float height = border.bottom;
			auto& borderColorData = border.bottomColor.getArray();
			guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 0.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 1.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 1.0f, 0.0f, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 0.0f, 0.0f);
		}
		if (border.left > 0) {
			float left = computedConstraints.left + computedConstraints.alignmentLeft;
			float top = computedConstraints.top + computedConstraints.alignmentTop;
			float width = border.left;
			float height = computedConstraints.height;
			auto& borderColorData = border.leftColor.getArray();
			guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 0.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 1.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 1.0f, 0.0f, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 0.0f, 0.0f);
		}
		if (border.right > 0) {
			float left = computedConstraints.left + computedConstraints.alignmentLeft + computedConstraints.width - border.right;
			float top = computedConstraints.top + computedConstraints.alignmentTop;
			float width = border.right;
			float height = computedConstraints.height;
			auto& borderColorData = border.rightColor.getArray();
			guiRenderer->addQuad(((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 0.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 1.0f, 1.0f, ((left + width) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 1.0f, 0.0f, ((left) / (screenWidth / 2.0f)) - 1.0f, ((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f, borderColorData[0], borderColorData[1], borderColorData[2], borderColorData[3], 0.0f, 0.0f);
		}
		guiRenderer->render();
	}
}

float GUINode::computeParentChildrenRenderOffsetXTotal()
{
	auto childrenRenderOffSetX = 0.0f;
	auto parentNode = this->parentNode;
	while (parentNode != nullptr) {
		childrenRenderOffSetX += parentNode->getChildrenRenderOffsetX();
		parentNode = parentNode->parentNode;
	}
	return childrenRenderOffSetX;
}

float GUINode::computeParentChildrenRenderOffsetYTotal()
{
	auto childrenRenderOffSetY = 0.0f;
	auto parentNode = this->parentNode;
	while (parentNode != nullptr) {
		childrenRenderOffSetY += parentNode->getChildrenRenderOffsetY();
		parentNode = parentNode->parentNode;
	}
	return childrenRenderOffSetY;
}

bool GUINode::isEventBelongingToNode(GUIMouseEvent* event, array<float,2>& position)
{
	auto eventXScreen = event->getX();
	auto eventYScreen = event->getY();
	auto parentNode = this->parentNode;
	while (parentNode != nullptr) {
		if (parentNode->flow == GUINode_Flow::FLOATING)
			break;

		auto eventX = eventXScreen + parentNode->computeParentChildrenRenderOffsetXTotal();
		auto eventY = eventYScreen + parentNode->computeParentChildrenRenderOffsetYTotal();
		if ((eventX >= parentNode->computedConstraints.left + parentNode->computedConstraints.alignmentLeft && eventX < parentNode->computedConstraints.left + parentNode->computedConstraints.alignmentLeft + parentNode->computedConstraints.width && eventY >= parentNode->computedConstraints.top + parentNode->computedConstraints.alignmentTop && eventY < parentNode->computedConstraints.top + parentNode->computedConstraints.alignmentTop + parentNode->computedConstraints.height) == false) {
			return false;
		}
		parentNode = parentNode->parentNode;
	}
	auto eventX = eventXScreen + computeParentChildrenRenderOffsetXTotal();
	auto eventY = eventYScreen + computeParentChildrenRenderOffsetYTotal();
	auto belongsToElement =
		eventX >= computedConstraints.left + computedConstraints.alignmentLeft &&
		eventX < computedConstraints.left + computedConstraints.alignmentLeft + computedConstraints.width &&
		eventY >= computedConstraints.top + computedConstraints.alignmentTop &&
		eventY < computedConstraints.top + computedConstraints.alignmentTop + computedConstraints.height;
	if (belongsToElement == true) {
		position[0] = static_cast< int32_t >((eventX - (computedConstraints.left + computedConstraints.alignmentLeft)));
		position[1] = static_cast< int32_t >((eventY - (computedConstraints.top + computedConstraints.alignmentTop)));
	}
	return belongsToElement;
}

bool GUINode::isEventBelongingToNode(GUIMouseEvent* event)
{
	array<float, 2> position;
	return isEventBelongingToNode(event, position);
}

void GUINode::getEventOffNodeRelativePosition(GUIMouseEvent* event, array<float, 2>& position)
{
	auto eventXScreen = event->getX();
	auto eventYScreen = event->getY();
	auto eventX = eventXScreen + computeParentChildrenRenderOffsetXTotal();
	auto eventY = eventYScreen + computeParentChildrenRenderOffsetYTotal();
	float left = computedConstraints.left + computedConstraints.alignmentLeft;
	float right = computedConstraints.left + computedConstraints.alignmentLeft + computedConstraints.width - 1;
	float top = computedConstraints.top + computedConstraints.alignmentTop;
	float bottom = computedConstraints.top + computedConstraints.alignmentTop + computedConstraints.height - 1;
	if (eventX < left) {
		position[0] = static_cast< int32_t >((eventX - left));
	} else if (eventX > right) {
		position[0] = static_cast< int32_t >((eventX - right));
	} else {
		position[0] = 0;
	}
	if (eventY < top) {
		position[1] = static_cast< int32_t >((eventY - top));
	} else if (eventY > bottom) {
		position[1] = static_cast< int32_t >((eventY - bottom));
	} else {
		position[1] = 0;
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

void GUINode::determineMouseEventNodes(GUIMouseEvent* event, set<string>& eventNodeIds)
{
	if (conditionsMet == false)
		return;

	if (isEventBelongingToNode(event) == true) {
		eventNodeIds.insert(this->id);
	}
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

GUINodeController* GUINode::getController()
{
	return controller;
}

void GUINode::setController(GUINodeController* controller)
{
	if (this->controller != nullptr) {
		screenNode->removeTickNode(this);
		this->controller->dispose();
		delete this->controller;
	}
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
	if (computedConstraints.top < scrollYParentNode->getChildrenRenderOffsetY() + scrollYParentNode->computedConstraints.top) {
		scrollYParentNode->setChildrenRenderOffsetY(computedConstraints.top - scrollYParentNode->computedConstraints.top);
	}
	if (computedConstraints.top + computedConstraints.height > scrollYParentNode->getChildrenRenderOffsetY() + scrollYParentNode->computedConstraints.top + scrollYParentNode->computedConstraints.height) {
		scrollYParentNode->setChildrenRenderOffsetY(computedConstraints.top + computedConstraints.height - scrollYParentNode->computedConstraints.top - scrollYParentNode->computedConstraints.height);
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
	if (computedConstraints.left < scrollXParentNode->getChildrenRenderOffsetX() + scrollXParentNode->computedConstraints.left) {
		scrollXParentNode->setChildrenRenderOffsetX(computedConstraints.left - scrollXParentNode->computedConstraints.left);
	}
	if (computedConstraints.left + computedConstraints.width > scrollXParentNode->getChildrenRenderOffsetX() + scrollXParentNode->computedConstraints.left + scrollXParentNode->computedConstraints.width) {
		scrollXParentNode->setChildrenRenderOffsetX(computedConstraints.left + computedConstraints.width - scrollXParentNode->computedConstraints.left - scrollXParentNode->computedConstraints.width);
	}
	scrollXParentNode->scrollToNodeX(toNode);
}

void GUINode::dumpNode(GUINode* node, int indent) {
	for (auto i = 0; i < indent; i++) Console::print("  ");
	Console::println(
		node->id + ": " +
		to_string(node->computedConstraints.left) + ", " +
		to_string(node->computedConstraints.top) + ", " +
		to_string(node->computedConstraints.width) + ", " +
		to_string(node->computedConstraints.height) + ", " +
		to_string(node->computedConstraints.alignmentLeft) + ", " +
		to_string(node->computedConstraints.alignmentTop) + ", " +
		to_string(node->computedConstraints.contentAlignmentLeft) + ", " +
		to_string(node->computedConstraints.contentAlignmentTop) + ": " +
		to_string(node->conditionsMet)
	);
	if (dynamic_cast< GUIParentNode* >(node) != nullptr) {
		auto parentNode = dynamic_cast< GUIParentNode* >(node);
		for (auto subNode: parentNode->subNodes) {
			dumpNode(subNode, indent + 1);
		}
	}
}


