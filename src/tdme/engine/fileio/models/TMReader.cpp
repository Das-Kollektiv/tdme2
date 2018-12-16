#include <tdme/engine/fileio/models/TMReader.h>

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/Color4.h>
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
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::array;
using std::map;
using std::vector;
using std::string;
using std::to_string;
using std::to_string;

using tdme::engine::fileio::models::TMReader;
using tdme::engine::fileio::models::TMReaderInputStream;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Animation;
using tdme::engine::model::Color4;
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
using tdme::engine::primitives::BoundingBox;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;

Model* TMReader::read(const string& pathName, const string& fileName) throw (FileSystemException, ModelFileIOException)
{
	vector<uint8_t> content;
	FileSystem::getInstance()->getContent(pathName, fileName, content);
	TMReaderInputStream is(&content);
	auto fileId = is.readString();
	if (fileId.length() == 0 || fileId != "TDME Model") {
		throw ModelFileIOException(
			"File is not a TDME model file, file id = '" +
			(fileId) +
			"'"
		);
	}
	array<uint8_t, 3> version;
	version[0] = is.readByte();
	version[1] = is.readByte();
	version[2] = is.readByte();
	if ((version[0] != 1 || version[1] != 0 || version[2] != 0) &&
		(version[0] != 1 || version[1] != 9 || version[2] != 9) &&
		(version[0] != 1 || version[1] != 9 || version[2] != 10)) {
		throw ModelFileIOException(
			"Version mismatch, should be 1.0.0, 1.9.9, 1.9.10 but is " +
			to_string(version[0]) +
			"." +
			to_string(version[1]) +
			"." +
			to_string(version[2])
		);
	}
	auto name = is.readString();
	auto upVector = UpVector::valueOf(is.readString());
	auto rotationOrder = RotationOrder::valueOf(is.readString());
	array<float, 3> boundingBoxMinXYZ;
	is.readFloatArray(boundingBoxMinXYZ);
	array<float, 3> boundingBoxMaxXYZ;
	is.readFloatArray(boundingBoxMaxXYZ);
	auto boundingBox = new BoundingBox(Vector3(boundingBoxMinXYZ), Vector3(boundingBoxMaxXYZ));
	auto model = new Model(
		pathName + "/" + fileName,
		fileName,
		upVector,
		rotationOrder,
		boundingBox
	);
	model->setFPS(is.readFloat());
	array<float, 16> importTransformationsMatrixArray;
	is.readFloatArray(importTransformationsMatrixArray);
	model->getImportTransformationsMatrix().set(importTransformationsMatrixArray);
	auto materialCount = is.readInt();
	for (auto i = 0; i < materialCount; i++) {
		auto material = readMaterial(pathName, &is, version);
		(*model->getMaterials())[material->getId()] = material;
	}
	readSubGroups(&is, model, nullptr, model->getSubGroups());
	auto animationSetupCount = is.readInt();
	for (auto i = 0; i < animationSetupCount; i++) {
		readAnimationSetup(&is, model);
	}
	if (model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT) == nullptr) {
		model->addAnimationSetup(Model::ANIMATIONSETUP_DEFAULT, 0, 0, true);
	}
	return model;
}

const string TMReader::getTexturePath(const string& modelPathName, const string& texturePathName, const string& textureFileName) {
	if (FileSystem::getInstance()->fileExists(texturePathName + "/" + textureFileName) == true) {
		return texturePathName;
	} else
	if (FileSystem::getInstance()->fileExists(modelPathName + "/" + textureFileName) == true) {
		return modelPathName;
	} else
	if (FileSystem::getInstance()->fileExists(FileSystem::getInstance()->getPathName(modelPathName) + "/" + textureFileName) == true) {
		return FileSystem::getInstance()->getPathName(modelPathName);
	} else {
		return texturePathName;
	}
}

