#include <tdme/gui/elements/GUIContextMenu.h>

#include <string>
#include <unordered_map>

#include <tdme/gui/elements/GUIContextMenuController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUIContextMenu;

using std::string;
using std::unordered_map;

using tdme::gui::elements::GUIContextMenuController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

string GUIContextMenu::NAME = "context-menu";

GUIContextMenu::GUIContextMenu()
{
}

const string& GUIContextMenu::getName()
{
	return NAME;
}

const string GUIContextMenu::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"context-menu.xml":fileName);
}

unordered_map<string, string> GUIContextMenu::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	attributes["text"] = "10";
	return attributes;
}

GUINodeController* GUIContextMenu::createController(GUINode* node)
{
	return new GUIContextMenuController(node);
}

