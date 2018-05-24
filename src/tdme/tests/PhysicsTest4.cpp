#include <tdme/tests/PhysicsTest4.h>

#include <string>

#include <tdme/utils/Time.h>

#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/PrimitiveModel.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

using std::string;
using std::to_string;

using tdme::tests::PhysicsTest4;

using tdme::utils::Time;

using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::Object3DModel;
using tdme::engine::Rotation;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::physics::RigidBody;
using tdme::engine::physics::World;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::PrimitiveModel;
using tdme::engine::primitives::Sphere;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utils::Console;
using tdme::utils::Exception;

constexpr int32_t PhysicsTest4::CAPSULE_COUNT;

PhysicsTest4::PhysicsTest4()
{
	keyLeft = false;
	keyRight = false;
	keyUp = false;
	keyDown = false;
	engine = Engine::getInstance();
	world = new World();
}

void PhysicsTest4::main(int argc, char** argv)
{
	auto physicsTest4 = new PhysicsTest4();
	physicsTest4->run(argc, argv, "PhysicsTest4", physicsTest4);
}

void PhysicsTest4::display()
{
	auto capsuleBig1 = world->getRigidBody("capsulebig1");
	if (keyLeft)
		capsuleBig1->getLinearVelocity().setX(8.0f);
	else if (keyRight)
		capsuleBig1->getLinearVelocity().setX(-8.0f);
	else
		capsuleBig1->getLinearVelocity().setX(0.0f);
	if (keyUp)
		capsuleBig1->getLinearVelocity().setZ(8.0f);
	else if (keyDown)
		capsuleBig1->getLinearVelocity().setZ(-8.0f);
	else
		capsuleBig1->getLinearVelocity().setZ(0.0f);
	auto capsuleBig2 = world->getRigidBody("capsulebig2");
	if (keyA)
		capsuleBig2->getLinearVelocity().setX(6.0f);
	else if (keyD)
		capsuleBig2->getLinearVelocity().setX(-6.0f);
	else
		capsuleBig2->getLinearVelocity().setX(0.0f);
	if (keyW)
		capsuleBig2->getLinearVelocity().setZ(6.0f);
	else if (keyS)
		capsuleBig2->getLinearVelocity().setZ(-6.0f);
	else
		capsuleBig2->getLinearVelocity().setZ(0.0f);
	auto fps = 60.0f;
	world->update(1.0f / fps);
	world->synch(engine);
	engine->display();

}

void PhysicsTest4::dispose()
{
	engine->dispose();
}

