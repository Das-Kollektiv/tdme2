// Generated from /tdme/src/tdme/tests/PhysicsTest2.java
#include <tdme/tests/PhysicsTest2.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>
#include <java/util/logging/Level.h>
#include <java/util/logging/Logger.h>
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
#include <tdme/utils/_HashMap.h>

using tdme::tests::PhysicsTest2;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using java::util::logging::Level;
using java::util::logging::Logger;
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
using tdme::utils::_HashMap;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

PhysicsTest2::PhysicsTest2(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

PhysicsTest2::PhysicsTest2() 
	: PhysicsTest2(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

constexpr int32_t PhysicsTest2::RIGID_TYPEID_STANDARD;

constexpr int32_t PhysicsTest2::BOX_COUNT;

void PhysicsTest2::main(int argc, char** argv)
{
	clinit();
	auto physicsTest2 = new PhysicsTest2();
	physicsTest2->run(argc, argv, L"PhysicsTest2");
}

void PhysicsTest2::ctor()
{
	super::ctor();
	engine = Engine::getInstance();
	world = new World();
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
	light0->getSpotDirection()->set(0.0f, 0.0f, 0.0f)->sub(new Vector3(light0->getPosition()->getArray()));
	light0->setConstantAttenuation(0.5f);
	light0->setLinearAttenuation(0.0f);
	light0->setQuadraticAttenuation(0.0f);
	light0->setSpotExponent(0.0f);
	light0->setSpotCutOff(180.0f);
	light0->setEnabled(true);
	// TODO: fix me, need to init static members of all classes on engine start up
	OrientedBoundingBox::clinit();
	auto ground = new OrientedBoundingBox(new Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X->clone(), OrientedBoundingBox::AABB_AXIS_Y->clone(), OrientedBoundingBox::AABB_AXIS_Z->clone(), new Vector3(30.0f, 1.0f, 30.0f));
	auto groundModel = PrimitiveModel::createModel(ground, u"ground_model"_j);
	(*groundModel->getMaterials())[L"tdme.primitive.material"]->getAmbientColor()->set(0.8f, 0.8f, 0.8f, 1.0f);
	(*groundModel->getMaterials())[L"tdme.primitive.material"]->getDiffuseColor()->set(1.0f, 1.0f, 1.0f, 1.0f);
	entity = new Object3D(u"ground"_j, groundModel);
	entity->getTranslation()->setY(-1.0f);
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody(u"ground"_j, true, RIGID_TYPEID_STANDARD, entity, ground, 0.5f);
	auto box = new OrientedBoundingBox(new Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X->clone(), OrientedBoundingBox::AABB_AXIS_Y->clone(), OrientedBoundingBox::AABB_AXIS_Z->clone(), new Vector3(1.0f, 1.0f, 1.0f));
	auto boxModel = PrimitiveModel::createModel(box, u"box_model"_j);
	(*boxModel->getMaterials())[L"tdme.primitive.material"]->getAmbientColor()->set(0.8f, 0.5f, 0.5f, 1.0f);
	(*boxModel->getMaterials())[L"tdme.primitive.material"]->getDiffuseColor()->set(1.0f, 0.0f, 0.0f, 1.0f);
	for (auto i = 0; i < BOX_COUNT; i++) {
		entity = new Object3D(::java::lang::StringBuilder().append(u"box"_j)->append(i)->toString(), boxModel);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(i * 2.0f + 1.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(::java::lang::StringBuilder().append(u"box"_j)->append(i)->toString(), true, RIGID_TYPEID_STANDARD, entity, box, 0.0f, 0.8f, 100.0f, RigidBody::computeInertiaMatrix(box, 100.0f, 1.0f, 1.0f, 1.0f));
	}
}

void PhysicsTest2::reshape(int32_t width, int32_t height)
{
	engine->reshape(0, 0, width, height);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PhysicsTest2::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tests.PhysicsTest2", 23);
    return c;
}

java::lang::Class* PhysicsTest2::getClass0()
{
	return class_();
}

