#include <tdme/gui/elements/GUIScrollAreaController.h>

#include <memory>

#include <tdme/tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>

using std::make_unique;
using std::unique_ptr;

using tdme::gui::elements::GUIScrollAreaController;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;

GUIScrollAreaController::GUIScrollAreaController(GUINode* node)
	: GUINodeController(node), actionListener(nullptr)
{
}

bool GUIScrollAreaController::isAtBottom() {
	auto contentNode = required_dynamic_cast<GUIParentNode*>(node->getScreenNode()->getNodeById(node->getId() + "_inner"));
	float elementHeight = contentNode->getComputedConstraints().height;
	float contentHeight = contentNode->getContentHeight();
	auto scrollableHeight = contentHeight - elementHeight;
	if (scrollableHeight <= 0.0f) return true;
	auto childrenRenderOffsetY = contentHeight - contentNode->getComputedConstraints().height;
	return contentNode->getChildrenRenderOffsetY() == childrenRenderOffsetY;

}

void GUIScrollAreaController::scrollToBottomInternal() {
	auto contentNode = required_dynamic_cast<GUIParentNode*>(node->getScreenNode()->getNodeById(node->getId() + "_inner"));
	float elementHeight = contentNode->getComputedConstraints().height;
	float contentHeight = contentNode->getContentHeight();
	auto scrollableHeight = contentHeight - elementHeight;
	if (scrollableHeight <= 0.0f) return;
	auto childrenRenderOffsetY = contentHeight - contentNode->getComputedConstraints().height;
	contentNode->setChildrenRenderOffsetY(childrenRenderOffsetY);
}

void GUIScrollAreaController::scrollToBottom() {
	// TODO: Currently we might need a layout pass after changing a scroll area content, hence this work around (1)
	scrollToBottomIssued = true;
	//
	scrollToBottomInternal();
}

bool GUIScrollAreaController::isDisabled()
{
	return false;
}

void GUIScrollAreaController::setDisabled(bool disabled)
{
}

void GUIScrollAreaController::initialize()
{
	class GUIScrollAreaControllerActionListener: public virtual GUIActionListener
	{

	public:
		void onAction(GUIActionListenerType type, GUIElementNode* node) override {
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
			} else
			if (node == downArrowNode) {
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
			} else
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
			} else
			if (node == rightArrowNode) {
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

		/**
		 * Public constructor
		 * @param guiScrollAreaController gui scroll area controller
		 * @param contentNode content node
		 * @param upArrowNode up arrow node
		 * @param downArrowNode down arrow node
		 * @param leftArrowNode left arrow node
		 * @param rightArrowNode right arrow node
		 */
		GUIScrollAreaControllerActionListener(GUIScrollAreaController* guiScrollAreaController, GUIParentNode* contentNode, GUIElementNode* upArrowNode, GUIElementNode* downArrowNode, GUIElementNode* leftArrowNode, GUIElementNode* rightArrowNode)
			: guiScrollAreaController(guiScrollAreaController)
			, contentNode(contentNode)
			, upArrowNode(upArrowNode)
			, downArrowNode(downArrowNode)
			, leftArrowNode(leftArrowNode)
			, rightArrowNode(rightArrowNode) {
		}

	private:
		GUIScrollAreaController* guiScrollAreaController;
		GUIElementNode* upArrowNode;
		GUIParentNode* contentNode;
		GUIElementNode* downArrowNode;
		GUIElementNode* leftArrowNode;
		GUIElementNode* rightArrowNode;
	};


	auto const contentNode = required_dynamic_cast<GUIParentNode*>(node->getScreenNode()->getNodeById(node->getId() + "_inner"));
	auto const upArrowNode = dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(node->getId() + "_scrollbar_vertical_layout_up"));
	auto const downArrowNode = dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(node->getId() + "_scrollbar_vertical_layout_down"));
	auto const leftArrowNode = dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(node->getId() + "_scrollbar_horizontal_layout_left"));
	auto const rightArrowNode = dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(node->getId() + "_scrollbar_horizontal_layout_right"));
	node->getScreenNode()->addActionListener((actionListener = make_unique<GUIScrollAreaControllerActionListener>(this, contentNode, upArrowNode, downArrowNode, leftArrowNode, rightArrowNode)).get());
}

void GUIScrollAreaController::dispose()
{
	if (actionListener != nullptr) {
		node->getScreenNode()->removeActionListener(actionListener.get());
		actionListener = nullptr;
	}
}

void GUIScrollAreaController::postLayout()
{
	// TODO: Currently we might need a layout pass after changing a scroll area content, hence this work around (2)
	if (scrollToBottomIssued == true) {
		scrollToBottomInternal();
		scrollToBottomIssued = false;
	}
	//
	{
		auto const contentNode = required_dynamic_cast<GUIParentNode*>(node->getScreenNode()->getNodeById(node->getId() + "_inner"));
		float elementHeight = contentNode->getComputedConstraints().height;
		float contentHeight = contentNode->getContentHeight();
		auto scrollableHeight = contentHeight - elementHeight;
		auto horizontalScrollBarNode = required_dynamic_cast<GUIParentNode*>(node->getScreenNode()->getNodeById(node->getId() + "_horizontal-scrollbar"));;
		if (contentHeight > elementHeight + horizontalScrollBarNode->getComputedConstraints().height) {
			required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions().add("vertical-scrollbar");
			if (contentNode->getChildrenRenderOffsetY() + elementHeight > contentHeight) {
				contentNode->setChildrenRenderOffsetY(contentHeight - elementHeight);
			}
		} else {
			required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions().remove("vertical-scrollbar");
			contentNode->setChildrenRenderOffsetY(0.0f);
		}
	}
	{
		auto const contentNode = required_dynamic_cast<GUIParentNode*>(node->getScreenNode()->getNodeById(node->getId() + "_inner"));
		float elementWidth = contentNode->getComputedConstraints().width;
		float contentWidth = contentNode->getContentWidth();
		auto scrollableWidth = contentWidth - elementWidth;
		auto verticalScrollBarNode = required_dynamic_cast<GUIParentNode*>(node->getScreenNode()->getNodeById(node->getId() + "_vertical-scrollbar"));;
		if (contentWidth > elementWidth + verticalScrollBarNode->getComputedConstraints().width) {
			required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions().add("horizontal-scrollbar");
			if (contentNode->getChildrenRenderOffsetX() + elementWidth > contentWidth) {
				contentNode->setChildrenRenderOffsetX(contentWidth - elementWidth);
			}
		} else {
			contentNode->setChildrenRenderOffsetX(0.0f);
			required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions().remove("horizontal-scrollbar");
		}
	}
}

void GUIScrollAreaController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
}

void GUIScrollAreaController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
}

void GUIScrollAreaController::tick()
{
}

void GUIScrollAreaController::onFocusGained()
{
}

void GUIScrollAreaController::onFocusLost()
{
}

bool GUIScrollAreaController::hasValue()
{
	return false;
}

const MutableString& GUIScrollAreaController::getValue()
{
	return value;
}

void GUIScrollAreaController::setValue(const MutableString& value)
{
}

void GUIScrollAreaController::onSubTreeChange()
{
}
