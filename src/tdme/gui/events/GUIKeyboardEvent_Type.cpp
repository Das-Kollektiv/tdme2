// Generated from /tdme/src/tdme/gui/events/GUIKeyboardEvent.java
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::gui::events::GUIKeyboardEvent_Type;
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
typedef ::SubArray< ::tdme::gui::events::GUIKeyboardEvent_Type, ::java::lang::EnumArray > GUIKeyboardEvent_TypeArray;
}  // namespace events
}  // namespace gui
}  // namespace tdme

GUIKeyboardEvent_Type::GUIKeyboardEvent_Type(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIKeyboardEvent_Type::GUIKeyboardEvent_Type(const wstring& name, int ordinal)
	: GUIKeyboardEvent_Type(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

GUIKeyboardEvent_Type* tdme::gui::events::GUIKeyboardEvent_Type::NONE = new GUIKeyboardEvent_Type(L"NONE", 0);
GUIKeyboardEvent_Type* tdme::gui::events::GUIKeyboardEvent_Type::KEY_PRESSED = new GUIKeyboardEvent_Type(L"KEY_PRESSED", 1);
GUIKeyboardEvent_Type* tdme::gui::events::GUIKeyboardEvent_Type::KEY_RELEASED = new GUIKeyboardEvent_Type(L"KEY_RELEASED", 2);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIKeyboardEvent_Type::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.events.GUIKeyboardEvent.Type", 37);
    return c;
}

GUIKeyboardEvent_Type* GUIKeyboardEvent_Type::valueOf(const wstring& a0)
{
	if (KEY_PRESSED->name() == a0) return KEY_PRESSED;
	if (KEY_RELEASED->name() == a0) return KEY_RELEASED;
	if (NONE->name() == a0) return NONE;
	// TODO: throw exception here maybe
	return nullptr;
}

GUIKeyboardEvent_TypeArray* GUIKeyboardEvent_Type::values()
{
	return new GUIKeyboardEvent_TypeArray({
		KEY_PRESSED,
		KEY_RELEASED,
		NONE,
	});
}

java::lang::Class* GUIKeyboardEvent_Type::getClass0()
{
	return class_();
}

