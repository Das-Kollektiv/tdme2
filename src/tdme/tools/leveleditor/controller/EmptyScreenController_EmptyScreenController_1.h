
#pragma once

#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::events::Action;
using tdme::tools::leveleditor::controller::EmptyScreenController;
using tdme::tools::leveleditor::views::EmptyView;

class tdme::tools::leveleditor::controller::EmptyScreenController_EmptyScreenController_1
	: public virtual Action
{
	friend class EmptyScreenController;

public:
	void performAction() override;

	/**
	 * Public constructor
	 * @param *emptyScreenController empty screen controller
	 * @param finalView final view
	 */
	EmptyScreenController_EmptyScreenController_1(EmptyScreenController *emptyScreenController, EmptyView* finalView);

private:
	EmptyScreenController* emptyScreenController;
	EmptyView* finalView;
};
