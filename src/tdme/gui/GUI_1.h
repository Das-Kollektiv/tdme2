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
	: public Pool<GUIMouseEvent*>
{

public:
	typedef Pool super;

public: /* protected */
	GUIMouseEvent* instantiate() override;

	// Generated

public:
	GUI_1(GUI *GUI_this);
	GUI *GUI_this;

private:
	friend class GUI;
	friend class GUI_2;
};
