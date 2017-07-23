// Generated from /tdme/src/tdme/gui/nodes/GUINode.java

#pragma once

#include <string>

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <java/lang/Enum.h>

using std::wstring;

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::String;
using tdme::gui::nodes::GUINode_AlignmentHorizontal;
using tdme::gui::nodes::GUINode_AlignmentVertical;
using tdme::gui::nodes::GUINode_Alignments;
using tdme::gui::nodes::GUINode_Border;
using tdme::gui::nodes::GUINode_ComputedConstraints;
using tdme::gui::nodes::GUINode_Flow;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode;
using java::lang::Object;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;

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

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsTypeArray;

struct default_init_tag;
class tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static GUINode_RequestedConstraints_RequestedConstraintsType *PIXEL;
	static GUINode_RequestedConstraints_RequestedConstraintsType *PERCENT;
	static GUINode_RequestedConstraints_RequestedConstraintsType *STAR;
	static GUINode_RequestedConstraints_RequestedConstraintsType *AUTO;

	// Generated

public:
	GUINode_RequestedConstraints_RequestedConstraintsType(const wstring& name, int ordinal);
protected:
	GUINode_RequestedConstraints_RequestedConstraintsType(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static GUINode_RequestedConstraints_RequestedConstraintsType* valueOf(const wstring& a0);
	static GUINode_RequestedConstraints_RequestedConstraintsTypeArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUINode;
	friend class GUINode_Flow;
	friend class GUINode_AlignmentHorizontal;
	friend class GUINode_AlignmentVertical;
	friend class GUINode_Alignments;
	friend class GUINode_RequestedConstraints;
	friend class GUINode_ComputedConstraints;
	friend class GUINode_Padding;
	friend class GUINode_Border;
};
