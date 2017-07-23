// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.java

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
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;
using java::lang::Object;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type;

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

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_TypeArray;

struct default_init_tag;
class tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static LevelEditorEntityParticleSystem_Type *NONE;
	static LevelEditorEntityParticleSystem_Type *OBJECT_PARTICLE_SYSTEM;
	static LevelEditorEntityParticleSystem_Type *POINT_PARTICLE_SYSTEM;

	// Generated

public:
	LevelEditorEntityParticleSystem_Type(const wstring& name, int ordinal);
protected:
	LevelEditorEntityParticleSystem_Type(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static LevelEditorEntityParticleSystem_Type* valueOf(const wstring& a0);
	static LevelEditorEntityParticleSystem_TypeArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class LevelEditorEntityParticleSystem;
	friend class LevelEditorEntityParticleSystem_ObjectParticleSystem;
	friend class LevelEditorEntityParticleSystem_PointParticleSystem;
	friend class LevelEditorEntityParticleSystem_Emitter;
	friend class LevelEditorEntityParticleSystem_PointParticleEmitter;
	friend class LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
	friend class LevelEditorEntityParticleSystem_SphereParticleEmitter;
};
