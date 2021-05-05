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
using tdme::tools::editor::misc::FileDialogPath;
using tdme::tools::editor::misc::FileDialogPath;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabviews::subviews::PrototypeSoundsSubView;
using tdme::tools::editor::tabviews::ModelEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::views::PlayableSoundView;

/**
 * Prototype sounds sub screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController final
{
private:
	GUIScreenNode* screenNode { nullptr };
	FileDialogPath* audioPath { nullptr };
	EditorView* editorView { nullptr };
	PrototypeSoundsSubView* view { nullptr };
	PlayableSoundView* playableSoundView { nullptr };
	array<string, 7> audioChangeNodes = {
		"sound_key",
		"sound_animation",
		"sound_gain",
		"sound_pitch",
		"sound_offset",
		"sound_looping",
		"sound_ambient",
	};

public:
	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param playableSoundView view that supports playing sounds
	 * @param popUps pop ups
	 * @param audioPath audio path
	 */
	PrototypeSoundsSubController(EditorView* editorView, PlayableSoundView* playableSoundView, PopUps* popUps, FileDialogPath* audioPath);

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
	void showErrorPopUp(const string& caption, const string& message);

	/**
	 * Create sounds XML for outliner
	 * @param prototype prototype
	 * @param xml xml
	 */
	void createOutlinerSoundsXML(Prototype* prototype, string& xml);

	/**
	 * Set sound details
	 * @param prototype prototype
	 * @param model model
	 * @param soundId sound Id
	 */
	void setSoundDetails(Prototype* prototype, Model* model, const string& soundId);

	/**
	 * Update sound details
	 * @param prototype prototype
	 * @param soundId sound Id
	 */
	void updateSoundDetails(Prototype* prototype, const string& soundId);

	/**
	 * On value changed
	 * @param node node
	 * @param prototype prototype
	 * @param model model
	 */
	void onValueChanged(GUIElementNode* node, Prototype* prototype, Model* model);

	/**
	 * On action performed
	 * @param type type
	 * @param node node
	 * @param prototype prototype
	 */
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype);

};
