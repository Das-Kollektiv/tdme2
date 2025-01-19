#include <agui/gui/elements/GUIMoveable.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/elements/GUIMoveableController.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using agui::gui::elements::GUIMoveable;
using agui::gui::elements::GUIMoveableController;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemException;
using agui::os::filesystem::FileSystemInterface;

string GUIMoveable::NAME = "moveable";

GUIMoveable::GUIMoveable()
{
}

const string& GUIMoveable::getName()
{
	return NAME;
}

const string GUIMoveable::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"moveable.xml":fileName);
}

unordered_map<string, string> GUIMoveable::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	attributes["width"] = "auto";
	attributes["height"] = "auto";
	attributes["horizontal-align"] = "center";
	attributes["vertical-align"] = "center";
	return attributes;
}

GUINodeController* GUIMoveable::createController(GUINode* node)
{
	return new GUIMoveableController(node);
}

