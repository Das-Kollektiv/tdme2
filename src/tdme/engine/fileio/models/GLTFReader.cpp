#include <tdme/engine/fileio/models/GLTFReader.h>

#include <string>

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
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

#include <ext/tinyxml/tinyxml.h>

using std::to_string;
using std::string;

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

	for (auto& gltfScene: gltfModel.scenes) {
		for (auto gltfNodeIdx: gltfScene.nodes) { 
			auto& node = gltfModel.nodes[gltfNodeIdx]; 
			auto group = parseNode(gltfModel, gltfNodeIdx, model, nullptr);
			model->getGroups()[group->getId()] = group;
			model->getSubGroups()[group->getId()] = group;
			if (node.children.empty() == false) parseNodeChildren(gltfModel, node.children, group);
		}	
	} 

	// create default animations
	if (ModelHelper::hasDefaultAnimation(model) == false) ModelHelper::createDefaultAnimation(model, 0);
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

Group* GLTFReader::parseNode(const tinygltf::Model& gltfModel, int gltfNodeIdx, Model* model, Group* parentGroup) {
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
		Console::println("GLTFReader::parseNode(): " + group->getId() + ": Invalid matrix with " + to_string(gltfNode.matrix.size()) + " elements");
	} 	
	if (gltfNode.mesh == -1) return group;
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
							if (writePNG(".", fileName, image.component == 3?24:32, image.width, image.height, (const uint8_t*)image.image.data()) == false) {
								Console::println("GLTFReader::parseNode(): " + group->getId() + ": An error occurred: Could not write PNG: " + fileName);
							}
							material->setDiffuseTexture(".", fileName);
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
			switch (getComponentTypeByteSize(indicesAccessor.componentType)) {
				case 2:	
					{
						// TODO: stride
						const uint16_t* indicesBufferData = (const uint16_t*)(indicesBuffer.data.data() + indicesBufferView.byteOffset);
						for (auto i = 0; i < indicesAccessor.count; i++) {
							indices.push_back(indicesBufferData[i]);
						}
						break;
					} 
				case 4:	
					{
						// TODO: stride
						const uint32_t* indicesBufferData = (const uint32_t*)(indicesBuffer.data.data() + indicesBufferView.byteOffset);
						for (auto i = 0; i < indicesAccessor.count; i++) {
							indices.push_back(indicesBufferData[i]);
						}
						break;
					} 
				default:
					Console::println("GLTFReader::parseNode(): " + group->getId() + ": Invalid indices component size: " + to_string(getComponentTypeByteSize(indicesAccessor.componentType)));
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
			if (getComponentTypeByteSize(attributeAccessor.componentType) != 4) {
				Console::println("GLTFReader::parseNode(): " + group->getId() + ": Invalid attributes component size: " + to_string(getComponentTypeByteSize(attributeAccessor.componentType)));
				continue;
			} 
			if (attributeBufferView.byteStride != 0) {
				Console::println("GLTFReader::parseNode(): " + group->getId() + ": Invalid attributes stride: " + to_string(attributeBufferView.byteStride));
			} else {
				const float* bufferData = (const float*)(attributeBuffer.data.data() + attributeBufferView.byteOffset);
				if (gltfBufferType == "POSITION") {
					haveVertices = true;
					start = vertices.size();
					if (start + attributeAccessor.count > vertices.size()) vertices.resize(start + attributeAccessor.count);
					for (auto i = 0; i < attributeAccessor.count; i++) {
						vertices[start + i] = Vector3(bufferData[i * 3 + 0], bufferData[i * 3 + 1], bufferData[i * 3 + 2]);
					}
				} else
				if (gltfBufferType == "NORMAL") {
					haveNormals = true;
					start = normals.size();
					if (start + attributeAccessor.count > normals.size()) normals.resize(start + attributeAccessor.count);
					for (auto i = 0; i < attributeAccessor.count; i++) {
						normals[start + i] = Vector3(bufferData[i * 3 + 0], bufferData[i * 3 + 1], bufferData[i * 3 + 2]);
					}
				} else
				if (gltfBufferType == "TEXCOORD_0") {
					haveTextureCoordinates = true;
					start = textureCoordinates.size();
					if (start + attributeAccessor.count > textureCoordinates.size()) textureCoordinates.resize(start + attributeAccessor.count);
					for (auto i = 0; i < attributeAccessor.count; i++) {
						textureCoordinates[start + i] = TextureCoordinate(bufferData[i * 2 + 0], bufferData[i * 2 + 1]);
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

	// set up group
	group->setVertices(vertices);
	group->setNormals(normals);
	group->setTextureCoordinates(textureCoordinates);
	group->setFacesEntities(facesEntities);

	//
	return group;
} 

void GLTFReader::parseNodeChildren(const tinygltf::Model& gltfModel, const vector<int>& gltfNodeChildrenIdx, Group* parentGroup) {
	for (auto gltfNodeIdx: gltfNodeChildrenIdx) { 
		auto& node = gltfModel.nodes[gltfNodeIdx];
		auto group = parseNode(gltfModel, gltfNodeIdx, parentGroup->getModel(), parentGroup);
		parentGroup->getModel()->getGroups()[group->getId()] = group;
		parentGroup->getModel()->getSubGroups()[group->getId()] = group;
		if (node.children.empty() == false) parseNodeChildren(gltfModel, node.children, group);
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

	// output is 8bit depth, RGBA format.
	png_set_IHDR(
		png,
		info,
		width,
		height,
		8,
		bitsPerPixel == 32?PNG_COLOR_TYPE_RGBA:PNG_COLOR_TYPE_RGB,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT
	);
	png_write_info(png, info);

	// Remove the alpha channel for PNG_COLOR_TYPE_RGB format
	// png_set_filler(png, 0, PNG_FILLER_AFTER);

	png_bytep* row_pointers = new png_bytep[height];
	for (auto y = 0; y < height; y++) row_pointers[y] = (png_bytep)(pixels + 	width * (bitsPerPixel / 8) * (height - 1 - y));

	png_write_image(png, row_pointers);
	png_write_end(png, NULL);

	free (row_pointers);

	fclose(fp);

	png_destroy_write_struct(&png, &info);

	return true;
}
