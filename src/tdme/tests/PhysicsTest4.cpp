#include <tdme/tests/PhysicsTest4.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/TerrainMesh.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/ObjectModel.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Primitives.h>
#include <tdme/utilities/Time.h>

using std::string;
using std::to_string;

using tdme::tests::PhysicsTest4;

using tdme::application::Application;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::physics::Body;
using tdme::engine::physics::World;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::TerrainMesh;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::Object;
using tdme::engine::ObjectModel;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Primitives;
using tdme::utilities::Time;

PhysicsTest4::PhysicsTest4()
{
	Application::setLimitFPS(true);
	engine = Engine::getInstance();
	world = new World("world");
}

PhysicsTest4::~PhysicsTest4()
{
	delete world;
}

void PhysicsTest4::main(int argc, char** argv)
{
	auto physicsTest4 = new PhysicsTest4();
	physicsTest4->run(argc, argv, "PhysicsTest4", physicsTest4);
}

void PhysicsTest4::display()
{
	auto start = Time::getCurrentMillis();
	world->update(1.0f / 60.0f);
	world->synch(engine);
	engine->display();
	auto end = Time::getCurrentMillis();
	auto rendererStatistics = engine->getRendererStatistics();
	Console::println(
		string("PhysicsTest4::display::") + to_string(end - start) + "ms; " +
		"clear calls: " + to_string(rendererStatistics.clearCalls) + ", " +
		"render calls: " + to_string(rendererStatistics.renderCalls) + ", " +
		"compute calls: " + to_string(rendererStatistics.computeCalls) + ", " +
		"tris: " + to_string(rendererStatistics.triangles) + ", " +
		"points: " + to_string(rendererStatistics.points) + ", " +
		"line points: " + to_string(rendererStatistics.linePoints) + ", " +
		"buffer up: " + to_string(rendererStatistics.bufferUploads) + ", " +
		"texture up: " + to_string(rendererStatistics.textureUploads) + ", " +
		"render passes: " + to_string(rendererStatistics.renderPasses) + ", " +
		"draw cmds: " + to_string(rendererStatistics.drawCommands) + ", " +
		"submits: " + to_string(rendererStatistics.submits) + ", " +
		"dis.tex: " + to_string(rendererStatistics.disposedTextures) + ", " +
		"dis.buf: " + to_string(rendererStatistics.disposedBuffers)
	);
}

void PhysicsTest4::dispose()
{
	engine->dispose();
}

void PhysicsTest4::initialize()
{
	engine->initialize();
	Object* entity;
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(15.0f);
	cam->setLookFrom(Vector3(0.0f, 4.0f, -6.0f));
	cam->setLookAt(Vector3(0.0f, 0.0f, 0.0f));
	cam->setUpVector(cam->computeUpVector(cam->getLookFrom(), cam->getLookAt()));
	auto light0 = engine->getLightAt(0);
	light0->setAmbient(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	light0->setDiffuse(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	light0->setSpecular(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	light0->setPosition(Vector4(0.0f, 20000.0f, 0.0f, 0.0f));
	light0->setSpotDirection(Vector3(0.0f, 0.0f, 0.0f).sub(Vector3(light0->getPosition().getX(), light0->getPosition().getY(), light0->getPosition().getZ())));
	light0->setConstantAttenuation(0.5f);
	light0->setLinearAttenuation(0.0f);
	light0->setQuadraticAttenuation(0.0f);
	light0->setSpotExponent(0.0f);
	light0->setSpotCutOff(180.0f);
	light0->setEnabled(true);
	auto box = bvDeleter.add(new OrientedBoundingBox(Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X, OrientedBoundingBox::AABB_AXIS_Y, OrientedBoundingBox::AABB_AXIS_Z, Vector3(0.1f, 0.1f, 0.1f)));
	auto boxModel = modelDeleter.add(Primitives::createModel(box, "box_model"));
	boxModel->getMaterials()["primitive"]->getSpecularMaterialProperties()->setAmbientColor(Color4(0.8f, 0.5f, 0.5f, 1.0f));
	boxModel->getMaterials()["primitive"]->getSpecularMaterialProperties()->setDiffuseColor(Color4(1.0f, 0.0f, 0.0f, 1.0f));
	entity = new Object("box", boxModel);
	entity->setContributesShadows(true);
	entity->setReceivesShadows(true);
	entity->setTranslation(Vector3(0.0f, 3.0f, 0.0f));
	entity->update();
	engine->addEntity(entity);
	world->addRigidBody("box", true, RIGID_TYPEID_STANDARD, entity->getTransform(), 0.0f, 1.0f, 100.0f, Vector3(1.0f, 1.0f, 1.0f), {box});
	world->getBody("box")->setLinearVelocity(world->getBody("box")->getLinearVelocity().clone().setX(1.0f));
	try {
		auto _terrainModel = modelDeleter.add(ModelReader::read("resources/tests/models/physicstest4", "TestGround.fbx.tm"));
		entity = new Object("terrain", _terrainModel);
		entity->setTranslation(Vector3(1.75f, 0.0f, -1.65f));
		entity->setReceivesShadows(true);
		entity->update();
		engine->addEntity(entity);
		ObjectModel terrainModel(_terrainModel);
		auto terrainMesh = new TerrainMesh(&terrainModel, entity->getTransform());
		world->addStaticRigidBody("ground", true, RIGID_TYPEID_STANDARD, Transform(), 0.5f, {terrainMesh});
	} catch (Exception& exception) {
		Console::print(string("PhysicsTest4::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
		Application::exit(1);
	}
}

void PhysicsTest4::reshape(int32_t width, int32_t height)
{
	engine->reshape(width, height);
}

void PhysicsTest4::onChar(int key, int x, int y) {
}

void PhysicsTest4::onKeyDown(int key, int keyCode, int x, int y, bool repeat, int modifiers) {
}

void PhysicsTest4::onKeyUp(int key, int keyCode, int x, int y) {
}

void PhysicsTest4::onMouseDragged(int x, int y) {
}

void PhysicsTest4::onMouseMoved(int x, int y) {
}

void PhysicsTest4::onMouseButton(int button, int state, int x, int y) {
}

void PhysicsTest4::onMouseWheel(int button, int direction, int x, int y) {
}
