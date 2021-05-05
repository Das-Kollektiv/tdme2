#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>

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
using tdme::engine::prototype::PrototypeProperty;
using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabviews::subviews::PrototypeBaseSubView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::MutableString;

/**
 * Prototype base sub screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeBaseSubController final
{
private:
	EditorView* editorView { nullptr };
	PrototypeBaseSubView* view { nullptr };
	PopUps* popUps { nullptr };
	GUIScreenNode* screenNode { nullptr };
	Action* onSetPrototypeDataAction { nullptr };

	array<string, 2> applyPropertyNodes = {
		"property_name",
		"property_value"
	};
	string propertyName;

public:
	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param popUps view
	 * @param onSetEntityDataAction on set entity data action
	 */
	PrototypeBaseSubController(EditorView* editorView, PopUps* popUps, Action* onSetEntityDataAction);

	/**
	 * Destructor
	 */
	~PrototypeBaseSubController();

	/**
	 * Init
	 * @param screenNode screen node
	 */
	void initialize(GUIScreenNode* screenNode);

	/**
	 * Set up general prototype data
	 * @param name name
	 * @param description description
	 */
	void setPrototypeData(const string& name, const string& description);

	/**
	 * Unset entity data
	 */
	void unsetPrototypeData();

	/**
	 * On prototype data apply
	 * @param model model
	 */
	void onPrototypeDataApply(Prototype* model);

	/**
	 * Create prototype properties XML for outliner
	 * @param prototype prototype
	 * @param xml xml
	 */
	void createPrototypePropertiesXML(Prototype* prototype, string& xml);

	/**
	 * Set property details
	 * @param prototype prototype
	 * @param propertyName property name
	 */
	void setPropertyDetails(Prototype* prototype, const string& propertyName);

	/**
	 * Apply property details
	 * @param prototype prototype
	 * @param propertyName property name
	 */
	void applyPropertyDetails(Prototype* prototype, const string& propertyName);

	/**
	 * On value changed
	 * @param node node
	 * @param prototype prototype
	 */
	void onValueChanged(GUIElementNode* node, Prototype* prototype);

	/**
	 * On action performed
	 * @param type type
	 * @param node node
	 * @param prototype prototype
	 */
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype);

	/**
	 * On focus
	 * @param node node
	 * @param prototype prototype
	 */
	void onFocus(GUIElementNode* node, Prototype* prototype);

	/**
	 * On unfocus
	 * @param node node
	 * @param prototype prototype
	 */
	void onUnfocus(GUIElementNode* node, Prototype* prototype);

	/**
	 * Shows the error pop up
	 * @param caption caption
	 * @param message message
	 */
	void showErrorPopUp(const string& caption, const string& message);

};
