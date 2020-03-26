#if defined(VULKAN)
	#define GLFW_INCLUDE_VULKAN
	#include <GLFW/glfw3.h>
#elif defined(GLFW3)
	#if ((defined(__linux__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)) && !defined(GLES2)) || defined(_WIN32) || defined(__HAIKU__)
		#define GLEW_NO_GLU
		#include <GL/glew.h>
		#if defined(_WIN32)
			#include <GL/wglew.h>
		#endif
	#endif
	#include <GLFW/glfw3.h>
#else
	#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__linux__)
		#include <GL/freeglut.h>
	#elif defined(__APPLE__)
		#include <GLUT/glut.h>
	#elif defined(_WIN32)
		#include <GL/freeglut.h>
	#elif defined(__HAIKU__)
		#include <GL/glut.h>
	#endif
#endif

#if defined(_WIN32)
	#include <windows.h>
	#include <dbghelp.h>
	#include <stdio.h>
	#include <string.h>
	#include <tdme/os/threading/Mutex.h>
#endif

#if defined(__APPLE__) && !defined(VULKAN) && !defined(GLFW3)
	#include <Carbon/Carbon.h>
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
#include <tdme/utils/Character.h>
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
using tdme::utils::Character;
using tdme::utils::Console;
using tdme::utils::HexEncDec;
using tdme::utils::RTTI;
using tdme::utils::StringTokenizer;
using tdme::utils::StringUtils;
using tdme::utils::Time;

string Application::execute(const string& command) {
	// see: https://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
	array<char, 128> buffer;
	string result;
	#if defined(_MSC_VER)
		shared_ptr<FILE> pipe(_popen(command.c_str(), "r"), _pclose);
	#else
		shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
	#endif
	if (!pipe) throw std::runtime_error("popen() failed!");
	while (!feof(pipe.get())) {
		if (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
			result += buffer.data();
	}
	return result;
}

void Application::executeBackground(const string& command) {
	#if defined(_WIN32)
		system(("start " + command).c_str());
	#else
		system((command + " </dev/null &>/dev/null &").c_str());
	#endif
}

void Application::exit(int exitCode) {
	::exit(exitCode);
}

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

		vector<string> backtraceLines;
		auto backtraceHeaderLine = "windowsExceptionHandler(): process " + to_string((uint64_t)process) + " crashed: Printing stacktrace(thread " + to_string((uint64_t)thread) + ")";
		Console::println(backtraceHeaderLine);
		backtraceLines.push_back(backtraceHeaderLine);

		CHAR _pathToExecutable[MAX_PATH];
		GetModuleFileName(GetModuleHandleW(NULL), _pathToExecutable, MAX_PATH);
		string pathToExecutable = _pathToExecutable;

		#if defined(_MSC_VER) == false
			auto addr2lineToolCmd = StringUtils::substring(pathToExecutable, 0, StringUtils::lastIndexOf(pathToExecutable, '\\')) + "\\addr2line.exe";
			if (FileSystem::getInstance()->fileExists(addr2lineToolCmd) == false) {
				Console::println("handler(): " + addr2lineToolCmd + ": not found! Please copy addr2line utility to binary location!");
				mutex.unlock();

				//
				Console::println();

				// shutdown console
				Console::shutdown();

				//
				return EXCEPTION_EXECUTE_HANDLER;
			}
			addr2lineToolCmd = "\"" + StringUtils::replace(addr2lineToolCmd, "\\", "\\\\") + "\"";
		#endif

		auto backtraceExecutableLine = "windowsExceptionHandler(): path to executable: " + pathToExecutable;
		Console::println(backtraceExecutableLine);
		backtraceLines.push_back(backtraceExecutableLine);

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

		// construct backtrace and save it to console.log and crash.log
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
					auto addr2LineOutput = Application::execute(addr2LineCommand);
					StringTokenizer t;
					t.tokenize(addr2LineOutput, " ");
					if (t.hasMoreTokens() == true) {
						auto addr2lineFunctionName = t.nextToken();
						addr2LineOutput = StringUtils::replace(StringUtils::replace(addr2LineOutput, addr2lineFunctionName, RTTI::demangle(addr2lineFunctionName.c_str())), "\n", "");
					}
					auto backtraceLine = to_string(frameIdx) + ": " + addr2LineOutput;
					Console::println(backtraceLine);
					backtraceLines.push_back(backtraceLine);
				} else {
					auto backtraceLine = to_string(frameIdx) + ": " + string(RTTI::demangle(_functionName)) + " at " + fileName + ":" + to_string(line);
					Console::println(backtraceLine);
					backtraceLines.push_back(backtraceLine);
				}
			#else
				Console::println(to_string(frameIdx) + ": " + functionName + " at " + fileName + ":" + to_string(line));
			#endif
			frameIdx++;
		}

		// store also to crash.log
		FileSystem::getInstance()->setContentFromStringArray(".", "crash.log", backtraceLines);

		SymCleanup(process);

		mutex.unlock();

		Console::println();

		// shutdown console
		Console::shutdown();

		//
		return EXCEPTION_EXECUTE_HANDLER;
	}
