// Generated from /tdme/src/tdme/tests/EngineTest.java
#include <tdme/tests/EngineTest.h>

#include <vector>

#include <java/lang/Character.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>
#include <java/util/logging/Level.h>
#include <java/util/logging/Logger.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/PointsParticleSystemEntity.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/fileio/models/DAEReader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model_UpVector.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/PrimitiveModel.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/subsystems/particlesystem/BoundingBoxParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/CircleParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/ParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemEntity.h>
#include <tdme/engine/subsystems/particlesystem/SphereParticleEmitter.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utils/_Exception.h>
#include <tdme/utils/_Console.h>
#include <Array.h>

using std::vector;

using tdme::tests::EngineTest;
using java::lang::Character;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using java::util::logging::Level;
using java::util::logging::Logger;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::Object3DModel;
using tdme::engine::PointsParticleSystemEntity;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::engine::Timing;
using tdme::engine::Transformations;
using tdme::engine::fileio::models::DAEReader;
using tdme::engine::model::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::engine::model::Model_UpVector;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::PrimitiveModel;
using tdme::engine::primitives::Sphere;
using tdme::engine::subsystems::particlesystem::BoundingBoxParticleEmitter;
using tdme::engine::subsystems::particlesystem::CircleParticleEmitter;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::particlesystem::ParticleSystemEntity;
using tdme::engine::subsystems::particlesystem::SphereParticleEmitter;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utils::_Console;
using tdme::utils::_Exception;

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

