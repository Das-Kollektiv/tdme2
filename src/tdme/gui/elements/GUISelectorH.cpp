#include <tdme/gui/elements/GUISelectorH.h>

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/gui/elements/GUISelectorHController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUISelectorH;

using std::string;
using std::unordered_map;

using tdme::gui::elements::GUISelectorHController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

string GUISelectorH::NAME = "selector-horizontal";

GUISelectorH::GUISelectorH()
{
}

const string& GUISelectorH::getName()
{
	return NAME;
}

const string GUISelectorH::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"selector-horizontal.xml":fileName);
}

unordered_map<string, string> GUISelectorH::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	attributes["width"] = "auto";
	attributes["height"] = "auto";
	return attributes;
}

GUINodeController* GUISelectorH::createController(GUINode* node)
{
	return new GUISelectorHController(node);
}

