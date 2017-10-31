
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
using tdme::tools::leveleditor::controller::EmptyScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::PopUps;

/** 
 * Empty View
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::leveleditor::views::EmptyView
	: public virtual View
	, public virtual GUIInputEventHandler
{
public: /* protected */
	Engine* engine {  };

private:
	PopUps* popUps {  };
	EmptyScreenController* emptyScreenController {  };
	LevelEditorEntity* entity {  };
	bool initModelRequested {  };
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
	 * @return selected entity
	 */
	virtual void setEntity(LevelEditorEntity* entity);

public: /* protected */

	/** 
	 * Init entity
	 */
	virtual void initModel();

public:
	void handleInputEvents() override;

	/** 
	 * Renders the scene 
	 */
	void display() override;

	/** 
	 * Init GUI elements
	 */
	virtual void updateGUIElements();
	void initialize() override;
	void activate() override;
	void deactivate() override;
	void dispose() override;

	/**
	 * Public constructor
	 * @param pop ups view
	 */
	EmptyView(PopUps* popUps);

	/**
	 * Destructor
	 */
	virtual ~EmptyView();
};