EngineTest::EngineTest(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

EngineTest::EngineTest()
	: EngineTest(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void EngineTest::main(int argc, char** argv)
{
	clinit();
	auto engineTest = new EngineTest();
	engineTest->run(argc, argv, L"EngineTest");
}

void EngineTest::ctor()
{
	super::ctor();
	keyLeft = false;
	keyRight = false;
	keyUp = false;
	keyW = false;
	keyA = false;
	keyS = false;
	keyD = false;
	mouseClicked_ = nullptr;
	entityClicked = nullptr;
	collision = new CollisionResponse();
	engine = Engine::getInstance();
}

Model* EngineTest::createWallModel()
{
	auto wall = new Model(u"wall"_j, u"wall"_j, Model_UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	auto wallMaterial = new Material(u"wall"_j);
	(*wall->getMaterials())[L"wall"] = wallMaterial;
	auto wallGroup = new Group(wall, nullptr, u"wall"_j, u"wall"_j);
	auto groupFacesEntityFarPlane = new FacesEntity(wallGroup, u"wall"_j);
	wallMaterial->getAmbientColor()->set(1.0f, 1.0f, 1.0f, 1.0f);
	wallMaterial->getDiffuseColor()->set(1.0f, 1.0f, 1.0f, 1.0f);
	groupFacesEntityFarPlane->setMaterial(wallMaterial);
	vector<FacesEntity*> groupFacesEntities;
	groupFacesEntities.push_back(groupFacesEntityFarPlane);
	vector<Vector3*> vertices;
	vertices.push_back(new Vector3(-4.0f, 0.0f, +4.0f));
	vertices.push_back(new Vector3(-4.0f, +4.0f, +4.0f));
	vertices.push_back(new Vector3(+4.0f, +4.0f, +4.0f));
	vertices.push_back(new Vector3(+4.0f, 0.0f, +4.0f));
	vector<Vector3*> normals;
	normals.push_back(new Vector3(0.0f, 0.0f, -1.0f));
	vector<TextureCoordinate*> textureCoordinates;
	textureCoordinates.push_back(new TextureCoordinate(0.0f, 0.0f));
	textureCoordinates.push_back(new TextureCoordinate(0.0f, 1.0f));
	textureCoordinates.push_back(new TextureCoordinate(1.0f, 1.0f));
	textureCoordinates.push_back(new TextureCoordinate(1.0f, 0.0f));
	vector<Face*> facesFarPlane;
	facesFarPlane.push_back(new Face(wallGroup, 0, 1, 2, 0, 0, 0, 0, 1, 2));
	facesFarPlane.push_back(new Face(wallGroup, 2, 3, 0, 0, 0, 0, 2, 3, 0));
	groupFacesEntityFarPlane->setFaces(facesFarPlane);
	wallGroup->setVertices(vertices);
	wallGroup->setNormals(normals);
	wallGroup->setTextureCoordinates(textureCoordinates);
	wallGroup->setFacesEntities(groupFacesEntities);
	wallGroup->determineFeatures();
	(*wall->getGroups())[L"wall"] = wallGroup;
	(*wall->getSubGroups())[L"wall"] = wallGroup;
	ModelHelper::prepareForIndexedRendering(wall);
	return wall;
}

void EngineTest::display()
{
	circleTransformations->getTranslation()->setX(players.at(0)->getTranslation()->getX());
	circleTransformations->getTranslation()->setZ(players.at(0)->getTranslation()->getZ());
	circleTransformations->getTranslation()->addY(0.1f);
	if (circleTransformations->getTranslation()->getY() > 1.5f) {
		circleTransformations->getTranslation()->setY(0.0f);
	}
	circleTransformations->update();
	(java_cast< ParticleSystemEntity* >(engine->getEntity(u"circle"_j)))->getParticleEmitter()->fromTransformations(circleTransformations);
	doPlayerControl(0, keyLeft, keyRight, keyUp);
	doPlayerControl(1, keyA, keyD, keyW);
	for (auto i = 0; i < players.size(); i++) {
		playersBoundingVolumeModel.at(i)->fromTransformations(players.at(i));
	}
	osEngine->display();
	engine->display();
	if (mouseClicked_ != nullptr) {
		if (entityClicked != nullptr) {
			entityClicked->getEffectColorMul()->setRed(1.0f);
			entityClicked->getEffectColorMul()->setGreen(1.0f);
			entityClicked->getEffectColorMul()->setBlue(1.0f);
		}
		auto _object3DClicked = engine->getObjectByMousePosition((*mouseClicked_)[0], (*mouseClicked_)[1]);
		if (_object3DClicked != nullptr) {
			_object3DClicked->getEffectColorMul()->setRed(2.0f);
			_object3DClicked->getEffectColorMul()->setGreen(2.0f);
			_object3DClicked->getEffectColorMul()->setBlue(2.0f);
		}
		entityClicked = _object3DClicked;
		mouseClicked_ = nullptr;
	}
}

void EngineTest::doPlayerControl(int32_t idx, bool keyLeft, bool keyRight, bool keyUp)
{
	auto fps = engine->getTiming()->getCurrentFPS();
	auto player = players.at(idx);
	auto playerBoundingVolumeTransformed = playerBoundingVolumesTransformed.at(idx);
	auto rotations = player->getRotations();
	auto r = rotations->get(0);
	player->update();
	auto movement = new Vector3();
	if (keyRight)
		r->setAngle(r->getAngle() - (135.0f / fps));

	if (keyLeft)
		r->setAngle(r->getAngle() + (135.0f / fps));

	if (keyRight || keyLeft) {
		player->update();
		playerBoundingVolumeTransformed->fromBoundingVolumeWithTransformations(playerBoundingVolume, player);
	}
	if (keyUp) {
		r->getQuaternion()->multiply(new Vector3(0.0f, 0.0f, 1.0f), movement);
		movement->scale(1.5f / fps);
		player->getTranslation()->add(movement);
		player->update();
		playerBoundingVolumeTransformed->fromBoundingVolumeWithTransformations(playerBoundingVolume, player);
		if (player->getAnimation() != L"walk") {
			player->setAnimation(L"walk");
		}
	} else {
		if (player->getAnimation() == L"walk") {
			player->setAnimation(L"still");
		}
	}
	if (playerBoundingVolumeTransformed->doesCollideWith(cubeBoundingVolumeTransformed, movement, collision) == true && collision->hasPenetration() == true) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"cube: "_j)->append(static_cast< Object* >(collision))->toString()));
		player->getTranslation()->sub(collision->getNormal()->clone()->scale(collision->getPenetration()));
		player->update();
		playerBoundingVolumeTransformed->fromBoundingVolumeWithTransformations(playerBoundingVolume, player);
	}
	if (CollisionDetection::getInstance()->doCollide(java_cast< Capsule* >(playerBoundingVolumeTransformed), java_cast< ConvexMesh* >(barrelBoundingVolumeTransformed), movement, collision) == true && collision->hasPenetration() == true) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"barrel: "_j)->append(static_cast< Object* >(collision))->toString()));
		player->getTranslation()->sub(collision->getNormal()->clone()->scale(collision->getPenetration()));
		player->update();
		playerBoundingVolumeTransformed->fromBoundingVolumeWithTransformations(playerBoundingVolume, player);
	}
	for (auto i = 0; i < players.size(); i++) {
		if (idx == i)
			continue;

		if (playerBoundingVolumeTransformed->doesCollideWith(playerBoundingVolumesTransformed.at(i), movement, collision) == true && collision->hasPenetration()) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"player: "_j)->append(static_cast< Object* >(collision))->toString()));
			player->getTranslation()->sub(collision->getNormal()->clone()->scale(collision->getPenetration()));
			player->update();
			playerBoundingVolumeTransformed->fromBoundingVolumeWithTransformations(playerBoundingVolume, player);
		}
	}
}

