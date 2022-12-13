#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/gui/events/GUIInputEventHandler.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/tools/editor/views/View.h>

using tdme::engine::Engine;
using tdme::gui::events::GUIInputEventHandler;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::math::Vector3;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::views::View;

/**
 * Editor View
 * @author Andreas Drewke
 */
class tdme::tools::editor::views::EditorView final
	: public View
	, public GUIInputEventHandler
{
private:
	Engine* engine { nullptr };
	PopUps* popUps { nullptr };
	EditorScreenController* editorScreenController { nullptr };
	string lastSelectedTabId;
	array<bool, 8> mouseButtonsDown = { false, false, false, false, false, false, false, false };

public:
	/**
	 * Public constructor
	 * @param popUps pop ups view
	 */
	EditorView(PopUps* popUps);

	/**
	 * Destructor
	 */
	~EditorView();

	/**
	 * @return pop ups
	 */
	PopUps* getPopUps();

	/**
	 * @return screen controller
	 */
	EditorScreenController* getScreenController() {
		return editorScreenController;
	}

	/**
	 * Init GUI elements
	 */
	void updateGUIElements();

	// overridden methods
	void handleInputEvents() override;
	void display() override;
	void initialize() override;
	void activate() override;
	void deactivate() override;
	void dispose() override;
	void tick() override;

	/**
	 * Set outliner content
	 * @param xml xml
	 */
	void setOutlinerContent(const string& xml);

	/**
	 * Set outliner add drop down content
	 * @param xml xml
	 */
	void setOutlinerAddDropDownContent(const string& xml);

	/**
	 * Set details content
	 * @param xml xml
	 */
	void setDetailsContent(const string& xml);

	/**
	 * Reload tab outliner
	 * @param newSelectionValue new selection value
	 */
	void reloadTabOutliner(const string& newSelectionValue = string());

	/**
	 * Determine current tab viewport screen constraints
	 * @param left left
	 * @param top top
	 * @param width width
	 * @param height height
	 * @param offsetX offset X
	 * @param offsetY offset Y
	 * @return success
	 */
	bool getCurrentTabViewPort(int& left, int& top, int& width, int& height, int& offsetX, int& offsetY);

	/**
	 * Determine viewport screen constraints
	 * @param viewPortNode view port node
	 * @param left left
	 * @param top top
	 * @param width width
	 * @param height height
	 * @param offsetX offset X
	 * @param offsetY offset Y
	 */
	void getViewPort(GUINode* viewPortNode, int& left, int& top, int& width, int& height, int& offsetX, int& offsetY);

	/**
	 * Determine current tab tooltip position
	 * @param screenNode screen node
	 * @param mouseX mouse x
	 * @param mouseY mouse Y
	 * @param tooltipLeft tooltip left
	 * @param tooltipTop tooltip top
	 * @return success
	 */
	bool getCurrentTabTooltipPosition(GUIScreenNode* screenNode, int mouseX, int mouseY, int& tooltipLeft, int& tooltipTop);

};
