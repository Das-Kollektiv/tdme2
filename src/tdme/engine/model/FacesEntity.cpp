// Generated from /tdme/src/tdme/engine/model/FacesEntity.java
#include <tdme/engine/model/FacesEntity.h>

#include <vector>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Arrays.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Material.h>
#include <tdme/utils/_ArrayList.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using std::vector;

using tdme::engine::model::FacesEntity;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Arrays;
using tdme::engine::model::Face;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::utils::_ArrayList;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::Face, ::java::lang::ObjectArray > FaceArray;
}  // namespace model
}  // namespace engine
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

FacesEntity::FacesEntity(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

FacesEntity::FacesEntity(Group* group, String* id) 
	: FacesEntity(*static_cast< ::default_init_tag* >(0))
{
	ctor(group,id);
}

void FacesEntity::ctor(Group* group, String* id)
{
	super::ctor();
	this->id = id;
	this->group = group;
	this->material = nullptr;
	this->faces = new FaceArray(0);
	this->textureCoordinatesAvailable = false;
	this->tangentBitangentAvailable = false;
}

String* FacesEntity::getId()
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

FaceArray* FacesEntity::getFaces()
{
	return faces;
}

void FacesEntity::setFaces(const vector<Face*>& faces)
{
	this->faces = new FaceArray(faces.size());
	int i = 0;
	for (Face* face: faces) {
		this->faces->set(i++, face);
	}
	this->textureCoordinatesAvailable = false;
	this->tangentBitangentAvailable = false;
}

void FacesEntity::setFaces(FaceArray* faces)
{
	this->faces = faces;
	this->textureCoordinatesAvailable = false;
	this->tangentBitangentAvailable = false;
}

void FacesEntity::determineFeatures()
{
	textureCoordinatesAvailable = true;
	tangentBitangentAvailable = true;
	for (auto face : *this->faces) {
		if (face->getTangentIndices() == nullptr || face->getBitangentIndices() == nullptr) {
			tangentBitangentAvailable = false;
		}
		if (face->getTextureCoordinateIndices() == nullptr) {
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

String* FacesEntity::toString()
{
	return ::java::lang::StringBuilder().append(u"FacesEntity [id="_j)->append(id)
		->append(u", group="_j)
		->append(group->getName())
		->append(u", material="_j)
		->append(static_cast< Object* >(material))
		->append(u", faces="_j)
		->append(Arrays::toString(static_cast< ObjectArray* >(faces)))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* FacesEntity::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.FacesEntity", 29);
    return c;
}

java::lang::Class* FacesEntity::getClass0()
{
	return class_();
}

