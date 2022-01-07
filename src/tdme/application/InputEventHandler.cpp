#include <tdme/application/InputEventHandler.h>

#include <tdme/tdme.h>

#include <tdme/application/Application.h>

using tdme::application::Application;

using tdme::application::InputEventHandler;

InputEventHandler::~InputEventHandler() {
}

int InputEventHandler::getKeyboardModifiers() {
	return 0;
}
