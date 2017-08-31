// Generated from /tdme/src/tdme/gui/elements/GUISelectBoxMultiple.java
#include <tdme/gui/elements/GUISelectBoxMultiple.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUISelectBoxMultipleController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>

using tdme::gui::elements::GUISelectBoxMultiple;
using java::lang::String;
using tdme::gui::elements::GUISelectBoxMultipleController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;

GUISelectBoxMultiple::GUISelectBoxMultiple(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUISelectBoxMultiple::GUISelectBoxMultiple() throw (_FileSystemException)
	: GUISelectBoxMultiple(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUISelectBoxMultiple::NAME;

void GUISelectBoxMultiple::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = new String(_FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"selectbox-multiple.xml"_j));
}

String* GUISelectBoxMultiple::getName()
{
	return NAME;
}

String* GUISelectBoxMultiple::getTemplate()
{
	return template_;
}

map<wstring, String*>* GUISelectBoxMultiple::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"width"] = u"100%"_j;
	attributes[L"height"] = u"auto"_j;
	return &attributes;
}

GUINodeController* GUISelectBoxMultiple::createController(GUINode* node)
{
	return new GUISelectBoxMultipleController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUISelectBoxMultiple::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUISelectBoxMultiple", 38);
    return c;
}

void GUISelectBoxMultiple::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"selectbox-multiple"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUISelectBoxMultiple::getClass0()
{
	return class_();
}

