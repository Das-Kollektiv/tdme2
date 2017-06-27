// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.java

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <java/lang/Enum.h>

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::String;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;
using java::lang::Object;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;

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

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_EmitterArray;

struct default_init_tag;
class tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static LevelEditorEntityParticleSystem_Emitter *NONE;
	static LevelEditorEntityParticleSystem_Emitter *POINT_PARTICLE_EMITTER;
	static LevelEditorEntityParticleSystem_Emitter *BOUNDINGBOX_PARTICLE_EMITTER;
	static LevelEditorEntityParticleSystem_Emitter *CIRCLE_PARTICLE_EMITTER;
	static LevelEditorEntityParticleSystem_Emitter *CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY;
	static LevelEditorEntityParticleSystem_Emitter *SPHERE_PARTICLE_EMITTER;

	// Generated

public:
	LevelEditorEntityParticleSystem_Emitter(::java::lang::String* name, int ordinal);
protected:
	LevelEditorEntityParticleSystem_Emitter(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static LevelEditorEntityParticleSystem_Emitter* valueOf(String* a0);
	static LevelEditorEntityParticleSystem_EmitterArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class LevelEditorEntityParticleSystem;
	friend class LevelEditorEntityParticleSystem_Type;
	friend class LevelEditorEntityParticleSystem_ObjectParticleSystem;
	friend class LevelEditorEntityParticleSystem_PointParticleSystem;
	friend class LevelEditorEntityParticleSystem_PointParticleEmitter;
	friend class LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
	friend class LevelEditorEntityParticleSystem_SphereParticleEmitter;
};
