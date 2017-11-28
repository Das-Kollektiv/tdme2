#include <tdme/tools/shared/model/LevelEditorEntityModel.h>

#include <tdme/engine/model/ModelHelper.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>

using tdme::engine::model::ModelHelper;
using tdme::tools::shared::model::LevelEditorEntityModel;
using tdme::tools::shared::model::LevelEditorEntity;

LevelEditorEntityModel::LevelEditorEntityModel(LevelEditorEntity* entity) {
	this->entity = entity;
	this->terrainMesh = false;
}

LevelEditorEntityModel::~LevelEditorEntityModel() {
}

LevelEditorEntity* LevelEditorEntityModel::getEntity() {
	return entity;
}

bool LevelEditorEntityModel::isTerrainMesh() {
	return terrainMesh;
}

void LevelEditorEntityModel::setTerrainMesh(bool terrainMesh) {
	this->terrainMesh = terrainMesh;
}
