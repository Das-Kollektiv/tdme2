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

#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

#include <ext/tinyxml/tinyxml.h>

using std::map;
using std::to_string;
using std::set;
using std::string;
using std::vector;

using tdme::engine::fileio::models::GLTFReader;
using tdme::engine::model::Animation;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Material;
using tdme::engine::model::UpVector;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::Console;
using tdme::utils::Exception;

Model* GLTFReader::read(const string& pathName, const string& fileName)
{
	string err;
	string warn;
	tinygltf::Model gltfModel;
	tinygltf::TinyGLTF gltfLoader;
	auto ret = gltfLoader.LoadBinaryFromFile(&gltfModel, &err, &warn, pathName + "/" + fileName); 
	if (warn.empty() == false) Console::println("GLTFReader::read(): warnings: " + warn);
	if (err.empty() == false) Console::println("GLTFReader::read(): errors: " + err);
	if (ret == false){
		Console::println("GLTFReader::read(): Failed to load model: " + pathName + "/" + fileName);
		return nullptr;
	}

	// 	create model
	auto model = new Model(
		FileSystem::getInstance()->getCanonicalPath(pathName, fileName),
		fileName,
		UpVector::Y_UP,
		RotationOrder::ZYX,
		nullptr,
		model::Model::AUTHORINGTOOL_UNKNOWN
	);
	// TODO: Z-Up for now
	// model->setImportTransformationsMatrix((Matrix4x4()).identity().rotate(-90.0f, Vector3(1.0f, 0.0f, 0.0f)));

	// parse nodes aka scene
	for (auto& gltfScene: gltfModel.scenes) {
		for (auto gltfNodeIdx: gltfScene.nodes) { 
			auto& node = gltfModel.nodes[gltfNodeIdx]; 
			auto group = parseNode(pathName, gltfModel, gltfNodeIdx, model, nullptr);
			model->getGroups()[group->getId()] = group;
			model->getSubGroups()[group->getId()] = group;
			if (node.children.empty() == false) parseNodeChildren(pathName, gltfModel, node.children, group);
		}	
	} 

	// animations
	// TODO: key times and interpolation
	auto maxFrames = 0;
	{
		set<string> animationGroups;
		map<string, vector<Matrix4x4>> animationScaleMatrices;
		map<string, vector<Matrix4x4>> animationRotationMatrices;
		map<string, vector<Matrix4x4>> animationTranslationMatrices;
		for (auto& gltfAnimation: gltfModel.animations) {
			// TRS matrices for each frame and groups
			auto frames = 0;
			for (auto& gltfChannel: gltfAnimation.channels) {
				Group* group = model->getGroupById(gltfModel.nodes[gltfChannel.target_node].name);
				animationGroups.insert(group->getId());
				auto& gltfSample = gltfAnimation.samplers[gltfChannel.sampler];
				auto& animationInputAccessor = gltfModel.accessors[gltfSample.input];
				auto& animationInputBufferView = gltfModel.bufferViews[animationInputAccessor.bufferView];
				auto& animationInputBuffer = gltfModel.buffers[animationInputBufferView.buffer];
				const float* animationInputBufferData = (const float*)(animationInputBuffer.data.data() + animationInputAccessor.byteOffset + animationInputBufferView.byteOffset);
				if (maxFrames + animationInputAccessor.count > animationScaleMatrices[group->getId()].size()) {
					animationScaleMatrices[group->getId()].resize(maxFrames + animationInputAccessor.count);
					for (auto i = 0; i < animationInputAccessor.count; i++) animationScaleMatrices[group->getId()][maxFrames + i].identity();
				}
				if (maxFrames + animationInputAccessor.count > animationRotationMatrices[group->getId()].size()) {
					animationRotationMatrices[group->getId()].resize(maxFrames + animationInputAccessor.count);
					for (auto i = 0; i < animationInputAccessor.count; i++) animationRotationMatrices[group->getId()][maxFrames + i].identity();
				}
				if (maxFrames + animationInputAccessor.count > animationTranslationMatrices[group->getId()].size()) {
					animationTranslationMatrices[group->getId()].resize(maxFrames + animationInputAccessor.count);
					for (auto i = 0; i < animationInputAccessor.count; i++) animationTranslationMatrices[group->getId()][maxFrames + i].identity();
				}
				/*
				// TODO: later
				Console::println("Input: ");
				for (auto i = 0; i < animationInputAccessor.count; i++) {
					Console::print(to_string(animationInputBufferData[i]) + ";");
				}
				Console::println();
				*/
				auto& animationOutputAccessor = gltfModel.accessors[gltfSample.output];
				auto& animationOutputBufferView = gltfModel.bufferViews[animationOutputAccessor.bufferView];
				auto& animationOutputBuffer = gltfModel.buffers[animationOutputBufferView.buffer];
				const float* animationOutputBufferData = (const float*)(animationOutputBuffer.data.data() + animationOutputAccessor.byteOffset + animationOutputBufferView.byteOffset);
				if (gltfChannel.target_path == "translation") {
					for (auto i = 0; i < animationOutputAccessor.count; i++) {
						animationTranslationMatrices[group->getId()][maxFrames + i].translate(Vector3(animationOutputBufferData[i * 3 + 0], animationOutputBufferData[i * 3 + 1], animationOutputBufferData[i * 3 + 2]));
					}
				} else
				if (gltfChannel.target_path == "rotation") {
					Quaternion rotationQuaternion;
					for (auto i = 0; i < animationOutputAccessor.count; i++) {
						rotationQuaternion.set(animationOutputBufferData[i * 4 + 0], animationOutputBufferData[i * 4 + 1], animationOutputBufferData[i * 4 + 2], animationOutputBufferData[i * 4 + 3]);
						rotationQuaternion.computeMatrix(animationRotationMatrices[group->getId()][maxFrames + i]);
					}
				} else
				if (gltfChannel.target_path == "scale") {
					for (auto i = 0; i < animationOutputAccessor.count; i++) {
						animationScaleMatrices[group->getId()][maxFrames + i].scale(Vector3(animationOutputBufferData[i * 3 + 0], animationOutputBufferData[i * 3 + 1], animationOutputBufferData[i * 3 + 2]));
					}
				} else {
					Console::println("GLTFReader::GLTFReader(): " + gltfAnimation.name + ": Invalid target path:" + gltfChannel.target_path);
				}
				if (animationInputAccessor.count > frames) frames = animationInputAccessor.count;
			}
			maxFrames+= frames;
		}
		// set up groups animations if we have frames
		for (auto& animationGroup: animationGroups) {
			auto group = model->getGroupById(animationGroup);
			if (group == nullptr) continue;
			vector<Matrix4x4> animationFinalMatrices;
			animationFinalMatrices.resize(maxFrames);
			for (auto i = 0; i < maxFrames; i++) {
				animationFinalMatrices[i].set(animationScaleMatrices[group->getId()][i]);
				animationFinalMatrices[i].multiply(animationRotationMatrices[group->getId()][i]);
				animationFinalMatrices[i].multiply(animationTranslationMatrices[group->getId()][i]);
			}
			auto animation = group->createAnimation();
			animation->setTransformationsMatrices(animationFinalMatrices);
		}
	}

	// create default animations
	ModelHelper::createDefaultAnimation(model, maxFrames);
	// set up joints
	ModelHelper::setupJoints(model);
	// fix animation length
	ModelHelper::fixAnimationLength(model);

	//
	return model;
}

