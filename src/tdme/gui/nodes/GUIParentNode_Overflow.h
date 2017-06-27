// Generated from /tdme/src/tdme/gui/nodes/GUIParentNode.java

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <java/lang/Enum.h>

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::String;
using tdme::gui::nodes::GUIParentNode;
using java::lang::Object;
using tdme::gui::nodes::GUIParentNode_Overflow;

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

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::gui::nodes::GUIParentNode_OverflowArray;

struct default_init_tag;
class tdme::gui::nodes::GUIParentNode_Overflow final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static GUIParentNode_Overflow *HIDDEN;
	static GUIParentNode_Overflow *DOWNSIZE_CHILDREN;
	static GUIParentNode_Overflow *SCROLL;

	// Generated

public:
	GUIParentNode_Overflow(::java::lang::String* name, int ordinal);
protected:
	GUIParentNode_Overflow(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static GUIParentNode_Overflow* valueOf(String* a0);
	static GUIParentNode_OverflowArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUIParentNode;
};
