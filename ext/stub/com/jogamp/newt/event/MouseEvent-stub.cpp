// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/newt/event/MouseEvent.h>

using com::jogamp::newt::event::MouseEvent;
template<typename ComponentType, typename... Bases> struct SubArray;
namespace com {
namespace jogamp {
namespace newt {
namespace event {
typedef ::SubArray< ::com::jogamp::newt::event::InputEvent_InputType, ::java::lang::ObjectArray > InputEvent_InputTypeArray;
}  // namespace event
}  // namespace newt
}  // namespace jogamp
}  // namespace com

namespace java {
namespace lang {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
}  // namespace lang

namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Enum, ObjectArray, ComparableArray, ::java::io::SerializableArray > EnumArray;
}  // namespace lang
}  // namespace java

namespace com {
namespace jogamp {
namespace newt {
namespace event {
typedef ::SubArray< ::com::jogamp::newt::event::MouseEvent_PointerType, ::java::lang::EnumArray, InputEvent_InputTypeArray > MouseEvent_PointerTypeArray;
}  // namespace event
}  // namespace newt
}  // namespace jogamp
}  // namespace com

extern void unimplemented_(const char16_t* name);
com::jogamp::newt::event::MouseEvent::MouseEvent(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

com::jogamp::newt::event::MouseEvent::MouseEvent(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int16_t arg6, int16_t arg7, floatArray* arg8, float arg9)
	: MouseEvent(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}

com::jogamp::newt::event::MouseEvent::MouseEvent(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3, MouseEvent_PointerTypeArray* arg4, int16_tArray* arg5, int32_tArray* arg6, int32_tArray* arg7, floatArray* arg8, float arg9, int16_t arg10, int16_t arg11, floatArray* arg12, float arg13)
	: MouseEvent(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13);
}

constexpr int16_t com::jogamp::newt::event::MouseEvent::BUTTON1;
constexpr int16_t com::jogamp::newt::event::MouseEvent::BUTTON2;
constexpr int16_t com::jogamp::newt::event::MouseEvent::BUTTON3;
constexpr int16_t com::jogamp::newt::event::MouseEvent::BUTTON4;
constexpr int16_t com::jogamp::newt::event::MouseEvent::BUTTON5;
constexpr int16_t com::jogamp::newt::event::MouseEvent::BUTTON6;
constexpr int16_t com::jogamp::newt::event::MouseEvent::BUTTON7;
constexpr int16_t com::jogamp::newt::event::MouseEvent::BUTTON8;
constexpr int16_t com::jogamp::newt::event::MouseEvent::BUTTON9;
constexpr int16_t com::jogamp::newt::event::MouseEvent::BUTTON_COUNT;
constexpr int16_t com::jogamp::newt::event::MouseEvent::EVENT_MOUSE_CLICKED;
constexpr int16_t com::jogamp::newt::event::MouseEvent::EVENT_MOUSE_DRAGGED;
constexpr int16_t com::jogamp::newt::event::MouseEvent::EVENT_MOUSE_ENTERED;
constexpr int16_t com::jogamp::newt::event::MouseEvent::EVENT_MOUSE_EXITED;
constexpr int16_t com::jogamp::newt::event::MouseEvent::EVENT_MOUSE_MOVED;
constexpr int16_t com::jogamp::newt::event::MouseEvent::EVENT_MOUSE_PRESSED;
constexpr int16_t com::jogamp::newt::event::MouseEvent::EVENT_MOUSE_RELEASED;
constexpr int16_t com::jogamp::newt::event::MouseEvent::EVENT_MOUSE_WHEEL_MOVED;
MouseEvent_PointerTypeArray* com::jogamp::newt::event::MouseEvent::constMousePointerTypes;
floatArray* com::jogamp::newt::event::MouseEvent::constMousePressure0;
floatArray* com::jogamp::newt::event::MouseEvent::constMousePressure1;

void MouseEvent::ctor(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int16_t arg6, int16_t arg7, floatArray* arg8, float arg9)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void MouseEvent::ctor(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int16_t arg6, int16_t arg7, floatArray* arg8, float arg9)");
}