Material* TMReader::readMaterial(const string& pathName, TMReaderInputStream* is, const array<uint8_t, 3>& version) throw (ModelFileIOException)
{
	auto id = is->readString();
	auto m = new Material(id);
	array<float, 4> colorRGBAArray;
	is->readFloatArray(colorRGBAArray);
	m->setAmbientColor(Color4(colorRGBAArray));
	is->readFloatArray(colorRGBAArray);
	m->setDiffuseColor(Color4(colorRGBAArray));
	is->readFloatArray(colorRGBAArray);
	m->setSpecularColor(Color4(colorRGBAArray));
	is->readFloatArray(colorRGBAArray);
	m->setEmissionColor(Color4(colorRGBAArray));
	m->setShininess(is->readFloat());
	auto diffuseTexturePathName = is->readString();
	auto diffuseTextureFileName = is->readString();
	auto diffuseTransparencyTexturePathName = is->readString();
	auto diffuseTransparencyTextureFileName = is->readString();
	if (diffuseTextureFileName.size() != 0) {
		m->setDiffuseTexture(
			getTexturePath(pathName, diffuseTexturePathName, diffuseTextureFileName),
			diffuseTextureFileName,
			getTexturePath(pathName, diffuseTransparencyTexturePathName, diffuseTransparencyTextureFileName),
			diffuseTransparencyTextureFileName
		);
	}
	auto specularTexturePathName = is->readString();
	auto specularTextureFileName = is->readString();
	if (specularTextureFileName.size() != 0) {
		m->setSpecularTexture(
			getTexturePath(pathName, specularTexturePathName, specularTextureFileName),
			specularTextureFileName
		);
	}
	auto normalTexturePathName = is->readString();
	auto normalTextureFileName = is->readString();
	if (normalTextureFileName.size() != 0) {
		m->setNormalTexture(
			getTexturePath(pathName, normalTexturePathName, normalTextureFileName),
			normalTextureFileName
		);
	}
	auto displacementTexturePathName = is->readString();
	auto displacementTextureFileName = is->readString();
	if (displacementTextureFileName.size() != 0) {
		m->setDisplacementTexture(
			getTexturePath(pathName, displacementTexturePathName, displacementTextureFileName),
			displacementTextureFileName
		);
	}
	m->setDiffuseTextureMaskedTransparency(is->readBoolean());
	if ((version[0] == 1 && version[1] == 9 && version[2] == 9) ||
		(version[0] == 1 && version[1] == 9 && version[2] == 10)) {
		m->setDiffuseTextureMaskedTransparencyThreshold(is->readFloat());
	}
	if ((version[0] == 1 && version[1] == 9 && version[2] == 10)) {
		array<float, 9> textureMatrix;
		is->readFloatArray(textureMatrix);
		m->setTextureMatrix(Matrix2D3x3(textureMatrix));
	}
	return m;
}

void TMReader::readAnimationSetup(TMReaderInputStream* is, Model* model) throw (ModelFileIOException) {
	auto id = is->readString();
	auto overlayFromGroupId = is->readString();
	auto startFrame = is->readInt();
	auto endFrame = is->readInt();
	auto loop = is->readBoolean();
	if (overlayFromGroupId.length() == 0) {
		model->addAnimationSetup(id, startFrame, endFrame, loop);
	} else {
		model->addOverlayAnimationSetup(id, overlayFromGroupId, startFrame, endFrame, loop);
	}
}

const vector<Vector3> TMReader::readVertices(TMReaderInputStream* is) throw (ModelFileIOException)
{
	vector<Vector3> v;
	array<float, 3> vXYZ;
	if (is->readBoolean() == true) {
		v.resize(is->readInt());
		for (auto i = 0; i < v.size(); i++) {
			is->readFloatArray(vXYZ);
			v[i].set(vXYZ);
		}
	}
	return v;
}

const vector<TextureCoordinate> TMReader::readTextureCoordinates(TMReaderInputStream* is) throw (ModelFileIOException)
{
	array<float, 2> tcUV;
	vector<TextureCoordinate> tc;
	if (is->readBoolean() == true) {
		tc.resize(is->readInt());
		for (auto i = 0; i < tc.size(); i++) {
			is->readFloatArray(tcUV);
			tc[i] = TextureCoordinate(tcUV);
		}
	}
	return tc;
}

bool TMReader::readIndices(TMReaderInputStream* is, array<int32_t, 3>* indices) throw (ModelFileIOException)
{
	if (is->readBoolean() == false) {
		return false;
	} else {
		auto length = is->readInt();
		if (length != indices->size()) {
			throw ModelFileIOException("Wrong indices array size");
		}
		for (auto i = 0; i < indices->size(); i++) {
			(*indices)[i] = is->readInt();
		}
		return true;
	}
}

Animation* TMReader::readAnimation(TMReaderInputStream* is, Group* g) throw (ModelFileIOException)
{
	if (is->readBoolean() == false) {
		return nullptr;
	} else {
		array<float, 16> matrixArray;
		g->createAnimation(is->readInt());
		for (auto i = 0; i < g->getAnimation()->getTransformationsMatrices()->size(); i++) {
			is->readFloatArray(matrixArray);
			(*g->getAnimation()->getTransformationsMatrices())[i].set(matrixArray);
		}
		return g->getAnimation();
	}
}

