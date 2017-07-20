// Generated from /tdme/src/tdme/tools/leveleditor/controller/EmptyScreenController.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/leveleditor/controller/fwd-tdme.h>
#include <tdme/tools/leveleditor/views/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/tools/shared/controller/ScreenController.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>

using tdme::tools::shared::controller::ScreenController;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIChangeListener;
using java::lang::Iterable;
using java::lang::String;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::leveleditor::views::EmptyView;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::utils::MutableString;

struct default_init_tag;

/** 
 * Empty screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::leveleditor::controller::EmptyScreenController final
	: public ScreenController
	, public GUIActionListener
	, public GUIChangeListener
{

public:
	typedef ScreenController super;

private:
	static MutableString* TEXT_EMPTY;
	EntityBaseSubScreenController* entityBaseSubScreenController {  };
	EmptyView* view {  };
	GUIScreenNode* screenNode {  };
	GUITextNode* screenCaption {  };
protected:

	/** 
	 * Public constructor
	 * @param view
	 */
	void ctor(EmptyView* view);

public:
	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;

	/** 
	 * Set screen caption
	 * @param text
	 */
	void setScreenCaption(String* text);

	/** 
	 * Set up general entity data
	 * @param name
	 * @param description
	 */
	void setEntityData(String* name, String* description);

	/** 
	 * Unset entity data
	 */
	void unsetEntityData();

	/** 
	 * Set up entity properties
	 * @param preset id
	 * @param entity properties
	 * @param selected name
	 */
	void setEntityProperties(String* presetId, String* selectedName);

	/** 
	 * Unset entity properties
	 */
	void unsetEntityProperties();

	/** 
	 * On quit
	 */
	void onQuit();

	/** 
	 * Shows the error pop up
	 */
	void showErrorPopUp(String* caption, String* message);
	void onValueChanged(GUIElementNode* node) override;
	void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) override;

	// Generated
	EmptyScreenController(EmptyView* view);
protected:
	EmptyScreenController(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
	friend class EmptyScreenController_EmptyScreenController_1;
};
