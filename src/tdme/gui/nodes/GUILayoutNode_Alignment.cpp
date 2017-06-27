// Generated from /tdme/src/tdme/gui/nodes/GUILayoutNode.java
#include <tdme/gui/nodes/GUILayoutNode_Alignment.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/IllegalArgumentException.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::gui::nodes::GUILayoutNode_Alignment;
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
typedef ::SubArray< ::tdme::gui::nodes::GUILayoutNode_Alignment, ::java::lang::EnumArray > GUILayoutNode_AlignmentArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

GUILayoutNode_Alignment::GUILayoutNode_Alignment(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUILayoutNode_Alignment::GUILayoutNode_Alignment(::java::lang::String* name, int ordinal)
	: GUILayoutNode_Alignment(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

GUILayoutNode_Alignment* tdme::gui::nodes::GUILayoutNode_Alignment::VERTICAL = new GUILayoutNode_Alignment(u"VERTICAL"_j, 0);
GUILayoutNode_Alignment* tdme::gui::nodes::GUILayoutNode_Alignment::HORIZONTAL = new GUILayoutNode_Alignment(u"HORIZONTAL"_j, 1);
GUILayoutNode_Alignment* tdme::gui::nodes::GUILayoutNode_Alignment::NONE = new GUILayoutNode_Alignment(u"NONE"_j, 2);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUILayoutNode_Alignment::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUILayoutNode.Alignment", 38);
    return c;
}

GUILayoutNode_Alignment* GUILayoutNode_Alignment::valueOf(String* a0)
{
	if (HORIZONTAL->toString()->equals(a0))
		return HORIZONTAL;
	if (NONE->toString()->equals(a0))
		return NONE;
	if (VERTICAL->toString()->equals(a0))
		return VERTICAL;
	throw new IllegalArgumentException(a0);
}

GUILayoutNode_AlignmentArray* GUILayoutNode_Alignment::values()
{
	return new GUILayoutNode_AlignmentArray({
		HORIZONTAL,
		NONE,
		VERTICAL,
	});
}

java::lang::Class* GUILayoutNode_Alignment::getClass0()
{
	return class_();
}

