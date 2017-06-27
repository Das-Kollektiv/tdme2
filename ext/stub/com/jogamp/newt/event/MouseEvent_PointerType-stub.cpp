// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/newt/event/MouseEvent_PointerType.h>

using com::jogamp::newt::event::MouseEvent_PointerType;
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
com::jogamp::newt::event::MouseEvent_PointerType::MouseEvent_PointerType(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

MouseEvent_PointerTypeArray* com::jogamp::newt::event::MouseEvent_PointerType::$VALUES;
MouseEvent_PointerType* com::jogamp::newt::event::MouseEvent_PointerType::Mouse;
MouseEvent_PointerType* com::jogamp::newt::event::MouseEvent_PointerType::Pen;
MouseEvent_PointerType* com::jogamp::newt::event::MouseEvent_PointerType::TouchPad;
MouseEvent_PointerType* com::jogamp::newt::event::MouseEvent_PointerType::TouchScreen;
MouseEvent_PointerType* com::jogamp::newt::event::MouseEvent_PointerType::Undefined;

/* private: void MouseEvent_PointerType::ctor(::java::lang::String* name, int ordinal, MouseEvent_PointerClass* arg0) */
MouseEvent_PointerClass* MouseEvent_PointerType::getPointerClass()
{ /* stub */
	unimplemented_(u"MouseEvent_PointerClass* MouseEvent_PointerType::getPointerClass()");
	return 0;
}

MouseEvent_PointerType* MouseEvent_PointerType::valueOf(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"MouseEvent_PointerType* MouseEvent_PointerType::valueOf(String* arg0)");
	return 0;
}

MouseEvent_PointerType* MouseEvent_PointerType::valueOf(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"MouseEvent_PointerType* MouseEvent_PointerType::valueOf(int32_t arg0)");
	return 0;
}

MouseEvent_PointerTypeArray* MouseEvent_PointerType::values()
{ /* stub */
	clinit();
	unimplemented_(u"MouseEvent_PointerTypeArray* MouseEvent_PointerType::values()");
	return 0;
}

MouseEvent_PointerTypeArray* MouseEvent_PointerType::valuesOf(int32_tArray* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"MouseEvent_PointerTypeArray* MouseEvent_PointerType::valuesOf(int32_tArray* arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* MouseEvent_PointerType::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.newt.event.MouseEvent.PointerType", 44);
    return c;
}

Enum* MouseEvent_PointerType::valueOf(Class* arg0, String* arg1)
{
	return super::valueOf(arg0, arg1);
}

java::lang::Class* MouseEvent_PointerType::getClass0()
{
	return class_();
}

