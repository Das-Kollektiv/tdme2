#include <tdme/tests/PivotTest.h>

#include <string>

#include <tdme/utils/Time.h>

#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Rotations.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/PrimitiveModel.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utils/Console.h>

using std::string;
using std::to_string;

using tdme::tests::PivotTest;

using tdme::utils::Time;

using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::Rotations;
using tdme::engine::Rotation;
using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::physics::RigidBody;
using tdme::engine::physics::World;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::Sphere;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::PrimitiveModel;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utils::Console;

PivotTest::PivotTest()
{
	engine = Engine::getInstance();
	world = new World();
}


void PivotTest::main(int argc, char** argv)
{
	auto pivotTest = new PivotTest();
	pivotTest->run(argc, argv, "PivotTest");
}

void PivotTest::display()
{
	auto fps = 60.0f;
	auto start = Time::getCurrentMillis();
	auto end = Time::getCurrentMillis();
	auto entity = engine->getEntity("box");
	//entity->getRotations()->get(0)->setAngle(entity->getRotations()->get(0)->getAngle() + 0.1f);
	entity->getRotations()->get(1)->setAngle(entity->getRotations()->get(1)->getAngle() + 0.1f);
	//entity->getRotations()->get(2)->setAngle(entity->getRotations()->get(2)->getAngle() + 0.1f);
	entity->update();
	engine->display();
}

void PivotTest::dispose()
{
	engine->dispose();
}

void PivotTest::initialize()
{
	engine->initialize();
	Object3D* entity;
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(100.0f);
	cam->getLookFrom().set(0.0f, 30.0f, 30.0f);
	cam->getLookAt().set(0.0f, 0.0f, 0.0f);
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
	auto ground = new OrientedBoundingBox(Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X, OrientedBoundingBox::AABB_AXIS_Y, OrientedBoundingBox::AABB_AXIS_Z, Vector3(30.0f, 1.0f, 30.0f));
	auto groundModel = PrimitiveModel::createModel(ground, "ground_model");
	(*groundModel->getMaterials())["tdme.primitive.material"]->getAmbientColor().set(0.8f, 0.8f, 0.8f, 1.0f);
	(*groundModel->getMaterials())["tdme.primitive.material"]->getDiffuseColor().set(1.0f, 1.0f, 1.0f, 1.0f);
	entity = new Object3D("ground", groundModel);
	entity->getTranslation().setY(-1.0f);
	entity->update();
	engine->addEntity(entity);
	auto box = new OrientedBoundingBox(Vector3(0.0f, 10.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X, OrientedBoundingBox::AABB_AXIS_Y, OrientedBoundingBox::AABB_AXIS_Z, Vector3(1.0f, 1.0f, 1.0f));
	Console::println("bbb");
	// auto box = new Capsule(Vector3(0.0f, 0.5f, 0.0f), Vector3(0.0f, 1.5f, 0.0f), 0.5f);
	// auto box = new Sphere(Vector3(0.0f, 2.0f, 0.0f), 1.0f);
	Console::println("ccc");
	auto boxModel = PrimitiveModel::createModel(box, "box_model");
	Console::println("ddd");
	(*boxModel->getMaterials())["tdme.primitive.material"]->getAmbientColor().set(0.8f, 0.5f, 0.5f, 1.0f);
	(*boxModel->getMaterials())["tdme.primitive.material"]->getDiffuseColor().set(1.0f, 0.0f, 0.0f, 1.0f);
	entity = new Object3D("box", boxModel);
	entity->setDynamicShadowingEnabled(true);
	entity->getTranslation().addY(0.0f);
	entity->getPivot().set(0.0f, 10.0f, 0.0f);
	entity->getRotations()->add(new Rotation(0.0f, Vector3(1.0f, 0.0f, 1.0f)));
	entity->getRotations()->add(new Rotation(0.0f, Vector3(0.0f, 1.0f, 1.0f)));
	entity->getRotations()->add(new Rotation(0.0f, Vector3(0.0f, 0.0f, 1.0f)));
	entity->update();
	engine->addEntity(entity);
}

void PivotTest::reshape(int32_t width, int32_t height)
{
	engine->reshape(0, 0, width, height);
}
