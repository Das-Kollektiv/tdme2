#pragma once

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>

/**
 * GUI node computed constraints
 * @author Andreas Drewke
 */
struct agui::gui::nodes::GUINode_ComputedConstraints
{
	int left { 0 };
	int top { 0 };
	int width { 0 };
	int height { 0 };
	int alignmentLeft { 0 };
	int alignmentTop { 0 };
	int contentAlignmentLeft { 0 };
	int contentAlignmentTop { 0 };
	int additionalAlignmentLeft { 0 };
	int additionalAlignmentTop { 0 };
};
