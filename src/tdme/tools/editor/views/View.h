#pragma once

#include <tdme/tdme.h>
#include <tdme/tools/editor/views/fwd-tdme.h>

/**
 * View interface, this combines application logic, regarding a application view, with screen controllers
 * @author Andreas Drewke
 */
struct tdme::tools::editor::views::View
{

	/**
	 * Initiates the view
	 */
	virtual void initialize() = 0;

	/**
	 * Activate view
	 */
	virtual void activate() = 0;

	/**
	 * Renders the view
	 */
	virtual void display() = 0;

	/**
	 * Deactivate view
	 */
	virtual void deactivate() = 0;

	/**
	 * Disposes the view
	 */
	virtual void dispose() = 0;

	/**
	 * Tick
	 */
	virtual void tick() = 0;

	/**
	 * Destructor
	 */
	virtual ~View() {}
};
