#include <tdme/gui/nodes/GUIParentNode.h>

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINode_Alignments.h>
#include <tdme/gui/nodes/GUINode_AlignmentHorizontal.h>
#include <tdme/gui/nodes/GUINode_AlignmentVertical.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUINode_Flow.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUINode_Scale9Grid.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode_Overflow.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/GUIParserException.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/StringTools.h>

using std::remove;
using std::string;
using std::to_string;
using std::unordered_set;
using std::vector;

using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUINode_Scale9Grid;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIParentNode_Overflow;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::gui::GUIParserException;
using tdme::math::Math;
using tdme::utilities::StringTools;

GUIParentNode::GUIParentNode(
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
	const GUINode_Scale9Grid& backgroundImageScale9Grid,
	const GUIColor& backgroundImageEffectColorMul,
	const GUIColor& backgroundImageEffectColorAdd,
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn,
	const string& tooltip
	):
	GUINode(screenNode, parentNode, id, flow, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScale9Grid, backgroundImageEffectColorMul, backgroundImageEffectColorAdd, border, padding, showOn, hideOn, tooltip)
{
	this->overflowX = overflowX;
	this->overflowY = overflowY;
	this->childrenRenderOffsetX = 0.0f;
	this->childrenRenderOffsetY = 0.0f;
	this->computeViewportCache = true;
}

GUINode* GUIParentNode::detachSubNode(int index) {
	if (index < 0 || index >= subNodes.size()) return nullptr;
	//
	auto detachedSubNode = subNodes[index];
	subNodes.erase(subNodes.begin() + index);

	//
	auto parentControllerNode = controller != nullptr?this:getParentControllerNode();

	{
		auto _parentControllerNode = parentControllerNode;
		while (_parentControllerNode != nullptr) {
			_parentControllerNode->getController()->onSubTreeChange();
			_parentControllerNode = _parentControllerNode->getParentControllerNode();
		}
	}

	screenNode->invalidateLayout(this);

	setConditionsMet();
	floatingNodesCache.clear();
	invalidateRenderCaches();

	{
		auto _parentControllerNode = parentControllerNode;
		while (_parentControllerNode != nullptr) {
			_parentControllerNode->getController()->onSubTreeChange();
			_parentControllerNode = _parentControllerNode->getParentControllerNode();
		}
	}

	//
	return detachedSubNode;
}

vector<GUINode*> GUIParentNode::detachSubNodes()
{
	//
	auto detachedSubNodes = subNodes;
	for (auto subNode: detachedSubNodes) {
		subNode->parentNode = nullptr;
	}

	//
	auto parentControllerNode = controller != nullptr?this:getParentControllerNode();

	childrenRenderOffsetX = 0.0f;
	childrenRenderOffsetY = 0.0f;
	subNodes.clear();

	{
		auto _parentControllerNode = parentControllerNode;
		while (_parentControllerNode != nullptr) {
			_parentControllerNode->getController()->onSubTreeChange();
			_parentControllerNode = _parentControllerNode->getParentControllerNode();
		}
	}

	screenNode->invalidateLayout(this);

	setConditionsMet();
	floatingNodesCache.clear();
	invalidateRenderCaches();

	{
		auto _parentControllerNode = parentControllerNode;
		while (_parentControllerNode != nullptr) {
			_parentControllerNode->getController()->onSubTreeChange();
			_parentControllerNode = _parentControllerNode->getParentControllerNode();
		}
	}

	//
	return detachedSubNodes;
}

void GUIParentNode::clearSubNodes()
{
	//
	auto detachedSubNodes = detachSubNodes();

	//
	for (auto i = 0; i < detachedSubNodes.size(); i++) {
		auto subNode = detachedSubNodes[i];
		screenNode->removeNode(subNode);
	}
}

