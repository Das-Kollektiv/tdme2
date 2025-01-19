#pragma once

#include <tdme/tdme.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>

#include <string>
#include <vector>

#include <tdme/engine/fwd-tdme.h>
#include <tdme/gui/events/GUIInputEventHandler.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/utilities/MutableString.h>

using std::string;
using std::vector;

using tdme::engine::Engine;
using tdme::gui::events::GUIInputEventHandler;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::utilities::MutableString;

/**
 * Tab view interface
 * @author Andreas Drewke
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
	 * @returns tab id
	 */
	virtual const string& getTabId() = 0;

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
	 * Activate
	 */
	virtual void activate() = 0;

	/**
	 * Deactivate
	 */
	virtual void deactivate() = 0;

	/**
	 * @returns engine
	 */
	virtual Engine* getEngine() = 0;

	/**
	 * @returns associated tab controller
	 */
	virtual TabController* getTabController() = 0;

	/**
	 * Update rendering
	 * @deprecated This should be removed
	 */
	virtual void updateRendering() = 0;

	/**
	 * Reload outliner
	 * @param newSelectionValue new selection value
	 *
	 */
	virtual void reloadOutliner() = 0;

	/**
	 * If this viewport framebuffer has a fixed size
	 */
	virtual bool hasFixedSize() = 0;

	/**
	 * Destructor
	 */
	virtual ~TabView() {}

};
