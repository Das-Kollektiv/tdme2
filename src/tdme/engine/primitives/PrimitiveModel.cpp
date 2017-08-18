// Generated from /tdme/src/tdme/engine/primitives/PrimitiveModel.java
#include <tdme/engine/primitives/PrimitiveModel.h>

#include <array>
#include <string>
#include <vector>

#include <java/lang/Math.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model_UpVector.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>

using std::array;
using std::vector;
using std::wstring;

using tdme::engine::primitives::PrimitiveModel;
using java::lang::Math;
using tdme::engine::model::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::engine::model::Model_UpVector;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::RotationOrder;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::math::MathTools;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utils::_Console;

constexpr int32_t PrimitiveModel::SPHERE_SEGMENTS_X;

constexpr int32_t PrimitiveModel::SPHERE_SEGMENTS_Y;

constexpr int32_t PrimitiveModel::CAPSULE_SEGMENTS_X;

constexpr int32_t PrimitiveModel::CAPSULE_SEGMENTS_Y;

Model* PrimitiveModel::createBoundingBoxModel(BoundingBox* boundingBox, const wstring& id)
{
	auto model = new Model(id, id, Model_UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	auto material = new Material(L"tdme.primitive.material");
	material->getAmbientColor()->set(0.5f, 0.5f, 0.5f, 1.0f);
	material->getDiffuseColor()->set(1.0f, 0.5f, 0.5f, 0.5f);
	material->getSpecularColor()->set(0.0f, 0.0f, 0.0f, 1.0f);
	(*model->getMaterials())[material->getId()] = material;
	auto group = new Group(model, nullptr, L"group", L"group");
	auto fvi = BoundingBox::getFacesVerticesIndexes();
	vector<Vector3> vertices;
	for (auto& vertex : *boundingBox->getVertices()) {
		vertices.push_back(vertex);
	}
	vector<Vector3> normals;
	normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
	normals.push_back(Vector3(+1.0f, 0.0f, 0.0f));
	normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
	normals.push_back(Vector3(0.0f, +1.0f, 0.0f));
	normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, +1.0f));
	vector<Face> faces;
	faces.push_back(Face(group, (*fvi)[0][0], (*fvi)[0][1], (*fvi)[0][2], 0, 0, 0));
	faces.push_back(Face(group, (*fvi)[1][0], (*fvi)[1][1], (*fvi)[1][2], 0, 0, 0));
	faces.push_back(Face(group, (*fvi)[2][0], (*fvi)[2][1], (*fvi)[2][2], 1, 1, 1));
	faces.push_back(Face(group, (*fvi)[3][0], (*fvi)[3][1], (*fvi)[3][2], 1, 1, 1));
	faces.push_back(Face(group, (*fvi)[4][0], (*fvi)[4][1], (*fvi)[4][2], 2, 2, 2));
	faces.push_back(Face(group, (*fvi)[5][0], (*fvi)[5][1], (*fvi)[5][2], 2, 2, 2));
	faces.push_back(Face(group, (*fvi)[6][0], (*fvi)[6][1], (*fvi)[6][2], 3, 3, 3));
	faces.push_back(Face(group, (*fvi)[7][0], (*fvi)[7][1], (*fvi)[7][2], 3, 3, 3));
	faces.push_back(Face(group, (*fvi)[8][0], (*fvi)[8][1], (*fvi)[8][2], 4, 4, 4));
	faces.push_back(Face(group, (*fvi)[9][0], (*fvi)[9][1], (*fvi)[9][2], 4, 4, 4));
	faces.push_back(Face(group, (*fvi)[10][0], (*fvi)[10][1], (*fvi)[10][2], 5, 5, 5));
	faces.push_back(Face(group, (*fvi)[11][0], (*fvi)[11][1], (*fvi)[11][2], 5, 5, 5));
	FacesEntity groupFacesEntity(group, L"faces entity");
	groupFacesEntity.setMaterial(material);
	groupFacesEntity.setFaces(&faces);
	vector<FacesEntity> groupFacesEntities;
	groupFacesEntities.push_back(groupFacesEntity);
	group->setVertices(&vertices);
	group->setNormals(&normals);
	group->setFacesEntities(&groupFacesEntities);
	group->determineFeatures();
	(*model->getGroups())[L"group"] = group;
	(*model->getSubGroups())[L"group"] = group;
	ModelHelper::prepareForIndexedRendering(model);
	return model;
}

