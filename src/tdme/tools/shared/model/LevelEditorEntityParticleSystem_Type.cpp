// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.java
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_Type.h>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type;
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
namespace tools {
namespace shared {
namespace model {
typedef ::SubArray< ::tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type, ::java::lang::EnumArray > LevelEditorEntityParticleSystem_TypeArray;
}  // namespace model
}  // namespace shared
}  // namespace tools
}  // namespace tdme

LevelEditorEntityParticleSystem_Type::LevelEditorEntityParticleSystem_Type(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelEditorEntityParticleSystem_Type::LevelEditorEntityParticleSystem_Type(::java::lang::String* name, int ordinal)
	: LevelEditorEntityParticleSystem_Type(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

LevelEditorEntityParticleSystem_Type* tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type::NONE = new LevelEditorEntityParticleSystem_Type(u"NONE"_j, 0);
LevelEditorEntityParticleSystem_Type* tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM = new LevelEditorEntityParticleSystem_Type(u"OBJECT_PARTICLE_SYSTEM"_j, 1);
LevelEditorEntityParticleSystem_Type* tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM = new LevelEditorEntityParticleSystem_Type(u"POINT_PARTICLE_SYSTEM"_j, 2);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorEntityParticleSystem_Type::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.LevelEditorEntityParticleSystem.Type", 60);
    return c;
}

LevelEditorEntityParticleSystem_Type* LevelEditorEntityParticleSystem_Type::valueOf(String* a0)
{
	if (NONE->toString()->equals(a0))
		return NONE;
	if (OBJECT_PARTICLE_SYSTEM->toString()->equals(a0))
		return OBJECT_PARTICLE_SYSTEM;
	if (POINT_PARTICLE_SYSTEM->toString()->equals(a0))
		return POINT_PARTICLE_SYSTEM;
	// TODO: throw exception here maybe
	return nullptr;
}

LevelEditorEntityParticleSystem_TypeArray* LevelEditorEntityParticleSystem_Type::values()
{
	return new LevelEditorEntityParticleSystem_TypeArray({
		NONE,
		OBJECT_PARTICLE_SYSTEM,
		POINT_PARTICLE_SYSTEM,
	});
}

java::lang::Class* LevelEditorEntityParticleSystem_Type::getClass0()
{
	return class_();
}

