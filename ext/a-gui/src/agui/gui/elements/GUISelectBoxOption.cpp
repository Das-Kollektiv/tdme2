#include <agui/gui/elements/GUISelectBoxOption.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/elements/GUISelectBoxOptionController.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using agui::gui::elements::GUISelectBoxOption;
using agui::gui::elements::GUISelectBoxOptionController;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemException;
using agui::os::filesystem::FileSystemInterface;

string GUISelectBoxOption::NAME = "selectbox-option";

GUISelectBoxOption::GUISelectBoxOption()
{
}

const string& GUISelectBoxOption::getName()
{
	return NAME;
}

const string GUISelectBoxOption::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"selectbox-option.xml":fileName);
}

unordered_map<string, string> GUISelectBoxOption::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	return attributes;
}

GUINodeController* GUISelectBoxOption::createController(GUINode* node)
{
	return new GUISelectBoxOptionController(node);
}

