// Generated from /tdme/src/tdme/tools/shared/views/SharedParticleSystemView.java

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/gui/events/GUIInputEventHandler.h>

using java::lang::Object;
using tdme::tools::shared::views::View;
using tdme::gui::events::GUIInputEventHandler;
using java::io::File;
using java::lang::String;
using tdme::engine::Engine;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::EntityBoundingVolumeView;
using tdme::tools::shared::views::EntityDisplayView;
using tdme::tools::shared::views::PopUps;


struct default_init_tag;

/** 
 * TDME particle system view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::views::SharedParticleSystemView
	: public virtual Object
	, public virtual View
	, public virtual GUIInputEventHandler
{

public:
	typedef Object super;

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
	String* particleSystemFile {  };
	CameraRotationInputHandler* cameraRotationInputHandler {  };
protected:

	/** 
	 * Public constructor
	 * @param pop ups view
	 */
	void ctor(PopUps* popUps);

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
	virtual String* getFileName();

	/** 
	 * Issue particle system loading
	 */
	virtual void loadFile(String* pathName, String* fileName);

	/** 
	 * Triggers saving a particle system
	 */
	virtual void saveFile(String* pathName, String* fileName) /* throws(Exception) */;

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
	virtual LevelEditorEntity* loadParticleSystem(String* name, String* description, String* pathName, String* fileName) /* throws(Exception) */;

public:

	/** 
	 * On set entity data hook
	 */
	virtual void onSetEntityData();

	// Generated
	SharedParticleSystemView(PopUps* popUps);
protected:
	SharedParticleSystemView(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
