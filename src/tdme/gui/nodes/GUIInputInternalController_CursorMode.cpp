// Generated from /tdme/src/tdme/gui/nodes/GUIInputInternalController.java
#include <tdme/gui/nodes/GUIInputInternalController_CursorMode.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/IllegalArgumentException.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::gui::nodes::GUIInputInternalController_CursorMode;
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
typedef ::SubArray< ::tdme::gui::nodes::GUIInputInternalController_CursorMode, ::java::lang::EnumArray > GUIInputInternalController_CursorModeArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

GUIInputInternalController_CursorMode::GUIInputInternalController_CursorMode(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIInputInternalController_CursorMode::GUIInputInternalController_CursorMode(::java::lang::String* name, int ordinal)
	: GUIInputInternalController_CursorMode(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

GUIInputInternalController_CursorMode* tdme::gui::nodes::GUIInputInternalController_CursorMode::SHOW = new GUIInputInternalController_CursorMode(u"SHOW"_j, 0);
GUIInputInternalController_CursorMode* tdme::gui::nodes::GUIInputInternalController_CursorMode::HIDE = new GUIInputInternalController_CursorMode(u"HIDE"_j, 1);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIInputInternalController_CursorMode::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIInputInternalController.CursorMode", 52);
    return c;
}

GUIInputInternalController_CursorMode* GUIInputInternalController_CursorMode::valueOf(String* a0)
{
	if (HIDE->toString()->equals(a0))
		return HIDE;
	if (SHOW->toString()->equals(a0))
		return SHOW;
	throw new IllegalArgumentException(a0);
}

GUIInputInternalController_CursorModeArray* GUIInputInternalController_CursorMode::values()
{
	return new GUIInputInternalController_CursorModeArray({
		HIDE,
		SHOW,
	});
}

java::lang::Class* GUIInputInternalController_CursorMode::getClass0()
{
	return class_();
}

