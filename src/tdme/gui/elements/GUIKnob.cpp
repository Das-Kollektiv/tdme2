#include <tdme/gui/elements/GUIKnob.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUIKnobController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::string;

using tdme::gui::elements::GUIKnob;
using tdme::gui::elements::GUIKnobController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

string GUIKnob::NAME = "knob";

GUIKnob::GUIKnob() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui/definitions/elements", "knob.xml");
}

const string& GUIKnob::getName()
{
	return NAME;
}

const string& GUIKnob::getTemplate()
{
	return template_;
}

map<string, string>* GUIKnob::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	attributes["disabled"] = "false";
	attributes["value"] = "0.0";
	return &attributes;
}

GUINodeController* GUIKnob::createController(GUINode* node)
{
	return new GUIKnobController(node);
}