void PhysicsTest4::initialize()
{
	engine->initialize();
	Object3D* entity;
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(50.0f);
	cam->getLookFrom().set(0.0f, 4.0f * 2.5f, -6.0f * 2.5f);
	cam->getLookAt().set(0.0f, 0.0f, 0.0f);
	cam->computeUpVector(cam->getLookFrom(), cam->getLookAt(), cam->getUpVector());
	auto light0 = engine->getLightAt(0);
	light0->getAmbient().set(1.0f, 1.0f, 1.0f, 1.0f);
	light0->getDiffuse().set(0.5f, 0.5f, 0.5f, 1.0f);
	light0->getSpecular().set(1.0f, 1.0f, 1.0f, 1.0f);
	light0->getPosition().set(0.0f, 20000.0f, 0.0f, 1.0f);
	light0->getSpotDirection().set(0.0f, 0.0f, 0.0f).sub(Vector3(light0->getPosition().getX(), light0->getPosition().getY(), light0->getPosition().getZ()));
	light0->setConstantAttenuation(0.5f);
	light0->setLinearAttenuation(0.0f);
	light0->setQuadraticAttenuation(0.0f);
	light0->setSpotExponent(0.0f);
	light0->setSpotCutOff(180.0f);
	light0->setEnabled(true);
	auto ground = new OrientedBoundingBox(Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X, OrientedBoundingBox::AABB_AXIS_Y, OrientedBoundingBox::AABB_AXIS_Z, Vector3(8.0f, 1.0f, 8.0f));
	auto groundModel = PrimitiveModel::createModel(ground, "ground_model");
	(*groundModel->getMaterials())["tdme.primitive.material"]->getAmbientColor().set(0.8f, 0.8f, 0.8f, 1.0f);
	(*groundModel->getMaterials())["tdme.primitive.material"]->getDiffuseColor().set(1.0f, 1.0f, 1.0f, 1.0f);
	entity = new Object3D("ground", groundModel);
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody("ground", true, RIGID_TYPEID_STANDARD, entity->getTransformations(), ground, 0.5f);
	auto side = new OrientedBoundingBox(Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X, OrientedBoundingBox::AABB_AXIS_Y, OrientedBoundingBox::AABB_AXIS_Z, Vector3(1.0f, 16.0f, 8.0f));
	auto sideModel = PrimitiveModel::createModel(side, "side_model");
	(*sideModel->getMaterials())["tdme.primitive.material"]->getAmbientColor().set(0.8f, 0.8f, 0.8f, 1.0f);
	(*sideModel->getMaterials())["tdme.primitive.material"]->getDiffuseColor().set(1.0f, 1.0f, 1.0f, 1.0f);
	auto nearFar = new OrientedBoundingBox(Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X, OrientedBoundingBox::AABB_AXIS_Y, OrientedBoundingBox::AABB_AXIS_Z, Vector3(8.0f, 16.0f, 1.0f));
	auto nearFarModel = PrimitiveModel::createModel(nearFar, "far_model");
	(*nearFarModel->getMaterials())["tdme.primitive.material"]->getAmbientColor().set(0.8f, 0.8f, 0.8f, 1.0f);
	(*nearFarModel->getMaterials())["tdme.primitive.material"]->getDiffuseColor().set(1.0f, 1.0f, 1.0f, 1.0f);
	entity = new Object3D("far", nearFarModel);
	entity->setTranslation(Vector3(0.0f, 0.0f, +9.0f));
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody("far", true, RIGID_TYPEID_STANDARD, entity->getTransformations(), nearFar, 0.5f);
	entity = new Object3D("near", nearFarModel);
	entity->setTranslation(Vector3(0.0f, 0.0f, -9.0f));
	entity->getEffectColorMul().set(1.0f, 1.0f, 1.0f, 0.0f);
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody("near", true, RIGID_TYPEID_STANDARD, entity->getTransformations(), nearFar, 0.5f);
	entity = new Object3D("sideright", sideModel);
	entity->setTranslation(Vector3(-9.0f, 0.0f, 0.0f));
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody("sideright", true, RIGID_TYPEID_STANDARD, entity->getTransformations(), side, 0.5f);
	entity = new Object3D("sideleft", sideModel);
	entity->setTranslation(Vector3(9.0f, 0.0f, 0.0f));
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody("sideleft", true, RIGID_TYPEID_STANDARD, entity->getTransformations(), side, 0.5f);
	auto capsule = new Capsule(Vector3(0.0f, 0.25f, 0.0f), Vector3(0.0f, 9.75f, 0.0f), 0.25f);
	auto capsuleModel = PrimitiveModel::createModel(capsule, "capsule_model");
	(*capsuleModel->getMaterials())["tdme.primitive.material"]->getAmbientColor().set(0.8f, 0.0f, 0.8f, 1.0f);
	(*capsuleModel->getMaterials())["tdme.primitive.material"]->getDiffuseColor().set(1.0f, 0.0f, 1.0f, 1.0f);
	for (auto i = 0; i < CAPSULE_COUNT; i++) {
		entity = new Object3D("capsule" + to_string(i), capsuleModel);
		entity->setDynamicShadowingEnabled(true);
		entity->setTranslation(Vector3((i * 1.25f)- 6.0f, 0, 0.0f));
		entity->setScale(Vector3(2.0f, 2.0f, 2.0f));
		entity->update();
		engine->addEntity(entity);
		world->addStaticRigidBody("capsule" + to_string(i), true, RIGID_TYPEID_STANDARD, entity->getTransformations(), capsule, 1.0f);
	}
	auto capsuleBig = new Capsule(Vector3(0.0f, 0.8f, 0.0f), Vector3(0.0f, 3.2f, 0.0f), 0.8f);
	auto capsuleBigModel = PrimitiveModel::createModel(capsuleBig, "capsulebig_model");
	(*capsuleBigModel->getMaterials())["tdme.primitive.material"]->getAmbientColor().set(1.0f, 0.8f, 0.8f, 1.0f);
	(*capsuleBigModel->getMaterials())["tdme.primitive.material"]->getDiffuseColor().set(1.0f, 0.0f, 0.0f, 1.0f);
	entity = new Object3D("capsulebig1", capsuleBigModel);
	entity->setDynamicShadowingEnabled(true);
	entity->setTranslation(Vector3(+2.0f, 5.0f, 0.0f));
	entity->setScale(Vector3(0.6f, 0.6f, 0.6f));
	entity->update();
	engine->addEntity(entity);
	world->addRigidBody("capsulebig1", true, RIGID_TYPEID_STANDARD, entity->getTransformations(), capsuleBig, 0.0f, 1.0f, 80.0f, RigidBody::getNoRotationInertiaMatrix());
	entity = new Object3D("capsulebig2", capsuleBigModel);
	entity->setDynamicShadowingEnabled(true);
	entity->setTranslation(Vector3(-2.0f, 5.0f, 0.0f));
	entity->update();
	engine->addEntity(entity);
	world->addRigidBody("capsulebig2", true, RIGID_TYPEID_STANDARD, entity->getTransformations(), capsuleBig, 0.0f, 1.0f, 100.0f, RigidBody::getNoRotationInertiaMatrix());
}

