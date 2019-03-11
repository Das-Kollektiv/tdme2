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
	#include <windows.h>
	#include <dbghelp.h>
	#include <stdio.h>
	#include <string.h>
	#include <tdme/os/threading/Mutex.h>
#elif defined(__HAIKU__)
	#include <GL/glew.h>
	#include <GL/glut.h>
#endif

#include <stdlib.h>

#include <array>
#include <memory>
#include <string>

#include <tdme/tdme.h>

#include <tdme/application/Application.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/HexEncDec.h>
#include <tdme/utils/RTTI.h>
#include <tdme/utils/StringTokenizer.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/Time.h>

using std::array;
using std::string;
using std::shared_ptr;
using std::to_string;

using tdme::application::Application;
using tdme::application::InputEventHandler;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::os::threading::Thread;
using tdme::utils::Console;
using tdme::utils::HexEncDec;
using tdme::utils::RTTI;
using tdme::utils::StringTokenizer;
using tdme::utils::StringUtils;
using tdme::utils::Time;

#if defined(_WIN32) && defined(_MSC_VER) == false
	string exec(const string& cmd) {
		// see: https://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
		array<char, 128> buffer;
		string result;
		shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
		if (!pipe) throw std::runtime_error("popen() failed!");
		while (!feof(pipe.get())) {
			if (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
				result += buffer.data();
		}
		return result;
	}
#endif

#if defined(_WIN32)
	LONG WINAPI windowsExceptionHandler(struct _EXCEPTION_POINTERS* exceptionInfo) {
		// see:
		//	https://asmaloney.com/2017/08/code/crash-reporting-for-mingw-32-windows-and-clang-macos-with-qt/
		//	https://www.gamedev.net/forums/topic/478943-stackwalk64-and-x86/
		//	https://stackoverflow.com/questions/12280472/stackwalk64-does-not-work-with-release-build

		static tdme::os::threading::Mutex mutex("windowsexceptionhandler");

		mutex.lock();

		HANDLE process = GetCurrentProcess();
		HANDLE thread = GetCurrentThread();

		Console::println("windowsExceptionHandler(): process " + to_string((uint64_t)process) + " crashed: Printing stacktrace(thread " + to_string((uint64_t)thread) + ")\n");

		CHAR _pathToExecutable[MAX_PATH];
		GetModuleFileName(GetModuleHandleW(NULL), _pathToExecutable, MAX_PATH);
		string pathToExecutable = _pathToExecutable;

		#if defined(_MSC_VER) == false
			auto addr2lineToolCmd = StringUtils::substring(pathToExecutable, 0, StringUtils::lastIndexOf(pathToExecutable, '\\')) + "\\addr2line.exe";
			if (FileSystem::getInstance()->fileExists(addr2lineToolCmd) == false) {
				Console::println("handler(): " + addr2lineToolCmd + ": not found! Please copy addr2line utility to binary location!");
				mutex.unlock();
				return EXCEPTION_EXECUTE_HANDLER;
			}
			addr2lineToolCmd = "\"" + StringUtils::replace(addr2lineToolCmd, "\\", "\\\\") + "\"";
		#endif

		pathToExecutable = string("\"") + StringUtils::replace(pathToExecutable, "\\", "\\\\") + "\"";

		SymSetOptions(
			SYMOPT_UNDNAME |
			SYMOPT_LOAD_LINES |
			SYMOPT_OMAP_FIND_NEAREST |
			SYMOPT_DEFERRED_LOADS |
			SymGetOptions()
		);

		SymInitialize(
			process,
			nullptr,
			true
		);

		STACKFRAME64 stackFrame;
		memset(&stackFrame, 0, sizeof(STACKFRAME64));

		CONTEXT context;
		memset(&context, 0, sizeof(context));
		context.ContextFlags = CONTEXT_FULL;
		RtlCaptureContext(&context);

		DWORD image;
		#ifdef _M_IX86
			image = IMAGE_FILE_MACHINE_I386;
			stackFrame.AddrPC.Offset = context.Eip;
			stackFrame.AddrPC.Mode = AddrModeFlat;
			stackFrame.AddrFrame.Offset = context.Ebp;
			stackFrame.AddrFrame.Mode = AddrModeFlat;
			stackFrame.AddrStack.Offset = context.Esp;
			stackFrame.AddrStack.Mode = AddrModeFlat;
		#elif _M_X64
			image = IMAGE_FILE_MACHINE_AMD64;
			stackFrame.AddrPC.Offset = context.Rip;
			stackFrame.AddrPC.Mode = AddrModeFlat;
			stackFrame.AddrFrame.Offset = context.Rsp;
			stackFrame.AddrFrame.Mode = AddrModeFlat;
			stackFrame.AddrStack.Offset = context.Rsp;
			stackFrame.AddrStack.Mode = AddrModeFlat;
		#elif _M_IA64
			image = IMAGE_FILE_MACHINE_IA64;
			stackFrame.AddrPC.Offset = context.StIIP;
			stackFrame.AddrPC.Mode = AddrModeFlat;
			stackFrame.AddrFrame.Offset = context.IntSp;
			stackFrame.AddrFrame.Mode = AddrModeFlat;
			stackFrame.AddrBStore.Offset = context.RsBSP;
			stackFrame.AddrBStore.Mode = AddrModeFlat;
			stackFrame.AddrStack.Offset = context.IntSp;
			stackFrame.AddrStack.Mode = AddrModeFlat;
		#else
			#error "Machine not supported"
		#endif

		int frameIdx = 1;
		while (StackWalk64(image, process, thread, &stackFrame, &context, NULL, &SymFunctionTableAccess64, &SymGetModuleBase64, NULL)) {
			if (stackFrame.AddrPC.Offset == stackFrame.AddrReturn.Offset) break;
			if (stackFrame.AddrPC.Offset == 0) continue;

			auto line = 0;
			char _fileName[1024];
			char _functionName[1024];

			// Get function name
			{
				#define cnBufferSize 1024
				unsigned char byBuffer[sizeof(IMAGEHLP_SYMBOL64) + cnBufferSize];
				IMAGEHLP_SYMBOL64* pSymbol = (IMAGEHLP_SYMBOL64*)byBuffer;
				DWORD64 dwDisplacement;
				memset(pSymbol, 0, sizeof(IMAGEHLP_SYMBOL64) + cnBufferSize);
				pSymbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
				pSymbol->MaxNameLength = cnBufferSize;
				if (!SymGetSymFromAddr64(process, stackFrame.AddrPC.Offset, &dwDisplacement, pSymbol)) {
					strcpy(_functionName, "??");
				} else {
					pSymbol->Name[cnBufferSize-1] = '\0';
					strcpy(_functionName, pSymbol->Name);
				}
			}

			// Get file/line number
			{
				IMAGEHLP_LINE64 theLine;
				DWORD dwDisplacement;
				memset(&theLine, 0, sizeof(theLine));
				theLine.SizeOfStruct = sizeof(theLine);
				if(!SymGetLineFromAddr64(process, stackFrame.AddrPC.Offset, &dwDisplacement, &theLine))
				{
					strcpy(_fileName, "??");
				}
				else
				{
					const char* pszFile = strrchr(theLine.FileName, '\\');
					if (!pszFile) pszFile = theLine.FileName; else ++pszFile;
					strncpy(_fileName, pszFile, cnBufferSize);
					line = theLine.LineNumber;
				}
			}

			//
			string functionName = _functionName;
			string fileName = _fileName;
			#if defined(_MSC_VER) == false
				if (functionName == "??") {
					string hexAddr;
					HexEncDec::encodeInt(stackFrame.AddrPC.Offset, hexAddr);
					string addr2LineCommand = "\"" + addr2lineToolCmd + " -f -p -e " + string(pathToExecutable) + " " + hexAddr + "\"";
					auto addr2LineOutput = exec(addr2LineCommand);
					StringTokenizer t;
					t.tokenize(addr2LineOutput, " ");
					if (t.hasMoreTokens() == true) {
						auto addr2lineFunctionName = t.nextToken();
						addr2LineOutput = StringUtils::replace(addr2LineOutput, addr2lineFunctionName, RTTI::demangle(addr2lineFunctionName.c_str()));
					}
					Console::print(to_string(frameIdx) + ": " + addr2LineOutput);
				} else {
					Console::println(to_string(frameIdx) + ": " + string(RTTI::demangle(_functionName)) + " at " + fileName + ":" + to_string(line));
				}
			#else
				Console::println(to_string(frameIdx) + ": " + functionName + " at " + fileName + ":" + to_string(line));
			#endif
			frameIdx++;
		}

		SymCleanup(process);

		mutex.unlock();

		Console::println();

		// shutdown console
		Console::forceShutdown();

		//
		return EXCEPTION_EXECUTE_HANDLER;
	}
#endif

constexpr int32_t Application::FPS;
Application::ApplicationShutdown Application::applicationShutdown;
Application* Application::application = nullptr;
InputEventHandler* Application::inputEventHandler = nullptr;
int64_t Application::timeLast = -1L;

Application::ApplicationShutdown::~ApplicationShutdown() {
	if (Application::application != nullptr) {
		Console::println("Application::ApplicationShutdown::~ApplicationShutdown(): Shutting down application");
		Application::application->dispose();
		delete Application::application;
		Application::application = nullptr;
	}
}

Application::Application() {
	Application::application = this;
	installExceptionHandler();
}

Application::~Application() {
}

void Application::setInputEventHandler(InputEventHandler* inputEventHandler) {
	Application::inputEventHandler = inputEventHandler;
}

int32_t Application::getWindowXPosition() const {
	return windowXPosition;
}

void Application::setWindowXPosition(int32_t windowXPosition) {
	this->windowXPosition = windowXPosition;
}

int32_t Application::getWindowYPosition() const {
	return windowYPosition;
}

void Application::setWindowYPosition(int32_t windowYPosition) {
	this->windowYPosition = windowYPosition;
}

int32_t Application::getWindowWidth() const {
	return windowWidth;
}

void Application::setWindowWidth(int32_t windowWidth) {
	this->windowWidth = windowWidth;
	if (initialized == true) glutReshapeWindow(windowWidth, windowHeight);
}

int32_t Application::getWindowHeight() const {
	return windowHeight;
}

void Application::setWindowHeight(int32_t windowHeight) {
	this->windowHeight = windowHeight;
	if (initialized == true) glutReshapeWindow(windowWidth, windowHeight);
}

bool Application::isFullScreen() const {
	return fullScreen;
}

void Application::setFullScreen(bool fullScreen) {
	this->fullScreen = fullScreen;
	if (initialized == true) {
		if (fullScreen == true) {
			glutFullScreen();
		} else {
			glutPositionWindow(windowXPosition, windowYPosition);
			glutReshapeWindow(windowWidth, windowHeight);
		}
	}
}

void Application::installExceptionHandler() {
	#if defined(_WIN32)
		SetUnhandledExceptionFilter(windowsExceptionHandler);
	#endif
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

void Application::run(int argc, char** argv, const string& title, InputEventHandler* inputEventHandler) {
	Application::inputEventHandler = inputEventHandler;
	glutInit(&argc, argv);
#if defined(__APPLE__)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
#elif ((defined(__linux__) || defined(__FreeBSD__) || defined(__NetBSD__)) && !defined(__arm__) && !defined(__aarch64__)) || defined(_WIN32)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowXPosition, windowYPosition);
	glutCreateWindow((title).c_str());
	if (fullScreen == true) {
		#if defined(_WIN32) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__linux__)
			glutFullScreen();
		#endif
	}
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
