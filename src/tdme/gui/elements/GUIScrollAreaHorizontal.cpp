#include <tdme/gui/elements/GUIScrollAreaHorizontal.h>

#include <tdme/gui/elements/GUIScrollAreaHorizontalController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUIScrollAreaHorizontal;
using tdme::gui::elements::GUIScrollAreaHorizontalController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUIScrollAreaHorizontal::GUIScrollAreaHorizontal() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui/definitions/elements", "scrollarea-horizontal.xml");
}

string GUIScrollAreaHorizontal::NAME = "scrollarea-horizontal";

const string& GUIScrollAreaHorizontal::getName()
{
	return NAME;
}

const string& GUIScrollAreaHorizontal::getTemplate()
{
	return template_;
}

map<string, string>* GUIScrollAreaHorizontal::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	attributes["width"] = "100%";
	attributes["height"] = "100%";
	attributes["horizontal-align"] = "left";
	attributes["vertical-align"] = "top";
	attributes["alignment"] = "vertical";
	attributes["background-color"] = "transparent";
	attributes["border"] = "0";
	attributes["border-color"] = "transparent";
	attributes["padding"] = "0";
	attributes["show-on"] = "";
	attributes["hide-on"] = "";
	return &attributes;
}

GUINodeController* GUIScrollAreaHorizontal::createController(GUINode* node)
{
	return new GUIScrollAreaHorizontalController(node);
}

