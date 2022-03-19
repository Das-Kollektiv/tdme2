#include <tdme/gui/elements/GUIStyledInput.h>

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUIStyledInput;

using std::string;
using std::unordered_map;

using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

string GUIStyledInput::NAME = "styled-input";

GUIStyledInput::GUIStyledInput()
{
}

const string& GUIStyledInput::getName()
{
	return NAME;
}

const string GUIStyledInput::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"styled-input.xml":fileName);
}

unordered_map<string, string> GUIStyledInput::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	attributes["width"] = "auto";
	attributes["height"] = "auto";
	return attributes;
}

GUINodeController* GUIStyledInput::createController(GUINode* node)
{
	return nullptr;
}

