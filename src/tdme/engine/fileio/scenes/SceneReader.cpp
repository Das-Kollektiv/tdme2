#include <tdme/engine/fileio/scenes/SceneReader.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeTransformFilter.h>
#include <tdme/engine/fileio/scenes/SceneWriter.h>
#include <tdme/engine/fileio/ProgressCallback.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/scene/SceneEntity.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/engine/scene/SceneLight.h>
#include <tdme/engine/subsystems/rendering/ModelStatistics.h>
#include <tdme/engine/ModelUtilities.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/utilities/StringTools.h>

#include <ext/rapidjson/document.h>

using std::string;
using std::to_string;

using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::models::TMWriter;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::prototypes::PrototypeTransformFilter;
using tdme::engine::fileio::scenes::SceneReader;
using tdme::engine::fileio::scenes::SceneWriter;
using tdme::engine::fileio::ProgressCallback;
using tdme::engine::model::Animation;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::UpVector;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneEntity;
using tdme::engine::scene::SceneLibrary;
using tdme::engine::scene::SceneLight;
using tdme::engine::subsystems::rendering::ModelStatistics;
using tdme::engine::ModelUtilities;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::misc::Tools;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::ModelTools;
using tdme::utilities::StringTools;

using rapidjson::Document;
using rapidjson::Value;

Scene* SceneReader::read(const string& pathName, const string& fileName, ProgressCallback* progressCallback, PrototypeTransformFilter* prototypeTransformFilter)
{
	return read(pathName, fileName, "", progressCallback, prototypeTransformFilter);
}

