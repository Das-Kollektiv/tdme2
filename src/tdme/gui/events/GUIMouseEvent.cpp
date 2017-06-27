// Generated from /tdme/src/tdme/gui/events/GUIMouseEvent.java
#include <tdme/gui/events/GUIMouseEvent.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>

using tdme::gui::events::GUIMouseEvent;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::events::GUIMouseEvent_Type;

GUIMouseEvent::GUIMouseEvent(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIMouseEvent::GUIMouseEvent() 
	: GUIMouseEvent(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void GUIMouseEvent::ctor()
{
	super::ctor();
	this->time = -1;
	this->type = GUIMouseEvent_Type::NONE;
	this->x = -1;
	this->y = -1;
	this->button = -1;
	this->wheelX = 0.0f;
	this->wheelY = 0.0f;
	this->wheelZ = 0.0f;
	this->processed = false;
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

bool GUIMouseEvent::isProcessed()
{
	return processed;
}

void GUIMouseEvent::setProcessed(bool processed)
{
	this->processed = processed;
}

String* GUIMouseEvent::toString()
{
	return ::java::lang::StringBuilder().append(u"GUIMouseEvent [time="_j)->append(time)
		->append(u", type="_j)
		->append(static_cast< Object* >(type))
		->append(u", x="_j)
		->append(x)
		->append(u", y="_j)
		->append(y)
		->append(u", button="_j)
		->append(button)
		->append(u", wheelX="_j)
		->append(wheelX)
		->append(u", wheelY="_j)
		->append(wheelY)
		->append(u", wheelZ="_j)
		->append(wheelZ)
		->append(u", processed="_j)
		->append(processed)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIMouseEvent::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.events.GUIMouseEvent", 29);
    return c;
}

java::lang::Class* GUIMouseEvent::getClass0()
{
	return class_();
}