void GUIParentNode::replaceSubNodes(const string& xml, bool resetScrollOffsets)
{
	auto parentControllerNode = controller != nullptr?this:getParentControllerNode();

	for (auto i = 0; i < subNodes.size(); i++) {
		auto subNode = subNodes[i];
		screenNode->removeNode(subNode);
	}
	subNodes.clear();

	{
		auto _parentControllerNode = parentControllerNode;
		while (_parentControllerNode != nullptr) {
			_parentControllerNode->getController()->onSubTreeChange();
			_parentControllerNode = _parentControllerNode->getParentControllerNode();
		}
	}

	screenNode->invalidateLayout(this);
	GUIParser::parse(this, xml);

	floatingNodesCache.clear();
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		if (guiSubNode->flow == GUINode_Flow::FLOATING) {
			floatingNodesCache.push_back(guiSubNode);
		}
	}

	invalidateRenderCaches();
	setConditionsMet();

	if (layouted == false || resetScrollOffsets == true) {
		if (overflowX == GUIParentNode_Overflow::SCROLL) childrenRenderOffsetX = 0.0f;
		if (overflowY == GUIParentNode_Overflow::SCROLL) childrenRenderOffsetY = 0.0f;
	} else {
		if (overflowX == GUIParentNode_Overflow::SCROLL) {
			float elementWidth = computedConstraints.width;
			float contentWidth = getContentWidth();
			auto scrollableWidth = contentWidth - elementWidth;
			if (scrollableWidth < 0.0f) scrollableWidth = 0.0;
			if (childrenRenderOffsetX < 0.0f) childrenRenderOffsetX = 0.0f;
			if (scrollableWidth > 0 && childrenRenderOffsetX > scrollableWidth) childrenRenderOffsetX = scrollableWidth;
		}

		if (overflowY == GUIParentNode_Overflow::SCROLL) {
			float elementHeight = computedConstraints.height;
			float contentHeight = getContentHeight();
			auto scrollableHeight = contentHeight - elementHeight;
			if (scrollableHeight < 0.0f) scrollableHeight = 0.0f;
			if (childrenRenderOffsetY < 0.0f) childrenRenderOffsetY = 0.0f;
			if (scrollableHeight > 0 && childrenRenderOffsetY > scrollableHeight) childrenRenderOffsetY = scrollableHeight;
		}
	}

	{
		auto _parentControllerNode = parentControllerNode;
		while (_parentControllerNode != nullptr) {
			_parentControllerNode->getController()->onSubTreeChange();
			_parentControllerNode = _parentControllerNode->getParentControllerNode();
		}
	}
}

void GUIParentNode::addSubNodes(const string& xml, bool resetScrollOffsets)
{
	screenNode->invalidateLayout(this);
	GUIParser::parse(this, xml);

	floatingNodesCache.clear();
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		if (guiSubNode->flow == GUINode_Flow::FLOATING) {
			floatingNodesCache.push_back(guiSubNode);
		}
	}

	invalidateRenderCaches();
	setConditionsMet();

	if (layouted == false || resetScrollOffsets == true) {
		if (overflowX == GUIParentNode_Overflow::SCROLL) childrenRenderOffsetX = 0.0f;
		if (overflowY == GUIParentNode_Overflow::SCROLL) childrenRenderOffsetY = 0.0f;
	} else {
		if (overflowX == GUIParentNode_Overflow::SCROLL) {
			float elementWidth = computedConstraints.width;
			float contentWidth = getContentWidth();
			auto scrollableWidth = contentWidth - elementWidth;
			if (scrollableWidth < 0.0f) scrollableWidth = 0.0;
			if (childrenRenderOffsetX < 0.0f) childrenRenderOffsetX = 0.0f;
			if (scrollableWidth > 0 && childrenRenderOffsetX > scrollableWidth) childrenRenderOffsetX = scrollableWidth;
		}

		if (overflowY == GUIParentNode_Overflow::SCROLL) {
			float elementHeight = computedConstraints.height;
			float contentHeight = getContentHeight();
			auto scrollableHeight = contentHeight - elementHeight;
			if (scrollableHeight < 0.0f) scrollableHeight = 0.0f;
			if (childrenRenderOffsetY < 0.0f) childrenRenderOffsetY = 0.0f;
			if (scrollableHeight > 0 && childrenRenderOffsetY > scrollableHeight) childrenRenderOffsetY = scrollableHeight;
		}
	}

	{
		auto parentControllerNode = controller != nullptr?this:getParentControllerNode();
		while (parentControllerNode != nullptr) {
			parentControllerNode->getController()->onSubTreeChange();
			parentControllerNode = parentControllerNode->getParentControllerNode();
		}
	}
}

