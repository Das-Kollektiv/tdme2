#include <agui/gui/elements/GUITab.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/elements/GUITabController.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using agui::gui::elements::GUITab;
using agui::gui::elements::GUITabController;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemException;
using agui::os::filesystem::FileSystemInterface;

string GUITab::NAME = "tab";

GUITab::GUITab()
{
}

const string& GUITab::getName()
{
	return NAME;
}

const string GUITab::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"tab.xml":fileName);
}

unordered_map<string, string> GUITab::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	attributes["type-color"] = "transparent";
	return attributes;
}

GUINodeController* GUITab::createController(GUINode* node)
{
	return new GUITabController(node);
}

