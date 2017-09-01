// Generated from /tdme/src/tdme/gui/elements/GUICheckbox.java
#include <tdme/gui/elements/GUICheckbox.h>

#include <map>
#include <string>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUICheckboxController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUICheckbox;
using java::lang::String;
using tdme::gui::elements::GUICheckboxController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;

GUICheckbox::GUICheckbox(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUICheckbox::GUICheckbox() throw (_FileSystemException)
	: GUICheckbox(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUICheckbox::NAME;

void GUICheckbox::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = new String(_FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"checkbox.xml"));
}

String* GUICheckbox::getName()
{
	return NAME;
}

String* GUICheckbox::getTemplate()
{
	return template_;
}

map<wstring, String*>* GUICheckbox::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUICheckbox::createController(GUINode* node)
{
	return new GUICheckboxController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUICheckbox::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUICheckbox", 29);
    return c;
}

void GUICheckbox::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"checkbox"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUICheckbox::getClass0()
{
	return class_();
}

