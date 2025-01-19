#include <agui/gui/elements/GUICheckbox.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/elements/GUICheckboxController.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using agui::gui::elements::GUICheckbox;
using agui::gui::elements::GUICheckboxController;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemException;
using agui::os::filesystem::FileSystemInterface;

string GUICheckbox::NAME = "checkbox";

GUICheckbox::GUICheckbox()
{
}

const string& GUICheckbox::getName()
{
	return NAME;
}

const string GUICheckbox::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"checkbox.xml":fileName);
}

unordered_map<string, string> GUICheckbox::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	attributes["image-unchecked"] = "resources/a-gui/images/checkbox_unchecked.png";
	attributes["image-checked"] = "resources/a-gui/images/checkbox_checked.png";
	attributes["size"] = "25";
	return attributes;
}

GUINodeController* GUICheckbox::createController(GUINode* node)
{
	return new GUICheckboxController(node);
}

