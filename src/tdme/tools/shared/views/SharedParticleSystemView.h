
#pragma once

#include <string>

#include <tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/gui/events/GUIInputEventHandler.h>

using std::wstring;

using tdme::tools::shared::views::View;
using tdme::gui::events::GUIInputEventHandler;
using tdme::engine::Engine;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::EntityBoundingVolumeView;
using tdme::tools::shared::views::EntityDisplayView;
using tdme::tools::shared::views::PopUps;

/** 
 * TDME particle system view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::views::SharedParticleSystemView
	: public virtual View
	, public virtual GUIInputEventHandler
{
public: /* protected */
	Engine* engine {  };

private:
	PopUps* popUps {  };
	ParticleSystemScreenController* particleSystemScreenController {  };
	EntityDisplayView* entityDisplayView {  };
	EntityBoundingVolumeView* entityBoundingVolumeView {  };
	LevelEditorEntity* entity {  };
	bool loadParticleSystemRequested {  };
	bool initParticleSystemRequested {  };
	wstring particleSystemFile {  };
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

	/**
	 * Init particle system
	 */
	virtual void initParticleSystem();

public: /* protected */

	/** 
	 * Request init particle system
	 */
	virtual void initParticleSystemRequest();

public:

	/** 
	 * @return current particle system file name
	 */
	virtual const wstring getFileName();

	/** 
	 * Issue particle system loading
	 */
	virtual void loadFile(const wstring& pathName, const wstring& fileName);

	/** 
	 * Triggers saving a particle system
	 */
	virtual void saveFile(const wstring& pathName, const wstring& fileName) /* throws(Exception) */;

	/** 
	 * Issue file reloading
	 */
	virtual void reloadFile();
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
	void dispose() override;
	void deactivate() override;

	/** 
	 * On load particle system
	 * @param old entity
	 * @oaram entity
	 */
	virtual void onLoadParticleSystem(LevelEditorEntity* oldEntity, LevelEditorEntity* entity);

private:

	/** 
	 * Load a particle system
	 */
	void loadParticleSystem();

public: /* protected */

	/** 
	 * Load particle system
	 * @param name
	 * @param description
	 * @param path name
	 * @param file name
	 * @return level editor entity
	 * @throws Exception
	 */
	virtual LevelEditorEntity* loadParticleSystem(const wstring& name, const wstring& description, const wstring& pathName, const wstring& fileName) /* throws(Exception) */;

public:

	/** 
	 * On set entity data hook
	 */
	virtual void onSetEntityData();

	/**
	 * Public constructor
	 * @param pop ups view
	 */
	SharedParticleSystemView(PopUps* popUps);

	/**
	 * Destructor
	 */
	~SharedParticleSystemView();
};
