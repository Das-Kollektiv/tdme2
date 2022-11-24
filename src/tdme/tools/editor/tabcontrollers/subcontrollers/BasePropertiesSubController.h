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
using tdme::engine::prototype::Prototype;
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
		"base_name",
		"base_description"
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
	 * @param baseProperties base properties
	 * @param prototype prototype or nullptr
	 */
	void setBasePropertiesDetails(BaseProperties* baseProperties, Prototype* prototype = nullptr);

	/**
	 * Apply property base details
	 * @param baseProperties base properties
	 */
	void applyPropertyDetails(BaseProperties* baseProperties);

	/**
	 * Set property details
	 * @param baseProperties base properties
	 * @param propertyName property name
	 */
	void setPropertyDetails(BaseProperties* baseProperties, const string& propertyName);

	/**
	 * Update details panel
	 * @param baseProperties base properties
	 * @param outlinerNode outliner node
	 * @param prototype prototype or nullptr
	 */
	void updateDetails(BaseProperties* baseProperties, const string& outlinerNode, Prototype* prototype = nullptr);

	/**
	 * Apply property details
	 * @param baseProperties base properties
	 * @param propertyName property name
	 */
	void applyPropertyDetails(BaseProperties* baseProperties, const string& propertyName);

	/**
	 * Create property
	 * @param baseProperties base properties
	 */
	void createProperty(BaseProperties* baseProperties);

	/**
	 * Start rename property
	 * @param baseProperties base properties
	 * @param propertyName property name
	 */
	void startRenameProperty(BaseProperties* baseProperties, const string& propertyName);

	/**
	 * Rename property
	 * @param baseProperties base properties
	 */
	void renameProperty(BaseProperties* baseProperties);

	/**
	 * On value changed
	 * @param node node
	 * @param baseProperties base properties
	 * @param prototype prototype or nullptr
	 */
	void onChange(GUIElementNode* node, BaseProperties* baseProperties, Prototype* prototype = nullptr);

	/**
	 * On action performed
	 * @param type type
	 * @param node node
	 * @param baseProperties base properties
	 */
	void onAction(GUIActionListenerType type, GUIElementNode* node, BaseProperties* baseProperties);

	/**
	 * On focus
	 * @param node node
	 * @param baseProperties base properties
	 */
	void onFocus(GUIElementNode* node, BaseProperties* baseProperties);

	/**
	 * On unfocus
	 * @param node node
	 * @param baseProperties base properties
	 */
	void onUnfocus(GUIElementNode* node, BaseProperties* baseProperties);

	/**
	 * On context menu requested
	 * @param node node
	 * @param mouseX unscaled mouse X position
	 * @param mouseY unscaled mouse Y position
	 * @param baseProperties base properties
	 */
	void onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY, BaseProperties* baseProperties);

	/**
	 * Apply property value
	 * @param baseProperties base properties
	 */
	void applyPropertyValue(BaseProperties* baseProperties);

	/**
	 * Shows the error pop up
	 * @param caption caption
	 * @param message message
	 */
	void showInfoPopUp(const string& caption, const string& message);

};