void GUIParentNode::addSubNode(GUINode* node)
{
	if (screenNode->addNode(node) == false) {
		throw GUIParserException(
			"Screen '" +
			(screenNode->id) +
			"' already has a node attached with given node id '" +
			(node->id) +
			"'"
		);
	}
	subNodes.push_back(node);
	if (node->flow == GUINode_Flow::FLOATING) {
		floatingNodesCache.push_back(node);
	}
}

void GUIParentNode::moveSubNode(GUIParentNode* otherParentNode, int index) {
	auto detachedSubNode = otherParentNode->detachSubNode(index);
	if (detachedSubNode == nullptr) return;

	//
	screenNode->invalidateLayout(this);

	// attach detached sub nodes here
	detachedSubNode->parentNode = this;
	subNodes.push_back(detachedSubNode);

	floatingNodesCache.clear();
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		if (guiSubNode->flow == GUINode_Flow::FLOATING) {
			floatingNodesCache.push_back(guiSubNode);
		}
	}

	invalidateRenderCaches();
	setConditionsMet();

	if (overflowX == GUIParentNode_Overflow::SCROLL) childrenRenderOffsetX = 0.0f;
	if (overflowY == GUIParentNode_Overflow::SCROLL) childrenRenderOffsetY = 0.0f;

	//
	{
		auto parentControllerNode = controller != nullptr?this:getParentControllerNode();
		while (parentControllerNode != nullptr) {
			parentControllerNode->getController()->onSubTreeChange();
			parentControllerNode = parentControllerNode->getParentControllerNode();
		}
	}
}

void GUIParentNode::moveSubNodes(GUIParentNode* otherParentNode) {
	auto detachedSubNodes = otherParentNode->detachSubNodes();

	//
	screenNode->invalidateLayout(this);

	// attach detached sub nodes here
	for (auto subNode: detachedSubNodes) {
		subNode->parentNode = this;
		subNodes.push_back(subNode);
	}

	floatingNodesCache.clear();
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		if (guiSubNode->flow == GUINode_Flow::FLOATING) {
			floatingNodesCache.push_back(guiSubNode);
		}
	}

	invalidateRenderCaches();
	setConditionsMet();

	if (overflowX == GUIParentNode_Overflow::SCROLL) childrenRenderOffsetX = 0.0f;
	if (overflowY == GUIParentNode_Overflow::SCROLL) childrenRenderOffsetY = 0.0f;

	//
	{
		auto parentControllerNode = controller != nullptr?this:getParentControllerNode();
		while (parentControllerNode != nullptr) {
			parentControllerNode->getController()->onSubTreeChange();
			parentControllerNode = parentControllerNode->getParentControllerNode();
		}
	}
}

GUIParentNode_Overflow* GUIParentNode::getOverflowX()
{
	return overflowX;
}

GUIParentNode_Overflow* GUIParentNode::getOverflowY()
{
	return overflowY;
}

GUIParentNode_Overflow* GUIParentNode::createOverflow(const string& overflow)
{
	if (StringTools::equalsIgnoreCase(StringTools::trim(overflow), "hidden") == true) {
		return GUIParentNode_Overflow::HIDDEN;
	} else
	if (StringTools::equalsIgnoreCase(StringTools::trim(overflow), "downsize-children") == true) {
		return GUIParentNode_Overflow::DOWNSIZE_CHILDREN;
	} else
	if (StringTools::equalsIgnoreCase(StringTools::trim(overflow), "scroll") == true) {
		return GUIParentNode_Overflow::SCROLL;
	} else
	if (overflow.empty() == true || StringTools::trim(overflow).length() == 0) {
		return GUIParentNode_Overflow::HIDDEN;
	} else {
		throw GUIParserException(
			"Unknown overflow '" +
			(overflow) +
			"'"
		);
	}
}

void GUIParentNode::setChildrenRenderOffsetX(float childrenRenderOffsetX)
{
	invalidateRenderCaches();
	this->childrenRenderOffsetX = childrenRenderOffsetX;
}

void GUIParentNode::setChildrenRenderOffsetY(float childrenRenderOffsetY)
{
	invalidateRenderCaches();
	this->childrenRenderOffsetY = childrenRenderOffsetY;
}

