// Generated from /tdme/src/tdme/gui/elements/GUITabsContent.java
#include <tdme/gui/elements/GUITabsContent.h>

#include <map>
#include <string>

#include <java/lang/String.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUITabsContent;
using java::lang::String;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;

GUITabsContent::GUITabsContent(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUITabsContent::GUITabsContent() throw (_FileSystemException)
	: GUITabsContent(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUITabsContent::NAME;

void GUITabsContent::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = new String(_FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"tabs-content.xml"));
}

String* GUITabsContent::getName()
{
	return NAME;
}

String* GUITabsContent::getTemplate()
{
	return template_;
}

map<wstring, String*>* GUITabsContent::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUITabsContent::createController(GUINode* node)
{
	return nullptr;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUITabsContent::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUITabsContent", 32);
    return c;
}

void GUITabsContent::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"tabs-content"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUITabsContent::getClass0()
{
	return class_();
}

