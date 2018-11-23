#include <tdme/gui/elements/GUISliderV.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUISliderVController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::string;

using tdme::gui::elements::GUISliderV;
using tdme::gui::elements::GUISliderVController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

string GUISliderV::NAME = "slider-vertical";

GUISliderV::GUISliderV() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui-system/definitions/elements", "slider-v.xml");
}

const string& GUISliderV::getName()
{
	return NAME;
}

const string& GUISliderV::getTemplate()
{
	return template_;
}

map<string, string>* GUISliderV::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	attributes["disabled"] = "false";
	attributes["value"] = "0.0";
	attributes["on-change"] = "";
	return &attributes;
}

GUINodeController* GUISliderV::createController(GUINode* node)
{
	return new GUISliderVController(node);
}

