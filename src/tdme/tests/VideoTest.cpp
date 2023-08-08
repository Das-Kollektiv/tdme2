#include <tdme/tests/VideoTest.h>

#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/utilities/Time.h>

#include <tdme/application/Application.h>
#include <tdme/audio/Audio.h>
#include <tdme/audio/PacketAudioStream.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/DynamicColorTexture.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/Rotation.h>
#include <tdme/math/Math.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/utilities/ObjectDeleter.h>
#include <tdme/utilities/Primitives.h>
#include <tdme/utilities/Time.h>
#include <tdme/video/decoder/MPEG1Decoder.h>

using std::make_unique;
using std::unique_ptr;

using std::string;
using std::to_string;
using std::vector;

using tdme::tests::VideoTest;

using tdme::application::Application;
using tdme::audio::Audio;
using tdme::audio::PacketAudioStream;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::model::UpVector;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::Camera;
using tdme::engine::DynamicColorTexture;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::Light;
using tdme::engine::Object;
using tdme::engine::Rotation;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::utilities::ModelTools;
using tdme::utilities::ObjectDeleter;
using tdme::utilities::Primitives;
using tdme::utilities::Time;
using tdme::video::decoder::MPEG1Decoder;

VideoTest::VideoTest() {
	Application::setLimitFPS(true);
	audio = Audio::getInstance();
	engine = Engine::getInstance();
}

Model* VideoTest::createWallModel()
{
	auto wall = new Model("wall", "wall", UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	auto wallMaterial = new Material("wall");
	wallMaterial->setSpecularMaterialProperties(new SpecularMaterialProperties());
	wallMaterial->getSpecularMaterialProperties()->setAmbientColor(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	wallMaterial->getSpecularMaterialProperties()->setDiffuseColor(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	wall->getMaterials()["wall"] = wallMaterial;
	auto wallNode = new Node(wall, nullptr, "wall", "wall");
	vector<FacesEntity> nodeFacesEntities;
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
	facesFarPlane.push_back(Face(wallNode, 0, 1, 2, 0, 0, 0, 0, 1, 2));
	facesFarPlane.push_back(Face(wallNode, 2, 3, 0, 0, 0, 0, 2, 3, 0));
	FacesEntity nodeFacesEntityFarPlane(wallNode, "wall");
	nodeFacesEntityFarPlane.setMaterial(wallMaterial);
	nodeFacesEntityFarPlane.setFaces(facesFarPlane);
	nodeFacesEntities.push_back(nodeFacesEntityFarPlane);
	wallNode->setVertices(vertices);
	wallNode->setNormals(normals);
	wallNode->setTextureCoordinates(textureCoordinates);
	wallNode->setFacesEntities(nodeFacesEntities);
	wall->getNodes()["wall"] = wallNode;
	wall->getSubNodes()["wall"] = wallNode;
	ModelTools::prepareForIndexedRendering(wall);
	return wall;
}

void VideoTest::main(int argc, char** argv)
{
	auto videoTest = new VideoTest();
	videoTest->run(argc, argv, "VideoTest", videoTest);
}

void VideoTest::display()
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

	// video
	videoDecoder.update(static_cast<float>(engine->getTiming()->getDeltaTime()) / 1000.0f);
	auto videoTextureData = videoTexture->getByteBuffer();
	videoTextureData->clear();
	if (videoDecoder.readVideoFromStream(videoTextureData) > 0) {
		videoTexture->update();
	}
	videoAudioBuffer->clear();
	if (videoDecoder.readAudioFromStream(videoAudioBuffer.get()) > 0) {
		videoAudioStream->addPacket(videoAudioBuffer.get());
	}

	// audio
	audio->update();

	// rendering
	auto start = Time::getCurrentMillis();
	engine->display();
	auto end = Time::getCurrentMillis();
	auto rendererStatistics = engine->getRendererStatistics();
	Console::println(
		string("VideoTest::display::") + to_string(end - start) + "ms; " +
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

void VideoTest::dispose()
{
	engine->dispose();
	videoTexture->dispose();
}

void VideoTest::initialize()
{
	engine->initialize();
	Object* entity;
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(30.0f);
	cam->setLookFrom(Vector3(0.0f, 3.0f, 60.0f));
	cam->setLookAt(Vector3(0.0f, 0.0f, 0.0f));
	cam->setUpVector(cam->computeUpVector(cam->getLookFrom(), cam->getLookAt()));
	auto light0 = engine->getLightAt(0);
	light0->setAmbient(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	light0->setDiffuse(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	light0->setSpecular(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	light0->setPosition(Vector4(0.0f, 20000.0f, 0.0f, 0.0f));
	light0->setSpotDirection(Vector3(0.0f, 0.0f, 0.0f).sub(Vector3(light0->getPosition().getX(), light0->getPosition().getY(), light0->getPosition().getZ())));
	light0->setConstantAttenuation(0.5f);
	light0->setLinearAttenuation(0.0f);
	light0->setQuadraticAttenuation(0.0f);
	light0->setSpotExponent(0.0f);
	light0->setSpotCutOff(180.0f);
	light0->setEnabled(true);
	auto ground = bvDeleter.add(new OrientedBoundingBox(Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X, OrientedBoundingBox::AABB_AXIS_Y, OrientedBoundingBox::AABB_AXIS_Z, Vector3(16.0f, 1.0f, 15.0f)));
	auto groundModel = modelDeleter.add(Primitives::createModel(ground, "ground_model"));
	groundModel->getMaterials()["primitive"]->getSpecularMaterialProperties()->setAmbientColor(Color4(0.8f, 0.8f, 0.8f, 1.0f));
	groundModel->getMaterials()["primitive"]->getSpecularMaterialProperties()->setDiffuseColor(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	entity = new Object("ground", groundModel);
	entity->setTranslation(Vector3(0.0f, -1.0f, 0.0f));
	entity->setReceivesShadows(true);
	entity->update();
	engine->addEntity(entity);
	auto farPlaneModel = modelDeleter.add(createWallModel());
	auto farPlane = new Object("wall", farPlaneModel);
	farPlane->addRotation(Rotation::Y_AXIS, 180.0f);
	farPlane->update();
	engine->addEntity(farPlane);
	// video
	videoDecoder.openFile("resources/tests/video", "video.mpg");
	videoTexture = make_unique<DynamicColorTexture>(videoDecoder.getVideoWidth(), videoDecoder.getVideoHeight());
	videoTexture->initialize();
	farPlane->bindDiffuseTexture(videoTexture.get(), "wall", "wall");
	// audio
	videoAudioBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(32768));
	videoAudioStream = new PacketAudioStream("video");
	videoAudioStream->setParameters(videoDecoder.getAudioSampleRate(), videoDecoder.getAudioChannels(), 32768);
	audio->addEntity(videoAudioStream);
	videoAudioStream->play();
}

void VideoTest::reshape(int32_t width, int32_t height)
{
	engine->reshape(width, height);
}

void VideoTest::onChar(int key, int x, int y) {
}

void VideoTest::onKeyDown(int key, int keyCode, int x, int y, bool repeat, int modifiers) {
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

void VideoTest::onKeyUp(int key, int keyCode, int x, int y) {
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

void VideoTest::onMouseDragged(int x, int y) {
}

void VideoTest::onMouseMoved(int x, int y) {
}

void VideoTest::onMouseButton(int button, int state, int x, int y) {
}

void VideoTest::onMouseWheel(int button, int direction, int x, int y) {
}
