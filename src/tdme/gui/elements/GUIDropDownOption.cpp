// Generated from /tdme/src/tdme/gui/elements/GUIDropDownOption.java
#include <tdme/gui/elements/GUIDropDownOption.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUIDropDownOptionController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/_HashMap.h>

using tdme::gui::elements::GUIDropDownOption;
using java::lang::String;
using tdme::gui::elements::GUIDropDownOptionController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::_HashMap;

GUIDropDownOption::GUIDropDownOption(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIDropDownOption::GUIDropDownOption()  /* throws(IOException) */
	: GUIDropDownOption(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUIDropDownOption::NAME;

void GUIDropDownOption::ctor() /* throws(IOException) */
{
	super::ctor();
	attributes = new _HashMap();
	template_ = _FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"dropdown-option.xml"_j);
}

String* GUIDropDownOption::getName()
{
	return NAME;
}

String* GUIDropDownOption::getTemplate()
{
	return template_;
}

_HashMap* GUIDropDownOption::getAttributes(GUIScreenNode* screenNode)
{
	attributes->clear();
	attributes->put(u"id"_j, screenNode->allocateNodeId());
	return attributes;
}

GUINodeController* GUIDropDownOption::createController(GUINode* node)
{
	return new GUIDropDownOptionController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIDropDownOption::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIDropDownOption", 35);
    return c;
}

void GUIDropDownOption::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"dropdown-option"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUIDropDownOption::getClass0()
{
	return class_();
}

