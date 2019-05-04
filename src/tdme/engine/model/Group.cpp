#include <tdme/engine/model/Group.h>

#include <map>
#include <string>
#include <vector>

#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::map;
using std::vector;
using std::string;

using tdme::engine::model::Group;
using tdme::engine::model::Animation;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Model;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

Group::Group(Model* model, Group* parentGroup, const string& id, const string& name)
{
	this->model = model;
	this->parentGroup = parentGroup;
	this->id = id;
	this->name = name;
	this->transformationsMatrix.identity();
	this->animation = nullptr;
	this->skinning = nullptr;
	this->isJoint_ = false;
}

Group::~Group() {
	if (animation != nullptr) delete animation;
	if (skinning != nullptr) delete skinning;
}

Model* Group::getModel()
{
	return model;
}

Group* Group::getParentGroup()
{
	return parentGroup;
}

const string& Group::getId()
{
	return id;
}

const string& Group::getName()
{
	return name;
}

bool Group::isJoint()
{
	return isJoint_;
}

void Group::setJoint(bool isJoint)
{
	this->isJoint_ = isJoint;
}

Matrix4x4& Group::getTransformationsMatrix()
{
	return transformationsMatrix;
}

vector<Vector3>& Group::getVertices()
{
	return vertices;
}

void Group::setVertices(const vector<Vector3>& vertices)
{
	this->vertices.resize(vertices.size());
	int i = 0;
	for (auto& vertex: vertices) {
		this->vertices[i++] = vertex;
	}
}

vector<Vector3>& Group::getNormals()
{
	return normals;
}

void Group::setNormals(const vector<Vector3>& normals)
{
	this->normals.resize(normals.size());
	int i = 0;
	for (auto& normal: normals) {
		this->normals[i++] = normal;
	}
}

vector<TextureCoordinate>& Group::getTextureCoordinates()
{
	return textureCoordinates;
}

void Group::setTextureCoordinates(const vector<TextureCoordinate>& textureCoordinates)
{
	this->textureCoordinates.resize(textureCoordinates.size());
	int i = 0;
	for (auto& textureCoordinate: textureCoordinates) {
		this->textureCoordinates[i++] = textureCoordinate;
	}
}

vector<Vector3>& Group::getTangents()
{
	return tangents;
}

void Group::setTangents(const vector<Vector3>& tangents)
{
	this->tangents.resize(tangents.size());
	int i = 0;
	for (auto& tangent: tangents) {
		this->tangents[i++] = tangent;
	}
}

vector<Vector3>& Group::getBitangents()
{
	return bitangents;
}

void Group::setBitangents(const vector<Vector3>& bitangents)
{
	this->bitangents.resize(bitangents.size());
	int i = 0;
	for (auto& bitangent: bitangents) {
		this->bitangents[i++] = bitangent;
	}
}

Animation* Group::getAnimation()
{
	return animation;
}

Animation* Group::createAnimation(int32_t frames)
{
	animation = new Animation(frames);
	return animation;
}

Skinning* Group::getSkinning()
{
	return skinning;
}

Skinning* Group::createSkinning()
{
	skinning = new Skinning();
	model->setHasSkinning(true);
	return skinning;
}

int32_t Group::getFaceCount()
{
	auto faceCount = 0;
	for (auto& facesEntity : facesEntities) {
		faceCount += facesEntity.getFaces().size();
	}
	return faceCount;
}

vector<FacesEntity>& Group::getFacesEntities()
{
	return facesEntities;
}

void Group::setFacesEntities(const vector<FacesEntity>& facesEntities)
{
	this->facesEntities.resize(facesEntities.size());
	int i = 0;
	for (auto& facesEntity: facesEntities) {
		this->facesEntities[i++] = facesEntity;
	}
}

map<string, Group*>* Group::getSubGroups()
{
	return &subGroups;
}

Group* Group::getSubGroupById(const string& groupId)
{
	auto groupIt = subGroups.find(groupId);
	if (groupIt != subGroups.end()) {
		return groupIt->second;
	}
	return nullptr;
}

void Group::determineFeatures()
{
	for (auto& facesEntity : facesEntities) {
		facesEntity.determineFeatures();
	}
}
