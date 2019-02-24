#pragma once

#include <array>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::array;
using std::vector;
using std::string;

using tdme::engine::model::Model;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::math::Vector3;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::EntitySoundsView;
using tdme::tools::shared::views::SharedModelEditorView;
using tdme::tools::shared::views::PopUps;
using tdme::utils::MutableString;

/** 
 * Entity bounding volume sub screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::EntitySoundsSubScreenController
{
	friend class EntitySoundsSubScreenController_BoundingVolumeType;
	friend class EntitySoundsSubScreenController_GenerateConvexMeshes;
	friend class EntitySoundsSubScreenController_onBoundingVolumeConvexMeshesFile;
	friend class EntitySoundsSubScreenController_onBoundingVolumeConvexMeshFile;

private:
	GUIScreenNode* screenNode {  };
	FileDialogPath* audioPath {  };
	EntitySoundsView* view {  };
	SharedModelEditorView* modelEditorView {  };
	array<GUIElementNode*, LevelEditorEntity::MODEL_SOUNDS_COUNT> soundsSoundAnimationDropDown {  };
	array<GUIElementNode*, LevelEditorEntity::MODEL_SOUNDS_COUNT> soundsSoundKey {  };
	array<GUIElementNode*, LevelEditorEntity::MODEL_SOUNDS_COUNT> soundsSoundFile {  };
	array<GUIElementNode*, LevelEditorEntity::MODEL_SOUNDS_COUNT> soundsSoundLoad {  };
	array<GUIElementNode*, LevelEditorEntity::MODEL_SOUNDS_COUNT> soundsSoundClear {  };
	array<GUIElementNode*, LevelEditorEntity::MODEL_SOUNDS_COUNT> soundsSoundGain {  };
	array<GUIElementNode*, LevelEditorEntity::MODEL_SOUNDS_COUNT> soundsSoundPitch {  };
	array<GUIElementNode*, LevelEditorEntity::MODEL_SOUNDS_COUNT> soundsSoundOffset {  };
	array<GUIElementNode*, LevelEditorEntity::MODEL_SOUNDS_COUNT> soundsSoundLooping {  };
	array<GUIElementNode*, LevelEditorEntity::MODEL_SOUNDS_COUNT> soundsSoundFixed {  };
	array<GUIElementNode*, LevelEditorEntity::MODEL_SOUNDS_COUNT> soundsSoundApply {  };

public:

	/** 
	 * @return view
	 */
	virtual EntitySoundsView* getView();

	/**
	 * @return screen node
	 */
	virtual GUIScreenNode* getScreenNode();

	/** 
	 * Init
	 * @param screenNode screen node
	 */
	virtual void initialize(GUIScreenNode* screenNode);

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
	virtual void unsetSound(int soundIdx);

	/**
	 * Unset sounds
	 */
	virtual void unsetSounds();

	/**
	 * Set physics
	 * @param entity entity
	 */
	virtual void setSounds(LevelEditorEntity* entity);

	/**
	 * On sound apply
	 * @param soundIdx sound index
	 * @param levelEditorEntity entity
	 */
	virtual void onSoundApply(int soundIdx, LevelEditorEntity* entity);

	/**
	 * On sound clear
	 * @param soundIdx sound index
	 */
	virtual void onSoundClear(int soundIdx);

	/**
	 * On sound load
	 * @param soundIdx sound index
	 */
	virtual void onSoundLoad(int soundIdx);

	/**
	 * Shows the error pop up
	 */
	virtual void showErrorPopUp(const string& caption, const string& message);

	/**
	 * On value changed
	 * @param node node
	 * @param entity entity
	 */
	virtual void onValueChanged(GUIElementNode* node, LevelEditorEntity* entity);

	/** 
	 * On action performed
	 * @param type type
	 * @param node node
	 * @param entity entity
	 */
	virtual void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node, LevelEditorEntity* entity);

	/**
	 * Public constructor
	 * @param popUps pop ups
	 * @param audioPath audio path
	 */
	EntitySoundsSubScreenController(SharedModelEditorView* modelEditorView, PopUps* popUps, FileDialogPath* audioPath);

	/**
	 * Destructor
	 */
	virtual ~EntitySoundsSubScreenController();
};
