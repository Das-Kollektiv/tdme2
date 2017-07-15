// Generated from /tdme/src/tdme/gui/nodes/GUINode.java
#include <tdme/gui/nodes/GUINode_Flow.h>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::gui::nodes::GUINode_Flow;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::Enum;
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
typedef ::SubArray< ::tdme::gui::nodes::GUINode_Flow, ::java::lang::EnumArray > GUINode_FlowArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

GUINode_Flow::GUINode_Flow(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUINode_Flow::GUINode_Flow(::java::lang::String* name, int ordinal)
	: GUINode_Flow(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

GUINode_Flow* tdme::gui::nodes::GUINode_Flow::INTEGRATED = new GUINode_Flow(u"INTEGRATED"_j, 0);
GUINode_Flow* tdme::gui::nodes::GUINode_Flow::FLOATING = new GUINode_Flow(u"FLOATING"_j, 1);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUINode_Flow::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUINode.Flow", 27);
    return c;
}

GUINode_Flow* GUINode_Flow::valueOf(String* a0)
{
	if (FLOATING->toString()->equals(a0))
		return FLOATING;
	if (INTEGRATED->toString()->equals(a0))
		return INTEGRATED;
	// TODO: throw exception here maybe
	return nullptr;
}

GUINode_FlowArray* GUINode_Flow::values()
{
	return new GUINode_FlowArray({
		FLOATING,
		INTEGRATED,
	});
}

java::lang::Class* GUINode_Flow::getClass0()
{
	return class_();
}

