#include <tdme/tools/editor/misc/GenerateImposterLOD.h>

#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/TMWriter.h>
#include <tdme/engine/fileio/textures/PNGTextureWriter.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/LODObject.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/SimplePartition.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/ModelTools.h>

using tdme::tools::editor::misc::GenerateImposterLOD;

using std::string;
using std::unique_ptr;
using std::vector;

using tdme::engine::fileio::models::TMWriter;
using tdme::engine::fileio::textures::PNGTextureWriter;
using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::model::UpVector;
using tdme::engine::Engine;
using tdme::engine::LODObject;
using tdme::engine::Object;
using tdme::engine::SimplePartition;
using tdme::math::Math;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::tools::editor::misc::Tools;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::ModelTools;

void GenerateImposterLOD::generate(
	Model* model,
	const string& pathName,
	const string& fileName,
	int billboardCount,
	vector<string>& imposterModelFileNames,
	vector<Model*>& imposterModels
) {
	auto osEngine = unique_ptr<Engine>(Engine::createOffScreenInstance(4096, 4096, true, true, false));
	osEngine->setPartition(new SimplePartition());
	osEngine->setSceneColor(Color4(0.0f, 0.0f, 0.0f, 0.0f));
	//
	auto light = osEngine->getLightAt(0);
	light->setAmbient(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setDiffuse(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	light->setSpecular(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setPosition(Vector4(0.0f, 20000.0f, 0.0f, 0.0f));
	light->setSpotDirection(Vector3(0.0f, 0.0f, 0.0f).sub(Vector3(light->getPosition().getX(), light->getPosition().getY(), light->getPosition().getZ())));
	light->setConstantAttenuation(0.5f);
	light->setLinearAttenuation(0.0f);
	light->setQuadraticAttenuation(0.0f);
	light->setSpotExponent(0.0f);
	light->setSpotCutOff(180.0f);
	light->setEnabled(true);
	// do a feasible scale
	auto boundingBox = model->getBoundingBox();
	float maxAxisDimension = Tools::computeMaxAxisDimension(boundingBox);
	if (maxAxisDimension < Math::EPSILON) maxAxisDimension = 1.0f;

	//
	auto camera = osEngine->getCamera();
	camera->setLookAt(boundingBox->getCenter());
	camera->setLookFrom(boundingBox->getCenter().clone().add(Vector3(0.0f, 0.0f, boundingBox->getCenter().getZ() + maxAxisDimension * 1.25f)));

	//
	auto entity = new Object("model", model);
	entity->addRotation(Vector3(0.0f, 1.0f, 0.0f), 0.0f);
	osEngine->addEntity(entity);

	//
	imposterModels.resize(billboardCount);
	imposterModelFileNames.resize(billboardCount);

	//
	for (auto i = 0; i < billboardCount; i++) {
		//
		auto yRotation = static_cast<float>(i) * (360.0f / static_cast<float>(billboardCount));
		entity->setRotationAngle(0, static_cast<float>(yRotation));
		entity->update();

		//
		osEngine->display();
		//
		auto modelId = Tools::removeFileExtension(fileName) + "-y" + to_string(static_cast<int>(yRotation)) + "deg";
		auto modelFileName = modelId + ".tm";
		auto textureFileName = Tools::removeFileExtension(fileName) + "-y" + to_string(static_cast<int>(yRotation)) + "deg.png";
		osEngine->makeScreenshot(pathName, textureFileName, false);

		//
		auto minX = 10000;
		auto maxX = -1;
		auto minY = 10000;
		auto maxY = -1;
		auto texture = unique_ptr<Texture, decltype([](Texture* texture){ texture->releaseReference(); })>(TextureReader::read(pathName, textureFileName, false, false));
		auto textureTextureData = texture->getRGBTextureData();
		for (auto y = 0; y < texture->getTextureHeight(); y++) {
			for (auto x = 0; x < texture->getTextureWidth(); x++) {
				auto alpha = textureTextureData.get(y * texture->getTextureWidth() * 4 + x * 4 + 3);
				if (alpha < 5) continue;
				minX = Math::min(minX, x);
				maxX = Math::max(maxX, x);
				minY = Math::min(minY, y);
				maxY = Math::max(maxY, y);
			}
		}

		// crop texture
		auto croppedTextureWidth = maxX - minX;
		auto croppedTextureHeight = maxY - minY;
		auto croppedTextureByteBuffer = ByteBuffer(croppedTextureWidth * croppedTextureHeight * 4);
		for (auto y = minY; y < maxY; y++) {
			for (auto x = minX; x < maxX; x++) {
				auto pixelOffset = y * texture->getTextureWidth() * 4 + x * 4;
				auto red = textureTextureData.get(pixelOffset + 0);
				auto green = textureTextureData.get(pixelOffset + 1);
				auto blue = textureTextureData.get(pixelOffset + 2);
				auto alpha = textureTextureData.get(pixelOffset + 3);
				croppedTextureByteBuffer.put(red);
				croppedTextureByteBuffer.put(green);
				croppedTextureByteBuffer.put(blue);
				croppedTextureByteBuffer.put(alpha);
			}
		}

		//
		{
			auto croppedTexture =
				unique_ptr<
					Texture,
					decltype([](Texture* texture){ texture->releaseReference(); })
				>(
					new Texture(
						"tdme.engine.croppedtexture",
						Texture::TEXTUREDEPTH_RGBA,
						Texture::TEXTUREFORMAT_RGBA,
						croppedTextureWidth,
						croppedTextureHeight,
						croppedTextureWidth,
						croppedTextureHeight,
						Texture::TEXTUREFORMAT_RGBA,
						croppedTextureByteBuffer
					)
				);
			croppedTexture->acquireReference();
			auto scaledTexture = unique_ptr<Texture, decltype([](Texture* texture){ texture->releaseReference(); })>(TextureReader::scale(croppedTexture.get(), 1024, 1024));
			// save
			PNGTextureWriter::write(scaledTexture.get(), pathName, textureFileName, false, false);
		}

		// create model
		auto left = boundingBox->getMin().getX();
		auto right = boundingBox->getMax().getX();
		auto top = boundingBox->getMin().getY();
		auto bottom = boundingBox->getMax().getY();
		auto depth = boundingBox->getCenter().getZ();
		//
		auto billboard = make_unique<Model>(modelId, modelId, UpVector::Y_UP, RotationOrder::ZYX, nullptr);
		//
		auto billboardMaterial = make_unique<Material>("billboard");
		billboardMaterial->setSpecularMaterialProperties(make_unique<SpecularMaterialProperties>().release());
		billboardMaterial->getSpecularMaterialProperties()->setSpecularColor(Color4(0.0f, 0.0f, 0.0f, 1.0f));
		billboardMaterial->getSpecularMaterialProperties()->setDiffuseTexture(pathName, textureFileName);
		billboardMaterial->getSpecularMaterialProperties()->setDiffuseTextureMaskedTransparency(true);
		//
		auto billboardNode = make_unique<Node>(billboard.get(), nullptr, "billboard", "billboard");
		vector<Vector3> billboardVertices;
		billboardVertices.emplace_back(left, top, depth);
		billboardVertices.emplace_back(left, bottom, depth);
		billboardVertices.emplace_back(right, bottom, depth);
		billboardVertices.emplace_back(right, top, depth);
		vector<Vector3> billboardNormals;
		billboardNormals.emplace_back(0.0f, 1.0f, 0.0f);
		vector<Vector2> billboardTextureCoordinates;
		billboardTextureCoordinates.emplace_back(0.0f, 1.0f);
		billboardTextureCoordinates.emplace_back(0.0f, 0.0f);
		billboardTextureCoordinates.emplace_back(1.0f, 0.0f);
		billboardTextureCoordinates.emplace_back(1.0f, 1.0f);
		vector<Face> billboardFacesGround;
		billboardFacesGround.emplace_back(billboardNode.get(), 0, 1, 2, 0, 0, 0, 0, 1, 2);
		billboardFacesGround.emplace_back(billboardNode.get(), 2, 3, 0, 0, 0, 0, 2, 3, 0);
		FacesEntity billboardNodeFacesEntity(billboardNode.get(), "billboard.facesentity");
		billboardNodeFacesEntity.setMaterial(billboardMaterial.get());
		vector<FacesEntity> billboardNodeFacesEntities;
		billboardNodeFacesEntity.setFaces(billboardFacesGround);
		billboardNodeFacesEntities.push_back(billboardNodeFacesEntity);
		billboardNode->setVertices(billboardVertices);
		billboardNode->setNormals(billboardNormals);
		billboardNode->setTextureCoordinates(billboardTextureCoordinates);
		billboardNode->setFacesEntities(billboardNodeFacesEntities);
		billboard->getNodes()["billboard"] = billboardNode.get();
		billboard->getSubNodes()["billboard"] = billboardNode.get();
		billboardNode.release();
		//
		billboard->getMaterials()[billboardMaterial->getId()] = billboardMaterial.get();
		billboardMaterial.release();
		//
		ModelTools::prepareForIndexedRendering(billboard.get());

		//
		TMWriter::write(
			billboard.get(),
			pathName,
			modelFileName
		);

		//
		imposterModels[i] = billboard.release();
		imposterModelFileNames[i] = (pathName.empty() == false?pathName + "/":"") + modelFileName;
	}

	//
	osEngine->dispose();
}
