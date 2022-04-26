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
#include <tdme/engine/fileio/textures/Texture.h>
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

using tdme::engine::fileio::textures::Texture;
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

Model* GLTFReader::read(const string& pathName, const string& fileName)
{
	// load model
	vector<uint8_t> glftBinaryData;
	FileSystem::getInstance()->getContent(pathName, fileName, glftBinaryData);
	// parse model
	string err;
	string warn;
	tinygltf::Model gltfModel;
	tinygltf::TinyGLTF gltfLoader;
	auto ret = gltfLoader.LoadBinaryFromMemory(&gltfModel, &err, &warn, glftBinaryData.data(), glftBinaryData.size());
	if (warn.empty() == false) Console::println("GLTFReader::read(): warnings: " + warn);
	if (err.empty() == false) Console::println("GLTFReader::read(): errors: " + err);
	if (ret == false){
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
	for (auto& gltfScene: gltfModel.scenes) {
		for (auto gltfNodeIdx: gltfScene.nodes) {
			auto& glTfNode = gltfModel.nodes[gltfNodeIdx];
			auto node = parseNode(pathName, gltfModel, gltfNodeIdx, model, nullptr);
			model->getNodes()[node->getId()] = node;
			if (model->getSubNodes().find(node->getId()) != model->getSubNodes().end()) {
				Console::println("GLTFReader::read(): node already exists: " + node->getId());
			}
			model->getSubNodes()[node->getId()] = node;
			if (glTfNode.children.empty() == false) parseNodeChildren(pathName, gltfModel, glTfNode.children, node);
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
				auto node = model->getNodeById(gltfModel.nodes[gltfChannel.target_node].name);
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
				auto channelFrames = static_cast<int32_t>(Math::ceil(animationInputBufferData[animationInputAccessor.count - 1] * 30.0f));
				// animation output: translation, rotation, scale
				auto& animationOutputAccessor = gltfModel.accessors[gltfSample.output];
				auto& animationOutputBufferView = gltfModel.bufferViews[animationOutputAccessor.bufferView];
				auto& animationOutputBuffer = gltfModel.buffers[animationOutputBufferView.buffer];
				auto animationOutputBufferData = (const float*)(animationOutputBuffer.data.data() + animationOutputAccessor.byteOffset + animationOutputBufferView.byteOffset);
				if (animationOutputAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
					Console::println("GLTFReader::read(): " + node->getId() + ": animation: " + gltfAnimation.name + ": Invalid output attributes component: " + getComponentTypeString(animationOutputAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(animationOutputAccessor.componentType)));
					continue;
				}
				if (maxFrames + channelFrames > animationScaleMatrices[node->getId()].size()) {
					animationScaleMatrices[node->getId()].resize(maxFrames + channelFrames);
				}
				if (maxFrames + channelFrames > animationRotationMatrices[node->getId()].size()) {
					animationRotationMatrices[node->getId()].resize(maxFrames + channelFrames);
				}
				if (maxFrames + channelFrames > animationTranslationMatrices[node->getId()].size()) {
					animationTranslationMatrices[node->getId()].resize(maxFrames + channelFrames);
				}
				// Console::println("xxx: " + node->getId() + ": " + gltfChannel.target_path + " / maxFrames = " + to_string(maxFrames) + ", output frames: " + to_string(animationOutputAccessor.count) + ", " + to_string(animationInputBufferData[0]) + ", channel frames: " + to_string(channelFrames));
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
					interpolateKeyFrames(animationInputAccessor.count, animationInputBufferData, keyFrameMatrices, channelFrames, animationTranslationMatrices[node->getId()], maxFrames);
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
					interpolateKeyFrames(animationInputAccessor.count, animationInputBufferData, keyFrameMatrices, channelFrames, animationRotationMatrices[node->getId()], maxFrames);
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
					interpolateKeyFrames(animationInputAccessor.count, animationInputBufferData, keyFrameMatrices, channelFrames, animationScaleMatrices[node->getId()], maxFrames);
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
			auto& animationMatrices = it.second;
			animationMatrices.resize(maxFrames);
		}
		for (auto& it: animationRotationMatrices) {
			auto& animationMatrices = it.second;
			animationMatrices.resize(maxFrames);
		}
		for (auto& it: animationTranslationMatrices) {
			auto& animationMatrices = it.second;
			animationMatrices.resize(maxFrames);
		}

		// set up nodes animations if we have frames
		for (auto& animationNode: animationNodes) {
			auto node = model->getNodeById(animationNode);
			if (node == nullptr) {
				Console::println("GLTFReader::GLTFReader(): animation: node not found:" + animationNode);
				continue;
			}
			vector<Matrix4x4> animationFinalMatrices(maxFrames);
			Matrix4x4 emptyTransformations;
			for (auto i = 0; i < maxFrames; i++) {
				if (animationScaleMatrices[node->getId()][i].equals(emptyTransformations) == true &&
					animationRotationMatrices[node->getId()][i].equals(emptyTransformations) == true &&
					animationTranslationMatrices[node->getId()][i].equals(emptyTransformations) == true) {
					animationFinalMatrices[i] = model->getNodeById(node->getId())->getTransformationsMatrix();
				} else {
					animationFinalMatrices[i].identity();
					if (animationScaleMatrices[node->getId()][i].equals(emptyTransformations) == false) animationFinalMatrices[i].multiply(animationScaleMatrices[node->getId()][i]);
					if (animationRotationMatrices[node->getId()][i].equals(emptyTransformations) == false) animationFinalMatrices[i].multiply(animationRotationMatrices[node->getId()][i]);
					if (animationTranslationMatrices[node->getId()][i].equals(emptyTransformations) == false) animationFinalMatrices[i].multiply(animationTranslationMatrices[node->getId()][i]);
				}
			}
			auto animation = new Animation();
			animation->setTransformationsMatrices(animationFinalMatrices);
			node->setAnimation(animation);
		}
	}

	// create default animations
	ModelTools::createDefaultAnimation(model, maxFrames);
	// set up joints
	ModelTools::setupJoints(model);
	// fix animation length
	ModelTools::fixAnimationLength(model);

	//
	return model;
}

void GLTFReader::interpolateKeyFrames(int frameTimeCount, const float* frameTimes, const vector<Matrix4x4>& keyFrameMatrices, int interpolatedMatrixCount, vector<Matrix4x4>& interpolatedMatrices, int frameStartIdx) {
	auto tansformationsMatrixLast = &keyFrameMatrices[0];
	auto keyFrameIdx = 0;
	auto frameIdx = 0;
	auto timeStampLast = 0.0f;
	for (auto i = 0; i < frameTimeCount; i++) {
		auto keyFrameTime = frameTimes[i];
		auto transformationsMatrixCurrent = &keyFrameMatrices[(keyFrameIdx) % keyFrameMatrices.size()];
		float timeStamp;
		for (timeStamp = timeStampLast; timeStamp < keyFrameTime; timeStamp += 1.0f / 30.0f) {
			if (frameIdx >= interpolatedMatrixCount) {
				// TODO: check me again!
				// Console::println(string("Warning: skipping frame: ") + to_string(frameIdx));
				frameIdx++;
				continue;
			}
			// Console::println("yyy: " + to_string(frameStartIdx +  frameIdx) + ": key frame idx: " + to_string(keyFrameIdx) + ", interpolation t: " + to_string((timeStamp - timeStampLast) / (keyFrameTime - timeStampLast)));
			interpolatedMatrices[frameStartIdx +  frameIdx] = Matrix4x4::interpolateLinear(*tansformationsMatrixLast, *transformationsMatrixCurrent, (timeStamp - timeStampLast) / (keyFrameTime - timeStampLast));
			frameIdx++;
		}
		timeStampLast = timeStamp;
		tansformationsMatrixLast = transformationsMatrixCurrent;
		keyFrameIdx++;
	}
}

Node* GLTFReader::parseNode(const string& pathName, const tinygltf::Model& gltfModel, int gltfNodeIdx, Model* model, Node* parentNode) {
	auto& gltfNode = gltfModel.nodes[gltfNodeIdx];
	auto node = new Node(model, parentNode, gltfNode.name, gltfNode.name);
	if (gltfNode.matrix.size() == 16) {
		node->setTransformationsMatrix(
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
		Matrix4x4 nodeScaleMatrices;
		Matrix4x4 nodeRotationMatrices;
		Matrix4x4 nodeTranslationMatrices;
		nodeScaleMatrices.identity();
		nodeRotationMatrices.identity();
		nodeTranslationMatrices.identity();
		if (gltfNode.scale.size() == 3) {
			nodeScaleMatrices.scale(Vector3(gltfNode.scale[0], gltfNode.scale[1], gltfNode.scale[2]));
		}
		if (gltfNode.rotation.size() == 4) {
			Quaternion rotationQuaternion(gltfNode.rotation[0], gltfNode.rotation[1], gltfNode.rotation[2], gltfNode.rotation[3]);
			nodeRotationMatrices = rotationQuaternion.computeMatrix();
		}
		if (gltfNode.translation.size() == 3) {
			nodeTranslationMatrices.translate(Vector3(gltfNode.translation[0], gltfNode.translation[1], gltfNode.translation[2]));
		}
		Matrix4x4 nodeTransformationsMatrix;
		nodeTransformationsMatrix.set(nodeScaleMatrices);
		nodeTransformationsMatrix.multiply(nodeRotationMatrices);
		nodeTransformationsMatrix.multiply(nodeTranslationMatrices);
		node->setTransformationsMatrix(nodeTransformationsMatrix);
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
						auto textureData = ByteBuffer::allocate(image.width * image.height * image.component * image.bits / 8);
						for (int y = image.height - 1; y >= 0; y--) {
							textureData->put(&image.image[y * image.width * image.component * image.bits / 8], image.width * image.component * image.bits / 8);
						}
						auto texture = new Texture(
							fileName,
							image.bits * image.component,
							image.width,
							image.height,
							image.width,
							image.height,
							textureData
						);
						pbrMaterialProperties->setBaseColorTexture(texture);
						if (pbrMaterialProperties->hasBaseColorTextureTransparency() == true) pbrMaterialProperties->setBaseColorTextureMaskedTransparency(true);
						specularMaterialProperties->setDiffuseTexture(texture);
						if (specularMaterialProperties->hasDiffuseTextureTransparency() == true) specularMaterialProperties->setDiffuseTextureMaskedTransparency(true);
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
						auto textureData = ByteBuffer::allocate(image.width * image.height * image.component * image.bits / 8);
						for (int y = image.height - 1; y >= 0; y--) {
							textureData->put(&image.image[y * image.width * image.component * image.bits / 8], image.width * image.component * image.bits / 8);
						}
						auto texture = new Texture(
							fileName,
							image.bits * image.component,
							image.width,
							image.height,
							image.width,
							image.height,
							textureData
						);
						pbrMaterialProperties->setMetallicRoughnessTexture(texture);
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
						auto textureData = ByteBuffer::allocate(image.width * image.height * image.component * image.bits / 8);
						for (int y = image.height - 1; y >= 0; y--) {
							textureData->put(&image.image[y * image.width * image.component * image.bits / 8], image.width * image.component * image.bits / 8);
						}
						auto texture = new Texture(
							fileName,
							image.bits * image.component,
							image.width,
							image.height,
							image.width,
							image.height,
							textureData
						);
						pbrMaterialProperties->setNormalTexture(texture);
					} catch (Exception& exception) {
						Console::println("GLTFReader::parseNode(): " + node->getId() + ": An error occurred: " + exception.what());
					}
				}
				material->setSpecularMaterialProperties(specularMaterialProperties);
				material->setPBRMaterialProperties(pbrMaterialProperties);
				model->getMaterials()[material->getId()] = material;
			}
		}
		if (gltfPrimitive.mode != 4) {
			Console::println("GLTFReader::parseNode(): " + node->getId() + ": Invalid primitive mode: " + to_string(gltfPrimitive.mode));
			continue;
		}
		vector<int> indices;
		{
			auto& indicesAccessor = gltfModel.accessors[gltfPrimitive.indices];
			auto& indicesBufferView = gltfModel.bufferViews[indicesAccessor.bufferView];
			auto& indicesBuffer = gltfModel.buffers[indicesBufferView.buffer];
			if (indicesBufferView.byteStride != 0) {
				Console::println("GLTFReader::parseNode(): " + node->getId() + ": Invalid stride: " + to_string(indicesBufferView.byteStride));
			} else
			switch (indicesAccessor.componentType) {
				case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
					{
						// TODO: stride
						const uint16_t* indicesBufferData = (const uint16_t*)(indicesBuffer.data.data() + indicesAccessor.byteOffset + indicesBufferView.byteOffset);
						for (auto i = 0; i < indicesAccessor.count; i++) {
							indices.push_back(indicesBufferData[i]);
						}
						break;
					}
				case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
					{
						// TODO: stride
						const uint32_t* indicesBufferData = (const uint32_t*)(indicesBuffer.data.data() + indicesAccessor.byteOffset + indicesBufferView.byteOffset);
						for (auto i = 0; i < indicesAccessor.count; i++) {
							indices.push_back(indicesBufferData[i]);
						}
						break;
					}
				default:
					Console::println("GLTFReader::parseNode(): " + node->getId() + ": Invalid indices component: " + to_string(indicesAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(indicesAccessor.componentType)));
			}
		}
		auto start = 0;
		bool haveVertices = false;
		bool haveNormals = false;
		bool haveTextureCoordinates = false;
		for (auto& gltfAttributeIt: gltfPrimitive.attributes) {
			auto gltfBufferType = gltfAttributeIt.first;
			auto& attributeAccessor = gltfModel.accessors[gltfAttributeIt.second];
			auto& attributeBufferView = gltfModel.bufferViews[attributeAccessor.bufferView];
			auto& attributeBuffer = gltfModel.buffers[attributeBufferView.buffer];
			if (attributeBufferView.byteStride != 0) {
				Console::println("GLTFReader::parseNode(): " + node->getId() + ": Invalid attributes stride: " + to_string(attributeBufferView.byteStride));
			} else {
				if (gltfBufferType == "POSITION") {
					if (attributeAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
						Console::println("GLTFReader::parseNode(): " + node->getId() + ": POSITION: Invalid attributes component: " + to_string(attributeAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(attributeAccessor.componentType)));
						continue;
					}
					haveVertices = true;
					start = vertices.size();
					if (start + attributeAccessor.count > vertices.size()) vertices.resize(start + attributeAccessor.count);
					auto bufferData = (const float*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
					for (auto i = 0; i < attributeAccessor.count; i++) {
						vertices[start + i] = Vector3(bufferData[i * 3 + 0], bufferData[i * 3 + 1], bufferData[i * 3 + 2]);
					}
				} else
				if (gltfBufferType == "NORMAL") {
					if (attributeAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
						Console::println("GLTFReader::parseNode(): " + node->getId() + ": NORMAL: Invalid attributes component: " + to_string(attributeAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(attributeAccessor.componentType)));
						continue;
					}
					haveNormals = true;
					auto start = normals.size();
					if (start + attributeAccessor.count > normals.size()) normals.resize(start + attributeAccessor.count);
					auto bufferData = (const float*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
					for (auto i = 0; i < attributeAccessor.count; i++) {
						normals[start + i] = Vector3(bufferData[i * 3 + 0], bufferData[i * 3 + 1], bufferData[i * 3 + 2]);
					}
				} else
				if (gltfBufferType == "TEXCOORD_0") {
					if (attributeAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
						Console::println("GLTFReader::parseNode(): " + node->getId() + ": TEXTCOORD_0: Invalid attributes component: " + to_string(attributeAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(attributeAccessor.componentType)));
						continue;
					}
					haveTextureCoordinates = true;
					auto start = textureCoordinates.size();
					if (start + attributeAccessor.count > textureCoordinates.size()) textureCoordinates.resize(start + attributeAccessor.count);
					auto bufferData = (const float*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
					for (auto i = 0; i < attributeAccessor.count; i++) {
						textureCoordinates[start + i] = TextureCoordinate(bufferData[i * 2 + 0], bufferData[i * 2 + 1]);
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
					auto start = weights.size();
					if (start + attributeAccessor.count * 4 > weights.size()) weights.resize(start + attributeAccessor.count * 4);
					auto bufferData = (const float*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
					for (auto i = 0; i < attributeAccessor.count * 4; i++) {
						weights[start + i] = bufferData[i];
					}
				} else
				if (gltfBufferType == "JOINTS_0") {
					if (attributeAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE) {
						auto start = joints.size();
						if (start + attributeAccessor.count * 4 > joints.size()) joints.resize(start + attributeAccessor.count * 4);
						auto bufferData = (const uint8_t*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
						for (auto i = 0; i < attributeAccessor.count * 4; i++) {
							joints[start + i] = bufferData[i];
						}
					} else
					if (attributeAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
						auto start = joints.size();
						if (start + attributeAccessor.count * 4 > joints.size()) joints.resize(start + attributeAccessor.count * 4);
						auto bufferData = (const uint16_t*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
						for (auto i = 0; i < attributeAccessor.count * 4; i++) {
							joints[start + i] = bufferData[i];
						}
					} else {
						Console::println("GLTFReader::parseNode(): " + node->getId() + ": JOINTS_0: Invalid attributes component: " + to_string(attributeAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(attributeAccessor.componentType)));
						continue;
					}
				} else {
					Console::println("GLTFReader::parseNode(): " + node->getId() + ": Invalid buffer type: " + gltfBufferType);
				}
			}
		}
		FacesEntity facesEntity(node, node->getId() + "-" + to_string(facesEntityIdx));
		facesEntity.setMaterial(material);
		vector<Face> faces;
		if (haveVertices == false || haveNormals == false) throw ModelFileIOException("Missing vertices or normals");
		if (haveTextureCoordinates == true) {
			for (auto i = 0; i < indices.size() / 3; i++) {
				faces.push_back(
					Face(
						node,
						start + indices[i * 3 + 0], start + indices[i * 3 + 1], start + indices[i * 3 + 2],
						start + indices[i * 3 + 0], start + indices[i * 3 + 1], start + indices[i * 3 + 2],
						start + indices[i * 3 + 0], start + indices[i * 3 + 1], start + indices[i * 3 + 2]
					)
				);
			}
		} else {
			for (auto i = 0; i < indices.size() / 3; i++) {
				faces.push_back(
					Face(
						node,
						start + indices[i * 3 + 0], start + indices[i * 3 + 1], start + indices[i * 3 + 2],
						start + indices[i * 3 + 0], start + indices[i * 3 + 1], start + indices[i * 3 + 2]
					)
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
		if (inverseBindMatricesBufferView.byteStride != 0) {
			Console::println("GLTFReader::parseNode(): " + node->getId() + ": Invalid attributes stride: " + to_string(inverseBindMatricesBufferView.byteStride));
		} else
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
							inverseBindMatricesBufferData[i * 16 + 0],
							inverseBindMatricesBufferData[i * 16 + 1],
							inverseBindMatricesBufferData[i * 16 + 2],
							inverseBindMatricesBufferData[i * 16 + 3],
							inverseBindMatricesBufferData[i * 16 + 4],
							inverseBindMatricesBufferData[i * 16 + 5],
							inverseBindMatricesBufferData[i * 16 + 6],
							inverseBindMatricesBufferData[i * 16 + 7],
							inverseBindMatricesBufferData[i * 16 + 8],
							inverseBindMatricesBufferData[i * 16 + 9],
							inverseBindMatricesBufferData[i * 16 + 10],
							inverseBindMatricesBufferData[i * 16 + 11],
							inverseBindMatricesBufferData[i * 16 + 12],
							inverseBindMatricesBufferData[i * 16 + 13],
							inverseBindMatricesBufferData[i * 16 + 14],
							inverseBindMatricesBufferData[i * 16 + 15]
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
							skinningJointWeights[i].push_back(JointWeight(joints[i * 4 + j], skinningWeights.size()));
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

	// create tangents and bitangets, as they seem not be delivered in GLTF files but needed for PBR
	if (vertices.empty() == false && normals.empty() == false) {
		ModelTools::createTangentsAndBitangents(node);
	};

	//
	return node;
}

void GLTFReader::parseNodeChildren(const string& pathName, const tinygltf::Model& gltfModel, const vector<int>& gltfNodeChildrenIdx, Node* parentNode) {
	for (auto gltfNodeIdx: gltfNodeChildrenIdx) {
		auto& gltfNode = gltfModel.nodes[gltfNodeIdx];
		auto node = parseNode(pathName, gltfModel, gltfNodeIdx, parentNode->getModel(), parentNode);
		parentNode->getModel()->getNodes()[node->getId()] = node;
		if (parentNode->getSubNodes().find(node->getId()) != parentNode->getSubNodes().end()) {
			Console::println("GLTFReader::parseNodeChildren(): node already exists: " + node->getId());
		}
		parentNode->getSubNodes()[node->getId()] = node;
		if (gltfNode.children.empty() == false) parseNodeChildren(pathName, gltfModel, gltfNode.children, node);
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
