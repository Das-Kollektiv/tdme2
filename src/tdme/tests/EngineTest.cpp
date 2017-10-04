#include <tdme/tests/EngineTest.h>

#include <cctype>
#include <vector>

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

using std::tolower;
using std::vector;

using tdme::tests::EngineTest;
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

EngineTest::EngineTest()
{
	keyLeft = false;
	keyRight = false;
	keyUp = false;
	keyW = false;
	keyA = false;
	keyS = false;
	keyD = false;
	mouseClicked = false;
	entityClicked = nullptr;
	collision = new CollisionResponse();
	engine = Engine::getInstance();
}

void EngineTest::main(int argc, char** argv)
{
	auto engineTest = new EngineTest();
	engineTest->run(argc, argv, L"EngineTest", engineTest);
}

Model* EngineTest::createWallModel()
{
	auto wall = new Model(L"wall", L"wall", Model_UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	auto wallMaterial = new Material(L"wall");
	wallMaterial->getAmbientColor()->set(1.0f, 1.0f, 1.0f, 1.0f);
	wallMaterial->getDiffuseColor()->set(1.0f, 1.0f, 1.0f, 1.0f);
	(*wall->getMaterials())[L"wall"] = wallMaterial;
	auto wallGroup = new Group(wall, nullptr, L"wall", L"wall");
	vector<FacesEntity> groupFacesEntities;
	vector<Vector3> vertices;
	vertices.push_back(Vector3(-4.0f, 0.0f, +4.0f));
	vertices.push_back(Vector3(-4.0f, +4.0f, +4.0f));
	vertices.push_back(Vector3(+4.0f, +4.0f, +4.0f));
	vertices.push_back(Vector3(+4.0f, 0.0f, +4.0f));
	vector<Vector3> normals;
	normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
	vector<TextureCoordinate> textureCoordinates;
	textureCoordinates.push_back(TextureCoordinate(0.0f, 0.0f));
	textureCoordinates.push_back(TextureCoordinate(0.0f, 1.0f));
	textureCoordinates.push_back(TextureCoordinate(1.0f, 1.0f));
	textureCoordinates.push_back(TextureCoordinate(1.0f, 0.0f));
	vector<Face> facesFarPlane;
	facesFarPlane.push_back(Face(wallGroup, 0, 1, 2, 0, 0, 0, 0, 1, 2));
	facesFarPlane.push_back(Face(wallGroup, 2, 3, 0, 0, 0, 0, 2, 3, 0));
	FacesEntity groupFacesEntityFarPlane(wallGroup, L"wall");
	groupFacesEntityFarPlane.setMaterial(wallMaterial);
	groupFacesEntityFarPlane.setFaces(&facesFarPlane);
	groupFacesEntities.push_back(groupFacesEntityFarPlane);
	wallGroup->setVertices(&vertices);
	wallGroup->setNormals(&normals);
	wallGroup->setTextureCoordinates(&textureCoordinates);
	wallGroup->setFacesEntities(&groupFacesEntities);
	wallGroup->determineFeatures();
	(*wall->getGroups())[L"wall"] = wallGroup;
	(*wall->getSubGroups())[L"wall"] = wallGroup;
	ModelHelper::prepareForIndexedRendering(wall);
	return wall;
}

void EngineTest::display()
{
	circleTransformations->getTranslation().setX(players.at(0)->getTranslation().getX());
	circleTransformations->getTranslation().setZ(players.at(0)->getTranslation().getZ());
	circleTransformations->getTranslation().addY(0.1f);
	if (circleTransformations->getTranslation().getY() > 1.5f) {
		circleTransformations->getTranslation().setY(0.0f);
	}
	circleTransformations->update();
	(dynamic_cast< ParticleSystemEntity* >(engine->getEntity(L"circle")))->getParticleEmitter()->fromTransformations(circleTransformations);
	doPlayerControl(0, keyLeft, keyRight, keyUp);
	doPlayerControl(1, keyA, keyD, keyW);
	for (auto i = 0; i < players.size(); i++) {
		playersBoundingVolumeModel.at(i)->fromTransformations(players.at(i));
	}
	osEngine->display();
	engine->display();
	if (mouseClicked == true) {
		if (entityClicked != nullptr) {
			entityClicked->getEffectColorMul().setRed(1.0f);
			entityClicked->getEffectColorMul().setGreen(1.0f);
			entityClicked->getEffectColorMul().setBlue(1.0f);
		}
		auto _object3DClicked = engine->getObjectByMousePosition(mouseClickedXY[0], mouseClickedXY[1]);
		if (_object3DClicked != nullptr) {
			_object3DClicked->getEffectColorMul().setRed(2.0f);
			_object3DClicked->getEffectColorMul().setGreen(2.0f);
			_object3DClicked->getEffectColorMul().setBlue(2.0f);
		}
		entityClicked = _object3DClicked;
		mouseClicked = false;
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
	Vector3 movement;
	if (keyRight)
		r->setAngle(r->getAngle() - (135.0f / fps));

	if (keyLeft)
		r->setAngle(r->getAngle() + (135.0f / fps));

	if (keyRight || keyLeft) {
		player->update();
		playerBoundingVolumeTransformed->fromBoundingVolumeWithTransformations(playerBoundingVolume, player);
	}
	if (keyUp) {
		r->getQuaternion().multiply(Vector3(0.0f, 0.0f, 1.0f), movement);
		movement.scale(1.5f / fps);
		player->getTranslation().add(movement);
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
		player->getTranslation().sub(collision->getNormal()->clone().scale(collision->getPenetration()));
		player->update();
		playerBoundingVolumeTransformed->fromBoundingVolumeWithTransformations(playerBoundingVolume, player);
	}
	if (CollisionDetection::doCollide(dynamic_cast< Capsule* >(playerBoundingVolumeTransformed), dynamic_cast< ConvexMesh* >(barrelBoundingVolumeTransformed), movement, collision) == true && collision->hasPenetration() == true) {
		player->getTranslation().sub(collision->getNormal()->clone().scale(collision->getPenetration()));
		player->update();
		playerBoundingVolumeTransformed->fromBoundingVolumeWithTransformations(playerBoundingVolume, player);
	}
	for (auto i = 0; i < players.size(); i++) {
		if (idx == i)
			continue;

		if (playerBoundingVolumeTransformed->doesCollideWith(playerBoundingVolumesTransformed.at(i), movement, collision) == true && collision->hasPenetration()) {
			player->getTranslation().sub(collision->getNormal()->clone().scale(collision->getPenetration()));
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
		osLight0->getPosition().set(0.0f, -4.0f, -4.0f, 1.0f);
		osLight0->getSpotDirection().set(Vector3(osLight0->getPosition().getX(), osLight0->getPosition().getY(), osLight0->getPosition().getZ())).sub(Vector3(0.0f, 0.0f, 0.0f));
		osLight0->setEnabled(true);
		auto osCam = osEngine->getCamera();
		osCam->setZNear(0.1f);
		osCam->setZFar(50.0f);
		osCam->getLookFrom().set(0.0f, 4.0f, -4.0f);
		osCam->getLookAt().set(0.0f, 0.5f, 0.0f);
		osCam->computeUpVector(osCam->getLookFrom(), osCam->getLookAt(), osCam->getUpVector());
		osEngine->getSceneColor()->set(0.5f, 0.0f, 0.0f, 1.0f);
	}
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(50.0f);
	cam->getLookFrom().set(0.0f, 3.0f, -8.0f);
	cam->getLookAt().set(0.0f, 0.5f, 0.0f);
	cam->computeUpVector(cam->getLookFrom(), cam->getLookAt(), cam->getUpVector());
	auto light0 = engine->getLightAt(0);
	light0->getAmbient()->set(1.0f, 1.0f, 1.0f, 1.0f);
	light0->getDiffuse()->set(0.5f, 0.5f, 0.5f, 1.0f);
	light0->getSpecular()->set(1.0f, 1.0f, 1.0f, 1.0f);
	light0->getPosition().set(0.0f, 20000.0f, 0.0f, 1.0f);
	light0->getSpotDirection().set(0.0f, 0.0f, 0.0f).sub(Vector3(light0->getPosition().getX(), light0->getPosition().getY(), light0->getPosition().getZ()));
	light0->setConstantAttenuation(0.5f);
	light0->setLinearAttenuation(0.0f);
	light0->setQuadraticAttenuation(0.0f);
	light0->setSpotExponent(0.0f);
	light0->setSpotCutOff(180.0f);
	light0->setEnabled(true);
	auto light1 = engine->getLightAt(1);
	light1->getDiffuse()->set(1.0f, 0.0f, 0.0f, 1.0f);
	light1->getPosition().set(-4.0f, 5.0f, -5.0f, 1.0f);
	light1->getSpotDirection().set(0.0f, 0.0f, 0.0f).sub(Vector3(light1->getPosition().getX(), light1->getPosition().getY(), light1->getPosition().getZ()));
	light1->setEnabled(true);
	auto light2 = engine->getLightAt(2);
	light2->getDiffuse()->set(0.0f, 1.0f, 0.0f, 1.0f);
	light2->getPosition().set(+4.0f, 5.0f, 0.0f, 1.0f);
	light2->getSpotDirection().set(0.0f, 0.0f, 0.0f).sub(Vector3(light2->getPosition().getX(), light2->getPosition().getY(), light2->getPosition().getZ()));
	light2->setEnabled(true);
	try {
		auto _barrel = DAEReader::read(L"resources/tests/models/barrel", L"barrel.dae");
		auto barrel = new Object3D(L"barrel", _barrel);
		barrelBoundingVolume = new ConvexMesh(new Object3DModel(_barrel));
		barrel->getTranslation().set(1.5f, 0.35f, -2.0f);
		barrel->setDynamicShadowingEnabled(true);
		barrel->setEnabled(true);
		barrel->update();
		barrelBoundingVolumeTransformed = barrelBoundingVolume->clone();
		barrelBoundingVolumeTransformed->fromBoundingVolumeWithTransformations(barrelBoundingVolume, barrel);
		engine->addEntity(barrel);
		auto _farPlane = createWallModel();
		auto farPlane = new Object3D(L"wall", _farPlane);
		farPlane->bindDiffuseTexture(L"wall", L"wall", osEngine->getFrameBuffer());
		engine->addEntity(farPlane);
		auto _grass = DAEReader::read(L"resources/tests/models/grass", L"grass.dae");
		auto grass = new Object3D(L"ground", _grass);
		grass->setEnabled(true);
		grass->getScale().set(8.0f, 1.0f, 8.0f);
		grass->update();
		engine->addEntity(grass);
		auto _player = DAEReader::read(L"resources/tests/models/dummy", L"testDummy_textured.DAE");
		_player->addAnimationSetup(L"still", 3, 3, true);
		_player->addAnimationSetup(L"walk", 0, 18, true);
		playerBoundingVolume = new Capsule(Vector3(0, 30.0f / 130.0f, 0), Vector3(0, 230.0f / 130.0f, 0), 25 / 130.0f);
		playerBoundingVolumeModel = PrimitiveModel::createModel(playerBoundingVolume, L"player_bv");
		auto player1 = new Object3D(L"player1", _player);
		player1->getTranslation().add(Vector3(-1.5f, 0.0f, 0.0f));
		player1->setAnimation(L"still");
		player1->getRotations()->add(new Rotation(0.0f, Vector3(0.0f, 1.0f, 0.0f)));
		player1->update();
		player1->setEnabled(true);
		player1->setPickable(true);
		player1->setDynamicShadowingEnabled(true);
		engine->addEntity(player1);
		auto player1BoundingVolumeTransformed = playerBoundingVolume->clone();
		player1BoundingVolumeTransformed->fromBoundingVolumeWithTransformations(playerBoundingVolume, player1);
		playerBoundingVolumesTransformed.push_back(player1BoundingVolumeTransformed);
		players.push_back(player1);
		auto player1BoundingVolume = new Object3D(L"player1_bv", playerBoundingVolumeModel);
		player1BoundingVolume->fromTransformations(player1);
		player1BoundingVolume->setEnabled(true);
		playersBoundingVolumeModel.push_back(player1BoundingVolume);
		auto player2 = new Object3D(L"player2", _player);
		player2->getTranslation().add(Vector3(1.5f, 0.0f, 0.0f));
		player2->setAnimation(L"still");
		player2->getRotations()->add(new Rotation(0.0f, Vector3(0.0f, 1.0f, 0.0f)));
		player2->update();
		player2->setEnabled(true);
		player2->setPickable(true);
		player2->setDynamicShadowingEnabled(true);
		players.push_back(player2);
		auto player2BoundingVolumeTransformed = playerBoundingVolume->clone();
		player2BoundingVolumeTransformed->fromBoundingVolumeWithTransformations(playerBoundingVolume, player2);
		playerBoundingVolumesTransformed.push_back(player2BoundingVolumeTransformed);
		engine->addEntity(player2);
		auto player2BoundingVolume = new Object3D(L"player2_bv", playerBoundingVolumeModel);
		player2BoundingVolume->fromTransformations(player2);
		player2BoundingVolume->setEnabled(true);
		playersBoundingVolumeModel.push_back(player2BoundingVolume);
		auto _cube = DAEReader::read(L"resources/tests/models/test", L"cube.dae");
		cube = new Object3D(L"cube", _cube);
		cube->getTranslation().add(Vector3(0.0f, 0.0f, 0.0f));
		cube->getScale().set(2.0f, 2.0f, 2.0f);
		cube->update();
		cube->setPickable(true);
		cube->setDynamicShadowingEnabled(true);
		cube->setEnabled(true);
		cubeBoundingVolume = cube->getBoundingBox();
		cubeBoundingVolumeTransformed = cubeBoundingVolume->clone();
		cubeBoundingVolumeTransformed->fromBoundingVolumeWithTransformations(cubeBoundingVolume, cube);
		engine->addEntity(cube);
		cubeBoundingVolumeModel = PrimitiveModel::createModel(cubeBoundingVolume, L"cube_bv");
		auto cubeBoundingVolumeObject3D = new Object3D(L"cube_bv", cubeBoundingVolumeModel);
		cubeBoundingVolumeObject3D->fromTransformations(cube);
		cubeBoundingVolumeObject3D->setEnabled(true);
		engine->addEntity(cubeBoundingVolumeObject3D);
		auto _wall = DAEReader::read(L"resources/tests/models/wall", L"wall.dae");
		auto wall0 = new Object3D(L"wall0", _wall);
		wall0->getTranslation().add(Vector3(-1.0f, 0.0f, 3.0f));
		wall0->update();
		wall0->setPickable(true);
		wall0->setEnabled(true);
		engine->addEntity(wall0);
		auto wall1 = new Object3D(L"wall1", _wall);
		wall1->getTranslation().add(Vector3(0.0f, 0.0f, 3.0f));
		wall1->update();
		wall1->setPickable(true);
		wall1->setEnabled(true);
		engine->addEntity(wall1);
		auto osCube = new Object3D(L"cube", _cube);
		osCube->getTranslation().add(Vector3(0.0f, 0.0f, 0.0f));
		osCube->getScale().set(2.0f, 2.0f, 2.0f);
		osCube->update();
		osEngine->addEntity(osCube);
		circleTransformations = new Transformations();
		engine->addEntity(new PointsParticleSystemEntity(L"circle", false, new CircleParticleEmitter(3000, 50, 50, Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), 0.4f, 0.0f, 0.0f, Vector3(0.0f, 0.2f, 0.0f), Vector3(0.0f, 0.2f, 0.0f), new Color4(1.0f, 1.0f, 1.0f, 0.3f), new Color4(1.0f, 1.0f, 1.0f, 0.3f)), 1000, true));
		engine->getEntity(L"circle")->setEnabled(true);
		engine->addEntity(new PointsParticleSystemEntity(L"water", true, new SphereParticleEmitter(4000, 1000, 0, 0.1f, 0.0f, new Sphere(Vector3(-1.0f, 1.0f, 0.0f), 0.05f), Vector3(-4.0f, 0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f), new Color4(0.8f, 0.8f, 1.0f, 0.25f), new Color4(0.8f, 0.8f, 1.0f, 0.25f)), 4000, true));
		engine->getEntity(L"water")->setEnabled(true);
		engine->addEntity(new PointsParticleSystemEntity(L"snow", false, new BoundingBoxParticleEmitter(15, 15000, 1000, 0, 0, new OrientedBoundingBox(Vector3(0.0f, 4.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(4.0f, 0.0f, 4.0f)), Vector3(0.0f, -0.5f, 0.0f), Vector3(0.0f, -0.1f, 0.0f), new Color4(0.8f, 0.8f, 1.0f, 0.5f), new Color4(0.8f, 0.8f, 1.0f, 0.5f)), 1024, true));
		engine->getEntity(L"snow")->setEnabled(true);
		engine->addEntity(new PointsParticleSystemEntity(L"firebase", false, new SphereParticleEmitter(2048, 1024, 2048, 0, 0, new Sphere(Vector3(2.5f, 0.2f, 0.0f), 0.2f), Vector3(0.0f, 0.1f, 0.0f), Vector3(0.0f, 0.1f, 0.0f), new Color4(0.0f, 0.0f, 0.0f, 0.5f), new Color4(0.4f, 0.0f, 0.0f, 0.5f)), 2048, true));
		engine->getEntity(L"firebase")->setEnabled(true);
		engine->addEntity(new PointsParticleSystemEntity(L"firetop", false, new SphereParticleEmitter(2048, 1024, 2048, 0, 0, new Sphere(Vector3(2.5f, 0.7f, 0.0f), 0.1f), Vector3(0.0f, 0.06f, 0.0f), Vector3(0.0f, 0.12f, 0.0f), new Color4(0.75f, 0.0f, 0.0f, 0.5f), new Color4(1.0f, 1.0f, 0.0f, 0.5f)), 2048, true));
		engine->getEntity(L"firetop")->setEnabled(true);
		engine->addEntity(new PointsParticleSystemEntity(L"firesmoke", false, new SphereParticleEmitter(2048, 1024, 2048, 0, 0, new Sphere(Vector3(2.5f, 0.7f, 0.0f), 0.1f), Vector3(0.0f, 0.2f, 0.0f), Vector3(0.0f, 0.4f, 0.0f), new Color4(0.8f, 0.8f, 0.8f, 0.1f), new Color4(0.8f, 0.8f, 0.8f, 0.1f)), 2048, true));
		engine->getEntity(L"firesmoke")->setEnabled(true);
		(dynamic_cast< ParticleSystemEntity* >(engine->getEntity(L"circle")))->setPickable(false);
		(dynamic_cast< ParticleSystemEntity* >(engine->getEntity(L"snow")))->setPickable(false);
		(dynamic_cast< ParticleSystemEntity* >(engine->getEntity(L"firebase")))->setPickable(true);
		(dynamic_cast< ParticleSystemEntity* >(engine->getEntity(L"firetop")))->setPickable(true);
		(dynamic_cast< ParticleSystemEntity* >(engine->getEntity(L"firesmoke")))->setPickable(true);
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

void EngineTest::onKeyDown (unsigned char key, int x, int y) {
	auto keyChar = tolower(key);
	if (keyChar == u'w') keyW = true;
	if (keyChar == u'a') keyA = true;
	if (keyChar == u's') keyS = true;
	if (keyChar == u'd') keyD = true;
}

void EngineTest::onKeyUp(unsigned char key, int x, int y) {
	auto keyChar = tolower(key);
	if (keyChar == u'w') keyW = false;
	if (keyChar == u'a') keyA = false;
	if (keyChar == u's') keyS = false;
	if (keyChar == u'd') keyD = false;
}

void EngineTest::onSpecialKeyDown (int key, int x, int y) {
	if (key == KEYBOARD_KEYCODE_LEFT) keyLeft = true;
	if (key == KEYBOARD_KEYCODE_RIGHT) keyRight = true;
	if (key == KEYBOARD_KEYCODE_UP) keyUp = true;
}

void EngineTest::onSpecialKeyUp(int key, int x, int y) {
	if (key == KEYBOARD_KEYCODE_LEFT) keyLeft = false;
	if (key == KEYBOARD_KEYCODE_RIGHT) keyRight = false;
	if (key == KEYBOARD_KEYCODE_UP) keyUp = false;
}

void EngineTest::onMouseDragged(int x, int y) {
}

void EngineTest::onMouseMoved(int x, int y) {
}

void EngineTest::onMouseButton(int button, int state, int x, int y) {
	if (state == MOUSE_BUTTON_DOWN) {
		mouseClicked = true;
		mouseClickedXY[0] = x;
		mouseClickedXY[1] = y;
	}
}
