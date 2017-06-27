// Generated from /tdme/src/tdme/gui/nodes/GUIInputInternalController.java

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <java/lang/Enum.h>

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::String;
using tdme::gui::nodes::GUIInputInternalController;
using java::lang::Object;
using tdme::gui::nodes::GUIInputInternalController_CursorMode;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::Enum, ObjectArray, ComparableArray, ::java::io::SerializableArray > EnumArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace gui {
namespace nodes {
typedef ::SubArray< ::tdme::gui::nodes::GUIInputInternalController_CursorMode, ::java::lang::EnumArray > GUIInputInternalController_CursorModeArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::gui::nodes::GUIInputInternalController_CursorModeArray;

struct default_init_tag;
class tdme::gui::nodes::GUIInputInternalController_CursorMode final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static GUIInputInternalController_CursorMode *SHOW;
	static GUIInputInternalController_CursorMode *HIDE;

	// Generated

public:
	GUIInputInternalController_CursorMode(::java::lang::String* name, int ordinal);
protected:
	GUIInputInternalController_CursorMode(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static GUIInputInternalController_CursorMode* valueOf(String* a0);
	static GUIInputInternalController_CursorModeArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUIInputInternalController;
};
