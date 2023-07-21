#pragma once

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIContextMenuRequestListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/utilities/MutableString.h>

using std::array;
using std::string;

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIContextMenuRequestListener;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeScriptSubController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::DecalEditorTabView;
using tdme::utilities::MutableString;

/**
 * Decal editor tab controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabcontrollers::DecalEditorTabController final
	: public TabController
{

private:
	BasePropertiesSubController* basePropertiesSubController { nullptr };
	PrototypePhysicsSubController* prototypePhysicsSubController { nullptr };
	PrototypeDisplaySubController* prototypeDisplaySubController { nullptr };
	PrototypeScriptSubController* prototypeScriptSubController { nullptr };
	DecalEditorTabView* view { nullptr };
	GUIScreenNode* screenNode { nullptr };
	PopUps* popUps { nullptr };

	array<string, 3> applyDecalNodes {
		"decal_texture_horizontal_sprites",
		"decal_texture_vertical_sprites",
		"decal_texture_fps",
	};

public:
	/**
	 * Public constructor
	 * @param view view
	 */
	DecalEditorTabController(DecalEditorTabView* view);

	/**
	 * Destructor
	 */
	virtual ~DecalEditorTabController();

	/**
	 * Get view
	 */
	DecalEditorTabView* getView();

	// overridden method
	GUIScreenNode* getScreenNode() override;

	/**
	 * @return prototype display sub screen controller
	 */
	inline PrototypeDisplaySubController* getPrototypeDisplaySubController() {
		return prototypeDisplaySubController;
	}

	/**
	 * @return prototype physics sub screen controller
	 */
	inline PrototypePhysicsSubController* getPrototypePhysicsSubController() {
		return prototypePhysicsSubController;
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
	 * Set decal texture
	 * @param fileName file name
	 */
	void setDecalTexture(const string& fileName);

	/**
	 * Set outliner content
	 */
	void setOutlinerContent();

	/**
	 * Set outliner add drop down content
	 */
	void setOutlinerAddDropDownContent();

	/**
	 * Set decal details
	 */
	void setDecalDetails();

	/**
	 * Update details panel
	 * @param outlinerNode outliner node
	 */
	void updateDetails(const string& outlinerNode);

	/**
	 * Apply decal details
	 */
	void applyDecalDetails();

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
