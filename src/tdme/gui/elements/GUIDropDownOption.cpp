#include <tdme/gui/elements/GUIDropDownOption.h>

#include <tdme/gui/elements/GUIDropDownOptionController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUIDropDownOption;
using tdme::gui::elements::GUIDropDownOptionController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUIDropDownOption::GUIDropDownOption() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui/definitions/elements", "dropdown-option.xml");
}

string GUIDropDownOption::NAME = "dropdown-option";

const string& GUIDropDownOption::getName()
{
	return NAME;
}

const string& GUIDropDownOption::getTemplate()
{
	return template_;
}

map<string, string>* GUIDropDownOption::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUIDropDownOption::createController(GUINode* node)
{
	return new GUIDropDownOptionController(node);
}
