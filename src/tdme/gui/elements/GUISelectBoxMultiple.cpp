#include <tdme/gui/elements/GUISelectBoxMultiple.h>

#include <tdme/gui/elements/GUISelectBoxMultipleController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUISelectBoxMultiple;
using tdme::gui::elements::GUISelectBoxMultipleController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUISelectBoxMultiple::GUISelectBoxMultiple() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui/definitions/elements", "selectbox-multiple.xml");
}

string GUISelectBoxMultiple::NAME = "selectbox-multiple";

const string& GUISelectBoxMultiple::getName()
{
	return NAME;
}

const string& GUISelectBoxMultiple::getTemplate()
{
	return template_;
}

map<string, string>* GUISelectBoxMultiple::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	attributes["width"] = "100%";
	attributes["height"] = "auto";
	return &attributes;
}

GUINodeController* GUISelectBoxMultiple::createController(GUINode* node)
{
	return new GUISelectBoxMultipleController(node);
}

