#include <tdme/gui/elements/GUIScrollAreaController_initialize_1.h>

#include <tdme/gui/elements/GUIScrollAreaController.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUIParentNode.h>

using tdme::gui::elements::GUIScrollAreaController_initialize_1;
using tdme::gui::elements::GUIScrollAreaController;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUIParentNode;

GUIScrollAreaController_initialize_1::GUIScrollAreaController_initialize_1(GUIScrollAreaController *GUIScrollAreaController_this, GUIElementNode* upArrowNode, GUIParentNode* contentNode, GUIElementNode* downArrowNode, GUIElementNode* leftArrowNode, GUIElementNode* rightArrowNode)
	: GUIScrollAreaController_this(GUIScrollAreaController_this)
	, upArrowNode(upArrowNode)
	, contentNode(contentNode)
	, downArrowNode(downArrowNode)
	, leftArrowNode(leftArrowNode)
	, rightArrowNode(rightArrowNode)
{
}

void GUIScrollAreaController_initialize_1::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	if (node == upArrowNode) {
		float elementHeight = contentNode->getComputedConstraints().height;
		float contentHeight = contentNode->getContentHeight();
		auto scrollableHeight = contentHeight - elementHeight;
		if (scrollableHeight <= 0.0f)
			return;

		auto childrenRenderOffsetY = contentNode->getChildrenRenderOffsetY() - 1.0f;
		if (childrenRenderOffsetY < 0.0f)
			childrenRenderOffsetY = 0.0f;

		contentNode->setChildrenRenderOffsetY(childrenRenderOffsetY);
	} else if (node == downArrowNode) {
		float elementHeight = contentNode->getComputedConstraints().height;
		float contentHeight = contentNode->getContentHeight();
		auto scrollableHeight = contentHeight - elementHeight;
		if (scrollableHeight <= 0.0f)
			return;

		auto childrenRenderOffsetY = contentNode->getChildrenRenderOffsetY() + 1.0f;
		if (childrenRenderOffsetY > contentHeight - contentNode->getComputedConstraints().height) {
			childrenRenderOffsetY = contentHeight - contentNode->getComputedConstraints().height;
		}
		contentNode->setChildrenRenderOffsetY(childrenRenderOffsetY);
	} else if (node == leftArrowNode) {
		float elementWidth = contentNode->getComputedConstraints().width;
		float contentWidth = contentNode->getContentWidth();
		auto scrollableWidth = contentWidth - elementWidth;
		if (scrollableWidth <= 0.0f)
			return;

		auto childrenRenderOffsetX = contentNode->getChildrenRenderOffsetX() - 1.0f;
		if (childrenRenderOffsetX < 0.0f)
			childrenRenderOffsetX = 0.0f;

		contentNode->setChildrenRenderOffsetX(childrenRenderOffsetX);
	} else if (node == rightArrowNode) {
		float elementWidth = contentNode->getComputedConstraints().width;
		float contentWidth = contentNode->getContentWidth();
		auto scrollableWidth = contentWidth - elementWidth;
		if (scrollableWidth <= 0.0f)
			return;

		auto childrenRenderOffsetX = contentNode->getChildrenRenderOffsetX() + 1.0f;
		if (childrenRenderOffsetX > contentWidth - contentNode->getComputedConstraints().width) {
			childrenRenderOffsetX = contentWidth - contentNode->getComputedConstraints().width;
		}
		contentNode->setChildrenRenderOffsetX(childrenRenderOffsetX);
	}
}

