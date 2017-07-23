// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntity.java

#pragma once

#include <string>

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <java/lang/Enum.h>

using std::wstring;

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::String;
using tdme::tools::shared::model::LevelEditorEntity;
using java::lang::Object;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;

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
namespace tools {
namespace shared {
namespace model {
typedef ::SubArray< ::tdme::tools::shared::model::LevelEditorEntity_EntityType, ::java::lang::EnumArray > LevelEditorEntity_EntityTypeArray;
}  // namespace model
}  // namespace shared
}  // namespace tools
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::tools::shared::model::LevelEditorEntity_EntityTypeArray;

struct default_init_tag;
class tdme::tools::shared::model::LevelEditorEntity_EntityType final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static LevelEditorEntity_EntityType *TRIGGER;
	static LevelEditorEntity_EntityType *MODEL;
	static LevelEditorEntity_EntityType *EMPTY;
	static LevelEditorEntity_EntityType *PARTICLESYSTEM;

	// Generated

public:
	LevelEditorEntity_EntityType(const wstring& name, int ordinal);
protected:
	LevelEditorEntity_EntityType(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static LevelEditorEntity_EntityType* valueOf(const wstring& a0);
	static LevelEditorEntity_EntityTypeArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class LevelEditorEntity;
};
