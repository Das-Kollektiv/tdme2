#include <tdme/gui/elements/GUISliderH.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUISliderHController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::string;

using tdme::gui::elements::GUISliderH;
using tdme::gui::elements::GUISliderHController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

string GUISliderH::NAME = "slider-horizontal";

GUISliderH::GUISliderH() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui-system/definitions/elements", "slider-h.xml");
}

const string& GUISliderH::getName()
{
	return NAME;
}

const string& GUISliderH::getTemplate()
{
	return template_;
}

map<string, string>* GUISliderH::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	attributes["disabled"] = "false";
	attributes["value"] = "0.0";
	return &attributes;
}

GUINodeController* GUISliderH::createController(GUINode* node)
{
	return new GUISliderHController(node);
}

