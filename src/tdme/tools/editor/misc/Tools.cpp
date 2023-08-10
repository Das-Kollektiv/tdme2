#include <tdme/tools/editor/misc/Tools.h>

#include <array>
#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/ShaderModel.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/prototype/PrototypeBoundingVolume.h>
#include <tdme/engine/prototype/PrototypeImposterLOD.h>
#include <tdme/engine/prototype/PrototypeLODLevel.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityHierarchy.h>
#include <tdme/engine/ImposterObject.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/SimplePartition.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandler.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/utilities/Primitives.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>

using std::array;
using std::make_unique;
using std::string;
using std::to_string;
using std::unique_ptr;

using tdme::tools::editor::misc::Tools;

using tdme::application::Application;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::ShaderModel;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::model::UpVector;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::prototype::PrototypeImposterLOD;
using tdme::engine::prototype::PrototypeLODLevel;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EntityHierarchy;
using tdme::engine::ImposterObject;
using tdme::engine::Light;
using tdme::engine::Object;
using tdme::engine::SceneConnector;
using tdme::engine::SimplePartition;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::misc::CameraRotationInputHandler;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::ModelTools;
using tdme::utilities::Primitives;
using tdme::utilities::Properties;
using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;

Engine* Tools::osEngine = nullptr;
Model* Tools::gizmoAll = nullptr;
Model* Tools::gizmoTranslationScale = nullptr;
Model* Tools::gizmoTranslation = nullptr;
Model* Tools::gizmoScale = nullptr;
Model* Tools::gizmoRotations = nullptr;
Model* Tools::defaultOBB = nullptr;
Tools::ToolsShutdown Tools::toolsShutdown;

string Tools::formatFloat(float value)
{

	string floatString = to_string(value);
	return floatString.substr(0, floatString.length() - 3);
}

