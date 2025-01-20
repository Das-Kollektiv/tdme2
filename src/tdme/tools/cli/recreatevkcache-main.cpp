#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using tdme::application::Application;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;

namespace tdme {
namespace tools {
namespace cli {

/**
 * Delete VK cache
 * @author andreas.drewke
 */
class RecreateVKCacheApplication final: public Application
{
public:
	// forbid class copy
	FORBID_CLASS_COPY(RecreateVKCacheApplication)

	/**
	 * Public constructor
	 */
	RecreateVKCacheApplication() {
	}

	/**
	 * Public denstructor
	 */
	~RecreateVKCacheApplication() {
	}

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 * @returns exit code
	 */
	inline static int main(int argc, char** argv) {
		auto recreateVKCacheApplication = new RecreateVKCacheApplication();
		return recreateVKCacheApplication->run(argc, argv, "Recreate VK cache Application", nullptr, Application::WINDOW_HINT_INVISIBLE);
	}

	// overridden methods
	void display() override {
		Application::exit(0);
	}

	void dispose() override {
		Engine::getInstance()->dispose();
	}

	void initialize() override {
		Engine::getInstance()->initialize();
		if (Engine::getInstance()->getGraphicsRendererBackendType() != RendererBackend::RENDERERTYPE_VULKAN) {
			Console::printLine("Note: recreatevkcache does not run with --vulkan, Vulkan shader cache can not get created. Exiting.");
			Application::exit(0);
		}
	}

	void reshape(int32_t width, int32_t height) override {
		Engine::getInstance()->reshape(width, height);
	}
};

};
};
};

int main(int argc, char** argv)
{
	Console::printLine(string("recreatevkcache ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	//
	Console::printLine("Deleting shader/vk path");
	try {
		FileSystem::getInstance()->removePath("shader/vk", true);
	} catch (Exception& exception) {
		Console::printLine(string() + "An error occurred: " + exception.what());
	}
	try {
		if (FileSystem::getInstance()->exists("shader/vk") == false) {
			FileSystem::getInstance()->createPath("shader/vk");
		}
	} catch (Exception& exception) {
		Console::printLine(string() + "An error occurred: " + exception.what());
	}
	Console::printLine("Creating shader/vk shader cache");
	tdme::tools::cli::RecreateVKCacheApplication::main(argc, argv);
	Console::printLine("Done");

	//
	Application::exit(Application::EXITCODE_SUCCESS);
}
