#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_ObjectParticleSystem.h>

#include <string>

#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/utils/ExceptionBase.h>
#include <tdme/utils/StringUtils.h>

using std::string;

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::model::Model;
using tdme::math::Vector3;
using tdme::tools::shared::tools::Tools;
using tdme::utils::ExceptionBase;
using tdme::utils::StringUtils;

LevelEditorEntityParticleSystem_ObjectParticleSystem::LevelEditorEntityParticleSystem_ObjectParticleSystem() 
{
	scale.set(1.0f, 1.0f, 1.0f);
	maxCount = 10;
	autoEmit = true;
	model = nullptr;
	modelFileName = "";
}

LevelEditorEntityParticleSystem_ObjectParticleSystem::~LevelEditorEntityParticleSystem_ObjectParticleSystem() {
	if (model != nullptr) delete model;
}

Vector3& LevelEditorEntityParticleSystem_ObjectParticleSystem::getScale()
{
	return scale;
}

int32_t LevelEditorEntityParticleSystem_ObjectParticleSystem::getMaxCount()
{
	return maxCount;
}

void LevelEditorEntityParticleSystem_ObjectParticleSystem::setMaxCount(int32_t maxCount)
{
	this->maxCount = maxCount;
}

bool LevelEditorEntityParticleSystem_ObjectParticleSystem::isAutoEmit()
{
	return autoEmit;
}

void LevelEditorEntityParticleSystem_ObjectParticleSystem::setAutoEmit(bool autoEmit)
{
	this->autoEmit = autoEmit;
}

Model* LevelEditorEntityParticleSystem_ObjectParticleSystem::getModel()
{
	return model;
}

void LevelEditorEntityParticleSystem_ObjectParticleSystem::setModel(Model* model)
{
	this->model = model;
}

const string& LevelEditorEntityParticleSystem_ObjectParticleSystem::getModelFile()
{
	return modelFileName;
}

void LevelEditorEntityParticleSystem_ObjectParticleSystem::setModelFile(const string& modelFileName) /* throws(Exception) */
{
	this->modelFileName = modelFileName;
	model = ModelReader::read(
		Tools::getPath(modelFileName),
		Tools::getFileName(modelFileName)
	);
}

