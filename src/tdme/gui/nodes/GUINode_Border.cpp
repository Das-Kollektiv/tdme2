// Generated from /tdme/src/tdme/gui/nodes/GUINode.java
#include <tdme/gui/nodes/GUINode_Border.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>

using tdme::gui::nodes::GUINode_Border;
using java::lang::String;
using java::lang::StringBuilder;

GUINode_Border::GUINode_Border(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUINode_Border::GUINode_Border()
	: GUINode_Border(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUINode_Border::toString()
{
	return ::java::lang::StringBuilder().append(u"Border [left="_j)->append(left)
		->append(u", top="_j)
		->append(top)
		->append(u", right="_j)
		->append(right)
		->append(u", bottom="_j)
		->append(bottom)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUINode_Border::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUINode.Border", 29);
    return c;
}

java::lang::Class* GUINode_Border::getClass0()
{
	return class_();
}

