// Generated from /tdme/src/tdme/gui/elements/GUITabsHeader.java
#include <tdme/gui/elements/GUITabsHeader.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUITabsHeaderController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/_FileSystem.h>
#include <tdme/os/filesystem/_FileSystemException.h>
#include <tdme/os/filesystem/_FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUITabsHeader;
using tdme::gui::elements::GUITabsHeaderController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::_FileSystem;
using tdme::os::filesystem::_FileSystemException;
using tdme::os::filesystem::_FileSystemInterface;

GUITabsHeader::GUITabsHeader(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUITabsHeader::GUITabsHeader() throw (_FileSystemException)
	: GUITabsHeader(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUITabsHeader::NAME = L"tabs-header";

void GUITabsHeader::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"tabs-header.xml");
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

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUITabsHeader::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUITabsHeader", 31);
    return c;
}

java::lang::Class* GUITabsHeader::getClass0()
{
	return class_();
}

