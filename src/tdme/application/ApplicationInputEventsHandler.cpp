#if defined(__FreeBSD__) or defined(__linux__) or defined(_WIN32)
	#include <GL/freeglut.h>
#elif defined(__APPLE__)
	#include <GLUT/glut.h>
#elif defined(__HAIKU__)
	#include <GL/glut.h>
#endif

#include <tdme/application/ApplicationInputEventsHandler.h>

using tdme::application::ApplicationInputEventsHandler;

int ApplicationInputEventsHandler::getKeyboardModifiers() {
	return glutGetModifiers();
}
