// Generated from /tdme/src/tdme/tools/leveleditor/views/TriggerView.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <java/lang/Object.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/gui/events/GUIInputEventHandler.h>

using java::lang::Object;
using tdme::tools::shared::views::View;
using tdme::gui::events::GUIInputEventHandler;
using tdme::engine::Engine;
using tdme::tools::leveleditor::controller::TriggerScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::PopUps;


struct default_init_tag;

/** 
 * TDME Model Viewer View
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::leveleditor::views::TriggerView
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
	TriggerScreenController* triggerScreenController {  };
	LevelEditorEntity* entity {  };
	bool initModelRequested {  };
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

	// Generated
	TriggerView(PopUps* popUps);
protected:
	TriggerView(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
