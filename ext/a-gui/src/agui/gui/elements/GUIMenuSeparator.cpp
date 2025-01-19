#include <agui/gui/elements/GUIMenuSeparator.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using agui::gui::elements::GUIMenuSeparator;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemException;
using agui::os::filesystem::FileSystemInterface;

string GUIMenuSeparator::NAME = "menu-separator";

GUIMenuSeparator::GUIMenuSeparator()
{
}

const string& GUIMenuSeparator::getName()
{
	return NAME;
}

const string GUIMenuSeparator::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"menu-separator.xml":fileName);
}

unordered_map<string, string> GUIMenuSeparator::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	return attributes;
}

GUINodeController* GUIMenuSeparator::createController(GUINode* node)
{
	return nullptr;
}
