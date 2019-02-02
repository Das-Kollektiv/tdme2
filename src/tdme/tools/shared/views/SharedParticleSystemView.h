#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/gui/events/GUIInputEventHandler.h>

using std::string;

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
protected:
	Engine* engine {  };

private:
	PopUps* popUps {  };
	ParticleSystemScreenController* particleSystemScreenController {  };
	EntityDisplayView* entityDisplayView {  };
	EntityBoundingVolumeView* entityBoundingVolumeView {  };
	LevelEditorEntity* entity {  };
	bool loadParticleSystemRequested {  };
	bool initParticleSystemRequested {  };
	string particleSystemFile {  };
	CameraRotationInputHandler* cameraRotationInputHandler {  };

	/**
	 * Load settings
	 */
	void loadSettings();

	/**
	 * Store settings
	 */
	void storeSettings();

	/**
	 * Load a particle system
	 */
	void loadParticleSystem();

	/**
	 * Load particle system
	 * @param name name
	 * @param description description
	 * @param pathName path name
	 * @param fileName file name
	 * @return level editor entity
	 * @throws Exception
	 */
	virtual LevelEditorEntity* loadParticleSystem(const string& name, const string& description, const string& pathName, const string& fileName) /* throws(Exception) */;

public:

	/**
	 * Request init particle system
	 */
	virtual void initParticleSystemRequest();

	/** 
	 * @return pop up views
	 */
	virtual PopUps* getPopUpsViews();

	/** 
	 * @return entity
	 */
	virtual LevelEditorEntity* getEntity();

	/** 
	 * Reset view
	 */
	virtual void reset();

	/**
	 * Set entity
	 */
	virtual void setEntity(LevelEditorEntity* entity);

	/**
	 * Init particle system
	 */
	virtual void initParticleSystem();

	/** 
	 * @return current particle system file name
	 */
	virtual const string getFileName();

	/** 
	 * Issue particle system loading
	 */
	virtual void loadFile(const string& pathName, const string& fileName);

	/** 
	 * Triggers saving a particle system
	 */
	virtual void saveFile(const string& pathName, const string& fileName) /* throws(Exception) */;

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
	 */
	virtual void onInitAdditionalScreens();

	void initialize() override;
	void activate() override;
	void dispose() override;
	void deactivate() override;

	/** 
	 * On load particle system
	 * @param oldEntity old entity
	 * @param entity entity
	 */
	virtual void onLoadParticleSystem(LevelEditorEntity* oldEntity, LevelEditorEntity* entity);

	/** 
	 * On set entity data hook
	 */
	virtual void onSetEntityData();

	/**
	 * Public constructor
	 * @param popUps pop ups view
	 */
	SharedParticleSystemView(PopUps* popUps);

	/**
	 * Destructor
	 */
	~SharedParticleSystemView();
};
