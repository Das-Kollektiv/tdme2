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
		for (auto& combatUnit: combatUnits) {
			auto cell = flowMap->getCell(combatUnit.object->getTranslation().getX(), combatUnit.object->getTranslation().getZ());
			if (cell != nullptr) {
				auto pathFindingNode = flowMap->getPath()[Math::min(cell->getPathNodeIdx() + 1, flowMap->getPath().size() - 1)];
				combatUnit.cellDirection = cell->getDirection();
				auto pathFindingNodeDirection = pathFindingNode - combatUnit.object->getTranslation();
				auto pcdDotPND = 0.0f;
				if (pathFindingNodeDirection.computeLengthSquared() > Math::square(Math::EPSILON)) {
					pathFindingNodeDirection.normalize();
					pcdDotPND = Math::clamp(Vector3::computeDotProduct(combatUnit.cellDirection, pathFindingNodeDirection), 0.0f, 1.0f);
				}
				Console::println(
					to_string(combatUnit.cellDirection.getX()) + ", " +
					to_string(combatUnit.cellDirection.getY()) + ", " +
					to_string(combatUnit.cellDirection.getZ()) + "; " +
					to_string(pathFindingNodeDirection.getX()) + ", " +
					to_string(pathFindingNodeDirection.getY()) + ", " +
					to_string(pathFindingNodeDirection.getZ()) + "; " +
					to_string(pcdDotPND)
				);
				combatUnit.movementDirection = (combatUnit.cellDirection * (1.0f - pcdDotPND)+ pathFindingNodeDirection * pcdDotPND).normalize();

				if (combatUnit.object->getAnimation() != "walk") combatUnit.object->setAnimation("walk");
				auto yRotationAngle = Vector3::computeAngle(Vector3(0.0f, 0.0f, 1.0f), cell->getDirection(), Vector3(0.0f, 1.0f, 0.0f));
				combatUnit.object->setRotationAngle(0, yRotationAngle);
				{
					auto pathFindingNodeId = "pathfindingnodecurrent";
					auto pathFindingNodeObject = new Object3D(pathFindingNodeId, emptyModel);
					pathFindingNodeObject->setScale(Vector3(2.0f, 2.0f, 2.0f));
					pathFindingNodeObject->setTranslation(pathFindingNode + Vector3(0.0f, 0.4f, 0.0f));
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
				combatUnit.object->setAnimation("still");
				combatUnit.cellDirection = Vector3();
			}
		}
		for (auto& combatUnit: combatUnits) {
			if (path[path.size() - 1].clone().sub(combatUnit.object->getTranslation()).computeLength() < 1.0f) {
				doPathFinding();
			} else {
				combatUnit.object->setTranslation(combatUnit.object->getTranslation() + combatUnit.movementDirection * 2.0f / 60.0f);
				combatUnit.object->update();
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
	formationLinePrototype = ModelReader::read("resources/tests/levels/pathfinding", "Formation_Line.tm");
	playerModelPrototype = PrototypeReader::read("resources/tests/models/mementoman", "mementoman.tmodel");
	playerModelPrototype->getModel()->addAnimationSetup("walk", 0, 23, true);
	playerModelPrototype->getModel()->addAnimationSetup("still", 24, 99, true);
	playerModelPrototype->getModel()->addAnimationSetup("death", 109, 169, false);
	int combatUnitIdx = 0;
	CombatUnit combatUnit;
	combatUnit.object = new Object3D("combatunit." + to_string(combatUnitIdx++), playerModelPrototype->getModel());
	combatUnit.object->addRotation(Vector3(0.0f, 1.0f, 0.0f), 90.0f);
	combatUnit.object->setTranslation(Vector3(2.5f, 0.25f, 0.5f));
	combatUnit.object->update();
	combatUnit.object->setAnimation("still");
	combatUnit.object->setContributesShadows(playerModelPrototype->isContributesShadows());
	combatUnit.object->setReceivesShadows(playerModelPrototype->isReceivesShadows());
	combatUnits.push_back(combatUnit);
	engine->addEntity(combatUnit.object);
	endPositions.push_back(Vector3(-17.0f, 0.25f, -0.5f));
	endPositions.push_back(Vector3(0.0f, 0.25f, 1.5f));
	endPositions.push_back(Vector3(0.0f, 0.25f, -9.5f));
	pathFinding = new PathFinding(world, true, 1000, 2.0f, 0.5f, 0.5f);
	doPathFinding();

	//
	for (auto i = 0; i < combatUnitFormationTransformations.size(); i++) {
		auto emptyName = "Waypoint_" + to_string(i);
		Matrix4x4 transformationsMatrix;
		if (formationLinePrototype->computeTransformationsMatrix(
			emptyName,
			formationLinePrototype->getImportTransformationsMatrix(),
			transformationsMatrix) == false) {
			Console::println("FlowMapTest2::initialize(): Missing '" + emptyName + "'");
		}
		combatUnitFormationTransformations[i].fromMatrix(transformationsMatrix, RotationOrder::ZYX);
	}
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
	for (auto& combatUnit: combatUnits) {
		combatUnit.object->update();
		combatUnit.object->setTranslation(endPositions[(int)(Math::random() * endPositions.size())]);
		combatUnit.object->update();
		combatUnit.cellDirection.set(0.0f, 0.0f, 0.0f);
	}
	pathFinding->findPath(
		combatUnits[0].object->getTransformations().getTranslation(),
		endPositions[(int)(Math::random() * endPositions.size())],
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
					pathB.push_back(pathA[pathA.size() - 8]);
					pathB.push_back(pathA[pathA.size() - 7]);
					pathB.push_back(pathA[pathA.size() - 6]);
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
			false
		);
		auto flowMap2 = pathFinding->createFlowMap(
			{
				path[path.size() - 1]
			},
			center,
			5.0f,
			5.0f,
			SceneConnector::RIGIDBODY_TYPEID_STATIC,
			pathB,
			true
		);
		flowMap->merge(flowMap2);
		flowMap2->releaseReference();
	} else {
		flowMap = pathFinding->createFlowMap(
			{
				path[path.size() - 1]
			},
			center,
			5.0f,
			5.0f,
			SceneConnector::RIGIDBODY_TYPEID_STATIC,
			path,
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
