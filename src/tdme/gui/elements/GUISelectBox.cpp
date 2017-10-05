// Generated from /tdme/src/tdme/gui/elements/GUISelectBox.java
#include <tdme/gui/elements/GUISelectBox.h>

#include <tdme/gui/elements/GUISelectBoxController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/_FileSystem.h>
#include <tdme/os/filesystem/_FileSystemException.h>
#include <tdme/os/filesystem/_FileSystemInterface.h>

using tdme::gui::elements::GUISelectBox;
using tdme::gui::elements::GUISelectBoxController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::_FileSystem;
using tdme::os::filesystem::_FileSystemException;
using tdme::os::filesystem::_FileSystemInterface;

GUISelectBox::GUISelectBox(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUISelectBox::GUISelectBox() throw (_FileSystemException)
	: GUISelectBox(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUISelectBox::NAME = L"selectbox";

void GUISelectBox::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"selectbox.xml");
}

const wstring& GUISelectBox::getName()
{
	return NAME;
}

const wstring& GUISelectBox::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUISelectBox::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"width"] = L"100%";
	attributes[L"height"] = L"auto";
	return &attributes;
}

GUINodeController* GUISelectBox::createController(GUINode* node)
{
	return new GUISelectBoxController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUISelectBox::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUISelectBox", 30);
    return c;
}

java::lang::Class* GUISelectBox::getClass0()
{
	return class_();
}

