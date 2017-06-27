// Generated from /tdme/src/tdme/gui/events/GUIActionListener.java
#include <tdme/gui/events/GUIActionListener_Type.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/IllegalArgumentException.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::gui::events::GUIActionListener_Type;
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
namespace events {
typedef ::SubArray< ::tdme::gui::events::GUIActionListener_Type, ::java::lang::EnumArray > GUIActionListener_TypeArray;
}  // namespace events
}  // namespace gui
}  // namespace tdme

GUIActionListener_Type::GUIActionListener_Type(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIActionListener_Type::GUIActionListener_Type(::java::lang::String* name, int ordinal)
	: GUIActionListener_Type(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

GUIActionListener_Type* tdme::gui::events::GUIActionListener_Type::PERFORMED = new GUIActionListener_Type(u"PERFORMED"_j, 0);
GUIActionListener_Type* tdme::gui::events::GUIActionListener_Type::PERFORMING = new GUIActionListener_Type(u"PERFORMING"_j, 1);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIActionListener_Type::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.events.GUIActionListener.Type", 38);
    return c;
}

GUIActionListener_Type* GUIActionListener_Type::valueOf(String* a0)
{
	if (PERFORMED->toString()->equals(a0))
		return PERFORMED;
	if (PERFORMING->toString()->equals(a0))
		return PERFORMING;
	throw new IllegalArgumentException(a0);
}

GUIActionListener_TypeArray* GUIActionListener_Type::values()
{
	return new GUIActionListener_TypeArray({
		PERFORMED,
		PERFORMING,
	});
}

java::lang::Class* GUIActionListener_Type::getClass0()
{
	return class_();
}

