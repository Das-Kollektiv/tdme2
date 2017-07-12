// Generated from /tdme/src/tdme/engine/fileio/models/WFObjReader.java
#include <tdme/engine/fileio/models/WFObjReader.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/CharSequence.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Comparable.h>
#include <java/lang/String.h>
#include <java/lang/Float.h>
#include <java/lang/Integer.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/StringTokenizer.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model_UpVector.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_HashMap.h>
#include <ObjectArray.h>
#include <SubArray.h>

using tdme::engine::fileio::models::WFObjReader;
using java::io::BufferedReader;
using java::io::DataInputStream;
using java::io::File;
using java::io::InputStreamReader;
using java::lang::ArrayStoreException;
using java::lang::ClassCastException;
using java::lang::Float;
using java::lang::Integer;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::StringTokenizer;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::engine::model::Model_UpVector;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Vector3;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

namespace
{
template<typename F>
struct finally_
{
    finally_(F f) : f(f), moved(false) { }
    finally_(finally_ &&x) : f(x.f), moved(false) { x.moved = true; }
    ~finally_() { if(!moved) f(); }
private:
    finally_(const finally_&); finally_& operator=(const finally_&);
    F f;
    bool moved;
};

template<typename F> finally_<F> finally(F f) { return finally_<F>(f); }
}
WFObjReader::WFObjReader(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

WFObjReader::WFObjReader()
	: WFObjReader(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Model* WFObjReader::read(String* pathName, String* fileName) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	auto model = new Model(
		::java::lang::StringBuilder().
		 	 append(pathName)->
			 append(u"/"_j)->
			 append(fileName)->
			 toString(),
		fileName,
		Model_UpVector::Y_UP,
		RotationOrder::XYZ,
		nullptr
	);
	auto vertices = new _ArrayList();
	auto textureCoordinates = new _ArrayList();
	auto materials = model->getMaterials();
	auto subGroups = model->getSubGroups();
	auto groups = model->getGroups();
	Group* group = nullptr;
	_HashMap* modelGroupVerticesMapping = nullptr;
	_HashMap* modelGroupTextureCoordinatesMapping = nullptr;
	_ArrayList* groupFacesEntityFaces = nullptr;
	_ArrayList* groupVertices = nullptr;
	_ArrayList* groupNormals = nullptr;
	_ArrayList* groupTextureCoordinates = nullptr;
	_ArrayList* groupFacesEntities = nullptr;
	FacesEntity* groupFacesEntity = nullptr;
	StringArray* lines = nullptr;
	{
		auto finally0 = finally([&] {
			if (lines != nullptr) delete lines;
		});
		{
			lines = _FileSystem::getInstance()->getContentAsStringArray(pathName, fileName);
			String* line;
			for (int lineIdx = 0; lineIdx < lines->length; lineIdx++) {
				line = lines->get(lineIdx)->trim();
				if (line->startsWith(u"#"_j)) {
					continue;
				}
				auto commandEndIdx = line->indexOf(static_cast< int32_t >(u' '));
				if (commandEndIdx == -1)
					commandEndIdx = line->length();

				auto command = line->substring(0, commandEndIdx)->trim()->toLowerCase();
				auto arguments = command->length() + 1 > line->length() ? u""_j : line->substring(command->length() + 1);
				if (command->equals(u"mtllib"_j)) {
					auto materialFileName = arguments;
					materials = WFObjReader::readMaterials(pathName, materialFileName);
				} else
				if (command->equals(u"v"_j)) {
					auto t = new StringTokenizer(arguments, u" "_j);
					auto x = Float::parseFloat(t->nextToken());
					auto y = Float::parseFloat(t->nextToken());
					auto z = Float::parseFloat(t->nextToken());
					vertices->add(new Vector3(x, y, z));
				} else
				if (command->equals(u"vt"_j)) {
					auto t = new StringTokenizer(arguments, u" "_j);
					auto u = Float::parseFloat(t->nextToken());
					auto v = Float::parseFloat(t->nextToken());
					textureCoordinates->add(new TextureCoordinate(u, v));
				} else
				if (command->equals(u"f"_j)) {
					StringTokenizer* t2;
					auto t = new StringTokenizer(arguments, u" "_j);
					auto v0 = -1;
					auto v1 = -1;
					auto v2 = -1;
					auto vt0 = -1;
					auto vt1 = -1;
					auto vt2 = -1;
					t2 = new StringTokenizer(t->nextToken(), u"/"_j);
					v0 = Integer::parseInt(t2->nextToken()) - 1;
					if (t2->hasMoreTokens()) {
						vt0 = Integer::parseInt(t2->nextToken()) - 1;
					}
					t2 = new StringTokenizer(t->nextToken(), u"/"_j);
					v1 = Integer::parseInt(t2->nextToken()) - 1;
					if (t2->hasMoreTokens()) {
						vt1 = Integer::parseInt(t2->nextToken()) - 1;
					}
					t2 = new StringTokenizer(t->nextToken(), u"/"_j);
					v2 = Integer::parseInt(t2->nextToken()) - 1;
					if (t2->hasMoreTokens()) {
						vt2 = Integer::parseInt(t2->nextToken()) - 1;
					}
					if (t->hasMoreTokens()) {
						throw new ModelFileIOException(u"We only support triangulated meshes"_j);
					}
					Integer* mappedVertex = nullptr;
					mappedVertex = java_cast< Integer* >(modelGroupVerticesMapping->get(Integer::valueOf(v0)));
					if (mappedVertex == nullptr) {
						groupVertices->add(java_cast< Vector3* >(vertices->get(v0))->clone());
						v0 = groupVertices->size() - 1;
					} else {
						v0 = mappedVertex->intValue();
					}
					mappedVertex = java_cast< Integer* >(modelGroupVerticesMapping->get(Integer::valueOf(v1)));
					if (mappedVertex == nullptr) {
						groupVertices->add(java_cast< Vector3* >(vertices->get(v1))->clone());
						v1 = groupVertices->size() - 1;
					} else {
						v1 = mappedVertex->intValue();
					}
					mappedVertex = java_cast< Integer* >(modelGroupVerticesMapping->get(Integer::valueOf(v2)));
					if (mappedVertex == nullptr) {
						groupVertices->add(java_cast< Vector3* >(vertices->get(v2))->clone());
						v2 = groupVertices->size() - 1;
					} else {
						v2 = mappedVertex->intValue();
					}
					Integer* mappedTextureCoordinate = nullptr;
					mappedTextureCoordinate = java_cast< Integer* >(modelGroupTextureCoordinatesMapping->get(Integer::valueOf(vt0)));
					if (mappedTextureCoordinate == nullptr) {
						groupTextureCoordinates->add(java_cast< TextureCoordinate* >(textureCoordinates->get(vt0))->clone());
						vt0 = groupTextureCoordinates->size() - 1;
					} else {
						vt0 = mappedTextureCoordinate->intValue();
					}
					mappedTextureCoordinate = java_cast< Integer* >(modelGroupTextureCoordinatesMapping->get(Integer::valueOf(vt1)));
					if (mappedTextureCoordinate == nullptr) {
						groupTextureCoordinates->add(java_cast< TextureCoordinate* >(textureCoordinates->get(vt1))->clone());
						vt1 = groupTextureCoordinates->size() - 1;
					} else {
						vt1 = mappedTextureCoordinate->intValue();
					}
					mappedTextureCoordinate = java_cast< Integer* >(modelGroupTextureCoordinatesMapping->get(Integer::valueOf(vt2)));
					if (mappedTextureCoordinate == nullptr) {
						groupTextureCoordinates->add(java_cast< TextureCoordinate* >(textureCoordinates->get(vt2))->clone());
						vt2 = groupTextureCoordinates->size() - 1;
					} else {
						vt2 = mappedTextureCoordinate->intValue();
					}
					auto faceVertexNormals = ModelHelper::computeNormals(new Vector3Array({
						java_cast< Vector3* >(groupVertices->get(v0)),
						java_cast< Vector3* >(groupVertices->get(v1)),
						java_cast< Vector3* >(groupVertices->get(v2))
					}));
					auto n0 = groupNormals->size();
					groupNormals->add((*faceVertexNormals)[0]);
					auto n1 = groupNormals->size();
					groupNormals->add((*faceVertexNormals)[1]);
					auto n2 = groupNormals->size();
					groupNormals->add((*faceVertexNormals)[2]);
					auto face = new Face(group, v0, v1, v2, n0, n1, n2);
					if (vt0 != -1 && vt1 != -1 && vt2 != -1) {
						face->setTextureCoordinateIndices(vt0, vt1, vt2);
					}
					groupFacesEntityFaces->add(face);
				} else
				if (command->equals(u"g"_j)) {
					if (group != nullptr) {
						if (groupFacesEntityFaces->isEmpty() == false) {
							groupFacesEntity->setFaces(groupFacesEntityFaces);
							groupFacesEntities->add(groupFacesEntity);
						}
						group->setVertices(groupVertices);
						group->setNormals(groupNormals);
						group->setTextureCoordinates(groupTextureCoordinates);
						group->setFacesEntities(groupFacesEntities);
						group->determineFeatures();
					}
					auto t = new StringTokenizer(arguments, u" "_j);
					auto name = t->nextToken();
					groupVertices = new _ArrayList();
					groupNormals = new _ArrayList();
					groupTextureCoordinates = new _ArrayList();
					groupFacesEntityFaces = new _ArrayList();
					group = new Group(model, nullptr, name, name);
					groupFacesEntity = new FacesEntity(group, name);
					groupFacesEntities = new _ArrayList();
					modelGroupVerticesMapping = new _HashMap();
					modelGroupTextureCoordinatesMapping = new _HashMap();
					subGroups->put(name, group);
					groups->put(name, group);
				} else
				if (command->equals(u"usemtl"_j)) {
					if (group != nullptr) {
						if (groupFacesEntityFaces->isEmpty() == false) {
							groupFacesEntity->setFaces(groupFacesEntityFaces);
							groupFacesEntities->add(groupFacesEntity);
						}
						groupFacesEntity = new FacesEntity(group, ::java::lang::StringBuilder().append(u"#"_j)->append(groupFacesEntities->size())->toString());
						groupFacesEntityFaces = new _ArrayList();
					}
					groupFacesEntity->setMaterial(java_cast< Material* >(materials->get(arguments)));
				} else {
				}
			}
			if (group != nullptr) {
				if (groupFacesEntityFaces->isEmpty() == false) {
					groupFacesEntity->setFaces(groupFacesEntityFaces);
					groupFacesEntities->add(groupFacesEntity);
				}
				group->setVertices(groupVertices);
				group->setNormals(groupNormals);
				group->setTextureCoordinates(groupTextureCoordinates);
				group->setFacesEntities(groupFacesEntities);
				group->determineFeatures();
			}
		}
	}

	ModelHelper::prepareForIndexedRendering(model);
	return model;
}

_HashMap* WFObjReader::readMaterials(String* pathName, String* fileName) /* throws(IOException) */
{
	clinit();
	auto materials = new _HashMap();
	Material* current = nullptr;
	String* line;
	auto alpha = 1.0f;
	StringArray* lines = nullptr;
	{
		auto finally0 = finally([&] {
			if (lines != nullptr) delete lines;
		});
		lines = _FileSystem::getInstance()->getContentAsStringArray(pathName, fileName);
		String* line;
		for (int lineIdx = 0; lineIdx < lines->length; lineIdx++) {
			line = lines->get(lineIdx)->trim();
			if (line->startsWith(u"#"_j)) {
				continue;
			}
			auto commandEndIdx = line->indexOf(static_cast< int32_t >(u' '));
			if (commandEndIdx == -1)
				commandEndIdx = line->length();

			auto command = line->substring(0, commandEndIdx)->trim()->toLowerCase();
			auto arguments = command->length() + 1 > line->length() ? u""_j : line->substring(command->length() + 1);
			if (command->equals(u"newmtl"_j)) {
				auto name = arguments;
				current = new Material(name);
				materials->put(name, current);
			} else
			if (command->equals(u"map_ka"_j)) {
				current->setDiffuseTexture(pathName, arguments);
			} else
			if (command->equals(u"map_kd"_j)) {
				current->setDiffuseTexture(pathName, arguments);
			} else
			if (command->equals(u"ka"_j)) {
				auto t = new StringTokenizer(arguments, u" "_j);
				current->getAmbientColor()->set(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), alpha);
			} else
			if (command->equals(u"kd"_j)) {
				auto t = new StringTokenizer(arguments, u" "_j);
				current->getDiffuseColor()->set(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), alpha);
			} else
			if (command->equals(u"ks"_j)) {
				auto t = new StringTokenizer(arguments, u" "_j);
				current->getSpecularColor()->set(Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), Float::parseFloat(t->nextToken()), alpha);
			} else
			if (command->equals(u"tr"_j)) {
				alpha = Float::parseFloat(arguments);
				current->getAmbientColor()->setAlpha(alpha);
				current->getDiffuseColor()->setAlpha(alpha);
				current->getSpecularColor()->setAlpha(alpha);
				current->getEmissionColor()->setAlpha(alpha);
			} else
			if (command->equals(u"d"_j)) {
				alpha = Float::parseFloat(arguments);
				current->getAmbientColor()->setAlpha(alpha);
				current->getDiffuseColor()->setAlpha(alpha);
				current->getSpecularColor()->setAlpha(alpha);
				current->getEmissionColor()->setAlpha(alpha);
			}
		}
	}
	return materials;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* WFObjReader::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.fileio.models.WFObjReader", 37);
    return c;
}

java::lang::Class* WFObjReader::getClass0()
{
	return class_();
}

