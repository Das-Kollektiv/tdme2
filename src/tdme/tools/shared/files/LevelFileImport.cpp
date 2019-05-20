#include <tdme/tools/shared/files/LevelFileImport.h>

#include <string>

#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/engine/ModelUtilities.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/subsystems/rendering/ModelStatistics.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>
#include <tdme/tools/shared/files/LevelFileExport.h>
#include <tdme/tools/shared/files/ProgressCallback.h>
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
using tdme::engine::Transformations;
using tdme::engine::model::Animation;
using tdme::engine::model::Color4;
using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::UpVector;
using tdme::engine::subsystems::rendering::ModelStatistics;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::shared::files::LevelFileExport;
using tdme::tools::shared::files::ModelMetaDataFileImport;
using tdme::tools::shared::files::ProgressCallback;
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

void LevelFileImport::doImport(const string& pathName, const string& fileName, LevelEditorLevel* level, ProgressCallback* progressCallback) throw (FileSystemException, JsonException, ModelFileIOException)
{
	doImport(pathName, fileName, level, "", progressCallback);
}

void LevelFileImport::doImport(const string& pathName, const string& fileName, LevelEditorLevel* level, const string& objectIdPrefix, ProgressCallback* progressCallback) throw (FileSystemException, JsonException, ModelFileIOException)
{
	if (progressCallback != nullptr) progressCallback->progress(0.0f);

	auto jsonContent = FileSystem::getInstance()->getContentAsString(pathName, fileName);
	if (progressCallback != nullptr) progressCallback->progress(0.165f);

	Value jRoot;
	jRoot.loadFromString(jsonContent);
	if (progressCallback != nullptr) progressCallback->progress(0.33f);

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
	auto jObjects = jRoot["objects"].getArray();
	auto progressStepCount =  + jObjects.size();
	auto progressStepCurrent = 0;

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

		if (progressCallback != nullptr) progressCallback->progress(0.33f + static_cast<float>(progressStepCurrent) / static_cast<float>(jModels.size()) * 0.33f);
		progressStepCurrent++;
	}
	level->clearObjects();

	for (auto i = 0; i < jObjects.size(); i++) {
		auto& jObject = jObjects[i];
		auto model = level->getEntityLibrary()->getEntity(jObject["mid"].getInt());
		if (model == nullptr) {
			Console::println("LevelFileImport::doImport(): No entity found with id = " + to_string(jObject["mid"].getInt()));

			if (progressCallback != nullptr && progressStepCurrent % 1000 == 0) progressCallback->progress(0.66f + static_cast<float>(progressStepCurrent) / static_cast<float>(jObjects.size()) * 0.33f);
			progressStepCurrent++;

			continue;
		}

		Transformations transformations;
		transformations.setPivot(model->getPivot());
		transformations.setTranslation(
			Vector3(
				static_cast< float >(jObject["tx"].getDouble()),
				static_cast< float >(jObject["ty"].getDouble()),
				static_cast< float >(jObject["tz"].getDouble())
			)
		);
		transformations.setScale(
			Vector3(
				static_cast< float >(jObject["sx"].getDouble()),
				static_cast< float >(jObject["sy"].getDouble()),
				static_cast< float >(jObject["sz"].getDouble())
			)
		);
		Vector3 rotation(
			static_cast< float >(jObject["rx"].getDouble()),
			static_cast< float >(jObject["ry"].getDouble()),
			static_cast< float >(jObject["rz"].getDouble())
		);
		transformations.addRotation(level->getRotationOrder()->getAxis0(), rotation.getArray()[level->getRotationOrder()->getAxis0VectorIndex()]);
		transformations.addRotation(level->getRotationOrder()->getAxis1(), rotation.getArray()[level->getRotationOrder()->getAxis1VectorIndex()]);
		transformations.addRotation(level->getRotationOrder()->getAxis2(), rotation.getArray()[level->getRotationOrder()->getAxis2VectorIndex()]);
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

		if (progressCallback != nullptr && progressStepCurrent % 1000 == 0) progressCallback->progress(0.66f + static_cast<float>(progressStepCurrent) / static_cast<float>(jObjects.size()) * 0.33f);
		progressStepCurrent++;
	}
	level->setObjectIdx(jRoot["objects_eidx"].getInt());
	level->setPathName(pathName);
	level->setFileName(fileName);
	level->update();

	if (progressCallback != nullptr) {
		progressCallback->progress(1.0f);
		delete progressCallback;
	}
}

void LevelFileImport::determineMeshGroups(LevelEditorLevel* level, Group* group, const string& parentName, const Matrix4x4& parentTransformationsMatrix, vector<LevelEditorEntityMeshGroup>& meshGroups) {
	auto entityLibrary = level->getEntityLibrary();
	auto groupId = group->getId();
	if (parentName.length() > 0) groupId = parentName + "." + groupId;
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
		return;
	}
	Matrix4x4 transformationsMatrix;
	// compute animation matrix if animation setups exist
	auto animation = group->getAnimation();
	if (animation != nullptr) {
		auto animationMatrices = animation->getTransformationsMatrices();
		transformationsMatrix.set((*animationMatrices)[0 % animationMatrices->size()]);
	} else {
		// no animation matrix, set up local transformation matrix up as group matrix
		transformationsMatrix.set(group->getTransformationsMatrix());
	}

	// apply parent transformation matrix
	transformationsMatrix.multiply(parentTransformationsMatrix);

	// check if no mesh?
	if (group->getVertices()->size() == 0 && group->getSubGroups()->size() > 0) {
		// ok, check sub meshes
		for (auto subGroupIt: *group->getSubGroups()) {
			determineMeshGroups(level, subGroupIt.second, groupId, transformationsMatrix.clone(), meshGroups);
		}
	} else {
		// add to group meshes, even if empty as its a empty :D
		LevelEditorEntityMeshGroup levelEditorEntityMeshGroup;
		levelEditorEntityMeshGroup.id = groupId;
		levelEditorEntityMeshGroup.name = modelName;
		levelEditorEntityMeshGroup.group = group;
		levelEditorEntityMeshGroup.transformationsMatrix.set(transformationsMatrix);
		meshGroups.push_back(levelEditorEntityMeshGroup);
	}
}

