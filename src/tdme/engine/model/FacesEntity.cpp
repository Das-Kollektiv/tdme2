#include <tdme/engine/model/FacesEntity.h>

#include <vector>
#include <string>

#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/math/Vector3.h>

using std::vector;
using std::string;

using tdme::engine::model::FacesEntity;
using tdme::engine::model::Face;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Vector3;

FacesEntity::FacesEntity()
{
	this->id = "";
	this->group = nullptr;
	this->material = nullptr;
	this->textureCoordinatesAvailable = false;
	this->tangentBitangentAvailable = false;
}

FacesEntity::FacesEntity(Group* group, const string& id)
{
	this->id = id;
	this->group = group;
	this->material = nullptr;
	this->textureCoordinatesAvailable = false;
	this->tangentBitangentAvailable = false;
}

const string& FacesEntity::getId()
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

vector<Face>& FacesEntity::getFaces()
{
	return faces;
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
	textureCoordinatesAvailable = group->getTextureCoordinates().size() > 0;
	tangentBitangentAvailable =
		group->getTangents().size() > 0 && group->getBitangents().size() > 0 &&
		group->getTangents().size() == group->getBitangents().size();
}

bool FacesEntity::isTextureCoordinatesAvailable()
{
	return textureCoordinatesAvailable;
}

bool FacesEntity::isTangentBitangentAvailable()
{
	return tangentBitangentAvailable;
}