GUINode_RequestedConstraints GUIParentNode::createRequestedConstraints(const string& left, const string& top, const string& width, const string& height, int factor)
{
	GUINode_RequestedConstraints constraints;
	constraints.leftType = getRequestedConstraintsType(StringTools::trim(left), GUINode_RequestedConstraints_RequestedConstraintsType::NONE);
	constraints.left = getRequestedConstraintsValue(StringTools::trim(left), 0);
	constraints.topType = getRequestedConstraintsType(StringTools::trim(top), GUINode_RequestedConstraints_RequestedConstraintsType::NONE);
	constraints.top = getRequestedConstraintsValue(StringTools::trim(top), 0);
	constraints.widthType = getRequestedConstraintsType(StringTools::trim(width), GUINode_RequestedConstraints_RequestedConstraintsType::AUTO);
	constraints.width = getRequestedConstraintsValue(StringTools::trim(width), -1);
	constraints.heightType = getRequestedConstraintsType(StringTools::trim(height), GUINode_RequestedConstraints_RequestedConstraintsType::AUTO);
	constraints.height = getRequestedConstraintsValue(StringTools::trim(height), -1);
	if (constraints.leftType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) constraints.left*= factor;
	if (constraints.topType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) constraints.top*= factor;
	if (constraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) constraints.width*= factor;
	if (constraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) constraints.height*= factor;
	return constraints;
}

void GUIParentNode::layout()
{
	if (conditionsMet == false) return;
	GUINode::layout();
	layoutSubNodes();
}

void GUIParentNode::layoutSubNodes()
{
	if (conditionsMet == false) {
		layouted = false;
		return;
	}
	for (auto i = 0; i < subNodes.size(); i++) {
		subNodes[i]->layout();
	}
}

void GUIParentNode::computeHorizontalChildrenAlignment()
{
	{
		if (alignments.horizontal == GUINode_AlignmentHorizontal::LEFT) {
			for (auto i = 0; i < subNodes.size(); i++) {
				auto guiSubNode = subNodes[i];
				if (guiSubNode->conditionsMet == false) continue;
				guiSubNode->computedConstraints.alignmentLeft = Math::max(0, border.left + padding.left);
			}
		} else
		if (alignments.horizontal == GUINode_AlignmentHorizontal::CENTER) {
			for (auto i = 0; i < subNodes.size(); i++) {
				auto guiSubNode = subNodes[i];
				if (guiSubNode->conditionsMet == false) continue;
				guiSubNode->computedConstraints.alignmentLeft = Math::max(0, (computedConstraints.width - guiSubNode->computedConstraints.width) / 2);
			}
		} else
		if (alignments.horizontal == GUINode_AlignmentHorizontal::RIGHT) {
			for (auto i = 0; i < subNodes.size(); i++) {
				auto guiSubNode = subNodes[i];
				if (guiSubNode->conditionsMet == false) continue;
				guiSubNode->computedConstraints.alignmentLeft = Math::max(0, (computedConstraints.width - guiSubNode->computedConstraints.width - border.right - padding.right));
			}
		}
	}
}

void GUIParentNode::computeVerticalChildrenAlignment()
{
	{
		if (alignments.vertical == GUINode_AlignmentVertical::TOP) {
			for (auto i = 0; i < subNodes.size(); i++) {
				auto guiSubNode = subNodes[i];
				if (guiSubNode->conditionsMet == false) continue;
				guiSubNode->computedConstraints.alignmentTop = Math::max(0, border.top + padding.top);
			}
		} else
		if (alignments.vertical == GUINode_AlignmentVertical::CENTER) {
			for (auto i = 0; i < subNodes.size(); i++) {
				auto guiSubNode = subNodes[i];
				if (guiSubNode->conditionsMet == false) continue;
				guiSubNode->computedConstraints.alignmentTop = Math::max(0, (computedConstraints.height - guiSubNode->computedConstraints.height) / 2);
			}
		} else
		if (alignments.vertical == GUINode_AlignmentVertical::BOTTOM) {
			for (auto i = 0; i < subNodes.size(); i++) {
				auto guiSubNode = subNodes[i];
				if (guiSubNode->conditionsMet == false) continue;
				guiSubNode->computedConstraints.alignmentTop = Math::max(0, (computedConstraints.height - guiSubNode->computedConstraints.height - border.bottom - padding.bottom));
			}
		}
	}
}

