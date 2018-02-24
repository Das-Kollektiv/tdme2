#include <tdme/tools/shared/files/LevelFileImport.h>

#include <string>

#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/engine/ModelUtilities.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/subsystems/object/ModelStatistics.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>
#include <tdme/tools/shared/files/LevelFileExport.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/model/LevelEditorLight.h>
#include <tdme/tools/shared/model/LevelEditorObject.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/utils/Float.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/StringUtils.h>

#include <ext/jsonbox/Value.h>
#include <ext/jsonbox/Array.h>

using std::string;
using std::to_string;

using tdme::tools::shared::files::LevelFileImport;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::models::TMWriter;
using tdme::engine::ModelUtilities;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::UpVector;
using tdme::engine::subsystems::object::ModelStatistics;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::shared::files::LevelFileExport;
using tdme::tools::shared::files::ModelMetaDataFileImport;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::LevelEditorLight;
using tdme::tools::shared::model::LevelEditorObject;
using tdme::tools::shared::tools::Tools;
using tdme::utils::Float;
using tdme::utils::Console;
using tdme::utils::StringUtils;

using tdme::ext::jsonbox::Value;
using tdme::ext::jsonbox::Array;

void LevelFileImport::doImport(const string& pathName, const string& fileName, LevelEditorLevel* level) throw (FileSystemException, JsonException, ModelFileIOException)
{
	doImport(pathName, fileName, level, "");
}

