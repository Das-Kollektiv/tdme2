// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Enum.h>

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Class;
using java::lang::Comparable;
using java::lang::String;
using com::jogamp::nativewindow::VisualIDHolder_VIDType;
using java::lang::Object;

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

using com::jogamp::nativewindow::VisualIDHolder_VIDTypeArray;
using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;

struct default_init_tag;
class com::jogamp::nativewindow::VisualIDHolder_VIDType final
	: public Enum
{

public:
	typedef Enum super;

private:
	static VisualIDHolder_VIDTypeArray* $VALUES;

public:
	static VisualIDHolder_VIDType* EGL_CONFIG;
	static VisualIDHolder_VIDType* INTRINSIC;
	static VisualIDHolder_VIDType* NATIVE;
	static VisualIDHolder_VIDType* WIN32_PFD;
	static VisualIDHolder_VIDType* X11_FBCONFIG;
	static VisualIDHolder_VIDType* X11_XVISUAL;
	int32_t id {  };

	/*void ctor(::java::lang::String* name, int ordinal, int32_t arg0); (private) */
	static VisualIDHolder_VIDType* valueOf(String* arg0);
	static VisualIDHolder_VIDTypeArray* values();

	// Generated
	VisualIDHolder_VIDType(::java::lang::String* name, int ordinal);
protected:
	VisualIDHolder_VIDType(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static Enum* valueOf(Class* enumType, String* name);

private:
	virtual ::java::lang::Class* getClass0();
};
