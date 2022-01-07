#include <tdme/tdme.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>

using tdme::gui::events::GUIKeyboardEvent;

int32_t GUIKeyboardEvent::getKeyCodeFromChar(char key) {
	return -1;
}

GUIKeyboardEvent::GUIKeyboardEvent()
{
	this->time = -1LL;
	this->type = GUIKeyboardEventType::KEYBOARDEVENT_NONE;
	this->keyCode = -1;
	this->keyChar = 0;
	this->metaDown = false;
	this->controlDown = false;
	this->altDown = false;
	this->shiftDown = false;
	this->processed = false;
}

GUIKeyboardEvent::~GUIKeyboardEvent() {
}
