// Generated from /tdme/src/tdme/gui/nodes/GUINode.java
#include <tdme/gui/nodes/GUINode_AlignmentHorizontal.h>

#include <string>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::wstring;

using tdme::gui::nodes::GUINode_AlignmentHorizontal;
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
typedef ::SubArray< ::tdme::gui::nodes::GUINode_AlignmentHorizontal, ::java::lang::EnumArray > GUINode_AlignmentHorizontalArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

GUINode_AlignmentHorizontal::GUINode_AlignmentHorizontal(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUINode_AlignmentHorizontal::GUINode_AlignmentHorizontal(const wstring& name, int ordinal)
	: GUINode_AlignmentHorizontal(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

GUINode_AlignmentHorizontal* tdme::gui::nodes::GUINode_AlignmentHorizontal::LEFT = new GUINode_AlignmentHorizontal(L"LEFT", 0);
GUINode_AlignmentHorizontal* tdme::gui::nodes::GUINode_AlignmentHorizontal::CENTER = new GUINode_AlignmentHorizontal(L"CENTER", 1);
GUINode_AlignmentHorizontal* tdme::gui::nodes::GUINode_AlignmentHorizontal::RIGHT = new GUINode_AlignmentHorizontal(L"RIGHT", 2);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUINode_AlignmentHorizontal::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUINode.AlignmentHorizontal", 42);
    return c;
}

GUINode_AlignmentHorizontal* GUINode_AlignmentHorizontal::valueOf(const wstring& a0)
{
	if (CENTER->name() == a0) return CENTER;
	if (LEFT->name() == a0) return LEFT;
	if (RIGHT->name() == a0) return RIGHT;
	// TODO: throw exception here maybe
	return nullptr;
}

GUINode_AlignmentHorizontalArray* GUINode_AlignmentHorizontal::values()
{
	return new GUINode_AlignmentHorizontalArray({
		CENTER,
		LEFT,
		RIGHT,
	});
}

java::lang::Class* GUINode_AlignmentHorizontal::getClass0()
{
	return class_();
}

