// Generated from /tdme/src/tdme/gui/nodes/GUIVerticalScrollbarInternalController.java
#include <tdme/gui/nodes/GUIVerticalScrollbarInternalController_State.h>

#include <string>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::wstring;

using tdme::gui::nodes::GUIVerticalScrollbarInternalController_State;
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
typedef ::SubArray< ::tdme::gui::nodes::GUIVerticalScrollbarInternalController_State, ::java::lang::EnumArray > GUIVerticalScrollbarInternalController_StateArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

GUIVerticalScrollbarInternalController_State::GUIVerticalScrollbarInternalController_State(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIVerticalScrollbarInternalController_State::GUIVerticalScrollbarInternalController_State(const wstring& name, int ordinal)
	: GUIVerticalScrollbarInternalController_State(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

GUIVerticalScrollbarInternalController_State* tdme::gui::nodes::GUIVerticalScrollbarInternalController_State::NONE = new GUIVerticalScrollbarInternalController_State(L"NONE", 0);
GUIVerticalScrollbarInternalController_State* tdme::gui::nodes::GUIVerticalScrollbarInternalController_State::MOUSEOVER = new GUIVerticalScrollbarInternalController_State(L"MOUSEOVER", 1);
GUIVerticalScrollbarInternalController_State* tdme::gui::nodes::GUIVerticalScrollbarInternalController_State::DRAGGING = new GUIVerticalScrollbarInternalController_State(L"DRAGGING", 2);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIVerticalScrollbarInternalController_State::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIVerticalScrollbarInternalController.State", 59);
    return c;
}

GUIVerticalScrollbarInternalController_State* GUIVerticalScrollbarInternalController_State::valueOf(const wstring& a0)
{
	if (DRAGGING->name() == a0) return DRAGGING;
	if (MOUSEOVER->name() == a0) return MOUSEOVER;
	if (NONE->name() == a0) return NONE;
	// TODO: throw exception here maybe
	return nullptr;
}

GUIVerticalScrollbarInternalController_StateArray* GUIVerticalScrollbarInternalController_State::values()
{
	return new GUIVerticalScrollbarInternalController_StateArray({
		DRAGGING,
		MOUSEOVER,
		NONE,
	});
}

java::lang::Class* GUIVerticalScrollbarInternalController_State::getClass0()
{
	return class_();
}

