// Generated from /tdme/src/tdme/gui/elements/GUIDropDown.java
#include <tdme/gui/elements/GUIDropDown.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUIDropDownController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/_HashMap.h>

using tdme::gui::elements::GUIDropDown;
using java::lang::String;
using tdme::gui::elements::GUIDropDownController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::_HashMap;

GUIDropDown::GUIDropDown(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIDropDown::GUIDropDown()  /* throws(IOException) */
	: GUIDropDown(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUIDropDown::NAME;

void GUIDropDown::ctor() /* throws(IOException) */
{
	super::ctor();
	attributes = new _HashMap();
	template_ = new String(_FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"dropdown.xml"_j));
}

String* GUIDropDown::getName()
{
	return NAME;
}

String* GUIDropDown::getTemplate()
{
	return template_;
}

_HashMap* GUIDropDown::getAttributes(GUIScreenNode* screenNode)
{
	attributes->clear();
	attributes->put(u"id"_j, screenNode->allocateNodeId());
	attributes->put(u"width"_j, u"100%"_j);
	attributes->put(u"height"_j, u"auto"_j);
	attributes->put(u"text"_j, u"10"_j);
	return attributes;
}

GUINodeController* GUIDropDown::createController(GUINode* node)
{
	return new GUIDropDownController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIDropDown::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIDropDown", 29);
    return c;
}

void GUIDropDown::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"dropdown"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUIDropDown::getClass0()
{
	return class_();
}

