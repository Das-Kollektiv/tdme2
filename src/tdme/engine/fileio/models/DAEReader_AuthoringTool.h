
#pragma once

#include <string>

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <java/lang/Enum.h>

using std::wstring;

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Comparable;
using tdme::engine::fileio::models::DAEReader;
using java::lang::Object;
using tdme::engine::fileio::models::DAEReader_AuthoringTool;

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
namespace fileio {
namespace models {
typedef ::SubArray< ::tdme::engine::fileio::models::DAEReader_AuthoringTool, ::java::lang::EnumArray > DAEReader_AuthoringToolArray;
}  // namespace models
}  // namespace fileio
}  // namespace engine
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::engine::fileio::models::DAEReader_AuthoringToolArray;

struct default_init_tag;
class tdme::engine::fileio::models::DAEReader_AuthoringTool final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static DAEReader_AuthoringTool *UNKNOWN;
	static DAEReader_AuthoringTool *BLENDER;

	// Generated

public:
	DAEReader_AuthoringTool(const wstring& name, int ordinal);
protected:
	DAEReader_AuthoringTool(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static DAEReader_AuthoringTool* valueOf(const wstring& a0);
	static DAEReader_AuthoringToolArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class DAEReader;
	friend class DAEReader_determineDisplacementFilename_1;
};
