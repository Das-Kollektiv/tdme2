#if defined(__linux__)
	#include <GL/freeglut.h>
#elif defined(__APPLE__)
	#include <GLUT/glut.h>
#elif defined(_WIN32)
	#include <GL/glew.h>
	#include <GL/freeglut.h>
#endif


#include <stdlib.h>

#include <string>

#include <tdme.h>

#include <tdme/utils/Time.h>
#include <tdme/os/threading/Thread.h>

#include <tdme/engine/Application.h>
#include <tdme/utils/StringConverter.h>
#include "ApplicationInputEventsHandler.h"
#include <tdme/utils/Console.h>
#include <tdme/utils/StringConverter.h>

using std::string;
using std::wstring;
using std::to_wstring;

using tdme::engine::Application;
using tdme::engine::ApplicationInputEventsHandler;
using tdme::utils::StringConverter;
using tdme::utils::Console;
using tdme::utils::StringConverter;
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

void Application::run(int argc, char** argv, const wstring& title, ApplicationInputEventsHandler* inputEventHandler) {
	Application::inputEventHandler = inputEventHandler;
	glutInit(&argc, argv);
#if defined(__APPLE__)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
#elif defined(__linux__) and !defined(__arm__) and !defined(__aarch64__)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitContextVersion(2,1);
#elif defined(__linux__) and (defined(__arm__) or defined(__aarch64__))
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitContextVersion(2,0);
#elif defined(_WIN32)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitContextVersion(3,2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
#endif
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(StringConverter::toString(title).c_str());
#if defined(_WIN32)
	glewExperimental = TRUE;
	GLenum glewInitStatus = glewInit();
	if (glewInitStatus != GLEW_OK) {
		Console::println(L"glewInit(): Error: " + StringConverter::toWideString(string((char*)glewGetErrorString(glewInitStatus))));
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
