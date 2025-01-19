#pragma once

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <agui/gui/events/GUIMoveListener.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unique_ptr;

using agui::gui::events::GUIMoveListener;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::ScreenController;
using tdme::utilities::Action;

/**
 * Dragging screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::controllers::DraggingScreenController final
	: public ScreenController
	, public GUIMoveListener
{

private:
	GUIScreenNode* screenNode { nullptr };
	GUIParentNode* draggableNode { nullptr };

	string payload;

	int dragReleaseMouseX { -1 };
	int dragReleaseMouseY { -1 };

	unique_ptr<Action> onReleaseAction;

public:
	// forbid class copy
	FORBID_CLASS_COPY(DraggingScreenController)

	/**
	 * Public constructor
	 */
	DraggingScreenController();

	/**
	 * Destructor
	 */
	virtual ~DraggingScreenController();

	/**
	 * @returns current payload
	 */
	inline const string& getPayload() {
		return payload;
	}

	/**
	 * @returns unscaled drag release mouse X position
	 */
	inline int getDragReleaseMouseX() {
		return dragReleaseMouseX;
	}

	/**
	 * @returns unscaled drag release mouse Y position
	 */
	inline int getDragReleaseMouseY() {
		return dragReleaseMouseY;
	}

	// overridden methods
	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;
	bool accept(GUINode* node) override;
	void onMove(GUINode* node) override;
	void onRelease(GUINode* node, int mouseX, int mouseY) override;

	/**
	 * Show dragging screen and a dragging image from given source
	 * @param mouseX mouse X
	 * @param mouseY mouse Y
	 * @param xml xml
	 * @param payload payload
	 * @param onReleaseAction on release action
	 */
	void start(int mouseX, int mouseY, const string& xml, const string& payload, Action* onReleaseAction);

	/**
	 * Close dragging screen
	 */
	void close();

};
