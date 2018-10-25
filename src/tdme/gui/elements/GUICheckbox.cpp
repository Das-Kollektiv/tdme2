#include <tdme/gui/elements/GUICheckbox.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUICheckboxController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::string;

using tdme::gui::elements::GUICheckbox;
using tdme::gui::elements::GUICheckboxController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUICheckbox::GUICheckbox() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui-system/definitions/elements", "checkbox.xml");
}

string GUICheckbox::NAME = "checkbox";

const string& GUICheckbox::getName()
{
	return NAME;
}

const string& GUICheckbox::getTemplate()
{
	return template_;
}

map<string, string>* GUICheckbox::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUICheckbox::createController(GUINode* node)
{
	return new GUICheckboxController(node);
}