void LevelFileImport::doImport(const string& pathName, const string& fileName, LevelEditorLevel* level, const string& objectIdPrefix) throw (FileSystemException, JsonException, ModelFileIOException)
{
	auto jsonContent = FileSystem::getInstance()->getContentAsString(pathName, fileName);

	Value jRoot;
	jRoot.loadFromString(jsonContent);

	level->setGameRoot(Tools::getGameRootPath(pathName));
	auto version = Float::parseFloat((jRoot["version"].getString()));
	level->setRotationOrder(jRoot["ro"].isNull() == false?RotationOrder::valueOf((jRoot["ro"].getString())) : RotationOrder::XYZ);
	level->clearProperties();
	auto jMapProperties = jRoot["properties"].getArray();
	for (auto i = 0; i < jMapProperties.size(); i++) {
		auto& jMapProperty = jMapProperties[i];
		level->addProperty(
			(jMapProperty["name"].getString()),
			(jMapProperty["value"].getString())
		);
	}
	if (jRoot["lights"].isNull() == false) {
		auto& jLights = jRoot["lights"].getArray();
		for (auto i = 0; i < jLights.size(); i++) {
			auto jLight = jLights[i];
			auto light = level->getLightAt(jLight["id"].isNull() == false? jLight["id"].getInt() : i);
			light->getAmbient().set(
				static_cast< float >(jLight["ar"].getDouble()),
				static_cast< float >(jLight["ag"].getDouble()),
				static_cast< float >(jLight["ab"].getDouble()),
				static_cast< float >(jLight["aa"].getDouble())
			);
			light->getDiffuse().set(
				static_cast< float >(jLight["dr"].getDouble()),
				static_cast< float >(jLight["dg"].getDouble()),
				static_cast< float >(jLight["db"].getDouble()),
				static_cast< float >(jLight["da"].getDouble())
			);
			light->getSpecular().set(
				static_cast< float >(jLight["sr"].getDouble()),
				static_cast< float >(jLight["sg"].getDouble()),
				static_cast< float >(jLight["sb"].getDouble()),
				static_cast< float >(jLight["sa"].getDouble())
			);
			light->getPosition().set(
				static_cast< float >(jLight["px"].getDouble()),
				static_cast< float >(jLight["py"].getDouble()),
				static_cast< float >(jLight["pz"].getDouble()),
				static_cast< float >(jLight["pw"].getDouble())
			);
			light->setConstantAttenuation(static_cast< float >(jLight["ca"].getDouble()));
			light->setLinearAttenuation(static_cast< float >(jLight["la"].getDouble()));
			light->setQuadraticAttenuation(static_cast< float >(jLight["qa"].getDouble()));
			light->getSpotTo().set(
				static_cast< float >(jLight["stx"].getDouble()),
				static_cast< float >(jLight["sty"].getDouble()),
				static_cast< float >(jLight["stz"].getDouble())
			);
			light->getSpotDirection().set(
				static_cast< float >(jLight["sdx"].getDouble()),
				static_cast< float >(jLight["sdy"].getDouble()),
				static_cast< float >(jLight["sdz"].getDouble())
			);
			light->setSpotExponent(static_cast< float >(jLight["se"].getDouble()));
			light->setSpotCutOff(static_cast< float >(jLight["sco"].getDouble()));
			light->setEnabled(jLight["e"].getBoolean());
		}
	}
	level->getEntityLibrary()->clear();
	auto jModels = jRoot["models"].getArray();
	for (auto i = 0; i < jModels.size(); i++) {
		auto jModel = jModels[i];
		LevelEditorEntity* levelEditorEntity = ModelMetaDataFileImport::doImportFromJSON(
			jModel["id"].getInt(),
			pathName,
			jModel["entity"]
		);
		if (levelEditorEntity == nullptr) {
			Console::println("LevelFileImport::doImport(): Invalid entity = " + to_string(jModel["id"].getInt()));
			continue;
		}
		level->getEntityLibrary()->addEntity(levelEditorEntity);
		if (jModel["properties"].isNull() == false) {
			auto jModelProperties = jModel["properties"].getArray();
			for (auto j = 0; j < jModelProperties.size(); j++) {
				auto jModelProperty = jModelProperties[j];
				levelEditorEntity->addProperty(
					(jModelProperty["name"].getString()),
					(jModelProperty["value"].getString())
				);
			}
		}
	}
	level->clearObjects();
	auto jObjects = jRoot["objects"].getArray();
	for (auto i = 0; i < jObjects.size(); i++) {
		auto& jObject = jObjects[i];
		auto model = level->getEntityLibrary()->getEntity(jObject["mid"].getInt());
		if (model == nullptr) {
			Console::println("LevelFileImport::doImport(): No entity found with id = " + to_string(jObject["mid"].getInt()));
			continue;
		}

		Transformations transformations;
		transformations.getPivot().set(model->getPivot());
		transformations.getTranslation().set(
			static_cast< float >(jObject["tx"].getDouble()),
			static_cast< float >(jObject["ty"].getDouble()),
			static_cast< float >(jObject["tz"].getDouble())
		);
		transformations.getScale().set(
			static_cast< float >(jObject["sx"].getDouble()),
			static_cast< float >(jObject["sy"].getDouble()),
			static_cast< float >(jObject["sz"].getDouble())
		);
		Vector3 rotation(
			static_cast< float >(jObject["rx"].getDouble()),
			static_cast< float >(jObject["ry"].getDouble()),
			static_cast< float >(jObject["rz"].getDouble())
		);
		transformations.getRotations()->add(new Rotation(rotation.getArray()[level->getRotationOrder()->getAxis0VectorIndex()], level->getRotationOrder()->getAxis0()));
		transformations.getRotations()->add(new Rotation(rotation.getArray()[level->getRotationOrder()->getAxis1VectorIndex()], level->getRotationOrder()->getAxis1()));
		transformations.getRotations()->add(new Rotation(rotation.getArray()[level->getRotationOrder()->getAxis2VectorIndex()], level->getRotationOrder()->getAxis2()));
		transformations.update();
		auto levelEditorObject = new LevelEditorObject(
			objectIdPrefix != "" ?
				objectIdPrefix + (jObject["id"].getString()) :
				(jObject["id"].getString()),
			 jObject["descr"].isNull() == false?(jObject["descr"].getString()) : "",
			 transformations,
			 model
		);
		if (jObject["properties"].isNull() == false) {
			auto jObjectProperties = jObject["properties"].getArray();
			for (auto j = 0; j < jObjectProperties.size(); j++) {
				auto jObjectProperty = jObjectProperties[j];
				levelEditorObject->addProperty(
					(jObjectProperty["name"].getString()),
					(jObjectProperty["value"].getString())
				);
			}
		}
		level->addObject(levelEditorObject);
	}
	level->setObjectIdx(jRoot["objects_eidx"].getInt());
	level->setPathName(pathName);
	level->setFileName(fileName);
	level->update();
}

