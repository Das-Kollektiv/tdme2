#include <tdme/gui/elements/GUISelectBoxOption.h>

#include <tdme/gui/elements/GUISelectBoxOptionController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUISelectBoxOption;
using tdme::gui::elements::GUISelectBoxOptionController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUISelectBoxOption::GUISelectBoxOption() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"selectbox-option.xml");
}

wstring GUISelectBoxOption::NAME = L"selectbox-option";

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

