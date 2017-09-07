// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.java
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_ObjectParticleSystem.h>

#include <string>

#include <tdme/engine/fileio/models/DAEReader.h>
#include <tdme/engine/fileio/models/TMReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_ExceptionBase.h>
#include <tdme/utils/StringUtils.h>

using std::wstring;

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem;
using tdme::engine::fileio::models::DAEReader;
using tdme::engine::fileio::models::TMReader;
using tdme::engine::model::Model;
using tdme::math::Vector3;
using tdme::tools::shared::tools::Tools;
using tdme::utils::StringConverter;
using tdme::utils::_ExceptionBase;
using tdme::utils::StringUtils;

LevelEditorEntityParticleSystem_ObjectParticleSystem::LevelEditorEntityParticleSystem_ObjectParticleSystem() 
{
	scale.set(1.0f, 1.0f, 1.0f);
	maxCount = 10;
	autoEmit = true;
	model = nullptr;
	modelFileName = L"";
}

Vector3* LevelEditorEntityParticleSystem_ObjectParticleSystem::getScale()
{
	return &scale;
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

const wstring& LevelEditorEntityParticleSystem_ObjectParticleSystem::getModelFile()
{
	return modelFileName;
}

void LevelEditorEntityParticleSystem_ObjectParticleSystem::setModelFile(const wstring& modelFileName) /* throws(Exception) */
{
	this->modelFileName = modelFileName;
	if (StringUtils::endsWith(StringUtils::toLowerCase(modelFileName), L".tm") == true) {
		model = TMReader::read(
			Tools::getPath(modelFileName),
			Tools::getFileName(modelFileName)
		);
	} else
	if (StringUtils::endsWith(StringUtils::toLowerCase(modelFileName), L".dae") == true) {
		model = DAEReader::read(
			Tools::getPath(modelFileName),
			Tools::getFileName(modelFileName)
		);
	} else {
		throw new _ExceptionBase(
			string("LevelEditorEntityParticleSystem::ObjectParticleSystem::setModelFileName(): unsupported model '") +
			StringConverter::toString(modelFileName)
		);
	}
}

