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

public:
	/**
	 * Public constructor
	 */
	DraggingScreenController();

	/**
	 * Destructor
	 */
	virtual ~DraggingScreenController();

	// overridden methods
	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;
	void onMove(GUINode* node) override;
	void onRelease(GUINode* node, int mouseX, int mouseY) override;

	/**
	 * Show dragging screen and a dragging image from given source
	 * @param mouseX mouse X
	 * @param mouseY mouse Y
	 * @param xml xml
	 */
	void start(int mouseX, int mouseY, const string& xml);

	/**
	 * Close dragging screen
	 */
	void close();

};
