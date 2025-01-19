#include <agui/gui/elements/GUIContextMenu.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/elements/GUIContextMenuController.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>

using agui::gui::elements::GUIContextMenu;

using std::string;
using std::unordered_map;

using agui::gui::elements::GUIContextMenuController;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemException;
using agui::os::filesystem::FileSystemInterface;

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

