#include <agui/gui/elements/GUIKnob.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/elements/GUIKnobController.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>

using std::string;
using std::unordered_map;

using agui::gui::elements::GUIKnob;
using agui::gui::elements::GUIKnobController;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemException;
using agui::os::filesystem::FileSystemInterface;

string GUIKnob::NAME = "knob";

GUIKnob::GUIKnob()
{
}

const string& GUIKnob::getName()
{
	return NAME;
}

const string GUIKnob::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"knob.xml":fileName);
}

unordered_map<string, string> GUIKnob::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	attributes["disabled"] = "false";
	attributes["value"] = "0.0";
	return attributes;
}

GUINodeController* GUIKnob::createController(GUINode* node)
{
	return new GUIKnobController(node);
}

