// Generated from /tdme/src/tdme/gui/GUI.java

#pragma once

#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/gui/events/GUIMouseEvent.h>

using tdme::utils::Pool;
using tdme::gui::GUI;
using tdme::gui::events::GUIMouseEvent;


struct default_init_tag;
class tdme::gui::GUI_1
	: public Pool
{

public:
	typedef Pool super;

public: /* protected */
	GUIMouseEvent* instantiate() override;

	// Generated

public:
	GUI_1(GUI *GUI_this);
	static ::java::lang::Class *class_();
	GUI *GUI_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUI;
	friend class GUI_2;
};
