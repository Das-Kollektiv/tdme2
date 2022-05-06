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

using tdme::engine::prototype::BaseProperties;
using tdme::engine::prototype::BaseProperty;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabviews::subviews::BasePropertiesSubView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::MutableString;

/**
 * Prototype base sub screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController final
{
private:
	EditorView* editorView { nullptr };
	BasePropertiesSubView* view { nullptr };
	PopUps* popUps { nullptr };
	GUIScreenNode* screenNode { nullptr };
	string rootNodeId;

	array<string, 1> applyPropertyNodes = {
		"property_value"
	};

	array<string, 2> applyBaseNodes = {
		"prototype_name",
		"prototype_description"
	};

	string renamePropertyName;

public:
	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param rootNode root node
	 */
	BasePropertiesSubController(EditorView* editorView, const string& rootNode);

	/**
	 * Destructor
	 */
	~BasePropertiesSubController();

	/**
	 * Init
	 * @param screenNode screen node
	 */
	void initialize(GUIScreenNode* screenNode);

	/**
	 * Create base properties XML for outliner
	 * @param baseProperties base properties
	 * @param xml xml
	 */
	void createBasePropertiesXML(BaseProperties* baseProperties, string& xml);

	/**
	 * Set property base details
	 * @param prototype prototype
	 */
	void setBasePropertiesDetails(BaseProperties* baseProperties);

	/**
	 * Apply property base details
	 * @param prototype prototype
	 */
	void applyPropertyDetails(BaseProperties* baseProperties);

	/**
	 * Set property details
	 * @param prototype prototype
	 * @param propertyName property name
	 */
	void setPropertyDetails(BaseProperties* baseProperties, const string& propertyName);

	/**
	 * Update details panel
	 * @param prototype prototype
	 * @param outlinerNode outliner node
	 */
	void updateDetails(BaseProperties* baseProperties, const string& outlinerNode);

	/**
	 * Apply property details
	 * @param prototype prototype
	 * @param propertyName property name
	 */
	void applyPropertyDetails(BaseProperties* baseProperties, const string& propertyName);

	/**
	 * Create property
	 * @param prototype prototype
	 */
	void createProperty(BaseProperties* baseProperties);

	/**
	 * Start rename property
	 * @param property property
	 * @param propertyName property name
	 */
	void startRenameProperty(BaseProperties* baseProperties, const string& propertyName);

	/**
	 * Rename property
	 * @param prototype prototype
	 */
	void renameProperty(BaseProperties* baseProperties);

	/**
	 * On value changed
	 * @param node node
	 * @param prototype prototype
	 */
	void onValueChanged(GUIElementNode* node, BaseProperties* baseProperties);

	/**
	 * On action performed
	 * @param type type
	 * @param node node
	 * @param prototype prototype
	 */
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node, BaseProperties* baseProperties);

	/**
	 * On focus
	 * @param node node
	 * @param prototype prototype
	 */
	void onFocus(GUIElementNode* node, BaseProperties* baseProperties);

	/**
	 * On unfocus
	 * @param node node
	 * @param prototype prototype
	 */
	void onUnfocus(GUIElementNode* node, BaseProperties* baseProperties);

	/**
	 * On context menu requested
	 * @param node node
	 * @param mouseX unscaled mouse X position
	 * @param mouseY unscaled mouse Y position
	 * @param prototype prototype
	 */
	void onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY, BaseProperties* baseProperties);

	/**
	 * Apply property value
	 * @param prototype prototype
	 */
	void applyPropertyValue(BaseProperties* baseProperties);

	/**
	 * Shows the error pop up
	 * @param caption caption
	 * @param message message
	 */
	void showErrorPopUp(const string& caption, const string& message);

};
