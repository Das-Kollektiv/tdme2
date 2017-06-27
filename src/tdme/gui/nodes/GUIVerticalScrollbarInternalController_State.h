// Generated from /tdme/src/tdme/gui/nodes/GUIVerticalScrollbarInternalController.java

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <java/lang/Enum.h>

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::String;
using tdme::gui::nodes::GUIVerticalScrollbarInternalController;
using java::lang::Object;
using tdme::gui::nodes::GUIVerticalScrollbarInternalController_State;

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
typedef ::SubArray< ::tdme::gui::nodes::GUIVerticalScrollbarInternalController_State, ::java::lang::EnumArray > GUIVerticalScrollbarInternalController_StateArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::gui::nodes::GUIVerticalScrollbarInternalController_StateArray;

struct default_init_tag;
class tdme::gui::nodes::GUIVerticalScrollbarInternalController_State final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static GUIVerticalScrollbarInternalController_State *NONE;
	static GUIVerticalScrollbarInternalController_State *MOUSEOVER;
	static GUIVerticalScrollbarInternalController_State *DRAGGING;

	// Generated

public:
	GUIVerticalScrollbarInternalController_State(::java::lang::String* name, int ordinal);
protected:
	GUIVerticalScrollbarInternalController_State(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static GUIVerticalScrollbarInternalController_State* valueOf(String* a0);
	static GUIVerticalScrollbarInternalController_StateArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUIVerticalScrollbarInternalController;
};