#endif

Application::ApplicationShutdown Application::applicationShutdown;
Application* Application::application = nullptr;
InputEventHandler* Application::inputEventHandler = nullptr;
int64_t Application::timeLast = -1L;
bool Application::limitFPS = false;

#if defined(VULKAN) || defined(GLFW3)
	GLFWwindow* Application::glfwWindow = nullptr;
	array<uint32_t, 10> Application::glfwButtonDownFrames;
	int Application::glfwMods = 0;
	bool Application::capsLockEnabled = false;
#endif

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

void Application::setVSyncEnabled(bool vSync) {
	#if defined(VULKAN) || defined(GLFW3)
		// not yet
	#else
		#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__linux__)
			// TODO: a.drewke: vsync
			// glXSwapIntervalEXT(vSync == true?1:0);
		#elif defined(_WIN32)
			wglSwapIntervalEXT(vSync == true?1:0);
		#endif
	#endif
}

string Application::getOSName() {
	#if defined(__FreeBSD__)
		return "FreeBSD";
	#elif defined(__HAIKU__)
		return "Haiku";
	#elif defined(__linux__)
		return "Linux";
	#elif defined(__APPLE__)
		return "MacOSX";
	#elif defined(__NetBSD__)
		return "NetBSD";
	#elif defined(__OpenBSD__)
		return "OpenBSD";
	#elif defined(_MSC_VER)
		return "Windows-MSC";
	#elif defined(_WIN32)
		return "Windows-MINGW";
	#else
		return "Unknown";
	#endif
}

string Application::getCPUName() {
	#if defined(__amd64__) || defined(_M_X64)
		return "x64";
	#elif defined(__ia64__) || defined(_M_IA64)
		return "ia64";
	#elif defined(__aarch64__)
		return "arm64";
	#elif defined(__arm__) || defined(_M_ARM)
		return "arm";
	#elif defined(__powerpc64__)
		return "ppc64";
	#elif defined(__powerpc__)
		return "ppc";
	#else
		return "Unknown";
	#endif
}

void Application::setInputEventHandler(InputEventHandler* inputEventHandler) {
	Application::inputEventHandler = inputEventHandler;
}

bool Application::isActive() {
	#if defined(_WIN32)
		return GetActiveWindow() == GetForegroundWindow();
	#else
		return true;
	#endif
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
	if (initialized == true) {
		#if defined(VULKAN) || defined(GLFW3)
			glfwSetWindowSize(glfwWindow, windowWidth, windowHeight);
		#else
			glutReshapeWindow(windowWidth, windowHeight);
		#endif
	}
}

int32_t Application::getWindowHeight() const {
	return windowHeight;
}

void Application::setWindowHeight(int32_t windowHeight) {
	this->windowHeight = windowHeight;
	if (initialized == true) {
		#if defined(VULKAN) || defined(GLFW3)
			glfwSetWindowSize(glfwWindow, windowWidth, windowHeight);
		#else
			glutReshapeWindow(windowWidth, windowHeight);
		#endif
	}
}

bool Application::isFullScreen() const {
	return fullScreen;
}

