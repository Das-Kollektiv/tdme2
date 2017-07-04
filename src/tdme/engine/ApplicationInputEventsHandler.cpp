#include <GLUT/glut.h>

#include "ApplicationInputEventsHandler.h"

using tdme::engine::ApplicationInputEventsHandler;

int ApplicationInputEventsHandler::getKeyboardModifiers() {
	return glutGetModifiers();
}
