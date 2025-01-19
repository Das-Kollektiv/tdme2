#pragma once

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>

/**
 * GUI node alignments
 * @author Andreas Drewke
 */
struct agui::gui::nodes::GUINode_Alignments
{
	GUINode_AlignmentHorizontal* horizontal { nullptr };
	GUINode_AlignmentVertical* vertical { nullptr };
};
