#include <array>
#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/tools/ThumbnailTool.h>

#include <tdme/application/Application.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/ShaderModel.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/prototype/PrototypeBoundingVolume.h>
#include <tdme/engine/prototype/PrototypeImposterLOD.h>
#include <tdme/engine/prototype/PrototypeLODLevel.h>
#include <tdme/engine/tools/CameraRotationInputHandler.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityHierarchy.h>
#include <tdme/engine/ImposterObject.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/SimplePartition.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Math.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/ModelTools.h>

using std::array;
using std::make_unique;
using std::string;
using std::to_string;
using std::unique_ptr;

using tdme::engine::tools::ThumbnailTool;

using tdme::application::Application;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::ShaderModel;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::model::UpVector;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::prototype::PrototypeImposterLOD;
using tdme::engine::prototype::PrototypeLODLevel;
using tdme::engine::tools::CameraRotationInputHandler;
using tdme::engine::Camera;
using tdme::engine::Color4;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EntityHierarchy;
using tdme::engine::ImposterObject;
using tdme::engine::Light;
using tdme::engine::Object;
using tdme::engine::SceneConnector;
using tdme::engine::SimplePartition;
using tdme::engine::Texture;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Quaternion;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::ModelTools;

Engine* ThumbnailTool::osEngine = nullptr;
ThumbnailTool::ToolsShutdown ThumbnailTool::toolsShutdown;

void ThumbnailTool::oseInit()
{
	if (osEngine != nullptr) return;
	osEngine = Engine::createOffScreenInstance(128, 128, false, true, false);
	osEngine->setPartition(new SimplePartition());
	setDefaultLight(osEngine->getLightAt(0));
}

void ThumbnailTool::oseDispose()
{
	if (osEngine == nullptr) return;
	osEngine->dispose();
	delete osEngine;
}

