#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/Gizmo.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/tools/shared/views/PlayableSoundView.h>
#include <tdme/gui/events/GUIInputEventHandler.h>

using std::string;

using tdme::audio::Audio;
using tdme::engine::Engine;
using tdme::engine::ParticleSystemEntity;
using tdme::gui::events::GUIInputEventHandler;
using tdme::math::Vector3;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::EntityPhysicsView;
using tdme::tools::shared::views::EntityDisplayView;
using tdme::tools::shared::views::EntitySoundsView;
using tdme::tools::shared::views::Gizmo;
using tdme::tools::shared::views::View;
using tdme::tools::shared::views::PlayableSoundView;
using tdme::tools::shared::views::PopUps;

/**
 * TDME particle system view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::views::SharedParticleSystemView
	: public View
	, public PlayableSoundView
	, public GUIInputEventHandler
	, protected Gizmo
{
protected:
	Engine* engine { nullptr };
	Audio* audio { nullptr };

private:
	PopUps* popUps { nullptr };
	ParticleSystemScreenController* particleSystemScreenController { nullptr };
	EntityDisplayView* entityDisplayView { nullptr };
	EntityPhysicsView* entityPhysicsView { nullptr };
	EntitySoundsView* entitySoundsView { nullptr };
	LevelEditorEntity* entity { nullptr };
	bool loadParticleSystemRequested;
	bool initParticleSystemRequested;
	bool updateParticleSystemRequested;
	string particleSystemFile;
	CameraRotationInputHandler* cameraRotationInputHandler { nullptr };
	int64_t audioStarted { -1LL };
	int64_t audioOffset { -1LL };
	int particleSystemIdx { 0 };
	Vector3 objectScale;
	int32_t mouseDownLastX { -1 };
	int32_t mouseDownLastY { -1 };
	Vector3 totalDeltaScale;

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
	 * @throws tdme::utilities::Exception
	 */
	virtual LevelEditorEntity* loadParticleSystem(const string& name, const string& description, const string& pathName, const string& fileName);

public:
	/**
	 * Public constructor
	 * @param popUps pop ups view
	 */
	SharedParticleSystemView(PopUps* popUps);

	/**
	 * Destructor
	 */
	~SharedParticleSystemView();

	/**
	 * Request init particle system
	 */
	void initParticleSystemRequest();

	/**
	 * Request update particle system
	 */
	void updateParticleSystemRequest();

	/**
	 * @return pop up views
	 */
	PopUps* getPopUpsViews();

	/**
	 * @return entity
	 */
	LevelEditorEntity* getEntity();

	/**
	 * Reset view
	 */
	void reset();

	/**
	 * Set entity
	 */
	void setEntity(LevelEditorEntity* entity);

	/**
	 * @return particle system index
	 */
	int getParticleSystemIndex();

	/**
	 * Set particle system index, the particle system to edit
	 * @param idx index
	 */
	void setParticleSystemIndex(int idx);

	/**
	 * Init particle system
	 */
	void initParticleSystem();

	/**
	 * @return current particle system file name
	 */
	const string getFileName();

	/**
	 * Issue particle system loading
	 */
	void loadFile(const string& pathName, const string& fileName);

	/**
	 * Triggers saving a particle system
	 */
	void saveFile(const string& pathName, const string& fileName) /* throws(Exception) */;

	/**
	 * Issue file reloading
	 */
	void reloadFile();
	void handleInputEvents() override;

	/**
	 * Renders the scene
	 */
	void display() override;

	/**
	 * Init GUI elements
	 */
	void updateGUIElements();

	// overridden methods
	void initialize() override;
	void activate() override;
	void dispose() override;
	void deactivate() override;
	void playSound(const string& soundId) override;

	/**
	 * On init additional screens
	 */
	virtual void onInitAdditionalScreens();

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
	 * Update GIZMO
	 * @param entity level editor entity
	 */
	void updateGizmo(LevelEditorEntity* entity);

	/**
	 * Set GIZMO rotation
	 * @param entity level editor entity
	 * @param transformations transformations
	 */
	void setGizmoRotation(LevelEditorEntity* entity, const Transformations& transformations);

	/**
	 * Apply particle system transformations
	 * @param particleSystemEntity particle system entity
	 * @param guiOnly GUI only
	 */
	void applyParticleSystemTransformations(ParticleSystemEntity* particleSystemEntity, bool guiOnly);

};
