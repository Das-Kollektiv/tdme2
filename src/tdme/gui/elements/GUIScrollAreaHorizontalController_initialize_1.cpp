#include <tdme/gui/elements/GUIScrollAreaHorizontalController_initialize_1.h>

#include <tdme/gui/elements/GUIScrollAreaHorizontalController.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUIParentNode.h>

using tdme::gui::elements::GUIScrollAreaHorizontalController_initialize_1;
using tdme::gui::elements::GUIScrollAreaHorizontalController;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUIParentNode;

GUIScrollAreaHorizontalController_initialize_1::GUIScrollAreaHorizontalController_initialize_1(GUIScrollAreaHorizontalController *GUIScrollAreaHorizontalController_this, GUIElementNode* leftArrowNode, GUIParentNode* contentNode, GUIElementNode* rightArrowNode)
	: GUIScrollAreaHorizontalController_this(GUIScrollAreaHorizontalController_this)
	, leftArrowNode(leftArrowNode)
	, contentNode(contentNode)
	, rightArrowNode(rightArrowNode)
{
}

void GUIScrollAreaHorizontalController_initialize_1::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	if (node == leftArrowNode) {
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

