#include <tdme/engine/fileio/models/GLTFReader.h>

#include <map>
#include <set>
#include <string>
#include <vector>

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <ext/libpng/png.h>
#include <ext/tinygltf/tiny_gltf.h>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/PBRMaterialProperties.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/ShaderModel.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/utilities/StringTools.h>

using std::map;
using std::set;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::fileio::models::GLTFReader;

using tdme::engine::Texture;
using tdme::engine::model::Animation;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::PBRMaterialProperties;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::ShaderModel;
using tdme::engine::model::Skinning;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::model::UpVector;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::ModelTools;
using tdme::utilities::StringTools;

Model* GLTFReader::read(const string& pathName, const string& fileName, bool useBC7TextureCompression)
{
	// hello
	Console::println("GLTFReader::read(): Loading model: " + pathName + "/" + fileName);

	// parse model
	string err;
	string warn;
	tinygltf::Model gltfModel;
	tinygltf::TinyGLTF gltfLoader;
	auto success = false;
	if (StringTools::endsWith(fileName, ".glb") == true) {
		vector<uint8_t> glftBinaryData;
		FileSystem::getInstance()->getContent(pathName, fileName, glftBinaryData);
		success = gltfLoader.LoadBinaryFromMemory(&gltfModel, &err, &warn, glftBinaryData.data(), glftBinaryData.size());
	} else
	if (StringTools::endsWith(fileName, ".gltf") == true) {
		string glftASCIIData = FileSystem::getInstance()->getContentAsString(pathName, fileName);
		success = gltfLoader.LoadASCIIFromString(&gltfModel, &err, &warn, glftASCIIData.c_str(), glftASCIIData.size(), pathName.c_str());
	} else {
		Console::println("GLTFReader::read(): File not supported");
		return nullptr;
	}

	if (warn.empty() == false) Console::println("GLTFReader::read(): warnings: " + warn);
	if (err.empty() == false) Console::println("GLTFReader::read(): errors: " + err);
	if (success == false){
		Console::println("GLTFReader::read(): Failed to load model: " + pathName + "/" + fileName);
		return nullptr;
	}

	// 	create model
	auto model = new Model(
		fileName,
		fileName,
		UpVector::Y_UP,
		RotationOrder::ZYX,
		nullptr,
		model::Model::AUTHORINGTOOL_UNKNOWN
	);
	model->setShaderModel(ShaderModel::SPECULARPBR);
	model->setEmbedSpecularTextures(true);
	model->setEmbedPBRTextures(true);

	// parse nodes aka scene
	int anonymousNodeIdx = 1;
	for (auto& gltfScene: gltfModel.scenes) {
		for (auto gltfNodeIdx: gltfScene.nodes) {
			auto& glTfNode = gltfModel.nodes[gltfNodeIdx];
			auto node = parseNode(pathName, gltfModel, gltfNodeIdx, model, nullptr, anonymousNodeIdx, useBC7TextureCompression);
			model->getNodes()[node->getId()] = node;
			if (model->getSubNodes().find(node->getId()) != model->getSubNodes().end()) {
				Console::println("GLTFReader::read(): node already exists: " + node->getId());
			}
			model->getSubNodes()[node->getId()] = node;
			if (glTfNode.children.empty() == false) parseNodeChildren(pathName, gltfModel, glTfNode.children, node, anonymousNodeIdx, useBC7TextureCompression);
		}
	}

	// animations
	auto maxFrames = 0;
	{
		set<string> animationNodes;
		map<string, vector<Matrix4x4>> animationScaleMatrices;
		map<string, vector<Matrix4x4>> animationRotationMatrices;
		map<string, vector<Matrix4x4>> animationTranslationMatrices;
		for (auto& gltfAnimation: gltfModel.animations) {
			auto frames = 0;
			for (auto& gltfChannel: gltfAnimation.channels) {
				auto gltfNodeName = gltfModel.nodes[gltfChannel.target_node].name;
				auto node = model->getNodeById(gltfNodeName);
				if (node == nullptr) {
					Console::println("GLTFReader::read(): '" + gltfNodeName + "': animation: " + gltfAnimation.name + ": Could not find animation node");
					continue;
				}
				animationNodes.insert(node->getId());
				auto& gltfSample = gltfAnimation.samplers[gltfChannel.sampler];
				// animation input: key frame time stamps
				auto& animationInputAccessor = gltfModel.accessors[gltfSample.input];
				auto& animationInputBufferView = gltfModel.bufferViews[animationInputAccessor.bufferView];
				auto& animationInputBuffer = gltfModel.buffers[animationInputBufferView.buffer];
				auto animationInputBufferData = (const float*)(animationInputBuffer.data.data() + animationInputAccessor.byteOffset + animationInputBufferView.byteOffset);
				if (animationInputAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
					Console::println("GLTFReader::read(): " + node->getId() + ": animation: " + gltfAnimation.name + ": Invalid input attributes component: " + getComponentTypeString(animationInputAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(animationInputAccessor.componentType)));
					continue;
				}
				auto channelFrames = Math::max(1, static_cast<int32_t>(Math::ceil(animationInputBufferData[animationInputAccessor.count - 1] * 30.0f)));
				// animation output: translation, rotation, scale
				auto& animationOutputAccessor = gltfModel.accessors[gltfSample.output];
				auto& animationOutputBufferView = gltfModel.bufferViews[animationOutputAccessor.bufferView];
				auto& animationOutputBuffer = gltfModel.buffers[animationOutputBufferView.buffer];
				auto animationOutputBufferData = (const float*)(animationOutputBuffer.data.data() + animationOutputAccessor.byteOffset + animationOutputBufferView.byteOffset);
				if (animationOutputAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
					Console::println("GLTFReader::read(): " + node->getId() + ": animation: " + gltfAnimation.name + ": Invalid output attributes component: " + getComponentTypeString(animationOutputAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(animationOutputAccessor.componentType)));
					continue;
				}
				auto& scaleMatrices = animationScaleMatrices[node->getId()];
				if (maxFrames + channelFrames > scaleMatrices.size()) {
					while (scaleMatrices.size() < maxFrames + channelFrames) scaleMatrices.emplace_back(getNodeScaleMatrix(gltfModel, node->getId()));
				}
				auto& rotationMatrices = animationRotationMatrices[node->getId()];
				if (maxFrames + channelFrames > rotationMatrices.size()) {
					while (rotationMatrices.size() < maxFrames + channelFrames) rotationMatrices.emplace_back(getNodeRotationMatrix(gltfModel, node->getId()));
				}
				auto& translationMatrices = animationTranslationMatrices[node->getId()];
				if (maxFrames + channelFrames > translationMatrices.size()) {
					while (translationMatrices.size() < maxFrames + channelFrames) translationMatrices.emplace_back(getNodeTranslationMatrix(gltfModel, node->getId()));
				}
				if (gltfChannel.target_path == "translation") {
					if (animationOutputAccessor.type != TINYGLTF_TYPE_VEC3) {
						Console::println("GLTFReader::read(): " + node->getId() + ": animation: " + gltfAnimation.name + ": Invalid translation channel output type: " + getTypeString(animationOutputAccessor.type) + ", expected: Vector3");
						continue;
					}
					vector<Matrix4x4> keyFrameMatrices(animationOutputAccessor.count);
					for (auto i = 0; i < animationOutputAccessor.count; i++) {
						keyFrameMatrices[i].identity();
						keyFrameMatrices[i].translate(Vector3(animationOutputBufferData[i * 3 + 0], animationOutputBufferData[i * 3 + 1], animationOutputBufferData[i * 3 + 2]));
					}
					interpolateKeyFrames(animationInputAccessor.count, animationInputBufferData, keyFrameMatrices, channelFrames, translationMatrices, maxFrames);
				} else
				if (gltfChannel.target_path == "rotation") {
					if (animationOutputAccessor.type != TINYGLTF_TYPE_VEC4) {
						Console::println("GLTFReader::read(): " + node->getId() + ": animation: " + gltfAnimation.name + ": Invalid rotation channel output type: " + getTypeString(animationOutputAccessor.type) + ", expected: Vector4");
						continue;
					}
					vector<Matrix4x4> keyFrameMatrices(animationOutputAccessor.count);
					Quaternion rotationQuaternion;
					for (auto i = 0; i < animationOutputAccessor.count; i++) {
						rotationQuaternion.set(animationOutputBufferData[i * 4 + 0], animationOutputBufferData[i * 4 + 1], animationOutputBufferData[i * 4 + 2], animationOutputBufferData[i * 4 + 3]);
						keyFrameMatrices[i] = rotationQuaternion.computeMatrix();
					}
					interpolateKeyFrames(animationInputAccessor.count, animationInputBufferData, keyFrameMatrices, channelFrames, rotationMatrices, maxFrames);
				} else
				if (gltfChannel.target_path == "scale") {
					if (animationOutputAccessor.type != TINYGLTF_TYPE_VEC3) {
						Console::println("GLTFReader::read(): " + node->getId() + ": animation: " + gltfAnimation.name + ": Invalid scale channel output type: " + getTypeString(animationOutputAccessor.type) + ", expected: Vector3");
						continue;
					}
					vector<Matrix4x4> keyFrameMatrices(animationOutputAccessor.count);
					for (auto i = 0; i < animationOutputAccessor.count; i++) {
						keyFrameMatrices[i].identity();
						keyFrameMatrices[i].scale(Vector3(animationOutputBufferData[i * 3 + 0], animationOutputBufferData[i * 3 + 1], animationOutputBufferData[i * 3 + 2]));
					}
					interpolateKeyFrames(animationInputAccessor.count, animationInputBufferData, keyFrameMatrices, channelFrames, scaleMatrices, maxFrames);
				} else {
					Console::println("GLTFReader::GLTFReader(): " + gltfAnimation.name + ": Invalid target path:" + gltfChannel.target_path);
				}
				if (channelFrames > frames) frames = channelFrames;
			}
			model->addAnimationSetup(gltfAnimation.name, maxFrames, maxFrames + frames - 1, false);
			maxFrames+= frames;
		}

		// extend all animation matrices to max frames
		for (auto& it: animationScaleMatrices) {
			auto& nodeId = it.first;
			auto& animationMatrices = it.second;
			while (animationMatrices.size() < maxFrames) animationMatrices.emplace_back(getNodeScaleMatrix(gltfModel, nodeId));
		}
		for (auto& it: animationRotationMatrices) {
			auto& nodeId = it.first;
			auto& animationMatrices = it.second;
			while (animationMatrices.size() < maxFrames) animationMatrices.emplace_back(getNodeRotationMatrix(gltfModel, nodeId));
		}
		for (auto& it: animationTranslationMatrices) {
			auto& nodeId = it.first;
			auto& animationMatrices = it.second;
			while (animationMatrices.size() < maxFrames) animationMatrices.emplace_back(getNodeTranslationMatrix(gltfModel, nodeId));
		}

		// set up nodes animations if we have frames
		for (auto& animationNode: animationNodes) {
			auto node = model->getNodeById(animationNode);
			if (node == nullptr) {
				Console::println("GLTFReader::GLTFReader(): animation: node not found:" + animationNode);
				continue;
			}
			//
			auto& nodeAnimationScaleMatrices = animationScaleMatrices[node->getId()];
			auto& nodeAnimationRotationMatrices = animationRotationMatrices[node->getId()];
			auto& nodeAnimationTranslationMatrices = animationTranslationMatrices[node->getId()];

			//
			vector<Matrix4x4> animationFinalMatrices(maxFrames);
			for (auto i = 0; i < maxFrames; i++) {
				animationFinalMatrices[i].set(nodeAnimationScaleMatrices[i]);
				animationFinalMatrices[i].multiply(nodeAnimationRotationMatrices[i]);
				animationFinalMatrices[i].multiply(nodeAnimationTranslationMatrices[i]);
			}
			auto animation = new Animation();
			animation->setTransformMatrices(animationFinalMatrices);
			node->setAnimation(animation);
		}
	}

	// set up joints
	ModelTools::setupJoints(model);

	// check if to compute normals
	{
		auto computeNormals = false;
		for (auto& nodeIt: model->getNodes()) {
			auto node = nodeIt.second;
			if (node->getVertices().size() != node->getNormals().size()) {
				computeNormals = true;
			}
		}
		if (computeNormals == true) {
			Console::println("GLTFReader::read(): Computing normals, as they were missing or mismatching vertex count");
			ModelTools::computeNormals(model);
		}
	}

	// compute tangents and bitangents
	for (auto& nodeIt: model->getSubNodes()) {
		computeTangentsAndBitangents(nodeIt.second);
	}

	// lets prepare for indexed rendering, or disable it later, as it makes not much sense with tangents and bitangents
	ModelTools::prepareForIndexedRendering(model);

	// create default animations
	ModelTools::createDefaultAnimation(model, maxFrames);

	// fix animation length
	ModelTools::fixAnimationLength(model);

	//
	return model;
}

