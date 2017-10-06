
#pragma once

#include <string>

#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::utils::Enum;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type;

class tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type final
	: public Enum
{
	friend class LevelEditorEntityParticleSystem;
	friend class LevelEditorEntityParticleSystem_ObjectParticleSystem;
	friend class LevelEditorEntityParticleSystem_PointParticleSystem;
	friend class LevelEditorEntityParticleSystem_Emitter;
	friend class LevelEditorEntityParticleSystem_PointParticleEmitter;
	friend class LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
	friend class LevelEditorEntityParticleSystem_SphereParticleEmitter;

public:
	static LevelEditorEntityParticleSystem_Type *NONE;
	static LevelEditorEntityParticleSystem_Type *OBJECT_PARTICLE_SYSTEM;
	static LevelEditorEntityParticleSystem_Type *POINT_PARTICLE_SYSTEM;
	LevelEditorEntityParticleSystem_Type(const wstring& name, int ordinal);
	static LevelEditorEntityParticleSystem_Type* valueOf(const wstring& a0);

};
