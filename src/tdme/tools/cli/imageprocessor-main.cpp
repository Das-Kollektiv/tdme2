#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/textures/PNGTextureWriter.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::application::Application;
using tdme::engine::fileio::textures::PNGTextureWriter;
using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::Version;
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

		// for now: do black pixel -> transparent pixels, every other pixel gets white
		//	later we can provide color transform matrices with preset matrices
		auto bytesPerPixel = image->getRGBDepthBitsPerPixel() / 8;
		auto imageTextureData = image->getRGBTextureData();
		for (auto y = 0; y < image->getTextureHeight(); y++) {
			for (auto x = 0; x < image->getTextureWidth(); x++) {
				auto offset = y * bytesPerPixel * image->getTextureWidth() + x * bytesPerPixel;
				auto red = imageTextureData.get(offset + 0);
				auto green = imageTextureData.get(offset + 1);
				auto blue = imageTextureData.get(offset + 2);
				auto alpha = bytesPerPixel == 4?imageTextureData.get(offset + 3):0xff;
				// transform black pixels to transparent pixels
				if (red < 5 && green < 5 && blue < 5) {
					alpha = 0;
				} else {
					// everything else should be white
					red = 0xff;
					green = 0xff;
					blue = 0xff;
				}
				imageTextureData.getBuffer()[offset + 0] = red;
				imageTextureData.getBuffer()[offset + 1] = green;
				imageTextureData.getBuffer()[offset + 2] = blue;
				if (bytesPerPixel == 4) {
					imageTextureData.getBuffer()[offset + 3] = alpha;
				}

			}
		}
		// write back to image
		image->setTextureData(Texture::getRGBFormatByPixelBitsPerPixel(image->getRGBDepthBitsPerPixel()), imageTextureData);

		// smooth
		auto smoothedTexture = TextureReader::smooth(image);
		image->releaseReference();
		image = smoothedTexture;

		//
		Console::println("Saving image: " + outputImageFileName);
		PNGTextureWriter::write(
			image,
			FileSystem::getInstance()->getPathName(outputImageFileName),
			FileSystem::getInstance()->getFileName(outputImageFileName),
			false,
			false
		);

		//
		image->releaseReference();
	} catch (Exception& exception) {
		Console::println("An error occurred: " + string(exception.what()));
	}

	//
	Console::shutdown();
	return 0;
}
