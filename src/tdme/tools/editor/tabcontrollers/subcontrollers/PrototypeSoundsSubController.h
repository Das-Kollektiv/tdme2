#pragma once

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>
#include <tdme/tools/editor/views/fwd-tdme.h>

using std::array;
using std::string;

using tdme::engine::model::Model;
using tdme::engine::prototype::Prototype;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
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
	PrototypeSoundsSubView* view { nullptr };
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
	 * @return view
	 */
	PrototypeSoundsSubView* getView();

	/**
	 * @return screen node
	 */
	GUIScreenNode* getScreenNode();

	/**
	 * Init
	 * @param screenNode screen node
	 */
	void initialize(GUIScreenNode* screenNode);

	/**
	 * On sound clear
	 * @param prototype prototype
	 * @param soundId sound id
	 */
	void onSoundClear(Prototype* prototype, const string& soundId);

	/**
	 * On sound load
	 * @param protoype prototype
	 * @param soundId sound id
	 */
	void onSoundLoad(Prototype* prototype, const string& soundId);

	/**
	 * Shows the error pop up
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
	 * @return new sound id
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
	 */
	void onChange(GUIElementNode* node, Prototype* prototype, Model* model);

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
	 * On action performed
	 * @param type type
	 * @param node node
	 * @param prototype prototype
	 */
	void onAction(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype);

	/**
	 * On context menu requested
	 * @param node node
	 * @param mouseX unscaled mouse X position
	 * @param mouseY unscaled mouse Y position
	 * @param prototype prototype
	 */
	void onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY, Prototype* prototype);

};