void Application::setFullScreen(bool fullScreen) {
	this->fullScreen = fullScreen;
	#if defined(VULKAN) || defined(GLFW3)
		auto windowMonitor = glfwGetWindowMonitor(glfwWindow);
		if (windowMonitor == nullptr && fullScreen == true) {
			auto monitor = glfwGetPrimaryMonitor();
			auto mode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(glfwWindow, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		} else
		if (windowMonitor != nullptr && fullScreen == false) {
			glfwSetWindowMonitor(glfwWindow, NULL, windowXPosition, windowYPosition, windowWidth, windowHeight, 0);
		}
	#else
		if (fullScreen == true) {
			glutFullScreen();
		} else {
			glutPositionWindow(windowXPosition, windowYPosition);
			glutReshapeWindow(windowWidth, windowHeight);
		}
	#endif
}

void Application::installExceptionHandler() {
	#if defined(_WIN32)
		SetUnhandledExceptionFilter(windowsExceptionHandler);
	#endif
}

void Application::setMouseCursor(int mouseCursor) {
	#if defined(VULKAN) || defined(GLFW3)
		if (mouseCursor == MOUSE_CURSOR_DISABLED) {
			glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		} else
		if (mouseCursor == MOUSE_CURSOR_ENABLED) {
			glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	#else
		glutSetCursor(mouseCursor);
	#endif
}

void Application::setMousePosition(int x, int y) {
	#if defined(VULKAN) || defined(GLFW3)
		glfwSetCursorPos(glfwWindow, x, y);
	#else
		#if defined(__APPLE__)
			CGPoint point;
			point.x = glutGet((GLenum)GLUT_WINDOW_X) + x;
			point.y = glutGet((GLenum)GLUT_WINDOW_Y) + y;
			CGWarpMouseCursorPosition(point);
			CGAssociateMouseAndMouseCursorPosition(true);
		#else
			glutWarpPointer(x, y);
		#endif
	#endif
}

void Application::swapBuffers() {
	#if defined(VULKAN) || defined(GLFW3)
	#else
		glutSwapBuffers();
	#endif
}

#if defined(VULKAN) || defined(GLFW3)
	static void glfwErrorCallback(int error, const char* description) {
		Console::println(string("glfwErrorCallback(): ") + description);
	}
#endif

void Application::run(int argc, char** argv, const string& title, InputEventHandler* inputEventHandler) {
	this->title = title;
	Application::inputEventHandler = inputEventHandler;
	#if defined(VULKAN) || defined(GLFW3)
		glfwSetErrorCallback(glfwErrorCallback);
		if (glfwInit() == false) {
			Console::println("glflInit(): failed!");
			return;
		}
		#if defined(VULKAN)
			if (glfwVulkanSupported() == false) {
				Console::println("glfwVulkanSupported(): Vulkan not available!");
				return;
			}
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		#else
				array<array<int, 3>, 3> glVersions = {{ {{1, 4, 3}}, {{1, 3, 2}}, {{0, 3,1}} }};
				glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
				auto i = 0;
				for (auto& glVersion: glVersions) {
					glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, glVersion[0] == 1?GLFW_TRUE:GLFW_FALSE);
					glfwWindowHint(GLFW_OPENGL_PROFILE, glVersion[0] == 1?GLFW_OPENGL_CORE_PROFILE:GLFW_OPENGL_ANY_PROFILE);
					glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glVersion[1]);
					glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glVersion[2]);
					glfwWindow = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), NULL, NULL);
					if (glfwWindow != nullptr) break;
				}
		#endif
		if (glfwWindow == nullptr) {
			Console::println("glfwCreateWindow(): Could not create window");
			glfwTerminate();
			return;
		}
		glfwSetWindowPos(glfwWindow, windowXPosition, windowYPosition);
		setFullScreen(fullScreen);
		#if !defined(VULKAN)
			glfwMakeContextCurrent(glfwWindow);
			#if defined(_WIN32) || ((defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__linux__)) && !defined(GLES2)) || defined(__HAIKU__)
				glewExperimental = true;
				GLenum glewInitStatus = glewInit();
				if (glewInitStatus != GLEW_OK) {
					Console::println("glewInit(): Error: " + (string((char*)glewGetErrorString(glewInitStatus))));
					Application::exit(1);
				}
			#endif
		#endif
		glfwSetCharCallback(glfwWindow, Application::glfwOnChar);
		glfwSetKeyCallback(glfwWindow, Application::glfwOnKey);
		glfwSetCursorPosCallback(glfwWindow, Application::glfwOnMouseMoved);
		glfwSetMouseButtonCallback(glfwWindow, Application::glfwOnMouseButton);
		glfwSetScrollCallback(glfwWindow, Application::glfwOnMouseWheel);
		glfwSetWindowSizeCallback(glfwWindow, Application::glfwOnWindowResize);
		while (glfwWindowShouldClose(glfwWindow) == false) {
			displayInternal();
			#if !defined(VULKAN)
				glfwSwapBuffers(glfwWindow);
			#endif
			glfwPollEvents();
		}
		glfwTerminate();
	#else
		glutInit(&argc, argv);
		#if defined(__APPLE__)
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
		#elif ((defined(__linux__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)) && !defined(GLES2)) || defined(_WIN32)
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
			glutInitContextProfile(GLUT_CORE_PROFILE);
			/*
			glutInitContextVersion(3, 1);
			glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
			*/
		#elif defined(__linux__) && defined(GLES2)
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
			glutInitContextVersion(2,0);
		#elif defined(__HAIKU__)
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
		#endif
		glutInitWindowSize(windowWidth, windowHeight);
		glutInitWindowPosition(windowXPosition, windowYPosition);
		glutCreateWindow(title.c_str());
		setFullScreen(fullScreen);
		#if defined(_WIN32) || ((defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__linux__)) && !defined(GLES2)) || defined(__HAIKU__)
			glewExperimental = true;
			GLenum glewInitStatus = glewInit();
			if (glewInitStatus != GLEW_OK) {
				Console::println("glewInit(): Error: " + (string((char*)glewGetErrorString(glewInitStatus))));
				Application::exit(1);
			}
		#endif
		#if defined(_WIN32)
			setIcon("resources/win32/app.ico");
		#endif
		// glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
		glutReshapeFunc(Application::reshapeInternal);
		glutDisplayFunc(Application::displayInternal);
		glutIdleFunc(Application::displayInternal);
		glutIgnoreKeyRepeat(true);
		glutKeyboardFunc(Application::glutOnKeyDown);
		glutKeyboardUpFunc(Application::glutOnKeyUp);
		glutSpecialFunc(Application::glutOnSpecialKeyDown);
		glutSpecialUpFunc(Application::glutOnSpecialKeyUp);
		glutMotionFunc(Application::glutOnMouseDragged);
		glutPassiveMotionFunc(Application::glutOnMouseMoved);
		glutMouseFunc(Application::glutOnMouseButton);
		#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__linux__) || defined(_WIN32)
			glutMouseWheelFunc(Application::glutOnMouseWheel);
		#endif
		glutMainLoop();
	#endif
}

