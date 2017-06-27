// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/nativewindow/WindowClosingProtocol_WindowClosingMode.h>

using com::jogamp::nativewindow::WindowClosingProtocol_WindowClosingMode;
template<typename ComponentType, typename... Bases> struct SubArray;
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
namespace nativewindow {
typedef ::SubArray< ::com::jogamp::nativewindow::WindowClosingProtocol_WindowClosingMode, ::java::lang::EnumArray > WindowClosingProtocol_WindowClosingModeArray;
}  // namespace nativewindow
}  // namespace jogamp
}  // namespace com

extern void unimplemented_(const char16_t* name);
com::jogamp::nativewindow::WindowClosingProtocol_WindowClosingMode::WindowClosingProtocol_WindowClosingMode(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

WindowClosingProtocol_WindowClosingModeArray* com::jogamp::nativewindow::WindowClosingProtocol_WindowClosingMode::$VALUES;
WindowClosingProtocol_WindowClosingMode* com::jogamp::nativewindow::WindowClosingProtocol_WindowClosingMode::DISPOSE_ON_CLOSE;
WindowClosingProtocol_WindowClosingMode* com::jogamp::nativewindow::WindowClosingProtocol_WindowClosingMode::DO_NOTHING_ON_CLOSE;

/* private: void WindowClosingProtocol_WindowClosingMode::ctor(::java::lang::String* name, int ordinal) */
WindowClosingProtocol_WindowClosingMode* WindowClosingProtocol_WindowClosingMode::valueOf(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"WindowClosingProtocol_WindowClosingMode* WindowClosingProtocol_WindowClosingMode::valueOf(String* arg0)");
	return 0;
}

WindowClosingProtocol_WindowClosingModeArray* WindowClosingProtocol_WindowClosingMode::values()
{ /* stub */
	clinit();
	unimplemented_(u"WindowClosingProtocol_WindowClosingModeArray* WindowClosingProtocol_WindowClosingMode::values()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* WindowClosingProtocol_WindowClosingMode::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.nativewindow.WindowClosingProtocol.WindowClosingMode", 63);
    return c;
}

Enum* WindowClosingProtocol_WindowClosingMode::valueOf(Class* enumType, String* name)
{
	return super::valueOf(enumType, name);
}

java::lang::Class* WindowClosingProtocol_WindowClosingMode::getClass0()
{
	return class_();
}

