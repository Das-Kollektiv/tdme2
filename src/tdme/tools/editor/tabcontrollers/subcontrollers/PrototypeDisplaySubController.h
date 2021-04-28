#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/MutableString.h>

using tdme::engine::Engine;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::utilities::MutableString;

/**
 * Prototype display sub screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController final
{
private:
	GUIScreenNode* screenNode { nullptr };
	PrototypeDisplaySubView* view { nullptr };
	PrototypePhysicsSubView* physicsView { nullptr };

public:
	/**
	 * Public constructor
	 * @param engine engine
	 * @param physicsView physics view
	 */
	PrototypeDisplaySubController(Engine* engine, PrototypePhysicsSubView* physicsView);

	/**
	 * Destructor
	 */
	~PrototypeDisplaySubController();

	/**
	 * @return view
	 */
	PrototypeDisplaySubView* getView();

	/**
	 * Init
	 * @param screenNode screen node
	 */
	void initialize(GUIScreenNode* screenNode);

	/**
	 * Set up display section
	 */
	void setupDisplay();

	/**
	 * On display apply button event
	 */
	void onDisplayApply();

	/**
	 * @return display shadowing checked
	 */
	bool getDisplayShadowing();

	/**
	 * @return display ground checked
	 */
	bool getDisplayGround();

	/**
	 * @return display bounding volume checked
	 */
	bool getDisplayBoundingVolume();
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node);

};
