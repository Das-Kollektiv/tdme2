#pragma once

#include <string>

#include <fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>

using std::wstring;

using tdme::gui::nodes::GUINodeController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::utils::MutableString;


struct default_init_tag;

/** 
 * GUI element controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIElementIgnoreEventsController
	: public GUINodeController
{

public:
	typedef GUINodeController super;

private:
	static wstring CONDITION_DISABLED;
	static wstring CONDITION_ENABLED;
	bool disabled {  };
protected:

	/** 
	 * GUI element controller
	 * @param node
	 */
	void ctor(GUINode* node);

public:
	bool isDisabled() override;
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event) override;
	void tick() override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	MutableString* getValue() override;
	void setValue(MutableString* value) override;

	// Generated

public: /* protected */
	GUIElementIgnoreEventsController(GUINode* node);
protected:
	GUIElementIgnoreEventsController(const ::default_init_tag&);

public:
	static void clinit();
};
