#include <tdme/tests/SkinningTest.h>

#include <string>

#include <tdme/utils/Time.h>

#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/PrimitiveModel.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Time.h>

using std::string;
using std::to_string;

using tdme::tests::SkinningTest;

using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::Rotation;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::PrimitiveModel;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utils::Console;
using tdme::utils::Time;

SkinningTest::SkinningTest()
{
	engine = Engine::getInstance();
}


void SkinningTest::main(int argc, char** argv)
{
	auto skinningTest = new SkinningTest();
	skinningTest->run(argc, argv, "SkinningTest", skinningTest);
}

void SkinningTest::display()
{
	auto camLookFrom = engine->getCamera()->getLookFrom();
	if (keyA == true) camLookFrom.addX(-20.0f / 60.0f);
	if (keyD == true) camLookFrom.addX(+20.0f / 60.0f);
	if (keyW == true) camLookFrom.addZ(-20.0f / 60.0f);
	if (keyS == true) camLookFrom.addZ(+20.0f / 60.0f);
	if (keyLeft == true) camRotationY+= 1.0f;
	if (keyRight == true) camRotationY-= 1.0f;
	Quaternion camRotationYQuaternion;
	camRotationYQuaternion.rotate(camRotationY, Rotation::Y_AXIS);
	auto camLookAt = engine->getCamera()->getLookAt();
	camRotationYQuaternion.multiply(Vector3(0.0f, 0.0f, -1.0f), camLookAt);
	engine->getCamera()->setLookFrom(camLookFrom);
	engine->getCamera()->setLookAt(camLookFrom.clone().add(camLookAt.scale(25.0f)));
	auto start = Time::getCurrentMillis();
	engine->display();
	auto end = Time::getCurrentMillis();
	Console::println(string("SkinningTest::display::" + to_string(end - start) + "ms"));
}

void SkinningTest::dispose()
{
	engine->dispose();
}

void SkinningTest::initialize()
{
	engine->initialize();
	Object3D* entity;
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(100.0f);
	cam->setLookFrom(Vector3(0.0f, 3.0f, 60.0f));
	cam->setLookAt(Vector3(0.0f, 2.5f, 0.0f));
	cam->setUpVector(cam->computeUpVector(cam->getLookFrom(), cam->getLookAt()));
	auto light0 = engine->getLightAt(0);
	light0->setAmbient(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	light0->setDiffuse(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	light0->setSpecular(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	light0->setPosition(Vector4(0.0f, 20000.0f, 0.0f, 1.0f));
	light0->setSpotDirection(Vector3(0.0f, 0.0f, 0.0f).sub(Vector3(light0->getPosition().getX(), light0->getPosition().getY(), light0->getPosition().getZ())));
	light0->setConstantAttenuation(0.5f);
	light0->setLinearAttenuation(0.0f);
	light0->setQuadraticAttenuation(0.0f);
	light0->setSpotExponent(0.0f);
	light0->setSpotCutOff(180.0f);
	light0->setEnabled(true);
	auto ground = new OrientedBoundingBox(Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X, OrientedBoundingBox::AABB_AXIS_Y, OrientedBoundingBox::AABB_AXIS_Z, Vector3(16.0f, 1.0f, 15.0f));
	auto groundModel = PrimitiveModel::createModel(ground, "ground_model");
	(*groundModel->getMaterials())["tdme.primitive.material"]->setAmbientColor(Color4(0.8f, 0.8f, 0.8f, 1.0f));
	(*groundModel->getMaterials())["tdme.primitive.material"]->setDiffuseColor(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	entity = new Object3D("ground", groundModel);
	entity->setTranslation(Vector3(0.0f, -1.0f, 0.0f));
	entity->update();
	engine->addEntity(entity);
	auto character = ModelReader::read("resources/tests/models/mementoman", "mementoman.dae");
	int characterIdx = 0;
	for (float z = -15.0f; z < 15.0f; z+= 1.8f)
	for (float x = -15.0f; x < 15.0f; x+= 1.8f) {
		auto entity = new Object3D("character." + to_string(characterIdx++), character);
		entity->setTranslation(Vector3(x, 0.0f, z));
		entity->update();
		entity->setDynamicShadowingEnabled(true);
		engine->addEntity(entity);
	}
	Console::println("Spawned characters: " + to_string(characterIdx));
}

void SkinningTest::reshape(int32_t width, int32_t height)
{
	engine->reshape(0, 0, width, height);
}
void SkinningTest::onKeyDown (unsigned char key, int x, int y) {
	auto keyChar = tolower(key);
	if (keyChar == u'w') keyW = true;
	if (keyChar == u'a') keyA = true;
	if (keyChar == u's') keyS = true;
	if (keyChar == u'd') keyD = true;
}

void SkinningTest::onKeyUp(unsigned char key, int x, int y) {
	auto keyChar = tolower(key);
	if (keyChar == u'w') keyW = false;
	if (keyChar == u'a') keyA = false;
	if (keyChar == u's') keyS = false;
	if (keyChar == u'd') keyD = false;
}

void SkinningTest::onSpecialKeyDown (int key, int x, int y) {
	if (key == KEYBOARD_KEYCODE_LEFT) keyLeft = true;
	if (key == KEYBOARD_KEYCODE_RIGHT) keyRight = true;
	if (key == KEYBOARD_KEYCODE_UP) keyUp = true;
	if (key == KEYBOARD_KEYCODE_DOWN) keyDown = true;
}

void SkinningTest::onSpecialKeyUp(int key, int x, int y) {
	if (key == KEYBOARD_KEYCODE_LEFT) keyLeft = false;
	if (key == KEYBOARD_KEYCODE_RIGHT) keyRight = false;
	if (key == KEYBOARD_KEYCODE_UP) keyUp = false;
	if (key == KEYBOARD_KEYCODE_DOWN) keyDown = false;
}

void SkinningTest::onMouseDragged(int x, int y) {
}

void SkinningTest::onMouseMoved(int x, int y) {
}

void SkinningTest::onMouseButton(int button, int state, int x, int y) {
}

void SkinningTest::onMouseWheel(int button, int direction, int x, int y) {
}
