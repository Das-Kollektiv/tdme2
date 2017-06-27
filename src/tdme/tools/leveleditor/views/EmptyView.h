// Generated from /tdme/src/tdme/tools/leveleditor/views/EmptyView.java

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
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
using com::jogamp::opengl::GLAutoDrawable;
using tdme::engine::Engine;
using tdme::tools::leveleditor::controller::EmptyScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::PopUps;


struct default_init_tag;

/** 
 * Empty View
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::leveleditor::views::EmptyView
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
	EmptyScreenController* emptyScreenController {  };
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
	virtual void initModel(GLAutoDrawable* drawable);

public:
	void handleInputEvents() override;

	/** 
	 * Renders the scene 
	 */
	void display(GLAutoDrawable* drawable) override;

	/** 
	 * Init GUI elements
	 */
	virtual void updateGUIElements();
	void initialize() override;
	void activate() override;
	void deactivate() override;
	void dispose() override;

	// Generated
	EmptyView(PopUps* popUps);
protected:
	EmptyView(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
