#include <tdme/gui/elements/GUITabsHeader.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUITabsHeaderController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUITabsHeader;
using tdme::gui::elements::GUITabsHeaderController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUITabsHeader::GUITabsHeader(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUITabsHeader::GUITabsHeader() throw (FileSystemException)
	: GUITabsHeader(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUITabsHeader::NAME = L"tabs-header";

void GUITabsHeader::ctor() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"tabs-header.xml");
}

const wstring& GUITabsHeader::getName()
{
	return NAME;
}

const wstring& GUITabsHeader::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUITabsHeader::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUITabsHeader::createController(GUINode* node)
{
	return new GUITabsHeaderController(node);
}

