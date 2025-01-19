#pragma once

#include <array>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <agui/utilities/fwd-agui.h>

using std::array;
using std::map;
using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

using tdme::engine::prototype::Prototype;
using agui::gui::events::GUIActionListenerType;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIScreenNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabviews::subviews::PrototypeScriptSubView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using agui::utilities::MutableString;

/**
 * Script sub screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeScriptSubController final
{
private:
	EditorView* editorView { nullptr };
	unique_ptr<PrototypeScriptSubView> view;
	PopUps* popUps { nullptr };
	GUIScreenNode* screenNode { nullptr };

public:
	// forbid class copy
	FORBID_CLASS_COPY(PrototypeScriptSubController)

	/**
	 * Public constructor
	 * @param editorView editor view
	 */
	PrototypeScriptSubController(EditorView* editorView);

	/**
	 * Destructor
	 */
	~PrototypeScriptSubController();

	/**
	 * Initialize
	 * @param screenNode screen node
	 */
	void initialize(GUIScreenNode* screenNode);

	/**
	 * Create prototype script XML for outliner
	 * @param prototype prototype
	 * @param xml xml
	 */
	void createScriptXML(Prototype* prototype, string& xml);

	/**
	 * Set script details
	 * @param prototype prototype
	 */
	void setScriptDetails(Prototype* prototype);

	/**
	 * Update script details
	 * @param prototype prototype
	 */
	void updateScriptDetails(Prototype* prototype);

	/**
	 * Update details panel
	 * @param prototype prototype
	 * @param outlinerNode outliner node
	 */
	void updateDetails(Prototype* prototype, const string& outlinerNode);

	/**
	 * On value changed
	 * @param node node
	 * @param prototype prototype
	 * @returns if this event has been handled
	 */
	bool onChange(GUIElementNode* node, Prototype* prototype);

	/**
	 * On action performed
	 * @param type type
	 * @param node node
	 * @param prototype prototype
	 * @returns if this event has been handled
	 */
	bool onAction(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype);

	/**
	 * On script set
	 * @param prototype prototype
	 */
	void onScriptSet(Prototype* prototype);

	/**
	 * On script unset
	 * @param prototype prototype
	 */
	void onScriptUnset(Prototype* prototype);

	/**
	 * On script browse to
	 * @param prototype prototype
	 */
	void onScriptBrowseTo(Prototype* prototype);

	/**
	 * Show the information pop up / modal
	 * @param caption caption
	 * @param message message
	 */
	void showInfoPopUp(const string& caption, const string& message);

	/**
	 * Set script
	 * @param fileName file name
	 * @param prototype prototype
	 */
	void setScript(const string& fileName, Prototype* prototype);

	/**
	 * On drop
	 * @param payload payload
	 * @param mouseX mouse X
	 * @param mouseY mouse Y
	 * @param prototype prototype
	 */
	bool onDrop(const string& payload, int mouseX, int mouseY, Prototype* prototype);

};