void GUIParentNode::getChildControllerNodesInternal(vector<GUINode*>& childControllerNodes, bool requireConditionsMet)
{
	if (requireConditionsMet == true && conditionsMet == false) return;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto node = subNodes[i];
		if (node->controller != nullptr) {
			childControllerNodes.push_back(node);
		}
		if (dynamic_cast<GUIParentNode*>(node) != nullptr) {
			(required_dynamic_cast<GUIParentNode*>(node))->getChildControllerNodesInternal(childControllerNodes);
		}
	}
}

void GUIParentNode::getChildControllerNodes(vector<GUINode*>& childControllerNodes, bool requireConditionsMet)
{
	childControllerNodes.clear();
	getChildControllerNodesInternal(childControllerNodes, requireConditionsMet);
}

void GUIParentNode::dispose()
{
	for (auto i = 0; i < subNodes.size(); i++) {
		subNodes[i]->dispose();
	}
	GUINode::dispose();
}

void GUIParentNode::setConditionsMet()
{
	auto conditionsMetBefore = conditionsMet;
	GUINode::setConditionsMet();
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		guiSubNode->setConditionsMet();
	}
	if (conditionsMetBefore != conditionsMet) invalidateRenderCaches();
}

void GUIParentNode::render(GUIRenderer* guiRenderer)
{
	layoutOnDemand();

	if (shouldRender() == false) return;

	auto renderAreaLeftCurrent = guiRenderer->getRenderAreaLeft();
	auto renderAreaTopCurrent = guiRenderer->getRenderAreaTop();
	auto renderAreaRightCurrent = guiRenderer->getRenderAreaRight();
	auto renderAreaBottomCurrent = guiRenderer->getRenderAreaBottom();
	auto screenWidth = screenNode->getScreenWidth();
	auto screenHeight = screenNode->getScreenHeight();
	float left = computedConstraints.left + computedConstraints.alignmentLeft;
	float top = computedConstraints.top + computedConstraints.alignmentTop;
	float width = computedConstraints.width;
	float height = computedConstraints.height;
	auto renderOffsetXCurrent = guiRenderer->getRenderOffsetX();
	auto renderOffsetYCurrent = guiRenderer->getRenderOffsetY();
	auto renderOffsetXPixel = 0.0f;
	auto renderOffsetYPixel = 0.0f;
	for (auto *_parentNode = this; _parentNode != nullptr; _parentNode = _parentNode->parentNode) {
		renderOffsetXPixel += _parentNode->childrenRenderOffsetX;
		renderOffsetYPixel += _parentNode->childrenRenderOffsetY;
	}
	auto renderOffsetX = renderOffsetXPixel / (screenWidth / 2.0f);
	auto renderOffsetY = renderOffsetYPixel / (screenHeight / 2.0f);
	auto renderAreaLeft = renderAreaLeftCurrent;
	auto renderAreaTop = renderAreaTopCurrent;
	auto renderAreaRight = renderAreaRightCurrent;
	auto renderAreaBottom = renderAreaBottomCurrent;
	// Floating node does not have correct dimension and such due non existance when layouting
	if (flow == GUINode_Flow::INTEGRATED) {
		renderAreaLeft = ((left) / (screenWidth / 2.0f)) - renderOffsetXCurrent - 1.0f;
		renderAreaTop = ((screenHeight - top) / (screenHeight / 2.0f)) + renderOffsetYCurrent - 1.0f;
		renderAreaRight = ((left + width) / (screenWidth / 2.0f)) - renderOffsetXCurrent - 1.0f;
		renderAreaBottom = ((screenHeight - top - height) / (screenHeight / 2.0f)) + renderOffsetYCurrent - 1.0f;
	}
	guiRenderer->setSubRenderAreaLeft(renderAreaLeft);
	guiRenderer->setSubRenderAreaTop(renderAreaTop);
	guiRenderer->setSubRenderAreaRight(renderAreaRight);
	guiRenderer->setSubRenderAreaBottom(renderAreaBottom);
	guiRenderer->setRenderOffsetX(renderOffsetX);
	guiRenderer->setRenderOffsetY(renderOffsetY);

	//
	GUINode::render(guiRenderer);

	//
	if (computeViewportCache == true) {
		for (auto i = 0; i < subNodes.size(); i++) {
			auto guiSubNode = subNodes[i];
			if (guiSubNode->flow == GUINode_Flow::FLOATING) {
				continue;
			}
			if (guiSubNode->layouted == false) {
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
			float left = guiSubNode->computedConstraints.left + guiSubNode->computedConstraints.alignmentLeft + guiSubNode->border.left;
			float top = guiSubNode->computedConstraints.top + guiSubNode->computedConstraints.alignmentTop + guiSubNode->border.top;
			float width = guiSubNode->computedConstraints.width - guiSubNode->border.left - guiSubNode->border.right;
			float height = guiSubNode->computedConstraints.height - guiSubNode->border.top - guiSubNode->border.bottom;
			if (guiRenderer->isQuadVisible(
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top) / (screenHeight / 2.0f)) - 1.0f,
				((left + width) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f,
				((left) / (screenWidth / 2.0f)) - 1.0f,
				((screenHeight - top - height) / (screenHeight / 2.0f)) - 1.0f) == true) {
				//
				//
				if (guiSubNode->hasEffects() == true) guiSubNode->applyEffects(guiRenderer);
				guiSubNode->render(guiRenderer);
				if (guiSubNode->hasEffects() == true) guiSubNode->undoEffects(guiRenderer);
				vieportSubNodesCache.push_back(guiSubNode);
			}
		}
		computeViewportCache = false;
	} else {
		for (auto i = 0; i < vieportSubNodesCache.size(); i++) {
			auto guiSubNode = vieportSubNodesCache[i];
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
			if (guiSubNode->hasEffects() == true) guiSubNode->applyEffects(guiRenderer);
			guiSubNode->render(guiRenderer);
			if (guiSubNode->hasEffects() == true) guiSubNode->undoEffects(guiRenderer);
		}
	}

	//
	guiRenderer->setRenderOffsetX(renderOffsetXCurrent);
	guiRenderer->setRenderOffsetY(renderOffsetYCurrent);
	guiRenderer->setRenderAreaLeft(renderAreaLeftCurrent);
	guiRenderer->setRenderAreaTop(renderAreaTopCurrent);
	guiRenderer->setRenderAreaRight(renderAreaRightCurrent);
	guiRenderer->setRenderAreaBottom(renderAreaBottomCurrent);
}

