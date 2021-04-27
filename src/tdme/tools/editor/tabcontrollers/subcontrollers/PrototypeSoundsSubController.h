#pragma once

#include <array>
#include <string>
#include <vector>

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
using std::vector;

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
using tdme::tools::editor::views::PlayableSoundView;

/**
 * Prototype sounds sub screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController final
{
	friend class PrototypeSoundsSubController_BoundingVolumeType;
	friend class PrototypeSoundsSubController_GenerateConvexMeshes;
	friend class PrototypeSoundsSubController_onBoundingVolumeConvexMeshesFile;
	friend class PrototypeSoundsSubController_onBoundingVolumeConvexMeshFile;

private:
	GUIScreenNode* screenNode { nullptr };
	FileDialogPath* audioPath { nullptr };
	PrototypeSoundsSubView* view { nullptr };
	PlayableSoundView* playableSoundView { nullptr };
	array<GUIElementNode*, Prototype::MODEL_SOUNDS_COUNT> soundsSoundAnimationDropDown;
	array<GUIElementNode*, Prototype::MODEL_SOUNDS_COUNT> soundsSoundKey;
	array<GUIElementNode*, Prototype::MODEL_SOUNDS_COUNT> soundsSoundFile;
	array<GUIElementNode*, Prototype::MODEL_SOUNDS_COUNT> soundsSoundLoad;
	array<GUIElementNode*, Prototype::MODEL_SOUNDS_COUNT> soundsSoundClear;
	array<GUIElementNode*, Prototype::MODEL_SOUNDS_COUNT> soundsSoundGain;
	array<GUIElementNode*, Prototype::MODEL_SOUNDS_COUNT> soundsSoundPitch;
	array<GUIElementNode*, Prototype::MODEL_SOUNDS_COUNT> soundsSoundOffset;
	array<GUIElementNode*, Prototype::MODEL_SOUNDS_COUNT> soundsSoundLooping;
	array<GUIElementNode*, Prototype::MODEL_SOUNDS_COUNT> soundsSoundFixed;
	array<GUIElementNode*, Prototype::MODEL_SOUNDS_COUNT> soundsSoundApply;

public:
	/**
	 * Public constructor
	 * @param playableSoundView view that supports playing sounds
	 * @param popUps pop ups
	 * @param audioPath audio path
	 */
	PrototypeSoundsSubController(PlayableSoundView* playableSoundView, PopUps* popUps, FileDialogPath* audioPath);

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
	 * Set sound animation drop down
	 * @param soundIdx sound index
	 * @param model model
	 */
	void setSoundAnimationDropDown(int soundIdx, Model* model);

	/**
	 * Unset sound by index
	 * @param soundIdx sound index
	 */
	void unsetSound(int soundIdx);

	/**
	 * Unset sounds
	 */
	void unsetSounds();

	/**
	 * Set physics
	 * @param prototype prototype
	 */
	void setSounds(Prototype* prototype);

	/**
	 * On sound apply
	 * @param soundIdx sound index
	 * @param prototype prototype
	 */
	void onSoundApply(int soundIdx, Prototype* prototype);

	/**
	 * On sound clear
	 * @param soundIdx sound index
	 */
	void onSoundClear(int soundIdx);

	/**
	 * On sound load
	 * @param soundIdx sound index
	 */
	void onSoundLoad(int soundIdx);

	/**
	 * Shows the error pop up
	 * @param caption caption
	 * @param message message
	 */
	void showErrorPopUp(const string& caption, const string& message);

	/**
	 * On value changed
	 * @param node node
	 * @param entity entity
	 */
	void onValueChanged(GUIElementNode* node, Prototype* prototype);

	/**
	 * On action performed
	 * @param type type
	 * @param node node
	 * @param prototype prototype
	 */
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype);

};
