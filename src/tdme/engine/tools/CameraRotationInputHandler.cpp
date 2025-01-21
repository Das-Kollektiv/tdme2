#include <tdme/engine/tools/CameraRotationInputHandler.h>

#include <agui/agui.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/GUI.h>

#include <tdme/tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/engine/tools/fwd-tdme.h>
#include <tdme/engine/tools/CameraRotationInputHandlerEventHandler.h>
#include <tdme/utilities/Character.h>

using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::GUI;

using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::engine::tools::CameraRotationInputHandler;
using tdme::engine::tools::CameraRotationInputHandlerEventHandler;
using tdme::utilities::Character;

CameraRotationInputHandler::CameraRotationInputHandler(Engine* engine, CameraRotationInputHandlerEventHandler* eventHandler)
{
	this->engine = engine;
	this->eventHandler = eventHandler;
	keyLeft = false;
	keyRight = false;
	keyUp = false;
	keyDown = false;
	keyPeriod = false;
	keyComma = false;
	keyPlus = false;
	keyMinus = false;
	keyR = false;
	mouseDragging = false;
	defaultScale = 1.0f;
	scale = 1.0f;
	lookFromRotations.addRotation(Vector3(0.0f, 1.0f, 0.0f), -45.0f);
	lookFromRotations.addRotation(Vector3(1.0f, 0.0f, 0.0f), -45.0f);
	lookFromRotations.addRotation(Vector3(0.0f, 0.0f, 1.0f), 0.0f);
	lookFromRotations.update();
	resetRequested = false;
	mouseLastX = 0;
	mouseLastY = 0;
}

CameraRotationInputHandler::~CameraRotationInputHandler() {
}

const Transform& CameraRotationInputHandler::getLookFromRotations()
{
	return lookFromRotations;
}

void CameraRotationInputHandler::reset()
{
	resetRequested = true;
}

void CameraRotationInputHandler::handleInputEvents()
{
	auto scaling = false;
	auto rotation = false;
	for (const auto& event: engine->getGUI()->getMouseEvents()) {
		if (event.isProcessed() == true) continue;
		if (mouseDragging == true) {
			if (event.getButton() == MOUSE_BUTTON_MIDDLE) {
				auto xMoved = (event.getX() - mouseLastX) / 5.0f;
				auto yMoved = (event.getY() - mouseLastY) / 5.0f;
				mouseLastX = event.getX();
				mouseLastY = event.getY();
				auto& xRotation = lookFromRotations.getRotation(0);
				auto& yRotation = lookFromRotations.getRotation(1);
				auto xRotationAngle = xRotation.getAngle() + xMoved;
				auto yRotationAngle = yRotation.getAngle() + yMoved;
				xRotation.setAngle(xRotationAngle);
				yRotation.setAngle(yRotationAngle);
				lookFromRotations.update();
				rotation = true;
			} else {
				mouseDragging = false;
			}
		} else {
			if (event.getButton() == MOUSE_BUTTON_MIDDLE) {
				mouseDragging = true;
				mouseLastX = event.getX();
				mouseLastY = event.getY();
			}
		}
		auto mouseWheel = event.getWheelY();
		if (mouseWheel != 0) {
			scale += -mouseWheel * 0.1f;
			if (scale < 0.0001f) scale = 0.0001f;
			scaling = true;
		}
	}
	for (const auto& event: engine->getGUI()->getKeyboardEvents()) {
		if (event.isProcessed() == true) continue;
		if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_TYPED) continue;
		auto isKeyDown = event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED;
		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_LEFT)
			keyLeft = isKeyDown;

		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_RIGHT)
			keyRight = isKeyDown;

		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_UP)
			keyUp = isKeyDown;

		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_DOWN)
			keyDown = isKeyDown;

		if (Character::toLowerCase(event.getKeyChar()) == '.')
			keyPeriod = isKeyDown;

		if (Character::toLowerCase(event.getKeyChar()) == ',')
			keyComma = isKeyDown;

		if (Character::toLowerCase(event.getKeyChar()) == '+')
			keyPlus = isKeyDown;

		if (Character::toLowerCase(event.getKeyChar()) == '-')
			keyMinus = isKeyDown;

		if (Character::toLowerCase(event.getKeyChar()) == 'r')
			keyR = isKeyDown;

	}

	auto entity = engine->getEntity("model");

	auto& rotationX = lookFromRotations.getRotation(0);
	auto& rotationY = lookFromRotations.getRotation(1);
	auto& rotationZ = lookFromRotations.getRotation(2);

	if (keyLeft == true) rotationX.setAngle(rotationX.getAngle() - 1.0f);
	if (keyRight == true) rotationX.setAngle(rotationX.getAngle() + 1.0f);
	if (keyUp == true) rotationY.setAngle(rotationY.getAngle() + 1.0f);
	if (keyDown == true) rotationY.setAngle(rotationY.getAngle() - 1.0f);
	if (keyComma == true) rotationZ.setAngle(rotationZ.getAngle() - 1.0f);
	if (keyPeriod == true) rotationZ.setAngle(rotationZ.getAngle() + 1.0f);

	if (keyMinus == true) {
		scaling = true;
		scale += 0.05f;
	}
	if (keyPlus  == true) {
		scaling = true;
		scale -= 0.05f;
		if (scale < 0.0001f) scale = 0.0001f;
	}

	if (keyR == true || resetRequested == true) {
		rotationY.setAngle(-45.0f);
		rotationZ.setAngle(0.0f);
		scale = defaultScale;
	}
	if (keyLeft == true ||
		keyRight == true ||
		keyUp == true ||
		keyDown == true ||
		keyComma == true ||
		keyPeriod == true ||
		keyR == true ||
		resetRequested) {
		lookFromRotations.update();
		if (entity != nullptr) {
			worldBoundingBox = *entity->getWorldBoundingBox();
		}
	}
	auto cam = engine->getCamera();
	auto lookAt = cam->getLookAt();
	if (resetRequested == true) {
		if (entity != nullptr) {
			worldBoundingBox = *entity->getWorldBoundingBox();
			lookAt.set(worldBoundingBox.getCenter());
		} else {
			lookAt.set(0.0f, 0.0f, 0.0f);
		}
		resetRequested = false;
	}
	Vector3 forwardVector(0.0f, 0.0f, 1.0f);
	auto forwardVectorTransformed = lookFromRotations.getTransformMatrix().multiply(forwardVector).scale(scale);
	auto upVector = lookFromRotations.getRotation(2).getQuaternion().multiply(Vector3(0.0f, 1.0f, 0.0f)).normalize();
	auto lookFrom = lookAt.clone().add(forwardVectorTransformed);
	cam->setLookFrom(lookFrom);
	cam->setLookAt(lookAt);
	cam->setUpVector(upVector);

	if (scaling == true && eventHandler != nullptr) {
		eventHandler->onCameraScale();
	}
	if ((rotation == true ||
		keyLeft == true ||
		keyRight == true ||
		keyUp == true ||
		keyDown == true ||
		keyComma == true ||
		keyPeriod == true ||
		keyR == true ||
		resetRequested == true) &&
		eventHandler != nullptr) {
		eventHandler->onCameraRotation();
	}
}
