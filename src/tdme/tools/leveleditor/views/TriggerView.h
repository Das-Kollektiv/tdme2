#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/gui/events/GUIInputEventHandler.h>

using tdme::tools::shared::views::View;
using tdme::gui::events::GUIInputEventHandler;
using tdme::engine::Engine;
using tdme::tools::leveleditor::controller::TriggerScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::PopUps;

/** 
 * TDME Model Viewer View
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::leveleditor::views::TriggerView
	: public virtual View
	, public virtual GUIInputEventHandler
{
private:
	Engine* engine {  };
	PopUps* popUps {  };
	TriggerScreenController* triggerScreenController {  };
	LevelEditorEntity* entity {  };
	bool initModelRequested {  };
	CameraRotationInputHandler* cameraRotationInputHandler {  };

	/**
	 * Init entity
	 */
	virtual void initModel();

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

	/** 
	 * Trigger apply
	 * @param width
	 * @param height
	 * @param depth
	 */
	virtual void triggerApply(float width, float height, float depth);
	void initialize() override;
	void activate() override;
	void deactivate() override;
	void dispose() override;

	/**
	 * Public constructor
	 * @param pop ups view
	 */
	TriggerView(PopUps* popUps);

	/**
	 * Destructor
	 */
	~TriggerView();
};
