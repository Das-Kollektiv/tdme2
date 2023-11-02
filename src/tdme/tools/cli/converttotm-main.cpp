#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/PBRMaterialProperties.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::unique_ptr;

using tdme::application::Application;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::models::TMWriter;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::PBRMaterialProperties;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::Engine;
using tdme::engine::Texture;
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
 * Convert to tm application
 * @author andreas.drewke
 */
class ConvertToTMApplication final
	: public virtual Application
{
private:
	vector<string> modelFileNames;
	bool useBC7TextureCompression { true };

public:
	// forbid class copy
	FORBID_CLASS_COPY(ConvertToTMApplication)

	/**
	 * Public constructor
	 * @param modelFileNames model file names
	 */
	ConvertToTMApplication(bool useBC7TextureCompression, const vector<string>& modelFileNames):
		useBC7TextureCompression(useBC7TextureCompression),
		modelFileNames(modelFileNames) {
	}

	/**
	 * Public denstructor
	 */
	~ConvertToTMApplication() {
	}

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 * @return exit code
	 */
	inline static int main(int argc, char** argv) {
		auto useBC7TextureCompression = true;
		vector<string> modelFileNames;
		for (auto i = 1; i < argc; i++) {
			string argumentValue = argv[i];
			if (argumentValue == "--no-texture-compression") {
				useBC7TextureCompression = false;
				continue;
			}
			modelFileNames.push_back(argumentValue);
		}
		auto convertToTMApplication = new ConvertToTMApplication(useBC7TextureCompression, modelFileNames);
		return convertToTMApplication->run(argc, argv, "Convert to tm Application", nullptr, Application::WINDOW_HINT_INVISIBLE);
	}

	// overridden methods
	void display() override {
		Console::println("Exporting models: Using BC7 texture compression: " + string(useBC7TextureCompression == true?"true":"false"));
		try {
			//
			auto scaleTo = 1024.0f;
			//
			for (const auto& inputFileName: modelFileNames) {
				auto outputFileName = StringTools::substring(inputFileName, 0, inputFileName.rfind('.')) + ".tm";
				try {
					Console::println("Loading model: " + inputFileName);
					auto model = unique_ptr<Model>(
						ModelReader::read(
							FileSystem::getInstance()->getPathName(inputFileName),
							FileSystem::getInstance()->getFileName(inputFileName),
							useBC7TextureCompression
						)
					);
					for (const auto& [materialId, material]: model->getMaterials()) {
						auto specularMaterialProperties = material->getSpecularMaterialProperties();
						// specular material
						if (specularMaterialProperties != nullptr) {
							// diffuse texture
							{
								auto texture = specularMaterialProperties->getDiffuseTexture();
								if (texture != nullptr) {
									auto widthScale = scaleTo / texture->getTextureWidth();
									auto heightScale = scaleTo / texture->getTextureHeight();
									auto scale = Math::min(widthScale, heightScale);
									if (scale < 1.0f) {
										auto scaledTexture = TextureReader::scale(texture, texture->getTextureWidth() * scale, texture->getTextureHeight() * scale, string());
										specularMaterialProperties->setDiffuseTexture(scaledTexture);
										scaledTexture->releaseReference();
									}
								}
							}
							// spec texture
							{
								auto texture = specularMaterialProperties->getSpecularTexture();
								if (texture != nullptr) {
									auto widthScale = scaleTo / texture->getTextureWidth();
									auto heightScale = scaleTo / texture->getTextureHeight();
									auto scale = Math::min(widthScale, heightScale);
									if (scale < 1.0f) {
										auto scaledTexture = TextureReader::scale(texture, texture->getTextureWidth() * scale, texture->getTextureHeight() * scale, string());
										specularMaterialProperties->setSpecularTexture(scaledTexture);
										scaledTexture->releaseReference();
									}
								}
							}
							// normal texture
							{
								auto texture = specularMaterialProperties->getNormalTexture();
								if (texture != nullptr) {
									auto widthScale = scaleTo / texture->getTextureWidth();
									auto heightScale = scaleTo / texture->getTextureHeight();
									auto scale = Math::min(widthScale, heightScale);
									if (scale < 1.0f) {
										auto scaledTexture = TextureReader::scale(texture, texture->getTextureWidth() * scale, texture->getTextureHeight() * scale, string());
										specularMaterialProperties->setNormalTexture(scaledTexture);
										scaledTexture->releaseReference();
									}
								}
							}
						}
						//
						auto pbrMaterialProperties = material->getPBRMaterialProperties();
						// pbr material
						if (pbrMaterialProperties != nullptr) {
							// base texture
							{
								auto texture = pbrMaterialProperties->getBaseColorTexture();
								if (texture != nullptr) {
									auto widthScale = scaleTo / texture->getTextureWidth();
									auto heightScale = scaleTo / texture->getTextureHeight();
									auto scale = Math::min(widthScale, heightScale);
									if (scale < 1.0f) {
										auto scaledTexture = TextureReader::scale(texture, texture->getTextureWidth() * scale, texture->getTextureHeight() * scale, string());
										pbrMaterialProperties->setBaseColorTexture(scaledTexture);
										scaledTexture->releaseReference();
									}
								}
							}
							// metallic roughness texture
							{
								auto texture = pbrMaterialProperties->getMetallicRoughnessTexture();
								if (texture != nullptr) {
									auto widthScale = scaleTo / texture->getTextureWidth();
									auto heightScale = scaleTo / texture->getTextureHeight();
									auto scale = Math::min(widthScale, heightScale);
									if (scale < 1.0f) {
										auto scaledTexture = TextureReader::scale(texture, texture->getTextureWidth() * scale, texture->getTextureHeight() * scale, string());
										pbrMaterialProperties->setMetallicRoughnessTexture(scaledTexture);
										scaledTexture->releaseReference();
									}
								}
							}
							// normal texture
							{
								auto texture = pbrMaterialProperties->getNormalTexture();
								if (texture != nullptr) {
									auto widthScale = scaleTo / texture->getTextureWidth();
									auto heightScale = scaleTo / texture->getTextureHeight();
									auto scale = Math::min(widthScale, heightScale);
									if (scale < 1.0f) {
										auto scaledTexture = TextureReader::scale(texture, texture->getTextureWidth() * scale, texture->getTextureHeight() * scale, string());
										pbrMaterialProperties->setNormalTexture(scaledTexture);
										scaledTexture->releaseReference();
									}
								}
							}
						}
					}
					//
					Console::println("Exporting model: " + outputFileName);
					TMWriter::write(
						model.get(),
						FileSystem::getInstance()->getPathName(outputFileName),
						FileSystem::getInstance()->getFileName(outputFileName),
						useBC7TextureCompression
					);
				} catch (Exception& exception) {
					Console::println("An error occurred: " + string(exception.what()));
				}
			}
		} catch (Exception& exception) {
			Console::println("An error occurred: " + string(exception.what()));
		}
		Application::exit(0);
	}

	void dispose() override {
		Engine::getInstance()->dispose();
	}

	void initialize() override {
		Engine::getInstance()->initialize();
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
	Console::println(string("converttotm ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();
	if (argc < 2) {
		Console::println("Usage: converttotm [--no-texture-compression] inputfile1 [inputfileN]");
		Application::exit(Application::EXITCODE_FAILURE);
	}
	return tdme::tools::cli::ConvertToTMApplication::main(argc, argv);
}
