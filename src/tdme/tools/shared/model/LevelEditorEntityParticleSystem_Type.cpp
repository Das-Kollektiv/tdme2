#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_Type.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type;
using tdme::utils::Enum;

LevelEditorEntityParticleSystem_Type::LevelEditorEntityParticleSystem_Type(const wstring& name, int ordinal)
	: Enum(name, ordinal)
{
}

LevelEditorEntityParticleSystem_Type* tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type::NONE = new LevelEditorEntityParticleSystem_Type(L"NONE", 0);
LevelEditorEntityParticleSystem_Type* tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM = new LevelEditorEntityParticleSystem_Type(L"OBJECT_PARTICLE_SYSTEM", 1);
LevelEditorEntityParticleSystem_Type* tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM = new LevelEditorEntityParticleSystem_Type(L"POINT_PARTICLE_SYSTEM", 2);

LevelEditorEntityParticleSystem_Type* LevelEditorEntityParticleSystem_Type::valueOf(const wstring& a0)
{
	if (NONE->getName() == a0) return NONE;
	if (OBJECT_PARTICLE_SYSTEM->getName() == a0) return OBJECT_PARTICLE_SYSTEM;
	if (POINT_PARTICLE_SYSTEM->getName() == a0) return POINT_PARTICLE_SYSTEM;
	// TODO: throw exception here maybe
	return nullptr;
}
