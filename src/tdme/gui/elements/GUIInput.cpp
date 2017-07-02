// Generated from /tdme/src/tdme/gui/elements/GUIInput.java
#include <tdme/gui/elements/GUIInput.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUIInputController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/_HashMap.h>

using tdme::gui::elements::GUIInput;
using java::lang::String;
using tdme::gui::elements::GUIInputController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::_HashMap;

GUIInput::GUIInput(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIInput::GUIInput()  /* throws(IOException) */
	: GUIInput(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUIInput::NAME;

void GUIInput::ctor() /* throws(IOException) */
{
	super::ctor();
	attributes = new _HashMap();
	template_ = new String(_FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"input.xml"_j));
}

String* GUIInput::getName()
{
	return NAME;
}

String* GUIInput::getTemplate()
{
	return template_;
}

_HashMap* GUIInput::getAttributes(GUIScreenNode* screenNode)
{
	attributes->clear();
	attributes->put(u"id"_j, screenNode->allocateNodeId());
	attributes->put(u"width"_j, u"auto"_j);
	attributes->put(u"height"_j, u"auto"_j);
	attributes->put(u"text"_j, u""_j);
	attributes->put(u"maxlength"_j, u"0"_j);
	return attributes;
}

GUINodeController* GUIInput::createController(GUINode* node)
{
	return new GUIInputController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIInput::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIInput", 26);
    return c;
}

void GUIInput::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"input"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUIInput::getClass0()
{
	return class_();
}

