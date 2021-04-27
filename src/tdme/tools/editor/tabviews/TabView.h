#pragma once

#include <tdme/tools/editor/tabviews/fwd-tdme.h>

#include <tdme/engine/fwd-tdme.h>

using tdme::engine::FrameBuffer;

/**
 * Tab view interface
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::tools::editor::tabviews::TabView
{

	/**
	 * Initiates the view
	 */
	virtual void initialize() = 0;

	/**
	 * Renders the view
	 */
	virtual void display() = 0;

	/**
	 * Disposes the view
	 */
	virtual void dispose() = 0;

	/**
	 * @return frame buffer
	 */
	virtual FrameBuffer* getFrameBuffer();

	/**
	 * Destructor
	 */
	virtual ~TabView() {}

	virtual void activate() = 0;
	virtual void deactivate() = 0;

};
