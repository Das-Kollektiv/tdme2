	#include <tdme/gui/events/GUIMouseEvent.h>

#include <tdme/gui/events/GUIMouseEvent_Type.h>

using tdme::gui::events::GUIMouseEvent;
using tdme::gui::events::GUIMouseEvent_Type;

GUIMouseEvent::GUIMouseEvent() 
{
	this->time = -1;
	this->type = GUIMouseEvent_Type::MOUSEEVENT_NONE;
	this->x = -1;
	this->y = -1;
	this->xUnscaled = -1;
	this->yUnscaled = -1;
	this->button = -1;
	this->wheelX = 0.0f;
	this->wheelY = 0.0f;
	this->wheelZ = 0.0f;
	this->shiftDown = false;
	this->altDown = false;
	this->controlDown = false;
	this->metaDown = false;
	this->processed = false;
}

GUIMouseEvent::~GUIMouseEvent() {
}
