#include <tdme/gui/nodes/GUINode_Alignments.h>

#include <tdme/gui/nodes/GUINode_AlignmentHorizontal.h>
#include <tdme/gui/nodes/GUINode_AlignmentVertical.h>

using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;

GUINode_Alignments::GUINode_Alignments(const ::default_init_tag&)
{
}

GUINode_Alignments::GUINode_Alignments()
	: GUINode_Alignments(*static_cast< ::default_init_tag* >(0))
{
}

