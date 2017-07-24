// Generated from /tdme/src/tdme/engine/model/ModelHelper.java

#pragma once

#include <string>

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <java/lang/Enum.h>

using std::wstring;

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Comparable;
using tdme::engine::model::ModelHelper;
using java::lang::Object;
using tdme::engine::model::ModelHelper_VertexOrder;

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
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::ModelHelper_VertexOrder, ::java::lang::EnumArray > ModelHelper_VertexOrderArray;
}  // namespace model
}  // namespace engine
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::engine::model::ModelHelper_VertexOrderArray;

struct default_init_tag;
class tdme::engine::model::ModelHelper_VertexOrder final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static ModelHelper_VertexOrder *CLOCKWISE;
	static ModelHelper_VertexOrder *COUNTERCLOCKWISE;

	// Generated

public:
	ModelHelper_VertexOrder(const wstring& name, int ordinal);
protected:
	ModelHelper_VertexOrder(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static ModelHelper_VertexOrder* valueOf(const wstring& a0);
	static ModelHelper_VertexOrderArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class ModelHelper;
};
