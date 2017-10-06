#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::utils::Enum;

LevelEditorEntity_EntityType::LevelEditorEntity_EntityType(const wstring& name, int ordinal): Enum(name, ordinal)
{
}

LevelEditorEntity_EntityType* tdme::tools::shared::model::LevelEditorEntity_EntityType::TRIGGER = new LevelEditorEntity_EntityType(L"TRIGGER", 0);
LevelEditorEntity_EntityType* tdme::tools::shared::model::LevelEditorEntity_EntityType::MODEL = new LevelEditorEntity_EntityType(L"MODEL", 1);
LevelEditorEntity_EntityType* tdme::tools::shared::model::LevelEditorEntity_EntityType::EMPTY = new LevelEditorEntity_EntityType(L"EMPTY", 2);
LevelEditorEntity_EntityType* tdme::tools::shared::model::LevelEditorEntity_EntityType::PARTICLESYSTEM = new LevelEditorEntity_EntityType(L"PARTICLESYSTEM", 3);

LevelEditorEntity_EntityType* LevelEditorEntity_EntityType::valueOf(const wstring& a0)
{
	if (EMPTY->getName() == a0) return EMPTY;
	if (MODEL->getName() == a0) return MODEL;
	if (PARTICLESYSTEM->getName() == a0) return PARTICLESYSTEM;
	if (TRIGGER->getName() == a0) return TRIGGER;
	// TODO: throw exception here maybe
	return nullptr;
}
