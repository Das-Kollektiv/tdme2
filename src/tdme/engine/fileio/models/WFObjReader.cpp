// Generated from /tdme/src/tdme/engine/fileio/models/WFObjReader.java
#include <tdme/engine/fileio/models/WFObjReader.h>

#include <map>
#include <string>
#include <vector>

#include <java/io/Serializable.h>
#include <java/lang/CharSequence.h>
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
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/_HashMap.h>
#include <ObjectArray.h>
#include <SubArray.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::fileio::models::WFObjReader;
using java::io::BufferedReader;
using java::io::DataInputStream;
using java::io::File;
using java::io::InputStreamReader;
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
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;
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

Model* WFObjReader::read(String* pathName, String* fileName) throw (_FileSystemException, ModelFileIOException)
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
	vector<Vector3*> vertices;
	vector<TextureCoordinate*> textureCoordinates;
	map<wstring, Material*> materials;
	auto subGroups = model->getSubGroups();
	auto groups = model->getGroups();
	Group* group = nullptr;
	map<int32_t, int32_t> modelGroupVerticesMapping;
	map<int32_t, int32_t> modelGroupTextureCoordinatesMapping;
	vector<Face*> groupFacesEntityFaces;
	vector<Vector3*> groupVertices;
	vector<Vector3*> groupNormals;
	vector<TextureCoordinate*> groupTextureCoordinates;
	vector<FacesEntity*> groupFacesEntities;
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
					WFObjReader::readMaterials(pathName, materialFileName, materials);
				} else
				if (command->equals(u"v"_j)) {
					auto t = new StringTokenizer(arguments, u" "_j);
					auto x = Float::parseFloat(t->nextToken());
					auto y = Float::parseFloat(t->nextToken());
					auto z = Float::parseFloat(t->nextToken());
					vertices.push_back(new Vector3(x, y, z));
				} else
				if (command->equals(u"vt"_j)) {
					auto t = new StringTokenizer(arguments, u" "_j);
					auto u = Float::parseFloat(t->nextToken());
					auto v = Float::parseFloat(t->nextToken());
					textureCoordinates.push_back(new TextureCoordinate(u, v));
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
						throw ModelFileIOException("We only support triangulated meshes");
					}
					{
						auto mappedVertexIt = modelGroupVerticesMapping.find(v0);
						if (mappedVertexIt == modelGroupVerticesMapping.end()) {
							groupVertices.push_back(vertices.at(v0)->clone());
							v0 = groupVertices.size() - 1;
						} else {
							v0 = mappedVertexIt->second;
						}
					}
					{
						auto mappedVertexIt = modelGroupVerticesMapping.find(v1);
						if (mappedVertexIt == modelGroupVerticesMapping.end()) {
							groupVertices.push_back(vertices.at(v1)->clone());
							v1 = groupVertices.size() - 1;
						} else {
							v1 = mappedVertexIt->second;
						}
					}
					{
						auto mappedVertexIt = modelGroupVerticesMapping.find(v2);
						if (mappedVertexIt == modelGroupVerticesMapping.end()) {
							groupVertices.push_back(vertices.at(v2)->clone());
							v2 = groupVertices.size() - 1;
						} else {
							v2 = mappedVertexIt->second;
						}
					}
					{
						auto mappedTextureCoordinateIt = modelGroupTextureCoordinatesMapping.find(vt0);
						if (mappedTextureCoordinateIt == modelGroupTextureCoordinatesMapping.end()) {
							groupTextureCoordinates.push_back(textureCoordinates.at(vt0)->clone());
							vt0 = groupTextureCoordinates.size() - 1;
						} else {
							vt0 = mappedTextureCoordinateIt->second;
						}
					}
					{
						auto mappedTextureCoordinateIt = modelGroupTextureCoordinatesMapping.find(vt1);
						if (mappedTextureCoordinateIt == modelGroupTextureCoordinatesMapping.end()) {
							groupTextureCoordinates.push_back(textureCoordinates.at(vt1)->clone());
							vt1 = groupTextureCoordinates.size() - 1;
						} else {
							vt1 = mappedTextureCoordinateIt->second;
						}
					}
					{
						auto mappedTextureCoordinateIt = modelGroupTextureCoordinatesMapping.find(vt2);
						if (mappedTextureCoordinateIt == modelGroupTextureCoordinatesMapping.end()) {
							groupTextureCoordinates.push_back(textureCoordinates.at(vt2)->clone());
							vt2 = groupTextureCoordinates.size() - 1;
						} else {
							vt2 = mappedTextureCoordinateIt->second;
						}
					}
					auto faceVertexNormals = ModelHelper::computeNormals(new Vector3Array({
						groupVertices.at(v0),
						groupVertices.at(v1),
						groupVertices.at(v2)
					}));
					auto n0 = groupNormals.size();
					groupNormals.push_back((*faceVertexNormals)[0]);
					auto n1 = groupNormals.size();
					groupNormals.push_back((*faceVertexNormals)[1]);
					auto n2 = groupNormals.size();
					groupNormals.push_back((*faceVertexNormals)[2]);
					auto face = new Face(group, v0, v1, v2, n0, n1, n2);
					if (vt0 != -1 && vt1 != -1 && vt2 != -1) {
						face->setTextureCoordinateIndices(vt0, vt1, vt2);
					}
					groupFacesEntityFaces.push_back(face);
				} else
				if (command->equals(u"g"_j)) {
					if (group != nullptr) {
						if (groupFacesEntityFaces.empty() == false) {
							groupFacesEntity->setFaces(groupFacesEntityFaces);
							groupFacesEntities.push_back(groupFacesEntity);
						}
						group->setVertices(groupVertices);
						group->setNormals(groupNormals);
						group->setTextureCoordinates(groupTextureCoordinates);
						group->setFacesEntities(groupFacesEntities);
						group->determineFeatures();
					}
					auto t = new StringTokenizer(arguments, u" "_j);
					auto name = t->nextToken();
					groupVertices.clear();
					groupNormals.clear();
					groupTextureCoordinates.clear();
					groupFacesEntityFaces.clear();
					group = new Group(model, nullptr, name, name);
					groupFacesEntity = new FacesEntity(group, name);
					groupFacesEntities.clear();
					modelGroupVerticesMapping.clear();
					modelGroupTextureCoordinatesMapping.clear();
					subGroups->put(name, group);
					groups->put(name, group);
				} else
				if (command->equals(u"usemtl"_j)) {
					if (group != nullptr) {
						if (groupFacesEntityFaces.empty() == false) {
							groupFacesEntity->setFaces(groupFacesEntityFaces);
							groupFacesEntities.push_back(groupFacesEntity);
						}
						groupFacesEntity = new FacesEntity(group, ::java::lang::StringBuilder().append(u"#"_j)->append((int32_t)groupFacesEntities.size())->toString());
						groupFacesEntityFaces.clear();
					}
					auto materialIt = materials.find(arguments->getCPPWString());
					if (materialIt != materials.end()) {
						Material* material = materialIt->second;
						group->getModel()->getMaterials()->put(material->getId(), material);
						groupFacesEntity->setMaterial(material);
					}
				} else {
				}
			}
			if (group != nullptr) {
				if (groupFacesEntityFaces.empty() == false) {
					groupFacesEntity->setFaces(groupFacesEntityFaces);
					groupFacesEntities.push_back(groupFacesEntity);
				}
				group->setVertices(groupVertices);
				group->setNormals(groupNormals);
				if (groupTextureCoordinates.size() > 0) {
					group->setTextureCoordinates(groupTextureCoordinates);
				}
				group->setFacesEntities(groupFacesEntities);
				group->determineFeatures();
			}
		}
	}

	ModelHelper::prepareForIndexedRendering(model);
	return model;
}

void WFObjReader::readMaterials(String* pathName, String* fileName, map<wstring, Material*>& materials) throw (_FileSystemException, ModelFileIOException)
{
	clinit();
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
				materials[name->getCPPWString()] = current;
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

