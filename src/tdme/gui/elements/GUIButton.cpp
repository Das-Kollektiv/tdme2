// Generated from /tdme/src/tdme/gui/elements/GUIButton.java
#include <tdme/gui/elements/GUIButton.h>

#include <map>
#include <string>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUIButtonController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUIButton;
using java::lang::String;
using tdme::gui::elements::GUIButtonController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;

GUIButton::GUIButton(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIButton::GUIButton() throw (_FileSystemException)
	: GUIButton(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUIButton::NAME;

void GUIButton::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = new String(_FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"button.xml"));
}

String* GUIButton::getName()
{
	return NAME;
}

String* GUIButton::getTemplate()
{
	return template_;
}

map<wstring, String*>* GUIButton::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"width"] = u"auto"_j;
	attributes[L"height"] = u"auto"_j;
	attributes[L"text"] = u""_j;
	return &attributes;
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

