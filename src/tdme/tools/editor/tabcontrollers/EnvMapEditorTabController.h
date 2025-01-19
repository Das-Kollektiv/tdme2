#pragma once

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIChangeListener.h>
#include <agui/gui/events/GUIContextMenuRequestListener.h>
#include <agui/gui/events/GUIFocusListener.h>
#include <agui/gui/events/GUITooltipRequestListener.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <agui/utilities/fwd-agui.h>

using std::array;
using std::string;

using agui::gui::events::GUIActionListener;
using agui::gui::events::GUIActionListenerType;
using agui::gui::events::GUIChangeListener;
using agui::gui::events::GUIContextMenuRequestListener;
using agui::gui::events::GUIFocusListener;
using agui::gui::events::GUITooltipRequestListener;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITextNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::EnvMapEditorTabView;
using agui::utilities::MutableString;

/**
 * Environ map editor screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabcontrollers::EnvMapEditorTabController final
	: public TabController
{

private:
	EnvMapEditorTabView* view { nullptr };
	GUIScreenNode* screenNode { nullptr };
	PopUps* popUps { nullptr };

	array<string, 7> applyNodesRenderPasses {
		"rendersettings_renderpass_standard",
		"rendersettings_renderpass_sky",
		"rendersettings_renderpass_terrain",
		"rendersettings_renderpass_water",
		"rendersettings_renderpass_postprocessing",
		"rendersettings_frequency",
		"rendersettings_frequency_value"
	};

	array<string, 3> applyNodesLocation {
		"location_translation_x",
		"location_translation_y",
		"location_translation_z"
	};

public:
	// forbid class copy
	FORBID_CLASS_COPY(EnvMapEditorTabController)

	/**
	 * Public constructor
	 * @param view view
	 */
	EnvMapEditorTabController(EnvMapEditorTabView* view);

	/**
	 * Destructor
	 */
	virtual ~EnvMapEditorTabController();

	/**
	 * Get view
	 * @returns view
	 */
	inline EnvMapEditorTabView* getView() {
		return view;
	}

	// overridden method
	inline GUIScreenNode* getScreenNode() override {
		return screenNode;
	}

	// overridden methods
	void initialize(GUIScreenNode* screenNode) override;
	void dispose() override;
	void onChange(GUIElementNode* node) override;
	void onAction(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;
	void onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) override;
	void onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) override;
	void onTooltipCloseRequest() override;
	void onCommand(TabControllerCommand command) override;
	void onDrop(const string& payload, int mouseX, int mouseY) override;

	/**
	 * Apply render passes
	 */
	void applyRenderPasses();

	/**
	 * Apply location
	 */
	void applyLocation();

	/**
	 * Set outliner content
	 */
	void setOutlinerContent();

	/**
	 * Set outliner add drop down content
	 */
	void setOutlinerAddDropDownContent();

	/**
	 * Update details panel
	 * @param outlinerNode outliner node
	 */
	void updateDetails(const string& outlinerNode);

	/**
	 * Update info text line
	 * @param text text
	 */
	void updateInfoText(const MutableString& text);

	/**
	 * Show the information pop up / modal
	 * @param caption caption
	 * @param message message
	 */
	void showInfoPopUp(const string& caption, const string& message);

};
