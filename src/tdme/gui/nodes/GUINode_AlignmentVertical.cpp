// Generated from /tdme/src/tdme/gui/nodes/GUINode.java
#include <tdme/gui/nodes/GUINode_AlignmentVertical.h>

#include <string>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::wstring;

using tdme::gui::nodes::GUINode_AlignmentVertical;
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
typedef ::SubArray< ::tdme::gui::nodes::GUINode_AlignmentVertical, ::java::lang::EnumArray > GUINode_AlignmentVerticalArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

GUINode_AlignmentVertical::GUINode_AlignmentVertical(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUINode_AlignmentVertical::GUINode_AlignmentVertical(const wstring& name, int ordinal)
	: GUINode_AlignmentVertical(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

GUINode_AlignmentVertical* tdme::gui::nodes::GUINode_AlignmentVertical::TOP = new GUINode_AlignmentVertical(L"TOP", 0);
GUINode_AlignmentVertical* tdme::gui::nodes::GUINode_AlignmentVertical::CENTER = new GUINode_AlignmentVertical(L"CENTER", 1);
GUINode_AlignmentVertical* tdme::gui::nodes::GUINode_AlignmentVertical::BOTTOM = new GUINode_AlignmentVertical(L"BOTTOM", 2);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUINode_AlignmentVertical::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUINode.AlignmentVertical", 40);
    return c;
}

GUINode_AlignmentVertical* GUINode_AlignmentVertical::valueOf(const wstring& a0)
{
	if (BOTTOM->name() == a0) return BOTTOM;
	if (CENTER->name() == a0) return CENTER;
	if (TOP->name() == a0) return TOP;
	// TODO: throw exception here maybe
	return nullptr;
}

GUINode_AlignmentVerticalArray* GUINode_AlignmentVertical::values()
{
	return new GUINode_AlignmentVerticalArray({
		BOTTOM,
		CENTER,
		TOP,
	});
}

java::lang::Class* GUINode_AlignmentVertical::getClass0()
{
	return class_();
}

