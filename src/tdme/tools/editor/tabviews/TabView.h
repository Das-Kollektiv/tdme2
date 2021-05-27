#pragma once

#include <tdme/tools/editor/tabviews/fwd-tdme.h>

#include <vector>

#include <tdme/engine/fwd-tdme.h>
#include <tdme/gui/events/GUIInputEventHandler.h>
#include <tdme/utilities/MutableString.h>

using std::vector;

using tdme::engine::Engine;
using tdme::gui::events::GUIInputEventHandler;
using tdme::utilities::MutableString;

/**
 * Tab view interface
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::tools::editor::tabviews::TabView: public GUIInputEventHandler
{
	struct OutlinerState {
		vector<string> expandedOutlinerParentOptionValues;
		MutableString value;
		float renderOffsetX { 0.0f };
		float renderOffsetY { 0.0f };
	};

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
	 * @return engine
	 */
	virtual Engine* getEngine() = 0;

	/**
	 * Activate
	 */
	virtual void activate() = 0;

	/**
	 * Deactivate
	 */
	virtual void deactivate() = 0;

	/**
	 * Update rendering
	 */
	virtual void updateRendering() = 0;

	/**
	 * Reload outliner
	 * @param newSelectionValue new selection value
	 *
	 */
	virtual void reloadOutliner() = 0;

	/**
	 * Destructor
	 */
	virtual ~TabView() {}

};