void LevelFileImport::doImportFromModel(const string& pathName, const string& fileName, LevelEditorLevel* level) throw (FileSystemException, JsonException, ModelFileIOException) {
	level->clearProperties();
	level->getEntityLibrary()->clear();
	level->clearObjects();

	string modelPathName = pathName + "/" + fileName + "-models";
	if (FileSystem::getInstance()->fileExists(modelPathName)) {
		FileSystem::getInstance()->removePath(modelPathName);
	}
	FileSystem::getInstance()->createPath(modelPathName);

	auto levelModel = ModelReader::read(pathName, fileName);

	auto upVector = levelModel->getUpVector();
	RotationOrder* rotationOrder = levelModel->getRotationOrder();

	level->setRotationOrder(rotationOrder);

	auto entityLibrary = level->getEntityLibrary();
	auto groupIdx = 0;
	LevelEditorEntity* emptyEntity = nullptr;
	Matrix4x4 modelImportRotationMatrix;
	Vector3 levelModelScale;
	modelImportRotationMatrix.set(levelModel->getImportTransformationsMatrix());
	modelImportRotationMatrix.getScale(levelModelScale);
	modelImportRotationMatrix.scale(Vector3(1.0f / levelModelScale.getX(), 1.0f / levelModelScale.getY(), 1.0f / levelModelScale.getZ()));
	for (auto groupIt: *levelModel->getSubGroups()) {
		auto group = groupIt.second;
		auto groupId = groupIt.second->getId();
		auto modelName = groupId;
		modelName = StringUtils::replaceAll(modelName, "[-_]{1}[0-9]+$", "");
		modelName = StringUtils::replaceAll(modelName, "[0-9]+$", "");
		auto haveName = entityLibrary->getEntityCount() == 0;
		if (haveName == false) {
			for (auto i = 0; i < 10000; i++) {
				haveName = true;
				auto modelNameTry = modelName;
				if (i > 0) modelNameTry+= to_string(i);
				for (auto entityIdx = 0; entityIdx < entityLibrary->getEntityCount(); entityIdx++) {
					auto entity = entityLibrary->getEntityAt(entityIdx);
					if (entity->getName() == modelNameTry) {
						haveName = false;
						break;
					}
				}
				if (haveName == true) {
					modelName = modelNameTry;
					break;
				}
			}
		}
		if (haveName == false) {
			Console::println(
				string(
					"LevelFileImport::doImportFromModel(): Skipping model '" +
					modelName +
					"' as no name could be created for it."
				)
			 );
			continue;
		}
		auto model = new Model(
			modelPathName,
			fileName + "-" + modelName,
			upVector,
			rotationOrder,
			nullptr
		);
		model->getImportTransformationsMatrix().set(levelModel->getImportTransformationsMatrix());
		Vector3 translation, scale, rotation;
		Vector3 xAxis, yAxis, zAxis, tmpAxis;
		Matrix4x4 groupTransformationsMatrix;
		groupTransformationsMatrix.set(group->getTransformationsMatrix());
		groupTransformationsMatrix.getAxes(xAxis, yAxis, zAxis);
		groupTransformationsMatrix.getTranslation(translation);
		groupTransformationsMatrix.getScale(scale);
		xAxis.normalize();
		yAxis.normalize();
		zAxis.normalize();
		groupTransformationsMatrix.setAxes(xAxis, yAxis, zAxis);
		if ((upVector == UpVector::Y_UP && Vector3::computeDotProduct(Vector3::computeCrossProduct(xAxis, yAxis, tmpAxis), zAxis) < 0.0f) ||
			(upVector == UpVector::Z_UP && Vector3::computeDotProduct(Vector3::computeCrossProduct(xAxis, zAxis, tmpAxis), yAxis) < 0.0f)) {
			xAxis.scale(-1.0f);
			yAxis.scale(-1.0f);
			zAxis.scale(-1.0f);
			groupTransformationsMatrix.setAxes(xAxis, yAxis, zAxis);
			scale.scale(-1.0f);
		}
		groupTransformationsMatrix.computeEulerAngles(rotation);
		modelImportRotationMatrix.multiply(scale, scale);
		modelImportRotationMatrix.multiply(rotation, rotation);
		model->getImportTransformationsMatrix().multiply(translation, translation);
		ModelHelper::cloneGroup(group, model);
		if (model->getSubGroups()->begin() != model->getSubGroups()->end()) {
			model->getSubGroups()->begin()->second->getTransformationsMatrix().identity();
		}
		model->addAnimationSetup(Model::ANIMATIONSETUP_DEFAULT, 0, 0, true);
		ModelHelper::prepareForIndexedRendering(model);
		auto entityType = LevelEditorEntity_EntityType::MODEL;
		ModelStatistics modelStatistics;
		ModelUtilities::computeModelStatistics(model, &modelStatistics);
		if (modelStatistics.opaqueFaceCount == 0 && modelStatistics.transparentFaceCount == 0) {
			entityType = LevelEditorEntity_EntityType::EMPTY;
		}
		LevelEditorEntity* levelEditorEntity = nullptr;
		if (entityType == LevelEditorEntity_EntityType::MODEL) {
			for (auto i = 0; i < level->getEntityLibrary()->getEntityCount(); i++) {
				auto levelEditorEntityCompare = level->getEntityLibrary()->getEntityAt(i);
				if (levelEditorEntityCompare->getType() != LevelEditorEntity_EntityType::MODEL)
					continue;

				if (ModelUtilities::equals(model, levelEditorEntityCompare->getModel()) == true) {
					levelEditorEntity = levelEditorEntityCompare;
					delete model;
					break;
				}
			}
			if (levelEditorEntity == nullptr) {
				auto modelFileName = modelName + ".tm";
				TMWriter::write(
					model,
					modelPathName,
					modelFileName
				  );
				levelEditorEntity = entityLibrary->addModel(
					groupIdx++,
					modelName,
					modelName,
					modelPathName,
					modelFileName,
					Vector3()
				);
			}
		} else
		if (entityType == LevelEditorEntity_EntityType::EMPTY) {
			if (emptyEntity == nullptr) {
				emptyEntity = entityLibrary->addEmpty(groupIdx++, "Default Empty", "");
			}
			levelEditorEntity = emptyEntity;
		} else {
			Console::println(string("DAEReader::readLevel(): unknown entity type. Skipping"));
			continue;
		}
		Transformations levelEditorObjectTransformations;
		levelEditorObjectTransformations.getTranslation().set(translation);
		levelEditorObjectTransformations.getRotations()->add(new Rotation(rotation.getArray()[rotationOrder->getAxis0VectorIndex()], rotationOrder->getAxis0()));
		levelEditorObjectTransformations.getRotations()->add(new Rotation(rotation.getArray()[rotationOrder->getAxis1VectorIndex()], rotationOrder->getAxis1()));
		levelEditorObjectTransformations.getRotations()->add(new Rotation(rotation.getArray()[rotationOrder->getAxis2VectorIndex()], rotationOrder->getAxis2()));
		levelEditorObjectTransformations.getScale().set(scale);
		levelEditorObjectTransformations.update();
		auto object = new LevelEditorObject(
			groupId,
			groupId,
			levelEditorObjectTransformations,
			levelEditorEntity
		);
		level->addObject(object);
	}
	LevelFileExport::export_(
		pathName,
		fileName + ".tl",
		level
	);
}
