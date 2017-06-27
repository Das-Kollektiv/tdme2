// Generated from /tdme/src/tdme/gui/nodes/GUINode.java
#include <tdme/gui/nodes/GUINode_Alignments.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/nodes/GUINode_AlignmentHorizontal.h>
#include <tdme/gui/nodes/GUINode_AlignmentVertical.h>

using tdme::gui::nodes::GUINode_Alignments;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;

GUINode_Alignments::GUINode_Alignments(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUINode_Alignments::GUINode_Alignments()
	: GUINode_Alignments(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUINode_Alignments::toString()
{
	return ::java::lang::StringBuilder().append(horizontal->toString()->toLowerCase())->append(u", "_j)
		->append(vertical->toString()->toLowerCase())->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUINode_Alignments::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUINode.Alignments", 33);
    return c;
}

java::lang::Class* GUINode_Alignments::getClass0()
{
	return class_();
}