void LevelFileImport::doImportFromModel(const string& pathName, const string& fileName, LevelEditorLevel* level, ProgressCallback* progressCallback) throw (FileSystemException, JsonException, ModelFileIOException) {
	if (progressCallback != nullptr) progressCallback->progress(0.0f);

	level->clearProperties();
	level->getEntityLibrary()->clear();
	level->clearObjects();

	string modelPathName = pathName + "/" + fileName + "-models";
	if (FileSystem::getInstance()->fileExists(modelPathName)) {
		FileSystem::getInstance()->removePath(modelPathName);
	}
	FileSystem::getInstance()->createPath(modelPathName);

	auto levelModel = ModelReader::read(pathName, fileName);

	if (progressCallback != nullptr) progressCallback->progress(0.1f);

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
	Console::println(to_string(levelModel->getSubGroups()->size()));
	auto progressTotal = levelModel->getSubGroups()->size();
	auto progressIdx = 0;
	for (auto groupIt: *levelModel->getSubGroups()) {
		if (progressCallback != nullptr) progressCallback->progress(0.1f + static_cast<float>(progressIdx) / static_cast<float>(progressTotal) * 0.8f);
		vector<LevelEditorEntityMeshGroup> meshGroups;
		determineMeshGroups(level, groupIt.second, "", (Matrix4x4()).identity(), meshGroups);
		for (auto& meshGroup: meshGroups) {
			auto model = new Model(
				modelPathName,
				fileName + "-" + meshGroup.name,
				upVector,
				rotationOrder,
				nullptr
			);
			model->getImportTransformationsMatrix().set(levelModel->getImportTransformationsMatrix());
			float importFixScale = 1.0f;
			Vector3 translation, scale, rotation;
			Vector3 xAxis, yAxis, zAxis, tmpAxis;
			Matrix4x4 groupTransformationsMatrix;
			groupTransformationsMatrix.set(meshGroup.transformationsMatrix);
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

			ModelHelper::cloneGroup(meshGroup.group, model);
			if (model->getSubGroups()->begin() != model->getSubGroups()->end()) {
				model->getSubGroups()->begin()->second->getTransformationsMatrix().identity();
			}
			model->addAnimationSetup(Model::ANIMATIONSETUP_DEFAULT, 0, 0, true);
			ModelHelper::prepareForIndexedRendering(model);
			// scale up model if dimension too less, this occurres with importing FBX that was exported by UE
			// TODO: maybe make this conditional
			{
				auto width = model->getBoundingBox()->getDimensions().getX();
				auto height = model->getBoundingBox()->getDimensions().getY();
				auto depth = model->getBoundingBox()->getDimensions().getZ();
				if (width < 0.2f && height < 0.2f && depth < 0.2f) {
					if (width > Math::EPSILON && width < height && width < depth) {
						importFixScale = 1.0f / width / 5.0f;
					} else
					if (height > Math::EPSILON && height < width && height < depth) {
						importFixScale = 1.0f / height / 5.0f;
					} else
					if (depth > Math::EPSILON) {
						importFixScale = 1.0f / depth / 5.0f;
					}
				}
				model->getImportTransformationsMatrix().scale(importFixScale);
				model->getBoundingBox()->getMin().scale(importFixScale);
				model->getBoundingBox()->getMax().scale(importFixScale);
				model->getBoundingBox()->update();
				scale.scale(1.0f / importFixScale);
			}
			auto entityType = LevelEditorEntity_EntityType::MODEL;
			if (meshGroup.group->getVertices()->size() == 0) {
				entityType = LevelEditorEntity_EntityType::EMPTY;
				delete model;
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
					auto modelFileName = meshGroup.name + ".tm";
					TMWriter::write(
						model,
						modelPathName,
						modelFileName
					  );
					delete model;
					levelEditorEntity = entityLibrary->addModel(
						groupIdx++,
						meshGroup.name,
						meshGroup.name,
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
				delete model;
				continue;
			}
			Transformations levelEditorObjectTransformations;
			levelEditorObjectTransformations.setTranslation(translation);
			levelEditorObjectTransformations.addRotation(rotationOrder->getAxis0(), rotation.getArray()[rotationOrder->getAxis0VectorIndex()]);
			levelEditorObjectTransformations.addRotation(rotationOrder->getAxis1(), rotation.getArray()[rotationOrder->getAxis1VectorIndex()]);
			levelEditorObjectTransformations.addRotation(rotationOrder->getAxis2(), rotation.getArray()[rotationOrder->getAxis2VectorIndex()]);
			levelEditorObjectTransformations.setScale(scale);
			levelEditorObjectTransformations.update();
			auto object = new LevelEditorObject(
				meshGroup.id,
				meshGroup.id,
				levelEditorObjectTransformations,
				levelEditorEntity
			);
			level->addObject(object);

		}
		//
		progressIdx++;
	}

	if (progressCallback != nullptr) progressCallback->progress(0.9f);

	// export to tl
	LevelFileExport::export_(
		pathName,
		fileName + ".tl",
		level
	);

	//
	delete levelModel;

	//
	if (progressCallback != nullptr) progressCallback->progress(1.0f);
}
