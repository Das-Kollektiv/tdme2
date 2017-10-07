#include <tdme/gui/elements/GUITabsContent.h>

#include <map>
#include <string>

#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/_FileSystem.h>
#include <tdme/os/filesystem/_FileSystemException.h>
#include <tdme/os/filesystem/_FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUITabsContent;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::_FileSystem;
using tdme::os::filesystem::_FileSystemException;
using tdme::os::filesystem::_FileSystemInterface;

GUITabsContent::GUITabsContent(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUITabsContent::GUITabsContent() throw (_FileSystemException)
	: GUITabsContent(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUITabsContent::NAME = L"tabs-content";

void GUITabsContent::ctor() throw (_FileSystemException)
{
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"tabs-content.xml");
}

const wstring& GUITabsContent::getName()
{
	return NAME;
}

const wstring& GUITabsContent::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUITabsContent::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUITabsContent::createController(GUINode* node)
{
	return nullptr;
}

