// Generated from /tdme/src/tdme/gui/elements/GUIInput.java
#include <tdme/gui/elements/GUIInput.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUIInputController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>

using tdme::gui::elements::GUIInput;
using java::lang::String;
using tdme::gui::elements::GUIInputController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;

GUIInput::GUIInput(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIInput::GUIInput() throw (_FileSystemException)
	: GUIInput(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUIInput::NAME;

void GUIInput::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = new String(_FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"input.xml"_j));
}

String* GUIInput::getName()
{
	return NAME;
}

String* GUIInput::getTemplate()
{
	return template_;
}

map<wstring, String*>* GUIInput::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"width"] = u"auto"_j;
	attributes[L"height"] = u"auto"_j;
	attributes[L"text"] = u""_j;
	attributes[L"maxlength"] = u"0"_j;
	return &attributes;
}

GUINodeController* GUIInput::createController(GUINode* node)
{
	return new GUIInputController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIInput::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIInput", 26);
    return c;
}

void GUIInput::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"input"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUIInput::getClass0()
{
	return class_();
}

