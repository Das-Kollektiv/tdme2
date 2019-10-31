#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/CameraRotationInputHandlerEventHandler.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/gui/events/GUIInputEventHandler.h>

using tdme::tools::shared::views::View;
using tdme::gui::events::GUIInputEventHandler;
using tdme::engine::Engine;
using tdme::math::Vector3;
using tdme::tools::leveleditor::controller::TriggerScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::CameraRotationInputHandlerEventHandler;
using tdme::tools::shared::views::EntityPhysicsView;
using tdme::tools::shared::views::PopUps;

/** 
 * Trigger view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::leveleditor::views::TriggerView
	: public virtual View
	, public virtual GUIInputEventHandler
	, protected virtual CameraRotationInputHandlerEventHandler
{
private:
	Engine* engine { nullptr };
	PopUps* popUps { nullptr };
	TriggerScreenController* triggerScreenController { nullptr };
	EntityPhysicsView* entityPhysicsView { nullptr };
	LevelEditorEntity* entity { nullptr };
	CameraRotationInputHandler* cameraRotationInputHandler { nullptr };
	Vector3 objectScale;

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
	 * @return selected entity
	 */
	virtual void setEntity(LevelEditorEntity* entity);

	void handleInputEvents() override;

	/** 
	 * Renders the scene 
	 */
	void display() override;

	/** 
	 * Init GUI elements
	 */
	virtual void updateGUIElements();

	// overridden methods
	void initialize() override;
	void activate() override;
	void deactivate() override;
	void dispose() override;

	/**
	 * On rotation event to be overloaded
	 */
	virtual void onRotation() override;

	/**
	 * On scale event to be overloaded
	 */
	virtual void onScale() override;

	/**
	 * Public constructor
	 * @param popUps pop ups view
	 */
	TriggerView(PopUps* popUps);

	/**
	 * Destructor
	 */
	~TriggerView();
};
