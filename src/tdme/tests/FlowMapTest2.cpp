#include <tdme/tests/FlowMapTest2.h>

#include <string>

#include <tdme/utilities/Time.h>

#include <tdme/application/Application.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/scenes/SceneReader.h>
#include <tdme/engine/fileio/scenes/SceneReader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeBoundingVolume.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/FlowMap.h>
#include <tdme/utilities/FlowMapCell.h>
#include <tdme/utilities/PathFinding.h>
#include <tdme/utilities/Primitives.h>

using std::string;
using std::to_string;

using tdme::tests::FlowMapTest2;

using tdme::application::Application;
using tdme::application::InputEventHandler;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::scenes::SceneReader;
using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::physics::Body;
using tdme::engine::physics::World;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::scene::Scene;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::Rotation;
using tdme::engine::SceneConnector;
using tdme::engine::SceneConnector;
using tdme::engine::Timing;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utilities::Console;
using tdme::utilities::FlowMap;
using tdme::utilities::FlowMapCell;
using tdme::utilities::PathFinding;
using tdme::utilities::Primitives;
using tdme::utilities::Time;

FlowMapTest2::FlowMapTest2()
{
	Application::setLimitFPS(true);
	engine = Engine::getInstance();
	world = new World();
	timeLastUpdate = -1;
}

FlowMapTest2::~FlowMapTest2() {
	if (flowMap != nullptr) flowMap->releaseReference();
	delete world;
	delete emptyModel;
	delete playerModelPrototype;
	delete pathFinding;
}

void FlowMapTest2::main(int argc, char** argv)
{
	auto flowMapTest2 = new FlowMapTest2();
	flowMapTest2->run(argc, argv, "FlowMapTest2", flowMapTest2);
}

void FlowMapTest2::display()
{
	if (pause != true) {
		//if (startPlayerCellPosition.clone().sub(startPlayerObject->getTranslation()).computeLength() < 0.1f) {
		{
			auto cell = flowMap->getCell(startPlayerObject->getTranslation().getX(), startPlayerObject->getTranslation().getZ());
			if (cell != nullptr) {
				startPlayerPathFindingNode = flowMap->getPath()[Math::min(cell->getPathNodeIdx() + 1, flowMap->getPath().size() - 1)];
				startPlayerCellDirection = cell->getDirection();
				auto pathFindingNodeDirection = startPlayerPathFindingNode - startPlayerObject->getTranslation();
				auto pcdDotPND = 0.0f;
				if (pathFindingNodeDirection.computeLengthSquared() > Math::square(Math::EPSILON)) {
					pathFindingNodeDirection.normalize();
					pcdDotPND = Math::clamp(Vector3::computeDotProduct(startPlayerCellDirection, pathFindingNodeDirection), 0.0f, 1.0f);
				}
				Console::println(
					to_string(startPlayerCellDirection.getX()) + ", " +
					to_string(startPlayerCellDirection.getY()) + ", " +
					to_string(startPlayerCellDirection.getZ()) + "; " +
					to_string(pathFindingNodeDirection.getX()) + ", " +
					to_string(pathFindingNodeDirection.getY()) + ", " +
					to_string(pathFindingNodeDirection.getZ()) + "; " +
					to_string(pcdDotPND)
				);
				startPlayerMovementDirection = (startPlayerCellDirection * (1.0f - pcdDotPND)+ pathFindingNodeDirection * pcdDotPND).normalize();

				startPlayerCellPosition = startPlayerObject->getTranslation().clone().add(startPlayerCellDirection.clone().scale(flowMap->getStepSize()));
				if (startPlayerObject->getAnimation() != "walk") startPlayerObject->setAnimation("walk");
				auto yRotationAngle = Vector3::computeAngle(Vector3(0.0f, 0.0f, 1.0f), cell->getDirection(), Vector3(0.0f, 1.0f, 0.0f));
				startPlayerObject->setRotationAngle(0, yRotationAngle);
				{
					auto pathFindingNodeId = "pathfindingnodecurrent";
					auto pathFindingNodeObject = new Object3D(pathFindingNodeId, emptyModel);
					pathFindingNodeObject->setScale(Vector3(2.0f, 2.0f, 2.0f));
					pathFindingNodeObject->setTranslation(startPlayerPathFindingNode + Vector3(0.0f, 0.4f, 0.0f));
					pathFindingNodeObject->addRotation(Vector3(0.0f, 0.0f, 1.0f), 90.0f);
					pathFindingNodeObject->setDisableDepthTest(true);
					pathFindingNodeObject->setEffectColorMul(Color4(0.0f, 0.0f, 0.0f, 1.0f));
					pathFindingNodeObject->update();
					engine->addEntity(pathFindingNodeObject);
				}
				{
					auto flowDirectionEntityId = "flowdirectioncurrent";
					auto yRotationAngle = Vector3::computeAngle(Vector3(0.0f, 0.0f, 1.0f), pathFindingNodeDirection, Vector3(0.0f, 1.0f, 0.0f));
					auto cellObject = new Object3D(flowDirectionEntityId, emptyModel);
					cellObject->setScale(Vector3(5.0f, 5.0f, 5.0f));
					cellObject->setTranslation(Vector3(-0.0f, 0.5f, -0.0f));
					cellObject->addRotation(Vector3(0.0f, 1.0f, 0.0f), yRotationAngle - 90.0f);
					cellObject->setDisableDepthTest(true);
					cellObject->update();
					engine->addEntity(cellObject);
				}

			} else {
				startPlayerObject->setAnimation("still");
				startPlayerCellDirection = Vector3();
			}
		}
		{
			if (endPlayerObject1->getTranslation().clone().sub(startPlayerObject->getTranslation()).computeLength() < 1.0f ||
				endPlayerObject2->getTranslation().clone().sub(startPlayerObject->getTranslation()).computeLength() < 1.0f) {
				doPathFinding();
			} else {
				startPlayerObject->setTranslation(startPlayerObject->getTranslation() + startPlayerMovementDirection * 2.0f / 60.0f);
				startPlayerObject->update();
			}
		}
	}
	engine->display();
}

