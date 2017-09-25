// Generated from /tdme/src/tdme/gui/nodes/GUIHorizontalScrollbarInternalController.java
#include <tdme/gui/nodes/GUIHorizontalScrollbarInternalController_State.h>

#include <string>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::wstring;

using tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::Enum;

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

GUIHorizontalScrollbarInternalController_State::GUIHorizontalScrollbarInternalController_State(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIHorizontalScrollbarInternalController_State::GUIHorizontalScrollbarInternalController_State(const wstring& name, int ordinal)
	: GUIHorizontalScrollbarInternalController_State(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

GUIHorizontalScrollbarInternalController_State* tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State::NONE = new GUIHorizontalScrollbarInternalController_State(L"NONE", 0);
GUIHorizontalScrollbarInternalController_State* tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State::MOUSEOVER = new GUIHorizontalScrollbarInternalController_State(L"MOUSEOVER", 1);
GUIHorizontalScrollbarInternalController_State* tdme::gui::nodes::GUIHorizontalScrollbarInternalController_State::DRAGGING = new GUIHorizontalScrollbarInternalController_State(L"DRAGGING", 2);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIHorizontalScrollbarInternalController_State::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIHorizontalScrollbarInternalController.State", 61);
    return c;
}

GUIHorizontalScrollbarInternalController_State* GUIHorizontalScrollbarInternalController_State::valueOf(const wstring& a0)
{
	if (DRAGGING->name() == a0) return DRAGGING;
	if (MOUSEOVER->name() == a0) return MOUSEOVER;
	if (NONE->name() == a0) return NONE;
	// TODO: throw exception here maybe
	return nullptr;
}

GUIHorizontalScrollbarInternalController_StateArray* GUIHorizontalScrollbarInternalController_State::values()
{
	return new GUIHorizontalScrollbarInternalController_StateArray({
		DRAGGING,
		MOUSEOVER,
		NONE,
	});
}

java::lang::Class* GUIHorizontalScrollbarInternalController_State::getClass0()
{
	return class_();
}

