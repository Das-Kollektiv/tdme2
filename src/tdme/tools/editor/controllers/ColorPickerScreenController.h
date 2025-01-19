#pragma once

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unique_ptr;

using tdme::engine::Color4;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::ScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Action;

/**
 * Color picker screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::controllers::ColorPickerScreenController final
	: public ScreenController
	, public virtual GUIActionListener
	, public virtual GUIChangeListener
	, public virtual GUIFocusListener
	, public virtual GUITooltipRequestListener
{

private:
	PopUps* popUps { nullptr };
	GUIScreenNode* screenNode { nullptr };
	GUIElementNode* redInput { nullptr };
	GUIElementNode* greenInput { nullptr };
	GUIElementNode* blueInput { nullptr };
	GUIElementNode* alphaInput { nullptr };
	GUIElementNode* hexInput { nullptr };
	GUIElementNode* brightnessSlider { nullptr };
	GUIImageNode* colorNew { nullptr };
	GUIImageNode* colorOld { nullptr };
	Color4 initialColor;
	Color4 color;
	unique_ptr<Action> onColorChangeAction;

	/**
	 * Update color
	 */
	void updateColor();

	/**
	 * Update color hex
	 */
	void updateColorHex();

public:
	// forbid class copy
	FORBID_CLASS_COPY(ColorPickerScreenController)

	/**
	 * Public constructor
	 * @param popUps pop ups
	 */
	ColorPickerScreenController(PopUps* popUps);

	/**
	 * Public denstructor
	 */
	virtual ~ColorPickerScreenController();

	// overridden methods
	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;
	#if defined(_WIN32) && defined(_MSC_VER)
		// I do not get it currently, somehow it does not accept override whereas everything works fine
		void onChange(GUIElementNode* node);
		void onAction(GUIActionListenerType type, GUIElementNode* node);
		void onFocus(GUIElementNode* node);
		void onUnfocus(GUIElementNode* node);
		void onTooltipShowRequest(GUINode* node, int mouseX, int mouseY);
		void onTooltipCloseRequest();
	#else
		void onChange(GUIElementNode* node) override;
		void onAction(GUIActionListenerType type, GUIElementNode* node) override;
		void onFocus(GUIElementNode* node) override;
		void onUnfocus(GUIElementNode* node) override;
		void onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) override;
		void onTooltipCloseRequest() override;
	#endif

	/**
	 * Shows the pop up
	 * @param color color
	 * @param onColorChangeAction on color change action
	 */
	void show(const Color4& color, Action* onColorChangeAction);

	/**
	 * Closes the pop up
	 */
	void close();

	/**
	 * Set color
	 * @param color color
	 */
	void setColor(const Color4& color);

	/**
	 * @returns color
	 */
	inline Color4 getColor() {
		return color;
	}

};
