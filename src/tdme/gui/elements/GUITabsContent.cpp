#include <tdme/gui/elements/GUITabsContent.h>

#include <map>
#include <string>

#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::string;

using tdme::gui::elements::GUITabsContent;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUITabsContent::GUITabsContent() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui-system/definitions/elements", "tabs-content.xml");
}

string GUITabsContent::NAME = "tabs-content";

const string& GUITabsContent::getName()
{
	return NAME;
}

const string& GUITabsContent::getTemplate()
{
	return template_;
}

map<string, string>* GUITabsContent::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUITabsContent::createController(GUINode* node)
{
	return nullptr;
}

