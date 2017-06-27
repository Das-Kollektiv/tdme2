// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Enum.h>

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Class;
using java::lang::Comparable;
using java::lang::String;
using com::jogamp::nativewindow::WindowClosingProtocol_WindowClosingMode;
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
typedef ::SubArray< ::com::jogamp::nativewindow::WindowClosingProtocol_WindowClosingMode, ::java::lang::EnumArray > WindowClosingProtocol_WindowClosingModeArray;
}  // namespace nativewindow
}  // namespace jogamp
}  // namespace com

using com::jogamp::nativewindow::WindowClosingProtocol_WindowClosingModeArray;
using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;

struct default_init_tag;
class com::jogamp::nativewindow::WindowClosingProtocol_WindowClosingMode final
	: public Enum
{

public:
	typedef Enum super;

private:
	static WindowClosingProtocol_WindowClosingModeArray* $VALUES;

public:
	static WindowClosingProtocol_WindowClosingMode* DISPOSE_ON_CLOSE;
	static WindowClosingProtocol_WindowClosingMode* DO_NOTHING_ON_CLOSE;

	/*void ctor(::java::lang::String* name, int ordinal); (private) */
	static WindowClosingProtocol_WindowClosingMode* valueOf(String* arg0);
	static WindowClosingProtocol_WindowClosingModeArray* values();

	// Generated
	WindowClosingProtocol_WindowClosingMode(::java::lang::String* name, int ordinal);
protected:
	WindowClosingProtocol_WindowClosingMode(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static Enum* valueOf(Class* enumType, String* name);

private:
	virtual ::java::lang::Class* getClass0();
};
