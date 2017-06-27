// Generated from /tdme/src/tdme/gui/elements/GUIScrollAreaVerticalController.java
#include <tdme/gui/elements/GUIScrollAreaVerticalController_initialize_1.h>

#include <tdme/gui/elements/GUIScrollAreaVerticalController.h>
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>
#include <tdme/gui/nodes/GUIParentNode.h>

using tdme::gui::elements::GUIScrollAreaVerticalController_initialize_1;
using tdme::gui::elements::GUIScrollAreaVerticalController;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUIParentNode;

GUIScrollAreaVerticalController_initialize_1::GUIScrollAreaVerticalController_initialize_1(GUIScrollAreaVerticalController *GUIScrollAreaVerticalController_this, GUIElementNode* upArrowNode, GUIParentNode* contentNode, GUIElementNode* downArrowNode)
	: super(*static_cast< ::default_init_tag* >(0))
	, GUIScrollAreaVerticalController_this(GUIScrollAreaVerticalController_this)
	, upArrowNode(upArrowNode)
	, contentNode(contentNode)
	, downArrowNode(downArrowNode)
{
	clinit();
	ctor();
}

void GUIScrollAreaVerticalController_initialize_1::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	if (node == upArrowNode) {
		float elementHeight = contentNode->getComputedConstraints()->height;
		float contentHeight = contentNode->getContentHeight();
		auto scrollableHeight = contentHeight - elementHeight;
		if (scrollableHeight <= 0.0f)
			return;

		auto childrenRenderOffsetY = contentNode->getChildrenRenderOffsetY() - 1.0f;
		if (childrenRenderOffsetY < 0.0f)
			childrenRenderOffsetY = 0.0f;

		contentNode->setChildrenRenderOffsetY(childrenRenderOffsetY);
	} else if (node == downArrowNode) {
		float elementHeight = contentNode->getComputedConstraints()->height;
		float contentHeight = contentNode->getContentHeight();
		auto scrollableHeight = contentHeight - elementHeight;
		if (scrollableHeight <= 0.0f)
			return;

		auto childrenRenderOffsetY = contentNode->getChildrenRenderOffsetY() + 1.0f;
		if (childrenRenderOffsetY > contentHeight - contentNode->getComputedConstraints()->height) {
			childrenRenderOffsetY = contentHeight - contentNode->getComputedConstraints()->height;
		}
		contentNode->setChildrenRenderOffsetY(childrenRenderOffsetY);
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIScrollAreaVerticalController_initialize_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* GUIScrollAreaVerticalController_initialize_1::getClass0()
{
	return class_();
}

