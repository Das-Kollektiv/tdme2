// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/newt/event/InputEvent.h>

using com::jogamp::newt::event::InputEvent;
extern void unimplemented_(const char16_t* name);
com::jogamp::newt::event::InputEvent::InputEvent(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

com::jogamp::newt::event::InputEvent::InputEvent(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3)
	: InputEvent(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3);
}

constexpr int32_t com::jogamp::newt::event::InputEvent::ALT_GRAPH_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::ALT_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::AUTOREPEAT_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::BUTTON1_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::BUTTON2_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::BUTTON3_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::BUTTON4_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::BUTTON5_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::BUTTON6_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::BUTTON7_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::BUTTON8_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::BUTTON9_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::BUTTONALL_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::BUTTONLAST_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::CONFINED_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::CTRL_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::INVISIBLE_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::META_MASK;
constexpr int32_t com::jogamp::newt::event::InputEvent::SHIFT_MASK;

void InputEvent::ctor(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void InputEvent::ctor(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3)");
}

int32_t InputEvent::getButtonDownCount()
{ /* stub */
	unimplemented_(u"int32_t InputEvent::getButtonDownCount()");
	return 0;
}

int32_t InputEvent::getButtonMask(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t InputEvent::getButtonMask(int32_t arg0)");
	return 0;
}

int16_tArray* InputEvent::getButtonsDown()
{ /* stub */
	unimplemented_(u"int16_tArray* InputEvent::getButtonsDown()");
	return 0;
}

int32_t InputEvent::getModifiers()
{ /* stub */
return modifiers ; /* getter */
}

StringBuilder* InputEvent::getModifiersString(StringBuilder* arg0)
{ /* stub */
	unimplemented_(u"StringBuilder* InputEvent::getModifiersString(StringBuilder* arg0)");
	return 0;
}

bool InputEvent::isAltDown()
{ /* stub */
	unimplemented_(u"bool InputEvent::isAltDown()");
	return 0;
}

bool InputEvent::isAltGraphDown()
{ /* stub */
	unimplemented_(u"bool InputEvent::isAltGraphDown()");
	return 0;
}

bool InputEvent::isAnyButtonDown()
{ /* stub */
	unimplemented_(u"bool InputEvent::isAnyButtonDown()");
	return 0;
}

bool InputEvent::isAutoRepeat()
{ /* stub */
	unimplemented_(u"bool InputEvent::isAutoRepeat()");
	return 0;
}

bool InputEvent::isButtonDown(int32_t arg0)
{ /* stub */
	unimplemented_(u"bool InputEvent::isButtonDown(int32_t arg0)");
	return 0;
}

bool InputEvent::isConfined()
{ /* stub */
	unimplemented_(u"bool InputEvent::isConfined()");
	return 0;
}

bool InputEvent::isControlDown()
{ /* stub */
	unimplemented_(u"bool InputEvent::isControlDown()");
	return 0;
}

bool InputEvent::isInvisible()
{ /* stub */
	unimplemented_(u"bool InputEvent::isInvisible()");
	return 0;
}

bool InputEvent::isMetaDown()
{ /* stub */
	unimplemented_(u"bool InputEvent::isMetaDown()");
	return 0;
}

bool InputEvent::isShiftDown()
{ /* stub */
	unimplemented_(u"bool InputEvent::isShiftDown()");
	return 0;
}

String* InputEvent::toString()
{ /* stub */
	unimplemented_(u"String* InputEvent::toString()");
	return 0;
}

StringBuilder* InputEvent::toString(StringBuilder* arg0)
{ /* stub */
	unimplemented_(u"StringBuilder* InputEvent::toString(StringBuilder* arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* InputEvent::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.newt.event.InputEvent", 32);
    return c;
}

java::lang::Class* InputEvent::getClass0()
{
	return class_();
}

