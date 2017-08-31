// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorEntityParticleSystem.java
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_ObjectParticleSystem.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/fileio/models/DAEReader.h>
#include <tdme/engine/fileio/models/TMReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_ExceptionBase.h>

using tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::fileio::models::DAEReader;
using tdme::engine::fileio::models::TMReader;
using tdme::engine::model::Model;
using tdme::math::Vector3;
using tdme::tools::shared::tools::Tools;
using tdme::utils::StringConverter;
using tdme::utils::_ExceptionBase;

LevelEditorEntityParticleSystem_ObjectParticleSystem::LevelEditorEntityParticleSystem_ObjectParticleSystem() 
{
	scale = new Vector3(1.0f, 1.0f, 1.0f);
	maxCount = 10;
	autoEmit = true;
	model = nullptr;
	modelFileName = u""_j;
}

Vector3* LevelEditorEntityParticleSystem_ObjectParticleSystem::getScale()
{
	return scale;
}

void LevelEditorEntityParticleSystem_ObjectParticleSystem::setScale(Vector3* scale)
{
	this->scale = scale;
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

String* LevelEditorEntityParticleSystem_ObjectParticleSystem::getModelFile()
{
	return modelFileName;
}

void LevelEditorEntityParticleSystem_ObjectParticleSystem::setModelFile(String* modelFileName) /* throws(Exception) */
{
	this->modelFileName = modelFileName;
	if (modelFileName->toLowerCase()->endsWith(u".tm"_j)) {
		model = TMReader::read(Tools::getPath(modelFileName), Tools::getFileName(modelFileName));
	} else
	if (modelFileName->toLowerCase()->endsWith(u".dae"_j)) {
		model = DAEReader::read(Tools::getPath(modelFileName), Tools::getFileName(modelFileName));
	} else {
		throw new _ExceptionBase(
			string("LevelEditorEntityParticleSystem::ObjectParticleSystem::setModelFileName(): unsupported model '") +
			StringConverter::toString(modelFileName->getCPPWString())
		);
	}
}