void Tools::setDefaultLight(Light* light)
{
	light->setAmbient(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setDiffuse(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	light->setSpecular(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setPosition(Vector4(0.0f, 20000.0f, 0.0f, 0.0f));
	light->setSpotDirection(Vector3(0.0f, 0.0f, 0.0f).sub(Vector3(light->getPosition().getX(), light->getPosition().getY(), light->getPosition().getZ())));
	light->setConstantAttenuation(0.5f);
	light->setLinearAttenuation(0.0f);
	light->setQuadraticAttenuation(0.0f);
	light->setSpotExponent(0.0f);
	light->setSpotCutOff(180.0f);
	light->setEnabled(true);
}

void Tools::oseInit()
{
	if (osEngine != nullptr) return;
	osEngine = Engine::createOffScreenInstance(128, 128, false, true, false);
	osEngine->setPartition(new SimplePartition());
	setDefaultLight(osEngine->getLightAt(0));
}

void Tools::oseDispose()
{
	if (osEngine == nullptr) return;
	osEngine->dispose();
	delete osEngine;
}

void Tools::oseThumbnail(Prototype* prototype, vector<uint8_t>& pngData)
{
	oseInit();
	Vector3 objectScale;
	Transform oseLookFromRotations;
	oseLookFromRotations.addRotation(Vector3(0.0f, 1.0f, 0.0f), -45.0f);
	oseLookFromRotations.addRotation(Vector3(1.0f, 0.0f, 0.0f), -45.0f);
	oseLookFromRotations.addRotation(Vector3(0.0f, 0.0f, 1.0f), 0.0f);
	oseLookFromRotations.update();
	Tools::setupPrototype(prototype, osEngine, oseLookFromRotations, 1, objectScale, nullptr, 1.0f);
	osEngine->setSceneColor(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	osEngine->display();
	osEngine->makeScreenshot(pngData);
	/*
	osEngine->setSceneColor(Color4(0.8f, 0.0f, 0.0f, 1.0f));
	osEngine->display();
	osEngine->makeScreenshot(pngData);
	*/
	osEngine->reset();
}

float Tools::computeMaxAxisDimension(BoundingBox* boundingBox)
{
	auto maxAxisDimension = 0.0f;
	Vector3 dimension = boundingBox->getMax().clone().sub(boundingBox->getMin());
	if (dimension.getX() > maxAxisDimension) maxAxisDimension = dimension.getX();
	if (dimension.getY() > maxAxisDimension) maxAxisDimension = dimension.getY();
	if (dimension.getZ() > maxAxisDimension) maxAxisDimension = dimension.getZ();
	return maxAxisDimension;
}

Model* Tools::createGroundModel(float width, float depth, float y)
{
	auto modelId = "tdme.ground" + to_string(static_cast<int>(width * 100)) + "x" + to_string(static_cast<int>(depth * 100)) + "@" + to_string(static_cast<int>(y * 100));
	auto ground = new Model(modelId, modelId, UpVector::Y_UP, RotationOrder::ZYX, nullptr);
	auto groundMaterial = new Material("ground");
	groundMaterial->setSpecularMaterialProperties(new SpecularMaterialProperties());
	groundMaterial->getSpecularMaterialProperties()->setSpecularColor(Color4(0.0f, 0.0f, 0.0f, 1.0f));
	groundMaterial->getSpecularMaterialProperties()->setDiffuseTexture("resources/engine/textures", "groundplate.png");
	ground->getMaterials()["ground"] = groundMaterial;
	auto groundNode = new Node(ground, nullptr, "ground", "ground");
	vector<Vector3> groundVertices;
	groundVertices.push_back(Vector3(-width/2, y, -depth/2));
	groundVertices.push_back(Vector3(-width/2, y, +depth/2));
	groundVertices.push_back(Vector3(+width/2, y, +depth/2));
	groundVertices.push_back(Vector3(+width/2, y, -depth/2));
	vector<Vector3> groundNormals;
	groundNormals.push_back(Vector3(0.0f, 1.0f, 0.0f));
	vector<TextureCoordinate> groundTextureCoordinates;
	groundTextureCoordinates.push_back(TextureCoordinate(0.0f, depth));
	groundTextureCoordinates.push_back(TextureCoordinate(0.0f, 0.0f));
	groundTextureCoordinates.push_back(TextureCoordinate(width, 0.0f));
	groundTextureCoordinates.push_back(TextureCoordinate(width, depth));
	vector<Face> groundFacesGround;
	groundFacesGround.push_back(Face(groundNode, 0, 1, 2, 0, 0, 0, 0, 1, 2));
	groundFacesGround.push_back(Face(groundNode, 2, 3, 0, 0, 0, 0, 2, 3, 0));
	FacesEntity nodeFacesEntityGround(groundNode, "ground.facesentity");
	nodeFacesEntityGround.setMaterial(groundMaterial);
	vector<FacesEntity> nodeFacesEntities;
	nodeFacesEntityGround.setFaces(groundFacesGround);
	nodeFacesEntities.push_back(nodeFacesEntityGround);
	groundNode->setVertices(groundVertices);
	groundNode->setNormals(groundNormals);
	groundNode->setTextureCoordinates(groundTextureCoordinates);
	groundNode->setFacesEntities(nodeFacesEntities);
	ground->getNodes()["ground"] = groundNode;
	ground->getSubNodes()["ground"] = groundNode;
	ModelTools::prepareForIndexedRendering(ground);
	return ground;
}

Model* Tools::createGridModel()
{
	auto groundPlate = new Model("tdme.grid", "tdme.grid", UpVector::Y_UP, RotationOrder::XYZ, new BoundingBox(Vector3(0.0f, -0.01f, 0.0f), Vector3(10000.0f, +0.01f, 10000.0f)));
	auto groundPlateMaterial = new Material("ground");
	groundPlateMaterial->setSpecularMaterialProperties(new SpecularMaterialProperties());
	groundPlateMaterial->getSpecularMaterialProperties()->setDiffuseColor(
		Color4(
			groundPlateMaterial->getSpecularMaterialProperties()->getDiffuseColor().getRed(),
			groundPlateMaterial->getSpecularMaterialProperties()->getDiffuseColor().getGreen(),
			groundPlateMaterial->getSpecularMaterialProperties()->getDiffuseColor().getBlue(),
			0.75f
		)
	);
	groundPlateMaterial->getSpecularMaterialProperties()->setDiffuseTexture("resources/engine/textures", "groundplate.png");
	groundPlateMaterial->getSpecularMaterialProperties()->setSpecularColor(Color4(0.0f, 0.0f, 0.0f, 1.0f));
	groundPlate->getMaterials()["grid"] = groundPlateMaterial;
	auto groundNode = new Node(groundPlate, nullptr, "grid", "grid");
	vector<Vector3> groundVertices;
	groundVertices.push_back(Vector3(0.0f, 0.0f, 0.0f));
	groundVertices.push_back(Vector3(0.0f, 0.0f, 10000.0f));
	groundVertices.push_back(Vector3(10000.0f, 0.0f, 10000.0f));
	groundVertices.push_back(Vector3(10000.0f, 0.0f, 0.0f));
	vector<Vector3> groundNormals;
	groundNormals.push_back(Vector3(0.0f, 1.0f, 0.0f));
	vector<TextureCoordinate> groundTextureCoordinates;
	groundTextureCoordinates.push_back(TextureCoordinate(0.0f, 10000.0f));
	groundTextureCoordinates.push_back(TextureCoordinate(0.0f, 0.0f));
	groundTextureCoordinates.push_back(TextureCoordinate(10000.0f, 0.0f));
	groundTextureCoordinates.push_back(TextureCoordinate(10000.0f, 10000.0f));
	vector<Face> groundFacesGround;
	groundFacesGround.push_back(Face(groundNode, 0, 1, 2, 0, 0, 0, 0, 1, 2));
	groundFacesGround.push_back(Face(groundNode, 2, 3, 0, 0, 0, 0, 2, 3, 0));
	FacesEntity nodeFacesEntityGround(groundNode, "tdme.sceneeditor.grid.facesentity");
	nodeFacesEntityGround.setMaterial(groundPlateMaterial);
	nodeFacesEntityGround.setFaces(groundFacesGround);
	vector<FacesEntity> nodeFacesEntities;
	nodeFacesEntities.push_back(nodeFacesEntityGround);
	groundNode->setVertices(groundVertices);
	groundNode->setNormals(groundNormals);
	groundNode->setTextureCoordinates(groundTextureCoordinates);
	groundNode->setFacesEntities(nodeFacesEntities);
	groundPlate->getNodes()[groundNode->getId()] = groundNode;
	groundPlate->getSubNodes()[groundNode->getId()] = groundNode;
	ModelTools::prepareForIndexedRendering(groundPlate);
	return groundPlate;
}

void Tools::setupPrototype(Prototype* prototype, Engine* engine, const Transform& lookFromRotations, int lodLevel, Vector3& objectScale, CameraRotationInputHandler* cameraRotationInputHandler, float scale, bool resetup)
{
	if (prototype == nullptr) return;

	// create engine entity
	auto entityBoundingBoxFallback = make_unique<BoundingBox>(Vector3(-2.5f, 0.0f, -2.5f), Vector3(2.5f, 2.0f, 2.5f));
	BoundingBox* entityBoundingBox = nullptr;
	Entity* modelEntity = nullptr;
	objectScale.set(1.0f, 1.0f, 1.0f);
	Color4 colorMul(1.0f, 1.0f, 1.0f, 1.0f);
	Color4 colorAdd(0.0f, 0.0f, 0.0f, 0.0f);

	// bounding volumes
	auto entityBoundingVolumesHierarchy = new EntityHierarchy("tdme.prototype.bvs");
	{
		auto i = 0;
		for (auto prototypeBoundingVolume: prototype->getBoundingVolumes()) {
			if (prototypeBoundingVolume->getModel() != nullptr) {
				auto bvObject = new Object("tdme.prototype.bv." + to_string(i), prototypeBoundingVolume->getModel());
				bvObject->setEnabled(false);
				entityBoundingVolumesHierarchy->addEntity(bvObject);
			}
			i++;
		}
	}
	entityBoundingVolumesHierarchy->update();
	engine->addEntity(entityBoundingVolumesHierarchy);

	//
	if (prototype->getType() == Prototype_Type::TRIGGER ||
		prototype->getType() == Prototype_Type::ENVIRONMENTMAPPING ||
		prototype->getType() == Prototype_Type::DECAL) {
		entityBoundingBox = entityBoundingVolumesHierarchy->getBoundingBox();
	} else
	if (prototype->getType() == Prototype_Type::PARTICLESYSTEM) {
		modelEntity = SceneConnector::createEntity(prototype, "model", Transform());
		if (modelEntity != nullptr) engine->addEntity(modelEntity);
	} else
	if (prototype->getModel() != nullptr) {
		// model
		Model* model = nullptr;
		switch (lodLevel) {
			case 1:
				model = prototype->getModel();
				break;
			case 2:
				{
					auto lodLevelEntity = prototype->getLODLevel2();
					if (lodLevelEntity != nullptr) {
						model = lodLevelEntity->getModel();
						colorMul.set(lodLevelEntity->getColorMul());
						colorAdd.set(lodLevelEntity->getColorAdd());
					}
					break;
				}
			case 3:
				{
					auto lodLevelEntity = prototype->getLODLevel3();
					if (lodLevelEntity != nullptr) {
						model = lodLevelEntity->getModel();
						colorMul.set(lodLevelEntity->getColorMul());
						colorAdd.set(lodLevelEntity->getColorAdd());
					}
					break;
				}
			case 4:
			{
				auto imposterLOD = prototype->getImposterLOD();
				if (imposterLOD != nullptr) {
					modelEntity = new ImposterObject(
						"model",
						imposterLOD->getModels()
					);
					// TODO: remove this duplicated code, see :368
					modelEntity->setContributesShadows(true);
					modelEntity->setReceivesShadows(true);
					modelEntity->setEffectColorMul(colorMul);
					modelEntity->setEffectColorAdd(colorAdd);
					auto object = dynamic_cast<ImposterObject*>(modelEntity);
					object->setShader(prototype->getShader());
					auto shaderParametersDefault = Engine::getShaderParameterDefaults(prototype->getShader());
					for (const auto& [parameterName, defaultParameterValue]: shaderParametersDefault) {
						auto parameterValue = prototype->getShaderParameters().getShaderParameter(parameterName);
						object->setShaderParameter(parameterName, parameterValue);
					}
					engine->addEntity(modelEntity);
				}
			}
		}
		entityBoundingBox = prototype->getModel()->getBoundingBox();
		if (model != nullptr) {
			modelEntity = new Object("model", model);
			modelEntity->setContributesShadows(true);
			modelEntity->setReceivesShadows(true);
			modelEntity->setEffectColorMul(colorMul);
			modelEntity->setEffectColorAdd(colorAdd);
			auto object = dynamic_cast<Object*>(modelEntity);
			object->setShader(prototype->getShader());
			auto shaderParametersDefault = Engine::getShaderParameterDefaults(prototype->getShader());
			for (const auto& [parameterName, defaultParameterValue]: shaderParametersDefault) {
				auto parameterValue = prototype->getShaderParameters().getShaderParameter(parameterName);
				object->setShaderParameter(parameterName, parameterValue);
			}
			engine->addEntity(modelEntity);
		}
	}

	//
	auto entityBoundingBoxToUse = entityBoundingBox != nullptr?entityBoundingBox:entityBoundingBoxFallback.get();

	// do a feasible scale
	float maxAxisDimension = Tools::computeMaxAxisDimension(entityBoundingBoxToUse);
	if (maxAxisDimension < Math::EPSILON) maxAxisDimension = 1.0f;

	if (modelEntity != nullptr) {
		modelEntity->setPickable(true);
		modelEntity->setScale(objectScale);
		modelEntity->update();
	}

	// generate ground
	auto ground = createGroundModel(
		50.0f,
		50.0f,
		0.0f
	);
	auto groundObject = new Object("ground", ground);
	groundObject->setEnabled(false);
	groundObject->setScale(objectScale);
	groundObject->setShader("solid");
	groundObject->update();
	engine->addEntity(groundObject);

	//
	dynamic_cast<EntityHierarchy*>(engine->getEntity("tdme.prototype.bvs"))->setScale(objectScale);
	dynamic_cast<EntityHierarchy*>(engine->getEntity("tdme.prototype.bvs"))->update();

	// if re setting up we do leave camera and lighting as it is
	if (resetup == false) {
		// lights
		for (auto i = 1; i < engine->getLightCount(); i++) engine->getLightAt(i)->setEnabled(false);
		auto light0 = engine->getLightAt(0);
		light0->setAmbient(Color4(0.7f, 0.7f, 0.7f, 1.0f));
		light0->setDiffuse(Color4(0.3f, 0.3f, 0.3f, 1.0f));
		light0->setSpecular(Color4(1.0f, 1.0f, 1.0f, 1.0f));
		light0->setPosition(
			Vector4(
				0.0f,
				20.0f * maxAxisDimension,
				20.0f * maxAxisDimension,
				1.0f
			)
		);
		light0->setSpotDirection(Vector3(0.0f, 0.0f, 0.0f).sub(Vector3(light0->getPosition().getX(), light0->getPosition().getY(), light0->getPosition().getZ())).normalize());
		light0->setConstantAttenuation(0.5f);
		light0->setLinearAttenuation(0.0f);
		light0->setQuadraticAttenuation(0.0f);
		light0->setSpotExponent(0.0f);
		light0->setSpotCutOff(180.0f);
		light0->setEnabled(true);

		// cam
		auto cam = engine->getCamera();
		auto lookAt = cam->getLookAt();
		lookAt.set(entityBoundingBoxToUse->getCenter().clone().scale(objectScale));
		Vector3 forwardVector(0.0f, 0.0f, 1.0f);
		// TODO: a.drewke
		Transform _lookFromRotations;
		_lookFromRotations.setTransform(lookFromRotations);
		if (cameraRotationInputHandler != nullptr) {
			cameraRotationInputHandler->setDefaultScale(maxAxisDimension * scale);
			cameraRotationInputHandler->setScale(maxAxisDimension * scale);
		}
		auto forwardVectorTransformed = _lookFromRotations.getTransformMatrix().multiply(forwardVector).scale(cameraRotationInputHandler != nullptr?cameraRotationInputHandler->getScale():maxAxisDimension * scale);
		auto upVector = _lookFromRotations.getRotation(2).getQuaternion().multiply(Vector3(0.0f, 1.0f, 0.0f)).normalize();
		auto lookFrom = lookAt.clone().add(forwardVectorTransformed);
		cam->setLookFrom(lookFrom);
		cam->setLookAt(lookAt);
		cam->setUpVector(upVector);
	} else {
		if (cameraRotationInputHandler != nullptr) {
			cameraRotationInputHandler->setDefaultScale(maxAxisDimension * scale);
		}
	}
}

const string Tools::getRelativeResourcesFileName(const string& applicationRoot, const string& fileName)
{
	auto newFileName = StringTools::replace(fileName, '\\', '/');
	auto cutFileNameIdx = string::npos;
	if (cutFileNameIdx == string::npos) {
		cutFileNameIdx = fileName.rfind("/resources/");
		if (cutFileNameIdx != string::npos) {
			newFileName = StringTools::substring(fileName, cutFileNameIdx + 1);
		}
	}
	if (cutFileNameIdx == string::npos) {
		cutFileNameIdx = fileName.rfind("resources/");
		if (cutFileNameIdx != string::npos) {
			newFileName = StringTools::substring(fileName, cutFileNameIdx);
		}
	}
	return newFileName;
}

const string Tools::getApplicationRootPathName(const string& fileName)
{
	auto newFileName = StringTools::replace(fileName, '\\', '/');
	auto applicationRootPathNameIdx = string::npos;
	if (applicationRootPathNameIdx == string::npos) {
		applicationRootPathNameIdx = fileName.rfind("/resources/");
		if (applicationRootPathNameIdx != string::npos) return StringTools::substring(fileName, 0, applicationRootPathNameIdx);
	}
	if (StringTools::startsWith(fileName, "resources/") == true) {
		return "";
	}
	if (StringTools::endsWith(fileName, "/resources") == true) {
		return StringTools::substring(fileName, 0, fileName.size() - string("/resources").size());
	}
	return "";
}

const string Tools::getApplicationSubPathName(const string& fileName)
{
	auto newFileName = StringTools::replace(fileName, '\\', '/');
	auto applicationSubPathNameIdx = -1;
	if (applicationSubPathNameIdx == -1) {
		applicationSubPathNameIdx = fileName.rfind("/resources/");
		if (applicationSubPathNameIdx != -1) {
			applicationSubPathNameIdx+= string("/resources/").size();
			auto applicationSubPathName = StringTools::substring(fileName, applicationSubPathNameIdx,  fileName.find("/", applicationSubPathNameIdx));
			if (applicationSubPathName == "engine") return applicationSubPathName; else
			if (applicationSubPathName == "project") return applicationSubPathName; else
			if (applicationSubPathName == "installer") return applicationSubPathName; else
				return "engine";
		}
	}
	if (applicationSubPathNameIdx == -1) {
		applicationSubPathNameIdx = fileName.rfind("resources/");
		if (applicationSubPathNameIdx != -1) {
			applicationSubPathNameIdx+= string("resources/").size();
			auto applicationSubPathName = StringTools::substring(fileName, applicationSubPathNameIdx,  fileName.find("/", applicationSubPathNameIdx));
			if (applicationSubPathName == "engine") return applicationSubPathName; else
			if (applicationSubPathName == "project") return applicationSubPathName; else
			if (applicationSubPathName == "installer") return applicationSubPathName; else
				return "engine";
		}
	}
	return "engine";
}

const string Tools::getPathName(const string& fileName)
{
	return FileSystem::getInstance()->getPathName(fileName);
}

const string Tools::getFileName(const string& fileName)
{
	return FileSystem::getInstance()->getFileName(fileName);
}

const string Tools::removeFileExtension(const string& fileName)
{
	auto idx = fileName.rfind('.');
	if (idx == string::npos) {
		return fileName;
	} else {
		return fileName.substr(0, idx);
	}
}

const string Tools::ensureFileExtension(const string& fileName, const string& extension)
{
	if (StringTools::endsWith(StringTools::toLowerCase(fileName), "." + extension) == true) {
		return fileName;
	} else {
		return removeFileExtension(fileName) + "." + extension;
	}
}

const string Tools::getFileExtension(const string& fileName)
{
	auto idx = fileName.rfind('.');
	if (idx == string::npos) {
		return string();
	} else {
		return fileName.substr(idx + 1);
	}
}

void Tools::loadSettings(Application* application) {
	Properties settings;

	// settings
	try {
		settings.load("settings", "settings.properties");
	} catch (FileSystemException &exception) {
		Console::println("Tools::loadSettings(): An error occurred: " + string(exception.what()));
	}

	// 4k
	if (settings.get("4k", "false") == "true") {
		Engine::set4K(true);
	}

	// Window
	application->setWindowWidth(Integer::parse(settings.get("window_width", "1024")));
	application->setWindowHeight(Integer::parse(settings.get("window_height", "768")));
	application->setWindowXPosition(Integer::parse(settings.get("window_x", "-1")));
	application->setWindowYPosition(Integer::parse(settings.get("window_y", "-1")));
	application->setFullScreen(settings.get("fullscreen", "false") == "true");
}

Model* Tools::getGizmoAll() {
	if (gizmoAll == nullptr) {
		gizmoAll = ModelReader::read("resources/engine/models", "gizmo_all.tm");
		ModelTools::prepareForShader(gizmoAll);
		ModelTools::changeFrontFace(gizmoAll); // TODO: why is this needed currently
		gizmoAll->setShaderModel(ShaderModel::SPECULAR);
	}
	return gizmoAll;
}

Model* Tools::getGizmoTranslationScale() {
	if (gizmoTranslationScale == nullptr) {
		gizmoTranslationScale = ModelReader::read("resources/engine/models", "gizmo_transscale.tm");
		ModelTools::prepareForShader(gizmoTranslationScale);
		ModelTools::changeFrontFace(gizmoTranslationScale); // TODO: why is this needed currently
		gizmoTranslationScale->setShaderModel(ShaderModel::SPECULAR);
	}
	return gizmoTranslationScale;
}

Model* Tools::getGizmoTranslation() {
	if (gizmoTranslation == nullptr) {
		gizmoTranslation = ModelReader::read("resources/engine/models", "gizmo_translate.tm");
		ModelTools::prepareForShader(gizmoTranslation);
		ModelTools::changeFrontFace(gizmoTranslation); // TODO: why is this needed currently
		gizmoTranslation->setShaderModel(ShaderModel::SPECULAR);
	}
	return gizmoTranslation;
}

Model* Tools::getGizmoScale() {
	if (gizmoScale == nullptr) {
		gizmoScale = ModelReader::read("resources/engine/models", "gizmo_scale.tm");
		ModelTools::prepareForShader(gizmoScale);
		ModelTools::changeFrontFace(gizmoScale); // TODO: why is this needed currently
		gizmoScale->setShaderModel(ShaderModel::SPECULAR);
	}
	return gizmoScale;
}

Model* Tools::getGizmoRotations() {
	if (gizmoRotations == nullptr) {
		gizmoRotations = ModelReader::read("resources/engine/models", "gizmo_rotate.tm");
		ModelTools::prepareForShader(gizmoRotations);
		ModelTools::changeFrontFace(gizmoRotations); // TODO: why is this needed currently
		gizmoRotations->setShaderModel(ShaderModel::SPECULAR);
	}
	return gizmoRotations;
}

Model* Tools::getDefaultObb() {
	if (defaultOBB == nullptr) {
		OrientedBoundingBox obb(
			Vector3(),
			OrientedBoundingBox::AABB_AXIS_X,
			OrientedBoundingBox::AABB_AXIS_Y,
			OrientedBoundingBox::AABB_AXIS_Z,
			Vector3(0.5f, 0.5f, 0.5f)
		);
		defaultOBB = Primitives::createModel(&obb, "tdme.obb.default");
	}
	return defaultOBB;

}

Tools::ToolsShutdown::~ToolsShutdown() {
	if (Application::hasApplication() == true) Tools::oseDispose();
};

bool Tools::hasFileExtension(const string& fileName, const vector<string>& extensions) {
	auto fileNameLowerCase = StringTools::toLowerCase(fileName);
	for (const auto& extension: extensions) {
		if (StringTools::endsWith(fileNameLowerCase, "." + extension) == true) return true;
	}
	return false;
}
