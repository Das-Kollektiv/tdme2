// Generated from /tdme/src/tdme/gui/elements/GUIButton.java
#include <tdme/gui/elements/GUIButton.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUIButtonController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/_HashMap.h>

using tdme::gui::elements::GUIButton;
using java::lang::String;
using tdme::gui::elements::GUIButtonController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::_HashMap;

GUIButton::GUIButton(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIButton::GUIButton()  /* throws(IOException) */
	: GUIButton(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUIButton::NAME;

void GUIButton::ctor() /* throws(IOException) */
{
	super::ctor();
	attributes = new _HashMap();
	template_ = _FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"button.xml"_j);
}

String* GUIButton::getName()
{
	return NAME;
}

String* GUIButton::getTemplate()
{
	return template_;
}

_HashMap* GUIButton::getAttributes(GUIScreenNode* screenNode)
{
	attributes->clear();
	attributes->put(u"id"_j, screenNode->allocateNodeId());
	attributes->put(u"width"_j, u"auto"_j);
	attributes->put(u"height"_j, u"auto"_j);
	attributes->put(u"text"_j, u""_j);
	return attributes;
}

GUINodeController* GUIButton::createController(GUINode* node)
{
	return new GUIButtonController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIButton::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIButton", 27);
    return c;
}

void GUIButton::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"button"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUIButton::getClass0()
{
	return class_();
}

