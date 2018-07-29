#pragma once

#include <tdme/tools/shared/files/fwd-tdme.h>

/**
 * Progress Callback
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::tools::shared::files::ProgressCallback
{
	/**
	 * Perform action
	 */
	virtual void progress(float value) = 0;

	/**
	 * Destructor
	 */
	virtual ~ProgressCallback() {}
};
