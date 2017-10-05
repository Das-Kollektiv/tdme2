// Generated from /tdme/src/tdme/gui/elements/GUISelectBoxOption.java
#include <tdme/gui/elements/GUISelectBoxOption.h>

#include <tdme/gui/elements/GUISelectBoxOptionController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/_FileSystem.h>
#include <tdme/os/filesystem/_FileSystemException.h>
#include <tdme/os/filesystem/_FileSystemInterface.h>

using tdme::gui::elements::GUISelectBoxOption;
using tdme::gui::elements::GUISelectBoxOptionController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::_FileSystem;
using tdme::os::filesystem::_FileSystemException;
using tdme::os::filesystem::_FileSystemInterface;

GUISelectBoxOption::GUISelectBoxOption(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUISelectBoxOption::GUISelectBoxOption() throw (_FileSystemException)
	: GUISelectBoxOption(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUISelectBoxOption::NAME = L"selectbox-option";

void GUISelectBoxOption::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"selectbox-option.xml");
}

const wstring& GUISelectBoxOption::getName()
{
	return NAME;
}

const wstring& GUISelectBoxOption::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUISelectBoxOption::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUISelectBoxOption::createController(GUINode* node)
{
	return new GUISelectBoxOptionController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUISelectBoxOption::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUISelectBoxOption", 36);
    return c;
}

java::lang::Class* GUISelectBoxOption::getClass0()
{
	return class_();
}

