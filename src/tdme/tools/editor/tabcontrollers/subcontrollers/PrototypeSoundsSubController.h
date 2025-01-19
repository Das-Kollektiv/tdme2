#pragma once

#include <array>
#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>
#include <tdme/tools/editor/views/fwd-tdme.h>

using std::array;
using std::string;
using std::unique_ptr;

using tdme::engine::model::Model;
using tdme::engine::prototype::Prototype;
using agui::gui::events::GUIActionListenerType;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIScreenNode;
using tdme::math::Vector3;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabviews::subviews::PrototypeSoundsSubView;
using tdme::tools::editor::tabviews::ModelEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::views::PlayableSoundView;

/**
 * Prototype sounds sub screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController final
{
private:
	GUIScreenNode* screenNode { nullptr };
	EditorView* editorView { nullptr };
	unique_ptr<PrototypeSoundsSubView> view;
	PopUps* popUps { nullptr };
	PlayableSoundView* playableSoundView { nullptr };
	array<string, 7> applyAudioNodes = {
		"sound_key",
		"sound_animation",
		"sound_gain",
		"sound_pitch",
		"sound_offset",
		"sound_looping",
		"sound_ambient",
	};
	string renameSoundName;

public:
	// forbid class copy
	FORBID_CLASS_COPY(PrototypeSoundsSubController)

	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param playableSoundView view that supports playing sounds
	 */
	PrototypeSoundsSubController(EditorView* editorView, PlayableSoundView* playableSoundView);

	/**
	 * Destructor
	 */
	~PrototypeSoundsSubController();

	/**
	 * @returns view
	 */
	inline PrototypeSoundsSubView* getView() {
		return view.get();
	}

	/**
	 * @returns screen node
	 */
	inline GUIScreenNode* getScreenNode() {
		return screenNode;
	}

	/**
	 * Init
	 * @param screenNode screen node
	 */
	void initialize(GUIScreenNode* screenNode);

	/**
	 * On sound load
	 * @param protoype prototype
	 * @param soundId sound id
	 */
	void onSoundLoad(Prototype* prototype, const string& soundId);

	/**
	 * On sound clear
	 * @param prototype prototype
	 * @param soundId sound id
	 */
	void onSoundClear(Prototype* prototype, const string& soundId);

	/**
	 * On sound browse to
	 * @param prototype prototype
	 * @param soundId sound id
	 */
	void onSoundBrowseTo(Prototype* prototype, const string& soundId);

	/**
	 * Show the information pop up / modal
	 * @param caption caption
	 * @param message message
	 */
	void showInfoPopUp(const string& caption, const string& message);

	/**
	 * Create sounds XML for outliner
	 * @param prototype prototype
	 * @param xml xml
	 */
	void createOutlinerSoundsXML(Prototype* prototype, string& xml);

	/**
	 * Update details
	 * @param prototype prototype
	 * @param model model
	 * @param outlinerNode outliner node
	 */
	void updateDetails(Prototype* prototype, Model* model, const string& outlinerNode);

	/**
	 * Apply sound details
	 * @param prototype prototype
	 * @param soundId sound Id
	 */
	void applySoundDetails(Prototype* prototype, const string& soundId);

	/**
	 * Apply sound details rename
	 * @param prototype prototype
	 * @param soundId sound Id
	 * @returns new sound id
	 */
	const string applySoundDetailsRename(Prototype* prototype, const string& soundId);

	/**
	 * Create sound
	 * @param prototype prototype
	 */
	void createSound(Prototype* prototype);

	/**
	 * Start rename sound
	 * @param property property
	 * @param soundName sound name
	 */
	void startRenameSound(Prototype* prototype, const string& soundName);

	/**
	 * Rename sound
	 * @param prototype prototype
	 */
	void renameSound(Prototype* prototype);

	/**
	 * On value changed
	 * @param node node
	 * @param prototype prototype
	 * @param model model
	 * @returns if this event has been handled
	 */
	bool onChange(GUIElementNode* node, Prototype* prototype, Model* model);

	/**
	 * On focus
	 * @param node node
	 * @param prototype prototype
	 * @returns if this event has been handled
	 */
	bool onFocus(GUIElementNode* node, Prototype* prototype);

	/**
	 * On unfocus
	 * @param node node
	 * @param prototype prototype
	 * @returns if this event has been handled
	 */
	bool onUnfocus(GUIElementNode* node, Prototype* prototype);

	/**
	 * On action performed
	 * @param type type
	 * @param node node
	 * @param prototype prototype
	 * @returns if this event has been handled
	 */
	bool onAction(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype);

	/**
	 * On context menu requested
	 * @param node node
	 * @param mouseX unscaled mouse X position
	 * @param mouseY unscaled mouse Y position
	 * @param prototype prototype
	 */
	void onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY, Prototype* prototype);

	/**
	 * Set sound
	 * @param soundId sound id
	 * @param fileName file name
	 * @param prototype prototype
	 */
	void setSound(const string& soundId, const string& fileName, Prototype* prototype);

	/**
	 * On drop
	 * @param payload payload
	 * @param mouseX mouse X
	 * @param mouseY mouse Y
	 * @param prototype prototype
	 */
	bool onDrop(const string& payload, int mouseX, int mouseY, Prototype* prototype);

};
