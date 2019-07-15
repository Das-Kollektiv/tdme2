#include <tdme/tests/RayTracingTest.h>

#include <string>

#include <tdme/utils/Time.h>

#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/PrimitiveModel.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/tools/leveleditor/logic/Level.h>
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/Time.h>

using std::string;
using std::to_string;

using tdme::tests::RayTracingTest;

using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::Rotation;
using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::physics::Body;
using tdme::engine::physics::World;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::PrimitiveModel;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::math::Quaternion;
using tdme::tools::leveleditor::logic::Level;
using tdme::tools::shared::files::ModelMetaDataFileImport;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::utils::Console;
using tdme::utils::MutableString;
using tdme::utils::Time;

constexpr int32_t RayTracingTest::RIGID_TYPEID_STANDARD;

constexpr int32_t RayTracingTest::BOX_COUNT;

RayTracingTest::RayTracingTest()
{
	engine = Engine::getInstance();
	world = new World();
}


void RayTracingTest::main(int argc, char** argv)
{
	auto rayTracingTest = new RayTracingTest();
	rayTracingTest->run(argc, argv, "RayTracingTest", rayTracingTest);
}

void RayTracingTest::display()
{
	auto transformations = world->getBody("player")->getTransformations();
	auto& yRotation = transformations.getRotation(0);
	yRotation.setAxis(Rotation::Y_AXIS);
	yRotation.setAngle(rotationY);
	transformations.update();
	world->getBody("player")->fromTransformations(transformations);

	// movement player
	{
		Vector3 movementVector;
		Vector3 tmpMovementVector;
		if (keyLeft == true) {
			movementVector.add(
				yRotation.getQuaternion().multiply(Vector3(1.0f, 0.0f, 0.0f), tmpMovementVector)
			);
		} else
		if (keyRight == true) {
			movementVector.sub(
				yRotation.getQuaternion().multiply(Vector3(1.0f, 0.0f, 0.0f), tmpMovementVector)
			);
		}
		if (keyUp == true) {
			movementVector.add(
				yRotation.getQuaternion().multiply(Vector3(0.0f, 0.0f, 1.0f), tmpMovementVector)
			);
		} else
		if (keyDown == true) {
			movementVector.sub(
				yRotation.getQuaternion().multiply(Vector3(0.0f, 0.0f, 1.0f), tmpMovementVector)
			);
		}
		world->getBody("player")->setLinearVelocity(movementVector.scale(4.0f));
	}

	Vector3 camLookAt;
	Vector3 camLookFrom;
	{
		auto headYPosition = 1.65f;
		float trdMovemventPlayerXAxis = 0.25f;
		float trdDistanceCamPlayer = 1.0f;

		Quaternion rotationQuaternion = transformations.getRotation(0).getQuaternion();
		rotationQuaternion.multiply((Quaternion().rotate(rotationX, Vector3(1.0f, 0.0f, 0.0f))));
		Vector3 vectorRotated;

		camLookAt.set(transformations.getTranslation().clone().addY(headYPosition));
		camLookAt.add(rotationQuaternion.multiply(Vector3(0.0f, 0.0f, 1.0f), vectorRotated).scale(80.0f));

		camLookFrom.set(transformations.getTranslation().clone().addY(headYPosition));
		camLookFrom.sub(rotationQuaternion.multiply(Vector3(0.0f, 0.0f, 1.0f), vectorRotated).scale(trdDistanceCamPlayer));
		camLookFrom.sub(transformations.getRotation(0).getQuaternion().multiply(Vector3(trdMovemventPlayerXAxis, 0.0f, 0.0f), vectorRotated));

		engine->getCamera()->setLookFrom(camLookFrom);
		engine->getCamera()->setLookAt(camLookAt);
		engine->getCamera()->setUpVector(Camera::computeUpVector(camLookFrom, camLookAt));
	}

	{
		dynamic_cast<GUIElementNode*>(engine->getGUI()->getScreen("crosshair")->getNodeById("crosshair_hud"))->getActiveConditions().removeAll();
		float trdTraceLength = 3.5f;
		Vector3 traceVector;
		Vector3 traceEnd;
		Vector3 hitPoint;
		traceVector.set(camLookAt).sub(camLookFrom);
		traceEnd.set(traceVector);
		traceEnd.scale(1.0f / traceEnd.computeLength());
		traceEnd.scale(trdTraceLength);
		traceEnd.add(camLookFrom);
		auto rayTracedRigidBody = world->doRayCasting(
			Level::RIGIDBODY_TYPEID_STATIC | Level::RIGIDBODY_TYPEID_DYNAMIC,
			camLookFrom,
			traceEnd,
			hitPoint,
			"player"
		);
		if (rayTracedRigidBody != nullptr) {
			dynamic_cast<GUITextNode*>(engine->getGUI()->getScreen("crosshair")->getNodeById("crosshair_hud_id"))->setText(MutableString("Interact with " + rayTracedRigidBody->getId()));
			dynamic_cast<GUIElementNode*>(engine->getGUI()->getScreen("crosshair")->getNodeById("crosshair_hud"))->getActiveConditions().add("pickup");
		}
	}

	// update world, display engine
	auto start = Time::getCurrentMillis();
	world->update(1.0f / 60.0f);
	engine->getEntity("player")->fromTransformations(transformations);
	engine->display();
	engine->getGUI()->render();
	auto end = Time::getCurrentMillis();
	Console::println(string("RayTracingTest::display::" + to_string(end - start) + "ms"));
}

