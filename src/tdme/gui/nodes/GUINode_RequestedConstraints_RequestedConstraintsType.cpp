// Generated from /tdme/src/tdme/gui/nodes/GUINode.java
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
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
typedef ::SubArray< ::tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType, ::java::lang::EnumArray > GUINode_RequestedConstraints_RequestedConstraintsTypeArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

GUINode_RequestedConstraints_RequestedConstraintsType::GUINode_RequestedConstraints_RequestedConstraintsType(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUINode_RequestedConstraints_RequestedConstraintsType::GUINode_RequestedConstraints_RequestedConstraintsType(::java::lang::String* name, int ordinal)
	: GUINode_RequestedConstraints_RequestedConstraintsType(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

GUINode_RequestedConstraints_RequestedConstraintsType* tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL = new GUINode_RequestedConstraints_RequestedConstraintsType(u"PIXEL"_j, 0);
GUINode_RequestedConstraints_RequestedConstraintsType* tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType::PERCENT = new GUINode_RequestedConstraints_RequestedConstraintsType(u"PERCENT"_j, 1);
GUINode_RequestedConstraints_RequestedConstraintsType* tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType::STAR = new GUINode_RequestedConstraints_RequestedConstraintsType(u"STAR"_j, 2);
GUINode_RequestedConstraints_RequestedConstraintsType* tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType::AUTO = new GUINode_RequestedConstraints_RequestedConstraintsType(u"AUTO"_j, 3);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUINode_RequestedConstraints_RequestedConstraintsType::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUINode.RequestedConstraints.RequestedConstraintsType", 68);
    return c;
}

GUINode_RequestedConstraints_RequestedConstraintsType* GUINode_RequestedConstraints_RequestedConstraintsType::valueOf(String* a0)
{
	if (AUTO->toString()->equals(a0))
		return AUTO;
	if (PERCENT->toString()->equals(a0))
		return PERCENT;
	if (PIXEL->toString()->equals(a0))
		return PIXEL;
	if (STAR->toString()->equals(a0))
		return STAR;
	// TODO: throw exception here maybe
	return nullptr;
}

GUINode_RequestedConstraints_RequestedConstraintsTypeArray* GUINode_RequestedConstraints_RequestedConstraintsType::values()
{
	return new GUINode_RequestedConstraints_RequestedConstraintsTypeArray({
		AUTO,
		PERCENT,
		PIXEL,
		STAR,
	});
}

java::lang::Class* GUINode_RequestedConstraints_RequestedConstraintsType::getClass0()
{
	return class_();
}