Scene* SceneReader::read(const string& pathName, const string& fileName, const string& objectIdPrefix, ProgressCallback* progressCallback, PrototypeTransformFilter* prototypeTransformFilter)
{
	if (progressCallback != nullptr) progressCallback->progress(0.0f);

	auto jsonContent = FileSystem::getInstance()->getContentAsString(pathName, fileName);
	if (progressCallback != nullptr) progressCallback->progress(0.165f);

	Document jRoot;
	jRoot.Parse(jsonContent.c_str());
	if (progressCallback != nullptr) progressCallback->progress(0.33f);

	//
	auto scene = new Scene(fileName, "");
	scene->setApplicationRootPathName(Tools::getApplicationRootPathName(pathName));
	// auto version = Float::parseFloat((jRoot["version"].GetString()));
	scene->setRotationOrder(jRoot.FindMember("ro") != jRoot.MemberEnd()?RotationOrder::valueOf(jRoot["ro"].GetString()):RotationOrder::XYZ);
	for (auto i = 0; i < jRoot["properties"].GetArray().Size(); i++) {
		auto& jSceneProperty = jRoot["properties"].GetArray()[i];
		scene->addProperty(
			jSceneProperty["name"].GetString(),
			jSceneProperty["value"].GetString()
		);
	}
	if (jRoot.FindMember("lights") != jRoot.MemberEnd()) {
		auto lightIdx = 0;
		auto jLights = jRoot["lights"].GetArray();
		for (auto i = 0; i < jLights.Size(); i++) {
			auto& jLight = jLights[i];
			if (jLight["e"].GetBool() == false) continue;
			auto light = lightIdx < scene->getLightCount()?(scene->getLightAt(jLight.FindMember("id") != jLight.MemberEnd()?jLight["id"].GetInt():lightIdx)):scene->addLight();
			light->setAmbient(
				Color4(
					jLight["ar"].GetFloat(),
					jLight["ag"].GetFloat(),
					jLight["ab"].GetFloat(),
					jLight["aa"].GetFloat()
				)
			);
			light->setDiffuse(
				Color4(
					jLight["dr"].GetFloat(),
					jLight["dg"].GetFloat(),
					jLight["db"].GetFloat(),
					jLight["da"].GetFloat()
				)
			);
			light->setSpecular(
				Color4(
					jLight["sr"].GetFloat(),
					jLight["sg"].GetFloat(),
					jLight["sb"].GetFloat(),
					jLight["sa"].GetFloat()
				)
			);
			light->setPosition(
				Vector4(
					jLight["px"].GetFloat(),
					jLight["py"].GetFloat(),
					jLight["pz"].GetFloat(),
					jLight["pw"].GetFloat()
				)
			);
			light->setConstantAttenuation(jLight["ca"].GetFloat());
			light->setLinearAttenuation(jLight["la"].GetFloat());
			light->setQuadraticAttenuation(jLight["qa"].GetFloat());
			light->setSpotDirection(
				Vector3(
					jLight["sdx"].GetFloat(),
					jLight["sdy"].GetFloat(),
					jLight["sdz"].GetFloat()
				)
			);
			light->setSpotExponent(jLight["se"].GetFloat());
			light->setSpotCutOff(jLight["sco"].GetFloat());
			light->setEnabled(jLight["e"].GetBool());
			lightIdx++;
		}
	}

	auto progressStepCurrent = 0;
	auto jPrototypes = jRoot["models"].GetArray();
	for (auto i = 0; i < jPrototypes.Size(); i++) {
		auto& jPrototype = jPrototypes[i];
		Prototype* prototype = nullptr;
		try {
			auto embedded = jPrototype.FindMember("e") != jPrototype.MemberEnd()?jPrototype["e"].GetBool():true;
			if (embedded == true) {
				prototype = PrototypeReader::read(
					jPrototype["id"].GetInt(),
					pathName,
					jPrototype["entity"],
					prototypeTransformFilter
				);
				prototype->setEmbedded(true);
			} else {
				auto externalPrototypePathName = PrototypeReader::getResourcePathName(pathName, jPrototype["pf"].GetString());
				auto externalPrototypeFileName = FileSystem::getInstance()->getFileName(jPrototype["pf"].GetString());
				prototype = PrototypeReader::read(
					jPrototype["id"].GetInt(),
					externalPrototypePathName,
					externalPrototypeFileName,
					prototypeTransformFilter
				);
				prototype->setEmbedded(false);
			}
		} catch (Exception& exception) {
			Console::println(string() + "SceneReader::read(): An error occurred: " + exception.what() + ": Using empty prototype");
			//
			string prototypeName = "Missing-Prototype-" + to_string(jPrototype["id"].GetInt());
			//
			prototype = new Prototype(
				jPrototype["id"].GetInt(),
				Prototype_Type::EMPTY,
				prototypeName,
				string(),
				prototypeName + ".tempty",
				"resources/engine/models/empty.tm",
				string(),
				ModelReader::read("resources/engine/models", "empty.tm"), // TODO: exception
				Vector3(0.0f, 0.0f, 0.0f)
			);
		}
		if (prototype == nullptr) {
			Console::println("SceneReader::read(): Invalid prototype = " + to_string(jPrototype["id"].GetInt()));
			continue;
		}
		scene->getLibrary()->addPrototype(prototype);
		if (jPrototype.FindMember("properties") != jPrototype.MemberEnd()) {
			for (auto j = 0; j < jPrototype["properties"].GetArray().Size(); j++) {
				auto& jPrototypeProperty = jPrototype["properties"].GetArray()[j];
				prototype->addProperty(
					jPrototypeProperty["name"].GetString(),
					jPrototypeProperty["value"].GetString()
				);
			}
		}

		if (progressCallback != nullptr) progressCallback->progress(0.33f + static_cast<float>(progressStepCurrent) / static_cast<float>(jRoot["models"].GetArray().Size()) * 0.33f);
		progressStepCurrent++;
	}

	auto jEntities = jRoot["objects"].GetArray();
	for (auto i = 0; i < jEntities.Size(); i++) {
		auto& jSceneEntity = jEntities[i];
		auto prototype = scene->getLibrary()->getPrototype(jSceneEntity["mid"].GetInt());
		if (prototype == nullptr) {
			Console::println("SceneReader::read(): No prototype found with id = " + to_string(jSceneEntity["mid"].GetInt()));

			if (progressCallback != nullptr && progressStepCurrent % 1000 == 0) progressCallback->progress(0.66f + static_cast<float>(progressStepCurrent) / static_cast<float>(jRoot["objects"].GetArray().Size()) * 0.33f);
			progressStepCurrent++;

			continue;
		}

		Transform transform;
		transform.setPivot(prototype->getPivot());
		transform.setTranslation(
			Vector3(
				jSceneEntity["tx"].GetFloat(),
				jSceneEntity["ty"].GetFloat(),
				jSceneEntity["tz"].GetFloat()
			)
		);
		transform.setScale(
			Vector3(
				jSceneEntity["sx"].GetFloat(),
				jSceneEntity["sy"].GetFloat(),
				jSceneEntity["sz"].GetFloat()
			)
		);
		Vector3 rotation(
			jSceneEntity["rx"].GetFloat(),
			jSceneEntity["ry"].GetFloat(),
			jSceneEntity["rz"].GetFloat()
		);
		transform.addRotation(scene->getRotationOrder()->getAxis0(), rotation.getArray()[scene->getRotationOrder()->getAxis0VectorIndex()]);
		transform.addRotation(scene->getRotationOrder()->getAxis1(), rotation.getArray()[scene->getRotationOrder()->getAxis1VectorIndex()]);
		transform.addRotation(scene->getRotationOrder()->getAxis2(), rotation.getArray()[scene->getRotationOrder()->getAxis2VectorIndex()]);
		transform.update();
		auto sceneEntity = new SceneEntity(
			objectIdPrefix != "" ?
				objectIdPrefix + jSceneEntity["id"].GetString() :
				(jSceneEntity["id"].GetString()),
			 jSceneEntity.FindMember("descr") != jSceneEntity.MemberEnd()?jSceneEntity["descr"].GetString() : "",
			 transform,
			 prototype
		);
		if (jSceneEntity.FindMember("properties") != jSceneEntity.MemberEnd()) {
			for (auto j = 0; j < jSceneEntity["properties"].GetArray().Size(); j++) {
				auto& jSceneEntityProperty = jSceneEntity["properties"].GetArray()[j];
				sceneEntity->addProperty(
					jSceneEntityProperty["name"].GetString(),
					jSceneEntityProperty["value"].GetString()
				);
			}
		}
		sceneEntity->setReflectionEnvironmentMappingId(jSceneEntity.FindMember("r") != jSceneEntity.MemberEnd()?jSceneEntity["r"].GetString():"");
		scene->addEntity(sceneEntity);

		if (progressCallback != nullptr && progressStepCurrent % 1000 == 0) progressCallback->progress(0.66f + static_cast<float>(progressStepCurrent) / static_cast<float>(jRoot["objects"].GetArray().Size()) * 0.33f);
		progressStepCurrent++;
	}
	scene->setEntityIdx(jRoot["objects_eidx"].GetInt());
	scene->setFileName((pathName.empty() == false?pathName + "/":"") + fileName);
	scene->update();

	//
	if (jRoot.FindMember("sky") != jRoot.MemberEnd()) {
		auto& jSky = jRoot["sky"];
		scene->setSkyModelFileName(jSky["file"].GetString());
		scene->setSkyModelScale(
			Vector3(
				jSky["sx"].GetFloat(),
				jSky["sy"].GetFloat(),
				jSky["sz"].GetFloat()
			)
		);
		if (scene->getSkyModelFileName().empty() == false) {
			auto skyModelPathName = PrototypeReader::getResourcePathName(pathName, scene->getSkyModelFileName());
			auto skyModelFileName = FileSystem::getInstance()->getFileName(scene->getSkyModelFileName());
			scene->setSkyModelFileName(skyModelPathName + "/" + skyModelFileName);
			try {
				scene->setSkyModel(
					ModelReader::read(
						skyModelPathName,
						skyModelFileName
					)
				);
			} catch (Exception& exception) {
				delete scene;
				throw exception;
			}
		}
	}

	//
	if (jRoot.FindMember("gui") != jRoot.MemberEnd()) {
		scene->setGUIFileName(jRoot["gui"].GetString());
	}

	//
	if (progressCallback != nullptr) {
		progressCallback->progress(1.0f);
		delete progressCallback;
	}

	//
	return scene;
}

