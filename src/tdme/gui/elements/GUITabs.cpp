#include <tdme/gui/elements/GUITabs.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUITabsController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/_FileSystem.h>
#include <tdme/os/filesystem/_FileSystemException.h>
#include <tdme/os/filesystem/_FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUITabs;
using tdme::gui::elements::GUITabsController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::_FileSystem;
using tdme::os::filesystem::_FileSystemException;
using tdme::os::filesystem::_FileSystemInterface;

GUITabs::GUITabs(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUITabs::GUITabs() throw (_FileSystemException)
	: GUITabs(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUITabs::NAME = L"tabs";

void GUITabs::ctor() throw (_FileSystemException)
{
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"tabs.xml");
}

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

