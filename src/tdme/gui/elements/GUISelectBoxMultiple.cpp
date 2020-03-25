#include <tdme/gui/elements/GUISelectBoxMultiple.h>

#include <string>
#include <unordered_map>

#include <tdme/gui/elements/GUISelectBoxMultipleController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using tdme::gui::elements::GUISelectBoxMultiple;
using tdme::gui::elements::GUISelectBoxMultipleController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

string GUISelectBoxMultiple::NAME = "selectbox-multiple";

GUISelectBoxMultiple::GUISelectBoxMultiple()
{
}

const string& GUISelectBoxMultiple::getName()
{
	return NAME;
}

const string GUISelectBoxMultiple::getTemplate(const string& pathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(pathName + "/resources/gui-system/definitions/elements", fileName.empty() == true?"selectbox-multiple.xml":fileName);
}

unordered_map<string, string> GUISelectBoxMultiple::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	attributes["width"] = "100%";
	attributes["height"] = "auto";
	return attributes;
}

GUINodeController* GUISelectBoxMultiple::createController(GUINode* node)
{
	return new GUISelectBoxMultipleController(node);
}

