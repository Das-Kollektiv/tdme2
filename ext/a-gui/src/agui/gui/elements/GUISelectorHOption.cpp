#include <agui/gui/elements/GUISelectorHOption.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/elements/GUISelectorHOptionController.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using agui::gui::elements::GUISelectorHOption;

using agui::gui::elements::GUISelectorHOptionController;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemException;
using agui::os::filesystem::FileSystemInterface;

string GUISelectorHOption::NAME = "selector-horizontal-option";

GUISelectorHOption::GUISelectorHOption()
{
}

const string& GUISelectorHOption::getName()
{
	return NAME;
}

const string GUISelectorHOption::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"selector-horizontal-option.xml":fileName);
}

unordered_map<string, string> GUISelectorHOption::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	return attributes;
}

GUINodeController* GUISelectorHOption::createController(GUINode* node)
{
	return new GUISelectorHOptionController(node);
}
