#include <tdme/gui/elements/GUIButton.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUIButtonController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUIButton;
using tdme::gui::elements::GUIButtonController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

wstring GUIButton::NAME = L"button";

GUIButton::GUIButton() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"button.xml");
}

const wstring& GUIButton::getName()
{
	return NAME;
}

const wstring& GUIButton::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUIButton::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"width"] = L"auto";
	attributes[L"height"] = L"auto";
	attributes[L"text"] = L"";
	return &attributes;
}

GUINodeController* GUIButton::createController(GUINode* node)
{
	return new GUIButtonController(node);
}