void GLTFReader::interpolateKeyFrames(int frameTimeCount, const float* frameTimes, const vector<Matrix4x4>& keyFrameMatrices, int interpolatedMatrixCount, vector<Matrix4x4>& interpolatedMatrices, int frameStartIdx) {
	auto keyFrameIdx = 0;
	auto frameIdx = 0;
	auto timeStampLast = frameTimes[keyFrameIdx];
	auto tansformationsMatrixLast = &keyFrameMatrices[keyFrameIdx];
	interpolatedMatrices[frameStartIdx + frameIdx++] = keyFrameMatrices[keyFrameIdx++];
	for (auto i = 1; i < frameTimeCount; i++) {
		auto keyFrameTime = frameTimes[i];
		auto transformMatrixCurrent = &keyFrameMatrices[(keyFrameIdx) % keyFrameMatrices.size()];
		float timeStamp;
		for (timeStamp = timeStampLast; timeStamp < keyFrameTime; timeStamp += 1.0f / 30.0f) {
			if (frameIdx >= interpolatedMatrixCount) {
				// TODO: check me again!
				// Console::println(string("Warning: skipping frame: ") + to_string(frameIdx));
				frameIdx++;
				continue;
			}
			// Console::println("yyy: " + to_string(frameStartIdx +  frameIdx) + ": key frame idx: " + to_string(keyFrameIdx) + ", interpolation t: " + to_string((timeStamp - timeStampLast) / (keyFrameTime - timeStampLast)));
			interpolatedMatrices[frameStartIdx +  frameIdx] = Matrix4x4::interpolateLinear(*tansformationsMatrixLast, *transformMatrixCurrent, (timeStamp - timeStampLast) / (keyFrameTime - timeStampLast));
			frameIdx++;
		}
		timeStampLast = timeStamp;
		tansformationsMatrixLast = transformMatrixCurrent;
		keyFrameIdx++;
	}
}