void RayTracingTest::dispose()
{
	engine->dispose();
}

void RayTracingTest::initialize()
{
	engine->initialize();
	engine->setSceneColor(Color4(0.8f, 0.8f, 0.8f, 1.0f));
	//engine->addPostProcessingProgram("depth_fog");
	Object3D* entity;
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(100.0f);
	cam->setLookFrom(Vector3(0.0f, 5.0f, 10.0f));
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
	auto ground = new OrientedBoundingBox(Vector3(0.0f, 0.0f, 0.0f), OrientedBoundingBox::AABB_AXIS_X, OrientedBoundingBox::AABB_AXIS_Y, OrientedBoundingBox::AABB_AXIS_Z, Vector3(240.0f, 1.0f, 240.0f));
	auto groundModel = PrimitiveModel::createModel(ground, "ground_model");
	(*groundModel->getMaterials())["tdme.primitive.material"]->setAmbientColor(Color4(0.25f, 0.25f, 0.25f, 1.0f));
	(*groundModel->getMaterials())["tdme.primitive.material"]->setDiffuseColor(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	entity = new Object3D("ground", groundModel);
	entity->setTranslation(Vector3(0.0f, -1.0f, 0.0f));
	entity->update();
	engine->addEntity(entity);
	world->addStaticRigidBody("ground", true, RIGID_TYPEID_STANDARD, entity->getTransformations(), 0.5f, {ground});
	auto interactionTable = ModelMetaDataFileImport::doImport(-1, "resources/tests/asw", "Mesh_Interaction_Table.fbx.tmm");
	auto logProduct = ModelMetaDataFileImport::doImport(-1, "resources/tests/asw", "Mesh_Product_Log.fbx.tmm");
	int interactionTableIdx = 0;
	for (float z = -20.0f; z < 20.0f; z+= 5.0f)
	for (float x = -20.0f; x < 20.0f; x+= 5.0f) {
		// engine
		auto id = "interactionTable." + to_string(interactionTableIdx++);
		auto entity = new Object3D(
			id,
			interactionTable->getModel()
		);
		entity->setTranslation(Vector3(x, 0.0f, z));
		entity->update();
		engine->addEntity(entity);

		// physics
		Level::createBody(
			world,
			interactionTable,
			id,
			entity->getTransformations(),
			Level::RIGIDBODY_TYPEID_STATIC
		);
	}
	auto capsuleBig = new Capsule(Vector3(0.0f, 0.35f, 0.0f), Vector3(0.0f, 1.5f, 0.0f), 0.35f);
	auto capsuleBigModel = PrimitiveModel::createModel(capsuleBig, "capsulebig_model");
	(*capsuleBigModel->getMaterials())["tdme.primitive.material"]->setAmbientColor(Color4(1.0f, 0.8f, 0.8f, 1.0f));
	(*capsuleBigModel->getMaterials())["tdme.primitive.material"]->setDiffuseColor(Color4(1.0f, 0.0f, 0.0f, 1.0f));
	entity = new Object3D("player", capsuleBigModel);
	entity->setDynamicShadowingEnabled(true);
	entity->setTranslation(Vector3(-2.0f, 0.0f, 0.0f));
	entity->addRotation(Vector3(0.0f, 1.0f, 0.0f), 0.0f);
	entity->update();
	engine->addEntity(entity);
	world->addRigidBody("player", true, Level::RIGIDBODY_TYPEID_DYNAMIC, entity->getTransformations(), 0.0f, 1.0f, 80.0f, Body::getNoRotationInertiaTensor(), {capsuleBig});

	//
	engine->getGUI()->addScreen("crosshair", GUIParser::parse("resources/screens", "crosshair.xml"));
	engine->getGUI()->addRenderScreen("crosshair");
}

void RayTracingTest::reshape(int32_t width, int32_t height)
{
	engine->reshape(0, 0, width, height);
}
void RayTracingTest::onKeyDown (unsigned char key, int x, int y) {
	auto keyChar = tolower(key);
	if (keyChar == 'w') keyUp = true;
	if (keyChar == 'a') keyLeft = true;
	if (keyChar == 's') keyDown = true;
	if (keyChar == 'd') keyRight = true;
}

void RayTracingTest::onKeyUp(unsigned char key, int x, int y) {
	auto keyChar = tolower(key);
	if (keyChar == 'w') keyUp = false;
	if (keyChar == 'a') keyLeft = false;
	if (keyChar == 's') keyDown = false;
	if (keyChar == 'd') keyRight = false;
}

void RayTracingTest::onSpecialKeyDown (int key, int x, int y) {
}

void RayTracingTest::onSpecialKeyUp(int key, int x, int y) {
}

void RayTracingTest::onMouseDragged(int x, int y) {
	if (mouseLastXDragged != -1 && mouseLastYDragged != -1) {
		rotationY-= x - mouseLastXDragged;
		rotationX+= y - mouseLastYDragged;
	}
	mouseLastXDragged = x;
	mouseLastYDragged = y;
}

void RayTracingTest::onMouseMoved(int x, int y) {
}

void RayTracingTest::onMouseButton(int button, int state, int x, int y) {
	mouseLastXDragged = -1;
	mouseLastYDragged = -1;
}

void RayTracingTest::onMouseWheel(int button, int direction, int x, int y) {
}
