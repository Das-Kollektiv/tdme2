#include <tdme/gui/elements/GUIDropDownOption.h>

#include <tdme/gui/elements/GUIDropDownOptionController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUIDropDownOption;
using tdme::gui::elements::GUIDropDownOptionController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUIDropDownOption::GUIDropDownOption() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"dropdown-option.xml");
}

wstring GUIDropDownOption::NAME = L"dropdown-option";

const wstring& GUIDropDownOption::getName()
{
	return NAME;
}

const wstring& GUIDropDownOption::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUIDropDownOption::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUIDropDownOption::createController(GUINode* node)
{
	return new GUIDropDownOptionController(node);
}