Model* PrimitiveModel::createOrientedBoundingBoxModel(OrientedBoundingBox* orientedBoundingBox, const wstring& id)
{
	auto model = new Model(id, id, Model_UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	auto material = new Material(L"tdme.primitive.material");
	material->getAmbientColor()->set(0.5f, 0.5f, 0.5f, 1.0f);
	material->getDiffuseColor()->set(1.0f, 0.5f, 0.5f, 0.5f);
	material->getSpecularColor()->set(0.0f, 0.0f, 0.0f, 1.0f);
	(*model->getMaterials())[material->getId()] = material;
	auto group = new Group(model, nullptr, L"group", L"group");
	auto fvi = OrientedBoundingBox::getFacesVerticesIndexes();
	vector<Vector3> vertices;
	for (auto& vertex : *orientedBoundingBox->getVertices()) {
		vertices.push_back(vertex);
	}
	auto axes = orientedBoundingBox->getAxes();
	vector<Vector3> normals;
	normals.push_back(*(*axes)[0].clone2().scale(-1.0f));
	normals.push_back((*axes)[0].clone2());
	normals.push_back(*(*axes)[1].clone2().scale(-1.0f));
	normals.push_back((*axes)[1].clone2());
	normals.push_back(*(*axes)[2].clone2().scale(-1.0f));
	normals.push_back((*axes)[2].clone2());
	vector<Face> faces;
	faces.push_back(Face(group, (*fvi)[0][0], (*fvi)[0][1], (*fvi)[0][2], 0, 0, 0));
	faces.push_back(Face(group, (*fvi)[1][0], (*fvi)[1][1], (*fvi)[1][2], 0, 0, 0));
	faces.push_back(Face(group, (*fvi)[2][0], (*fvi)[2][1], (*fvi)[2][2], 1, 1, 1));
	faces.push_back(Face(group, (*fvi)[3][0], (*fvi)[3][1], (*fvi)[3][2], 1, 1, 1));
	faces.push_back(Face(group, (*fvi)[4][0], (*fvi)[4][1], (*fvi)[4][2], 2, 2, 2));
	faces.push_back(Face(group, (*fvi)[5][0], (*fvi)[5][1], (*fvi)[5][2], 2, 2, 2));
	faces.push_back(Face(group, (*fvi)[6][0], (*fvi)[6][1], (*fvi)[6][2], 3, 3, 3));
	faces.push_back(Face(group, (*fvi)[7][0], (*fvi)[7][1], (*fvi)[7][2], 3, 3, 3));
	faces.push_back(Face(group, (*fvi)[8][0], (*fvi)[8][1], (*fvi)[8][2], 4, 4, 4));
	faces.push_back(Face(group, (*fvi)[9][0], (*fvi)[9][1], (*fvi)[9][2], 4, 4, 4));
	faces.push_back(Face(group, (*fvi)[10][0], (*fvi)[10][1], (*fvi)[10][2], 5, 5, 5));
	faces.push_back(Face(group, (*fvi)[11][0], (*fvi)[11][1], (*fvi)[11][2], 5, 5, 5));
	FacesEntity groupFacesEntity(group, L"faces entity");
	groupFacesEntity.setMaterial(material);
	groupFacesEntity.setFaces(&faces);
	vector<FacesEntity> groupFacesEntities;
	groupFacesEntities.push_back(groupFacesEntity);
	group->setVertices(&vertices);
	group->setNormals(&normals);
	group->setFacesEntities(&groupFacesEntities);
	group->determineFeatures();
	(*model->getGroups())[L"group"] = group;
	(*model->getSubGroups())[L"group"] = group;
	ModelHelper::prepareForIndexedRendering(model);
	return model;
}

Model* PrimitiveModel::createSphereModel(Sphere* sphere, const wstring& id, int32_t segmentsX, int32_t segmentsY)
{
	auto radius = sphere->getRadius();
	auto center = sphere->getCenter();
	auto model = new Model(id, id, Model_UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	auto material = new Material(L"tdme.primitive.material");
	material->getAmbientColor()->set(0.5f, 0.5f, 0.5f, 1.0f);
	material->getDiffuseColor()->set(1.0f, 0.5f, 0.5f, 0.5f);
	material->getSpecularColor()->set(0.0f, 0.0f, 0.0f, 1.0f);
	(*model->getMaterials())[material->getId()] = material;
	auto group = new Group(model, nullptr, L"group", L"group");
	vector<Vector3> vertices;
	vertices.resize((segmentsY + 1) * segmentsX);

	for (auto ySegment = 0; ySegment <= segmentsY; ySegment++) 
		for (auto xSegment = 0; xSegment < segmentsX; xSegment++) {
			auto vertex = (new Vector3(static_cast< float >((Math::sin(Math::PI * ySegment / segmentsY) * Math::cos(Math::PI * 2 * xSegment / segmentsX))), static_cast< float >((Math::cos(Math::PI * ySegment / segmentsY))), static_cast< float >((Math::sin(Math::PI * ySegment / segmentsY) * Math::sin(Math::PI * 2 * xSegment / segmentsX)))))->scale(radius)->add(center);
			vertices[ySegment * segmentsX + xSegment] = vertex;
		}

	vector<Vector3> normals;
	vector<Face> faces;
	int32_t vi0, vi1, vi2;
	int32_t ni;
	for (auto y = 0; y <= segmentsY; y++) {
		for (auto x = 0; x < segmentsX; x++) {
			vi0 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			vi1 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			vi2 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			ni = normals.size();
			for (auto normal : ModelHelper::computeNormals(array<Vector3,3>{
				&vertices.at(vi0),
				&vertices.at(vi1),
				&vertices.at(vi2)
			})) {
				normals.push_back(normal);
			}
			faces.push_back(Face(group, vi0, vi1, vi2, ni + 0, ni + 1, ni + 2));
			vi0 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			vi1 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			vi2 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			ni = normals.size();
			for (auto normal : ModelHelper::computeNormals(array<Vector3,3>{
				&vertices.at(vi0),
				&vertices.at(vi1),
				&vertices.at(vi2)
			})) {
				normals.push_back(normal);
			}
			faces.push_back(Face(group, vi0, vi1, vi2, ni + 0, ni + 1, ni + 2));
		}
	}
	FacesEntity groupFacesEntity(group, L"faces entity");
	groupFacesEntity.setMaterial(material);
	groupFacesEntity.setFaces(&faces);
	vector<FacesEntity> groupFacesEntities;
	groupFacesEntities.push_back(groupFacesEntity);
	group->setVertices(&vertices);
	group->setNormals(&normals);
	group->setFacesEntities(&groupFacesEntities);
	group->determineFeatures();
	(*model->getGroups())[L"group"] = group;
	(*model->getSubGroups())[L"group"] = group;
	ModelHelper::prepareForIndexedRendering(model);
	return model;
}

Model* PrimitiveModel::createCapsuleModel(Capsule* capsule, const wstring& id, int32_t segmentsX, int32_t segmentsY)
{
	auto radius = capsule->getRadius();
	auto a = capsule->getA();
	auto b = capsule->getB();
	auto rotationQuaternion = new Quaternion();
	rotationQuaternion->identity();
	auto yAxis = new Vector3(0.0f, -1.0f, 0.0f);
	auto abNormalized = a->clone()->sub(b)->normalize();
	auto abNormalizedVectorXYZ = abNormalized->getArray();
	Vector3* rotationAxis;
	if (Math::abs((*abNormalizedVectorXYZ)[0]) < MathTools::EPSILON && Math::abs((*abNormalizedVectorXYZ)[2]) < MathTools::EPSILON) {
		rotationAxis = new Vector3((*abNormalizedVectorXYZ)[1], 0.0f, 0.0f);
	} else {
		rotationAxis = Vector3::computeCrossProduct(yAxis, abNormalized)->normalize();
	}
	auto angle = Vector3::computeAngle(yAxis, abNormalized, yAxis);
	rotationQuaternion->rotate(angle, rotationAxis);
	auto model = new Model(id, id, Model_UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	auto material = new Material(L"tdme.primitive.material");
	material->getAmbientColor()->set(0.5f, 0.5f, 0.5f, 1.0f);
	material->getDiffuseColor()->set(1.0f, 0.5f, 0.5f, 0.5f);
	material->getSpecularColor()->set(0.0f, 0.0f, 0.0f, 1.0f);
	(*model->getMaterials())[material->getId()] = material;
	auto group = new Group(model, nullptr, L"group", L"group");
	vector<Vector3> vertices;
	vertices.resize((segmentsY + 2) * segmentsX);

	for (auto ySegment = segmentsY / 2; ySegment <= segmentsY; ySegment++) 
		for (auto xSegment = 0; xSegment < segmentsX; xSegment++) {
			auto vertex = Vector3();
			rotationQuaternion->multiply(
				new Vector3(
					static_cast< float >((Math::sin(Math::PI * ySegment / segmentsY) * Math::cos(Math::PI * 2 * xSegment / segmentsX))),
					static_cast< float >((Math::cos(Math::PI * ySegment / segmentsY))),
					static_cast< float >((Math::sin(Math::PI * ySegment / segmentsY) * Math::sin(Math::PI * 2 * xSegment / segmentsX)))),
					&vertex
				);
			vertex.scale(radius);
			vertex.add(a);
			vertices[ySegment * segmentsX + xSegment] = vertex;
		}
	for (auto ySegment = 0; ySegment <= segmentsY / 2; ySegment++) 
		for (auto xSegment = 0; xSegment < segmentsX; xSegment++) {
			auto vertex = Vector3();
			rotationQuaternion->multiply(
				new Vector3(
					static_cast< float >((Math::sin(Math::PI * ySegment / segmentsY) * Math::cos(Math::PI * 2 * xSegment / segmentsX))),
					static_cast< float >((Math::cos(Math::PI * ySegment / segmentsY))),
					static_cast< float >((Math::sin(Math::PI * ySegment / segmentsY) * Math::sin(Math::PI * 2 * xSegment / segmentsX)))),
					&vertex
				);
			vertex.scale(radius);
			vertex.add(b);
			vertices[ySegment * segmentsX + xSegment] = vertex;
		}

	vector<Vector3> normals;
	vector<Face> faces;
	int32_t vi0, vi1, vi2;
	int32_t ni;
	for (auto y = 0; y <= segmentsY + 1; y++) {
		for (auto x = 0; x < segmentsX; x++) {
			vi0 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			vi1 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			vi2 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			ni = normals.size();
			for (auto normal : ModelHelper::computeNormals(array<Vector3,3>{
				&vertices.at(vi0),
				&vertices.at(vi1),
				&vertices.at(vi2)
			})) {
				normals.push_back(normal);
			}
			faces.push_back(Face(group, vi0, vi1, vi2, ni + 0, ni + 1, ni + 2));
			vi0 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			vi1 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			vi2 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			ni = normals.size();
			for (auto normal : ModelHelper::computeNormals(array<Vector3,3>{
				&vertices.at(vi0),
				&vertices.at(vi1),
				&vertices.at(vi2)
			})) {
				normals.push_back(normal);
			}
			faces.push_back(Face(group, vi0, vi1, vi2, ni + 0, ni + 1, ni + 2));
		}
	}
	FacesEntity groupFacesEntity(group, L"faces entity");
	groupFacesEntity.setMaterial(material);
	groupFacesEntity.setFaces(&faces);
	vector<FacesEntity> groupFacesEntities;
	groupFacesEntities.push_back(groupFacesEntity);
	group->setVertices(&vertices);
	group->setNormals(&normals);
	group->setFacesEntities(&groupFacesEntities);
	group->determineFeatures();
	(*model->getGroups())[L"group"] = group;
	(*model->getSubGroups())[L"group"] = group;
	ModelHelper::prepareForIndexedRendering(model);
	return model;
}

void PrimitiveModel::setupConvexMeshModel(Model* model)
{
	auto material = new Material(L"tdme.primitive.material");
	material->getAmbientColor()->set(0.5f, 0.5f, 0.5f, 1.0f);
	material->getDiffuseColor()->set(1.0f, 0.5f, 0.5f, 0.5f);
	material->getSpecularColor()->set(0.0f, 0.0f, 0.0f, 1.0f);
	(*model->getMaterials())[material->getId()] = material;
	setupConvexMeshMaterial(model->getSubGroups(), material);
}

void PrimitiveModel::setupConvexMeshMaterial(map<wstring, Group*>* groups, Material* material)
{
	for (auto it: *groups) {
		Group* group = it.second;
		for (auto& faceEntity : *group->getFacesEntities()) {
			faceEntity.setMaterial(material);
		}
	}
}

Model* PrimitiveModel::createModel(BoundingVolume* boundingVolume, const wstring& id)
{
	if (dynamic_cast< BoundingBox* >(boundingVolume) != nullptr) {
		return PrimitiveModel::createBoundingBoxModel(dynamic_cast< BoundingBox* >(boundingVolume), id);
	} else
	if (dynamic_cast< OrientedBoundingBox* >(boundingVolume) != nullptr) {
		return PrimitiveModel::createOrientedBoundingBoxModel(dynamic_cast< OrientedBoundingBox* >(boundingVolume), id);
	} else
	if (dynamic_cast< Sphere* >(boundingVolume) != nullptr) {
		return PrimitiveModel::createSphereModel(dynamic_cast< Sphere* >(boundingVolume), id, SPHERE_SEGMENTS_X, SPHERE_SEGMENTS_Y);
	} else
	if (dynamic_cast< Capsule* >(boundingVolume) != nullptr) {
		return PrimitiveModel::createCapsuleModel(dynamic_cast< Capsule* >(boundingVolume), id, CAPSULE_SEGMENTS_X, CAPSULE_SEGMENTS_Y);
	} else {
		_Console::println(wstring(L"PrimitiveModel::createModel(): unsupported bounding volume"));
		return nullptr;
	}
}