void FlowMapTest2::dispose()
{
	engine->dispose();
}

void FlowMapTest2::initialize()
{
	engine->initialize();
	SceneReader::read("resources/tests/levels/pathfinding", "test.flowmap.tscene", scene);
	SceneConnector::setLights(engine, scene);
	SceneConnector::addScene(engine, scene, false, false, false, false);
	SceneConnector::addScene(world, scene);
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(15.0f);
	cam->setLookFrom(scene.getCenter() + Vector3(0.0f, 20.0f, 0.0f));
	cam->setLookAt(scene.getCenter());
	cam->setUpVector(cam->computeUpVector(cam->getLookFrom(), cam->getLookAt()));
	emptyModel = ModelReader::read("resources/engine/models", "empty.tm");
	playerModelPrototype = PrototypeReader::read("resources/tests/models/mementoman", "mementoman.tmodel");
	playerModelPrototype->getModel()->addAnimationSetup("walk", 0, 23, true);
	playerModelPrototype->getModel()->addAnimationSetup("still", 24, 99, true);
	playerModelPrototype->getModel()->addAnimationSetup("death", 109, 169, false);
	startPlayerObject = new Object3D("startPlayerObject", playerModelPrototype->getModel());
	startPlayerObject->addRotation(Vector3(0.0f, 1.0f, 0.0f), 90.0f);
	startPlayerObject->setTranslation(Vector3(2.5f, 0.25f, 0.5f));
	startPlayerObject->update();
	startPlayerObject->setAnimation("still");
	startPlayerObject->setContributesShadows(playerModelPrototype->isContributesShadows());
	startPlayerObject->setReceivesShadows(playerModelPrototype->isReceivesShadows());
	engine->addEntity(startPlayerObject);
	endPlayerObject1 = new Object3D("endPlayerObject1", playerModelPrototype->getModel());
	endPlayerObject1->addRotation(Vector3(0.0f, 1.0f, 0.0f), 90.0f);
	endPlayerObject1->setTranslation(Vector3(2.5f, 0.25f, 0.5f));
	endPlayerObject1->update();
	endPlayerObject1->setAnimation("still");
	endPlayerObject1->setContributesShadows(playerModelPrototype->isContributesShadows());
	endPlayerObject1->setReceivesShadows(playerModelPrototype->isReceivesShadows());
	endPlayerObject1->setEffectColorAdd(Color4(1.0f, 0.0f, 0.0f, 0.0f));
	endPlayerObject1->setEffectColorMul(Color4(1.0f, 0.0f, 0.0f, 1.0f));
	engine->addEntity(endPlayerObject1);
	endPlayerObject2 = new Object3D("endPlayerObject2", playerModelPrototype->getModel());
	endPlayerObject2->addRotation(Vector3(0.0f, 1.0f, 0.0f), 90.0f);
	endPlayerObject2->setTranslation(Vector3(2.5f, 0.25f, 0.5f));
	endPlayerObject2->update();
	endPlayerObject2->setAnimation("still");
	endPlayerObject2->setContributesShadows(playerModelPrototype->isContributesShadows());
	endPlayerObject2->setReceivesShadows(playerModelPrototype->isReceivesShadows());
	endPlayerObject2->setEffectColorAdd(Color4(1.0f, 0.0f, 0.0f, 0.0f));
	endPlayerObject2->setEffectColorMul(Color4(1.0f, 0.0f, 0.0f, 1.0f));
	engine->addEntity(endPlayerObject2);
	pathPositions.push_back(Vector3(-17.0f, 0.25f, -0.5f));
	pathPositions.push_back(Vector3(0.0f, 0.25f, 1.5f));
	pathPositions.push_back(Vector3(0.0f, 0.25f, -9.5f));
	pathFinding = new PathFinding(world, true, 1000, 2.0f, 0.5f, 0.5f);
	doPathFinding();
}

