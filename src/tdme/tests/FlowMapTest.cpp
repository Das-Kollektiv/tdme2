#include <tdme/tests/FlowMapTest.h>

#include <string>

#include <tdme/utils/Time.h>

#include <tdme/application/Application.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/LinesObject3D.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/PrimitiveModel.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/tools/leveleditor/logic/Level.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/files/LevelFileImport.h>
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/PathFinding.h>

using std::string;
using std::to_string;

using tdme::tests::FlowMapTest;

using tdme::application::Application;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::LinesObject3D;
using tdme::engine::Object3D;
using tdme::engine::Rotation;
using tdme::engine::Timing;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::physics::Body;
using tdme::engine::physics::World;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::PrimitiveModel;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::tools::leveleditor::logic::Level;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::files::LevelFileImport;
using tdme::tools::shared::files::ModelMetaDataFileImport;
using tdme::utils::Console;
using tdme::utils::PathFinding;
using tdme::utils::Time;

FlowMapTest::FlowMapTest()
{
	Application::setLimitFPS(true);
	engine = Engine::getInstance();
	world = new World();
	timeLastUpdate = -1;
}

void FlowMapTest::main(int argc, char** argv)
{
	auto flowMapTest = new FlowMapTest();
	flowMapTest->run(argc, argv, "FlowMapTest");
}

void FlowMapTest::display()
{
	auto stepSize = 0.5f;
	auto cellPosition = Vector3(
		Math::floor(startPointObject->getTranslation().getX() / stepSize) * stepSize,
		0.0f,
		Math::floor(startPointObject->getTranslation().getZ() / stepSize) * stepSize
	);
	auto cell = flowMap->getCell(cellPosition.getX(), cellPosition.getZ());
	if (cell != nullptr/* && cell->isWalkable() == false*/) {
		Console::println(
			"xxx:" +
			to_string(cell->getDirection().getX()) + ", " +
			to_string(cell->getDirection().getY()) + ", " +
			to_string(cell->getDirection().getZ())
		);
		startPointObject->setAnimation("walk");
		startPointObject->setTranslation(startPointObject->getTranslation() + cell->getDirection() * stepSize / 60.0f);
		startPointObject->update();
	}
	/*
	if (frames > 60 * 15) {
		doPathFinding();
		frames = 0;
	}
	*/
	engine->display();
	frames++;
}

void FlowMapTest::dispose()
{
	engine->dispose();
}

void FlowMapTest::initialize()
{
	engine->initialize();
	LevelFileImport::doImport("resources/tests/levels/pathfinding", "test.tl", &level);
	Level::setLight(engine, &level);
	Level::addLevel(engine, &level, false, false, false);
	Level::addLevel(world, &level);
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(15.0f);
	cam->setLookFrom(level.getCenter() + Vector3(0.0f, 10.0f, 0.0f));
	cam->setLookAt(level.getCenter());
	cam->setUpVector(cam->computeUpVector(cam->getLookFrom(), cam->getLookAt()));
	emptyModel = ModelReader::read("resources/engine/tools/leveleditor/models", "empty.dae");
	playerModelEntity = ModelMetaDataFileImport::doImport("resources/tests/models/mementoman", "mementoman.dae.tmm");
	playerModelEntity->getModel()->addAnimationSetup("walk", 0, 23, true);
	playerModelEntity->getModel()->addAnimationSetup("still", 24, 99, true);
	playerModelEntity->getModel()->addAnimationSetup("death", 109, 169, false);
	startPointObject = new Object3D("startpointobject", playerModelEntity->getModel());
	startPointObject->addRotation(Vector3(0.0f, 1.0f, 0.0f), 90.0f);
	startPointObject->setTranslation(Vector3(2.5f, 0.25f, 0.5f));
	startPointObject->update();
	startPointObject->setAnimation("still");
	startPointObject->setContributesShadows(playerModelEntity->isContributesShadows());
	startPointObject->setReceivesShadows(playerModelEntity->isReceivesShadows());
	engine->addEntity(startPointObject);
	endPointObject = new Object3D("endpointobject", playerModelEntity->getModel());
	endPointObject->addRotation(Vector3(0.0f, 1.0f, 0.0f), 90.0f);
	endPointObject->setTranslation(Vector3(2.5f, 0.25f, 0.5f));
	endPointObject->update();
	endPointObject->setAnimation("still");
	endPointObject->setContributesShadows(playerModelEntity->isContributesShadows());
	endPointObject->setReceivesShadows(playerModelEntity->isReceivesShadows());
	endPointObject->setEffectColorAdd(Color4(1.0f, 0.0f, 0.0f, 0.0f));
	endPointObject->setEffectColorMul(Color4(1.0f, 0.5f, 0.5f, 1.0f));
	engine->addEntity(endPointObject);
	pathPositions.push_back(Vector3(-2.5f, 0.25f, -4.5f));
	pathPositions.push_back(Vector3(-2.5f, 0.25f, 0.5f));
	pathPositions.push_back(Vector3(2.5f, 0.25f, 0.5f));
	pathPositions.push_back(Vector3(2.5f, 0.25f, -4.5f));
	pathFinding = new PathFinding(world, false, 1000, 2.0f, 0.5f);
	doPathFinding();
}

