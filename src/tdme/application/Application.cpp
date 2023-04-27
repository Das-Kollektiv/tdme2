#if defined(_MSC_VER)
	// this suppresses a warning redefinition of APIENTRY macro
	#define NOMINMAX
	#include <windows.h>
#endif
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#if defined(_WIN32)
	#define GLFW_EXPOSE_NATIVE_WIN32
	#include <GLFW/glfw3native.h>
#endif

#if defined(_WIN32)
	#include <windows.h>
	#include <dbghelp.h>
	#include <stdio.h>
	#include <string.h>
	#include <tdme/os/threading/Mutex.h>
#endif

#if defined(__APPLE__)
	#include <Carbon/Carbon.h>
#endif

#if !defined(_MSC_VER)
	#include <dlfcn.h>
#endif

#include <stdlib.h>

#include <array>
#include <clocale>
#include <memory>
#include <string>

#include <tdme/tdme.h>

#include <tdme/application/Application.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Hex.h>
#include <tdme/utilities/RTTI.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::array;
using std::shared_ptr;
using std::string;
using std::to_string;

using tdme::application::Application;
using tdme::application::InputEventHandler;
using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::os::threading::Thread;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::utilities::Hex;
using tdme::utilities::RTTI;
using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

Renderer* Application::renderer = nullptr;
Application* Application::application = nullptr;
InputEventHandler* Application::inputEventHandler = nullptr;
int64_t Application::timeLast = -1L;
bool Application::limitFPS = true;

GLFWwindow* Application::glfwWindow = nullptr;
array<unsigned int, 10> Application::glfwMouseButtonDownFrames;
int Application::glfwMouseButtonLast = -1;
bool Application::glfwCapsLockEnabled = false;
GLFWcursor* Application::glfwHandCursor = nullptr;

int Application::mouseCursor = MOUSE_CURSOR_ENABLED;

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

void Application::openBrowser(const string& url) {
	#if defined(_WIN32)
		execute("explorer \"" + url + "\"");
	#elif defined(__APPLE__) || defined(__HAIKU__)
		execute("open \"" + url + "\"");
	#else
		execute("xdg-open \"" + url + "\"");
	#endif
}

void Application::cancelExit() {
	glfwSetWindowShouldClose(glfwWindow, GLFW_FALSE);
}

