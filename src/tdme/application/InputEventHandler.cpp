
#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__linux__) || defined(_WIN32)
	#include <GL/freeglut.h>
#elif defined(__APPLE__)
	#include <GLUT/glut.h>
#elif defined(__HAIKU__)
	#include <GL/glut.h>
#endif

#include "InputEventHandler.h"

using tdme::application::InputEventHandler;

InputEventHandler::~InputEventHandler() {
}

int InputEventHandler::getKeyboardModifiers() {
	return glutGetModifiers();
}