void SceneReader::determineMeshNodes(Scene* scene, Node* node, const string& parentName, const Matrix4x4& parentTransformMatrix, vector<PrototypeMeshNode>& meshNodes) {
	auto sceneLibrary = scene->getLibrary();
	auto nodeId = node->getId();
	if (parentName.length() > 0) nodeId = parentName + "." + nodeId;
	auto modelName = nodeId;
	modelName = StringTools::regexReplace(modelName, "[-_]{1}[0-9]+$", "");
	modelName = StringTools::regexReplace(modelName, "[0-9]+$", "");
	auto haveName = sceneLibrary->getPrototypeCount() == 0;
	if (haveName == false) {
		for (auto i = 0; i < 10000; i++) {
			haveName = true;
			auto modelNameTry = modelName;
			if (i > 0) modelNameTry+= to_string(i);
			for (auto entityIdx = 0; entityIdx < sceneLibrary->getPrototypeCount(); entityIdx++) {
				auto entity = sceneLibrary->getPrototypeAt(entityIdx);
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
				"SceneReader::doImportFromModel(): Skipping model '" +
				modelName +
				"' as no name could be created for it."
			)
		 );
		return;
	}
	Matrix4x4 transformMatrix;
	// compute animation matrix if animation setups exist
	auto animation = node->getAnimation();
	if (animation != nullptr) {
		auto& animationMatrices = animation->getTransformMatrices();
		transformMatrix.set(animationMatrices[0 % animationMatrices.size()]);
	} else {
		// no animation matrix, set up local transform matrix up as node matrix
		transformMatrix.set(node->getTransformMatrix());
	}

	// apply parent transform matrix
	transformMatrix.multiply(parentTransformMatrix);

	// check if no mesh?
	if (node->getVertices().size() == 0 && node->getSubNodes().size() > 0) {
		// ok, check sub meshes
		for (auto subNodeIt: node->getSubNodes()) {
			determineMeshNodes(scene, subNodeIt.second, nodeId, transformMatrix.clone(), meshNodes);
		}
	} else {
		// add to node meshes, even if empty as its a empty :D
		PrototypeMeshNode prototypeMeshNode;
		prototypeMeshNode.id = nodeId;
		prototypeMeshNode.name = modelName;
		prototypeMeshNode.node = node;
		prototypeMeshNode.transformMatrix.set(transformMatrix);
		meshNodes.push_back(prototypeMeshNode);
	}
}

