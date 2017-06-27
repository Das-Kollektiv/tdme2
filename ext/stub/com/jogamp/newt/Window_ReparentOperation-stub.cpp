// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/newt/Window_ReparentOperation.h>

using com::jogamp::newt::Window_ReparentOperation;
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
namespace newt {
typedef ::SubArray< ::com::jogamp::newt::Window_ReparentOperation, ::java::lang::EnumArray > Window_ReparentOperationArray;
}  // namespace newt
}  // namespace jogamp
}  // namespace com

extern void unimplemented_(const char16_t* name);
com::jogamp::newt::Window_ReparentOperation::Window_ReparentOperation(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Window_ReparentOperationArray* com::jogamp::newt::Window_ReparentOperation::$VALUES;
Window_ReparentOperation* com::jogamp::newt::Window_ReparentOperation::ACTION_INVALID;
Window_ReparentOperation* com::jogamp::newt::Window_ReparentOperation::ACTION_NATIVE_CREATION;
Window_ReparentOperation* com::jogamp::newt::Window_ReparentOperation::ACTION_NATIVE_CREATION_PENDING;
Window_ReparentOperation* com::jogamp::newt::Window_ReparentOperation::ACTION_NATIVE_REPARENTING;
Window_ReparentOperation* com::jogamp::newt::Window_ReparentOperation::ACTION_NOP;

/* private: void Window_ReparentOperation::ctor(::java::lang::String* name, int ordinal) */
Window_ReparentOperation* Window_ReparentOperation::valueOf(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Window_ReparentOperation* Window_ReparentOperation::valueOf(String* arg0)");
	return 0;
}

Window_ReparentOperationArray* Window_ReparentOperation::values()
{ /* stub */
	clinit();
	unimplemented_(u"Window_ReparentOperationArray* Window_ReparentOperation::values()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Window_ReparentOperation::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.newt.Window.ReparentOperation", 40);
    return c;
}

Enum* Window_ReparentOperation::valueOf(Class* enumType, String* name)
{
	return super::valueOf(enumType, name);
}

java::lang::Class* Window_ReparentOperation::getClass0()
{
	return class_();
}

