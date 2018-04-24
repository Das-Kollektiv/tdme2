#include <tdme/tools/shared/model/LevelEditorEntityLODLevel.h>

#include <string>

#include <tdme/engine/LODObject3D.h>
#include <tdme/engine/model/Model.h>

using tdme::tools::shared::model::LevelEditorEntityLODLevel;

using std::string;

using tdme::engine::LODObject3D;
using tdme::engine::model::Model;

LevelEditorEntityLODLevel::LevelEditorEntityLODLevel(
	LODObject3D::LODLevelType type,
	const string& fileName,
	Model* model,
	float minDistance,
	float planeRotationY
) :
	type(type),
	fileName(fileName),
	model(model),
	minDistance(minDistance),
	planeRotationY(planeRotationY) {

}

LevelEditorEntityLODLevel::~LevelEditorEntityLODLevel() {
	if (model != nullptr) delete model;
}

const string& LevelEditorEntityLODLevel::getFileName() {
	return fileName;
}

void LevelEditorEntityLODLevel::setFileName(const string& fileName) {
	this->fileName = fileName;
}

Model* LevelEditorEntityLODLevel::getModel() {
	return model;
}

void LevelEditorEntityLODLevel::setModel(Model* model) {
	if (this->model != nullptr) delete this->model;
	this->model = model;
}

float LevelEditorEntityLODLevel::getMinDistance() const {
	return minDistance;
}

void LevelEditorEntityLODLevel::setMinDistance(float minDistance) {
	this->minDistance = minDistance;
}

float LevelEditorEntityLODLevel::getPlaneRotationY() const {
	return planeRotationY;
}

void LevelEditorEntityLODLevel::setPlaneRotationY(float planeRotationY) {
	this->planeRotationY = planeRotationY;
}

LODObject3D::LODLevelType LevelEditorEntityLODLevel::getType() const {
	return type;
}

void LevelEditorEntityLODLevel::setType(LODObject3D::LODLevelType type) {
	this->type = type;
}
