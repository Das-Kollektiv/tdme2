// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntity.java
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/IllegalArgumentException.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::Comparable;
using java::lang::Enum;
using java::lang::IllegalArgumentException;
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
namespace tools {
namespace shared {
namespace model {
typedef ::SubArray< ::tdme::tools::shared::model::LevelEditorEntity_EntityType, ::java::lang::EnumArray > LevelEditorEntity_EntityTypeArray;
}  // namespace model
}  // namespace shared
}  // namespace tools
}  // namespace tdme

LevelEditorEntity_EntityType::LevelEditorEntity_EntityType(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelEditorEntity_EntityType::LevelEditorEntity_EntityType(::java::lang::String* name, int ordinal)
	: LevelEditorEntity_EntityType(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

LevelEditorEntity_EntityType* tdme::tools::shared::model::LevelEditorEntity_EntityType::TRIGGER = new LevelEditorEntity_EntityType(u"TRIGGER"_j, 0);
LevelEditorEntity_EntityType* tdme::tools::shared::model::LevelEditorEntity_EntityType::MODEL = new LevelEditorEntity_EntityType(u"MODEL"_j, 1);
LevelEditorEntity_EntityType* tdme::tools::shared::model::LevelEditorEntity_EntityType::EMPTY = new LevelEditorEntity_EntityType(u"EMPTY"_j, 2);
LevelEditorEntity_EntityType* tdme::tools::shared::model::LevelEditorEntity_EntityType::PARTICLESYSTEM = new LevelEditorEntity_EntityType(u"PARTICLESYSTEM"_j, 3);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorEntity_EntityType::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.LevelEditorEntity.EntityType", 52);
    return c;
}

LevelEditorEntity_EntityType* LevelEditorEntity_EntityType::valueOf(String* a0)
{
	if (EMPTY->toString()->equals(a0))
		return EMPTY;
	if (MODEL->toString()->equals(a0))
		return MODEL;
	if (PARTICLESYSTEM->toString()->equals(a0))
		return PARTICLESYSTEM;
	if (TRIGGER->toString()->equals(a0))
		return TRIGGER;
	throw new IllegalArgumentException(a0);
}

LevelEditorEntity_EntityTypeArray* LevelEditorEntity_EntityType::values()
{
	return new LevelEditorEntity_EntityTypeArray({
		EMPTY,
		MODEL,
		PARTICLESYSTEM,
		TRIGGER,
	});
}

java::lang::Class* LevelEditorEntity_EntityType::getClass0()
{
	return class_();
}

