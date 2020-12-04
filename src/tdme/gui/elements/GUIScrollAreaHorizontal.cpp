#include <tdme/gui/elements/GUIScrollAreaHorizontal.h>

#include <string>
#include <unordered_map>

#include <tdme/gui/elements/GUIScrollAreaHorizontalController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using tdme::gui::elements::GUIScrollAreaHorizontal;
using tdme::gui::elements::GUIScrollAreaHorizontalController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

string GUIScrollAreaHorizontal::NAME = "scrollarea-horizontal";

GUIScrollAreaHorizontal::GUIScrollAreaHorizontal()
{
}

const string& GUIScrollAreaHorizontal::getName()
{
	return NAME;
}

const string GUIScrollAreaHorizontal::getTemplate(const string& pathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(pathName + "/resources/engine/gui/definitions", fileName.empty() == true?"scrollarea-horizontal.xml":fileName);
}

unordered_map<string, string> GUIScrollAreaHorizontal::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
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
	return attributes;
}

GUINodeController* GUIScrollAreaHorizontal::createController(GUINode* node)
{
	return new GUIScrollAreaHorizontalController(node);
}

