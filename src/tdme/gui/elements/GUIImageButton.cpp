#include <tdme/gui/elements/GUIImageButton.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUIButtonController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::string;

using tdme::gui::elements::GUIImageButton;
using tdme::gui::elements::GUIButtonController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

string GUIImageButton::NAME = "image-button";

GUIImageButton::GUIImageButton() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui-system/definitions/elements", "image-button.xml");
}

const string& GUIImageButton::getName()
{
	return NAME;
}

const string& GUIImageButton::getTemplate()
{
	return template_;
}

map<string, string>* GUIImageButton::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	attributes["width"] = "auto";
	attributes["height"] = "auto";
	return &attributes;
}

GUINodeController* GUIImageButton::createController(GUINode* node)
{
	return new GUIButtonController(node);
}

