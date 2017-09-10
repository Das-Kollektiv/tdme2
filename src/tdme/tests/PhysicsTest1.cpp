#include <tdme/tests/PhysicsTest1.h>

#include <string>

#include <java/lang/String.h>
#include <java/lang/System.h>

#include <java/util/logging/Level.h>
#include <java/util/logging/Logger.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/engine/fileio/models/DAEReader.h>
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
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>

using std::wstring;
using std::to_wstring;

using tdme::tests::PhysicsTest1;

using java::lang::String;
using java::lang::System;

using java::util::logging::Level;
using java::util::logging::Logger;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::Object3DModel;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::engine::fileio::models::DAEReader;
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
using tdme::utils::_Console;
using tdme::utils::_Exception;

constexpr int32_t PhysicsTest1::RIGID_TYPEID_STANDARD;

constexpr int32_t PhysicsTest1::BOX_COUNT;

constexpr int32_t PhysicsTest1::BOXSTACK_COUNT;

constexpr int32_t PhysicsTest1::CAPSULE_COUNT;

constexpr int32_t PhysicsTest1::SPHERE_COUNT;

PhysicsTest1::PhysicsTest1() 
{
	keyLeft = false;
	keyRight = false;
	keyUp = false;
	keyDown = false;
	engine = Engine::getInstance();
	world = new World();
}

void PhysicsTest1::main(int argc, char** argv)
{
	auto physicsTest1 = new PhysicsTest1();
	physicsTest1->run(argc, argv, L"PhysicsTest1", physicsTest1);
}

void PhysicsTest1::display()
{
	for (auto i = 0; i < BOX_COUNT; i++) {
		auto body = world->getRigidBody(L"box" + to_wstring(i));
		body->getLinearVelocity()->setX(body->getLinearVelocity()->getX() * (1.0f - 1.0f / 10.0f));
		body->getLinearVelocity()->setZ(body->getLinearVelocity()->getZ() * (1.0f - 1.0f / 10.0f));
	}
	for (auto i = 0; i < BOXSTACK_COUNT; i++) {
		auto body = world->getRigidBody(L"box" + to_wstring(BOX_COUNT + i));
		body->getLinearVelocity()->setX(body->getLinearVelocity()->getX() * (1.0f - 1.0f / 10.0f));
		body->getLinearVelocity()->setZ(body->getLinearVelocity()->getZ() * (1.0f - 1.0f / 10.0f));
	}
	auto capsuleBig1 = world->getRigidBody(L"capsulebig1");
	if (keyLeft)
		capsuleBig1->getLinearVelocity()->setX(8.0f);
	else if (keyRight)
		capsuleBig1->getLinearVelocity()->setX(-8.0f);
	else
		capsuleBig1->getLinearVelocity()->setX(0.0f);
	if (keyUp)
		capsuleBig1->getLinearVelocity()->setZ(8.0f);
	else if (keyDown)
		capsuleBig1->getLinearVelocity()->setZ(-8.0f);
	else
		capsuleBig1->getLinearVelocity()->setZ(0.0f);
	auto capsuleBig2 = world->getRigidBody(L"capsulebig2");
	if (keyA)
		capsuleBig2->getLinearVelocity()->setX(6.0f);
	else if (keyD)
		capsuleBig2->getLinearVelocity()->setX(-6.0f);
	else
		capsuleBig2->getLinearVelocity()->setX(0.0f);
	if (keyW)
		capsuleBig2->getLinearVelocity()->setZ(6.0f);
	else if (keyS)
		capsuleBig2->getLinearVelocity()->setZ(-6.0f);
	else
		capsuleBig2->getLinearVelocity()->setZ(0.0f);
	auto start = System::currentTimeMillis();
	auto fps = 60.0f;
	world->update(1.0f / fps);
	world->synch(engine);
	engine->display();
	auto end = System::currentTimeMillis();
	_Console::println(wstring(L"PhysicsTest::display::" + to_wstring(end - start) + L"ms"));
}

