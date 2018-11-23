#include <tdme/gui/elements/GUISelectBox.h>

#include <tdme/gui/elements/GUISelectBoxController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUISelectBox;
using tdme::gui::elements::GUISelectBoxController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUISelectBox::GUISelectBox() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui-system/definitions/elements", "selectbox.xml");
}

string GUISelectBox::NAME = "selectbox";

const string& GUISelectBox::getName()
{
	return NAME;
}

const string& GUISelectBox::getTemplate()
{
	return template_;
}

map<string, string>* GUISelectBox::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	attributes["width"] = "100%";
	attributes["height"] = "auto";
	attributes["on-change"] = "";
	return &attributes;
}

GUINodeController* GUISelectBox::createController(GUINode* node)
{
	return new GUISelectBoxController(node);
}

