#ifdef __linux__
	#include <GL/freeglut.h>
#elif __APPLE__
	#include <GLUT/glut.h>
#endif

#include "ApplicationInputEventsHandler.h"

using tdme::engine::ApplicationInputEventsHandler;

int ApplicationInputEventsHandler::getKeyboardModifiers() {
	return glutGetModifiers();
}
