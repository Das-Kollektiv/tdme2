// Generated from /tdme/src/tdme/gui/nodes/GUILayoutNode.java

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
using tdme::gui::nodes::GUILayoutNode;
using java::lang::Object;
using tdme::gui::nodes::GUILayoutNode_Alignment;

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

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::gui::nodes::GUILayoutNode_AlignmentArray;

struct default_init_tag;
class tdme::gui::nodes::GUILayoutNode_Alignment final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static GUILayoutNode_Alignment *VERTICAL;
	static GUILayoutNode_Alignment *HORIZONTAL;
	static GUILayoutNode_Alignment *NONE;

	// Generated

public:
	GUILayoutNode_Alignment(const wstring& name, int ordinal);
protected:
	GUILayoutNode_Alignment(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static GUILayoutNode_Alignment* valueOf(const wstring& a0);
	static GUILayoutNode_AlignmentArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUILayoutNode;
};
