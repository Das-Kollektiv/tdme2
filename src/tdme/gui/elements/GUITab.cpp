// Generated from /tdme/src/tdme/gui/elements/GUITab.java
#include <tdme/gui/elements/GUITab.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUITabController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/_FileSystem.h>
#include <tdme/os/filesystem/_FileSystemException.h>
#include <tdme/os/filesystem/_FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUITab;
using tdme::gui::elements::GUITabController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::_FileSystem;
using tdme::os::filesystem::_FileSystemException;
using tdme::os::filesystem::_FileSystemInterface;

GUITab::GUITab(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUITab::GUITab() throw (_FileSystemException)
	: GUITab(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUITab::NAME = L"tab";

void GUITab::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"tab.xml");
}

const wstring& GUITab::getName()
{
	return NAME;
}

const wstring& GUITab::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUITab::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUITab::createController(GUINode* node)
{
	return new GUITabController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUITab::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUITab", 24);
    return c;
}

java::lang::Class* GUITab::getClass0()
{
	return class_();
}

