#include <tdme/tools/shared/views/CameraRotationInputHandler.h>

#include <string>

#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Character.h>

using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Transformations;
using tdme::gui::GUI;
using tdme::gui::events::GUIKeyboardEvent_Type;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utils::Character;

CameraRotationInputHandler::CameraRotationInputHandler(Engine* engine) 
{
	this->engine = engine;
	keyLeft = false;
	keyRight = false;
	keyUp = false;
	keyDown = false;
	keyPlus = false;
	keyMinus = false;
	keyR = false;
	mouseDragging = false;
	maxAxisDimension = 0.0f;
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

float CameraRotationInputHandler::getMaxAxisDimension()
{
	return maxAxisDimension;
}

void CameraRotationInputHandler::setMaxAxisDimension(float maxAxisDimension)
{
	this->maxAxisDimension = maxAxisDimension;
}

const Transformations& CameraRotationInputHandler::getLookFromRotations()
{
	return lookFromRotations;
}

float CameraRotationInputHandler::getScale()
{
	return scale;
}

void CameraRotationInputHandler::setScale(float scale)
{
	this->scale = scale;
}

void CameraRotationInputHandler::reset()
{
	resetRequested = true;
}

void CameraRotationInputHandler::handleInputEvents()
{
	for (auto i = 0; i < engine->getGUI()->getMouseEvents().size(); i++) {
		auto& event = engine->getGUI()->getMouseEvents()[i];
		if (event.isProcessed() == true)
			continue;

		if (mouseDragging == true) {
			if (event.getButton() == 1) {
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
			} else {
				mouseDragging = false;
			}
		} else {
			if (event.getButton() == 1) {
				mouseDragging = true;
				mouseLastX = event.getX();
				mouseLastY = event.getY();
			}
		}
		auto mouseWheel = event.getWheelY();
		if (mouseWheel != 0) {
			scale += mouseWheel * 0.1f;
			if (scale < 0.05f)
				scale = 0.05f;

		}
	}
	for (auto i = 0; i < engine->getGUI()->getKeyboardEvents().size(); i++) {
		auto& event = engine->getGUI()->getKeyboardEvents()[i];
		if (event.isProcessed() == true)
			continue;

		auto isKeyDown = event.getType() == GUIKeyboardEvent_Type::KEYBOARDEVENT_KEY_PRESSED;
		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_LEFT)
			keyLeft = isKeyDown;

		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_RIGHT)
			keyRight = isKeyDown;

		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_UP)
			keyUp = isKeyDown;

		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_DOWN)
			keyDown = isKeyDown;

		if (Character::toLowerCase(event.getKeyChar()) == u'.')
			keyPeriod = isKeyDown;

		if (Character::toLowerCase(event.getKeyChar()) == u',')
			keyComma = isKeyDown;

		if (Character::toLowerCase(event.getKeyChar()) == u'+')
			keyPlus = isKeyDown;

		if (Character::toLowerCase(event.getKeyChar()) == u'-')
			keyMinus = isKeyDown;

		if (Character::toLowerCase(event.getKeyChar()) == u'r')
			keyR = isKeyDown;

	}
	auto& rotationX = lookFromRotations.getRotation(0);
	auto& rotationY = lookFromRotations.getRotation(1);
	auto& rotationZ = lookFromRotations.getRotation(2);
	if (keyLeft)
		rotationX.setAngle(rotationX.getAngle() - 1.0f);

	if (keyRight)
		rotationX.setAngle(rotationX.getAngle() + 1.0f);

	if (keyUp)
		rotationY.setAngle(rotationY.getAngle() + 1.0f);

	if (keyDown)
		rotationY.setAngle(rotationY.getAngle() - 1.0f);

	if (keyComma)
		rotationZ.setAngle(rotationZ.getAngle() - 1.0f);

	if (keyPeriod)
		rotationZ.setAngle(rotationZ.getAngle() + 1.0f);

	if (keyMinus)
		scale += 0.05f;

	if (keyPlus && scale > 0.05f)
		scale -= 0.05f;

	if (keyR == true || resetRequested == true) {
		rotationY.setAngle(-45.0f);
		rotationZ.setAngle(0.0f);
		scale = 1.0f;
	}
	if (keyLeft || keyRight || keyUp|| keyDown|| keyComma|| keyPeriod|| keyR|| resetRequested) {
		lookFromRotations.update();
		resetRequested = false;
	}
	auto cam = engine->getCamera();
	auto lookAt = cam->getLookAt();
	auto model = engine->getEntity("model");
	if (model != nullptr) {
		lookAt.set(model->getBoundingBoxTransformed()->getCenter());
	} else {
		lookAt.set(0.0f, 0.0f, 0.0f);
	}
	Vector3 forwardVector(0.0f, 0.0f, 1.0f);
	Vector3 forwardVectorTransformed;
	Vector3 upVector;
	lookFromRotations.getTransformationsMatrix().multiply(forwardVector, forwardVectorTransformed).scale(scale);
	lookFromRotations.getRotation(2).getQuaternion().multiply(Vector3(0.0f, 1.0f, 0.0f), upVector).normalize();
	auto lookFrom = lookAt.clone().add(forwardVectorTransformed);
	cam->setLookFrom(lookFrom);
	cam->setLookAt(lookAt);
	cam->setUpVector(upVector);
}