void PhysicsTest4::reshape(int32_t width, int32_t height)
{
	engine->reshape(0, 0, width, height);
}

void PhysicsTest4::onKeyDown (unsigned char key, int x, int y) {
	auto keyChar = tolower(key);
	if (keyChar == u'w') keyW = true;
	if (keyChar == u'a') keyA = true;
	if (keyChar == u's') keyS = true;
	if (keyChar == u'd') keyD = true;
}

void PhysicsTest4::onKeyUp(unsigned char key, int x, int y) {
	auto keyChar = tolower(key);
	if (keyChar == u'w') keyW = false;
	if (keyChar == u'a') keyA = false;
	if (keyChar == u's') keyS = false;
	if (keyChar == u'd') keyD = false;
}

void PhysicsTest4::onSpecialKeyDown (int key, int x, int y) {
	if (key == KEYBOARD_KEYCODE_LEFT) keyLeft = true;
	if (key == KEYBOARD_KEYCODE_RIGHT) keyRight = true;
	if (key == KEYBOARD_KEYCODE_UP) keyUp = true;
	if (key == KEYBOARD_KEYCODE_DOWN) keyDown = true;
}

void PhysicsTest4::onSpecialKeyUp(int key, int x, int y) {
	if (key == KEYBOARD_KEYCODE_LEFT) keyLeft = false;
	if (key == KEYBOARD_KEYCODE_RIGHT) keyRight = false;
	if (key == KEYBOARD_KEYCODE_UP) keyUp = false;
	if (key == KEYBOARD_KEYCODE_DOWN) keyDown = false;
}

void PhysicsTest4::onMouseDragged(int x, int y) {
}

void PhysicsTest4::onMouseMoved(int x, int y) {
}

void PhysicsTest4::onMouseButton(int button, int state, int x, int y) {
}

void PhysicsTest4::onMouseWheel(int button, int direction, int x, int y) {
}
