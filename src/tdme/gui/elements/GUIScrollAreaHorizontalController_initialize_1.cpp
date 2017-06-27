// Generated from /tdme/src/tdme/gui/elements/GUIScrollAreaHorizontalController.java
#include <tdme/gui/elements/GUIScrollAreaHorizontalController_initialize_1.h>

#include <tdme/gui/elements/GUIScrollAreaHorizontalController.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUIParentNode.h>

using tdme::gui::elements::GUIScrollAreaHorizontalController_initialize_1;
using tdme::gui::elements::GUIScrollAreaHorizontalController;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUIParentNode;

GUIScrollAreaHorizontalController_initialize_1::GUIScrollAreaHorizontalController_initialize_1(GUIScrollAreaHorizontalController *GUIScrollAreaHorizontalController_this, GUIElementNode* leftArrowNode, GUIParentNode* contentNode, GUIElementNode* rightArrowNode)
	: super(*static_cast< ::default_init_tag* >(0))
	, GUIScrollAreaHorizontalController_this(GUIScrollAreaHorizontalController_this)
	, leftArrowNode(leftArrowNode)
	, contentNode(contentNode)
	, rightArrowNode(rightArrowNode)
{
	clinit();
	ctor();
}

void GUIScrollAreaHorizontalController_initialize_1::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	if (node == leftArrowNode) {
		float elementWidth = contentNode->getComputedConstraints()->width;
		float contentWidth = contentNode->getContentWidth();
		auto scrollableWidth = contentWidth - elementWidth;
		if (scrollableWidth <= 0.0f)
			return;

		auto childrenRenderOffsetX = contentNode->getChildrenRenderOffsetX() - 1.0f;
		if (childrenRenderOffsetX < 0.0f)
			childrenRenderOffsetX = 0.0f;

		contentNode->setChildrenRenderOffsetX(childrenRenderOffsetX);
	} else if (node == rightArrowNode) {
		float elementWidth = contentNode->getComputedConstraints()->width;
		float contentWidth = contentNode->getContentWidth();
		auto scrollableWidth = contentWidth - elementWidth;
		if (scrollableWidth <= 0.0f)
			return;

		auto childrenRenderOffsetX = contentNode->getChildrenRenderOffsetX() + 1.0f;
		if (childrenRenderOffsetX > contentWidth - contentNode->getComputedConstraints()->width) {
			childrenRenderOffsetX = contentWidth - contentNode->getComputedConstraints()->width;
		}
		contentNode->setChildrenRenderOffsetX(childrenRenderOffsetX);
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIScrollAreaHorizontalController_initialize_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* GUIScrollAreaHorizontalController_initialize_1::getClass0()
{
	return class_();
}

