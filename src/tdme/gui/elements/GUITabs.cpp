#include <tdme/gui/elements/GUITabs.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUITabsController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUITabs;
using tdme::gui::elements::GUITabsController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUITabs::GUITabs() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"tabs.xml");
}

wstring GUITabs::NAME = L"tabs";

const wstring& GUITabs::getName()
{
	return NAME;
}

const wstring& GUITabs::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUITabs::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"width"] = L"100%";
	attributes[L"height"] = L"*";
	return &attributes;
}

GUINodeController* GUITabs::createController(GUINode* node)
{
	return new GUITabsController(node);
}

