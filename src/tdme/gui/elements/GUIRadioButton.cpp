// Generated from /tdme/src/tdme/gui/elements/GUIRadioButton.java
#include <tdme/gui/elements/GUIRadioButton.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUIRadioButtonController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/_HashMap.h>

using tdme::gui::elements::GUIRadioButton;
using java::lang::String;
using tdme::gui::elements::GUIRadioButtonController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::_HashMap;

GUIRadioButton::GUIRadioButton(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIRadioButton::GUIRadioButton()  /* throws(IOException) */
	: GUIRadioButton(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUIRadioButton::NAME;

void GUIRadioButton::ctor() /* throws(IOException) */
{
	super::ctor();
	attributes = new _HashMap();
	template_ = new String(_FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"radiobutton.xml"_j));
}

String* GUIRadioButton::getName()
{
	return NAME;
}

String* GUIRadioButton::getTemplate()
{
	return template_;
}

_HashMap* GUIRadioButton::getAttributes(GUIScreenNode* screenNode)
{
	attributes->clear();
	attributes->put(u"id"_j, screenNode->allocateNodeId());
	attributes->put(u"name"_j, u""_j);
	return attributes;
}

GUINodeController* GUIRadioButton::createController(GUINode* node)
{
	return new GUIRadioButtonController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIRadioButton::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIRadioButton", 32);
    return c;
}

void GUIRadioButton::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"radiobutton"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUIRadioButton::getClass0()
{
	return class_();
}

