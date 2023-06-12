#include <tdme/tests/PhysicsTest5.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/Time.h>

#include <tdme/application/Application.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/physics/BodyHierarchy.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/EntityHierarchy.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/ObjectModel.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ObjectDeleter.h>
#include <tdme/utilities/Primitives.h>

using std::string;
using std::to_string;

using tdme::tests::PhysicsTest5;

using tdme::utilities::Time;

using tdme::application::Application;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::physics::Body;
using tdme::engine::physics::BodyHierarchy;
using tdme::engine::physics::World;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::EntityHierarchy;
using tdme::engine::Light;
using tdme::engine::Object;
using tdme::engine::ObjectModel;
using tdme::engine::Rotation;
using tdme::engine::SceneConnector;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ObjectDeleter;
using tdme::utilities::Primitives;

PhysicsTest5::PhysicsTest5()
{
	Application::setLimitFPS(true);
	keyLeft = false;
	keyRight = false;
	keyUp = false;
	keyDown = false;
	keyW = false;
	keyA = false;
	keyS = false;
	keyD = false;
	engine = Engine::getInstance();
	world = new World("world");
}

PhysicsTest5::~PhysicsTest5()
{
	delete world;
}

void PhysicsTest5::main(int argc, char** argv)
{
	auto physicsTest5 = new PhysicsTest5();
	physicsTest5->run(argc, argv, "PhysicsTest5", physicsTest5);
}

void PhysicsTest5::display()
{
	{
		auto velocity = world->getBody("bot")->getLinearVelocity();
		if (keyLeft) velocity.setX(8.0f); else
		if (keyRight) velocity.setX(-8.0f); else
			velocity.setX(0.0f);
		if (keyUp) velocity.setZ(8.0f); else
		if (keyDown) velocity.setZ(-8.0f); else
			velocity.setZ(0.0f);
		world->getBody("bot")->setLinearVelocity(velocity);
	}

	//
	Transform weaponAttachmentTransform;
	weaponAttachmentTransform.fromMatrix(dynamic_cast<Object*>(dynamic_cast<EntityHierarchy*>(engine->getEntity("bot"))->getEntity("bot"))->getNodeTransformMatrix("attach_weapon_left"), RotationOrder::ZYX);
	weaponAttachmentTransform.setScale(weaponAttachmentTransform.getScale() * 0.6f);
	weaponAttachmentTransform.update();
	dynamic_cast<Object*>(dynamic_cast<EntityHierarchy*>(engine->getEntity("bot"))->getEntity("weapon_left"))->setTransform(weaponAttachmentTransform);

	//
	auto start = Time::getCurrentMillis();
	auto fps = 60.0f;
	world->update(1.0f / fps);
	world->synchronize(engine);
	engine->display();
	auto end = Time::getCurrentMillis();
	auto rendererStatistics = engine->getRendererStatistics();
	/*
	Console::println(
		string("PhysicsTest5::display::") + to_string(end - start) + "ms; " +
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
	*/
}

void PhysicsTest5::dispose()
{
	engine->dispose();
}

