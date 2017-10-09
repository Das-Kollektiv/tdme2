#include <tdme/gui/elements/GUIInput.h>

#include <tdme/gui/elements/GUIInputController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUIInput;
using tdme::gui::elements::GUIInputController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

GUIInput::GUIInput() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"input.xml");
}

wstring GUIInput::NAME = L"input";

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

