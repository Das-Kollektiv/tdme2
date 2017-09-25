// Generated from /tdme/src/tdme/gui/elements/GUIInput.java
#include <tdme/gui/elements/GUIInput.h>

#include <tdme/gui/elements/GUIInputController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>

using tdme::gui::elements::GUIInput;
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

wstring GUIInput::NAME = L"input";

void GUIInput::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"input.xml");
}

const wstring& GUIInput::getName()
{
	return NAME;
}

const wstring& GUIInput::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUIInput::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"width"] = L"auto";
	attributes[L"height"] = L"auto";
	attributes[L"text"] = L"";
	attributes[L"maxlength"] = L"0";
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

java::lang::Class* GUIInput::getClass0()
{
	return class_();
}

