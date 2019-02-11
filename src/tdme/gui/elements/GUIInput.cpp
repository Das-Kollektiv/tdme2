#include <tdme/gui/elements/GUIInput.h>

#include <tdme/gui/elements/GUIInputController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUIInput;
using tdme::gui::elements::GUIInputController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

string GUIInput::NAME = "input";

GUIInput::GUIInput() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui-system/definitions/elements", "input.xml");
}

const string& GUIInput::getName()
{
	return NAME;
}

const string& GUIInput::getTemplate()
{
	return template_;
}

map<string, string>* GUIInput::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	attributes["width"] = "auto";
	attributes["height"] = "auto";
	attributes["text"] = "";
	attributes["maxlength"] = "0";
	attributes["on-mouse-click"] = "";
	attributes["on-mouse-doubleclick"] = "";
	attributes["on-change"] = "";
	return &attributes;
}

GUINodeController* GUIInput::createController(GUINode* node)
{
	return new GUIInputController(node);
}

