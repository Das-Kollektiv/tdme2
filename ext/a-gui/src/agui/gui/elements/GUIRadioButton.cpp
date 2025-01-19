#include <agui/gui/elements/GUIRadioButton.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/elements/GUIRadioButtonController.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using agui::gui::elements::GUIRadioButton;
using agui::gui::elements::GUIRadioButtonController;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemException;
using agui::os::filesystem::FileSystemInterface;

string GUIRadioButton::NAME = "radiobutton";

GUIRadioButton::GUIRadioButton()
{
}

const string& GUIRadioButton::getName()
{
	return NAME;
}

const string GUIRadioButton::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"radiobutton.xml":fileName);
}

unordered_map<string, string> GUIRadioButton::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	return attributes;
}

GUINodeController* GUIRadioButton::createController(GUINode* node)
{
	return new GUIRadioButtonController(node);
}