void PhysicsTest5::initialize()
{
	engine->initialize();
	engine->addPostProcessingProgram("ssao");
	Object* entity;
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(15.0f);
	cam->setLookFrom(Vector3(0.0f, 4.0f * 2.5f, -6.0f * 2.5f));
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
	auto ground = bvDeleter.add(new OrientedBoundingBox(Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X, OrientedBoundingBox::AABB_AXIS_Y, OrientedBoundingBox::AABB_AXIS_Z, Vector3(8.0f, 1.0f, 8.0f)));
	auto groundModel = modelDeleter.add(Primitives::createModel(ground, "ground_model"));
	groundModel->getMaterials()["primitive"]->getSpecularMaterialProperties()->setAmbientColor(Color4(0.8f, 0.8f, 0.8f, 1.0f));
	groundModel->getMaterials()["primitive"]->getSpecularMaterialProperties()->setDiffuseColor(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	entity = new Object("ground", groundModel);
	entity->setReceivesShadows(true);
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody("ground", true, RIGID_TYPEID_STANDARD, entity->getTransform(), 0.5f, {ground});
	auto side = bvDeleter.add(new OrientedBoundingBox(Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X, OrientedBoundingBox::AABB_AXIS_Y, OrientedBoundingBox::AABB_AXIS_Z, Vector3(1.0f, 16.0f, 8.0f)));
	auto sideModel = modelDeleter.add(Primitives::createModel(side, "side_model"));
	sideModel->getMaterials()["primitive"]->getSpecularMaterialProperties()->setAmbientColor(Color4(0.8f, 0.8f, 0.8f, 1.0f));
	sideModel->getMaterials()["primitive"]->getSpecularMaterialProperties()->setDiffuseColor(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	auto nearFar = bvDeleter.add(new OrientedBoundingBox(Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X, OrientedBoundingBox::AABB_AXIS_Y, OrientedBoundingBox::AABB_AXIS_Z, Vector3(8.0f, 16.0f, 1.0f)));
	auto nearFarModel = modelDeleter.add(Primitives::createModel(nearFar, "far_model"));
	nearFarModel->getMaterials()["primitive"]->getSpecularMaterialProperties()->setAmbientColor(Color4(0.8f, 0.8f, 0.8f, 1.0f));
	nearFarModel->getMaterials()["primitive"]->getSpecularMaterialProperties()->setDiffuseColor(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	entity = new Object("far", nearFarModel);
	entity->setTranslation(Vector3(0.0f, 0.0f, +9.0f));
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody("far", true, RIGID_TYPEID_STANDARD, entity->getTransform(), 0.5f, {nearFar});
	entity = new Object("near", nearFarModel);
	entity->setTranslation(Vector3(0.0f, 0.0f, -9.0f));
	entity->setEffectColorMul(Color4(1.0f, 1.0f, 1.0f, 0.0f));
	entity->update();
	entity->setEnabled(false);
	engine->addEntity(entity);
	world->addStaticRigidBody("near", true, RIGID_TYPEID_STANDARD, entity->getTransform(), 0.5f, {nearFar});
	entity = new Object("sideright", sideModel);
	entity->setTranslation(Vector3(-9.0f, 0.0f, 0.0f));
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody("sideright", true, RIGID_TYPEID_STANDARD, entity->getTransform(), 0.5f, {side});
	entity = new Object("sideleft", sideModel);
	entity->setTranslation(Vector3(9.0f, 0.0f, 0.0f));
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody("sideleft", true, RIGID_TYPEID_STANDARD, entity->getTransform(), 0.5f, {side});
	auto box = bvDeleter.add(new OrientedBoundingBox(Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X, OrientedBoundingBox::AABB_AXIS_Y, OrientedBoundingBox::AABB_AXIS_Z, Vector3(0.6f, 0.6f, 0.6f)));
	auto boxModel = modelDeleter.add(Primitives::createModel(box, "box_model"));
	boxModel->getMaterials()["primitive"]->getSpecularMaterialProperties()->setAmbientColor(Color4(0.8f, 0.5f, 0.5f, 1.0f));
	boxModel->getMaterials()["primitive"]->getSpecularMaterialProperties()->setDiffuseColor(Color4(1.0f, 0.0f, 0.0f, 1.0f));
	auto sphere = bvDeleter.add(new Sphere(Vector3(0.0f, 0.0f, 0.0f), 0.4f));
	auto sphereModel = modelDeleter.add(Primitives::createModel(sphere, "sphere_model"));
	sphereModel->getMaterials()["primitive"]->getSpecularMaterialProperties()->setAmbientColor(Color4(0.5f, 0.8f, 0.8f, 1.0f));
	sphereModel->getMaterials()["primitive"]->getSpecularMaterialProperties()->setDiffuseColor(Color4(0.0f, 1.0f, 1.0f, 1.0f));
	for (auto i = 0; i < SPHERE_COUNT; i++) {
		entity = new Object("sphere" + to_string(i), sphereModel);
		entity->setContributesShadows(true);
		entity->setReceivesShadows(true);
		entity->setTranslation(Vector3(0.0f, 3.0f + (i * 1.0f), 0.0f));
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody("sphere" + to_string(i), true, RIGID_TYPEID_STANDARD, entity->getTransform(), 0.75f, 0.4f, 10.0f, Vector3(1.0f, 1.0f, 1.0f), {sphere});
	}
	try {
		auto botPrototype = PrototypeReader::read("resources/botrts", "unit_bot.tmodel");
		// create bot body in engine
		Transform botTransform;
		botTransform.addRotation(Vector3(0.0f, 1.0f, 0.0f), 180.0f);
		botTransform.setScale(botTransform.getScale() * 2.0f);
		botTransform.update();
		auto botEntityHierarchy = new EntityHierarchy("bot");
		botEntityHierarchy->setTransform(botTransform);
		botEntityHierarchy->addEntity(SceneConnector::createEntity(botPrototype, "bot", Transform()));
		botEntityHierarchy->update();
		engine->addEntity(botEntityHierarchy);

		// create bot body in physics
		auto botBody = dynamic_cast<BodyHierarchy*>(SceneConnector::createBody(world, botPrototype, "bot", botTransform, SceneConnector::RIGIDBODY_TYPEID_STANDARD, true));

		// we only need scale for now as parent transform for attaching weapon to bot
		Transform botTransformScale;
		botTransformScale.setScale(botTransform.getScale());
		botTransformScale.update();

		// weapon attachment point in space of bot model without applied transform
		Transform weaponAttachmentLocalTransform;
		weaponAttachmentLocalTransform.fromMatrix(dynamic_cast<Object*>(dynamic_cast<EntityHierarchy*>(engine->getEntity("bot"))->getEntity("bot"))->getNodeTransformMatrix("attach_weapon_left"), RotationOrder::ZYX);
		weaponAttachmentLocalTransform.setScale(weaponAttachmentLocalTransform.getScale() * 0.6f);
		weaponAttachmentLocalTransform.update();

		// create weapon in engine
		auto weaponPrototype = PrototypeReader::read("resources/botrts", "weapon_flamethrower.tmodel");
		botEntityHierarchy->addEntity(SceneConnector::createEntity(weaponPrototype, "weapon_left", weaponAttachmentLocalTransform));
		botEntityHierarchy->update();

		// create weapon in physics
		botBody->addBody("weapon_left", weaponAttachmentLocalTransform, weaponPrototype->getBoundingVolumePrimitives(), "bot");
		botBody->update();

		{
			auto box2 = bvDeleter.add(new OrientedBoundingBox(Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X, OrientedBoundingBox::AABB_AXIS_Y, OrientedBoundingBox::AABB_AXIS_Z, Vector3(0.50f, 0.25f, 0.25f)));
			auto box2Model = modelDeleter.add(Primitives::createModel(box2, "box2_model"));

			auto box2Object = new Object("box2", box2Model);
			box2Object->setTranslation(Vector3(1.0f, 0.0f, 0.0f));
			box2Object->setScale(Vector3(2.0f, 2.0f, 2.0f));
			box2Object->addRotation(Vector3(0.0f, 1.0f, 0.0f), 90.0f);
			box2Object->update();
			botEntityHierarchy->addEntity(box2Object, "weapon_left");
			botEntityHierarchy->update();

			//
			// create weapon in physics
			botBody->addBody("box2_model", box2Object->getTransform(), { box2 }, "weapon_left");
			botBody->update();
		}

		//world->addRigidBody("cone", true, RIGID_TYPEID_STANDARD, entity->getTransform(), 0.0f, 1.0f, 100.0f, Vector3(1.0f, 1.0f, 1.0f), {coneBoundingVolume});
		/*
		auto _tire = modelDeleter.add(ModelReader::read("resources/tests/models/tire", "tire.dae"));
		auto tireBoundingVolume = bvDeleter.add(new ConvexMesh(objectModelDeleter.add(new ObjectModel(_tire))));
		entity = new Object("tire", _tire);
		entity->setContributesShadows(true);
		entity->setReceivesShadows(true);
		entity->setTranslation(Vector3(0.0f, 1.0f, 0.0f));
		entity->setScale(Vector3(5.0f, 5.0f, 5.0f));
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody("tire", true, RIGID_TYPEID_STANDARD, entity->getTransform(), 0.0f, 1.0f, 100.0f, Vector3(1.0f, 1.0f, 1.0f), {tireBoundingVolume});
		//
		world->addFixedJoint("tire|cone", world->getBody("tire"), world->getBody("cone"));
		*/
	} catch (Exception& exception) {
		Console::print(string("PhysicsTest5::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
		Application::exit(1);
	}
}

void PhysicsTest5::reshape(int32_t width, int32_t height)
{
	engine->reshape(width, height);
}

void PhysicsTest5::onChar(int key, int x, int y) {
}

void PhysicsTest5::onKeyDown(int key, int keyCode, int x, int y, bool repeat, int modifiers) {
	auto keyChar = Character::toLowerCase(key);
	if (keyChar == 'w') keyW = true;
	if (keyChar == 'a') keyA = true;
	if (keyChar == 's') keyS = true;
	if (keyChar == 'd') keyD = true;
	if (keyCode == KEYBOARD_KEYCODE_LEFT) keyLeft = true;
	if (keyCode == KEYBOARD_KEYCODE_RIGHT) keyRight = true;
	if (keyCode == KEYBOARD_KEYCODE_UP) keyUp = true;
	if (keyCode == KEYBOARD_KEYCODE_DOWN) keyDown = true;
}

void PhysicsTest5::onKeyUp(int key, int keyCode, int x, int y) {
	auto keyChar = Character::toLowerCase(key);
	if (keyChar == 'w') keyW = false;
	if (keyChar == 'a') keyA = false;
	if (keyChar == 's') keyS = false;
	if (keyChar == 'd') keyD = false;
	if (keyCode == KEYBOARD_KEYCODE_LEFT) keyLeft = false;
	if (keyCode == KEYBOARD_KEYCODE_RIGHT) keyRight = false;
	if (keyCode == KEYBOARD_KEYCODE_UP) keyUp = false;
	if (keyCode == KEYBOARD_KEYCODE_DOWN) keyDown = false;
}

void PhysicsTest5::onMouseDragged(int x, int y) {
}

void PhysicsTest5::onMouseMoved(int x, int y) {
}

void PhysicsTest5::onMouseButton(int button, int state, int x, int y) {
}

void PhysicsTest5::onMouseWheel(int button, int direction, int x, int y) {
}
