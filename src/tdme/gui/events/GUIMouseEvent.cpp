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
	this->button = -1;
	this->wheelX = 0.0f;
	this->wheelY = 0.0f;
	this->wheelZ = 0.0f;
	this->processed = false;
}

GUIMouseEvent::~GUIMouseEvent() {
}

int64_t GUIMouseEvent::getTime()
{
	return time;
}

void GUIMouseEvent::setTime(int64_t time)
{
	this->time = time;
}

GUIMouseEvent_Type* GUIMouseEvent::getType()
{
	return type;
}

void GUIMouseEvent::setType(GUIMouseEvent_Type* type)
{
	this->type = type;
}

int32_t GUIMouseEvent::getXUnscaled()
{
	return xUnscaled;
}

void GUIMouseEvent::setXUnscaled(int32_t xUnscaled)
{
	this->xUnscaled = xUnscaled;
}

int32_t GUIMouseEvent::getYUnscaled()
{
	return yUnscaled;
}

void GUIMouseEvent::setYUnscaled(int32_t yUnscaled)
{
	this->yUnscaled = yUnscaled;
}

int32_t GUIMouseEvent::getX()
{
	return x;
}

void GUIMouseEvent::setX(int32_t x)
{
	this->x = x;
}

int32_t GUIMouseEvent::getY()
{
	return y;
}

void GUIMouseEvent::setY(int32_t y)
{
	this->y = y;
}

int32_t GUIMouseEvent::getButton()
{
	return button;
}

void GUIMouseEvent::setButton(int32_t button)
{
	this->button = button;
}

float GUIMouseEvent::getWheelX()
{
	return wheelX;
}

void GUIMouseEvent::setWheelX(float wheelX)
{
	this->wheelX = wheelX;
}

float GUIMouseEvent::getWheelY()
{
	return wheelY;
}

void GUIMouseEvent::setWheelY(float wheelY)
{
	this->wheelY = wheelY;
}

float GUIMouseEvent::getWheelZ()
{
	return wheelZ;
}

void GUIMouseEvent::setWheelZ(float wheelZ)
{
	this->wheelZ = wheelZ;
}

bool GUIMouseEvent::isMetaDown()
{
	return metaDown;
}

void GUIMouseEvent::setMetaDown(bool metaDown)
{
	this->metaDown = metaDown;
}

bool GUIMouseEvent::isControlDown()
{
	return controlDown;
}

void GUIMouseEvent::setControlDown(bool controlDown)
{
	this->controlDown = controlDown;
}

bool GUIMouseEvent::isAltDown()
{
	return altDown;
}

void GUIMouseEvent::setAltDown(bool altDown)
{
	this->altDown = altDown;
}

bool GUIMouseEvent::isShiftDown()
{
	return shiftDown;
}

void GUIMouseEvent::setShiftDown(bool shiftDown)
{
	this->shiftDown = shiftDown;
}

bool GUIMouseEvent::isProcessed()
{
	return processed;
}

void GUIMouseEvent::setProcessed(bool processed)
{
	this->processed = processed;
}

