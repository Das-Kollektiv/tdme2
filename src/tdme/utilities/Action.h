#pragma once

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>

/**
 * Action Interface
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::utilities::Action
{
	/**
	 * Perform action
	 */
	virtual void performAction() = 0;

	/**
	 * Destructor
	 */
	virtual ~Action() {}
};