size_t GLTFReader::getComponentTypeByteSize(int type) {
	switch (type) {
		case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
		case TINYGLTF_COMPONENT_TYPE_BYTE:
			return sizeof(char);
		case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
		case TINYGLTF_COMPONENT_TYPE_SHORT:
			return sizeof(short);
		case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
		case TINYGLTF_COMPONENT_TYPE_INT:
			return sizeof(int);
		case TINYGLTF_COMPONENT_TYPE_FLOAT:
			return sizeof(float);
		case TINYGLTF_COMPONENT_TYPE_DOUBLE:
			return sizeof(double);
		default:
			return 0;
	}
}

Group* GLTFReader::parseNode(const string& pathName, const tinygltf::Model& gltfModel, int gltfNodeIdx, Model* model, Group* parentGroup) {
	auto& gltfNode = gltfModel.nodes[gltfNodeIdx];
	auto group = new Group(model, parentGroup, gltfNode.name, gltfNode.name);
	if (gltfNode.matrix.size() == 16) {
		group->setTransformationsMatrix(
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
		Matrix4x4 groupScaleMatrices;
		Matrix4x4 groupRotationMatrices;
		Matrix4x4 groupTranslationMatrices;
		groupScaleMatrices.identity();
		groupRotationMatrices.identity();
		groupTranslationMatrices.identity();
		if (gltfNode.scale.size() == 3) {
			groupScaleMatrices.scale(Vector3(gltfNode.scale[0], gltfNode.scale[1], gltfNode.scale[2]));
		}
		if (gltfNode.rotation.size() == 4) {
			Quaternion rotationQuaternion(gltfNode.rotation[0], gltfNode.rotation[1], gltfNode.rotation[2], gltfNode.rotation[3]);
			rotationQuaternion.computeMatrix(groupRotationMatrices);
		}
		if (gltfNode.translation.size() == 3) {
			groupTranslationMatrices.translate(Vector3(gltfNode.translation[0], gltfNode.translation[1], gltfNode.translation[2]));
		}
		Matrix4x4 groupTransformationsMatrix;
		groupTransformationsMatrix.set(groupScaleMatrices);
		groupTransformationsMatrix.multiply(groupRotationMatrices);
		groupTransformationsMatrix.multiply(groupTranslationMatrices);
		group->setTransformationsMatrix(groupTransformationsMatrix);
	}
	if (gltfNode.mesh == -1) return group;
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
				auto& gltfMaterialBaseColorTexture = gltfMaterial.values.find("baseColorTexture")->second;
				// TODO: This does not seem to work in any case
				if (gltfMaterialBaseColorTexture.TextureIndex() != -1) {
					/*
					Console::println(gltfMaterialName + " => Color Factor: ");
					for (auto value: gltfMaterialBaseColorTexture.ColorFactor()) {
						Console::print(to_string(value));
					}
					Console::println();
					Console::println(image.uri);
					Console::println(image.mimeType);
					*/
					auto& gltfTexture = gltfModel.textures[gltfMaterialBaseColorTexture.TextureIndex()];
					auto& image = gltfModel.images[gltfTexture.source];
					if (image.mimeType == "image/png")
						try {
							auto fileName = image.name + ".png";
							if (writePNG(pathName, fileName, image.component == 3?24:32, image.width, image.height, (const uint8_t*)image.image.data()) == false) {
								Console::println("GLTFReader::parseNode(): " + group->getId() + ": An error occurred: Could not write PNG: " + fileName);
							}
							material->setDiffuseTexture(pathName, fileName);
					} catch (Exception& exception) {
						Console::println("GLTFReader::parseNode(): " + group->getId() + ": An error occurred: " + exception.what());
					}
				}
				/*
				Console::println(gltfMaterialName + " => Texture Index : " + to_string(gltfMaterialBaseColorTexture.TextureIndex()));
				Console::println(gltfMaterialName + " => Texture Scale : " + to_string(gltfMaterialBaseColorTexture.TextureScale()));
				Console::println(gltfMaterialName + " => Texture Strength : " + to_string(gltfMaterialBaseColorTexture.TextureStrength()));
				*/
				model->getMaterials()[material->getId()] = material;
			}
		}
		if (gltfPrimitive.mode != 4) {
			Console::println("GLTFReader::parseNode(): " + group->getId() + ": Invalid primitive mode: " + to_string(gltfPrimitive.mode));
			continue;
		} 
		vector<int> indices;
		{	
			auto& indicesAccessor = gltfModel.accessors[gltfPrimitive.indices];
			auto& indicesBufferView = gltfModel.bufferViews[indicesAccessor.bufferView];
			auto& indicesBuffer = gltfModel.buffers[indicesBufferView.buffer];
			if (indicesBufferView.byteStride != 0) {
				Console::println("GLTFReader::parseNode(): " + group->getId() + ": Invalid stride: " + to_string(indicesBufferView.byteStride));
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
					Console::println("GLTFReader::parseNode(): " + group->getId() + ": Invalid indices component: " + to_string(indicesAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(indicesAccessor.componentType)));
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
				Console::println("GLTFReader::parseNode(): " + group->getId() + ": Invalid attributes stride: " + to_string(attributeBufferView.byteStride));
			} else {
				if (gltfBufferType == "POSITION") {
					if (attributeAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
						Console::println("GLTFReader::parseNode(): " + group->getId() + ": Invalid attributes component: " + to_string(attributeAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(attributeAccessor.componentType)));
						continue;
					}
					haveVertices = true;
					start = vertices.size();
					if (start + attributeAccessor.count > vertices.size()) vertices.resize(start + attributeAccessor.count);
					const float* bufferData = (const float*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
					for (auto i = 0; i < attributeAccessor.count; i++) {
						vertices[start + i] = Vector3(bufferData[i * 3 + 0], bufferData[i * 3 + 1], bufferData[i * 3 + 2]);
					}
				} else
				if (gltfBufferType == "NORMAL") {
					if (attributeAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
						Console::println("GLTFReader::parseNode(): " + group->getId() + ": Invalid attributes component: " + to_string(attributeAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(attributeAccessor.componentType)));
						continue;
					}
					haveNormals = true;
					auto start = normals.size();
					if (start + attributeAccessor.count > normals.size()) normals.resize(start + attributeAccessor.count);
					const float* bufferData = (const float*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
					for (auto i = 0; i < attributeAccessor.count; i++) {
						normals[start + i] = Vector3(bufferData[i * 3 + 0], bufferData[i * 3 + 1], bufferData[i * 3 + 2]);
					}
				} else
				if (gltfBufferType == "TEXCOORD_0") {
					if (attributeAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
						Console::println("GLTFReader::parseNode(): " + group->getId() + ": Invalid attributes component: " + to_string(attributeAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(attributeAccessor.componentType)));
						continue;
					}
					haveTextureCoordinates = true;
					auto start = textureCoordinates.size();
					if (start + attributeAccessor.count > textureCoordinates.size()) textureCoordinates.resize(start + attributeAccessor.count);
					const float* bufferData = (const float*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
					for (auto i = 0; i < attributeAccessor.count; i++) {
						textureCoordinates[start + i] = TextureCoordinate(bufferData[i * 2 + 0], bufferData[i * 2 + 1]);
					}
				} else
				if (gltfBufferType == "COLOR_0") {
					// ignored for now
				} else
				if (gltfBufferType == "WEIGHTS_0") {
					if (attributeAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
						Console::println("GLTFReader::parseNode(): " + group->getId() + ": Invalid attributes component: " + to_string(attributeAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(attributeAccessor.componentType)));
						continue;
					}
					auto start = weights.size();
					if (start + attributeAccessor.count * 4 > weights.size()) weights.resize(start + attributeAccessor.count * 4);
					const float* bufferData = (const float*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
					for (auto i = 0; i < attributeAccessor.count * 4; i++) {
						weights[start + i] = bufferData[i];
					}
				} else
				if (gltfBufferType == "JOINTS_0") {
					if (attributeAccessor.componentType != TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
						Console::println("GLTFReader::parseNode(): " + group->getId() + ": Invalid attributes component: " + to_string(attributeAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(attributeAccessor.componentType)));
						continue;
					}
					auto start = joints.size();
					if (start + attributeAccessor.count * 4 > joints.size()) joints.resize(start + attributeAccessor.count * 4);
					const uint16_t* bufferData = (const uint16_t*)(attributeBuffer.data.data() + attributeAccessor.byteOffset + attributeBufferView.byteOffset);
					for (auto i = 0; i < attributeAccessor.count * 4; i++) {
						joints[start + i] = bufferData[i];
					}
				} else {
					Console::println("GLTFReader::parseNode(): " + group->getId() + ": Invalid buffer type: " + gltfBufferType);
				}
			}
		}
		FacesEntity facesEntity(group, group->getId() + "-" + to_string(facesEntityIdx));
		facesEntity.setMaterial(material);
		vector<Face> faces;
		if (haveVertices == false || haveNormals == false) throw ModelFileIOException("Missing vertices or normals");
		if (haveTextureCoordinates == true) {
			for (auto i = 0; i < indices.size() / 3; i++) {
				faces.push_back(
					Face(
						group,
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
						group,
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
			Console::println("GLTFReader::parseNode(): " + group->getId() + ": Invalid attributes stride: " + to_string(inverseBindMatricesBufferView.byteStride));
		} else
		if (inverseBindMatricesAccessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
			Console::println("GLTFReader::parseNode(): " + group->getId() + ": Inverse bind matrices: Invalid attributes component: " + to_string(inverseBindMatricesAccessor.componentType) + ", with size: " + to_string(getComponentTypeByteSize(inverseBindMatricesAccessor.componentType)));
		} else {
			inverseBindMatricesBufferData = (const float*)(inverseBindMatricesBuffer.data.data() + inverseBindMatricesAccessor.byteOffset + inverseBindMatricesBufferView.byteOffset);
		}
		if (inverseBindMatricesBufferData != nullptr) {
			auto skinning = group->createSkinning();
			{
				vector<Joint> skinningJoints;
				for (auto gltfJointNodeIdx: gltfSkin.joints) {
					Joint joint(gltfModel.nodes[gltfJointNodeIdx].name);
					joint.setBindMatrix(
						Matrix4x4(
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 0],
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 1],
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 2],
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 3],
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 4],
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 5],
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 6],
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 7],
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 8],
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 9],
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 10],
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 11],
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 12],
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 13],
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 14],
							inverseBindMatricesBufferData[skinningJoints.size() * 16 + 15]
						)
					);
					skinningJoints.push_back(joint);
				}
				skinning->setJoints(skinningJoints);
			}
			{
				vector<float> skinningWeights;
				vector<vector<JointWeight>> skinningJointWeights;
				skinningJointWeights.resize(vertices.size());
				for (auto i = 0; i < vertices.size(); i++) {
					for (auto j = 0; j < 4; j++) {
						if (weights[i * 4 + j] > 0.0f) {
							// TODO: reuse weights
							skinningJointWeights[i].push_back(JointWeight(joints[i * 4 + j], skinningWeights.size()));
							skinningWeights.push_back(weights[i * 4 + j]);
						}
					}
				}
				skinning->setWeights(skinningWeights);
				skinning->setVerticesJointsWeights(skinningJointWeights);
			}
		}
	}

	// set up group
	group->setVertices(vertices);
	group->setNormals(normals);
	group->setTextureCoordinates(textureCoordinates);
	group->setFacesEntities(facesEntities);

	//
	return group;
} 

