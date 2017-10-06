
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
using tdme::engine::model::Model;
using java::lang::Object;
using tdme::engine::model::Model_UpVector;

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
typedef ::SubArray< ::tdme::engine::model::Model_UpVector, ::java::lang::EnumArray > Model_UpVectorArray;
}  // namespace model
}  // namespace engine
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::engine::model::Model_UpVectorArray;

struct default_init_tag;
class tdme::engine::model::Model_UpVector final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static Model_UpVector *Y_UP;
	static Model_UpVector *Z_UP;

	// Generated

public:
	Model_UpVector(const wstring& name, int ordinal);
protected:
	Model_UpVector(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static Model_UpVector* valueOf(const wstring& a0);
	static Model_UpVectorArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class Model;
};
