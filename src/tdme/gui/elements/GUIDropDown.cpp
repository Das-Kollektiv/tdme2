#include <tdme/gui/elements/GUIDropDown.h>

#include <tdme/gui/elements/GUIDropDownController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/_FileSystem.h>
#include <tdme/os/filesystem/_FileSystemException.h>
#include <tdme/os/filesystem/_FileSystemInterface.h>

using tdme::gui::elements::GUIDropDown;
using tdme::gui::elements::GUIDropDownController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::_FileSystem;
using tdme::os::filesystem::_FileSystemException;
using tdme::os::filesystem::_FileSystemInterface;

GUIDropDown::GUIDropDown(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUIDropDown::GUIDropDown() throw (_FileSystemException)
	: GUIDropDown(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUIDropDown::NAME = L"dropdown";

void GUIDropDown::ctor() throw (_FileSystemException)
{
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"dropdown.xml");
}

const wstring& GUIDropDown::getName()
{
	return NAME;
}

const wstring& GUIDropDown::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUIDropDown::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"width"] = L"100%";
	attributes[L"height"] = L"auto";
	attributes[L"text"] = L"10";
	return &attributes;
}

GUINodeController* GUIDropDown::createController(GUINode* node)
{
	return new GUIDropDownController(node);
}

