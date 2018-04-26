#include <tdme/tools/shared/model/LevelEditorEntityLODLevel.h>

#include <string>

#include <tdme/engine/LODObject3D.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Color4.h>

using tdme::tools::shared::model::LevelEditorEntityLODLevel;

using std::string;

using tdme::engine::LODObject3D;
using tdme::engine::model::Model;
using tdme::engine::model::Color4;

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
	colorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	colorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
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

const Color4& LevelEditorEntityLODLevel::getColorAdd() const {
	return colorAdd;
}

void LevelEditorEntityLODLevel::setColorAdd(const Color4& colorAdd) {
	this->colorAdd = colorAdd;
}

const Color4& LevelEditorEntityLODLevel::getColorMul() const {
	return colorMul;
}

void LevelEditorEntityLODLevel::setColorMul(const Color4& colorMul) {
	this->colorMul = colorMul;
}
