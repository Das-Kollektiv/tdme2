#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::array;
using std::map;
using std::string;
using std::vector;

using tdme::engine::prototype::Prototype;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabviews::subviews::PrototypeScriptSubView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::MutableString;

/**
 * Script sub screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeScriptSubController final
{
private:
	EditorView* editorView { nullptr };
	PrototypeScriptSubView* view { nullptr };
	PopUps* popUps { nullptr };
	GUIScreenNode* screenNode { nullptr };

public:
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
	 */
	void onChange(GUIElementNode* node, Prototype* prototype);

	/**
	 * On action performed
	 * @param type type
	 * @param node node
	 * @param prototype prototype
	 */
	void onAction(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype);

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
	 * Shows the error pop up
	 * @param caption caption
	 * @param message message
	 */
	void showErrorPopUp(const string& caption, const string& message);

};
