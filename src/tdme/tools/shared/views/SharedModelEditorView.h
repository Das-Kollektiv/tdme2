#pragma once

#include <string>

#include "../../../gui/events/GUIInputEventHandler.h"
#include "View.h"

#include <tdme/audio/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using std::string;

using tdme::audio::Audio;
using tdme::engine::Engine;
using tdme::gui::events::GUIInputEventHandler;
using tdme::math::Vector3;
using tdme::tools::shared::controller::ModelEditorScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::EntityBoundingVolumeView;
using tdme::tools::shared::views::EntityDisplayView;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::View;

/** 
 * TDME model editor view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::views::SharedModelEditorView
	: public virtual View
	, public virtual GUIInputEventHandler
{
protected:
	Engine* engine {  };
	Audio* audio {  };

private:
	PopUps* popUps {  };
	ModelEditorScreenController* modelEditorScreenController {  };
	EntityDisplayView* entityDisplayView {  };
	EntityBoundingVolumeView* entityBoundingVolumeView {  };
	LevelEditorEntity* entity {  };
	bool loadModelRequested {  };
	bool initModelRequested {  };
	bool initModelRequestedReset {  };
	string modelFile {  };
	int lodLevel {  };
	CameraRotationInputHandler* cameraRotationInputHandler {  };
	int64_t audioStarted { -1LL };
	int64_t audioOffset { -1LL };

	/**
	 * Init model
	 */
	virtual void initModel();

	/**
	 * Load settings
	 */
	void loadSettings();

	/**
	 * Store settings
	 */
	void storeSettings();

	/**
	 * Load a model
	 */
	void loadModel();

	/**
	 * Load model
	 * @param name name
	 * @param description description
	 * @param pathName path name
	 * @param fileName file name
	 * @param pivot pivot
	 * @return level editor entity
	 * @throws Exception
	 */
	virtual LevelEditorEntity* loadModel(const string& name, const string& description, const string& pathName, const string& fileName, const Vector3& pivot) /* throws(Exception) */;

public:

	/** 
	 * @return pop up views
	 */
	virtual PopUps* getPopUpsViews();

	/** 
	 * @return entity
	 */
	virtual LevelEditorEntity* getEntity();

	/** 
	 * Set entity
	 */
	virtual void setEntity(LevelEditorEntity* entity);

	/**
	 * Reset entity
	 */
	virtual void resetEntity();

	/** 
	 * @return current model file name
	 */
	virtual const string& getFileName();

	/**
	 * @return LOD level
	 */
	int getLodLevel() const;

	/**
	 * Set lod level to display
	 * @param lodLevel lod level
	 */
	void setLodLevel(int lodLevel);

	/** 
	 * Issue file loading
	 */
	virtual void loadFile(const string& pathName, const string& fileName);

	/** 
	 * Triggers saving a map
	 */
	virtual void saveFile(const string& pathName, const string& fileName) /* throws(Exception) */;

	/** 
	 * Issue file reloading
	 */
	virtual void reloadFile();

	/** 
	 * Apply pivot
	 * @param x x
	 * @param y y
	 * @param z z
	 */
	virtual void pivotApply(float x, float y, float z);
	void handleInputEvents() override;

	/** 
	 * Renders the scene 
	 */
	void display() override;

	/** 
	 * Init GUI elements
	 */
	virtual void updateGUIElements();

	/** 
	 * On init additional screens
	 */
	virtual void onInitAdditionalScreens();

	void initialize() override;
	void activate() override;
	void deactivate() override;
	void dispose() override;

	/** 
	 * On load model
	 * @param oldEntity old entity
	 * @param entity entity
	 */
	virtual void onLoadModel(LevelEditorEntity* oldEntity, LevelEditorEntity* entity);

	/** 
	 * On set entity data hook
	 */
	virtual void onSetEntityData();

	/**
	 * Play animation
	 */
	virtual void playAnimation(const string& animationId);

	/**
	 * Public constructor
	 * @param popUps pop ups
	 */
	SharedModelEditorView(PopUps* popUps);

	/**
	 * Destructor
	 */
	~SharedModelEditorView();
};
