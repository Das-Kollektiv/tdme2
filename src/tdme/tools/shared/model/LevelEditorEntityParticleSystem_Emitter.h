
#pragma once

#include <string>

#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/utils/Enum.h>

using std::string;

using tdme::utils::Enum;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;

class tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter final
	: public Enum
{
	friend class LevelEditorEntityParticleSystem;
	friend class LevelEditorEntityParticleSystem_Type;
	friend class LevelEditorEntityParticleSystem_ObjectParticleSystem;
	friend class LevelEditorEntityParticleSystem_PointParticleSystem;
	friend class LevelEditorEntityParticleSystem_PointParticleEmitter;
	friend class LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitter;
	friend class LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
	friend class LevelEditorEntityParticleSystem_SphereParticleEmitter;

public:
	static LevelEditorEntityParticleSystem_Emitter *NONE;
	static LevelEditorEntityParticleSystem_Emitter *POINT_PARTICLE_EMITTER;
	static LevelEditorEntityParticleSystem_Emitter *BOUNDINGBOX_PARTICLE_EMITTER;
	static LevelEditorEntityParticleSystem_Emitter *CIRCLE_PARTICLE_EMITTER;
	static LevelEditorEntityParticleSystem_Emitter *CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY;
	static LevelEditorEntityParticleSystem_Emitter *SPHERE_PARTICLE_EMITTER;
	LevelEditorEntityParticleSystem_Emitter(const string& name, int ordinal);
	static LevelEditorEntityParticleSystem_Emitter* valueOf(const string& a0);
};