void GUIParentNode::determineNodesByCoordinate(const Vector2& coordinate, unordered_set<string>& nodeIds) {
	if (conditionsMet == false)
		return;

	//
	if (isCoordinateBelongingToNode(coordinate) == true || flow == GUINode_Flow::FLOATING) {
		for (auto i = 0; i < vieportSubNodesCache.size(); i++) {
			auto subNode = vieportSubNodesCache[i];
			subNode->determineNodesByCoordinate(coordinate, nodeIds);
		}
	}

	//
	GUINode::determineNodesByCoordinate(coordinate, nodeIds);
}

void GUIParentNode::determineMouseEventNodes(GUIMouseEvent* event, bool floatingNode, unordered_set<string>& eventNodeIds, unordered_set<string>& eventFloatingNodeIds, int flags)
{
	if (conditionsMet == false)
		return;

	if (isEventBelongingToNode(event) == true || flow == GUINode_Flow::FLOATING) {
		if (event->getType() == GUIMouseEvent::MOUSEEVENT_WHEEL_MOVED) {
			if (event->getWheelX() != 0.0f && overflowX == GUIParentNode_Overflow::SCROLL) {
				childrenRenderOffsetX -= event->getWheelX() * 10.0f;
				float nodeWidth = this->computedConstraints.width;
				float contentWidth = this->getContentWidth();
				auto scrollableWidth = contentWidth - nodeWidth;
				if (static_cast<int>(nodeWidth) >= static_cast<int>(contentWidth)) {
					childrenRenderOffsetX = 0.0f;
				} else {
					if (childrenRenderOffsetX < 0) childrenRenderOffsetX = 0;
					if (childrenRenderOffsetX > scrollableWidth) childrenRenderOffsetX = scrollableWidth;
					event->setProcessed(true);
				}
				invalidateRenderCaches();
				return;
			}
			if (event->getWheelY() != 0.0f && overflowY == GUIParentNode_Overflow::SCROLL) {
				childrenRenderOffsetY -= event->getWheelY() * 10.0f;
				float nodeHeight = this->computedConstraints.height;
				float contentHeight = this->getContentHeight();
				auto scrollableHeight = contentHeight - nodeHeight;
				if (static_cast<int>(nodeHeight) >= static_cast<int>(contentHeight)) {
					childrenRenderOffsetY = 0.0f;
				} else {
					if (childrenRenderOffsetY < 0.0f) childrenRenderOffsetY = 0.0f;
					if (childrenRenderOffsetY > scrollableHeight) childrenRenderOffsetY = scrollableHeight;
					event->setProcessed(true);
				}
				invalidateRenderCaches();
				return;
			}
		}
		for (auto i = 0; i < vieportSubNodesCache.size(); i++) {
			auto subNode = vieportSubNodesCache[i];
			subNode->determineMouseEventNodes(event, floatingNode == true || subNode->flow == GUINode_Flow::FLOATING, eventNodeIds, eventFloatingNodeIds, flags);
		}
	}

	GUINode::determineMouseEventNodes(event, floatingNode, eventNodeIds, eventFloatingNodeIds, flags);
}

