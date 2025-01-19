#include <agui/gui/elements/GUIMenuHeaderItem.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/elements/GUIMenuHeaderItemController.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>

using agui::gui::elements::GUIMenuHeaderItem;

using std::string;
using std::unordered_map;

using agui::gui::elements::GUIMenuHeaderItemController;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemException;
using agui::os::filesystem::FileSystemInterface;

string GUIMenuHeaderItem::NAME = "menu-header-item";

GUIMenuHeaderItem::GUIMenuHeaderItem()
{
}

const string& GUIMenuHeaderItem::getName()
{
	return NAME;
}

const string GUIMenuHeaderItem::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"menu-header-item.xml":fileName);
}

unordered_map<string, string> GUIMenuHeaderItem::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	attributes["text"] = "10";
	return attributes;
}

GUINodeController* GUIMenuHeaderItem::createController(GUINode* node)
{
	return new GUIMenuHeaderItemController(node);
}

