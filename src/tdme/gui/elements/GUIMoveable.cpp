#include <tdme/gui/elements/GUIMoveable.h>

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/gui/elements/GUIMoveableController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using tdme::gui::elements::GUIMoveable;
using tdme::gui::elements::GUIMoveableController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

string GUIMoveable::NAME = "moveable";

GUIMoveable::GUIMoveable()
{
}

const string& GUIMoveable::getName()
{
	return NAME;
}

const string GUIMoveable::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"moveable.xml":fileName);
}

unordered_map<string, string> GUIMoveable::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	attributes["left"] = "0";
	attributes["top"] = "0";
	attributes["width"] = "auto";
	attributes["height"] = "auto";
	attributes["horizontal-align"] = "center";
	attributes["vertical-align"] = "center";
	attributes["alignment"] = "none";
	return attributes;
}

GUINodeController* GUIMoveable::createController(GUINode* node)
{
	return new GUIMoveableController(node);
}

