#if defined(__linux__) or defined(_WIN32)
	#include <GL/freeglut.h>
#elif __APPLE__
	#include <GLUT/glut.h>
#endif

#include <tdme/application/ApplicationInputEventsHandler.h>

using tdme::application::ApplicationInputEventsHandler;

int ApplicationInputEventsHandler::getKeyboardModifiers() {
	return glutGetModifiers();
}