void TMReader::readFacesEntities(TMReaderInputStream* is, Group* g) throw (ModelFileIOException)
{
	vector<FacesEntity> facesEntities;
	facesEntities.resize(is->readInt());
	for (auto i = 0; i < facesEntities.size(); i++) {
		facesEntities[i] = FacesEntity(g, is->readString());
		if (is->readBoolean() == true) {
			Material* material = nullptr;
			auto materialIt = g->getModel()->getMaterials()->find(is->readString());
			if (materialIt != g->getModel()->getMaterials()->end()) {
				material = materialIt->second;
			}
			facesEntities[i].setMaterial(material);
		}
		vector<Face> faces;
		faces.resize(is->readInt());
		array<int32_t,3> vertexIndices;
		array<int32_t,3> normalIndices;
		array<int32_t,3> textureCoordinateIndices;
		array<int32_t,3> tangentIndices;
		array<int32_t,3> bitangentIndices;
		bool haveTextureCoordinateIndices;
		bool haveTangentIndices;
		bool haveBitangentIndices;
		for (auto j = 0; j < faces.size(); j++) {
			readIndices(is, &vertexIndices);
			readIndices(is, &normalIndices);
			haveTextureCoordinateIndices = readIndices(is, &textureCoordinateIndices);
			haveTangentIndices = readIndices(is, &tangentIndices);
			haveBitangentIndices = readIndices(is, &bitangentIndices);
			faces[j] = Face(g,
				vertexIndices[0], vertexIndices[1], vertexIndices[2],
				normalIndices[0], normalIndices[1], normalIndices[2]
			);
			if (haveTextureCoordinateIndices == true) {
				faces[j].setTextureCoordinateIndices(
					textureCoordinateIndices[0], textureCoordinateIndices[1], textureCoordinateIndices[2]
				);
			}
			if (haveTangentIndices == true && haveBitangentIndices == true) {
				faces[j].setTangentIndices(tangentIndices[0], tangentIndices[1], tangentIndices[2]);
				faces[j].setBitangentIndices(bitangentIndices[0], bitangentIndices[1], bitangentIndices[2]);
			}
		}
		facesEntities[i].setFaces(&faces);
	}
	g->setFacesEntities(facesEntities);
}

Joint TMReader::readSkinningJoint(TMReaderInputStream* is) throw (ModelFileIOException)
{
	array<float, 16> matrixArray;
	Joint joint(is->readString());
	is->readFloatArray(matrixArray);
	joint.getBindMatrix().set(matrixArray);
	return joint;
}

JointWeight TMReader::readSkinningJointWeight(TMReaderInputStream* is) throw (ModelFileIOException)
{

	int32_t jointIndex = is->readInt();
	int32_t weightIndex = is->readInt();
	return JointWeight(jointIndex, weightIndex);
}

void TMReader::readSkinning(TMReaderInputStream* is, Group* g) throw (ModelFileIOException)
{
	if (is->readBoolean() == true) {
		auto skinning = g->createSkinning();
		skinning->setWeights(is->readFloatVector());
		vector<Joint> joints;
		joints.resize(is->readInt());
		for (auto i = 0; i < joints.size(); i++) {
			joints[i] = readSkinningJoint(is);
		}
		skinning->setJoints(joints);
		vector<vector<JointWeight>> verticesJointsWeight;
		verticesJointsWeight.resize(is->readInt());
		for (auto i = 0; i < verticesJointsWeight.size(); i++) {
			verticesJointsWeight[i].resize(is->readInt());
			for (auto j = 0; j < verticesJointsWeight[i].size(); j++) {
				verticesJointsWeight[i][j] = readSkinningJointWeight(is);
			}
		}
		skinning->setVerticesJointsWeights(verticesJointsWeight);
	}
}

void TMReader::readSubGroups(TMReaderInputStream* is, Model* model, Group* parentGroup, map<string, Group*>* subGroups) throw (ModelFileIOException)
{
	auto subGroupCount = is->readInt();
	for (auto i = 0; i < subGroupCount; i++) {
		auto subGroup = readGroup(is, model, parentGroup);
		(*subGroups)[subGroup->getId()] = subGroup;
		(*model->getGroups())[subGroup->getId()] = subGroup;
	}
}

Group* TMReader::readGroup(TMReaderInputStream* is, Model* model, Group* parentGroup) throw (ModelFileIOException)
{

	auto groupId = is->readString();
	auto groupName = is->readString();
	auto group = new Group(model, parentGroup, groupId, groupName);
	group->setJoint(is->readBoolean());
	array<float, 16> matrixArray;
	is->readFloatArray(matrixArray);
	group->getTransformationsMatrix().set(matrixArray);
	vector<Vector3> vertices = readVertices(is);
	group->setVertices(vertices);
	vector<Vector3> normals = readVertices(is);
	group->setNormals(normals);
	vector<TextureCoordinate> textureCoordinates = readTextureCoordinates(is);
	group->setTextureCoordinates(textureCoordinates);
	vector<Vector3> tangents = readVertices(is);
	group->setTangents(tangents);
	vector<Vector3> bitangents = readVertices(is);
	group->setBitangents(bitangents);
	readAnimation(is, group);
	readSkinning(is, group);
	readFacesEntities(is, group);
	group->determineFeatures();
	readSubGroups(is, model, parentGroup, group->getSubGroups());
	return group;
}
