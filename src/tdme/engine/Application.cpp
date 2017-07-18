#ifdef __linux__
	#include <GL/freeglut.h>
#elif
	#include <GLUT/glut.h>
#endif

#include <fwd-tdme.h>

#include <java/lang/System.h>
#include <java/lang/Thread.h>

#include <tdme/engine/Application.h>
#include <tdme/utils/StringConverter.h>
#include "ApplicationInputEventsHandler.h"

using tdme::engine::Application;
using tdme::engine::ApplicationInputEventsHandler;
using tdme::utils::StringConverter;
using java::lang::System;

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
	// initialize GLUT
	glutInit(&argc, argv);

#ifdef __APPLE__
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
#else
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitContextVersion(3,2);
#endif
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(StringConverter::toString(title).c_str());
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
	// run
	glutMainLoop();
}

void Application::glutDisplay() {
	if (Application::application->initialized == false) {
		Application::application->initialize();
		Application::application->initialized = true;
	}
	int64_t timeNow = System::currentTimeMillis();
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
