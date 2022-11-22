#pragma once

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::array;
using std::string;

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::EnvMapEditorTabView;
using tdme::utilities::MutableString;

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
	 */
	EnvMapEditorTabView* getView();

	// overridden method
	GUIScreenNode* getScreenNode() override;

	// overridden methods
	void initialize(GUIScreenNode* screenNode) override;
	void dispose() override;
	void onValueChanged(GUIElementNode* node) override;
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;
	void onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) override;
	void executeCommand(TabControllerCommand command) override;

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
	 * Shows the error pop up
	 * @param caption caption
	 * @param message message
	 */
	void showErrorPopUp(const string& caption, const string& message);

};
