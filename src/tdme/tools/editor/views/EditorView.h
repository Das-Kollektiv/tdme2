#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/gui/events/GUIInputEventHandler.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/tools/editor/views/View.h>

using tdme::engine::Engine;
using tdme::gui::events::GUIInputEventHandler;
using tdme::math::Vector3;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::views::View;

/**
 * Editor View
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::views::EditorView final
	: public View
	, public GUIInputEventHandler
{
private:
	Engine* engine { nullptr };
	PopUps* popUps { nullptr };
	EditorScreenController* editorScreenController { nullptr };

public:
	/**
	 * Public constructor
	 * @param popUps pop ups view
	 */
	EditorView(PopUps* popUps);

	/**
	 * Destructor
	 */
	~EditorView();

	/**
	 * @return pop ups
	 */
	PopUps* getPopUps();

	/**
	 * @return screen controller
	 */
	EditorScreenController* getScreenController() {
		return editorScreenController;
	}

	/**
	 * Init GUI elements
	 */
	void updateGUIElements();

	// overridden methods
	void handleInputEvents() override;
	void display() override;
	void initialize() override;
	void activate() override;
	void deactivate() override;
	void dispose() override;

};
