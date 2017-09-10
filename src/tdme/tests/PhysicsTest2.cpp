#include <tdme/tests/PhysicsTest2.h>

#include <string>

#include <java/lang/String.h>
#include <java/lang/System.h>

#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/PrimitiveModel.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>

using std::wstring;
using std::to_wstring;

using tdme::tests::PhysicsTest2;

using java::lang::String;
using java::lang::System;

using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::physics::RigidBody;
using tdme::engine::physics::World;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::PrimitiveModel;
using tdme::math::Vector3;
using tdme::math::Vector4;

constexpr int32_t PhysicsTest2::RIGID_TYPEID_STANDARD;

constexpr int32_t PhysicsTest2::BOX_COUNT;

PhysicsTest2::PhysicsTest2() 
{
	engine = Engine::getInstance();
	world = new World();
}


void PhysicsTest2::main(int argc, char** argv)
{
	auto physicsTest2 = new PhysicsTest2();
	physicsTest2->run(argc, argv, L"PhysicsTest2");
}

void PhysicsTest2::display()
{
	auto fps = 60.0f;
	auto start = System::currentTimeMillis();
	world->update(1.0f / fps);
	world->synch(engine);
	auto end = System::currentTimeMillis();
	engine->display();
}

void PhysicsTest2::dispose()
{
	engine->dispose();
}

void PhysicsTest2::initialize()
{
	engine->initialize();
	Object3D* entity;
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(100.0f);
	cam->getLookFrom()->set(0.0f, 30.0f, 30.0f);
	cam->getLookAt()->set(0.0f, 0.0f, 0.0f);
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
	auto ground = new OrientedBoundingBox(new Vector3(0.0f, 0.0f, 0.0f), &OrientedBoundingBox::AABB_AXIS_X, &OrientedBoundingBox::AABB_AXIS_Y, &OrientedBoundingBox::AABB_AXIS_Z, new Vector3(30.0f, 1.0f, 30.0f));
	auto groundModel = PrimitiveModel::createModel(ground, L"ground_model");
	(*groundModel->getMaterials())[L"tdme.primitive.material"]->getAmbientColor()->set(0.8f, 0.8f, 0.8f, 1.0f);
	(*groundModel->getMaterials())[L"tdme.primitive.material"]->getDiffuseColor()->set(1.0f, 1.0f, 1.0f, 1.0f);
	entity = new Object3D(L"ground", groundModel);
	entity->getTranslation()->setY(-1.0f);
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody(L"ground", true, RIGID_TYPEID_STANDARD, entity, ground, 0.5f);
	auto box = new OrientedBoundingBox(new Vector3(0.0f, 0.0f, 0.0f), &OrientedBoundingBox::AABB_AXIS_X, &OrientedBoundingBox::AABB_AXIS_Y, &OrientedBoundingBox::AABB_AXIS_Z, new Vector3(1.0f, 1.0f, 1.0f));
	auto boxModel = PrimitiveModel::createModel(box, L"box_model");
	(*boxModel->getMaterials())[L"tdme.primitive.material"]->getAmbientColor()->set(0.8f, 0.5f, 0.5f, 1.0f);
	(*boxModel->getMaterials())[L"tdme.primitive.material"]->getDiffuseColor()->set(1.0f, 0.0f, 0.0f, 1.0f);
	for (auto i = 0; i < BOX_COUNT; i++) {
		entity = new Object3D(L"box" + to_wstring(i), boxModel);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(i * 2.0f + 1.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(L"box" + to_wstring(i), true, RIGID_TYPEID_STANDARD, entity, box, 0.0f, 0.8f, 100.0f, RigidBody::computeInertiaMatrix(box, 100.0f, 1.0f, 1.0f, 1.0f));
	}
}

void PhysicsTest2::reshape(int32_t width, int32_t height)
{
	engine->reshape(0, 0, width, height);
}
