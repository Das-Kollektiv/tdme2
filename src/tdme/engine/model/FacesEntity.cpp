#include <tdme/engine/model/FacesEntity.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Node.h>

using std::string;
using std::vector;

using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Material;
using tdme::engine::model::Node;

FacesEntity::FacesEntity()
{
	this->id = "";
	this->node = nullptr;
	this->material = nullptr;
	this->textureCoordinatesAvailable = false;
	this->tangentBitangentAvailable = false;
	this->lod1Distance = 64.0f;
	this->lod2Distance = 128.0f;
	this->lod3Distance = 192.0f;
}

FacesEntity::FacesEntity(Node* node, const string& id)
{
	this->id = id;
	this->node = node;
	this->material = nullptr;
	this->textureCoordinatesAvailable = false;
	this->tangentBitangentAvailable = false;
	this->lod1Distance = 64.0f;
	this->lod2Distance = 128.0f;
	this->lod3Distance = 192.0f;
}

void FacesEntity::setFaces(const vector<Face>& faces)
{
	this->faces.clear();
	this->faces.resize(faces.size());
	int i = 0;
	for (auto& face: faces) {
		this->faces[i++] = face;
	}
	determineFeatures();
}

void FacesEntity::determineFeatures()
{
	textureCoordinatesAvailable = false;
	tangentBitangentAvailable = false;
	for (auto& face: faces) {
		const auto& textureCoordinateIndices = face.getTextureCoordinateIndices();
		if (textureCoordinateIndices[0] != -1 && textureCoordinateIndices[1] != -1 && textureCoordinateIndices[2] != -1) textureCoordinatesAvailable = true;
		const auto& tangentIndices = face.getTangentIndices();
		const auto& biTangentIndices = face.getBitangentIndices();
		if (tangentIndices[0] != -1 && tangentIndices[1] != -1 && tangentIndices[2] != -1 &&
			biTangentIndices[0] != -1 && biTangentIndices[1] != -1 && biTangentIndices[2] != -1) tangentBitangentAvailable = true;
	}
}

void FacesEntity::setLOD1Indices(const vector<int32_t>& lod1Indices) {
	this->lod1Indices.resize(lod1Indices.size());
	auto i = 0;
	for (auto lod1Index: lod1Indices) {
		this->lod1Indices[i++] = lod1Index;
	}
}

void FacesEntity::setLOD2Indices(const vector<int32_t>& lod2Indices) {
	this->lod2Indices.resize(lod2Indices.size());
	auto i = 0;
	for (auto lod2Index: lod2Indices) {
		this->lod2Indices[i++] = lod2Index;
	}
}

void FacesEntity::setLOD3Indices(const vector<int32_t>& lod3Indices) {
	this->lod3Indices.resize(lod3Indices.size());
	auto i = 0;
	for (auto lod3Index: lod3Indices) {
		this->lod3Indices[i++] = lod3Index;
	}
}

