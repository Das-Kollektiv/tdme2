#include <tdme/gui/elements/GUIDropDown.h>

#include <tdme/gui/elements/GUIDropDownController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUIDropDown;
using tdme::gui::elements::GUIDropDownController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUIDropDown::GUIDropDown(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUIDropDown::GUIDropDown() throw (FileSystemException)
	: GUIDropDown(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUIDropDown::NAME = L"dropdown";

void GUIDropDown::ctor() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"dropdown.xml");
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

