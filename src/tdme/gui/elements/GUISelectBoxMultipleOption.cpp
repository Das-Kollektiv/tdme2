#include <tdme/gui/elements/GUISelectBoxMultipleOption.h>

#include <string>
#include <unordered_map>

#include <tdme/gui/elements/GUISelectBoxMultipleOptionController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using tdme::gui::elements::GUISelectBoxMultipleOption;
using tdme::gui::elements::GUISelectBoxMultipleOptionController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

string GUISelectBoxMultipleOption::NAME = "selectbox-multiple-option";

GUISelectBoxMultipleOption::GUISelectBoxMultipleOption()
{
}

const string& GUISelectBoxMultipleOption::getName()
{
	return NAME;
}

const string GUISelectBoxMultipleOption::getTemplate(const string& pathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(pathName + "/resources/engine/gui/definitions", fileName.empty() == true?"selectbox-multiple-option.xml":fileName);
}

unordered_map<string, string> GUISelectBoxMultipleOption::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	return attributes;
}

GUINodeController* GUISelectBoxMultipleOption::createController(GUINode* node)
{
	return new GUISelectBoxMultipleOptionController(node);
}