void Application::setIcon(const string& fileName) {
	// https://stackoverflow.com/questions/12748103/how-to-change-freeglut-main-window-icon-in-c
	#if defined(_WIN32)
		HWND hwnd = FindWindow(NULL, title.c_str());
		HANDLE icon = LoadImage(GetModuleHandle(nullptr), fileName.c_str(), IMAGE_ICON, 256, 256, LR_LOADFROMFILE | LR_COLOR);
		SendMessage(hwnd, (UINT)WM_SETICON, ICON_BIG, (LPARAM)icon);
	#endif
}

void Application::displayInternal() {
	if (Application::application->initialized == false) {
		Application::application->initialize();
		#if defined(VULKAN) || defined(GLFW3)
			Application::application->reshape(Application::application->windowWidth, Application::application->windowHeight);
		#endif
		Application::application->initialized = true;
	}
	int64_t timeNow = Time::getCurrentMillis();
	int64_t timeFrame = 1000/Application::FPS;
	if (Application::timeLast != -1L) {
		#if !defined(VULKAN) || defined(GLFW3)
			int64_t timePassed = timeNow - timeLast;
			if (limitFPS == true && timePassed < timeFrame) Thread::sleep(timeFrame - timePassed);
		#endif
	}
	Application::timeLast = timeNow;
	Application::application->display();
	#if defined(VULKAN) || defined(GLFW3)
	#else
		glutSwapBuffers();
	#endif
}

void Application::reshapeInternal(int32_t width, int32_t height) {
	if (Application::application->initialized == false) {
		Application::application->initialize();
		Application::application->initialized = true;
	}
	Application::application->reshape(width, height);
}

