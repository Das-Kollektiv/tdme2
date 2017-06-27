// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/newt/event/MouseEvent_PointerClass.h>

using com::jogamp::newt::event::MouseEvent_PointerClass;
template<typename ComponentType, typename... Bases> struct SubArray;
namespace com {
namespace jogamp {
namespace newt {
namespace event {
typedef ::SubArray< ::com::jogamp::newt::event::InputEvent_InputClass, ::java::lang::ObjectArray > InputEvent_InputClassArray;
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
typedef ::SubArray< ::com::jogamp::newt::event::MouseEvent_PointerClass, ::java::lang::EnumArray, InputEvent_InputClassArray > MouseEvent_PointerClassArray;
}  // namespace event
}  // namespace newt
}  // namespace jogamp
}  // namespace com

extern void unimplemented_(const char16_t* name);
com::jogamp::newt::event::MouseEvent_PointerClass::MouseEvent_PointerClass(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

MouseEvent_PointerClassArray* com::jogamp::newt::event::MouseEvent_PointerClass::$VALUES;
MouseEvent_PointerClass* com::jogamp::newt::event::MouseEvent_PointerClass::Offscreen;
MouseEvent_PointerClass* com::jogamp::newt::event::MouseEvent_PointerClass::Onscreen;
MouseEvent_PointerClass* com::jogamp::newt::event::MouseEvent_PointerClass::Undefined;

/* private: void MouseEvent_PointerClass::ctor(::java::lang::String* name, int ordinal) */
MouseEvent_PointerClass* MouseEvent_PointerClass::valueOf(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"MouseEvent_PointerClass* MouseEvent_PointerClass::valueOf(String* arg0)");
	return 0;
}

MouseEvent_PointerClassArray* MouseEvent_PointerClass::values()
{ /* stub */
	clinit();
	unimplemented_(u"MouseEvent_PointerClassArray* MouseEvent_PointerClass::values()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* MouseEvent_PointerClass::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.newt.event.MouseEvent.PointerClass", 45);
    return c;
}

Enum* MouseEvent_PointerClass::valueOf(Class* arg0, String* arg1)
{
	return super::valueOf(arg0, arg1);
}

java::lang::Class* MouseEvent_PointerClass::getClass0()
{
	return class_();
}

