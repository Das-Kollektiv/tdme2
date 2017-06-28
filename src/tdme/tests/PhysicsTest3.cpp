// Generated from /tdme/src/tdme/tests/PhysicsTest3.java
#include <tdme/tests/PhysicsTest3.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Exception.h>
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
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_HashMap.h>

using tdme::tests::PhysicsTest3;
using java::lang::ClassCastException;
using java::lang::Exception;
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
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utils::_ArrayList;
using tdme::utils::_Console;
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
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

PhysicsTest3::PhysicsTest3(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

PhysicsTest3::PhysicsTest3() 
	: PhysicsTest3(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

constexpr int32_t PhysicsTest3::RIGID_TYPEID_STANDARD;

constexpr int32_t PhysicsTest3::BOX_COUNT;

constexpr int32_t PhysicsTest3::BOXSTACK_COUNT;

constexpr int32_t PhysicsTest3::CAPSULE_COUNT;

constexpr int32_t PhysicsTest3::SPHERE_COUNT;

void PhysicsTest3::main(StringArray* args)
{
	clinit();
	auto physicsTest3 = new PhysicsTest3();
}

void PhysicsTest3::ctor()
{
	super::ctor();
	keyLeft = false;
	keyRight = false;
	keyUp = false;
	keyDown = false;
	engine = Engine::getInstance();
	world = new World();
}

void PhysicsTest3::display()
{
	for (auto i = 0; i < BOX_COUNT; i++) {
		auto body = world->getRigidBody(::java::lang::StringBuilder().append(u"box"_j)->append(i)->toString());
		body->getLinearVelocity()->setX(body->getLinearVelocity()->getX() * (1.0f - 1.0f / 10.0f));
		body->getLinearVelocity()->setZ(body->getLinearVelocity()->getZ() * (1.0f - 1.0f / 10.0f));
	}
	for (auto i = 0; i < BOXSTACK_COUNT; i++) {
		auto body = world->getRigidBody(::java::lang::StringBuilder().append(u"box"_j)->append((BOX_COUNT + i))->toString());
		body->getLinearVelocity()->setX(body->getLinearVelocity()->getX() * (1.0f - 1.0f / 10.0f));
		body->getLinearVelocity()->setZ(body->getLinearVelocity()->getZ() * (1.0f - 1.0f / 10.0f));
	}
	auto capsuleBig1 = world->getRigidBody(u"capsulebig1"_j);
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
	auto capsuleBig2 = world->getRigidBody(u"capsulebig2"_j);
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
	_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"PhysicsTest::display::"_j)->append((end - start))
		->append(u"ms"_j)->toString()));
}

void PhysicsTest3::dispose()
{
	engine->dispose();
}

