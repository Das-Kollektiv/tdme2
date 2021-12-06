#include <tdme/gui/elements/GUIContextMenuItem.h>

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/gui/elements/GUIContextMenuItemController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using tdme::gui::elements::GUIContextMenuItem;
using tdme::gui::elements::GUIContextMenuItemController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

string GUIContextMenuItem::NAME = "context-menu-item";

GUIContextMenuItem::GUIContextMenuItem()
{
}

const string& GUIContextMenuItem::getName()
{
	return NAME;
}

const string GUIContextMenuItem::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"context-menu-item.xml":fileName);
}

unordered_map<string, string> GUIContextMenuItem::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	return attributes;
}

GUINodeController* GUIContextMenuItem::createController(GUINode* node)
{
	return new GUIContextMenuItemController(node);
}