void FlowMapTest2::reshape(int32_t width, int32_t height)
{
	engine->reshape(width, height);
}

void FlowMapTest2::doPathFinding() {
	if (flowMap != nullptr) {
		flowMap->releaseReference();
		flowMap = nullptr;
	}
	startPlayerObject->update();
	startPlayerCellPosition.set(pathPositions[(int)(Math::random() * pathPositions.size())]);
	startPlayerObject->setTranslation(startPlayerCellPosition);
	startPlayerObject->update();
	startPlayerCellDirection.set(0.0f, 0.0f, 0.0f);
	endPlayerObject1->setTranslation(pathPositions[(int)(Math::random() * pathPositions.size())]);
	endPlayerObject1->update();
	endPlayerObject2->setTranslation(pathPositions[(int)(Math::random() * pathPositions.size())]);
	endPlayerObject2->update();
	vector<Vector3> path;
	pathFinding->findPath(
		startPlayerObject->getTransformations().getTranslation(),
		endPlayerObject1->getTransformations().getTranslation(),
		SceneConnector::RIGIDBODY_TYPEID_STATIC,
		path
	);
	Console::println("Found a path: steps: " + to_string(path.size()));
	auto center = scene.getBoundingBox()->getCenter();
	auto depth = Math::ceil(scene.getBoundingBox()->getDimensions().getZ());
	auto width = Math::ceil(scene.getBoundingBox()->getDimensions().getX());

	if (path.size() > 12) {
		vector<Vector3> pathA;
		vector<Vector3> pathB;
		for (auto i = 0; i < path.size(); i++) {
			if (i < (path.size() / 2)) {
				pathA.push_back(path[i]);
			} else {
				if (pathB.empty() == true) {
					pathB.push_back(pathA[pathA.size() - 5]);
					pathB.push_back(pathA[pathA.size() - 4]);
					pathB.push_back(pathA[pathA.size() - 3]);
					pathB.push_back(pathA[pathA.size() - 2]);
					pathB.push_back(pathA[pathA.size() - 1]);
				}
				pathB.push_back(path[i]);
			}
		}
		Console::println(to_string(pathA.size()));
		Console::println(to_string(pathB.size()));
		flowMap = pathFinding->createFlowMap(
			{
				pathA[pathA.size() - 1]
			},
			center,
			5.0f,
			5.0f,
			SceneConnector::RIGIDBODY_TYPEID_STATIC,
			pathA,
			false,
			true
		);
		auto flowMap2 = pathFinding->createFlowMap(
			{
				endPlayerObject1->getTransformations().getTranslation(),
				endPlayerObject2->getTransformations().getTranslation(),
			},
			center,
			5.0f,
			5.0f,
			SceneConnector::RIGIDBODY_TYPEID_STATIC,
			pathB,
			true,
			true
		);
		flowMap->merge(flowMap2);
		flowMap2->releaseReference();
	} else {
		flowMap = pathFinding->createFlowMap(
			{
				endPlayerObject1->getTransformations().getTranslation(),
				endPlayerObject2->getTransformations().getTranslation(),
			},
			center,
			5.0f,
			5.0f,
			SceneConnector::RIGIDBODY_TYPEID_STATIC,
			path,
			true,
			true
		);
	}
	{
		auto i = 0;
		while(true == true) {
			auto flowDirectionEntityId = "flowdirection." + to_string(i);
			if (engine->getEntity(flowDirectionEntityId) == nullptr) break;
			engine->removeEntity(flowDirectionEntityId);
			i++;
		}
	}
	{
		auto i = 0;
		while(true == true) {
			auto flowDirectionEntityId = "pathfindingnode." + to_string(i);
			if (engine->getEntity(flowDirectionEntityId) == nullptr) break;
			engine->removeEntity(flowDirectionEntityId);
			i++;
		}
	}
	if (flowMap == nullptr) return;
	{
		auto i = 0;
		auto j = 0;
		for (auto z = -depth / 2; z <= depth / 2; z+= flowMap->getStepSize())
		for (auto x = -width / 2; x <= width / 2; x+= flowMap->getStepSize()) {
			auto cellPosition = Vector3(
				x + center.getX(),
				0.0f,
				z + center.getZ()
			);
			auto cell = flowMap->getCell(cellPosition.getX(), cellPosition.getZ());
			if (cell == nullptr) continue;
			{
				auto flowDirectionEntityId = "flowdirection." + to_string(i);
				auto yRotationAngle = Vector3::computeAngle(Vector3(0.0f, 0.0f, 1.0f), cell->getDirection(), Vector3(0.0f, 1.0f, 0.0f));
				auto cellObject = new Object3D(flowDirectionEntityId, emptyModel);
				cellObject->setScale(Vector3(0.5f, 0.5f, 0.5f));
				cellObject->setTranslation(cellPosition + Vector3(0.0f, 0.25f, 0.0f));
				cellObject->addRotation(Vector3(0.0f, 1.0f, 0.0f), yRotationAngle - 90.0f);
				cellObject->setDisableDepthTest(true);
				if (cell->isBorderCell() == true && cell->isMissingNeighborCells() == true) cellObject->setEffectColorMul(Color4(1.0f, 0.0f, 0.0f, 1.0f)); else
					if (cell->isBorderCell() == true) cellObject->setEffectColorMul(Color4(0.0f, 1.0f, 0.0f, 1.0f)); else
						if (cell->isMissingNeighborCells() == true) cellObject->setEffectColorMul(Color4(0.0f, 0.0f, 1.0f, 1.0f));
				cellObject->update();
				engine->addEntity(cellObject);
				i++;
			}
			/*
			{
				auto pathFindingNodeId = "pathfindingnode." + to_string(j);
				auto pathFindingNodeObject = new Object3D(pathFindingNodeId, emptyModel);
				pathFindingNodeObject->setScale(Vector3(2.0f, 2.0f, 2.0f));
				pathFindingNodeObject->setTranslation(flowMap->getPath()[cell->getPathIdx()] + Vector3(0.0f, 0.4f, 0.0f));
				pathFindingNodeObject->addRotation(Vector3(0.0f, 0.0f, 1.0f), 90.0f);
				pathFindingNodeObject->setDisableDepthTest(true);
				pathFindingNodeObject->setEffectColorMul(Color4(0.0f, 0.0f, 0.0f, 1.0f));
				pathFindingNodeObject->update();
				engine->addEntity(pathFindingNodeObject);
				j++;
			}
			*/
		}
	}
}

void FlowMapTest2::onChar(unsigned int key, int x, int y) {
	if (key == ' ') pause = pause == true?false:true;
}

void FlowMapTest2::onKeyDown (unsigned char key, int x, int y) {
}

void FlowMapTest2::onKeyUp(unsigned char key, int x, int y) {
}

void FlowMapTest2::onSpecialKeyDown (int key, int x, int y) {
}

void FlowMapTest2::onSpecialKeyUp(int key, int x, int y) {
}

void FlowMapTest2::onMouseDragged(int x, int y) {
}

void FlowMapTest2::onMouseMoved(int x, int y) {
}

void FlowMapTest2::onMouseButton(int button, int state, int x, int y) {
}

void FlowMapTest2::onMouseWheel(int button, int direction, int x, int y) {
}