void PhysicsTest3::init_()
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
	light0->getSpotDirection()->set(0.0f, 0.0f, 0.0f)->sub(new Vector3(light0->getPosition()->getArray()));
	light0->setConstantAttenuation(0.5f);
	light0->setLinearAttenuation(0.0f);
	light0->setQuadraticAttenuation(0.0f);
	light0->setSpotExponent(0.0f);
	light0->setSpotCutOff(180.0f);
	light0->setEnabled(true);
	auto side = new OrientedBoundingBox(new Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X->clone(), OrientedBoundingBox::AABB_AXIS_Y->clone(), OrientedBoundingBox::AABB_AXIS_Z->clone(), new Vector3(1.0f, 16.0f, 8.0f));
	auto sideModel = PrimitiveModel::createModel(side, u"side_model"_j);
	java_cast< Material* >(sideModel->getMaterials()->get(u"tdme.primitive.material"_j))->getAmbientColor()->set(0.8f, 0.8f, 0.8f, 1.0f);
	java_cast< Material* >(sideModel->getMaterials()->get(u"tdme.primitive.material"_j))->getDiffuseColor()->set(1.0f, 1.0f, 1.0f, 1.0f);
	auto nearFar = new OrientedBoundingBox(new Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X->clone(), OrientedBoundingBox::AABB_AXIS_Y->clone(), OrientedBoundingBox::AABB_AXIS_Z->clone(), new Vector3(8.0f, 16.0f, 1.0f));
	auto nearFarModel = PrimitiveModel::createModel(nearFar, u"far_model"_j);
	java_cast< Material* >(nearFarModel->getMaterials()->get(u"tdme.primitive.material"_j))->getAmbientColor()->set(0.8f, 0.8f, 0.8f, 1.0f);
	java_cast< Material* >(nearFarModel->getMaterials()->get(u"tdme.primitive.material"_j))->getDiffuseColor()->set(1.0f, 1.0f, 1.0f, 1.0f);
	entity = new Object3D(u"far"_j, nearFarModel);
	entity->getTranslation()->addZ(+9.0f);
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody(u"far"_j, true, RIGID_TYPEID_STANDARD, entity, nearFar, 0.5f);
	entity = new Object3D(u"near"_j, nearFarModel);
	entity->getTranslation()->addZ(-9.0f);
	entity->getEffectColorMul()->set(1.0f, 1.0f, 1.0f, 0.0f);
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody(u"near"_j, true, RIGID_TYPEID_STANDARD, entity, nearFar, 0.5f);
	entity = new Object3D(u"sideright"_j, sideModel);
	entity->getTranslation()->addX(-9.0f);
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody(u"sideright"_j, true, RIGID_TYPEID_STANDARD, entity, side, 0.5f);
	entity = new Object3D(u"sideleft"_j, sideModel);
	entity->getTranslation()->addX(9.0f);
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody(u"sideleft"_j, true, RIGID_TYPEID_STANDARD, entity, side, 0.5f);
	auto box = new OrientedBoundingBox(new Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X->clone(), OrientedBoundingBox::AABB_AXIS_Y->clone(), OrientedBoundingBox::AABB_AXIS_Z->clone(), new Vector3(0.6f, 0.6f, 0.6f));
	auto boxModel = PrimitiveModel::createModel(box, u"box_model"_j);
	java_cast< Material* >(boxModel->getMaterials()->get(u"tdme.primitive.material"_j))->getAmbientColor()->set(0.8f, 0.5f, 0.5f, 1.0f);
	java_cast< Material* >(boxModel->getMaterials()->get(u"tdme.primitive.material"_j))->getDiffuseColor()->set(1.0f, 0.0f, 0.0f, 1.0f);
	for (auto i = 0; i < BOX_COUNT; i++) {
		entity = new Object3D(::java::lang::StringBuilder().append(u"box"_j)->append(i)->toString(), boxModel);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(10.0f + i * 3.0f);
		entity->getTranslation()->addX(-2.0f + i * 0.1f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(::java::lang::StringBuilder().append(u"box"_j)->append(i)->toString(), true, RIGID_TYPEID_STANDARD, entity, box, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(box, 100.0f, 1.0f, 1.0f, 1.0f));
	}
	for (auto i = 0; i < BOXSTACK_COUNT; i++) {
		entity = new Object3D(::java::lang::StringBuilder().append(u"box"_j)->append((BOX_COUNT + i))->toString(), boxModel);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(1.6f + (i * 1.2f));
		entity->getTranslation()->addX(+3.0f);
		entity->getTranslation()->addZ(-5.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(::java::lang::StringBuilder().append(u"box"_j)->append((BOX_COUNT + i))->toString(), true, RIGID_TYPEID_STANDARD, entity, box, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(box, 100.0f, 1.0f, 1.0f, 1.0f));
	}
	auto sphere = new Sphere(new Vector3(0.0f, 0.0f, 0.0f), 0.4f);
	auto sphereModel = PrimitiveModel::createModel(sphere, u"sphere_model"_j);
	java_cast< Material* >(sphereModel->getMaterials()->get(u"tdme.primitive.material"_j))->getAmbientColor()->set(0.5f, 0.8f, 0.8f, 1.0f);
	java_cast< Material* >(sphereModel->getMaterials()->get(u"tdme.primitive.material"_j))->getDiffuseColor()->set(0.0f, 1.0f, 1.0f, 1.0f);
	for (auto i = 0; i < SPHERE_COUNT; i++) {
		entity = new Object3D(::java::lang::StringBuilder().append(u"sphere"_j)->append(i)->toString(), sphereModel);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(12.0f + (i * 1.0f));
		entity->getTranslation()->addX(0.45f * i - 3.0f);
		entity->getTranslation()->addZ(0.1f * i - 3.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(::java::lang::StringBuilder().append(u"sphere"_j)->append(i)->toString(), true, RIGID_TYPEID_STANDARD, entity, sphere, 0.75f, 0.4f, 10.0f, RigidBody::computeInertiaMatrix(sphere, 10.0f, 1.0f, 1.0f, 1.0f));
	}
	auto capsule = new Capsule(new Vector3(0.0f, 0.5f, 0.0f), new Vector3(0.0f, -0.5f, 0.0f), 0.25f);
	auto capsuleModel = PrimitiveModel::createModel(capsule, u"capsule_model"_j);
	java_cast< Material* >(capsuleModel->getMaterials()->get(u"tdme.primitive.material"_j))->getAmbientColor()->set(0.8f, 0.0f, 0.8f, 1.0f);
	java_cast< Material* >(capsuleModel->getMaterials()->get(u"tdme.primitive.material"_j))->getDiffuseColor()->set(1.0f, 0.0f, 1.0f, 1.0f);
	for (auto i = 0; i < CAPSULE_COUNT; i++) {
		entity = new Object3D(::java::lang::StringBuilder().append(u"capsule"_j)->append(i)->toString(), capsuleModel);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(14.0f + (i * 2.0f));
		entity->getTranslation()->addX((i * 0.5f));
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(::java::lang::StringBuilder().append(u"capsule"_j)->append(i)->toString(), true, RIGID_TYPEID_STANDARD, entity, capsule, 0.0f, 0.4f, 3.0f, RigidBody::computeInertiaMatrix(capsule, 3.0f, 1.0f, 1.0f, 1.0f));
	}
	auto capsuleBig = new OrientedBoundingBox(new Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X->clone(), OrientedBoundingBox::AABB_AXIS_Y->clone(), OrientedBoundingBox::AABB_AXIS_Z->clone(), new Vector3(0.5f, 1.0f, 0.5f));
	auto capsuleBigModel = PrimitiveModel::createModel(capsuleBig, u"capsulebig_model"_j);
	java_cast< Material* >(capsuleBigModel->getMaterials()->get(u"tdme.primitive.material"_j))->getAmbientColor()->set(1.0f, 0.8f, 0.8f, 1.0f);
	java_cast< Material* >(capsuleBigModel->getMaterials()->get(u"tdme.primitive.material"_j))->getDiffuseColor()->set(1.0f, 0.0f, 0.0f, 1.0f);
	_Console::println(static_cast< Object* >(capsuleBig->getCenter()));
	entity = new Object3D(u"capsulebig1"_j, capsuleBigModel);
	entity->setDynamicShadowingEnabled(true);
	entity->getTranslation()->addY(5.0f);
	entity->getTranslation()->addX(-2.0f);
	entity->update();
	engine->addEntity(entity);
	world->addRigidBody(u"capsulebig1"_j, true, RIGID_TYPEID_STANDARD, entity, capsuleBig, 0.0f, 1.0f, 80.0f, RigidBody::getNoRotationInertiaMatrix());
	entity = new Object3D(u"capsulebig2"_j, capsuleBigModel);
	entity->setDynamicShadowingEnabled(true);
	entity->getTranslation()->addY(5.0f);
	entity->getTranslation()->addX(+2.0f);
	entity->update();
	engine->addEntity(entity);
	world->addRigidBody(u"capsulebig2"_j, true, RIGID_TYPEID_STANDARD, entity, capsuleBig, 0.0f, 1.0f, 100.0f, RigidBody::getNoRotationInertiaMatrix());
	try {
		auto _terrainModel = DAEReader::read(u"resources/tests/environment/terrain_test"_j, u"terrain_test.dae"_j);
		_terrainModel->getImportTransformationsMatrix()->scale(1.5f);
		entity = new Object3D(u"terrain"_j, _terrainModel);
		entity->getTranslation()->setY(-4.0f);
		entity->update();
		engine->addEntity(entity);
		auto groundConvexMeshes = new _ArrayList();
		ConvexMesh::createTerrainConvexMeshes(new Object3DModel(_terrainModel), groundConvexMeshes);
		for (auto i = 0; i < groundConvexMeshes->size(); i++) {
			world->addStaticRigidBody(::java::lang::StringBuilder().append(u"ground"_j)->append(i)->toString(), true, RIGID_TYPEID_STANDARD, entity, java_cast< ConvexMesh* >(groundConvexMeshes->get(i)), 0.5f);
		}
		auto _barrel = DAEReader::read(u"resources/tests/models/barrel"_j, u"barrel.dae"_j);
		auto barrelBoundingVolume = new ConvexMesh(new Object3DModel(_barrel));
		entity = new Object3D(u"barrel1"_j, _barrel);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(5.0f);
		entity->getTranslation()->addX(+4.0f);
		entity->getScale()->set(2.0f, 2.0f, 2.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(u"barrel1"_j, true, RIGID_TYPEID_STANDARD, entity, barrelBoundingVolume, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(barrelBoundingVolume, 100.0f, 1.0f, 1.0f, 1.0f));
		entity = new Object3D(u"barrel2"_j, _barrel);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(5.0f);
		entity->getTranslation()->addX(+6.0f);
		entity->getScale()->set(2.0f, 2.0f, 2.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(u"barrel2"_j, true, RIGID_TYPEID_STANDARD, entity, barrelBoundingVolume, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(barrelBoundingVolume, 100.0f, 1.0f, 1.0f, 1.0f));
		auto _cone = DAEReader::read(u"resources/tests/models/cone"_j, u"cone.dae"_j);
		auto coneBoundingVolume = new ConvexMesh(new Object3DModel(_cone));
		entity = new Object3D(u"cone1"_j, _cone);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(5.0f);
		entity->getTranslation()->addX(-4.0f);
		entity->getScale()->set(3.0f, 3.0f, 3.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(u"cone1"_j, true, RIGID_TYPEID_STANDARD, entity, coneBoundingVolume, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(coneBoundingVolume, 100.0f, 1.0f, 1.0f, 1.0f));
		entity = new Object3D(u"cone2"_j, _cone);
		entity->setDynamicShadowingEnabled(true);
		entity->getTranslation()->addY(5.0f);
		entity->getTranslation()->addX(-5.0f);
		entity->getScale()->set(3.0f, 3.0f, 3.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(u"cone2"_j, true, RIGID_TYPEID_STANDARD, entity, coneBoundingVolume, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(coneBoundingVolume, 100.0f, 1.0f, 1.0f, 1.0f));
		auto _tire = DAEReader::read(u"resources/tests/models/tire"_j, u"tire.dae"_j);
		auto tireBoundingVolume = new ConvexMesh(new Object3DModel(_tire));
		entity = new Object3D(u"tire1"_j, _tire);
		entity->setDynamicShadowingEnabled(true);
		entity->getRotations()->add(new Rotation(90.0f, new Vector3(1.0f, 0.0f, 0.0f)));
		entity->getTranslation()->addY(5.0f);
		entity->getTranslation()->addX(-4.0f);
		entity->getTranslation()->addZ(-2.0f);
		entity->getScale()->set(2.0f, 2.0f, 2.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(u"tire1"_j, true, RIGID_TYPEID_STANDARD, entity, tireBoundingVolume, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(tireBoundingVolume, 100.0f, 1.0f, 1.0f, 1.0f));
		entity = new Object3D(u"tire2"_j, _tire);
		entity->setDynamicShadowingEnabled(true);
		entity->getRotations()->add(new Rotation(90.0f, new Vector3(1.0f, 0.0f, 0.0f)));
		entity->getTranslation()->addY(5.0f);
		entity->getTranslation()->addX(-6.0f);
		entity->getTranslation()->addZ(-2.0f);
		entity->getScale()->set(2.0f, 2.0f, 2.0f);
		entity->update();
		engine->addEntity(entity);
		world->addRigidBody(u"tire2"_j, true, RIGID_TYPEID_STANDARD, entity, tireBoundingVolume, 0.0f, 1.0f, 100.0f, RigidBody::computeInertiaMatrix(tireBoundingVolume, 100.0f, 1.0f, 1.0f, 1.0f));
	} catch (Exception* e) {
		e->printStackTrace();
	}
}

void PhysicsTest3::reshape(int32_t x, int32_t y, int32_t width, int32_t height)
{
	engine->reshape(x, y, width, height);
}

/*
void PhysicsTest3::keyPressed(KeyEvent* e)
{
	int32_t keyCode = e->getKeyCode();
	if (keyCode == KeyEvent::VK_LEFT)
		keyLeft = true;

	if (keyCode == KeyEvent::VK_RIGHT)
		keyRight = true;

	if (keyCode == KeyEvent::VK_UP)
		keyUp = true;

	if (keyCode == KeyEvent::VK_DOWN)
		keyDown = true;

	if (keyCode == KeyEvent::VK_A)
		keyA = true;

	if (keyCode == KeyEvent::VK_D)
		keyD = true;

	if (keyCode == KeyEvent::VK_W)
		keyW = true;

	if (keyCode == KeyEvent::VK_S)
		keyS = true;

}

void PhysicsTest3::keyReleased(KeyEvent* e)
{
	int32_t keyCode = e->getKeyCode();
	if (keyCode == KeyEvent::VK_LEFT)
		keyLeft = false;

	if (keyCode == KeyEvent::VK_RIGHT)
		keyRight = false;

	if (keyCode == KeyEvent::VK_UP)
		keyUp = false;

	if (keyCode == KeyEvent::VK_DOWN)
		keyDown = false;

	if (keyCode == KeyEvent::VK_A)
		keyA = false;

	if (keyCode == KeyEvent::VK_D)
		keyD = false;

	if (keyCode == KeyEvent::VK_W)
		keyW = false;

	if (keyCode == KeyEvent::VK_S)
		keyS = false;

}
*/

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PhysicsTest3::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tests.PhysicsTest3", 23);
    return c;
}

java::lang::Class* PhysicsTest3::getClass0()
{
	return class_();
}

