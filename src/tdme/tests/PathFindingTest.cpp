#include <tdme/tests/PathFindingTest.h>

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/Time.h>

#include <tdme/application/Application.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/scenes/SceneReader.h>
#include <tdme/engine/Color4.h>
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
#include <tdme/engine/Object.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/PathFinding.h>
#include <tdme/utilities/Primitives.h>

using std::make_unique;
using std::string;
using std::to_string;
using std::unique_ptr;

using tdme::tests::PathFindingTest;

using tdme::application::Application;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::scenes::SceneReader;
using tdme::engine::Color4;
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
using tdme::engine::Object;
using tdme::engine::Rotation;
using tdme::engine::SceneConnector;
using tdme::engine::Timing;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utilities::Console;
using tdme::utilities::PathFinding;
using tdme::utilities::Primitives;
using tdme::utilities::Time;

PathFindingTest::PathFindingTest()
{
	Application::setLimitFPS(true);
	engine = Engine::getInstance();
	world = make_unique<World>("world");
	timeLastUpdate = -1;
	pathIdx = 0;
	playerXDirection = 0.0f;
	playerZDirection = 0.0f;
}

PathFindingTest::~PathFindingTest()
{
}

int PathFindingTest::main(int argc, char** argv)
{
	auto pathFindingTest = new PathFindingTest();
	return pathFindingTest->run(argc, argv, "PathFindingTest");
}

void PathFindingTest::determinePlayerMovementDirection() {
	if (pathIdx >= path.size()) {
		playerXDirection = 0.0f;
		playerZDirection = 0.0f;
		return;
	}
	if (Math::abs(playerObject->getTranslation().getX() - path[pathIdx].getX()) < 0.01f)  {
		playerXDirection = 0.0f;
	} else
	if (playerObject->getTranslation().getX() < path[pathIdx].getX())  {
		playerXDirection = +1.0f;
	} else
	if (playerObject->getTranslation().getX() > path[pathIdx].getX())  {
		playerXDirection = -1.0f;
	}
	if (Math::abs(playerObject->getTranslation().getZ() - path[pathIdx].getZ()) < 0.01f)  {
		playerZDirection = 0.0f;
	} else
	if (playerObject->getTranslation().getZ() < path[pathIdx].getZ())  {
		playerZDirection = +1.0f;
	} else
	if (playerObject->getTranslation().getZ() > path[pathIdx].getZ())  {
		playerZDirection = -1.0f;
	}
}

bool PathFindingTest::determinePlayerCompletedStepX() {
	return
		(playerXDirection > 0.1f && playerObject->getTranslation().getX() >= path[pathIdx].getX()) ||
		(playerXDirection < -0.1f && playerObject->getTranslation().getX() <= path[pathIdx].getX()) ||
		(Math::abs(playerObject->getTranslation().getX() - path[pathIdx].getX()) < 0.01f);
}

bool PathFindingTest::determinePlayerCompletedStepZ() {
	return
		(playerZDirection > 0.1f && playerObject->getTranslation().getZ() >= path[pathIdx].getZ()) ||
		(playerZDirection < -0.1f && playerObject->getTranslation().getZ() <= path[pathIdx].getZ()) ||
		(Math::abs(playerObject->getTranslation().getZ() - path[pathIdx].getZ()) < 0.01f);
}

void PathFindingTest::display()
{
	bool hadMovement = false;
	auto playerTranslation = playerObject->getTranslation();
	if (determinePlayerCompletedStepX() == false) {
		if (hadMovement == false) playerTranslation.add(Vector3(playerXDirection * engine->getTiming()->getDeltaTime() / 1000.0f * 4.0f, 0.0f, 0.0f));
		playerObject->getRotation(0).setAngle(playerXDirection > 0.1f?90.0f:270.0f);
		hadMovement = true;
	} else {
		playerTranslation.setX(path[pathIdx].getX());
	}
	if (determinePlayerCompletedStepZ() == false) {
		if (hadMovement == false) playerTranslation.add(Vector3(0.0f, 0.0f, playerZDirection * engine->getTiming()->getDeltaTime() / 1000.0f * 4.0f));
		playerObject->getRotation(0).setAngle(playerZDirection > 0.1f?0.0f:180.0f);
		hadMovement = true;
	} else {
		playerTranslation.setZ(path[pathIdx].getZ());
	}
	playerObject->setTranslation(playerTranslation);
	playerObject->update();
	if (hadMovement == false) {
		pathIdx = pathIdx + 1;
		if (pathIdx >= path.size()) {
			pathIdx = 0;
			doPathFinding();
		}
		determinePlayerMovementDirection();
	}
	engine->display();
}

void PathFindingTest::dispose()
{
	engine->dispose();
}

void PathFindingTest::initialize()
{
	engine->initialize();
	scene = unique_ptr<Scene>(SceneReader::read("resources/tests/levels/pathfinding", "test.tscene"));
	SceneConnector::setLights(engine, scene.get());
	SceneConnector::addScene(engine, scene.get(), false, false, false, false, false);
	SceneConnector::addScene(world.get(), scene.get());
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(15.0f);
	cam->setLookFrom(Vector3(0.0f, 10.0f, -6.0f));
	cam->setLookAt(scene->getCenter());
	cam->setUpVector(cam->computeUpVector(cam->getLookFrom(), cam->getLookAt()));
	playerModelPrototype = unique_ptr<Prototype>(PrototypeReader::read("resources/tests/models/mementoman", "mementoman.tmodel"));
	playerModelPrototype->getModel()->addAnimationSetup("walk", 0, 23, true);
	playerModelPrototype->getModel()->addAnimationSetup("still", 24, 99, true);
	playerModelPrototype->getModel()->addAnimationSetup("death", 109, 169, false);
	playerObject = new Object("player", playerModelPrototype->getModel());
	playerObject->addRotation(Vector3(0.0f, 1.0f, 0.0f), 90.0f);
	playerObject->setTranslation(Vector3(2.5f, 0.25f, 0.5f));
	playerObject->update();
	playerObject->setAnimation("walk");
	playerObject->setContributesShadows(playerModelPrototype->isContributesShadows());
	playerObject->setReceivesShadows(playerModelPrototype->isReceivesShadows());
	engine->addEntity(playerObject);
	pathIdx = 0;
	pathPositions.push_back(Vector3(-2.5f, 0.25f, -4.5f));
	pathPositions.push_back(Vector3(-2.5f, 0.25f, 0.5f));
	pathPositions.push_back(Vector3(2.5f, 0.25f, 0.5f));
	pathPositions.push_back(Vector3(2.5f, 0.25f, -4.5f));
	pathFinding = make_unique<PathFinding>(world.get());
	doPathFinding();
	determinePlayerMovementDirection();
}

void PathFindingTest::reshape(int32_t width, int32_t height)
{
	engine->reshape(width, height);
}

void PathFindingTest::doPathFinding() {
	if (pathFinding->findPath(
			playerObject->getTransform().getTranslation(),
			pathPositions[(int)(Math::random() * pathPositions.size())],
			SceneConnector::BODY_TYPEID_STATIC,
			path
		) == true) {
		Console::println("Found a path: steps: " + to_string(path.size()));
	} else {
		Console::println("Found no path");
	}
}
