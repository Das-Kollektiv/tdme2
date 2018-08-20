
#pragma once

#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::events::Action;
using tdme::tools::leveleditor::controller::TriggerScreenController;
using tdme::tools::leveleditor::views::TriggerView;

class tdme::tools::leveleditor::controller::TriggerScreenController_TriggerScreenController_1
	: public virtual Action
{
	friend class TriggerScreenController;

public:
	void performAction() override;

	/**
	 * Public constructor
	 * @param triggerScreenController trigger screen controller
	 * @param finalView final view
	 */
	TriggerScreenController_TriggerScreenController_1(TriggerScreenController* triggerScreenController, TriggerView* finalView);

private:
	TriggerScreenController *triggerScreenController;
	TriggerView* finalView;

};
