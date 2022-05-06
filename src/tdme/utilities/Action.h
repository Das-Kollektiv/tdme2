#pragma once

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>

/**
 * Action Interface
 * @author Andreas Drewke
 */
struct tdme::utilities::Action
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