void GUIParentNode::invalidateRenderCaches() {
	computeViewportCache = true;
	vieportSubNodesCache.clear();
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNodeParentNode = dynamic_cast<GUIParentNode*>(subNodes[i]);
		if (guiSubNodeParentNode != nullptr) guiSubNodeParentNode->invalidateRenderCaches();
	}
}

void GUIParentNode::removeSubNode(GUINode* node, bool resetScrollOffsets)
{
	screenNode->invalidateLayout(this);
	subNodes.erase(remove(subNodes.begin(), subNodes.end(), node), subNodes.end());

	floatingNodesCache.clear();
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		if (guiSubNode->flow == GUINode_Flow::FLOATING) {
			floatingNodesCache.push_back(guiSubNode);
		}
	}

	invalidateRenderCaches();
	setConditionsMet();

	{
		auto parentControllerNode = controller != nullptr?this:getParentControllerNode();
		while (parentControllerNode != nullptr) {
			parentControllerNode->getController()->onSubTreeChange();
			parentControllerNode = parentControllerNode->getParentControllerNode();
		}
	}

	if (layouted == false || resetScrollOffsets == true) {
		if (overflowX == GUIParentNode_Overflow::SCROLL) childrenRenderOffsetX = 0.0f;
		if (overflowY == GUIParentNode_Overflow::SCROLL) childrenRenderOffsetY = 0.0f;
	} else {
		if (overflowX == GUIParentNode_Overflow::SCROLL) {
			float elementWidth = computedConstraints.width;
			float contentWidth = getContentWidth();
			auto scrollableWidth = contentWidth - elementWidth;
			if (scrollableWidth < 0.0f) scrollableWidth = 0.0;
			if (childrenRenderOffsetX < 0.0f) childrenRenderOffsetX = 0.0f;
			if (scrollableWidth > 0 && childrenRenderOffsetX > scrollableWidth) childrenRenderOffsetX = scrollableWidth;
		}

		if (overflowY == GUIParentNode_Overflow::SCROLL) {
			float elementHeight = computedConstraints.height;
			float contentHeight = getContentHeight();
			auto scrollableHeight = contentHeight - elementHeight;
			if (scrollableHeight < 0.0f) scrollableHeight = 0.0f;
			if (childrenRenderOffsetY < 0.0f) childrenRenderOffsetY = 0.0f;
			if (scrollableHeight > 0 && childrenRenderOffsetY > scrollableHeight) childrenRenderOffsetY = scrollableHeight;
		}
	}
}

void GUIParentNode::unsetMouseStates() {
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		auto guiElementSubNode = dynamic_cast<GUIElementNode*>(guiSubNode);
		if (guiElementSubNode != nullptr) {
			guiElementSubNode->getActiveConditions().remove(GUIElementNode::CONDITION_ONMOUSEOVER);
			guiElementSubNode->getActiveConditions().remove(GUIElementNode::CONDITION_CLICK);
			guiElementSubNode->unsetMouseStates();
		} else {
			auto guiParentSubNode = dynamic_cast<GUIParentNode*>(guiSubNode);
			if (guiParentSubNode != nullptr) guiParentSubNode->unsetMouseStates();
		}
	}
}
