#include <tdme/gui/elements/GUISelectBoxMultipleOption.h>

#include <tdme/gui/elements/GUISelectBoxMultipleOptionController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::string;

using tdme::gui::elements::GUISelectBoxMultipleOption;
using tdme::gui::elements::GUISelectBoxMultipleOptionController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUISelectBoxMultipleOption::GUISelectBoxMultipleOption() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui-system/definitions/elements", "selectbox-multiple-option.xml");
}

string GUISelectBoxMultipleOption::NAME = "selectbox-multiple-option";

const string& GUISelectBoxMultipleOption::getName()
{
	return NAME;
}

const string& GUISelectBoxMultipleOption::getTemplate()
{
	return template_;
}

map<string, string>* GUISelectBoxMultipleOption::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUISelectBoxMultipleOption::createController(GUINode* node)
{
	return new GUISelectBoxMultipleOptionController(node);
}

