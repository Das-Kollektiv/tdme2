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

void LevelEditorEntityParticleSystem_ObjectParticleSystem::setModelFile(const string& modelFileName) /* throws(Exception) */
{
	this->modelFileName = modelFileName;
	model = ModelReader::read(
		Tools::getPath(modelFileName),
		Tools::getFileName(modelFileName)
	);
}

LevelEditorEntityParticleSystem_ObjectParticleSystem::~LevelEditorEntityParticleSystem_ObjectParticleSystem() {
	if (model != nullptr) delete model;
}
