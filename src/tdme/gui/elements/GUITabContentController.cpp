// Generated from /tdme/src/tdme/gui/elements/GUITabContentController.java
#include <tdme/gui/elements/GUITabContentController.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIParentNode.h>

using tdme::gui::elements::GUITabContentController;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUITabContentController::GUITabContentController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUITabContentController::GUITabContentController(GUINode* node) 
	: GUITabContentController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

void GUITabContentController::ctor(GUINode* node)
{
	super::ctor(node);
	this->selected = false;
	CONDITION_SELECTED = node->getId() + L"-selected";
	CONDITION_UNSELECTED = node->getId() + L"-unselected";
}

bool GUITabContentController::isDisabled()
{
	return false;
}

void GUITabContentController::setDisabled(bool disabled)
{
}

bool GUITabContentController::isSelected()
{
	return selected;
}

void GUITabContentController::setSelected(bool selected)
{
	auto nodeConditions = (java_cast< GUIElementNode* >(this->node->getParentNode()))->getActiveConditions();
	nodeConditions->remove(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	this->selected = selected;
	nodeConditions->add(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
}

void GUITabContentController::initialize()
{
	setSelected(selected);
}

void GUITabContentController::dispose()
{
}

void GUITabContentController::postLayout()
{
}

void GUITabContentController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
}

void GUITabContentController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
}

void GUITabContentController::tick()
{
}

void GUITabContentController::onFocusGained()
{
}

void GUITabContentController::onFocusLost()
{
}

bool GUITabContentController::hasValue()
{
	return false;
}

MutableString* GUITabContentController::getValue()
{
	return nullptr;
}

void GUITabContentController::setValue(MutableString* value)
{
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUITabContentController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUITabContentController", 41);
    return c;
}

java::lang::Class* GUITabContentController::getClass0()
{
	return class_();
}

