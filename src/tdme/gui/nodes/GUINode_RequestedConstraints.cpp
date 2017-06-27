// Generated from /tdme/src/tdme/gui/nodes/GUINode.java
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>

using tdme::gui::nodes::GUINode_RequestedConstraints;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;

GUINode_RequestedConstraints::GUINode_RequestedConstraints(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUINode_RequestedConstraints::GUINode_RequestedConstraints()
	: GUINode_RequestedConstraints(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUINode_RequestedConstraints::toString()
{
	return ::java::lang::StringBuilder().append(left)->append(u" "_j)
		->append(leftType->toString()->toLowerCase())
		->append(u", "_j)
		->append(top)
		->append(u" "_j)
		->append(topType->toString()->toLowerCase())
		->append(u", "_j)
		->append(width)
		->append(u" "_j)
		->append(widthType->toString()->toLowerCase())
		->append(u", "_j)
		->append(height)
		->append(u" "_j)
		->append(heightType->toString()->toLowerCase())->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUINode_RequestedConstraints::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUINode.RequestedConstraints", 43);
    return c;
}

java::lang::Class* GUINode_RequestedConstraints::getClass0()
{
	return class_();
}

