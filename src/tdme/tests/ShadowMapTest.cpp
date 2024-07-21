#include <tdme/tests/ShadowMapTest.h>

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/engine/fileio/scenes/SceneReader.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Time.h>

using std::make_unique;
using std::string;
using std::to_string;
using std::unique_ptr;

using tdme::tests::ShadowMapTest;

using tdme::application::Application;
using tdme::application::InputEventHandler;
using tdme::engine::fileio::scenes::SceneReader;
using tdme::engine::physics::World;
using tdme::engine::scene::Scene;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::SceneConnector;
using tdme::engine::Timing;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::utilities::Time;

ShadowMapTest::ShadowMapTest()
{
	Application::setLimitFPS(true);
	engine = Engine::getInstance();
	world = make_unique<World>("world");
}

ShadowMapTest::~ShadowMapTest() {
}

int ShadowMapTest::main(int argc, char** argv)
{
	auto shadowMapTest = new ShadowMapTest();
	return shadowMapTest->run(argc, argv, "ShadowMapTest", shadowMapTest);
}

void ShadowMapTest::display()
{
	// light
	if (keyComma == true) t-= 0.001f;
	if (keyDot == true) t+= 0.001f;

	//
	engine->getLightAt(Engine::LIGHTIDX_SUN)->setupSun(t);
	engine->getLightAt(Engine::LIGHTIDX_MOON)->setupMoon(t);

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
		"Scene Center: " +
		to_string(scene->getCenter().getX()) + ", " +
		to_string(scene->getCenter().getY()) + ", " +
		to_string(scene->getCenter().getZ())
	);

	Console::printLine(
		"Scene Dimension: " +
		to_string(scene->getDimension().getX()) + ", " +
		to_string(scene->getDimension().getY()) + ", " +
		to_string(scene->getDimension().getZ())
	);

	Console::printLine(
		string("SkinningTest::display::") + to_string(end - start) + "ms; " +
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

void ShadowMapTest::dispose()
{
	engine->dispose();
}

void ShadowMapTest::initialize()
{
	Engine::setAnimationComputationReduction1Distance(175.0f);
	Engine::setAnimationComputationReduction2Distance(250.0f);
	engine->initialize();
	scene = unique_ptr<Scene>(SceneReader::read("../WarStory/resources/project/maps", "Map_RTS_Valley.tscene"));
	SceneConnector::setLights(engine, scene.get());
	SceneConnector::addScene(engine, scene.get(), false, false, false, false, false);
	SceneConnector::addScene(world.get(), scene.get());
	auto cam = engine->getCamera();
	cam->setLookFrom(scene->getCenter() + Vector3(0.0f, 20.0f, 0.0f));
	cam->setLookAt(scene->getCenter());
	cam->setUpVector(cam->computeUpVector(cam->getLookFrom(), cam->getLookAt()));
	//
	engine->getLightAt(1)->setEnabled(false);
	engine->getLightAt(2)->setEnabled(false);
	//
	engine->getLightAt(Engine::LIGHTIDX_SUN)->setupSun(0.15f);
	engine->getLightAt(Engine::LIGHTIDX_MOON)->setupMoon(0.15f);
	//
	engine->setSkyShaderEnabled(true);
	auto sunLight = engine->getLightAt(Engine::LIGHTIDX_SUN);
	sunLight->setDiffuse(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	sunLight->setRenderSource(false);
	sunLight->setEnabled(true);
	auto moonLight = engine->getLightAt(Engine::LIGHTIDX_MOON);
	moonLight->setDiffuse(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	moonLight->setRenderSource(false);
	moonLight->setEnabled(true);
}

void ShadowMapTest::reshape(int32_t width, int32_t height)
{
	engine->reshape(width, height);
}


void ShadowMapTest::onChar(int key, int x, int y) {
	if (key == ' ') pause = pause == true?false:true;
}

void ShadowMapTest::onKeyDown(int key, int keyCode, int x, int y, bool repeat, int modifiers) {
	auto keyChar = Character::toLowerCase(key);
	if (keyChar == 'w') keyW = true;
	if (keyChar == 'a') keyA = true;
	if (keyChar == 's') keyS = true;
	if (keyChar == 'd') keyD = true;
	if (keyChar == '-') keyMinus = true;
	if (keyChar == '+') keyPlus = true;
	if (keyChar == ',') keyComma = true;
	if (keyChar == '.') keyDot = true;
	if (keyCode == KEYBOARD_KEYCODE_LEFT) keyLeft = true;
	if (keyCode == KEYBOARD_KEYCODE_RIGHT) keyRight = true;
	if (keyCode == KEYBOARD_KEYCODE_UP) keyUp = true;
	if (keyCode == KEYBOARD_KEYCODE_DOWN) keyDown = true;
}

void ShadowMapTest::onKeyUp(int key, int keyCode, int x, int y) {
	auto keyChar = Character::toLowerCase(key);
	if (keyChar == 'w') keyW = false;
	if (keyChar == 'a') keyA = false;
	if (keyChar == 's') keyS = false;
	if (keyChar == 'd') keyD = false;
	if (keyChar == '-') keyMinus = false;
	if (keyChar == '+') keyPlus = false;
	if (keyChar == ',') keyComma = false;
	if (keyChar == '.') keyDot = false;
	if (keyChar == 't') engine->toggleRenderToScreen();
	if (keyCode == KEYBOARD_KEYCODE_LEFT) keyLeft = false;
	if (keyCode == KEYBOARD_KEYCODE_RIGHT) keyRight = false;
	if (keyCode == KEYBOARD_KEYCODE_UP) keyUp = false;
	if (keyCode == KEYBOARD_KEYCODE_DOWN) keyDown = false;
}

void ShadowMapTest::onMouseDragged(int x, int y) {
}

void ShadowMapTest::onMouseMoved(int x, int y) {
}

void ShadowMapTest::onMouseButton(int button, int state, int x, int y) {
	if (state == MOUSE_BUTTON_UP) {
		mouseClicked = true;
		mouseClickPosition = { x, y };
	}
}

void ShadowMapTest::onMouseWheel(int button, int direction, int x, int y) {
}
