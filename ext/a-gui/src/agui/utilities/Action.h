#pragma once

#include <agui/agui.h>
#include <agui/utilities/fwd-agui.h>

/**
 * Action Interface
 * @author Andreas Drewke
 */
struct agui::utilities::Action
{
	/**
	 * Destructor
	 */
	virtual ~Action() {}

	/**
	 * Perform action
	 */
	virtual void performAction() = 0;

};