void FlowMapTest::reshape(int32_t width, int32_t height)
{
	engine->reshape(width, height);
}

void FlowMapTest::doPathFinding() {
	if (flowMap != nullptr) {
		delete flowMap;
		flowMap = nullptr;
	}
	startPointObject->setTranslation(endPointObject->getTransformations().getTranslation());
	startPointObject->update();
	endPointObject->setTranslation(pathPositions[(int)(Math::random() * pathPositions.size())]);
	endPointObject->update();
	map<string, PathFinding::DijkstraCellStruct> dijkstraCellMap;
	flowMap = pathFinding->createFlowMap(
		dijkstraCellMap,
		endPointObject->getTransformations().getTranslation(), 
		level.getBoundingBox()->getCenter(),
		Math::ceil(level.getBoundingBox()->getDimensions().getZ()),
		Math::ceil(level.getBoundingBox()->getDimensions().getX()),
		Level::RIGIDBODY_TYPEID_STATIC
	);
	auto i = 0;
	while(true == true) {
		auto flowDirectionEntityId = "flowdirection." + to_string(i);
		if (engine->getEntity(flowDirectionEntityId) == nullptr) break;
		engine->removeEntity(flowDirectionEntityId);
		i++;
	}
	Console::println("deleted " + to_string(i) + " entities");
	if (flowMap == nullptr) return;
	i = 0;

	auto stepSize = 0.5f;
	auto center = level.getBoundingBox()->getCenter();
	auto depth = Math::ceil(level.getBoundingBox()->getDimensions().getZ());
	auto width = Math::ceil(level.getBoundingBox()->getDimensions().getX());
	for (auto z = -depth / 2; z < depth / 2; z+= stepSize)
	for (auto x = -width / 2; x < width / 2; x+= stepSize) {
		auto cellPosition = Vector3(
			Math::floor((x + center.getX()) / stepSize) * stepSize,
			0.0f,
			Math::floor((z + center.getZ()) / stepSize) * stepSize
		);
		auto cell = flowMap->getCell(cellPosition.getX(), cellPosition.getZ());
		if (cell == nullptr || cell->isWalkable() == false) continue;
		auto flowDirectionEntityId = "flowdirection." + to_string(i);
		auto yRotationAngle = Vector3::computeAngle(Vector3(0.0f, 0.0f, 1.0f), cell->getDirection(), Vector3(0.0f, 1.0f, 0.0f));
		auto cellObject = new Object3D(flowDirectionEntityId, emptyModel);
		cellObject->setScale(Vector3(0.25f, 0.25f, 0.25f));
		cellObject->setTranslation(cellPosition + Vector3(0.0f, 0.25f, 0.0f));
		cellObject->addRotation(Vector3(0.0f, 1.0f, 0.0f), yRotationAngle - 90.0f);
		cellObject->setDisableDepthTest(true);
		cellObject->update();
		engine->addEntity(cellObject);
		i++;
	}
	{
		auto startPosition = Vector3(2.5f, 0.25f, 0.5f);
		auto cellPosition = Vector3(
			Math::floor(startPosition.getX() / stepSize) * stepSize,
			0.0f,
			Math::floor(startPosition.getZ() / stepSize) * stepSize
		);
		auto cell = flowMap->getCell(cellPosition.getX(), cellPosition.getZ());
		Console::println(
			to_string(cellPosition.getX()) + ", " +
			to_string(cellPosition.getY()) + ", " +
			to_string(cellPosition.getZ()) + "("  +
			to_string(cell != nullptr) + ", " +
			to_string(cell != nullptr?cell->isWalkable():false)
		);
	}
	/*
	Console::println(to_string(dijkstraCellMap.size()));
	for (auto it: dijkstraCellMap) {
		auto& cell = it.second;
		Console::println(
			cell.id + " = " + 
			to_string(cell.position.getX()) + ", " +
			to_string(cell.position.getY()) + ", " +
			to_string(cell.position.getZ())
		);
		auto flowDirectionEntityId = "flowdirection." + to_string(i);
		auto cellObject = new Object3D(flowDirectionEntityId, emptyModel);
		cellObject->setScale(Vector3(0.25f, 0.25f, 0.25f));
		cellObject->setTranslation(cell.position + Vector3(0.0f, 2.5f, 0.0f));
		cellObject->setEffectColorMul(Color4(cell.costs / 15.0f, 0.0f, 0.0f, 1.0f));
		cellObject->setEffectColorAdd(Color4(cell.costs / 15.0f, 0.0f, 0.0f, 0.0f));
		cellObject->update();
		engine->addEntity(cellObject);
		i++;
	}
	*/

	Console::println("added " + to_string(i) + " entities");
}