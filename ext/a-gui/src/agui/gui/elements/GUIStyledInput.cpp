#include <agui/gui/elements/GUIStyledInput.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/elements/GUIStyledInputController.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemInterface.h>

using agui::gui::elements::GUIStyledInput;

using std::string;
using std::unordered_map;

using agui::gui::elements::GUIStyledInputController;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemInterface;

string GUIStyledInput::NAME = "styled-input";

GUIStyledInput::GUIStyledInput()
{
}

const string& GUIStyledInput::getName()
{
	return NAME;
}

const string GUIStyledInput::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"styled-input.xml":fileName);
}

unordered_map<string, string> GUIStyledInput::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	attributes["width"] = "auto";
	attributes["height"] = "auto";
	return attributes;
}

GUINodeController* GUIStyledInput::createController(GUINode* node)
{
	return new GUIStyledInputController(node);
}

