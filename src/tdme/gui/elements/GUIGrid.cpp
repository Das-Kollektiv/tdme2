#include <tdme/gui/elements/GUIGrid.h>

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/gui/elements/GUIGridController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using tdme::gui::elements::GUIGrid;
using tdme::gui::elements::GUIGridController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

string GUIGrid::NAME = "grid";

GUIGrid::GUIGrid()
{
}

const string& GUIGrid::getName()
{
	return NAME;
}

const string GUIGrid::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"grid.xml":fileName);
}

unordered_map<string, string> GUIGrid::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	attributes["width"] = "100%";
	attributes["height"] = "auto";
	return attributes;
}

GUINodeController* GUIGrid::createController(GUINode* node)
{
	return new GUIGridController(node);
}

