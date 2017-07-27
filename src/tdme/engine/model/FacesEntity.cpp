// Generated from /tdme/src/tdme/engine/model/FacesEntity.java
#include <tdme/engine/model/FacesEntity.h>

#include <vector>
#include <string>

#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Material.h>

using std::vector;
using std::wstring;

using tdme::engine::model::FacesEntity;
using tdme::engine::model::Face;
using tdme::engine::model::Group;
using tdme::engine::model::Material;

FacesEntity::FacesEntity()
{
	this->id = L"";
	this->group = group;
	this->material = nullptr;
	this->textureCoordinatesAvailable = false;
	this->tangentBitangentAvailable = false;
}

FacesEntity::FacesEntity(Group* group, const wstring& id)
{
	this->id = id;
	this->group = group;
	this->material = nullptr;
	this->textureCoordinatesAvailable = false;
	this->tangentBitangentAvailable = false;
}

const wstring& FacesEntity::getId()
{
	return id;
}

void FacesEntity::setMaterial(Material* material)
{
	this->material = material;
}

Material* FacesEntity::getMaterial()
{
	return material;
}

vector<Face>* FacesEntity::getFaces()
{
	return &faces;
}

void FacesEntity::setFaces(const vector<Face>* faces)
{
	this->faces.clear();
	this->faces.resize(faces->size());
	int i = 0;
	for (auto& face: *faces) {
		this->faces[i++] = face;
	}
	this->textureCoordinatesAvailable = false;
	this->tangentBitangentAvailable = false;
}

void FacesEntity::determineFeatures()
{
	textureCoordinatesAvailable = true;
	tangentBitangentAvailable = true;
	for (auto& face : faces) {
		if (face.getTangentIndices() == nullptr || face.getBitangentIndices() == nullptr) {
			tangentBitangentAvailable = false;
		}
		if (face.getTextureCoordinateIndices() == nullptr) {
			textureCoordinatesAvailable = false;
		}
	}
}

bool FacesEntity::isTextureCoordinatesAvailable()
{
	return textureCoordinatesAvailable;
}

bool FacesEntity::isTangentBitangentAvailable()
{
	return tangentBitangentAvailable;
}

