#include <tdme/gui/events/GUIKeyboardEvent.h>

#include <tdme/gui/events/GUIKeyboardEvent_Type.h>

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIKeyboardEvent_Type;

int32_t GUIKeyboardEvent::getKeyCodeFromChar(char key) {
	switch(key) {
		case(9): return KEYCODE_TAB;
		case(25): return KEYCODE_TAB_SHIFT;
		case(27): return KEYCODE_ESCAPE;
		case(32): return KEYCODE_SPACE;
		#if defined(__APPLE__)
			case(8): return KEYCODE_DELETE;
			case(127): return KEYCODE_BACKSPACE;
		#else
			case(127): return KEYCODE_DELETE;
			case(8): return KEYCODE_BACKSPACE;
		#endif
		default: return -1;
	}
}

GUIKeyboardEvent::GUIKeyboardEvent() 
{
	this->time = -1LL;
	this->type = GUIKeyboardEvent_Type::KEYBOARDEVENT_NONE;
	this->keyCode = -1;
	this->keyChar = char(0x0000);
	this->metaDown = false;
	this->controlDown = false;
	this->altDown = false;
	this->shiftDown = false;
	this->processed = false;
}

constexpr int32_t GUIKeyboardEvent::KEYCODE_TAB;

constexpr int32_t GUIKeyboardEvent::KEYCODE_TAB_SHIFT;

constexpr int32_t GUIKeyboardEvent::KEYCODE_BACKSPACE;

constexpr int32_t GUIKeyboardEvent::KEYCODE_SPACE;

constexpr int32_t GUIKeyboardEvent::KEYCODE_DELETE;

constexpr int32_t GUIKeyboardEvent::KEYCODE_LEFT;

constexpr int32_t GUIKeyboardEvent::KEYCODE_UP;

constexpr int32_t GUIKeyboardEvent::KEYCODE_RIGHT;

constexpr int32_t GUIKeyboardEvent::KEYCODE_DOWN;

constexpr int32_t GUIKeyboardEvent::KEYCODE_ESCAPE;

GUIKeyboardEvent::~GUIKeyboardEvent() {
}

int64_t GUIKeyboardEvent::getTime()
{
	return time;
}

void GUIKeyboardEvent::setTime(int64_t time)
{
	this->time = time;
}

GUIKeyboardEvent_Type* GUIKeyboardEvent::getType()
{
	return type;
}

void GUIKeyboardEvent::setType(GUIKeyboardEvent_Type* type)
{
	this->type = type;
}

int32_t GUIKeyboardEvent::getKeyCode()
{
	return keyCode;
}

void GUIKeyboardEvent::setKeyCode(int32_t code)
{
	this->keyCode = code;
}

char GUIKeyboardEvent::getKeyChar()
{
	return keyChar;
}

void GUIKeyboardEvent::setKeyChar(char keyChar)
{
	this->keyChar = keyChar;
}

bool GUIKeyboardEvent::isMetaDown()
{
	return metaDown;
}

void GUIKeyboardEvent::setMetaDown(bool metaDown)
{
	this->metaDown = metaDown;
}

bool GUIKeyboardEvent::isControlDown()
{
	return controlDown;
}

void GUIKeyboardEvent::setControlDown(bool controlDown)
{
	this->controlDown = controlDown;
}

bool GUIKeyboardEvent::isAltDown()
{
	return altDown;
}

void GUIKeyboardEvent::setAltDown(bool altDown)
{
	this->altDown = altDown;
}

bool GUIKeyboardEvent::isShiftDown()
{
	return shiftDown;
}

void GUIKeyboardEvent::setShiftDown(bool shiftDown)
{
	this->shiftDown = shiftDown;
}

bool GUIKeyboardEvent::isProcessed()
{
	return processed;
}

void GUIKeyboardEvent::setProcessed(bool processed)
{
	this->processed = processed;
}

