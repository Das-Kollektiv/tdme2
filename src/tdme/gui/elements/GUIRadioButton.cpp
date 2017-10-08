#include <tdme/gui/elements/GUIRadioButton.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUIRadioButtonController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUIRadioButton;
using tdme::gui::elements::GUIRadioButtonController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUIRadioButton::GUIRadioButton() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"radiobutton.xml");
}

wstring GUIRadioButton::NAME = L"radiobutton";

const wstring& GUIRadioButton::getName()
{
	return NAME;
}

const wstring& GUIRadioButton::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUIRadioButton::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"name"] = L"";
	return &attributes;
}

GUINodeController* GUIRadioButton::createController(GUINode* node)
{
	return new GUIRadioButtonController(node);
}

