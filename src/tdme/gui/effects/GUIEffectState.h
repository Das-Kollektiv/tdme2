#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/effects/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>

using tdme::gui::nodes::GUIColor;

/**
 * GUI effect state
 * @author Andreas Drewke
 */
struct tdme::gui::effects::GUIEffectState
{
	float positionX { 0.0f };
	float positionY { 0.0f };
	GUIColor colorAdd { 0.0f, 0.0f, 0.0f, 0.0f };
	GUIColor colorMul { 1.0f, 1.0f, 1.0f, 1.0f };
};
