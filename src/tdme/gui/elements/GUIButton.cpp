#include <tdme/gui/elements/GUIButton.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUIButtonController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::string;

using tdme::gui::elements::GUIButton;
using tdme::gui::elements::GUIButtonController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

string GUIButton::NAME = "button";

GUIButton::GUIButton() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui/definitions/elements", "button.xml");
}

const string& GUIButton::getName()
{
	return NAME;
}

const string& GUIButton::getTemplate()
{
	return template_;
}

map<string, string>* GUIButton::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	attributes["width"] = "auto";
	attributes["height"] = "auto";
	attributes["text"] = "";
	return &attributes;
}

GUINodeController* GUIButton::createController(GUINode* node)
{
	return new GUIButtonController(node);
}

