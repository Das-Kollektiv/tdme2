// Generated from /tdme/src/tdme/gui/nodes/GUINode.java
#include <tdme/gui/nodes/GUINode_Padding.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>

using tdme::gui::nodes::GUINode_Padding;
using java::lang::String;
using java::lang::StringBuilder;

GUINode_Padding::GUINode_Padding(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUINode_Padding::GUINode_Padding()
	: GUINode_Padding(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUINode_Padding::toString()
{
	return ::java::lang::StringBuilder().append(u"Padding [left="_j)->append(left)
		->append(u", top="_j)
		->append(top)
		->append(u", right="_j)
		->append(right)
		->append(u", bottom="_j)
		->append(bottom)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUINode_Padding::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUINode.Padding", 30);
    return c;
}

java::lang::Class* GUINode_Padding::getClass0()
{
	return class_();
}

