#pragma once

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>

/**
 * GUI node requested constraints entity
 * @author Andreas Drewke
 */
struct agui::gui::nodes::GUINode_RequestedConstraints
{
	GUINode_RequestedConstraints_RequestedConstraintsType* leftType { nullptr };
	int left { 0 };
	GUINode_RequestedConstraints_RequestedConstraintsType* topType { nullptr };
	int top { 0 };
	GUINode_RequestedConstraints_RequestedConstraintsType* widthType { nullptr };
	int width { 0 };
	GUINode_RequestedConstraints_RequestedConstraintsType* heightType { nullptr };
	int height { 0 };
};
