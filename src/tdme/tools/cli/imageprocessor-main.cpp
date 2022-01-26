#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Version.h>
#include <tdme/engine/fileio/textures/PNGTextureWriter.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::application::Application;
using tdme::engine::Version;
using tdme::engine::fileio::textures::PNGTextureWriter;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;

int main(int argc, char** argv)
{
	Console::println(string("imageprocessor ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	if (argc != 3) {
		Console::println("Usage: imageprocessor input.png output.png");
		Application::exit(1);
	}

	//
	auto inputImageFileName = string(argv[1]);
	auto outputImageFileName = string(argv[2]);

	//
	try {
		Console::println("Loading image: " + inputImageFileName);
		auto image = TextureReader::read(
			FileSystem::getInstance()->getPathName(inputImageFileName),
			FileSystem::getInstance()->getFileName(inputImageFileName)
		);

		//
		Console::println("Processing image");
		// todo: processing

		//
		Console::println("Saving image: " + outputImageFileName);
		PNGTextureWriter::write(
			image,
			FileSystem::getInstance()->getPathName(outputImageFileName),
			FileSystem::getInstance()->getFileName(outputImageFileName)
		);
	} catch (Exception& exception) {
		Console::println("An error occurred: " + string(exception.what()));
	}
}
