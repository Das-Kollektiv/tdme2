#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>

#include <tdme/tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;

using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITextNode;

using tdme::tools::editor::controllers::ScreenController;

/**
 * Tooltip screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::controllers::TooltipScreenController final
	: public ScreenController
{

private:
	GUIScreenNode* screenNode { nullptr };
	GUITextNode* tooltipNode { nullptr };

public:
	// forbid class copy
	FORBID_CLASS_COPY(TooltipScreenController)

	/**
	 * Public constructor
	 */
	TooltipScreenController();

	/**
	 * Destructor
	 */
	virtual ~TooltipScreenController();

	// overridden methods
	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;

	/**
	 * Show tooltip
	 * @param mouseX mouse X
	 * @param mouseY mouse Y
	 * @param tooltip tooltip
	 */
	void show(int mouseX, int mouseY, const string& tooltip);

	/**
	 * Closes the tool tip
	 */
	void close();

};
