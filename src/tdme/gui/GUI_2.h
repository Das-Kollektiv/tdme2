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
	: public Pool<GUIKeyboardEvent*>
{

public:
	typedef Pool super;

public: /* protected */
	GUIKeyboardEvent* instantiate() override;

	// Generated

public:
	GUI_2(GUI *GUI_this);
	GUI *GUI_this;

private:
	friend class GUI;
	friend class GUI_1;
};
