#include <tdme/engine/fileio/models/WFObjReader.h>

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Float.h>
#include <tdme/utils/Integer.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/StringTokenizer.h>

using std::array;
using std::map;
using std::vector;
using std::string;
using std::to_string;

using tdme::engine::fileio::models::WFObjReader;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::engine::model::UpVector;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::Integer;
using tdme::utils::Float;
using tdme::utils::StringUtils;
using tdme::utils::StringTokenizer;

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

Model* WFObjReader::read(const string& pathName, const string& fileName) throw (FileSystemException, ModelFileIOException)
{
	auto model = new Model(
		pathName + "/" + fileName,
		fileName,
		UpVector::Y_UP,
		RotationOrder::XYZ,
		nullptr
	);
	vector<Vector3> vertices;
	vector<TextureCoordinate> textureCoordinates;
	map<string, Material*> materials;
	auto subGroups = model->getSubGroups();
	auto groups = model->getGroups();
	Group* group = nullptr;
	map<int32_t, int32_t> modelGroupVerticesMapping;
	map<int32_t, int32_t> modelGroupTextureCoordinatesMapping;
	vector<Face> groupFacesEntityFaces;
	vector<Vector3> groupVertices;
	vector<Vector3> groupNormals;
	vector<TextureCoordinate> groupTextureCoordinates;
	vector<FacesEntity> groupFacesEntities;
	FacesEntity* groupFacesEntity = nullptr;
	{
		auto finally0 = finally([&] {
			// finally block
		});
		{
			StringTokenizer t;
			StringTokenizer t2;
			vector<string> lines;
			FileSystem::getInstance()->getContentAsStringArray(pathName, fileName, &lines);
			string line;
			for (int lineIdx = 0; lineIdx < lines.size(); lineIdx++) {
				line = StringUtils::trim(lines[lineIdx]);
				if (StringUtils::startsWith(line, "#")) {
					continue;
				}
				auto commandEndIdx = line.find(L' ');
				if (commandEndIdx == -1) commandEndIdx = line.size();
				auto command = StringUtils::toLowerCase(StringUtils::trim(StringUtils::substring(line, 0, commandEndIdx)));
				auto arguments = command.size() + 1 > line.length() ? "" : StringUtils::substring(line, command.length() + 1);
				if (command == "mtllib") {
					auto materialFileName = arguments;
					WFObjReader::readMaterials(pathName, materialFileName, &materials);
				} else
				if (command == "v") {
					t.tokenize(arguments, " ");
					auto x = Float::parseFloat(t.nextToken());
					auto y = Float::parseFloat(t.nextToken());
					auto z = Float::parseFloat(t.nextToken());
					vertices.push_back(Vector3(x, y, z));
				} else
				if (command == "vt") {
					t.tokenize(arguments, " ");
					auto u = Float::parseFloat(t.nextToken());
					auto v = Float::parseFloat(t.nextToken());
					textureCoordinates.push_back(TextureCoordinate(u, v));
				} else
				if (command == "f") {
					t.tokenize(arguments, " ");
					auto v0 = -1;
					auto v1 = -1;
					auto v2 = -1;
					auto vt0 = -1;
					auto vt1 = -1;
					auto vt2 = -1;
					t2.tokenize(t.nextToken(), "/");
					v0 = Integer::parseInt(t2.nextToken()) - 1;
					if (t2.hasMoreTokens()) {
						vt0 = Integer::parseInt(t2.nextToken()) - 1;
					}
					t2.tokenize(t.nextToken(), "/");
					v1 = Integer::parseInt(t2.nextToken()) - 1;
					if (t2.hasMoreTokens()) {
						vt1 = Integer::parseInt(t2.nextToken()) - 1;
					}
					t2.tokenize(t.nextToken(), "/");
					v2 = Integer::parseInt(t2.nextToken()) - 1;
					if (t2.hasMoreTokens()) {
						vt2 = Integer::parseInt(t2.nextToken()) - 1;
					}
					if (t.hasMoreTokens()) {
						throw ModelFileIOException("We only support triangulated meshes");
					}
					{
						auto mappedVertexIt = modelGroupVerticesMapping.find(v0);
						if (mappedVertexIt == modelGroupVerticesMapping.end()) {
							groupVertices.push_back(vertices.at(v0));
							v0 = groupVertices.size() - 1;
						} else {
							v0 = mappedVertexIt->second;
						}
					}
					{
						auto mappedVertexIt = modelGroupVerticesMapping.find(v1);
						if (mappedVertexIt == modelGroupVerticesMapping.end()) {
							groupVertices.push_back(vertices.at(v1));
							v1 = groupVertices.size() - 1;
						} else {
							v1 = mappedVertexIt->second;
						}
					}
					{
						auto mappedVertexIt = modelGroupVerticesMapping.find(v2);
						if (mappedVertexIt == modelGroupVerticesMapping.end()) {
							groupVertices.push_back(vertices.at(v2));
							v2 = groupVertices.size() - 1;
						} else {
							v2 = mappedVertexIt->second;
						}
					}
					{
						auto mappedTextureCoordinateIt = modelGroupTextureCoordinatesMapping.find(vt0);
						if (mappedTextureCoordinateIt == modelGroupTextureCoordinatesMapping.end()) {
							groupTextureCoordinates.push_back(textureCoordinates.at(vt0));
							vt0 = groupTextureCoordinates.size() - 1;
						} else {
							vt0 = mappedTextureCoordinateIt->second;
						}
					}
					{
						auto mappedTextureCoordinateIt = modelGroupTextureCoordinatesMapping.find(vt1);
						if (mappedTextureCoordinateIt == modelGroupTextureCoordinatesMapping.end()) {
							groupTextureCoordinates.push_back(textureCoordinates.at(vt1));
							vt1 = groupTextureCoordinates.size() - 1;
						} else {
							vt1 = mappedTextureCoordinateIt->second;
						}
					}
					{
						auto mappedTextureCoordinateIt = modelGroupTextureCoordinatesMapping.find(vt2);
						if (mappedTextureCoordinateIt == modelGroupTextureCoordinatesMapping.end()) {
							groupTextureCoordinates.push_back(textureCoordinates.at(vt2));
							vt2 = groupTextureCoordinates.size() - 1;
						} else {
							vt2 = mappedTextureCoordinateIt->second;
						}
					}
					array<Vector3, 3> faceVertices = {
						groupVertices.at(v0),
						groupVertices.at(v1),
						groupVertices.at(v2)
					};
					array<Vector3, 3> faceVertexNormals;
					ModelHelper::computeNormals(
						&faceVertices,
						&faceVertexNormals
					);
					auto n0 = groupNormals.size();
					groupNormals.push_back(faceVertexNormals[0]);
					auto n1 = groupNormals.size();
					groupNormals.push_back(faceVertexNormals[1]);
					auto n2 = groupNormals.size();
					groupNormals.push_back(faceVertexNormals[2]);
					Face face(group, v0, v1, v2, n0, n1, n2);
					if (vt0 != -1 && vt1 != -1 && vt2 != -1) {
						face.setTextureCoordinateIndices(vt0, vt1, vt2);
					}
					groupFacesEntityFaces.push_back(face);
				} else
				if (command == "g") {
					if (group != nullptr) {
						if (groupFacesEntityFaces.empty() == false) {
							groupFacesEntity->setFaces(&groupFacesEntityFaces);
							groupFacesEntities.push_back(*groupFacesEntity);
						}
						group->setVertices(&groupVertices);
						group->setNormals(&groupNormals);
						group->setTextureCoordinates(&groupTextureCoordinates);
						group->setFacesEntities(&groupFacesEntities);
						group->determineFeatures();
					}
					t.tokenize(arguments, " ");
					auto name = t.nextToken();
					groupVertices.clear();
					groupNormals.clear();
					groupTextureCoordinates.clear();
					groupFacesEntityFaces.clear();
					group = new Group(model, nullptr, name, name);
					groupFacesEntity = new FacesEntity(group, name);
					groupFacesEntities.clear();
					modelGroupVerticesMapping.clear();
					modelGroupTextureCoordinatesMapping.clear();
					(*subGroups)[name] = group;
					(*groups)[name] = group;
				} else
				if (command == "usemtl") {
					if (group != nullptr) {
						if (groupFacesEntityFaces.empty() == false) {
							groupFacesEntity->setFaces(&groupFacesEntityFaces);
							groupFacesEntities.push_back(*groupFacesEntity);
						}
						groupFacesEntity = new FacesEntity(
							group,
							"#" + to_string(groupFacesEntities.size())
						);
						groupFacesEntityFaces.clear();
					}
					auto materialIt = materials.find(arguments);
					if (materialIt != materials.end()) {
						Material* material = materialIt->second;
						(*group->getModel()->getMaterials())[material->getId()] = material;
						groupFacesEntity->setMaterial(material);
					}
				} else {
				}
			}
			if (group != nullptr) {
				if (groupFacesEntityFaces.empty() == false) {
					groupFacesEntity->setFaces(&groupFacesEntityFaces);
					groupFacesEntities.push_back(*groupFacesEntity);
				}
				group->setVertices(&groupVertices);
				group->setNormals(&groupNormals);
				if (groupTextureCoordinates.size() > 0) {
					group->setTextureCoordinates(&groupTextureCoordinates);
				}
				group->setFacesEntities(&groupFacesEntities);
				group->determineFeatures();
			}
		}
	}

	ModelHelper::prepareForIndexedRendering(model);
	return model;
}

