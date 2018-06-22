#pragma once

#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/utils/MutableString.h>

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUINode;
using tdme::utils::MutableString;

/** 
 * GUI knob controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUIKnobController final: public GUINodeController
{
	friend class GUIKnob;

public:
	bool isDisabled() override;
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event) override;
	void tick() override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	const MutableString& getValue() override;
	void setValue(const MutableString& value) override;

private:
	GUIKnobController(GUINode* node);

	/**
	 * Update knob
	 */
	void updateKnob();

	GUINode* knobNode { nullptr };
	bool disabled { false };
	float valueFloat { 0.0f };
	MutableString value { };
	int mouseLastX {  };
};
