#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/MutableString.h>

using std::array;

using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::engine::EntityShaderParameters;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::MutableString;

/**
 * Prototype display sub screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController final
{
private:
	GUIScreenNode* screenNode { nullptr };
	EditorView* editorView { nullptr };
	TabView* tabView { nullptr };
	PrototypeDisplaySubView* view { nullptr };
	PrototypePhysicsSubView* physicsView { nullptr };
	PopUps* popUps { nullptr };

	bool displayShadowing { true };
	bool displayGround { true };
	bool displayBoundingVolumes { true };

	array<string, 6> applyDisplayNodes = {
		"rendering_shader",
		"rendering_distance_shader",
		"rendering_contributes_shadows",
		"rendering_receives_shadows",
		"rendering_render_groups"
	};
	array<string, 2> applyDisplayUpdateRenderingNodes = {
		"rendering_shader",
		"rendering_distance_shader"
	};

public:
	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param tabView tab view
	 * @param physicsView physics view
	 */
	PrototypeDisplaySubController(EditorView* editorView, TabView* tabView, PrototypePhysicsSubView* physicsView);

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

	/**
	 * Create display properties XML
	 * @param prototype prototype
	 * @param xml xml
	 */
	void createDisplayPropertiesXML(Prototype* prototype, string& xml);

	/**
	 * Set display details
	 * @param prototype prototype
	 */
	void setDisplayDetails(Prototype* prototype);

	/**
	 * Update details panel
	 * @param prototype prototype
	 * @param outlinerNode outliner node
	 */
	void updateDetails(Prototype* prototype, const string& outlinerNode);

	/**
	 * Apply display details
	 * @param prototype prototype
	 */
	void applyDisplayDetails(Prototype* prototype);

	/**
	 * Create display shader details XML
	 * @param prototype prototype
	 * @param shaderParameterPrefix shader parameter prefix
	 * @param shader shader
	 * @param shaderParameters shader parameters
	 * @param xml xml
	 */
	void createDisplayShaderDetailsXML(Prototype* prototype, const string& shaderParameterPrefix, const string& shader, const EntityShaderParameters& shaderParameters, string& xml);

	/**
	 * Set display shader details
	 * @param prototype prototype
	 */
	void setDisplayShaderDetails(Prototype* prototype);

	/**
	 * Apply display shader details
	 * @param prototype prototype
	 * @param shaderParameterPrefix shader parameter prefix
	 * @param parameterName parameter name
	 * @param shaderParameters shader parameters
	 */
	void applyDisplayShaderDetails(Prototype* prototype, const string& shaderParameterPrefix, const string& parameterName, EntityShaderParameters& shaderParameters);
	/**
	 * On value changed
	 * @param node node
	 * @param prototype prototype
	 * @return if this event has been handled
	 */
	bool onChange(GUIElementNode* node, Prototype* prototype);

	/**
	 * Show the information pop up / modal
	 * @param caption caption
	 * @param message message
	 */
	void showInfoPopUp(const string& caption, const string& message);

};
