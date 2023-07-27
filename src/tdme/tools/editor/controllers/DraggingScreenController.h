#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/GUIMoveListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;

using tdme::gui::events::GUIMoveListener;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
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

	Action* onReleaseAction { nullptr };

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
	 * @return current payload
	 */
	inline const string& getPayload() {
		return payload;
	}

	/**
	 * @return unscaled drag release mouse X position
	 */
	inline int getDragReleaseMouseX() {
		return dragReleaseMouseX;
	}

	/**
	 * @return unscaled drag release mouse Y position
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