void ThumbnailTool::oseThumbnail(Prototype* prototype, vector<uint8_t>& pngData)
{
	oseInit();
	Vector3 objectScale;
	Transform oseLookFromRotations;
	oseLookFromRotations.addRotation(Vector3(0.0f, 1.0f, 0.0f), -45.0f);
	oseLookFromRotations.addRotation(Vector3(1.0f, 0.0f, 0.0f), -45.0f);
	oseLookFromRotations.addRotation(Vector3(0.0f, 0.0f, 1.0f), 0.0f);
	oseLookFromRotations.update();
	ThumbnailTool::setupPrototype(prototype, osEngine, oseLookFromRotations, 1, objectScale, nullptr, 1.0f);
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

void ThumbnailTool::setDefaultLight(Light* light)
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

float ThumbnailTool::computeMaxAxisDimension(BoundingBox* boundingBox)
{
	auto maxAxisDimension = 0.0f;
	Vector3 dimension = boundingBox->getMax().clone().sub(boundingBox->getMin());
	if (dimension.getX() > maxAxisDimension) maxAxisDimension = dimension.getX();
	if (dimension.getY() > maxAxisDimension) maxAxisDimension = dimension.getY();
	if (dimension.getZ() > maxAxisDimension) maxAxisDimension = dimension.getZ();
	return maxAxisDimension;
}

Model* ThumbnailTool::createGroundModel(float width, float depth, float y)
{
	auto modelId = "tdme.ground" + to_string(static_cast<int>(width * 100)) + "x" + to_string(static_cast<int>(depth * 100)) + "@" + to_string(static_cast<int>(y * 100));
	auto ground = make_unique<Model>(modelId, modelId, UpVector::Y_UP, RotationOrder::ZYX, nullptr);
	//
	auto groundMaterial = make_unique<Material>("ground");
	groundMaterial->setSpecularMaterialProperties(make_unique<SpecularMaterialProperties>().release());
	groundMaterial->getSpecularMaterialProperties()->setSpecularColor(Color4(0.0f, 0.0f, 0.0f, 1.0f));
	groundMaterial->getSpecularMaterialProperties()->setDiffuseTexture("resources/engine/textures", "groundplate.png");
	//
	auto groundNode = make_unique<Node>(ground.get(), nullptr, "ground", "ground");
	vector<Vector3> groundVertices;
	groundVertices.emplace_back(-width/2, y, -depth/2);
	groundVertices.emplace_back(-width/2, y, +depth/2);
	groundVertices.emplace_back(+width/2, y, +depth/2);
	groundVertices.emplace_back(+width/2, y, -depth/2);
	vector<Vector3> groundNormals;
	groundNormals.emplace_back(0.0f, 1.0f, 0.0f);
	vector<Vector2> groundTextureCoordinates;
	groundTextureCoordinates.emplace_back(0.0f, 0.0f);
	groundTextureCoordinates.emplace_back(0.0f, depth);
	groundTextureCoordinates.emplace_back(width, depth);
	groundTextureCoordinates.emplace_back(width, 0.0f);
	vector<Face> groundFacesGround;
	groundFacesGround.emplace_back(groundNode.get(), 0, 1, 2, 0, 0, 0, 0, 1, 2);
	groundFacesGround.emplace_back(groundNode.get(), 2, 3, 0, 0, 0, 0, 2, 3, 0);
	FacesEntity nodeFacesEntityGround(groundNode.get(), "ground.facesentity");
	nodeFacesEntityGround.setMaterial(groundMaterial.get());
	vector<FacesEntity> nodeFacesEntities;
	nodeFacesEntityGround.setFaces(groundFacesGround);
	nodeFacesEntities.push_back(nodeFacesEntityGround);
	groundNode->setVertices(groundVertices);
	groundNode->setNormals(groundNormals);
	groundNode->setTextureCoordinates(groundTextureCoordinates);
	groundNode->setFacesEntities(nodeFacesEntities);
	ground->getNodes()["ground"] = groundNode.get();
	ground->getSubNodes()["ground"] = groundNode.get();
	groundNode.release();
	//
	ground->getMaterials()["ground"] = groundMaterial.get();
	groundMaterial.release();
	//
	ModelTools::prepareForIndexedRendering(ground.get());
	//
	return ground.release();
}

Model* ThumbnailTool::createGridModel()
{
	//
	auto groundPlate = make_unique<Model>("tdme.grid", "tdme.grid", UpVector::Y_UP, RotationOrder::XYZ, make_unique<BoundingBox>(Vector3(0.0f, -0.01f, 0.0f), Vector3(10000.0f, +0.01f, 10000.0f)).release());
	//
	auto groundPlateMaterial = make_unique<Material>("ground");
	groundPlateMaterial->setSpecularMaterialProperties(make_unique<SpecularMaterialProperties>().release());
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
	//
	auto groundNode = make_unique<Node>(groundPlate.get(), nullptr, "grid", "grid");
	vector<Vector3> groundVertices;
	groundVertices.emplace_back(0.0f, 0.0f, 0.0f);
	groundVertices.emplace_back(0.0f, 0.0f, 10000.0f);
	groundVertices.emplace_back(10000.0f, 0.0f, 10000.0f);
	groundVertices.emplace_back(10000.0f, 0.0f, 0.0f);
	vector<Vector3> groundNormals;
	groundNormals.emplace_back(0.0f, 1.0f, 0.0f);
	vector<Vector2> groundTextureCoordinates;
	groundTextureCoordinates.emplace_back(0.0f, 0.0f);
	groundTextureCoordinates.emplace_back(0.0f, 10000.0f);
	groundTextureCoordinates.emplace_back(10000.0f, 10000.0f);
	groundTextureCoordinates.emplace_back(10000.0f, 0.0f);
	vector<Face> groundFacesGround;
	groundFacesGround.emplace_back(groundNode.get(), 0, 1, 2, 0, 0, 0, 0, 1, 2);
	groundFacesGround.emplace_back(groundNode.get(), 2, 3, 0, 0, 0, 0, 2, 3, 0);
	FacesEntity nodeFacesEntityGround(groundNode.get(), "tdme.sceneeditor.grid.facesentity");
	nodeFacesEntityGround.setMaterial(groundPlateMaterial.get());
	nodeFacesEntityGround.setFaces(groundFacesGround);
	vector<FacesEntity> nodeFacesEntities;
	nodeFacesEntities.push_back(nodeFacesEntityGround);
	groundNode->setVertices(groundVertices);
	groundNode->setNormals(groundNormals);
	groundNode->setTextureCoordinates(groundTextureCoordinates);
	groundNode->setFacesEntities(nodeFacesEntities);
	groundPlate->getNodes()[groundNode->getId()] = groundNode.get();
	groundPlate->getSubNodes()[groundNode->getId()] = groundNode.get();
	groundNode.release();
	//
	groundPlate->getMaterials()["grid"] = groundPlateMaterial.get();
	groundPlateMaterial.release();
	//
	ModelTools::prepareForIndexedRendering(groundPlate.get());
	//
	return groundPlate.release();
}

void ThumbnailTool::setupPrototype(Prototype* prototype, Engine* engine, const Transform& lookFromRotations, int lodLevel, Vector3& objectScale, CameraRotationInputHandler* cameraRotationInputHandler, float scale, bool resetup)
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
					for (const auto& parameterName: Engine::getShaderParameterNames(prototype->getShader())) {
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
			for (const auto& parameterName: Engine::getShaderParameterNames(prototype->getShader())) {
				auto parameterValue = prototype->getShaderParameters().getShaderParameter(parameterName);
				object->setShaderParameter(parameterName, parameterValue);
			}
			engine->addEntity(modelEntity);
		}
	}

	//
	auto entityBoundingBoxToUse = entityBoundingBox != nullptr?entityBoundingBox:entityBoundingBoxFallback.get();

	// do a feasible scale
	float maxAxisDimension = ThumbnailTool::computeMaxAxisDimension(entityBoundingBoxToUse);
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

ThumbnailTool::ToolsShutdown::~ToolsShutdown() {
	if (Application::hasApplication() == true) ThumbnailTool::oseDispose();
};
