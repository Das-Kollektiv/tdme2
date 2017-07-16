// Generated from /tdme/src/tdme/engine/model/Group.java
#include <tdme/engine/model/Group.h>

#include <vector>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Arrays.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_HashMap.h>
#include <ObjectArray.h>
#include <SubArray.h>

using std::vector;

using tdme::engine::model::Group;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Arrays;
using tdme::engine::model::Animation;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Model;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::Face, ::java::lang::ObjectArray > FaceArray;
typedef ::SubArray< ::tdme::engine::model::FacesEntity, ::java::lang::ObjectArray > FacesEntityArray;
typedef ::SubArray< ::tdme::engine::model::TextureCoordinate, ::java::lang::ObjectArray > TextureCoordinateArray;
}  // namespace model
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

Group::Group(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Group::Group(Model* model, Group* parentGroup, String* id, String* name) 
	: Group(*static_cast< ::default_init_tag* >(0))
{
	ctor(model,parentGroup,id,name);
}

void Group::ctor(Model* model, Group* parentGroup, String* id, String* name)
{
	super::ctor();
	this->model = model;
	this->parentGroup = parentGroup;
	this->id = id;
	this->name = name;
	this->transformationsMatrix = (new Matrix4x4())->identity();
	this->vertices = new Vector3Array(0);
	this->normals = new Vector3Array(0);
	this->textureCoordinates = nullptr;
	this->tangents = nullptr;
	this->bitangents = nullptr;
	this->animation = nullptr;
	this->skinning = nullptr;
	this->facesEntities = new FacesEntityArray(0);
	this->subGroups = new _HashMap();
}

Model* Group::getModel()
{
	return model;
}

Group* Group::getParentGroup()
{
	return parentGroup;
}

String* Group::getId()
{
	return id;
}

String* Group::getName()
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

Matrix4x4* Group::getTransformationsMatrix()
{
	return transformationsMatrix;
}

void Group::setVertices(const vector<Vector3*>& vertices)
{
	this->vertices = new Vector3Array(vertices.size());
	int i = 0;
	for (Vector3* vertex: vertices) {
		this->vertices->set(i++, vertex);
	}
}

Vector3Array* Group::getVertices()
{
	return vertices;
}

void Group::setVertices(Vector3Array* vertices)
{
	this->vertices = vertices;
}

Vector3Array* Group::getNormals()
{
	return normals;
}

void Group::setNormals(Vector3Array* normals)
{
	this->normals = normals;
}

void Group::setNormals(const vector<Vector3*>& normals)
{
	this->normals = new Vector3Array(normals.size());
	int i = 0;
	for (Vector3* normal: normals) {
		this->normals->set(i++, normal);
	}
}

TextureCoordinateArray* Group::getTextureCoordinates()
{
	return textureCoordinates;
}

void Group::setTextureCoordinates(TextureCoordinateArray* textureCoordinates)
{
	this->textureCoordinates = textureCoordinates;
}

void Group::setTextureCoordinates(const vector<TextureCoordinate*>& textureCoordinates)
{
	this->textureCoordinates = new TextureCoordinateArray(textureCoordinates.size());
	int i = 0;
	for (TextureCoordinate* textureCoordinate: textureCoordinates) {
		this->textureCoordinates->set(i++, textureCoordinate);
	}
}

Vector3Array* Group::getTangents()
{
	return tangents;
}

void Group::setTangents(Vector3Array* tangents)
{
	this->tangents = tangents;
}

void Group::setTangents(_ArrayList* tangents)
{
	this->tangents = java_cast< Vector3Array* >(tangents->toArray(new Vector3Array(tangents->size())));
}

Vector3Array* Group::getBitangents()
{
	return bitangents;
}

void Group::setBitangents(Vector3Array* bitangents)
{
	this->bitangents = bitangents;
}

void Group::setBitangents(_ArrayList* bitangents)
{
	this->bitangents = java_cast< Vector3Array* >(bitangents->toArray(new Vector3Array(bitangents->size())));
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
	for (auto facesEntity : *facesEntities) {
		faceCount += facesEntity->getFaces()->length;
	}
	return faceCount;
}

FacesEntityArray* Group::getFacesEntities()
{
	return facesEntities;
}

void Group::setFacesEntities(const vector<FacesEntity*>& facesEntities)
{
	this->facesEntities = new FacesEntityArray(facesEntities.size());
	int i = 0;
	for (FacesEntity* facesEntity: facesEntities) {
		this->facesEntities->set(i++, facesEntity);
	}
}

void Group::setFacesEntities(FacesEntityArray* facesEntities)
{
	this->facesEntities = facesEntities;
}

_HashMap* Group::getSubGroups()
{
	return subGroups;
}

Group* Group::getSubGroupById(String* groupId)
{
	return java_cast< Group* >(subGroups->get(groupId));
}

void Group::determineFeatures()
{
	for (auto facesEntity : *facesEntities) {
		facesEntity->determineFeatures();
	}
}

String* Group::toString()
{
	return ::java::lang::StringBuilder().append(u"ObjectGroup [id="_j)->append(id)
		->append(u", name="_j)
		->append(name)
		->append(u", faces entities="_j)
		->append(Arrays::toString(static_cast< ObjectArray* >(facesEntities)))
		->append(u", vertices ="_j)
		->append(Arrays::toString(static_cast< ObjectArray* >(vertices)))
		->append(u", normals ="_j)
		->append(Arrays::toString(static_cast< ObjectArray* >(normals)))
		->append(u", texture coordinates ="_j)
		->append(Arrays::toString(static_cast< ObjectArray* >(textureCoordinates)))
		->append(u", tangents ="_j)
		->append(Arrays::toString(static_cast< ObjectArray* >(tangents)))
		->append(u", bitangents ="_j)
		->append(Arrays::toString(static_cast< ObjectArray* >(bitangents)))
		->append(u", subgroups ="_j)
		->append(static_cast< Object* >(subGroups))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Group::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.Group", 23);
    return c;
}

java::lang::Class* Group::getClass0()
{
	return class_();
}

