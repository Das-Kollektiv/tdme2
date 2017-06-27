// Generated from /tdme/src/tdme/gui/nodes/GUIVerticalScrollbarInternalController.java
#include <tdme/gui/nodes/GUIVerticalScrollbarInternalController_State.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/IllegalArgumentException.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::gui::nodes::GUIVerticalScrollbarInternalController_State;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::Comparable;
using java::lang::Enum;
using java::lang::IllegalArgumentException;
using java::lang::String;

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

GUIVerticalScrollbarInternalController_State::GUIVerticalScrollbarInternalController_State(::java::lang::String* name, int ordinal)
	: GUIVerticalScrollbarInternalController_State(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

GUIVerticalScrollbarInternalController_State* tdme::gui::nodes::GUIVerticalScrollbarInternalController_State::NONE = new GUIVerticalScrollbarInternalController_State(u"NONE"_j, 0);
GUIVerticalScrollbarInternalController_State* tdme::gui::nodes::GUIVerticalScrollbarInternalController_State::MOUSEOVER = new GUIVerticalScrollbarInternalController_State(u"MOUSEOVER"_j, 1);
GUIVerticalScrollbarInternalController_State* tdme::gui::nodes::GUIVerticalScrollbarInternalController_State::DRAGGING = new GUIVerticalScrollbarInternalController_State(u"DRAGGING"_j, 2);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIVerticalScrollbarInternalController_State::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIVerticalScrollbarInternalController.State", 59);
    return c;
}

GUIVerticalScrollbarInternalController_State* GUIVerticalScrollbarInternalController_State::valueOf(String* a0)
{
	if (DRAGGING->toString()->equals(a0))
		return DRAGGING;
	if (MOUSEOVER->toString()->equals(a0))
		return MOUSEOVER;
	if (NONE->toString()->equals(a0))
		return NONE;
	throw new IllegalArgumentException(a0);
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