void WFObjReader::readMaterials(const string& pathName, const string& fileName, map<string, Material*>* materials) throw (FileSystemException, ModelFileIOException)
{
	Material* current = nullptr;
	auto alpha = 1.0f;
	{
		auto finally0 = finally([&] {
			// finally block
		});
		StringTokenizer t;
		vector<string> lines;
		FileSystem::getInstance()->getContentAsStringArray(pathName, fileName, &lines);
		for (int lineIdx = 0; lineIdx < lines.size(); lineIdx++) {
			auto line = StringUtils::trim(lines[lineIdx]);
			if (StringUtils::startsWith(line, "#") == true) {
				continue;
			}
			auto commandEndIdx = line.find(L' ');
			if (commandEndIdx == -1) commandEndIdx = line.length();
			auto command = StringUtils::toLowerCase(StringUtils::trim(StringUtils::substring(line, 0, commandEndIdx)));
			auto arguments = command.length() + 1 > line.length() ? "" : StringUtils::substring(line, command.length() + 1);
			if (command == "newmtl") {
				auto name = arguments;
				current = new Material(name);
				(*materials)[name] = current;
			} else
			if (command == "map_ka") {
				current->setDiffuseTexture(pathName, arguments);
			} else
			if (command == "map_kd") {
				current->setDiffuseTexture(pathName, arguments);
			} else
			if (command == "ka") {
				t.tokenize(arguments, " ");
				float r = Float::parseFloat(t.nextToken());
				float g = Float::parseFloat(t.nextToken());
				float b = Float::parseFloat(t.nextToken());
				current->getAmbientColor().set(r, g, b, alpha);
			} else
			if (command == "kd") {
				t.tokenize(arguments, " ");
				float r = Float::parseFloat(t.nextToken());
				float g = Float::parseFloat(t.nextToken());
				float b = Float::parseFloat(t.nextToken());
				current->getDiffuseColor().set(r, g, b, alpha);
			} else
			if (command == "ks") {
				t.tokenize(arguments, " ");
				float r = Float::parseFloat(t.nextToken());
				float g = Float::parseFloat(t.nextToken());
				float b = Float::parseFloat(t.nextToken());
				current->getSpecularColor().set(r, g, b, alpha);
			} else
			if (command == "tr") {
				alpha = Float::parseFloat(arguments);
				current->getDiffuseColor().setAlpha(alpha);
			} else
			if (command == "d") {
				alpha = Float::parseFloat(arguments);
				current->getDiffuseColor().setAlpha(alpha);
			}
		}
	}
}
