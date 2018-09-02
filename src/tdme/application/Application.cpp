#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__linux__)
	#if !defined(__arm__) && !defined(__aarch64__)
		#define GLEW_NO_GLU
		#include <GL/glew.h>
	#endif
	#include <GL/freeglut.h>
#elif defined(__APPLE__)
	#include <GLUT/glut.h>
	#include <Carbon/Carbon.h>
#elif defined(_WIN32)
	#include <GL/glew.h>
	#include <GL/freeglut.h>
#elif defined(__HAIKU__)
	#include <GL/glew.h>
	#include <GL/glut.h>
#endif

#include <stdlib.h>

#include <string>

#include <tdme/tdme.h>

#include <tdme/utils/Time.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/application/Application.h>
#include <tdme/application/ApplicationInputEventsHandler.h>
#include <tdme/utils/Console.h>

using std::string;
using std::string;
using std::to_string;

using tdme::application::Application;
using tdme::application::ApplicationInputEventsHandler;
using tdme::utils::Console;
using tdme::utils::Time;
using tdme::os::threading::Thread;

constexpr int32_t Application::FPS;
Application* Application::application = nullptr;
ApplicationInputEventsHandler* Application::inputEventHandler = nullptr;
int64_t Application::timeLast = -1L;

Application::Application() {
	Application::application = this;
}

Application::~Application() {
}

void Application::setInputEventHandler(ApplicationInputEventsHandler* inputEventHandler) {
	Application::inputEventHandler = inputEventHandler;
}

void Application::setMouseCursor(int mouseCursor) {
	glutSetCursor(mouseCursor);
}

void Application::setMousePosition(int x, int y) {
	#if defined(__APPLE__)
		CGPoint point;
		point.x = glutGet((GLenum)GLUT_WINDOW_X) + x;
		point.y = glutGet((GLenum)GLUT_WINDOW_Y) + y;
		CGWarpMouseCursorPosition(point);
		CGAssociateMouseAndMouseCursorPosition(true);
	#else
		glutWarpPointer(x, y);
	#endif
}

void Application::swapBuffers() {
	glutSwapBuffers();
}

void Application::run(int argc, char** argv, const string& title, ApplicationInputEventsHandler* inputEventHandler) {
	Application::inputEventHandler = inputEventHandler;
	glutInit(&argc, argv);
#if defined(__APPLE__)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
#elif ((defined(__linux__) || defined(__FreeBSD__) || defined(__NetBSD__)) && !defined(__arm__) && !defined(__aarch64__)) || defined(_WIN32)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//	glutInitContextVersion(4,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	/*
	glutInitContextVersion(3, 1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	*/
#elif defined(__linux__) && (defined(__arm__) || defined(__aarch64__))
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitContextVersion(2,0);
#elif defined(__HAIKU__)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#endif
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow((title).c_str());
#if defined(_WIN32) || ((defined(__FreeBSD__) || defined(__NetBSD__) || defined(__linux__)) && !defined(__arm__) && !defined(__aarch64__)) || defined(__HAIKU__)
	glewExperimental = true;
	GLenum glewInitStatus = glewInit();
	if (glewInitStatus != GLEW_OK) {
		Console::println("glewInit(): Error: " + (string((char*)glewGetErrorString(glewInitStatus))));
		exit(0);
	}
#endif
	// glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutReshapeFunc(Application::glutReshape);
	glutDisplayFunc(Application::glutDisplay);
	glutIdleFunc(Application::glutDisplay);
	glutKeyboardFunc(Application::glutOnKeyDown);
	glutKeyboardUpFunc(Application::glutOnKeyUp);
	glutSpecialFunc(Application::glutOnSpecialKeyDown);
	glutSpecialUpFunc(Application::glutOnSpecialKeyUp);
	glutMotionFunc(Application::glutOnMouseDragged);
	glutPassiveMotionFunc(Application::glutOnMouseMoved);
	glutMouseFunc(Application::glutOnMouseButton);
#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__linux__) || defined(_WIN32)
	glutMouseWheelFunc(Application::glutOnMouseWheel);
#endif
	glutMainLoop();
}

void Application::glutDisplay() {
	if (Application::application->initialized == false) {
		Application::application->initialize();
		Application::application->initialized = true;
	}
	int64_t timeNow = Time::getCurrentMillis();
	int64_t timeFrame = 1000/Application::FPS;
	if (Application::timeLast != -1L) {
		int64_t timePassed = timeNow - timeLast;
		if (timePassed < timeFrame) Thread::sleep(timeFrame - timePassed);
	}
	Application::timeLast = timeNow;
	Application::application->display();
	glutSwapBuffers();
}

void Application::glutReshape(int32_t width, int32_t height) {
	if (Application::application->initialized == false) {
		Application::application->initialize();
		Application::application->initialized = true;
	}
	Application::application->reshape(width, height);
}

void Application::glutOnKeyDown (unsigned char key, int x, int y) {
	if (Application::inputEventHandler == nullptr) return;
	Application::inputEventHandler->onKeyDown(key, x, y);
}

void Application::glutOnKeyUp(unsigned char key, int x, int y) {
	if (Application::inputEventHandler == nullptr) return;
	Application::inputEventHandler->onKeyUp(key, x, y);
}

void Application::glutOnSpecialKeyDown (int key, int x, int y) {
	if (Application::inputEventHandler == nullptr) return;
	Application::inputEventHandler->onSpecialKeyDown(key, x, y);
}

void Application::glutOnSpecialKeyUp(int key, int x, int y) {
	if (Application::inputEventHandler == nullptr) return;
	Application::inputEventHandler->onSpecialKeyUp(key, x, y);
}

void Application::glutOnMouseDragged(int x, int y) {
	if (Application::inputEventHandler == nullptr) return;
	Application::inputEventHandler->onMouseDragged(x, y);
}

void Application::glutOnMouseMoved(int x, int y) {
	if (Application::inputEventHandler == nullptr) return;
	Application::inputEventHandler->onMouseMoved(x, y);
}

void Application::glutOnMouseButton(int button, int state, int x, int y) {
	if (Application::inputEventHandler == nullptr) return;
	Application::inputEventHandler->onMouseButton(button, state, x, y);
}

void Application::glutOnMouseWheel(int button, int direction, int x, int y) {
	if (Application::inputEventHandler == nullptr) return;
	Application::inputEventHandler->onMouseWheel(button, direction, x, y);
}
