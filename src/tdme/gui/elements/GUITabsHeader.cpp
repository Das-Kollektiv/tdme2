#include <tdme/gui/elements/GUITabsHeader.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUITabsHeaderController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::string;

using tdme::gui::elements::GUITabsHeader;
using tdme::gui::elements::GUITabsHeaderController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUITabsHeader::GUITabsHeader() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString("resources/gui/definitions/elements", "tabs-header.xml");
}

string GUITabsHeader::NAME = "tabs-header";

const string& GUITabsHeader::getName()
{
	return NAME;
}

const string& GUITabsHeader::getTemplate()
{
	return template_;
}

map<string, string>* GUITabsHeader::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes["id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUITabsHeader::createController(GUINode* node)
{
	return new GUITabsHeaderController(node);
}