void PhysicsTest1::dispose()
{
	engine->dispose();
}

void PhysicsTest1::initialize()
{
	engine->initialize();
	Object3D* entity;
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(50.0f);
	cam->getLookFrom()->set(0.0f, 4.0f * 2.5f, -6.0f * 2.5f);
	cam->getLookAt()->set(0.0f, 0.0f, 0.0f);
	cam->computeUpVector(cam->getLookFrom(), cam->getLookAt(), cam->getUpVector());
	auto light0 = engine->getLightAt(0);
	light0->getAmbient()->set(1.0f, 1.0f, 1.0f, 1.0f);
	light0->getDiffuse()->set(0.5f, 0.5f, 0.5f, 1.0f);
	light0->getSpecular()->set(1.0f, 1.0f, 1.0f, 1.0f);
	light0->getPosition()->set(0.0f, 20000.0f, 0.0f, 1.0f);
	light0->getSpotDirection()->set(0.0f, 0.0f, 0.0f)->sub(new Vector3(light0->getPosition()));
	light0->setConstantAttenuation(0.5f);
	light0->setLinearAttenuation(0.0f);
	light0->setQuadraticAttenuation(0.0f);
	light0->setSpotExponent(0.0f);
	light0->setSpotCutOff(180.0f);
	light0->setEnabled(true);
	auto ground = new OrientedBoundingBox(new Vector3(0.0f, 0.0f, 0.0f), &OrientedBoundingBox::AABB_AXIS_X, &OrientedBoundingBox::AABB_AXIS_Y, &OrientedBoundingBox::AABB_AXIS_Z, new Vector3(8.0f, 1.0f, 8.0f));
	auto groundModel = PrimitiveModel::createModel(ground, L"ground_model");
	(*groundModel->getMaterials())[L"tdme.primitive.material"]->getAmbientColor()->set(0.8f, 0.8f, 0.8f, 1.0f);
	(*groundModel->getMaterials())[L"tdme.primitive.material"]->getDiffuseColor()->set(1.0f, 1.0f, 1.0f, 1.0f);
	entity = new Object3D(L"ground", groundModel);
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody(L"ground", true, RIGID_TYPEID_STANDARD, entity, ground, 0.5f);
	auto side = new OrientedBoundingBox(new Vector3(0.0f, 0.0f, 0.0f), &OrientedBoundingBox::AABB_AXIS_X, &OrientedBoundingBox::AABB_AXIS_Y, &OrientedBoundingBox::AABB_AXIS_Z, new Vector3(1.0f, 16.0f, 8.0f));
	auto sideModel = PrimitiveModel::createModel(side, L"side_model");
	(*sideModel->getMaterials())[L"tdme.primitive.material"]->getAmbientColor()->set(0.8f, 0.8f, 0.8f, 1.0f);
	(*sideModel->getMaterials())[L"tdme.primitive.material"]->getDiffuseColor()->set(1.0f, 1.0f, 1.0f, 1.0f);
	auto nearFar = new OrientedBoundingBox(new Vector3(0.0f, 0.0f, 0.0f), &OrientedBoundingBox::AABB_AXIS_X, &OrientedBoundingBox::AABB_AXIS_Y, &OrientedBoundingBox::AABB_AXIS_Z, new Vector3(8.0f, 16.0f, 1.0f));
	auto nearFarModel = PrimitiveModel::createModel(nearFar, L"far_model");
	(*nearFarModel->getMaterials())[L"tdme.primitive.material"]->getAmbientColor()->set(0.8f, 0.8f, 0.8f, 1.0f);
	(*nearFarModel->getMaterials())[L"tdme.primitive.material"]->getDiffuseColor()->set(1.0f, 1.0f, 1.0f, 1.0f);
	entity = new Object3D(L"far", nearFarModel);
	entity->getTranslation()->addZ(+9.0f);
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody(L"far", true, RIGID_TYPEID_STANDARD, entity, nearFar, 0.5f);
	entity = new Object3D(L"near", nearFarModel);
	entity->getTranslation()->addZ(-9.0f);
	entity->getEffectColorMul()->set(1.0f, 1.0f, 1.0f, 0.0f);
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody(L"near", true, RIGID_TYPEID_STANDARD, entity, nearFar, 0.5f);
	entity = new Object3D(L"sideright", sideModel);
	entity->getTranslation()->addX(-9.0f);
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody(L"sideright", true, RIGID_TYPEID_STANDARD, entity, side, 0.5f);
	entity = new Object3D(L"sideleft", sideModel);
	entity->getTranslation()->addX(9.0f);
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody(L"sideleft", true, RIGID_TYPEID_STANDARD, entity, side, 0.5f);
	auto box = new OrientedBoundingBox(new Vector3(0.0f, 0.0f, 0.0f), &OrientedBoundingBox::AABB_AXIS_X, &OrientedBoundingBox::AABB_AXIS_Y, &OrientedBoundingBox::AABB_AXIS_Z, new Vector3(0.6f, 0.6f, 0.6f));
	auto boxModel = PrimitiveModel::createModel(box, L"box_model");
	(*boxModel->getMaterials())[L"tdme.primitive.material"]->getAmbientColor()->set(0.8f, 0.5f, 0.5f, 1.0f);
	(*boxModel->getMaterials())[L"tdme.primitive.material"]->getDiffuseColor()->set(1.0f, 0.0f, 0.0f, 1.0f);
	for (auto i = 0; i < BOX_COUNT; i++) {
		entity = new Object3D(L"box" + to_wstring(i), boxModel);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(10.0f + i * 3.0f);
		entity->getTranslation()->addX(-2.0f + i * 0.1f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(L"box" + to_wstring(i), true, RIGID_TYPEID_STANDARD, entity, box, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(box, 100.0f, 1.0f, 1.0f, 1.0f));
	}
	for (auto i = 0; i < BOXSTACK_COUNT; i++) {
		entity = new Object3D(L"box" + to_wstring(BOX_COUNT + i), boxModel);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(1.6f + (i * 1.2f));
		entity->getTranslation()->addX(+3.0f);
		entity->getTranslation()->addZ(-5.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(L"box" + to_wstring(BOX_COUNT + i), true, RIGID_TYPEID_STANDARD, entity, box, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(box, 100.0f, 1.0f, 1.0f, 1.0f));
	}
	auto sphere = new Sphere(new Vector3(0.0f, 0.0f, 0.0f), 0.4f);
	auto sphereModel = PrimitiveModel::createModel(sphere, L"sphere_model");
	(*sphereModel->getMaterials())[L"tdme.primitive.material"]->getAmbientColor()->set(0.5f, 0.8f, 0.8f, 1.0f);
	(*sphereModel->getMaterials())[L"tdme.primitive.material"]->getDiffuseColor()->set(0.0f, 1.0f, 1.0f, 1.0f);
	for (auto i = 0; i < SPHERE_COUNT; i++) {
		entity = new Object3D(L"sphere" + to_wstring(i), sphereModel);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(12.0f + (i * 1.0f));
		entity->getTranslation()->addX(0.45f * i - 3.0f);
		entity->getTranslation()->addZ(0.1f * i - 3.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(L"sphere" + to_wstring(i), true, RIGID_TYPEID_STANDARD, entity, sphere, 0.75f, 0.4f, 10.0f, RigidBody::computeInertiaMatrix(sphere, 10.0f, 1.0f, 1.0f, 1.0f));
	}
	auto capsule = new Capsule(new Vector3(0.0f, 0.5f, 0.0f), new Vector3(0.0f, -0.5f, 0.0f), 0.25f);
	auto capsuleModel = PrimitiveModel::createModel(capsule, L"capsule_model");
	(*capsuleModel->getMaterials())[L"tdme.primitive.material"]->getAmbientColor()->set(0.8f, 0.0f, 0.8f, 1.0f);
	(*capsuleModel->getMaterials())[L"tdme.primitive.material"]->getDiffuseColor()->set(1.0f, 0.0f, 1.0f, 1.0f);
	for (auto i = 0; i < CAPSULE_COUNT; i++) {
		entity = new Object3D(L"capsule" + to_wstring(i), capsuleModel);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(14.0f + (i * 2.0f));
		entity->getTranslation()->addX((i * 0.5f));
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(L"capsule" + to_wstring(i), true, RIGID_TYPEID_STANDARD, entity, capsule, 0.0f, 0.4f, 3.0f, RigidBody::computeInertiaMatrix(capsule, 3.0f, 1.0f, 1.0f, 1.0f));
	}
	auto capsuleBig = new OrientedBoundingBox(new Vector3(0.0f, 0.0f, 0.0f), &OrientedBoundingBox::AABB_AXIS_X, &OrientedBoundingBox::AABB_AXIS_Y, &OrientedBoundingBox::AABB_AXIS_Z, new Vector3(0.5f, 1.0f, 0.5f));
	auto capsuleBigModel = PrimitiveModel::createModel(capsuleBig, L"capsulebig_model");
	(*capsuleBigModel->getMaterials())[L"tdme.primitive.material"]->getAmbientColor()->set(1.0f, 0.8f, 0.8f, 1.0f);
	(*capsuleBigModel->getMaterials())[L"tdme.primitive.material"]->getDiffuseColor()->set(1.0f, 0.0f, 0.0f, 1.0f);
	entity = new Object3D(L"capsulebig1", capsuleBigModel);
	entity->setDynamicShadowingEnabled(true);
	entity->getTranslation()->addY(5.0f);
	entity->getTranslation()->addX(-2.0f);
	entity->update();
	engine->addEntity(entity);
	world->addRigidBody(L"capsulebig1", true, RIGID_TYPEID_STANDARD, entity, capsuleBig, 0.0f, 1.0f, 80.0f, RigidBody::getNoRotationInertiaMatrix());
	entity = new Object3D(L"capsulebig2", capsuleBigModel);
	entity->setDynamicShadowingEnabled(true);
	entity->getTranslation()->addY(5.0f);
	entity->getTranslation()->addX(+2.0f);
	entity->update();
	engine->addEntity(entity);
	world->addRigidBody(L"capsulebig2", true, RIGID_TYPEID_STANDARD, entity, capsuleBig, 0.0f, 1.0f, 100.0f, RigidBody::getNoRotationInertiaMatrix());
	try {
		auto _barrel = DAEReader::read(L"resources/tests/models/barrel", L"barrel.dae");
		auto barrelBoundingVolume = new ConvexMesh(new Object3DModel(_barrel));
		entity = new Object3D(L"barrel1", _barrel);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(5.0f);
		entity->getTranslation()->addX(+4.0f);
		entity->getScale()->set(2.0f, 2.0f, 2.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(L"barrel1", true, RIGID_TYPEID_STANDARD, entity, barrelBoundingVolume, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(barrelBoundingVolume, 100.0f, 1.0f, 1.0f, 1.0f));
		entity = new Object3D(L"barrel2", _barrel);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(5.0f);
		entity->getTranslation()->addX(+6.0f);
		entity->getScale()->set(2.0f, 2.0f, 2.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(L"barrel2", true, RIGID_TYPEID_STANDARD, entity, barrelBoundingVolume, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(barrelBoundingVolume, 100.0f, 1.0f, 1.0f, 1.0f));
		auto _cone = DAEReader::read(L"resources/tests/models/cone", L"cone.dae");
		auto coneBoundingVolume = new ConvexMesh(new Object3DModel(_cone));
		entity = new Object3D(L"cone1", _cone);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(5.0f);
		entity->getTranslation()->addX(-4.0f);
		entity->getScale()->set(3.0f, 3.0f, 3.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(L"cone1", true, RIGID_TYPEID_STANDARD, entity, coneBoundingVolume, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(coneBoundingVolume, 100.0f, 1.0f, 1.0f, 1.0f));
		entity = new Object3D(L"cone2", _cone);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(5.0f);
		entity->getTranslation()->addX(-5.0f);
		entity->getScale()->set(3.0f, 3.0f, 3.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(L"cone2", true, RIGID_TYPEID_STANDARD, entity, coneBoundingVolume, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(coneBoundingVolume, 100.0f, 1.0f, 1.0f, 1.0f));
		auto _tire = DAEReader::read(L"resources/tests/models/tire", L"tire.dae");
		auto tireBoundingVolume = new ConvexMesh(new Object3DModel(_tire));
		entity = new Object3D(L"tire1", _tire);
		entity->setDynamicShadowingEnabled(true);
		entity->getRotations()->add(new Rotation(90.0f, new Vector3(1.0f, 0.0f, 0.0f)));
		entity->getTranslation()->addY(5.0f);
		entity->getTranslation()->addX(-4.0f);
		entity->getTranslation()->addZ(-2.0f);
		entity->getScale()->set(2.0f, 2.0f, 2.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(L"tire1", true, RIGID_TYPEID_STANDARD, entity, tireBoundingVolume, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(tireBoundingVolume, 100.0f, 1.0f, 1.0f, 1.0f));
		entity = new Object3D(L"tire2", _tire);
		entity->setDynamicShadowingEnabled(true);
		entity->getRotations()->add(new Rotation(90.0f, new Vector3(1.0f, 0.0f, 0.0f)));
		entity->getTranslation()->addY(5.0f);
		entity->getTranslation()->addX(-6.0f);
		entity->getTranslation()->addZ(-2.0f);
		entity->getScale()->set(2.0f, 2.0f, 2.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(L"tire2", true, RIGID_TYPEID_STANDARD, entity, tireBoundingVolume, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(tireBoundingVolume, 100.0f, 1.0f, 1.0f, 1.0f));
	} catch (_Exception& exception) {
		_Console::print(string("PhysicsTest1::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
		exit(0);
	}

}

void PhysicsTest1::reshape(int32_t width, int32_t height)
{
	engine->reshape(0, 0, width, height);
}

void PhysicsTest1::onKeyDown (unsigned char key, int x, int y) {
	auto keyChar = tolower(key);
	if (keyChar == u'w') keyW = true;
	if (keyChar == u'a') keyA = true;
	if (keyChar == u's') keyS = true;
	if (keyChar == u'd') keyD = true;
}

void PhysicsTest1::onKeyUp(unsigned char key, int x, int y) {
	auto keyChar = tolower(key);
	if (keyChar == u'w') keyW = false;
	if (keyChar == u'a') keyA = false;
	if (keyChar == u's') keyS = false;
	if (keyChar == u'd') keyD = false;
}

void PhysicsTest1::onSpecialKeyDown (int key, int x, int y) {
	if (key == KEYBOARD_KEYCODE_LEFT) keyLeft = true;
	if (key == KEYBOARD_KEYCODE_RIGHT) keyRight = true;
	if (key == KEYBOARD_KEYCODE_UP) keyUp = true;
	if (key == KEYBOARD_KEYCODE_DOWN) keyDown = true;
}

void PhysicsTest1::onSpecialKeyUp(int key, int x, int y) {
	if (key == KEYBOARD_KEYCODE_LEFT) keyLeft = false;
	if (key == KEYBOARD_KEYCODE_RIGHT) keyRight = false;
	if (key == KEYBOARD_KEYCODE_UP) keyUp = false;
	if (key == KEYBOARD_KEYCODE_DOWN) keyDown = false;
}

void PhysicsTest1::onMouseDragged(int x, int y) {
}

void PhysicsTest1::onMouseMoved(int x, int y) {
}

void PhysicsTest1::onMouseButton(int button, int state, int x, int y) {
}