void GLTFReader::parseNodeChildren(const string& pathName, const tinygltf::Model& gltfModel, const vector<int>& gltfNodeChildrenIdx, Group* parentGroup) {
	for (auto gltfNodeIdx: gltfNodeChildrenIdx) { 
		auto& node = gltfModel.nodes[gltfNodeIdx];
		auto group = parseNode(pathName, gltfModel, gltfNodeIdx, parentGroup->getModel(), parentGroup);
		parentGroup->getModel()->getGroups()[group->getId()] = group;
		parentGroup->getSubGroups()[group->getId()] = group;
		if (node.children.empty() == false) parseNodeChildren(pathName, gltfModel, node.children, group);
	}	
} 

bool GLTFReader::writePNG(const string& pathName, const string& fileName, int bitsPerPixel, int width, int height, const uint8_t* pixels) {
	// see: https://gist.github.com/niw/5963798
	FILE *fp = fopen((pathName + "/" + fileName).c_str(), "wb");
	if (!fp) {
		Console::println("Engine::makeScreenshot(): Failed to create file: " + pathName + "/" + fileName);
		return false;
	}

	png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png) {
		fclose(fp);
		return false;
	}

	png_infop info = png_create_info_struct(png);
	if (!info) {
		fclose(fp);
		return false;
	}

	if (setjmp(png_jmpbuf(png))) {
		fclose(fp);
		return false;
	}

	png_init_io(png, fp);

	auto targetBitsPerPixel = bitsPerPixel;
	png_bytep* row_pointers = new png_bytep[height];
	for (auto y = 0; y < height; y++) row_pointers[y] = (png_bytep)(pixels + 	width * (bitsPerPixel / 8) * (height - 1 - y));
	// try to reduce from 32 bits with alpha to 24 bits without alpha
	if (targetBitsPerPixel == 32) {
		targetBitsPerPixel = 24;
		for (auto y = 0; y < height; y++) {
			for (auto x = 0; x < width / 4; x++) {
				if (row_pointers[y][x * 4 + 3] < 255) {
					targetBitsPerPixel = 32;
					break;
				}
			}
			if (targetBitsPerPixel == 32) break;
		}
	}

	// output is 8bit depth, RGBA format.
	png_set_IHDR(
		png,
		info,
		width,
		height,
		8,
		targetBitsPerPixel == 32?PNG_COLOR_TYPE_RGBA:PNG_COLOR_TYPE_RGB,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT
	);
	png_write_info(png, info);

	// Remove the alpha channel for PNG_COLOR_TYPE_RGB format
	if (bitsPerPixel == 32 && targetBitsPerPixel == 24) {
		png_set_filler(png, 0, PNG_FILLER_AFTER);
	}

	png_write_image(png, row_pointers);
	png_write_end(png, NULL);

	free (row_pointers);

	fclose(fp);

	png_destroy_write_struct(&png, &info);

	return true;
}
