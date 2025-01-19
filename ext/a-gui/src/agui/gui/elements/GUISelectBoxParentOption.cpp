#include <agui/gui/elements/GUISelectBoxParentOption.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/elements/GUISelectBoxParentOptionController.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using agui::gui::elements::GUISelectBoxParentOption;
using agui::gui::elements::GUISelectBoxParentOptionController;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemException;
using agui::os::filesystem::FileSystemInterface;

string GUISelectBoxParentOption::NAME = "selectbox-parent-option";

GUISelectBoxParentOption::GUISelectBoxParentOption()
{
}

const string& GUISelectBoxParentOption::getName()
{
	return NAME;
}

const string GUISelectBoxParentOption::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"selectbox-parent-option.xml":fileName);
}

unordered_map<string, string> GUISelectBoxParentOption::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	return attributes;
}

GUINodeController* GUISelectBoxParentOption::createController(GUINode* node)
{
	return new GUISelectBoxParentOptionController(node);
}

