#include <tdme/gui/elements/GUIRadioButton.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUIRadioButtonController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::string;

using tdme::gui::elements::GUIRadioButton;
using tdme::gui::elements::GUIRadioButtonController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUIRadioButton::GUIRadioButton() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui-system/definitions/elements", "radiobutton.xml");
}

string GUIRadioButton::NAME = "radiobutton";

const string& GUIRadioButton::getName()
{
	return NAME;
}

const string& GUIRadioButton::getTemplate()
{
	return template_;
}

map<string, string>* GUIRadioButton::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	attributes["name"] = "";
	attributes["on-change"] = "";
	return &attributes;
}

GUINodeController* GUIRadioButton::createController(GUINode* node)
{
	return new GUIRadioButtonController(node);
}

