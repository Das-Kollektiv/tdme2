#pragma once

#include <agui/agui.h>
#include <agui/gui/effects/fwd-agui.h>
#include <agui/gui/nodes/GUIColor.h>

// namespaces
namespace agui {
namespace gui {
namespace effects {
	using ::agui::gui::nodes::GUIColor;
}
}
}

/**
 * GUI effect state
 * @author Andreas Drewke
 */
struct agui::gui::effects::GUIEffectState
{
	float positionX { 0.0f };
	float positionY { 0.0f };
	GUIColor colorAdd { 0.0f, 0.0f, 0.0f, 0.0f };
	GUIColor colorMul { 1.0f, 1.0f, 1.0f, 1.0f };
};
