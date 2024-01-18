#include <tdme/tests/WaterTest.h>

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/scenes/SceneReader.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/utilities/ObjectDeleter.h>
#include <tdme/utilities/Time.h>

using std::make_unique;
using std::string;
using std::to_string;
using std::unique_ptr;

using tdme::tests::WaterTest;

using tdme::utilities::Time;

using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::scenes::SceneReader;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::Object;
using tdme::engine::SceneConnector;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::utilities::ModelTools;
using tdme::utilities::ObjectDeleter;
using tdme::utilities::Time;

WaterTest::WaterTest()
{
	engine = Engine::getInstance();
}


int WaterTest::main(int argc, char** argv)
{
	auto waterTest = new WaterTest();
	return waterTest->run(argc, argv, "WaterTest", waterTest);
}

void WaterTest::display()
{
	// camera
	auto camLookFrom = engine->getCamera()->getLookFrom();
	if (keyMinus == true) camLookFrom.add(Vector3(0.0f, -20.0f / 60.0f, 0.0f));
	if (keyPlus == true) camLookFrom.add(Vector3(0.0f, +20.0f / 60.0f, 0.0f));
	if (keyLeft == true) camRotationY+= 1.0f;
	if (keyRight == true) camRotationY-= 1.0f;
	if (keyDown == true) camRotationX+= 1.0f;
	if (keyUp == true) camRotationX-= 1.0f;

	Quaternion camRotationYQuaternion;
	camRotationYQuaternion.rotate(Rotation::Y_AXIS, camRotationY);
	Quaternion camRotationXQuaternion;
	camRotationXQuaternion.rotate(Rotation::X_AXIS, camRotationX);
	Quaternion camRotationQuaternion;
	camRotationQuaternion.set(camRotationYQuaternion).multiply(camRotationXQuaternion);

	auto camLookAt = camRotationQuaternion.multiply(Vector3(0.0f, 0.0f, -1.0f));
	auto forwardVector = camLookAt;
	auto sideVector = Vector3::computeCrossProduct(forwardVector.normalize(), Vector3(0.0f, 1.0f, 0.0f)).normalize();

	if (keyA == true) camLookFrom.add(sideVector.clone().scale(-20.0f / 60.0f));
	if (keyD == true) camLookFrom.add(sideVector.clone().scale(+20.0f / 60.0f));
	if (keyW == true) camLookFrom.add(forwardVector.clone().scale(+20.0f / 60.0f));
	if (keyS == true) camLookFrom.add(forwardVector.clone().scale(-20.0f / 60.0f));

	engine->getCamera()->setLookFrom(camLookFrom);
	engine->getCamera()->setLookAt(camLookFrom.clone().add(camLookAt.scale(25.0f)));
	engine->getCamera()->setUpVector(Camera::computeUpVector(engine->getCamera()->getLookFrom(), engine->getCamera()->getLookAt()));

	// rendering
	auto start = Time::getCurrentMillis();
	engine->display();
	auto end = Time::getCurrentMillis();
	auto rendererStatistics = engine->getRendererStatistics();
	Console::printLine(
		string("WaterTest::display::") + to_string(end - start) + "ms; " +
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
}

void WaterTest::dispose()
{
	engine->dispose();
}

void WaterTest::initialize()
{
	engine->initialize();
	engine->setSkyShaderEnabled(true);

	//
	scene = unique_ptr<Scene>(SceneReader::read("resources/tests/levels/water", "Level_WaterShader.tscene"));
	SceneConnector::setLights(engine, scene.get());
	SceneConnector::addScene(engine, scene.get(), false, false, false, false, false);

	//
	spherePrototype = unique_ptr<Prototype>(PrototypeReader::read("resources/tests/levels/water/", "sphere.tmodel"));

	{
		// sphere
		spherePrototype->getModel()->getMaterials()["CM_Shader_Sphere_M"]->getSpecularMaterialProperties()->setReflection(1.0f);
		auto sphere = new Object("sphere", spherePrototype->getModel());
		sphere->setScale(Vector3(5.0f, 5.0f, 5.0f));
		sphere->setTranslation(Vector3(0.0f, 20.0f, 0.0f));
		sphere->setReflectionEnvironmentMappingId("New environment mapping_2");
		sphere->setReflectionEnvironmentMappingPosition(sphere->getTranslation());
		sphere->update();
		engine->addEntity(sphere);
	}

	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(150.0f);
	cam->setLookFrom(Vector3(0.0f, 30.0f, 50.0f));
	cam->setLookAt(Vector3(0.0f, 0.0f, 0.0f));
	cam->setUpVector(Camera::computeUpVector(cam->getLookFrom(), cam->getLookAt()));
}

void WaterTest::reshape(int32_t width, int32_t height)
{
	engine->reshape(width, height);
}

void WaterTest::onChar(int key, int x, int y) {
}

void WaterTest::onKeyDown(int key, int keyCode, int x, int y, bool repeat, int modifiers) {
	auto keyChar = Character::toLowerCase(key);
	if (keyChar == 'w') keyW = true;
	if (keyChar == 'a') keyA = true;
	if (keyChar == 's') keyS = true;
	if (keyChar == 'd') keyD = true;
	if (keyChar == '-') keyMinus = true;
	if (keyChar == '+') keyPlus = true;
	if (keyCode == KEYBOARD_KEYCODE_LEFT) keyLeft = true;
	if (keyCode == KEYBOARD_KEYCODE_RIGHT) keyRight = true;
	if (keyCode == KEYBOARD_KEYCODE_UP) keyUp = true;
	if (keyCode == KEYBOARD_KEYCODE_DOWN) keyDown = true;
}

void WaterTest::onKeyUp(int key, int keyCode, int x, int y) {
	auto keyChar = Character::toLowerCase(key);
	if (keyChar == 'w') keyW = false;
	if (keyChar == 'a') keyA = false;
	if (keyChar == 's') keyS = false;
	if (keyChar == 'd') keyD = false;
	if (keyChar == '-') keyMinus = false;
	if (keyChar == '+') keyPlus = false;
	if (keyCode == KEYBOARD_KEYCODE_LEFT) keyLeft = false;
	if (keyCode == KEYBOARD_KEYCODE_RIGHT) keyRight = false;
	if (keyCode == KEYBOARD_KEYCODE_UP) keyUp = false;
	if (keyCode == KEYBOARD_KEYCODE_DOWN) keyDown = false;
}

void WaterTest::onMouseDragged(int x, int y) {
}

void WaterTest::onMouseMoved(int x, int y) {
}

void WaterTest::onMouseButton(int button, int state, int x, int y) {
}

void WaterTest::onMouseWheel(int button, int direction, int x, int y) {
}
