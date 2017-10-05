// Generated from /tdme/src/tdme/gui/elements/GUITabContent.java
#include <tdme/gui/elements/GUITabContent.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUITabContentController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/_FileSystem.h>
#include <tdme/os/filesystem/_FileSystemException.h>
#include <tdme/os/filesystem/_FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUITabContent;
using tdme::gui::elements::GUITabContentController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::_FileSystem;
using tdme::os::filesystem::_FileSystemException;
using tdme::os::filesystem::_FileSystemInterface;

GUITabContent::GUITabContent(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUITabContent::GUITabContent() throw (_FileSystemException)
	: GUITabContent(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUITabContent::NAME = L"tab-content";

void GUITabContent::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"tab-content.xml");
}

const wstring& GUITabContent::getName()
{
	return NAME;
}

const wstring& GUITabContent::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUITabContent::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"horizontal-align"] = L"center";
	attributes[L"vertical-align"] = L"center";
	return &attributes;
}

GUINodeController* GUITabContent::createController(GUINode* node)
{
	return new GUITabContentController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUITabContent::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUITabContent", 31);
    return c;
}

java::lang::Class* GUITabContent::getClass0()
{
	return class_();
}

