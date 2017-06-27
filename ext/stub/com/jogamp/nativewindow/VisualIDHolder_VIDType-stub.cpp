// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/nativewindow/VisualIDHolder_VIDType.h>

using com::jogamp::nativewindow::VisualIDHolder_VIDType;
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
typedef ::SubArray< ::com::jogamp::nativewindow::VisualIDHolder_VIDType, ::java::lang::EnumArray > VisualIDHolder_VIDTypeArray;
}  // namespace nativewindow
}  // namespace jogamp
}  // namespace com

extern void unimplemented_(const char16_t* name);
com::jogamp::nativewindow::VisualIDHolder_VIDType::VisualIDHolder_VIDType(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

VisualIDHolder_VIDTypeArray* com::jogamp::nativewindow::VisualIDHolder_VIDType::$VALUES;
VisualIDHolder_VIDType* com::jogamp::nativewindow::VisualIDHolder_VIDType::EGL_CONFIG;
VisualIDHolder_VIDType* com::jogamp::nativewindow::VisualIDHolder_VIDType::INTRINSIC;
VisualIDHolder_VIDType* com::jogamp::nativewindow::VisualIDHolder_VIDType::NATIVE;
VisualIDHolder_VIDType* com::jogamp::nativewindow::VisualIDHolder_VIDType::WIN32_PFD;
VisualIDHolder_VIDType* com::jogamp::nativewindow::VisualIDHolder_VIDType::X11_FBCONFIG;
VisualIDHolder_VIDType* com::jogamp::nativewindow::VisualIDHolder_VIDType::X11_XVISUAL;

/* private: void VisualIDHolder_VIDType::ctor(::java::lang::String* name, int ordinal, int32_t arg0) */
VisualIDHolder_VIDType* VisualIDHolder_VIDType::valueOf(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"VisualIDHolder_VIDType* VisualIDHolder_VIDType::valueOf(String* arg0)");
	return 0;
}

VisualIDHolder_VIDTypeArray* VisualIDHolder_VIDType::values()
{ /* stub */
	clinit();
	unimplemented_(u"VisualIDHolder_VIDTypeArray* VisualIDHolder_VIDType::values()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* VisualIDHolder_VIDType::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.nativewindow.VisualIDHolder.VIDType", 46);
    return c;
}

Enum* VisualIDHolder_VIDType::valueOf(Class* enumType, String* name)
{
	return super::valueOf(enumType, name);
}

java::lang::Class* VisualIDHolder_VIDType::getClass0()
{
	return class_();
}

