#include <agui/gui/elements/GUIContextMenuItem.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/elements/GUIContextMenuItemController.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using agui::gui::elements::GUIContextMenuItem;
using agui::gui::elements::GUIContextMenuItemController;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemException;
using agui::os::filesystem::FileSystemInterface;

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
