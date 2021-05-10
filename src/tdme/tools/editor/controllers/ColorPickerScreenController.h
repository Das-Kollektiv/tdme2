#pragma once

#include <string>

#include <tdme/engine/model/Color4Base.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;

using tdme::engine::model::Color4Base;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIMultilineTextNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::editor::controllers::ScreenController;
using tdme::utilities::MutableString;

/**
 * Color picker screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::controllers::ColorPickerScreenController final
	: public ScreenController
	, public virtual GUIActionListener
	, public virtual GUIChangeListener
	, public virtual GUIFocusListener
{

private:
	GUIScreenNode* screenNode { nullptr };
	GUIElementNode* redInput { nullptr };
	GUIElementNode* greenInput { nullptr };
	GUIElementNode* blueInput { nullptr };
	GUIElementNode* alphaInput { nullptr };
	GUIElementNode* hexInput { nullptr };
	GUIElementNode* brightnessSlider { nullptr };
	Color4Base initialColor;
	Color4Base color;

	/**
	 * Update color
	 */
	void updateColor();

	/**
	 * Update color hex
	 */
	void updateColorHex();

public:
	/**
	 * Public constructor
	 */
	ColorPickerScreenController();

	// overriden methods
	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;
	void onValueChanged(GUIElementNode* node) override;
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;

	/**
	 * Shows the pop up
	 * @param color color
	 */
	void show(const Color4Base& color);

	/**
	 * Closes the pop up
	 */
	void close();

};