Node* GLTFReader::parseNode(const string& pathName, tinygltf::Model& gltfModel, int gltfNodeIdx, Model* model, Node* parentNode, int& anonymousNodeIdx, bool useBC7TextureCompression) {
	auto& gltfNode = gltfModel.nodes[gltfNodeIdx];
	// this fixes nodes that have no name
	auto nodeId = gltfNode.name.empty() == true?"<" + to_string(anonymousNodeIdx++) + ">":gltfNode.name;
	gltfNode.name = nodeId;
	//
	auto node = new Node(model, parentNode, nodeId, nodeId);
	if (gltfNode.matrix.size() == 16) {
		node->setTransformMatrix(
			Matrix4x4(
				static_cast<float>(gltfNode.matrix[0]),
				static_cast<float>(gltfNode.matrix[1]),
				static_cast<float>(gltfNode.matrix[2]),
				static_cast<float>(gltfNode.matrix[3]),
				static_cast<float>(gltfNode.matrix[4]),
				static_cast<float>(gltfNode.matrix[5]),
				static_cast<float>(gltfNode.matrix[6]),
				static_cast<float>(gltfNode.matrix[7]),
				static_cast<float>(gltfNode.matrix[8]),
				static_cast<float>(gltfNode.matrix[9]),
				static_cast<float>(gltfNode.matrix[10]),
				static_cast<float>(gltfNode.matrix[11]),
				static_cast<float>(gltfNode.matrix[12]),
				static_cast<float>(gltfNode.matrix[13]),
				static_cast<float>(gltfNode.matrix[14]),
				static_cast<float>(gltfNode.matrix[15])
			)
		);
	} else {
		Matrix4x4 nodeScaleMatrix;
		Matrix4x4 nodeRotationMatrix;
		Matrix4x4 nodeTranslationMatrix;
		nodeScaleMatrix.identity();
		nodeRotationMatrix.identity();
		nodeTranslationMatrix.identity();
		if (gltfNode.scale.size() == 3) {
			nodeScaleMatrix.scale(Vector3(gltfNode.scale[0], gltfNode.scale[1], gltfNode.scale[2]));
		}
		if (gltfNode.rotation.size() == 4) {
			Quaternion rotationQuaternion(gltfNode.rotation[0], gltfNode.rotation[1], gltfNode.rotation[2], gltfNode.rotation[3]);
			nodeRotationMatrix = rotationQuaternion.computeMatrix();
		}
		if (gltfNode.translation.size() == 3) {
			nodeTranslationMatrix.translate(Vector3(gltfNode.translation[0], gltfNode.translation[1], gltfNode.translation[2]));
		}
		Matrix4x4 nodeTransformMatrix;
		nodeTransformMatrix.set(nodeScaleMatrix);
		nodeTransformMatrix.multiply(nodeRotationMatrix);
		nodeTransformMatrix.multiply(nodeTranslationMatrix);
		node->setTransformMatrix(nodeTransformMatrix);
	}
	if (gltfNode.mesh == -1) return node;
	vector<int> joints;
	vector<float> weights;
	vector<Vector3> vertices;
	vector<Vector3> normals;
	vector<TextureCoordinate> textureCoordinates;
	vector<FacesEntity> facesEntities;
	auto& mesh = gltfModel.meshes[gltfNode.mesh];
	int facesEntityIdx = 0;
	for (auto& gltfPrimitive: mesh.primitives) {
		Material* material = nullptr;
		if (gltfPrimitive.material != -1) {
			auto& gltfMaterial = gltfModel.materials[gltfPrimitive.material];
			auto& gltfMaterialName = gltfMaterial.name;
			auto materialIt = model->getMaterials().find(gltfMaterialName);
			if (materialIt != model->getMaterials().end()) {
				material = materialIt->second;
			} else {
				material = new Material(gltfMaterial.name);
				material->setDoubleSided(false/*TODO: enable me: gltfMaterial.doubleSided*/);
				auto pbrMaterialProperties = new PBRMaterialProperties();
				auto specularMaterialProperties = new SpecularMaterialProperties();
				// some adjustment, lets see if we can extract this later
				specularMaterialProperties->setAmbientColor(Color4(0.8f, 0.8f, 0.8f, 1.0f));
				specularMaterialProperties->setDiffuseColor(Color4(0.2f, 0.2f, 0.2f, 1.0f));
				if (gltfMaterial.values.find("baseColorFactor") != gltfMaterial.values.end()) {
					auto& gltfMaterialBaseColorFactor = gltfMaterial.values.find("baseColorFactor")->second;
					Console::println(
						"GLTFReader::parseNode(): " +
						node->getId() + ": " +
						"have base color factor with " +
						to_string(gltfMaterialBaseColorFactor.number_array[0]) + ", " +
						to_string(gltfMaterialBaseColorFactor.number_array[1]) + ", " +
						to_string(gltfMaterialBaseColorFactor.number_array[2]) + ", " +
						to_string(gltfMaterialBaseColorFactor.number_array[3])
					);
					pbrMaterialProperties->setBaseColorFactor(
						Color4(
							gltfMaterialBaseColorFactor.number_array[0],
							gltfMaterialBaseColorFactor.number_array[1],
							gltfMaterialBaseColorFactor.number_array[2],
							gltfMaterialBaseColorFactor.number_array[3]
						)
					);
					specularMaterialProperties->setAmbientColor(
						Color4(
							specularMaterialProperties->getAmbientColor().getRed() * gltfMaterialBaseColorFactor.number_array[0],
							specularMaterialProperties->getAmbientColor().getGreen() * gltfMaterialBaseColorFactor.number_array[1],
							specularMaterialProperties->getAmbientColor().getBlue() * gltfMaterialBaseColorFactor.number_array[2],
							gltfMaterialBaseColorFactor.number_array[3]
						)
					);
					specularMaterialProperties->setDiffuseColor(
						Color4(
							specularMaterialProperties->getDiffuseColor().getRed() * gltfMaterialBaseColorFactor.number_array[0],
							specularMaterialProperties->getDiffuseColor().getGreen() * gltfMaterialBaseColorFactor.number_array[1],
							specularMaterialProperties->getDiffuseColor().getBlue() * gltfMaterialBaseColorFactor.number_array[2],
							gltfMaterialBaseColorFactor.number_array[3]
						)
					);
				}
				if (gltfMaterial.values.find("metallicFactor") != gltfMaterial.values.end()) {
					auto& gltfMaterialMatallicFactor = gltfMaterial.values.find("metallicFactor")->second;
					Console::println(
						"GLTFReader::parseNode(): " +
						node->getId() + ": " +
						"have metallic factor with " +
						to_string(gltfMaterialMatallicFactor.number_value)
					);
					pbrMaterialProperties->setMetallicFactor(gltfMaterialMatallicFactor.number_value);
				}
				if (gltfMaterial.values.find("roughnessFactor") != gltfMaterial.values.end()) {
					auto& gltfMaterialRoughnessFactor = gltfMaterial.values.find("roughnessFactor")->second;
					Console::println(
						"GLTFReader::parseNode(): " +
						node->getId() + ": " +
						"have roughness factor with " +
						to_string(gltfMaterialRoughnessFactor.number_value)
					);
					pbrMaterialProperties->setRoughnessFactor(gltfMaterialRoughnessFactor.number_value);
				}
				// we ignore for now Factor, ColorFactor, TextureScale, TextureStrength, TextureTexCoord as I do not see them feasible in Blender exported GLTF files
				if (gltfMaterial.values.find("baseColorTexture") != gltfMaterial.values.end() &&
					gltfMaterial.values.find("baseColorTexture")->second.TextureIndex() != -1) {
					auto& gltfMaterialBaseColorTexture = gltfMaterial.values.find("baseColorTexture")->second;
					auto& gltfTexture = gltfModel.textures[gltfMaterialBaseColorTexture.TextureIndex()];
					auto& image = gltfModel.images[gltfTexture.source];
					try {
						if (image.component != 3 && image.component != 4) throw ExceptionBase("We only support RGB or RGBA textures for now");
						if (image.bits != 8) throw ExceptionBase("We only support 8 bit channels for now");
						auto fileName = determineTextureFileName(image.name);
						Console::println("GLTFReader::parseNode(): " + node->getId() + ": have base color texture with " + to_string(image.width) + " x " + to_string(image.height) + " x " + to_string(image.component) + " x " + to_string(image.bits) + ": " + fileName);
						auto textureData = ByteBuffer(image.width * image.height * image.component * image.bits / 8);
						for (int y = image.height - 1; y >= 0; y--) {
							textureData.put(&image.image[y * image.width * image.component * image.bits / 8], image.width * image.component * image.bits / 8);
						}
						auto texture = new Texture(
							fileName,
							Texture::getRGBDepthByPixelBitsPerPixel(image.bits * image.component),
							Texture::getPNGFormatByPixelBitsPerPixel(image.bits * image.component),
							image.width,
							image.height,
							image.width,
							image.height,
							Texture::getRGBFormatByPixelBitsPerPixel(image.bits * image.component),
							textureData
						);
						texture->setUseCompression(useBC7TextureCompression);
						//
						pbrMaterialProperties->setBaseColorTexture(texture);
						if (pbrMaterialProperties->hasBaseColorTextureTransparency() == true) pbrMaterialProperties->setBaseColorTextureMaskedTransparency(true);
						specularMaterialProperties->setDiffuseTexture(texture);
						if (specularMaterialProperties->hasDiffuseTextureTransparency() == true) specularMaterialProperties->setDiffuseTextureMaskedTransparency(true);
						//
						if (gltfTexture.sampler != -1) {
							auto& sampler = gltfModel.samplers[gltfTexture.sampler];
							switch (sampler.minFilter) {
								case TINYGLTF_TEXTURE_FILTER_NEAREST: texture->setMinFilter(Texture::TEXTUREFILTER_NEAREST); texture->setUseMipMap(false); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR: texture->setMinFilter(Texture::TEXTUREFILTER_LINEAR); texture->setUseMipMap(false); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST: texture->setMinFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST: texture->setMinFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR: texture->setMinFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: texture->setMinFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
							}
							switch (sampler.magFilter) {
								case TINYGLTF_TEXTURE_FILTER_NEAREST: texture->setMagFilter(Texture::TEXTUREFILTER_NEAREST); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR: texture->setMagFilter(Texture::TEXTUREFILTER_LINEAR); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST: texture->setMagFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST: texture->setMagFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR: texture->setMagFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: texture->setMagFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
							}
						}
					} catch (Exception& exception) {
						Console::println("GLTFReader::parseNode(): " + node->getId() + ": An error occurred: " + exception.what());
					}
				}
				if (gltfMaterial.values.find("metallicRoughnessTexture") != gltfMaterial.values.end() &&
					gltfMaterial.values.find("metallicRoughnessTexture")->second.TextureIndex() != -1) {
					auto& gltfMetallicRoughnessTexture = gltfMaterial.values.find("metallicRoughnessTexture")->second;
					auto& gltfTexture = gltfModel.textures[gltfMetallicRoughnessTexture.TextureIndex()];
					auto& image = gltfModel.images[gltfTexture.source];
					try {
						if (image.component != 3 && image.component != 4) throw ExceptionBase("We only support RGB or RGBA textures for now");
						if (image.bits != 8) throw ExceptionBase("We only support 8 bit channels for now");
						auto fileName = determineTextureFileName(image.name);
						Console::println("GLTFReader::parseNode(): " + node->getId() + ": have metallic roughness texture with " + to_string(image.width) + " x " + to_string(image.height) + " x " + to_string(image.component) + " x " + to_string(image.bits) + ": " + fileName);
						auto textureData = ByteBuffer(image.width * image.height * image.component * image.bits / 8);
						for (int y = image.height - 1; y >= 0; y--) {
							textureData.put(&image.image[y * image.width * image.component * image.bits / 8], image.width * image.component * image.bits / 8);
						}
						auto texture = new Texture(
							fileName,
							Texture::getRGBDepthByPixelBitsPerPixel(image.bits * image.component),
							Texture::getPNGFormatByPixelBitsPerPixel(image.bits * image.component),
							image.width,
							image.height,
							image.width,
							image.height,
							Texture::getRGBFormatByPixelBitsPerPixel(image.bits * image.component),
							textureData
						);
						texture->setUseCompression(useBC7TextureCompression);
						//
						pbrMaterialProperties->setMetallicRoughnessTexture(texture);
						//
						if (gltfTexture.sampler != -1) {
							auto& sampler = gltfModel.samplers[gltfTexture.sampler];
							switch (sampler.minFilter) {
								case TINYGLTF_TEXTURE_FILTER_NEAREST: texture->setMinFilter(Texture::TEXTUREFILTER_NEAREST); texture->setUseMipMap(false); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR: texture->setMinFilter(Texture::TEXTUREFILTER_LINEAR); texture->setUseMipMap(false); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST: texture->setMinFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST: texture->setMinFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR: texture->setMinFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: texture->setMinFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
							}
							switch (sampler.magFilter) {
								case TINYGLTF_TEXTURE_FILTER_NEAREST: texture->setMagFilter(Texture::TEXTUREFILTER_NEAREST); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR: texture->setMagFilter(Texture::TEXTUREFILTER_LINEAR); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST: texture->setMagFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST: texture->setMagFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR: texture->setMagFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: texture->setMagFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
							}
						}
					} catch (Exception& exception) {
						Console::println("GLTFReader::parseNode(): " + node->getId() + ": An error occurred: " + exception.what());
					}
				}
				if (gltfMaterial.additionalValues.find("normalTexture") != gltfMaterial.additionalValues.end() &&
					gltfMaterial.additionalValues.find("normalTexture")->second.TextureIndex() != -1) {
					auto& gltfNormalTexture = gltfMaterial.additionalValues.find("normalTexture")->second;
					auto& gltfTexture = gltfModel.textures[gltfNormalTexture.TextureIndex()];
					auto& image = gltfModel.images[gltfTexture.source];
					try {
						if (image.component != 3 && image.component != 4) throw ExceptionBase("We only support RGB or RGBA textures for now");
						if (image.bits != 8) throw ExceptionBase("We only support 8 bit channels for now");
						auto fileName = determineTextureFileName(image.name);
						Console::println("GLTFReader::parseNode(): " + node->getId() + ": have normal texture with " + to_string(image.width) + " x " + to_string(image.height) + " x " + to_string(image.component) + " x " + to_string(image.bits) + ": " + fileName);
						auto textureData = ByteBuffer(image.width * image.height * image.component * image.bits / 8);
						for (int y = image.height - 1; y >= 0; y--) {
							textureData.put(&image.image[y * image.width * image.component * image.bits / 8], image.width * image.component * image.bits / 8);
						}
						auto texture = new Texture(
							fileName,
							Texture::getRGBDepthByPixelBitsPerPixel(image.bits * image.component),
							Texture::getPNGFormatByPixelBitsPerPixel(image.bits * image.component),
							image.width,
							image.height,
							image.width,
							image.height,
							Texture::getRGBFormatByPixelBitsPerPixel(image.bits * image.component),
							textureData
						);
						texture->setUseCompression(useBC7TextureCompression);
						//
						pbrMaterialProperties->setNormalTexture(texture);
						//
						if (gltfTexture.sampler != -1) {
							auto& sampler = gltfModel.samplers[gltfTexture.sampler];
							switch (sampler.minFilter) {
								case TINYGLTF_TEXTURE_FILTER_NEAREST: texture->setMinFilter(Texture::TEXTUREFILTER_NEAREST); texture->setUseMipMap(false); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR: texture->setMinFilter(Texture::TEXTUREFILTER_LINEAR); texture->setUseMipMap(false); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST: texture->setMinFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST: texture->setMinFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR: texture->setMinFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: texture->setMinFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
							}
							switch (sampler.magFilter) {
								case TINYGLTF_TEXTURE_FILTER_NEAREST: texture->setMagFilter(Texture::TEXTUREFILTER_NEAREST); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR: texture->setMagFilter(Texture::TEXTUREFILTER_LINEAR); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST: texture->setMagFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST: texture->setMagFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR: texture->setMagFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: texture->setMagFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
							}
						}
					} catch (Exception& exception) {
						Console::println("GLTFReader::parseNode(): " + node->getId() + ": An error occurred: " + exception.what());
					}
				}
				if (gltfMaterial.emissiveTexture.index != -1) {
					auto& gltfTexture = gltfModel.textures[gltfMaterial.emissiveTexture.index];
					auto& image = gltfModel.images[gltfTexture.source];
					try {
						if (image.component != 3 && image.component != 4) throw ExceptionBase("We only support RGB or RGBA textures for now");
						if (image.bits != 8) throw ExceptionBase("We only support 8 bit channels for now");
						auto fileName = determineTextureFileName(image.name);
						Console::println("GLTFReader::parseNode(): " + node->getId() + ": have emissive texture with " + to_string(image.width) + " x " + to_string(image.height) + " x " + to_string(image.component) + " x " + to_string(image.bits) + ": " + fileName);
						auto textureData = ByteBuffer(image.width * image.height * image.component * image.bits / 8);
						for (int y = image.height - 1; y >= 0; y--) {
							textureData.put(&image.image[y * image.width * image.component * image.bits / 8], image.width * image.component * image.bits / 8);
						}
						auto texture = new Texture(
							fileName,
							Texture::getRGBDepthByPixelBitsPerPixel(image.bits * image.component),
							Texture::getPNGFormatByPixelBitsPerPixel(image.bits * image.component),
							image.width,
							image.height,
							image.width,
							image.height,
							Texture::getRGBFormatByPixelBitsPerPixel(image.bits * image.component),
							textureData
						);
						texture->setUseCompression(useBC7TextureCompression);
						//
						pbrMaterialProperties->setEmissiveFactor(Color4(gltfMaterial.emissiveFactor[0], gltfMaterial.emissiveFactor[1], gltfMaterial.emissiveFactor[2], 1.0f));
						pbrMaterialProperties->setEmissiveTexture(texture);
						//
						if (gltfTexture.sampler != -1) {
							auto& sampler = gltfModel.samplers[gltfTexture.sampler];
							switch (sampler.minFilter) {
								case TINYGLTF_TEXTURE_FILTER_NEAREST: texture->setMinFilter(Texture::TEXTUREFILTER_NEAREST); texture->setUseMipMap(false); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR: texture->setMinFilter(Texture::TEXTUREFILTER_LINEAR); texture->setUseMipMap(false); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST: texture->setMinFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST: texture->setMinFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR: texture->setMinFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: texture->setMinFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
							}
							switch (sampler.magFilter) {
								case TINYGLTF_TEXTURE_FILTER_NEAREST: texture->setMagFilter(Texture::TEXTUREFILTER_NEAREST); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR: texture->setMagFilter(Texture::TEXTUREFILTER_LINEAR); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST: texture->setMagFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST: texture->setMagFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_NEAREST); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR: texture->setMagFilter(Texture::TEXTUREFILTER_NEAREST_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
								case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: texture->setMagFilter(Texture::TEXTUREFILTER_LINEAR_MIPMAP_LINEAR); texture->setUseMipMap(true); break;
							}
						}
					} catch (Exception& exception) {
						Console::println("GLTFReader::parseNode(): " + node->getId() + ": An error occurred: " + exception.what());
					}
				}
				material->setSpecularMaterialProperties(specularMaterialProperties);
				material->setPBRMaterialProperties(pbrMaterialProperties);
				model->getMaterials()[material->getId()] = material;
			}
		}
		if (gltfPrimitive.mode != TINYGLTF_MODE_TRIANGLES) {
			Console::println("GLTFReader::parseNode(): " + node->getId() + ": Invalid primitive mode: " + to_string(gltfPrimitive.mode));
			continue;
		}

		//
		auto start = 0;
		bool haveVertices = false;
		bool haveNormals = false;
		bool haveTextureCoordinates = false;
		for (auto& gltfAttributeIt: gltfPrimitive.attributes) {
			auto gltfBufferType = gltfAttributeIt.first;
			auto& attributeAccessor = gltfModel.accessors[gltfAttributeIt.second];
			auto& attributeBufferView = gltfModel.bufferViews[attributeAccessor.bufferView];
			auto& attributeBuffer = gltfModel.buffers[attributeBufferView.buffer];
			if (gltfBufferType == "POSITION") {
				if (attributeAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
					Console::println("GLTFReader::parseNode(): " + node->getId() + ": POSITION: Invalid attributes component: " + to_string(attributeAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(attributeAccessor.componentType)));
					continue;
				}
				auto stride = attributeBufferView.byteStride == 0?3 * sizeof(float) / sizeof(float):attributeBufferView.byteStride / sizeof(float);
				haveVertices = true;
				start = vertices.size();
				if (start + attributeAccessor.count > vertices.size()) vertices.resize(start + attributeAccessor.count);
				auto bufferData = (const float*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
				for (auto i = 0; i < attributeAccessor.count; i++) {
					vertices[start + i] = Vector3(bufferData[i * stride + 0], bufferData[i * stride + 1], bufferData[i * stride + 2]);
				}
			} else
			if (gltfBufferType == "NORMAL") {
				if (attributeAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
					Console::println("GLTFReader::parseNode(): " + node->getId() + ": NORMAL: Invalid attributes component: " + to_string(attributeAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(attributeAccessor.componentType)));
					continue;
				}
				auto stride = attributeBufferView.byteStride == 0?3 * sizeof(float) / sizeof(float):attributeBufferView.byteStride / sizeof(float);
				haveNormals = true;
				auto start = normals.size();
				if (start + attributeAccessor.count > normals.size()) normals.resize(start + attributeAccessor.count);
				auto bufferData = (const float*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
				for (auto i = 0; i < attributeAccessor.count; i++) {
					normals[start + i] = Vector3(bufferData[i * stride + 0], bufferData[i * stride + 1], bufferData[i * stride + 2]);
				}
			} else
			if (gltfBufferType == "TEXCOORD_0") {
				if (attributeAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
					Console::println("GLTFReader::parseNode(): " + node->getId() + ": TEXTCOORD_0: Invalid attributes component: " + to_string(attributeAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(attributeAccessor.componentType)));
					continue;
				}
				auto stride = attributeBufferView.byteStride == 0?2 * sizeof(float) / sizeof(float):attributeBufferView.byteStride / sizeof(float);
				haveTextureCoordinates = true;
				auto start = textureCoordinates.size();
				if (start + attributeAccessor.count > textureCoordinates.size()) textureCoordinates.resize(start + attributeAccessor.count);
				auto bufferData = (const float*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
				for (auto i = 0; i < attributeAccessor.count; i++) {
					textureCoordinates[start + i] = TextureCoordinate( bufferData[i * stride + 0], bufferData[i * stride + 1]);
				}
			} else
			if (gltfBufferType == "COLOR_0") {
				// ignored for now
			} else
			if (gltfBufferType == "WEIGHTS_0") {
				if (attributeAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
					Console::println("GLTFReader::parseNode(): " + node->getId() + ": WEIGHTS_0: Invalid attributes component: " + to_string(attributeAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(attributeAccessor.componentType)));
					continue;
				}
				auto stride = attributeBufferView.byteStride == 0?4 * sizeof(float) / sizeof(float):attributeBufferView.byteStride / sizeof(float);
				auto start = weights.size();
				if (start + attributeAccessor.count * 4 > weights.size()) weights.resize(start + attributeAccessor.count * 4);
				auto bufferData = (const float*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
				for (auto i = 0; i < attributeAccessor.count; i++) {
					weights[start + i * 4 + 0] = bufferData[i * stride + 0];
					weights[start + i * 4 + 1] = bufferData[i * stride + 1];
					weights[start + i * 4 + 2] = bufferData[i * stride + 2];
					weights[start + i * 4 + 3] = bufferData[i * stride + 3];
				}
			} else
			if (gltfBufferType == "JOINTS_0") {
				if (attributeAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE) {
					auto stride = attributeBufferView.byteStride == 0?4 * sizeof(uint8_t) / sizeof(uint8_t):attributeBufferView.byteStride / sizeof(uint8_t);
					auto start = joints.size();
					if (start + attributeAccessor.count * 4 > joints.size()) joints.resize(start + attributeAccessor.count * 4);
					auto bufferData = (const uint8_t*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
					for (auto i = 0; i < attributeAccessor.count; i++) {
						joints[start + i * 4 + 0] = bufferData[i * stride + 0];
						joints[start + i * 4 + 1] = bufferData[i * stride + 1];
						joints[start + i * 4 + 2] = bufferData[i * stride + 2];
						joints[start + i * 4 + 3] = bufferData[i * stride + 3];
					}
				} else
				if (attributeAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
					auto stride = attributeBufferView.byteStride == 0?4 * sizeof(uint16_t) / sizeof(uint16_t):attributeBufferView.byteStride / sizeof(uint16_t);
					auto start = joints.size();
					if (start + attributeAccessor.count * 4 > joints.size()) joints.resize(start + attributeAccessor.count * 4);
					auto bufferData = (const uint16_t*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
					for (auto i = 0; i < attributeAccessor.count; i++) {
						joints[start + i * 4 + 0] = bufferData[i * stride + 0];
						joints[start + i * 4 + 1] = bufferData[i * stride + 1];
						joints[start + i * 4 + 2] = bufferData[i * stride + 2];
						joints[start + i * 4 + 3] = bufferData[i * stride + 3];
					}
				} else {
					Console::println("GLTFReader::parseNode(): " + node->getId() + ": JOINTS_0: Invalid attributes component: " + to_string(attributeAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(attributeAccessor.componentType)));
					continue;
				}
			} else {
				Console::println("GLTFReader::parseNode(): " + node->getId() + ": Invalid buffer type: " + gltfBufferType);
			}
		}

		// check for vertices
		if (haveVertices == false) {
			throw ModelFileIOException("Missing vertices");
		}

		// indices
		vector<int> indices;
		{
			if (gltfPrimitive.indices == -1) {
				indices.resize(vertices.size());
				for (auto i = 0; i < vertices.size(); i++) indices[i] = i;
			} else {
				auto& indicesAccessor = gltfModel.accessors[gltfPrimitive.indices];
				auto& indicesBufferView = gltfModel.bufferViews[indicesAccessor.bufferView];
				auto& indicesBuffer = gltfModel.buffers[indicesBufferView.buffer];
				switch (indicesAccessor.componentType) {
					case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
						{
							auto stride = indicesBufferView.byteStride == 0?1 * sizeof(uint8_t) / sizeof(uint8_t):indicesBufferView.byteStride / sizeof(uint8_t);
							const uint8_t* indicesBufferData = (const uint8_t*)(indicesBuffer.data.data() + indicesAccessor.byteOffset + indicesBufferView.byteOffset);
							for (auto i = 0; i < indicesAccessor.count; i++) {
								indices.push_back(indicesBufferData[i * stride]);
							}
							break;
						}
					case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
						{
							auto stride = indicesBufferView.byteStride == 0?1 * sizeof(uint16_t) / sizeof(uint16_t):indicesBufferView.byteStride / sizeof(uint16_t);
							const uint16_t* indicesBufferData = (const uint16_t*)(indicesBuffer.data.data() + indicesAccessor.byteOffset + indicesBufferView.byteOffset);
							for (auto i = 0; i < indicesAccessor.count; i++) {
								indices.push_back(indicesBufferData[i * stride]);
							}
							break;
						}
					case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
						{
							auto stride = indicesBufferView.byteStride == 0?1 * sizeof(uint32_t) / sizeof(uint32_t):indicesBufferView.byteStride / sizeof(uint32_t);
							const uint32_t* indicesBufferData = (const uint32_t*)(indicesBuffer.data.data() + indicesAccessor.byteOffset + indicesBufferView.byteOffset);
							for (auto i = 0; i < indicesAccessor.count; i++) {
								indices.push_back(indicesBufferData[i * stride]);
							}
							break;
						}
					default:
						Console::println("GLTFReader::parseNode(): " + node->getId() + ": Invalid indices component: " + to_string(indicesAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(indicesAccessor.componentType)));
				}
			}
		}

		//
		FacesEntity facesEntity(node, node->getId() + "-" + to_string(facesEntityIdx));
		facesEntity.setMaterial(material);
		vector<Face> faces;
		if (haveTextureCoordinates == true) {
			for (auto i = 0; i < indices.size() / 3; i++) {
				faces.emplace_back(
					node,
					start + indices[i * 3 + 0], start + indices[i * 3 + 1], start + indices[i * 3 + 2],
					start + indices[i * 3 + 0], start + indices[i * 3 + 1], start + indices[i * 3 + 2],
					start + indices[i * 3 + 0], start + indices[i * 3 + 1], start + indices[i * 3 + 2]
				);
			}
		} else {
			for (auto i = 0; i < indices.size() / 3; i++) {
				faces.emplace_back(
					node,
					start + indices[i * 3 + 0], start + indices[i * 3 + 1], start + indices[i * 3 + 2],
					start + indices[i * 3 + 0], start + indices[i * 3 + 1], start + indices[i * 3 + 2]
				);
			}
		}
		facesEntity.setFaces(faces);
		facesEntities.push_back(facesEntity);
		facesEntityIdx++;
	}

	// skinning
	if (gltfNode.skin != -1) {
		auto& gltfSkin = gltfModel.skins[gltfNode.skin];
		auto& inverseBindMatricesAccessor = gltfModel.accessors[gltfSkin.inverseBindMatrices];
		auto& inverseBindMatricesBufferView = gltfModel.bufferViews[inverseBindMatricesAccessor.bufferView];
		auto& inverseBindMatricesBuffer = gltfModel.buffers[inverseBindMatricesBufferView.buffer];
		const float* inverseBindMatricesBufferData = nullptr;
		auto stride = inverseBindMatricesBufferView.byteStride == 0?16 * sizeof(float) / sizeof(float):inverseBindMatricesBufferView.byteStride / sizeof(float);
		if (inverseBindMatricesAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
			Console::println("GLTFReader::parseNode(): " + node->getId() + ": Inverse bind matrices: Invalid attributes component: " + to_string(inverseBindMatricesAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(inverseBindMatricesAccessor.componentType)));
		} else {
			inverseBindMatricesBufferData = (const float*)(inverseBindMatricesBuffer.data.data() + inverseBindMatricesAccessor.byteOffset + inverseBindMatricesBufferView.byteOffset);
		}
		if (inverseBindMatricesBufferData != nullptr) {
			auto skinning = new Skinning();
			{
				auto i = 0;
				vector<Joint> skinningJoints(gltfSkin.joints.size());
				for (auto gltfJointNodeIdx: gltfSkin.joints) {
					Joint joint(gltfModel.nodes[gltfJointNodeIdx].name);
					joint.setBindMatrix(
						Matrix4x4(
							inverseBindMatricesBufferData[i * stride + 0],
							inverseBindMatricesBufferData[i * stride + 1],
							inverseBindMatricesBufferData[i * stride + 2],
							inverseBindMatricesBufferData[i * stride + 3],
							inverseBindMatricesBufferData[i * stride + 4],
							inverseBindMatricesBufferData[i * stride + 5],
							inverseBindMatricesBufferData[i * stride + 6],
							inverseBindMatricesBufferData[i * stride + 7],
							inverseBindMatricesBufferData[i * stride + 8],
							inverseBindMatricesBufferData[i * stride + 9],
							inverseBindMatricesBufferData[i * stride + 10],
							inverseBindMatricesBufferData[i * stride + 11],
							inverseBindMatricesBufferData[i * stride + 12],
							inverseBindMatricesBufferData[i * stride + 13],
							inverseBindMatricesBufferData[i * stride + 14],
							inverseBindMatricesBufferData[i * stride + 15]
						)
					);
					skinningJoints[i++] = joint;
				}
				skinning->setJoints(skinningJoints);
			}
			{
				vector<float> skinningWeights;
				vector<vector<JointWeight>> skinningJointWeights(vertices.size());
				for (auto i = 0; i < vertices.size(); i++) {
					for (auto j = 0; j < 4; j++) {
						// TODO: reuse weights
						if (weights[i * 4 + j] > Math::EPSILON) {
							skinningJointWeights[i].emplace_back(joints[i * 4 + j], static_cast<int32_t>(skinningWeights.size()));
							skinningWeights.push_back(weights[i * 4 + j]);
						}
					}
				}
				skinning->setWeights(skinningWeights);
				skinning->setVerticesJointsWeights(skinningJointWeights);
			}
			node->setSkinning(skinning);
		}
	}

	// set up node
	node->setVertices(vertices);
	node->setNormals(normals);
	node->setTextureCoordinates(textureCoordinates);
	node->setFacesEntities(facesEntities);

	//
	return node;
}

void GLTFReader::parseNodeChildren(const string& pathName, tinygltf::Model& gltfModel, const vector<int>& gltfNodeChildrenIdx, Node* parentNode, int& anonymousNodeIdx, bool useBC7TextureCompression) {
	for (auto gltfNodeIdx: gltfNodeChildrenIdx) {
		auto& gltfNode = gltfModel.nodes[gltfNodeIdx];
		auto node = parseNode(pathName, gltfModel, gltfNodeIdx, parentNode->getModel(), parentNode, anonymousNodeIdx, useBC7TextureCompression);
		parentNode->getModel()->getNodes()[node->getId()] = node;
		if (parentNode->getSubNodes().find(node->getId()) != parentNode->getSubNodes().end()) {
			Console::println("GLTFReader::parseNodeChildren(): node already exists: " + node->getId());
		}
		parentNode->getSubNodes()[node->getId()] = node;
		if (gltfNode.children.empty() == false) parseNodeChildren(pathName, gltfModel, gltfNode.children, node, anonymousNodeIdx, useBC7TextureCompression);
	}
}


string GLTFReader::determineTextureFileName(const string& imageName) {
	/*
	// try to avoid double parts in names that can happen when having 2 maps, 1 for colors and 1 for transparency
	string doubleFileNamePart = "";
	for (auto i = 3; i < imageName.size(); i++) {
		auto doubleFileNamePartTest = StringTools::substring(imageName, 0, i);
		if (imageName.rfind(doubleFileNamePartTest) > i) {
			doubleFileNamePart = doubleFileNamePartTest;
		} else {
			break;
		}
	}
	if (doubleFileNamePart.empty() == false) {
		return StringTools::replace(imageName, doubleFileNamePart, "", imageName.rfind(doubleFileNamePart)) + ".png";
	} else {
		return imageName + ".png";
	}
	*/
	return imageName + ".png";
}

void GLTFReader::computeTangentsAndBitangents(Node* node) {
	ModelTools::computeTangentsAndBitangents(node);
	for (auto& nodeIt: node->getSubNodes()) {
		computeTangentsAndBitangents(nodeIt.second);
	}
}

const Matrix4x4 GLTFReader::getNodeScaleMatrix(const tinygltf::Model& gltfModel, const string& nodeId) {
	Matrix4x4 scaleMatrix;
	scaleMatrix.identity();
	auto foundNode = false;
	for (auto& gltfNode: gltfModel.nodes) {
		if (gltfNode.name == nodeId) {
			foundNode = true;
			//
			if (gltfNode.scale.size() == 3) {
				scaleMatrix.scale(Vector3(gltfNode.scale[0], gltfNode.scale[1], gltfNode.scale[2]));
			}
			//
			break;
		}
	}
	if (foundNode == false) {
		Console::println("GLTFReader::GLTFReader(): getting node scale: GLTF node not found:" + nodeId);
	}
	//
	return scaleMatrix;
}

const Matrix4x4 GLTFReader::getNodeRotationMatrix(const tinygltf::Model& gltfModel, const string& nodeId) {
	Matrix4x4 rotationMatrix;
	rotationMatrix.identity();
	auto foundNode = false;
	for (auto& gltfNode: gltfModel.nodes) {
		if (gltfNode.name == nodeId) {
			foundNode = true;
			//
			if (gltfNode.rotation.size() == 4) {
				Quaternion rotationQuaternion(gltfNode.rotation[0], gltfNode.rotation[1], gltfNode.rotation[2], gltfNode.rotation[3]);
				rotationMatrix = rotationQuaternion.computeMatrix();
			}
			//
			break;
		}
	}
	if (foundNode == false) {
		Console::println("GLTFReader::GLTFReader(): getting node rotation: GLTF node not found:" + nodeId);
	}
	//
	return rotationMatrix;
}

const Matrix4x4 GLTFReader::getNodeTranslationMatrix(const tinygltf::Model& gltfModel, const string& nodeId) {
	Matrix4x4 translationMatrix;
	translationMatrix.identity();
	auto foundNode = false;
	for (auto& gltfNode: gltfModel.nodes) {
		if (gltfNode.name == nodeId) {
			foundNode = true;
			//
			if (gltfNode.translation.size() == 3) {
				translationMatrix.translate(Vector3(gltfNode.translation[0], gltfNode.translation[1], gltfNode.translation[2]));
			}
			//
			break;
		}
	}
	if (foundNode == false) {
		Console::println("GLTFReader::GLTFReader(): getting node translation: GLTF node not found:" + nodeId);
	}
	//
	return translationMatrix;
}
