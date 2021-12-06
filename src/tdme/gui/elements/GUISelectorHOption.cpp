#include <tdme/gui/elements/GUISelectorHOption.h>

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/gui/elements/GUISelectorHOptionController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using tdme::gui::elements::GUISelectorHOption;

using tdme::gui::elements::GUISelectorHOptionController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

string GUISelectorHOption::NAME = "selector-horizontal-option";

GUISelectorHOption::GUISelectorHOption()
{
}

const string& GUISelectorHOption::getName()
{
	return NAME;
}

const string GUISelectorHOption::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"selector-h-option.xml":fileName);
}

unordered_map<string, string> GUISelectorHOption::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	return attributes;
}

GUINodeController* GUISelectorHOption::createController(GUINode* node)
{
	return new GUISelectorHOptionController(node);
}