void EngineTest::dispose()
{
	engine->dispose();
}

void EngineTest::initialize()
{
	engine->initialize();
	if (osEngine == nullptr) {
		osEngine = Engine::createOffScreenInstance(512, 512);
		auto osLight0 = osEngine->getLightAt(0);
		osLight0->getAmbient()->set(1.0f, 1.0f, 1.0f, 1.0f);
		osLight0->getDiffuse()->set(1.0f, 1.0f, 1.0f, 1.0f);
		osLight0->getPosition()->set(0.0f, -4.0f, -4.0f, 1.0f);
		osLight0->getSpotDirection()->set(new Vector3(osLight0->getPosition()->getArray()))->sub(new Vector3(0.0f, 0.0f, 0.0f));
		osLight0->setEnabled(true);
		auto osCam = osEngine->getCamera();
		osCam->setZNear(0.1f);
		osCam->setZFar(50.0f);
		osCam->getLookFrom()->set(0.0f, 4.0f, -4.0f);
		osCam->getLookAt()->set(0.0f, 0.5f, 0.0f);
		osCam->computeUpVector(osCam->getLookFrom(), osCam->getLookAt(), osCam->getUpVector());
		osEngine->getSceneColor()->set(0.5f, 0.0f, 0.0f, 1.0f);
	}
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(50.0f);
	cam->getLookFrom()->set(0.0f, 3.0f, -8.0f);
	cam->getLookAt()->set(0.0f, 0.5f, 0.0f);
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
	auto light1 = engine->getLightAt(1);
	light1->getDiffuse()->set(1.0f, 0.0f, 0.0f, 1.0f);
	light1->getPosition()->set(-4.0f, 5.0f, -5.0f, 1.0f);
	light1->getSpotDirection()->set(0.0f, 0.0f, 0.0f)->sub(new Vector3(light1->getPosition()->getArray()));
	light1->setEnabled(true);
	auto light2 = engine->getLightAt(2);
	light2->getDiffuse()->set(0.0f, 1.0f, 0.0f, 1.0f);
	light2->getPosition()->set(+4.0f, 5.0f, 0.0f, 1.0f);
	light2->getSpotDirection()->set(0.0f, 0.0f, 0.0f)->sub(new Vector3(light2->getPosition()->getArray()));
	light2->setEnabled(true);
	try {
		auto _barrel = DAEReader::read(u"resources/tests/models/barrel"_j, u"barrel.dae"_j);
		auto barrel = new Object3D(u"barrel"_j, _barrel);
		barrelBoundingVolume = new ConvexMesh(new Object3DModel(_barrel));
		barrel->getTranslation()->set(1.5f, 0.35f, -2.0f);
		barrel->setDynamicShadowingEnabled(true);
		barrel->setEnabled(true);
		barrel->update();
		barrelBoundingVolumeTransformed = barrelBoundingVolume->clone();
		barrelBoundingVolumeTransformed->fromBoundingVolumeWithTransformations(barrelBoundingVolume, barrel);
		engine->addEntity(barrel);
		auto _farPlane = createWallModel();
		auto farPlane = new Object3D(u"wall"_j, _farPlane);
		farPlane->bindDiffuseTexture(u"wall"_j, u"wall"_j, osEngine->getFrameBuffer());
		engine->addEntity(farPlane);
		auto _grass = DAEReader::read(u"resources/tests/models/grass"_j, u"grass.dae"_j);
		auto grass = new Object3D(u"ground"_j, _grass);
		grass->setEnabled(true);
		grass->getScale()->set(8.0f, 1.0f, 8.0f);
		grass->update();
		engine->addEntity(grass);
		auto _player = DAEReader::read(u"resources/tests/models/dummy"_j, u"testDummy_textured.DAE"_j);
		_player->addAnimationSetup(L"still", 3, 3, true);
		_player->addAnimationSetup(L"walk", 0, 18, true);
		playerBoundingVolume = Capsule::createBoundingVolume(new Vector3(0, 30.0f / 130.0f, 0), new Vector3(0, 230.0f / 130.0f, 0), 25 / 130.0f);
		playerBoundingVolumeModel = PrimitiveModel::createModel(playerBoundingVolume, u"player_bv"_j);
		auto player1 = new Object3D(u"player1"_j, _player);
		player1->getTranslation()->add(new Vector3(-1.5f, 0.0f, 0.0f));
		player1->setAnimation(L"still");
		player1->getRotations()->add(new Rotation(0.0f, new Vector3(0.0f, 1.0f, 0.0f)));
		player1->update();
		player1->setEnabled(true);
		player1->setPickable(true);
		player1->setDynamicShadowingEnabled(true);
		engine->addEntity(player1);
		auto player1BoundingVolumeTransformed = playerBoundingVolume->clone();
		player1BoundingVolumeTransformed->fromBoundingVolumeWithTransformations(playerBoundingVolume, player1);
		playerBoundingVolumesTransformed.push_back(player1BoundingVolumeTransformed);
		players.push_back(player1);
		auto player1BoundingVolume = new Object3D(u"player1_bv"_j, playerBoundingVolumeModel);
		player1BoundingVolume->fromTransformations(player1);
		player1BoundingVolume->setEnabled(true);
		playersBoundingVolumeModel.push_back(player1BoundingVolume);
		auto player2 = new Object3D(u"player2"_j, _player);
		player2->getTranslation()->add(new Vector3(1.5f, 0.0f, 0.0f));
		player2->setAnimation(L"still");
		player2->getRotations()->add(new Rotation(0.0f, new Vector3(0.0f, 1.0f, 0.0f)));
		player2->update();
		player2->setEnabled(true);
		player2->setPickable(true);
		player2->setDynamicShadowingEnabled(true);
		players.push_back(player2);
		auto player2BoundingVolumeTransformed = playerBoundingVolume->clone();
		player2BoundingVolumeTransformed->fromBoundingVolumeWithTransformations(playerBoundingVolume, player2);
		playerBoundingVolumesTransformed.push_back(player2BoundingVolumeTransformed);
		engine->addEntity(player2);
		auto player2BoundingVolume = new Object3D(u"player2_bv"_j, playerBoundingVolumeModel);
		player2BoundingVolume->fromTransformations(player2);
		player2BoundingVolume->setEnabled(true);
		playersBoundingVolumeModel.push_back(player2BoundingVolume);
		auto _cube = DAEReader::read(u"resources/tests/models/test"_j, u"cube.dae"_j);
		cube = new Object3D(u"cube"_j, _cube);
		cube->getTranslation()->add(new Vector3(0.0f, 0.0f, 0.0f));
		cube->getScale()->set(2.0f, 2.0f, 2.0f);
		cube->update();
		cube->setPickable(true);
		cube->setDynamicShadowingEnabled(true);
		cube->setEnabled(true);
		cubeBoundingVolume = cube->getBoundingBox();
		cubeBoundingVolumeTransformed = cubeBoundingVolume->clone();
		cubeBoundingVolumeTransformed->fromBoundingVolumeWithTransformations(cubeBoundingVolume, cube);
		engine->addEntity(cube);
		cubeBoundingVolumeModel = PrimitiveModel::createModel(cubeBoundingVolume, u"cube_bv"_j);
		auto cubeBoundingVolumeObject3D = new Object3D(u"cube_bv"_j, cubeBoundingVolumeModel);
		cubeBoundingVolumeObject3D->fromTransformations(cube);
		cubeBoundingVolumeObject3D->setEnabled(true);
		engine->addEntity(cubeBoundingVolumeObject3D);
		auto _wall = DAEReader::read(u"resources/tests/models/wall"_j, u"wall.dae"_j);
		auto wall0 = new Object3D(u"wall0"_j, _wall);
		wall0->getTranslation()->add(new Vector3(-1.0f, 0.0f, 3.0f));
		wall0->update();
		wall0->setPickable(true);
		wall0->setEnabled(true);
		engine->addEntity(wall0);
		auto wall1 = new Object3D(u"wall1"_j, _wall);
		wall1->getTranslation()->add(new Vector3(0.0f, 0.0f, 3.0f));
		wall1->update();
		wall1->setPickable(true);
		wall1->setEnabled(true);
		engine->addEntity(wall1);
		auto osCube = new Object3D(u"cube"_j, _cube);
		osCube->getTranslation()->add(new Vector3(0.0f, 0.0f, 0.0f));
		osCube->getScale()->set(2.0f, 2.0f, 2.0f);
		osCube->update();
		osEngine->addEntity(osCube);
		circleTransformations = new Transformations();
		engine->addEntity(new PointsParticleSystemEntity(u"circle"_j, false, new CircleParticleEmitter(3000, 50, 50, new Vector3(1.0f, 0.0f, 0.0f), new Vector3(0.0f, 0.0f, 1.0f), new Vector3(0.0f, 0.0f, 0.0f), 0.4f, 0.0f, 0.0f, new Vector3(0.0f, 0.2f, 0.0f), new Vector3(0.0f, 0.2f, 0.0f), new Color4(1.0f, 1.0f, 1.0f, 0.3f), new Color4(1.0f, 1.0f, 1.0f, 0.3f)), 1000, true));
		engine->getEntity(u"circle"_j)->setEnabled(true);
		engine->addEntity(new PointsParticleSystemEntity(u"water"_j, true, new SphereParticleEmitter(4000, 1000, 0, 0.1f, 0.0f, new Sphere(new Vector3(-1.0f, 1.0f, 0.0f), 0.05f), new Vector3(-4.0f, 0.0f, 1.0f), new Vector3(-1.0f, 0.0f, 0.0f), new Color4(0.8f, 0.8f, 1.0f, 0.25f), new Color4(0.8f, 0.8f, 1.0f, 0.25f)), 4000, true));
		engine->getEntity(u"water"_j)->setEnabled(true);
		engine->addEntity(new PointsParticleSystemEntity(u"snow"_j, false, new BoundingBoxParticleEmitter(15, 15000, 1000, 0, 0, new OrientedBoundingBox(new Vector3(0.0f, 4.0f, 0.0f), new Vector3(1.0f, 0.0f, 0.0f), new Vector3(0.0f, 1.0f, 0.0f), new Vector3(0.0f, 0.0f, 1.0f), new Vector3(4.0f, 0.0f, 4.0f)), new Vector3(0.0f, -0.5f, 0.0f), new Vector3(0.0f, -0.1f, 0.0f), new Color4(0.8f, 0.8f, 1.0f, 0.5f), new Color4(0.8f, 0.8f, 1.0f, 0.5f)), 1024, true));
		engine->getEntity(u"snow"_j)->setEnabled(true);
		engine->addEntity(new PointsParticleSystemEntity(u"firebase"_j, false, new SphereParticleEmitter(2048, 1024, 2048, 0, 0, new Sphere(new Vector3(2.5f, 0.2f, 0.0f), 0.2f), new Vector3(0.0f, 0.1f, 0.0f), new Vector3(0.0f, 0.1f, 0.0f), new Color4(0.0f, 0.0f, 0.0f, 0.5f), new Color4(0.4f, 0.0f, 0.0f, 0.5f)), 2048, true));
		engine->getEntity(u"firebase"_j)->setEnabled(true);
		engine->addEntity(new PointsParticleSystemEntity(u"firetop"_j, false, new SphereParticleEmitter(2048, 1024, 2048, 0, 0, new Sphere(new Vector3(2.5f, 0.7f, 0.0f), 0.1f), new Vector3(0.0f, 0.06f, 0.0f), new Vector3(0.0f, 0.12f, 0.0f), new Color4(0.75f, 0.0f, 0.0f, 0.5f), new Color4(1.0f, 1.0f, 0.0f, 0.5f)), 2048, true));
		engine->getEntity(u"firetop"_j)->setEnabled(true);
		engine->addEntity(new PointsParticleSystemEntity(u"firesmoke"_j, false, new SphereParticleEmitter(2048, 1024, 2048, 0, 0, new Sphere(new Vector3(2.5f, 0.7f, 0.0f), 0.1f), new Vector3(0.0f, 0.2f, 0.0f), new Vector3(0.0f, 0.4f, 0.0f), new Color4(0.8f, 0.8f, 0.8f, 0.1f), new Color4(0.8f, 0.8f, 0.8f, 0.1f)), 2048, true));
		engine->getEntity(u"firesmoke"_j)->setEnabled(true);
		(java_cast< ParticleSystemEntity* >(engine->getEntity(u"circle"_j)))->setPickable(false);
		(java_cast< ParticleSystemEntity* >(engine->getEntity(u"snow"_j)))->setPickable(false);
		(java_cast< ParticleSystemEntity* >(engine->getEntity(u"firebase"_j)))->setPickable(true);
		(java_cast< ParticleSystemEntity* >(engine->getEntity(u"firetop"_j)))->setPickable(true);
		(java_cast< ParticleSystemEntity* >(engine->getEntity(u"firesmoke"_j)))->setPickable(true);
	} catch (_Exception& exception) {
		_Console::print(string("EngineTest::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
		exit(0);
	}
}

void EngineTest::reshape(int32_t width, int32_t height)
{
	engine->reshape(0, 0, width, height);
}

/*
void EngineTest::mousePressed(MouseEvent* e)
{
	mouseClicked_ = new int32_tArray({
		e->getX(),
		e->getY()
	});
}

void EngineTest::keyPressed(KeyEvent* e)
{
	int32_t keyCode = e->getKeyCode();
	auto keyChar = Character::toLowerCase(e->getKeyChar());
	if (keyChar == u'w')
		keyW = true;

	if (keyChar == u'a')
		keyA = true;

	if (keyChar == u's')
		keyS = true;

	if (keyChar == u'd')
		keyD = true;

	if (keyCode == KeyEvent::VK_LEFT)
		keyLeft = true;

	if (keyCode == KeyEvent::VK_RIGHT)
		keyRight = true;

	if (keyCode == KeyEvent::VK_UP)
		keyUp = true;

}

void EngineTest::keyReleased(KeyEvent* e)
{
	int32_t keyCode = e->getKeyCode();
	auto keyChar = Character::toLowerCase(e->getKeyChar());
	if (keyChar == u'w')
		keyW = false;

	if (keyChar == u'a')
		keyA = false;

	if (keyChar == u's')
		keyS = false;

	if (keyChar == u'd')
		keyD = false;

	if (keyCode == KeyEvent::VK_LEFT)
		keyLeft = false;

	if (keyCode == KeyEvent::VK_RIGHT)
		keyRight = false;

	if (keyCode == KeyEvent::VK_UP)
		keyUp = false;

}
*/

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* EngineTest::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tests.EngineTest", 21);
    return c;
}

java::lang::Class* EngineTest::getClass0()
{
	return class_();
}