Scene* SceneReader::readFromModel(const string& pathName, const string& fileName, ProgressCallback* progressCallback) {
	if (progressCallback != nullptr) progressCallback->progress(0.0f);

	string modelPathName = pathName + "/" + fileName + "-models";
	if (FileSystem::getInstance()->fileExists(modelPathName)) {
		FileSystem::getInstance()->removePath(modelPathName, true);
	}
	FileSystem::getInstance()->createPath(modelPathName);

	auto sceneModel = ModelReader::read(pathName, fileName);

	if (progressCallback != nullptr) progressCallback->progress(0.1f);

	auto upVector = sceneModel->getUpVector();
	RotationOrder* rotationOrder = sceneModel->getRotationOrder();

	//
	auto scene = new Scene(fileName, "");
	scene->setRotationOrder(rotationOrder);

	auto sceneLibrary = scene->getLibrary();
	auto nodeIdx = 0;
	Prototype* emptyPrototype = nullptr;
	Matrix4x4 sceneModelImportRotationMatrix;
	Vector3 sceneModelScale;
	sceneModelImportRotationMatrix.set(sceneModel->getImportTransformMatrix());
	sceneModelImportRotationMatrix.getScale(sceneModelScale);
	sceneModelImportRotationMatrix.scale(Vector3(1.0f / sceneModelScale.getX(), 1.0f / sceneModelScale.getY(), 1.0f / sceneModelScale.getZ()));
	auto progressTotal = sceneModel->getSubNodes().size();
	auto progressIdx = 0;
	for (auto nodeIt: sceneModel->getSubNodes()) {
		if (progressCallback != nullptr) progressCallback->progress(0.1f + static_cast<float>(progressIdx) / static_cast<float>(progressTotal) * 0.8f);
		vector<PrototypeMeshNode> meshNodes;
		determineMeshNodes(scene, nodeIt.second, "", (Matrix4x4()).identity(), meshNodes);
		for (auto& meshNode: meshNodes) {
			auto model = new Model(
				meshNode.name + ".tm",
				fileName + "-" + meshNode.name,
				upVector,
				rotationOrder,
				nullptr
			);
			model->setImportTransformMatrix(sceneModel->getImportTransformMatrix());
			float importFixScale = 1.0f;
			Vector3 translation, scale;
			Vector3 xAxis, yAxis, zAxis;
			Matrix4x4 nodeTransformMatrix;
			nodeTransformMatrix.set(meshNode.transformMatrix);
			nodeTransformMatrix.getAxes(xAxis, yAxis, zAxis);
			nodeTransformMatrix.getTranslation(translation);
			nodeTransformMatrix.getScale(scale);
			xAxis.normalize();
			yAxis.normalize();
			zAxis.normalize();
			nodeTransformMatrix.setAxes(xAxis, yAxis, zAxis);
			if ((upVector == UpVector::Y_UP && Vector3::computeDotProduct(Vector3::computeCrossProduct(xAxis, yAxis), zAxis) < 0.0f) ||
				(upVector == UpVector::Z_UP && Vector3::computeDotProduct(Vector3::computeCrossProduct(xAxis, zAxis), yAxis) < 0.0f)) {
				xAxis.scale(-1.0f);
				yAxis.scale(-1.0f);
				zAxis.scale(-1.0f);
				nodeTransformMatrix.setAxes(xAxis, yAxis, zAxis);
				scale.scale(-1.0f);
			}
			auto rotation = nodeTransformMatrix.computeEulerAngles();
			scale = sceneModelImportRotationMatrix.multiply(scale);
			rotation = sceneModelImportRotationMatrix.multiply(rotation);
			translation = model->getImportTransformMatrix().multiply(translation);

			ModelTools::cloneNode(meshNode.node, model);
			if (model->getSubNodes().begin() != model->getSubNodes().end()) {
				model->getSubNodes().begin()->second->setTransformMatrix(Matrix4x4().identity());
			}
			model->addAnimationSetup(Model::ANIMATIONSETUP_DEFAULT, 0, 0, true);
			ModelTools::prepareForIndexedRendering(model);
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
				model->setImportTransformMatrix(model->getImportTransformMatrix().clone().scale(importFixScale));
				model->getBoundingBox()->getMin().scale(importFixScale);
				model->getBoundingBox()->getMax().scale(importFixScale);
				model->getBoundingBox()->update();
				scale.scale(1.0f / importFixScale);
			}
			auto prototypeType = Prototype_Type::MODEL;
			if (meshNode.node->getVertices().size() == 0) {
				prototypeType = Prototype_Type::EMPTY;
				delete model;
				model = nullptr;
			}
			Prototype* prototype = nullptr;
			if (prototypeType == Prototype_Type::MODEL && model != nullptr) {
				for (auto i = 0; i < scene->getLibrary()->getPrototypeCount(); i++) {
					auto prototypeCompare = scene->getLibrary()->getPrototypeAt(i);
					if (prototypeCompare->getType() != Prototype_Type::MODEL)
						continue;

					if (ModelUtilities::equals(model, prototypeCompare->getModel()) == true) {
						prototype = prototypeCompare;
						delete model;
						model = nullptr;
						break;
					}
				}
				if (prototype == nullptr && model != nullptr) {
					auto modelFileName = meshNode.name + ".tm";
					try {
						TMWriter::write(
							model,
							modelPathName,
							modelFileName
						);
					} catch (Exception& exception) {
						delete model;
						delete scene;
						delete sceneModel;
						throw exception;
					}
					prototype = new Prototype(
						Prototype::ID_NONE,
						Prototype_Type::MODEL,
						Tools::removeFileExtension(fileName),
						Tools::removeFileExtension(fileName),
						modelPathName + "/" + modelFileName,
						"resources/engine/models/empty.tm",
						string(),
						model,
						Vector3(0.0f, 0.0f, 0.0f)
					);
					sceneLibrary->addPrototype(prototype);
				}
			} else
			if (prototypeType == Prototype_Type::EMPTY) {
				if (emptyPrototype == nullptr) {
					emptyPrototype = new Prototype(
						nodeIdx++,
						Prototype_Type::EMPTY,
						"Default Empty",
						"Default Empty",
						string(),
						"resources/engine/models/empty.tm",
						string(),
						ModelReader::read("resources/engine/models", "empty.tm"), // TODO: exception
						Vector3(0.0f, 0.0f, 0.0f)
					);
					sceneLibrary->addPrototype(emptyPrototype);
				}
				prototype = emptyPrototype;
			} else {
				Console::println(string("DAEReader::readLevel(): unknown entity type. Skipping"));
				delete model;
				model = nullptr;
				continue;
			}
			Transform sceneEntityTransform;
			sceneEntityTransform.setTranslation(translation);
			sceneEntityTransform.addRotation(rotationOrder->getAxis0(), rotation.getArray()[rotationOrder->getAxis0VectorIndex()]);
			sceneEntityTransform.addRotation(rotationOrder->getAxis1(), rotation.getArray()[rotationOrder->getAxis1VectorIndex()]);
			sceneEntityTransform.addRotation(rotationOrder->getAxis2(), rotation.getArray()[rotationOrder->getAxis2VectorIndex()]);
			sceneEntityTransform.setScale(scale);
			sceneEntityTransform.update();
			auto sceneEntity = new SceneEntity(
				meshNode.id,
				meshNode.id,
				sceneEntityTransform,
				prototype
			);
			scene->addEntity(sceneEntity);
		}
		//
		progressIdx++;
	}

	if (progressCallback != nullptr) progressCallback->progress(0.9f);

	try {
		// export to tscene
		SceneWriter::write(
			pathName,
			Tools::removeFileExtension(fileName) + ".tscene",
			scene
		);
	} catch (Exception& exception) {
		delete scene;
		delete sceneModel;
		throw exception;
	}

	//
	delete sceneModel;

	//
	if (progressCallback != nullptr) progressCallback->progress(1.0f);

	//
	return scene;
}