void MouseEvent::ctor(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3, MouseEvent_PointerTypeArray* arg4, int16_tArray* arg5, int32_tArray* arg6, int32_tArray* arg7, floatArray* arg8, float arg9, int16_t arg10, int16_t arg11, floatArray* arg12, float arg13)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void MouseEvent::ctor(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3, MouseEvent_PointerTypeArray* arg4, int16_tArray* arg5, int32_tArray* arg6, int32_tArray* arg7, floatArray* arg8, float arg9, int16_t arg10, int16_t arg11, floatArray* arg12, float arg13)");
}

MouseEvent* MouseEvent::createVariant(int16_t arg0)
{ /* stub */
	unimplemented_(u"MouseEvent* MouseEvent::createVariant(int16_t arg0)");
	return 0;
}

int16_tArray* MouseEvent::getAllPointerIDs()
{ /* stub */
	unimplemented_(u"int16_tArray* MouseEvent::getAllPointerIDs()");
	return 0;
}

MouseEvent_PointerTypeArray* MouseEvent::getAllPointerTypes()
{ /* stub */
	unimplemented_(u"MouseEvent_PointerTypeArray* MouseEvent::getAllPointerTypes()");
	return 0;
}

floatArray* MouseEvent::getAllPressures()
{ /* stub */
	unimplemented_(u"floatArray* MouseEvent::getAllPressures()");
	return 0;
}

int32_tArray* MouseEvent::getAllX()
{ /* stub */
	unimplemented_(u"int32_tArray* MouseEvent::getAllX()");
	return 0;
}

int32_tArray* MouseEvent::getAllY()
{ /* stub */
	unimplemented_(u"int32_tArray* MouseEvent::getAllY()");
	return 0;
}

int16_t MouseEvent::getButton()
{ /* stub */
return button ; /* getter */
}

int16_t MouseEvent::getClickCount()
{ /* stub */
return clickCount ; /* getter */
}

int16_t MouseEvent::getClickTimeout()
{ /* stub */
	clinit();
	unimplemented_(u"int16_t MouseEvent::getClickTimeout()");
	return 0;
}

String* MouseEvent::getEventTypeString(int16_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* MouseEvent::getEventTypeString(int16_t arg0)");
	return 0;
}

float MouseEvent::getMaxPressure()
{ /* stub */
return maxPressure ; /* getter */
}

int32_t MouseEvent::getPointerCount()
{ /* stub */
	unimplemented_(u"int32_t MouseEvent::getPointerCount()");
	return 0;
}

int16_t MouseEvent::getPointerId(int32_t arg0)
{ /* stub */
	unimplemented_(u"int16_t MouseEvent::getPointerId(int32_t arg0)");
	return 0;
}

int32_t MouseEvent::getPointerIdx(int16_t arg0)
{ /* stub */
	unimplemented_(u"int32_t MouseEvent::getPointerIdx(int16_t arg0)");
	return 0;
}

MouseEvent_PointerType* MouseEvent::getPointerType(int32_t arg0)
{ /* stub */
}

float MouseEvent::getPressure(bool arg0)
{ /* stub */
}

float MouseEvent::getPressure(int32_t arg0, bool arg1)
{ /* stub */
}

floatArray* MouseEvent::getRotation()
{ /* stub */
	unimplemented_(u"floatArray* MouseEvent::getRotation()");
	return 0;
}

float MouseEvent::getRotationScale()
{ /* stub */
return rotationScale ; /* getter */
}

floatArray* MouseEvent::getRotationXYZ(float arg0, int32_t arg1)
{ /* stub */
	clinit();
	unimplemented_(u"floatArray* MouseEvent::getRotationXYZ(float arg0, int32_t arg1)");
	return 0;
}

int32_t MouseEvent::getX()
{ /* stub */
}

int32_t MouseEvent::getX(int32_t arg0)
{ /* stub */
}

int32_t MouseEvent::getY()
{ /* stub */
}

int32_t MouseEvent::getY(int32_t arg0)
{ /* stub */
}

String* MouseEvent::toString()
{ /* stub */
	unimplemented_(u"String* MouseEvent::toString()");
	return 0;
}

StringBuilder* MouseEvent::toString(StringBuilder* arg0)
{ /* stub */
	unimplemented_(u"StringBuilder* MouseEvent::toString(StringBuilder* arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* MouseEvent::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.newt.event.MouseEvent", 32);
    return c;
}

java::lang::Class* MouseEvent::getClass0()
{
	return class_();
}

