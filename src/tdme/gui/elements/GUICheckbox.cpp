#include <tdme/gui/elements/GUICheckbox.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUICheckboxController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUICheckbox;
using tdme::gui::elements::GUICheckboxController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUICheckbox::GUICheckbox() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"checkbox.xml");
}

wstring GUICheckbox::NAME = L"checkbox";

const wstring& GUICheckbox::getName()
{
	return NAME;
}

const wstring& GUICheckbox::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUICheckbox::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUICheckbox::createController(GUINode* node)
{
	return new GUICheckboxController(node);
}

