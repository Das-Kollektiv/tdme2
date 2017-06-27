// Generated from /tdme/src/tdme/gui/elements/GUISelectBox.java
#include <tdme/gui/elements/GUISelectBox.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUISelectBoxController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/_HashMap.h>

using tdme::gui::elements::GUISelectBox;
using java::lang::String;
using tdme::gui::elements::GUISelectBoxController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::_HashMap;

GUISelectBox::GUISelectBox(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUISelectBox::GUISelectBox()  /* throws(IOException) */
	: GUISelectBox(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUISelectBox::NAME;

void GUISelectBox::ctor() /* throws(IOException) */
{
	super::ctor();
	attributes = new _HashMap();
	template_ = _FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"selectbox.xml"_j);
}

String* GUISelectBox::getName()
{
	return NAME;
}

String* GUISelectBox::getTemplate()
{
	return template_;
}

_HashMap* GUISelectBox::getAttributes(GUIScreenNode* screenNode)
{
	attributes->clear();
	attributes->put(u"id"_j, screenNode->allocateNodeId());
	attributes->put(u"width"_j, u"100%"_j);
	attributes->put(u"height"_j, u"auto"_j);
	return attributes;
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

void GUISelectBox::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"selectbox"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUISelectBox::getClass0()
{
	return class_();
}

