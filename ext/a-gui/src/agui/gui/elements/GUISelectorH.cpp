#include <agui/gui/elements/GUISelectorH.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/elements/GUISelectorHController.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>

using agui::gui::elements::GUISelectorH;

using std::string;
using std::unordered_map;

using agui::gui::elements::GUISelectorHController;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemException;
using agui::os::filesystem::FileSystemInterface;

string GUISelectorH::NAME = "selector-horizontal";

GUISelectorH::GUISelectorH()
{
}

const string& GUISelectorH::getName()
{
	return NAME;
}

const string GUISelectorH::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"selector-horizontal.xml":fileName);
}

unordered_map<string, string> GUISelectorH::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	attributes["width"] = "auto";
	attributes["height"] = "auto";
	return attributes;
}

GUINodeController* GUISelectorH::createController(GUINode* node)
{
	return new GUISelectorHController(node);
}

