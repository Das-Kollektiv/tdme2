#include <tdme/gui/elements/GUIScrollArea.h>

#include <tdme/gui/elements/GUIScrollAreaController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUIScrollArea;
using tdme::gui::elements::GUIScrollAreaController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUIScrollArea::GUIScrollArea() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui-system/definitions/elements", "scrollarea.xml");
}

string GUIScrollArea::NAME = "scrollarea";

const string& GUIScrollArea::getName()
{
	return NAME;
}

const string& GUIScrollArea::getTemplate()
{
	return template_;
}

map<string, string>* GUIScrollArea::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	attributes["width"] = "100%";
	attributes["height"] = "100%";
	attributes["horizontal-align"] = "left";
	attributes["vertical-align"] = "top";
	attributes["alignment"] = "vertical";
	attributes["background-color"] = "transparent";
	attributes["show-on"] = "";
	attributes["hide-on"] = "";
	return &attributes;
}

GUINodeController* GUIScrollArea::createController(GUINode* node)
{
	return new GUIScrollAreaController(node);
}

