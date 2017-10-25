#include <tdme/gui/elements/GUITabs.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUITabsController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::string;

using tdme::gui::elements::GUITabs;
using tdme::gui::elements::GUITabsController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUITabs::GUITabs() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui/definitions/elements", "tabs.xml");
}

string GUITabs::NAME = "tabs";

const string& GUITabs::getName()
{
	return NAME;
}

const string& GUITabs::getTemplate()
{
	return template_;
}

map<string, string>* GUITabs::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	attributes["width"] = "100%";
	attributes["height"] = "*";
	return &attributes;
}

GUINodeController* GUITabs::createController(GUINode* node)
{
	return new GUITabsController(node);
}

