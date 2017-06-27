// Generated from /tdme/src/tdme/gui/nodes/GUINode.java
#include <tdme/gui/nodes/GUINode_ComputedConstraints.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>

using tdme::gui::nodes::GUINode_ComputedConstraints;
using java::lang::String;
using java::lang::StringBuilder;

GUINode_ComputedConstraints::GUINode_ComputedConstraints(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUINode_ComputedConstraints::GUINode_ComputedConstraints()
	: GUINode_ComputedConstraints(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUINode_ComputedConstraints::toString()
{
	return ::java::lang::StringBuilder().append(left)->append(u", "_j)
		->append(top)
		->append(u", "_j)
		->append(width)
		->append(u", "_j)
		->append(height)
		->append((alignmentLeft != 0 || alignmentTop != 0 ? ::java::lang::StringBuilder().append(u" +A("_j)->append(alignmentLeft)
			->append(u", "_j)
			->append(alignmentTop)
			->append(u")"_j)->toString() : u""_j))
		->append((contentAlignmentLeft != 0 || contentAlignmentTop != 0 ? ::java::lang::StringBuilder().append(u" +CA("_j)->append(contentAlignmentLeft)
			->append(u", "_j)
			->append(contentAlignmentTop)
			->append(u")"_j)->toString() : u""_j))->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUINode_ComputedConstraints::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUINode.ComputedConstraints", 42);
    return c;
}

java::lang::Class* GUINode_ComputedConstraints::getClass0()
{
	return class_();
}

