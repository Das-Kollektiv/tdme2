// Generated from /tdme/src/tdme/gui/events/GUIMouseEvent.java
#include <tdme/gui/events/GUIMouseEvent_Type.h>

#include <string>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::wstring;

using tdme::gui::events::GUIMouseEvent_Type;
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
namespace events {
typedef ::SubArray< ::tdme::gui::events::GUIMouseEvent_Type, ::java::lang::EnumArray > GUIMouseEvent_TypeArray;
}  // namespace events
}  // namespace gui
}  // namespace tdme

GUIMouseEvent_Type::GUIMouseEvent_Type(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIMouseEvent_Type::GUIMouseEvent_Type(const wstring& name, int ordinal)
	: GUIMouseEvent_Type(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

GUIMouseEvent_Type* tdme::gui::events::GUIMouseEvent_Type::NONE = new GUIMouseEvent_Type(L"NONE", 0);
GUIMouseEvent_Type* tdme::gui::events::GUIMouseEvent_Type::MOUSE_WHEEL_MOVED = new GUIMouseEvent_Type(L"MOUSE_WHEEL_MOVED", 1);
GUIMouseEvent_Type* tdme::gui::events::GUIMouseEvent_Type::MOUSE_PRESSED = new GUIMouseEvent_Type(L"MOUSE_PRESSED", 2);
GUIMouseEvent_Type* tdme::gui::events::GUIMouseEvent_Type::MOUSE_RELEASED = new GUIMouseEvent_Type(L"MOUSE_RELEASED", 3);
GUIMouseEvent_Type* tdme::gui::events::GUIMouseEvent_Type::MOUSE_MOVED = new GUIMouseEvent_Type(L"MOUSE_MOVED", 4);
GUIMouseEvent_Type* tdme::gui::events::GUIMouseEvent_Type::MOUSE_DRAGGED = new GUIMouseEvent_Type(L"MOUSE_DRAGGED", 5);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIMouseEvent_Type::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.events.GUIMouseEvent.Type", 34);
    return c;
}

GUIMouseEvent_Type* GUIMouseEvent_Type::valueOf(const wstring& a0)
{
	if (MOUSE_DRAGGED->name() == a0) return MOUSE_DRAGGED;
	if (MOUSE_MOVED->name() == a0) return MOUSE_MOVED;
	if (MOUSE_PRESSED->name() == a0) return MOUSE_PRESSED;
	if (MOUSE_RELEASED->name() == a0) return MOUSE_RELEASED;
	if (MOUSE_WHEEL_MOVED->name() == a0) return MOUSE_WHEEL_MOVED;
	if (NONE->name() == a0) return NONE;
	// TODO: throw exception here maybe
	return nullptr;
}

GUIMouseEvent_TypeArray* GUIMouseEvent_Type::values()
{
	return new GUIMouseEvent_TypeArray({
		MOUSE_DRAGGED,
		MOUSE_MOVED,
		MOUSE_PRESSED,
		MOUSE_RELEASED,
		MOUSE_WHEEL_MOVED,
		NONE,
	});
}

java::lang::Class* GUIMouseEvent_Type::getClass0()
{
	return class_();
}

