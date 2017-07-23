// Generated from /tdme/src/tdme/gui/nodes/GUIHorizontalScrollbarInternalController.java

#pragma once

#include <string>

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <java/lang/Enum.h>

using std::wstring;

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::String;
using tdme::gui::nodes::GUIHorizontalScrollbarInternalController;
using java::lang::Object;
using tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State;

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
typedef ::SubArray< ::tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State, ::java::lang::EnumArray > GUIHorizontalScrollbarInternalController_StateArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::gui::nodes::GUIHorizontalScrollbarInternalController_StateArray;

struct default_init_tag;
class tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static GUIHorizontalScrollbarInternalController_State *NONE;
	static GUIHorizontalScrollbarInternalController_State *MOUSEOVER;
	static GUIHorizontalScrollbarInternalController_State *DRAGGING;

	// Generated

public:
	GUIHorizontalScrollbarInternalController_State(const wstring& name, int ordinal);
protected:
	GUIHorizontalScrollbarInternalController_State(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static GUIHorizontalScrollbarInternalController_State* valueOf(const wstring& a0);
	static GUIHorizontalScrollbarInternalController_StateArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUIHorizontalScrollbarInternalController;
};
