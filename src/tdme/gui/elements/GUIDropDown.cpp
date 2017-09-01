// Generated from /tdme/src/tdme/gui/elements/GUIDropDown.java
#include <tdme/gui/elements/GUIDropDown.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUIDropDownController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>

using tdme::gui::elements::GUIDropDown;
using java::lang::String;
using tdme::gui::elements::GUIDropDownController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;

GUIDropDown::GUIDropDown(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIDropDown::GUIDropDown() throw (_FileSystemException)
	: GUIDropDown(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUIDropDown::NAME;

void GUIDropDown::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = new String(_FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"dropdown.xml"));
}

String* GUIDropDown::getName()
{
	return NAME;
}

String* GUIDropDown::getTemplate()
{
	return template_;
}

map<wstring, String*>* GUIDropDown::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"width"] = u"100%"_j;
	attributes[L"height"] = u"auto"_j;
	attributes[L"text"] = u"10"_j;
	return &attributes;
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

