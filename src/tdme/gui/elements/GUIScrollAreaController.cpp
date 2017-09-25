// Generated from /tdme/src/tdme/gui/elements/GUIScrollAreaController.java
#include <tdme/gui/elements/GUIScrollAreaController.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/elements/GUIScrollAreaController_initialize_1.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>

using tdme::gui::elements::GUIScrollAreaController;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::elements::GUIScrollAreaController_initialize_1;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUIScrollAreaController::GUIScrollAreaController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIScrollAreaController::GUIScrollAreaController(GUINode* node) 
	: GUIScrollAreaController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

void GUIScrollAreaController::ctor(GUINode* node)
{
	super::ctor(node);
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
	auto const contentNode = java_cast< GUIParentNode* >(node->getScreenNode()->getNodeById(node->getId() + L"_inner"));
	auto const upArrowNode = java_cast< GUIElementNode* >(node->getScreenNode()->getNodeById(node->getId() + L"_scrollbar_vertical_layout_up"));
	auto const downArrowNode = java_cast< GUIElementNode* >(node->getScreenNode()->getNodeById(node->getId() + L"_scrollbar_vertical_layout_down"));
	auto const leftArrowNode = java_cast< GUIElementNode* >(node->getScreenNode()->getNodeById(node->getId() + L"_scrollbar_horizontal_layout_left"));
	auto const rightArrowNode = java_cast< GUIElementNode* >(node->getScreenNode()->getNodeById(node->getId() + L"_scrollbar_horizontal_layout_right"));
	node->getScreenNode()->addActionListener(new GUIScrollAreaController_initialize_1(this, upArrowNode, contentNode, downArrowNode, leftArrowNode, rightArrowNode));
}

void GUIScrollAreaController::dispose()
{
}

void GUIScrollAreaController::postLayout()
{
}

void GUIScrollAreaController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
}

void GUIScrollAreaController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
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

MutableString* GUIScrollAreaController::getValue()
{
	return nullptr;
}

void GUIScrollAreaController::setValue(MutableString* value)
{
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIScrollAreaController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIScrollAreaController", 41);
    return c;
}

java::lang::Class* GUIScrollAreaController::getClass0()
{
	return class_();
}

