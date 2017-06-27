// Generated from /tdme/src/tdme/gui/GUI.java

#pragma once

#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>

using tdme::utils::Pool;
using tdme::gui::GUI;
using tdme::gui::events::GUIKeyboardEvent;


struct default_init_tag;
class tdme::gui::GUI_2
	: public Pool
{

public:
	typedef Pool super;

public: /* protected */
	GUIKeyboardEvent* instantiate() override;

	// Generated

public:
	GUI_2(GUI *GUI_this);
	static ::java::lang::Class *class_();
	GUI *GUI_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUI;
	friend class GUI_1;
};