#if defined(VULKAN) || defined(GLFW3)

	void Application::glfwOnChar(GLFWwindow* window, unsigned int key) {
		if (Application::inputEventHandler == nullptr) return;
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		Application::inputEventHandler->onChar(key, (int)mouseX, (int)mouseY);
	}

	bool Application::glfwIsSpecialKey(int key) {
		return
			key == GLFW_KEY_UP ||
			key == GLFW_KEY_DOWN ||
			key == GLFW_KEY_LEFT ||
			key == GLFW_KEY_RIGHT ||
			key == GLFW_KEY_TAB ||
			key == GLFW_KEY_BACKSPACE ||
			key == GLFW_KEY_ENTER ||
			key == GLFW_KEY_DELETE ||
			key == GLFW_KEY_HOME ||
			key == GLFW_KEY_END ||
			key == GLFW_KEY_ESCAPE ||
			key == GLFW_KEY_LEFT_SHIFT ||
			key == GLFW_KEY_LEFT_CONTROL ||
			key == GLFW_KEY_LEFT_ALT ||
			key == GLFW_KEY_LEFT_SUPER ||
			key == GLFW_KEY_RIGHT_SHIFT ||
			key == GLFW_KEY_RIGHT_CONTROL ||
			key == GLFW_KEY_RIGHT_ALT ||
			key == GLFW_KEY_RIGHT_SUPER;
	}

	void Application::glfwOnKey(GLFWwindow* window, int key, int scanCode, int action, int mods) {
		if (Application::inputEventHandler == nullptr) return;
		glfwMods = mods;
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		// TODO: Use GLFW_MOD_CAPS_LOCK, which does not seem to be available with my version, need to update perhabs
		if (key == GLFW_KEY_CAPS_LOCK) {
			if (action == GLFW_PRESS) {
				capsLockEnabled = capsLockEnabled == false?true:false;
			}
		}
		if (glfwIsSpecialKey(key) == true) {
			if (action == GLFW_PRESS || action == GLFW_REPEAT) {
				Application::inputEventHandler->onSpecialKeyDown(key, (int)mouseX, (int)mouseY);
			} else
			if (action == GLFW_RELEASE) {
				Application::inputEventHandler->onSpecialKeyUp(key, (int)mouseX, (int)mouseY);
			}
		} else {
			if (action == GLFW_PRESS || action == GLFW_REPEAT) {
				auto keyName = key == GLFW_KEY_SPACE?" ":glfwGetKeyName(key, scanCode);
				if (keyName != nullptr) {
					Application::inputEventHandler->onKeyDown(
						(mods & GLFW_MOD_SHIFT) == 0 && capsLockEnabled == false?Character::toLowerCase(keyName[0]):keyName[0],
						(int)mouseX,
						(int)mouseY
					);
				}
			} else
			if (action == GLFW_RELEASE) {
				auto keyName = key == GLFW_KEY_SPACE?" ":glfwGetKeyName(key, scanCode);
				if (keyName != nullptr) {
					Application::inputEventHandler->onKeyUp(
						(mods & GLFW_MOD_SHIFT) == 0 && capsLockEnabled == false?Character::toLowerCase(keyName[0]):keyName[0],
						(int)mouseX,
						(int)mouseY
					);
				}
			}
		}
	}

	void Application::glfwOnMouseMoved(GLFWwindow* window, double x, double y) {
		if (Application::inputEventHandler == nullptr) return;
		if (glfwButtonDownFrames[0] > 0) {
			Application::inputEventHandler->onMouseDragged((int)x, (int)y);
		} else {
			Application::inputEventHandler->onMouseMoved((int)x, (int)y);
		}
	}

	void Application::glfwOnMouseButton(GLFWwindow* window, int button, int action, int mods) {
		if (Application::inputEventHandler == nullptr) return;
		glfwMods = mods;
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		Application::inputEventHandler->onMouseButton(button, action == GLFW_PRESS?MOUSE_BUTTON_DOWN:MOUSE_BUTTON_UP, (int)mouseX, (int)mouseY);
		if (action == GLFW_PRESS) {
			glfwButtonDownFrames[button]++;
		} else {
			glfwButtonDownFrames[button] = 0;
		}
	}
	void Application::glfwOnMouseWheel(GLFWwindow* window, double x, double y) {
		if (Application::inputEventHandler == nullptr) return;
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		if (x != 0.0) Application::inputEventHandler->onMouseWheel(0, (int)x, (int)mouseX, (int)mouseY);
		if (y != 0.0) Application::inputEventHandler->onMouseWheel(1, (int)y, (int)mouseX, (int)mouseY);
	}

	void Application::glfwOnWindowResize(GLFWwindow* window, int width, int height) {
		Application::reshapeInternal(width, height);
	}

#else
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
		if (button == 3) {
			#if !defined(_MSC_VER)
				Application::inputEventHandler->onMouseWheel(3, 1, x, y);
			#endif
			return;
		} else
		if (button == 4) {
			#if !defined(_MSC_VER)
				Application::inputEventHandler->onMouseWheel(4, -1, x, y);
			#endif
			return;
		}
		Application::inputEventHandler->onMouseButton(button, state, x, y);
	}

	void Application::glutOnMouseWheel(int button, int direction, int x, int y) {
		if (Application::inputEventHandler == nullptr) return;
		Application::inputEventHandler->onMouseWheel(button, direction, x, y);
	}
#endif