void Application::exit(int exitCode) {
	if (Application::application == nullptr) {
		::exit(exitCode);
	} else {
		if (Application::application->initialized == false) {
			::exit(exitCode);
		} else {
			Application::application->exitCode = exitCode;
			glfwSetWindowShouldClose(glfwWindow, GLFW_TRUE);
		}
	}
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
			auto addr2lineToolCmd = StringTools::substring(pathToExecutable, 0, StringTools::lastIndexOf(pathToExecutable, '\\')) + "\\addr2line.exe";
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
			addr2lineToolCmd = "\"" + StringTools::replace(addr2lineToolCmd, "\\", "\\\\") + "\"";
		#endif

		auto backtraceExecutableLine = "windowsExceptionHandler(): path to executable: " + pathToExecutable;
		Console::println(backtraceExecutableLine);
		backtraceLines.push_back(backtraceExecutableLine);

		pathToExecutable = string("\"") + StringTools::replace(pathToExecutable, "\\", "\\\\") + "\"";

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
					Hex::encodeInt(stackFrame.AddrPC.Offset, hexAddr);
					string addr2LineCommand = "\"" + addr2lineToolCmd + " -f -p -e " + string(pathToExecutable) + " " + hexAddr + "\"";
					auto addr2LineOutput = Application::execute(addr2LineCommand);
					StringTokenizer t;
					t.tokenize(addr2LineOutput, " ");
					if (t.hasMoreTokens() == true) {
						auto addr2lineFunctionName = t.nextToken();
						addr2LineOutput = StringTools::replace(StringTools::replace(addr2LineOutput, addr2lineFunctionName, RTTI::demangle(addr2lineFunctionName.c_str())), "\n", "");
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

Application::Application() {
	Application::application = this;
	installExceptionHandler();
}

Application::~Application() {
}

void Application::setVSyncEnabled(bool vSync) {
	Engine::renderer->setVSync(vSync);
	if (Engine::renderer->getRendererType() != Renderer::RENDERERTYPE_VULKAN) {
		glfwSwapInterval(vSync == true?1:0);
	}
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

void Application::setLocale(const string& locale) {
	setlocale(LC_ALL, locale.c_str());
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

int Application::getWindowXPosition() {
	if (glfwWindow != nullptr) glfwGetWindowPos(glfwWindow, &windowXPosition, &windowYPosition);
	return windowXPosition;
}

void Application::setWindowXPosition(int windowXPosition) {
	if (glfwWindow != nullptr) glfwSetWindowPos(glfwWindow, windowXPosition, windowYPosition);
	this->windowXPosition = windowXPosition;
}

int Application::getWindowYPosition() {
	if (glfwWindow != nullptr) glfwGetWindowPos(glfwWindow, &windowXPosition, &windowYPosition);
	return windowYPosition;
}

void Application::setWindowYPosition(int windowYPosition) {
	if (glfwWindow != nullptr) glfwSetWindowPos(glfwWindow, windowXPosition, windowYPosition);
	this->windowYPosition = windowYPosition;
}

int Application::getWindowWidth() const {
	return windowWidth;
}

void Application::setWindowWidth(int windowWidth) {
	this->windowWidth = windowWidth;
	if (initialized == true) {
		if (fullScreen == false) glfwSetWindowSize(glfwWindow, windowWidth, windowHeight);
	}
}

int Application::getWindowHeight() const {
	return windowHeight;
}

void Application::setWindowHeight(int windowHeight) {
	this->windowHeight = windowHeight;
	if (initialized == true) {
		if (fullScreen == false) glfwSetWindowSize(glfwWindow, windowWidth, windowHeight);
	}
}

bool Application::isFullScreen() const {
	return fullScreen;
}

void Application::setFullScreen(bool fullScreen) {
	this->fullScreen = fullScreen;
	if (initialized == true) {
		auto windowMonitor = glfwGetWindowMonitor(glfwWindow);
		if (windowMonitor == nullptr && fullScreen == true) {
			auto monitor = glfwGetPrimaryMonitor();
			auto mode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(glfwWindow, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		} else
		if (windowMonitor != nullptr && fullScreen == false) {
			glfwSetWindowMonitor(glfwWindow, NULL, windowXPosition, windowYPosition, windowWidth, windowHeight, 0);
			if ((windowHints & WINDOW_HINT_MAXIMIZED) == WINDOW_HINT_MAXIMIZED) {
				glfwSetWindowPos(glfwWindow, windowXPosition, windowYPosition);
				glfwGetWindowSize(glfwWindow, &windowWidth, &windowHeight);
				glfwOnWindowResize(glfwWindow, windowWidth, windowHeight);
			}
		}
	}
}

void Application::installExceptionHandler() {
	#if defined(_WIN32)
		SetUnhandledExceptionFilter(windowsExceptionHandler);
	#endif
}

void Application::setMouseCursor(int mouseCursor) {
	if (mouseCursor == MOUSE_CURSOR_DISABLED) {
		glfwSetCursor(glfwWindow, nullptr);
		glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	} else
	if (mouseCursor == MOUSE_CURSOR_ENABLED) {
		glfwSetCursor(glfwWindow, nullptr);
		glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else
	if (mouseCursor == MOUSE_CURSOR_HAND) {
		glfwSetCursor(glfwWindow, glfwHandCursor);
		glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	Application::mouseCursor = mouseCursor;
}

int Application::getMousePositionX() {
	double mouseX, mouseY;
	glfwGetCursorPos(glfwWindow, &mouseX, &mouseY);
	return static_cast<int>(mouseX);
}

int Application::getMousePositionY() {
	double mouseX, mouseY;
	glfwGetCursorPos(glfwWindow, &mouseX, &mouseY);
	return static_cast<int>(mouseY);
}

void Application::setMousePosition(int x, int y) {
	#if defined(__APPLE__)
		int windowXPos, windowYPos;
		glfwGetWindowPos(Application::glfwWindow, &windowXPos, &windowYPos);
		CGPoint point;
		point.x = windowXPos + x;
		point.y = windowYPos + y;
		CGWarpMouseCursorPosition(point);
		CGAssociateMouseAndMouseCursorPosition(true);
	#else
		glfwSetCursorPos(glfwWindow, x, y);
	#endif
}

void Application::swapBuffers() {
	if (Engine::renderer->getRendererType() != Renderer::RENDERERTYPE_VULKAN) glfwSwapBuffers(glfwWindow);
}

string Application::getClipboardContent() {
	return string(glfwGetClipboardString(glfwWindow));
}

void Application::setClipboardContent(const string& content) {
	glfwSetClipboardString(glfwWindow, content.c_str());
}

static void glfwErrorCallback(int error, const char* description) {
	Console::println(string("glfwErrorCallback(): ") + description);
}

void Application::run(int argc, char** argv, const string& title, InputEventHandler* inputEventHandler, int windowHints) {
	string rendererLibrary = "libopengl3corerenderer";
	for (auto i = 1; i < argc; i++) {
		auto argValue = string(argv[i]);
		if (argValue == "--debug") debuggingEnabled = true; else
		if (argValue == "--gles2") rendererLibrary = "libopengles2renderer"; else
		if (argValue == "--gl2") rendererLibrary = "libopengl2renderer"; else
		if (argValue == "--gl3core") rendererLibrary = "libopengl3corerenderer"; else
		if (argValue == "--vulkan") rendererLibrary = "libvulkanrenderer";
	}

	#if defined(_WIN32)
		rendererLibrary = rendererLibrary + ".dll";
	#elif defined(__APPLE__)
		rendererLibrary = rendererLibrary + ".dylib";
	#else
		rendererLibrary = rendererLibrary + ".so";
	#endif

	//
	this->title = title;
	this->windowHints = windowHints;
	executableFileName = FileSystem::getInstance()->getFileName(argv[0]);
	Application::inputEventHandler = inputEventHandler;
	glfwSetErrorCallback(glfwErrorCallback);
	if (glfwInit() == false) {
		Console::println("glflInit(): failed!");
		return;
	}

	// TODO: dispose
	Application::glfwHandCursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);

	// determine window position of not yet done
	if (windowXPosition == -1 || windowYPosition == -1) {
		// have some random position if position determination does fail
		windowXPosition = 100;
		windowYPosition = 100;
		// otherwise center application window on primary monitor
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* monitorMode = glfwGetVideoMode(monitor);
		if (monitorMode != nullptr) {
			int monitorX = -1;
			int monitorY = -1;
			glfwGetMonitorPos(monitor, &monitorX, &monitorY);
			windowXPosition = monitorX + (monitorMode->width - windowWidth) / 2;
			windowYPosition = monitorY + (monitorMode->height - windowHeight) / 2;
		}
	}

	Console::println("Application::run(): Opening renderer library: " + rendererLibrary);

	// load renderer library
	#if defined(_MSC_VER)
		//
		auto rendererLibraryHandle = LoadLibrary(rendererLibrary.c_str());
		if (rendererLibraryHandle == nullptr) {
			Console::println("Application::run(): Could not open renderer library");
			glfwTerminate();
			return;
		}
		//
		Renderer* (*rendererCreateInstance)() = (Renderer*(*)())GetProcAddress(rendererLibraryHandle, "createInstance");
		//
		if (rendererCreateInstance == nullptr) {
			Console::println("Application::run(): Could not find renderer library createInstance() entry point");
			glfwTerminate();
			return;
		}
		//
		renderer = (Renderer*)rendererCreateInstance();
		if (renderer == nullptr) {
			Console::println("Application::run(): Could not create renderer");
			glfwTerminate();
			return;
		}
	#else
		//
		#if defined(__HAIKU__)
			auto rendererLibraryHandle = dlopen(("lib/" + rendererLibrary).c_str(), RTLD_NOW);
		#else
			auto rendererLibraryHandle = dlopen(rendererLibrary.c_str(), RTLD_NOW);
		#endif
		if (rendererLibraryHandle == nullptr) {
			Console::println("Application::run(): Could not open renderer library");
			glfwTerminate();
			return;
		}
		//
		Renderer* (*rendererCreateInstance)() = (Renderer*(*)())dlsym(rendererLibraryHandle, "createInstance");
		//
		if (rendererCreateInstance == nullptr) {
			Console::println("Application::run(): Could not find renderer library createInstance() entry point");
			glfwTerminate();
			return;
		}
		//
		renderer = (Renderer*)rendererCreateInstance();
		if (renderer == nullptr) {
			Console::println("Application::run(): Could not create renderer");
			glfwTerminate();
			return;
		}
	#endif

	// window hints
	if ((windowHints & WINDOW_HINT_NOTRESIZEABLE) == WINDOW_HINT_NOTRESIZEABLE) glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	if ((windowHints & WINDOW_HINT_NOTDECORATED) == WINDOW_HINT_NOTDECORATED) glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	if ((windowHints & WINDOW_HINT_INVISIBLE) == WINDOW_HINT_INVISIBLE) glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	if ((windowHints & WINDOW_HINT_MAXIMIZED) == WINDOW_HINT_MAXIMIZED) glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	//
	for (auto i = 0; renderer->prepareWindowSystemRendererContext(i) == true; i++) {
		glfwWindow = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), NULL, NULL);
		if (glfwWindow != nullptr) break;
	}

	//
	if (glfwWindow == nullptr) {
		Console::println("glfwCreateWindow(): Could not create window");
		glfwTerminate();
		return;
	}

	//
	if (renderer->initializeWindowSystemRendererContext(glfwWindow) == false) {
		Console::println("glfwCreateWindow(): Could not initialize window system renderer context");
		glfwTerminate();
		return;
	}

	//
	if ((windowHints & WINDOW_HINT_MAXIMIZED) == 0) glfwSetWindowPos(glfwWindow, windowXPosition, windowYPosition);

	//
	setIcon();

	//
	glfwSetCharCallback(glfwWindow, Application::glfwOnChar);
	glfwSetKeyCallback(glfwWindow, Application::glfwOnKey);
	glfwSetCursorPosCallback(glfwWindow, Application::glfwOnMouseMoved);
	glfwSetMouseButtonCallback(glfwWindow, Application::glfwOnMouseButton);
	glfwSetScrollCallback(glfwWindow, Application::glfwOnMouseWheel);
	glfwSetWindowSizeCallback(glfwWindow, Application::glfwOnWindowResize);
	glfwSetWindowCloseCallback(glfwWindow, Application::glfwOnClose);
	glfwSetDropCallback(glfwWindow, glfwOnDrop);
	if ((windowHints & WINDOW_HINT_MAXIMIZED) == WINDOW_HINT_MAXIMIZED) {
		glfwGetWindowPos(glfwWindow, &windowXPosition, &windowYPosition);
		glfwGetWindowSize(glfwWindow, &windowWidth, &windowHeight);
		glfwOnWindowResize(glfwWindow, windowWidth, windowHeight);
	}
	#if defined(__APPLE__)
		// change working directory on MacOSX if started from app bundle
		auto executablePathName = string(argv[0]);
		if (executablePathName.find(".app/Contents/MacOS/") != string::npos) {
			auto appBundleName = StringTools::substring(executablePathName, 0, executablePathName.rfind(".app") + string(".app").size());
			auto workingPathName = StringTools::substring(appBundleName, 0, appBundleName.rfind('/'));
			FileSystem::getStandardFileSystem()->changePath(workingPathName);
		}
	#endif
	while (glfwWindowShouldClose(glfwWindow) == false) {
		displayInternal();
		if (Engine::renderer->getRendererType() != Renderer::RENDERERTYPE_VULKAN) glfwSwapBuffers(glfwWindow);
		glfwPollEvents();
	}
	glfwTerminate();
	if (Application::application != nullptr) {
		Console::println("Application::run(): Shutting down application");
		Application::application->dispose();
		delete Application::application;
		Application::application = nullptr;
	}
	if (exitCode != 0) ::exit(exitCode);
}

void Application::setIcon() {
	auto logoFileName = StringTools::replace(StringTools::toLowerCase(executableFileName), ".exe", "") + "-icon.png";
	if (FileSystem::getInstance()->fileExists("resources/platforms/icons/" + logoFileName) == false) logoFileName = "default-icon.png";
	auto texture = TextureReader::read("resources/platforms/icons", logoFileName, false, false);
	if (texture != nullptr) {
		auto textureData = texture->getRGBTextureData();
		auto textureWidth = texture->getTextureWidth();
		auto textureHeight = texture->getTextureHeight();
		auto textureBytePerPixel = texture->getRGBDepthBitsPerPixel() == 32?4:3;
		auto glfwPixels = new uint8_t[textureWidth * textureHeight * 4];
		for (auto y = 0; y < textureHeight; y++)
		for (auto x = 0; x < textureWidth; x++) {
			glfwPixels[y * textureWidth * 4 + x * 4 + 0] = textureData.get(y * textureWidth * textureBytePerPixel + x * textureBytePerPixel + 0);
			glfwPixels[y * textureWidth * 4 + x * 4 + 1] = textureData.get(y * textureWidth * textureBytePerPixel + x * textureBytePerPixel + 1);
			glfwPixels[y * textureWidth * 4 + x * 4 + 2] = textureData.get(y * textureWidth * textureBytePerPixel + x * textureBytePerPixel + 2);
			glfwPixels[y * textureWidth * 4 + x * 4 + 3] = textureBytePerPixel == 3?255:textureData.get(y * textureWidth * textureBytePerPixel + x * textureBytePerPixel + 3);
		}
		GLFWimage glfwIcon;
		glfwIcon.width = texture->getTextureWidth();
		glfwIcon.height = texture->getTextureHeight();
		glfwIcon.pixels = glfwPixels;
		glfwSetWindowIcon(glfwWindow, 1, &glfwIcon);
		texture->releaseReference();
		delete [] glfwPixels;
	}
}

void Application::displayInternal() {
	if (Application::application->initialized == false) {
		Application::application->initialize();
		Application::application->reshape(Application::application->windowWidth, Application::application->windowHeight);
		Application::application->initialized = true;
		Application::application->setFullScreen(Application::application->fullScreen);
	}
	int64_t timeNow = Time::getCurrentMillis();
	int64_t timeFrame = 1000/Application::FPS;
	if (Application::timeLast != -1L) {
		int64_t timePassed = timeNow - timeLast;
		if (limitFPS == true && timePassed < timeFrame) Thread::sleep(timeFrame - timePassed);
	}
	Application::timeLast = timeNow;
	Application::application->display();
}

void Application::reshapeInternal(int width, int height) {
	if (Application::application->initialized == false) {
		Application::application->initialize();
		Application::application->initialized = true;
	}
	Application::application->reshape(width, height);
}

void Application::glfwOnChar(GLFWwindow* window, unsigned int key) {
	if (Application::inputEventHandler == nullptr) return;
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	Application::inputEventHandler->onChar(key, (int)mouseX, (int)mouseY);
}

void Application::glfwOnKey(GLFWwindow* window, int key, int scanCode, int action, int mods) {
	if (Application::inputEventHandler == nullptr) return;
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	// TODO: Use GLFW_MOD_CAPS_LOCK, which does not seem to be available with my version, need to update perhabs
	if (key == GLFW_KEY_CAPS_LOCK) {
		if (action == GLFW_PRESS) {
			glfwCapsLockEnabled = glfwCapsLockEnabled == false?true:false;
		}
	}
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		auto keyName = key == GLFW_KEY_SPACE?" ":glfwGetKeyName(key, scanCode);
		Application::inputEventHandler->onKeyDown(
			keyName == nullptr?-1:((mods & GLFW_MOD_SHIFT) == 0 && glfwCapsLockEnabled == false?Character::toLowerCase(keyName[0]):keyName[0]),
			key,
			(int)mouseX,
			(int)mouseY,
			action == GLFW_REPEAT,
			mods
		);
	} else
	if (action == GLFW_RELEASE) {
		auto keyName = key == GLFW_KEY_SPACE?" ":glfwGetKeyName(key, scanCode);
		Application::inputEventHandler->onKeyUp(
			keyName == nullptr?-1:((mods & GLFW_MOD_SHIFT) == 0 && glfwCapsLockEnabled == false?Character::toLowerCase(keyName[0]):keyName[0]),
			key,
			(int)mouseX,
			(int)mouseY
		);
	}
}

void Application::glfwOnMouseMoved(GLFWwindow* window, double x, double y) {
	if (Application::inputEventHandler == nullptr) return;
	if (glfwMouseButtonLast != -1 && glfwMouseButtonDownFrames[glfwMouseButtonLast] > 0) {
		Application::inputEventHandler->onMouseDragged((int)x, (int)y);
	} else {
		Application::inputEventHandler->onMouseMoved((int)x, (int)y);
	}
}

void Application::glfwOnMouseButton(GLFWwindow* window, int button, int action, int mods) {
	if (Application::inputEventHandler == nullptr) return;
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	Application::inputEventHandler->onMouseButton(button, action == GLFW_PRESS?MOUSE_BUTTON_DOWN:MOUSE_BUTTON_UP, (int)mouseX, (int)mouseY);
	if (action == GLFW_PRESS) {
		glfwMouseButtonDownFrames[button]++;
	} else {
		glfwMouseButtonDownFrames[button] = 0;
	}
	glfwMouseButtonLast = action == MOUSE_BUTTON_DOWN?button:-1;
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

void Application::glfwOnClose(GLFWwindow* window) {
	Application::application->onClose();
}

void Application::glfwOnDrop(GLFWwindow* window, int count, const char** paths) {
	Console::println("Application::glfwOnDrop(): " + to_string(count) + " items have been dropped");
	vector<string> pathsVector;
	for (auto i = 0; i < count; i++) {
		Console::println("\t" + string(paths[i]));
		pathsVector.push_back(paths[i]);
	}
	Application::application->onDrop(pathsVector);
}

void Application::onClose() {
}

void Application::onDrop(const vector<string>& paths) {
}
