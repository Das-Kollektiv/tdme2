// Generated from /tdme/src/tdme/gui/nodes/GUIParentNode.java
#include <tdme/gui/nodes/GUIParentNode_Overflow.h>

#include <string>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::wstring;

using tdme::gui::nodes::GUIParentNode_Overflow;
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
typedef ::SubArray< ::tdme::gui::nodes::GUIParentNode_Overflow, ::java::lang::EnumArray > GUIParentNode_OverflowArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

GUIParentNode_Overflow::GUIParentNode_Overflow(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIParentNode_Overflow::GUIParentNode_Overflow(const wstring& name, int ordinal)
	: GUIParentNode_Overflow(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

GUIParentNode_Overflow* tdme::gui::nodes::GUIParentNode_Overflow::HIDDEN = new GUIParentNode_Overflow(L"HIDDEN", 0);
GUIParentNode_Overflow* tdme::gui::nodes::GUIParentNode_Overflow::DOWNSIZE_CHILDREN = new GUIParentNode_Overflow(L"DOWNSIZE_CHILDREN", 1);
GUIParentNode_Overflow* tdme::gui::nodes::GUIParentNode_Overflow::SCROLL = new GUIParentNode_Overflow(L"SCROLL", 2);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIParentNode_Overflow::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIParentNode.Overflow", 37);
    return c;
}

GUIParentNode_Overflow* GUIParentNode_Overflow::valueOf(const wstring& a0)
{
	if (DOWNSIZE_CHILDREN->name() == a0) return DOWNSIZE_CHILDREN;
	if (HIDDEN->name() == a0) return HIDDEN;
	if (SCROLL->name() == a0) return SCROLL;
	// TODO: throw exception here maybe
	return nullptr;
}

GUIParentNode_OverflowArray* GUIParentNode_Overflow::values()
{
	return new GUIParentNode_OverflowArray({
		DOWNSIZE_CHILDREN,
		HIDDEN,
		SCROLL,
	});
}

java::lang::Class* GUIParentNode_Overflow::getClass0()
{
	return class_();
}

