
#pragma once

#include <string>

#include "../../../gui/events/GUIInputEventHandler.h"
#include "View.h"

#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using std::wstring;

using tdme::tools::shared::views::View;
using tdme::gui::events::GUIInputEventHandler;
using tdme::engine::Engine;
using tdme::math::Vector3;
using tdme::tools::shared::controller::ModelViewerScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::EntityBoundingVolumeView;
using tdme::tools::shared::views::EntityDisplayView;
using tdme::tools::shared::views::PopUps;

/** 
 * TDME Model Viewer View
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::views::SharedModelViewerView
	: public virtual View
	, public virtual GUIInputEventHandler
{
public: /* protected */
	Engine* engine {  };

private:
	PopUps* popUps {  };
	ModelViewerScreenController* modelViewerScreenController {  };
	EntityDisplayView* entityDisplayView {  };
	EntityBoundingVolumeView* entityBoundingVolumeView {  };
	LevelEditorEntity* entity {  };
	bool loadModelRequested {  };
	bool initModelRequested {  };
	wstring modelFile {  };
	CameraRotationInputHandler* cameraRotationInputHandler {  };

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

public: /* protected */

	/** 
	 * Init model
	 */
	virtual void initModel();

public:

	/** 
	 * @return current model file name
	 */
	virtual const wstring& getFileName();

	/** 
	 * Issue file loading
	 */
	virtual void loadFile(const wstring& pathName, const wstring& fileName);

	/** 
	 * Triggers saving a map
	 */
	virtual void saveFile(const wstring& pathName, const wstring& fileName) /* throws(Exception) */;

	/** 
	 * Issue file reloading
	 */
	virtual void reloadFile();

	/** 
	 * Apply pivot
	 * @param x
	 * @param y
	 * @param z
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
	 * @param drawable
	 */
	virtual void onInitAdditionalScreens();

private:

	/** 
	 * Load settings
	 */
	void loadSettings();

public:
	void initialize() override;
	void activate() override;

private:

	/** 
	 * Store settings
	 */
	void storeSettings();

public:
	void deactivate() override;
	void dispose() override;

	/** 
	 * On load model
	 * @param oldModel
	 * @oaram entity
	 */
	virtual void onLoadModel(LevelEditorEntity* oldModel, LevelEditorEntity* model);

private:

	/** 
	 * Load a model
	 */
	void loadModel();

public: /* protected */

	/** 
	 * Load model
	 * @param name
	 * @param description
	 * @param path name
	 * @param file name
	 * @param pivot
	 * @return level editor entity
	 * @throws Exception
	 */
	virtual LevelEditorEntity* loadModel(const wstring& name, const wstring& description, const wstring& pathName, const wstring& fileName, const Vector3& pivot) /* throws(Exception) */;

public:

	/** 
	 * On set entity data hook
	 */
	virtual void onSetEntityData();

	/**
	 * Public constructor
	 * @param pop ups
	 */
	SharedModelViewerView(PopUps* popUps);

	/**
	 * Destructor
	 */
	~SharedModelViewerView();
};
