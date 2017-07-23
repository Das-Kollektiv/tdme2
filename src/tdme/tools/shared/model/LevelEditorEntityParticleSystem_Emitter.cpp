// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.java
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_Emitter.h>

#include <string>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::wstring;

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;
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
typedef ::SubArray< ::tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter, ::java::lang::EnumArray > LevelEditorEntityParticleSystem_EmitterArray;
}  // namespace model
}  // namespace shared
}  // namespace tools
}  // namespace tdme

LevelEditorEntityParticleSystem_Emitter::LevelEditorEntityParticleSystem_Emitter(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelEditorEntityParticleSystem_Emitter::LevelEditorEntityParticleSystem_Emitter(const wstring& name, int ordinal)
	: LevelEditorEntityParticleSystem_Emitter(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

LevelEditorEntityParticleSystem_Emitter* tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter::NONE = new LevelEditorEntityParticleSystem_Emitter(L"NONE", 0);
LevelEditorEntityParticleSystem_Emitter* tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER = new LevelEditorEntityParticleSystem_Emitter(L"POINT_PARTICLE_EMITTER", 1);
LevelEditorEntityParticleSystem_Emitter* tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER = new LevelEditorEntityParticleSystem_Emitter(L"BOUNDINGBOX_PARTICLE_EMITTER", 2);
LevelEditorEntityParticleSystem_Emitter* tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER = new LevelEditorEntityParticleSystem_Emitter(L"CIRCLE_PARTICLE_EMITTER", 3);
LevelEditorEntityParticleSystem_Emitter* tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY = new LevelEditorEntityParticleSystem_Emitter(L"CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY", 4);
LevelEditorEntityParticleSystem_Emitter* tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER = new LevelEditorEntityParticleSystem_Emitter(L"SPHERE_PARTICLE_EMITTER", 5);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorEntityParticleSystem_Emitter::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.LevelEditorEntityParticleSystem.Emitter", 63);
    return c;
}

LevelEditorEntityParticleSystem_Emitter* LevelEditorEntityParticleSystem_Emitter::valueOf(const wstring& a0)
{
	if (BOUNDINGBOX_PARTICLE_EMITTER->name() == a0) return BOUNDINGBOX_PARTICLE_EMITTER;
	if (CIRCLE_PARTICLE_EMITTER->name() == a0) return CIRCLE_PARTICLE_EMITTER;
	if (CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY->name() == a0) return CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY;
	if (NONE->name() == a0) return NONE;
	if (POINT_PARTICLE_EMITTER->name() == a0) return POINT_PARTICLE_EMITTER;
	if (SPHERE_PARTICLE_EMITTER->name() == a0) return SPHERE_PARTICLE_EMITTER;
	// TODO: throw exception here maybe
	return nullptr;
}

LevelEditorEntityParticleSystem_EmitterArray* LevelEditorEntityParticleSystem_Emitter::values()
{
	return new LevelEditorEntityParticleSystem_EmitterArray({
		BOUNDINGBOX_PARTICLE_EMITTER,
		CIRCLE_PARTICLE_EMITTER,
		CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY,
		NONE,
		POINT_PARTICLE_EMITTER,
		SPHERE_PARTICLE_EMITTER,
	});
}

java::lang::Class* LevelEditorEntityParticleSystem_Emitter::getClass0()
{
	return class_();
}

