// Generated from /tdme/src/tdme/gui/elements/GUIScrollAreaHorizontalController.java
#include <tdme/gui/elements/GUIScrollAreaHorizontalController.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/elements/GUIScrollAreaHorizontalController_initialize_1.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>

using tdme::gui::elements::GUIScrollAreaHorizontalController;
using java::lang::ClassCastException;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::elements::GUIScrollAreaHorizontalController_initialize_1;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

GUIScrollAreaHorizontalController::GUIScrollAreaHorizontalController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIScrollAreaHorizontalController::GUIScrollAreaHorizontalController(GUINode* node) 
	: GUIScrollAreaHorizontalController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

void GUIScrollAreaHorizontalController::ctor(GUINode* node)
{
	super::ctor(node);
}

bool GUIScrollAreaHorizontalController::isDisabled()
{
	return false;
}

void GUIScrollAreaHorizontalController::setDisabled(bool disabled)
{
}

void GUIScrollAreaHorizontalController::initialize()
{
	auto const contentNode = java_cast< GUIParentNode* >(node->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(node->getId())->append(u"_inner"_j)->toString()));
	auto const leftArrowNode = java_cast< GUIElementNode* >(node->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(node->getId())->append(u"_scrollbar_horizontal_layout_left"_j)->toString()));
	auto const rightArrowNode = java_cast< GUIElementNode* >(node->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(node->getId())->append(u"_scrollbar_horizontal_layout_right"_j)->toString()));
	node->getScreenNode()->addActionListener(new GUIScrollAreaHorizontalController_initialize_1(this, leftArrowNode, contentNode, rightArrowNode));
}

void GUIScrollAreaHorizontalController::dispose()
{
}

void GUIScrollAreaHorizontalController::postLayout()
{
}

void GUIScrollAreaHorizontalController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
}

void GUIScrollAreaHorizontalController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
}

void GUIScrollAreaHorizontalController::tick()
{
}

void GUIScrollAreaHorizontalController::onFocusGained()
{
}

void GUIScrollAreaHorizontalController::onFocusLost()
{
}

bool GUIScrollAreaHorizontalController::hasValue()
{
	return false;
}

MutableString* GUIScrollAreaHorizontalController::getValue()
{
	return nullptr;
}

void GUIScrollAreaHorizontalController::setValue(MutableString* value)
{
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIScrollAreaHorizontalController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIScrollAreaHorizontalController", 51);
    return c;
}

java::lang::Class* GUIScrollAreaHorizontalController::getClass0()
{
	return class_();
}

