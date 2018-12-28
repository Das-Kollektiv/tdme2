#include <tdme/engine/primitives/PrimitiveModel.h>

#include <array>
#include <string>
#include <vector>

#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/math/Math.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>

using std::array;
using std::vector;
using std::string;
using std::to_string;

using tdme::engine::primitives::PrimitiveModel;
using tdme::engine::model::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::engine::model::UpVector;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::RotationOrder;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::math::Math;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utils::Console;

constexpr int32_t PrimitiveModel::SPHERE_SEGMENTS_X;

constexpr int32_t PrimitiveModel::SPHERE_SEGMENTS_Y;

constexpr int32_t PrimitiveModel::CAPSULE_SEGMENTS_X;

constexpr int32_t PrimitiveModel::CAPSULE_SEGMENTS_Y;

Model* PrimitiveModel::createBoundingBoxModel(BoundingBox* boundingBox, const string& id)
{
	// model
	auto model = new Model(id, id, UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	// material
	auto material = new Material("tdme.primitive.material");
	material->setAmbientColor(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	material->setDiffuseColor(Color4(1.0f, 0.5f, 0.5f, 0.5f));
	material->setSpecularColor(Color4(0.0f, 0.0f, 0.0f, 1.0f));
	(*model->getMaterials())[material->getId()] = material;
	// group
	auto group = new Group(model, nullptr, "group", "group");
	// triangle vertices indexes
	auto fvi = BoundingBox::getFacesVerticesIndexes();
	// vertices
	vector<Vector3> vertices;
	for (auto& vertex : *boundingBox->getVertices()) {
		vertices.push_back(vertex);
	}
	// normals
	vector<Vector3> normals;
	normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
	normals.push_back(Vector3(+1.0f, 0.0f, 0.0f));
	normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
	normals.push_back(Vector3(0.0f, +1.0f, 0.0f));
	normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, +1.0f));
	// faces
	vector<Face> faces;
	//	left
	faces.push_back(Face(group, (*fvi)[0][0], (*fvi)[0][1], (*fvi)[0][2], 0, 0, 0));
	faces.push_back(Face(group, (*fvi)[1][0], (*fvi)[1][1], (*fvi)[1][2], 0, 0, 0));
	//	right
	faces.push_back(Face(group, (*fvi)[2][0], (*fvi)[2][1], (*fvi)[2][2], 1, 1, 1));
	faces.push_back(Face(group, (*fvi)[3][0], (*fvi)[3][1], (*fvi)[3][2], 1, 1, 1));
	//	top
	faces.push_back(Face(group, (*fvi)[4][0], (*fvi)[4][1], (*fvi)[4][2], 2, 2, 2));
	faces.push_back(Face(group, (*fvi)[5][0], (*fvi)[5][1], (*fvi)[5][2], 2, 2, 2));
	//	bottom
	faces.push_back(Face(group, (*fvi)[6][0], (*fvi)[6][1], (*fvi)[6][2], 3, 3, 3));
	faces.push_back(Face(group, (*fvi)[7][0], (*fvi)[7][1], (*fvi)[7][2], 3, 3, 3));
	//	near
	faces.push_back(Face(group, (*fvi)[8][0], (*fvi)[8][1], (*fvi)[8][2], 4, 4, 4));
	faces.push_back(Face(group, (*fvi)[9][0], (*fvi)[9][1], (*fvi)[9][2], 4, 4, 4));
	//	far
	faces.push_back(Face(group, (*fvi)[10][0], (*fvi)[10][1], (*fvi)[10][2], 5, 5, 5));
	faces.push_back(Face(group, (*fvi)[11][0], (*fvi)[11][1], (*fvi)[11][2], 5, 5, 5));
	// faces entity
	FacesEntity groupFacesEntity(group, "faces entity");
	groupFacesEntity.setMaterial(material);
	groupFacesEntity.setFaces(&faces);
	// set up faces entity
	vector<FacesEntity> groupFacesEntities;
	groupFacesEntities.push_back(groupFacesEntity);
	// setup group vertex data
	group->setVertices(vertices);
	group->setNormals(normals);
	group->setFacesEntities(groupFacesEntities);
	// determine features
	group->determineFeatures();
	// register group
	(*model->getGroups())["group"] = group;
	(*model->getSubGroups())["group"] = group;
	// prepare for indexed rendering
	ModelHelper::prepareForIndexedRendering(model);
	//
	return model;
}

Model* PrimitiveModel::createOrientedBoundingBoxModel(OrientedBoundingBox* orientedBoundingBox, const string& id)
{
	// model
	auto model = new Model(id, id, UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	// material
	auto material = new Material("tdme.primitive.material");
	material->setAmbientColor(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	material->setDiffuseColor(Color4(1.0f, 0.5f, 0.5f, 0.5f));
	material->setSpecularColor(Color4(0.0f, 0.0f, 0.0f, 1.0f));
	(*model->getMaterials())[material->getId()] = material;
	// group
	auto group = new Group(model, nullptr, "group", "group");
	// triangle vertices indexes
	auto fvi = OrientedBoundingBox::getFacesVerticesIndexes();
	// vertices
	vector<Vector3> vertices;
	for (auto& vertex : orientedBoundingBox->getVertices()) {
		vertices.push_back(transformVector3(orientedBoundingBox, toRP3DVector3(vertex)));
	}
	// normals
	auto axes = orientedBoundingBox->getAxes();
	vector<Vector3> normals;
	normals.push_back(transformVector3Normal(orientedBoundingBox, toRP3DVector3((*axes)[0].clone().scale(-1.0f))));
	normals.push_back(transformVector3Normal(orientedBoundingBox, toRP3DVector3((*axes)[0].clone())));
	normals.push_back(transformVector3Normal(orientedBoundingBox, toRP3DVector3((*axes)[1].clone().scale(-1.0f))));
	normals.push_back(transformVector3Normal(orientedBoundingBox, toRP3DVector3((*axes)[1].clone())));
	normals.push_back(transformVector3Normal(orientedBoundingBox, toRP3DVector3((*axes)[2].clone().scale(-1.0f))));
	normals.push_back(transformVector3Normal(orientedBoundingBox, toRP3DVector3((*axes)[2].clone())));
	// faces
	vector<Face> faces;
	//	left
	faces.push_back(Face(group, fvi[0][0], fvi[0][1], fvi[0][2], 0, 0, 0));
	faces.push_back(Face(group, fvi[1][0], fvi[1][1], fvi[1][2], 0, 0, 0));
	//	right
	faces.push_back(Face(group, fvi[2][0], fvi[2][1], fvi[2][2], 1, 1, 1));
	faces.push_back(Face(group, fvi[3][0], fvi[3][1], fvi[3][2], 1, 1, 1));
	//	top
	faces.push_back(Face(group, fvi[4][0], fvi[4][1], fvi[4][2], 2, 2, 2));
	faces.push_back(Face(group, fvi[5][0], fvi[5][1], fvi[5][2], 2, 2, 2));
	//	bottom
	faces.push_back(Face(group, fvi[6][0], fvi[6][1], fvi[6][2], 3, 3, 3));
	faces.push_back(Face(group, fvi[7][0], fvi[7][1], fvi[7][2], 3, 3, 3));
	//	near
	faces.push_back(Face(group, fvi[8][0], fvi[8][1], fvi[8][2], 4, 4, 4));
	faces.push_back(Face(group, fvi[9][0], fvi[9][1], fvi[9][2], 4, 4, 4));
	//	far
	faces.push_back(Face(group, fvi[10][0], fvi[10][1], fvi[10][2], 5, 5, 5));
	faces.push_back(Face(group, fvi[11][0], fvi[11][1], fvi[11][2], 5, 5, 5));
	// faces entity
	FacesEntity groupFacesEntity(group, "faces entity");
	groupFacesEntity.setMaterial(material);
	groupFacesEntity.setFaces(&faces);
	// set up faces entity
	vector<FacesEntity> groupFacesEntities;
	groupFacesEntities.push_back(groupFacesEntity);
	// setup group vertex data
	group->setVertices(vertices);
	group->setNormals(normals);
	group->setFacesEntities(groupFacesEntities);
	// determine features
	group->determineFeatures();
	// register group
	(*model->getGroups())["group"] = group;
	(*model->getSubGroups())["group"] = group;
	// prepare for indexed rendering
	ModelHelper::prepareForIndexedRendering(model);
	//
	return model;
}

Model* PrimitiveModel::createSphereModel(Sphere* sphere, const string& id, int32_t segmentsX, int32_t segmentsY)
{
	// sphere properties
	auto radius = sphere->getRadius();
	auto& center = sphere->getCenter();
	// model
	auto model = new Model(id, id, UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	// material
	auto material = new Material("tdme.primitive.material");
	material->setAmbientColor(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	material->setDiffuseColor(Color4(1.0f, 0.5f, 0.5f, 0.5f));
	material->setSpecularColor(Color4(0.0f, 0.0f, 0.0f, 1.0f));
	(*model->getMaterials())[material->getId()] = material;
	// group
	auto group = new Group(model, nullptr, "group", "group");
	// vertices
	vector<Vector3> vertices;
	for (auto ySegment = 0; ySegment < segmentsY + 1; ySegment++)
		for (auto xSegment = 0; xSegment < segmentsX; xSegment++) {
			auto vertex = (
				Vector3(
					((Math::sin(Math::PI * ySegment / segmentsY) * Math::cos(Math::PI * 2 * xSegment / segmentsX))),
					((Math::cos(Math::PI * ySegment / segmentsY))),
					((Math::sin(Math::PI * ySegment / segmentsY) * Math::sin(Math::PI * 2 * xSegment / segmentsX))))
				).scale(radius).add(center);
			vertices.push_back(transformVector3(sphere, toRP3DVector3(vertex)));
		}
	// normals
	vector<Vector3> normals;
	// faces
	vector<Face> faces;
	int32_t vi0, vi1, vi2;
	int32_t ni;
	for (auto y = 0; y < segmentsY + 1; y++) {
		for (auto x = 0; x < segmentsX; x++) {
			vi0 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			vi1 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			vi2 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			ni = normals.size();
			{
				array<Vector3, 3> faceVertices = {
					vertices.at(vi0),
					vertices.at(vi1),
					vertices.at(vi2)
				};
				array<Vector3, 3> faceNormals;
				ModelHelper::computeNormals(faceVertices, faceNormals);
				for (auto& normal : faceNormals) {
					normals.push_back(normal);
				}
			}
			faces.push_back(Face(group, vi0, vi1, vi2, ni + 0, ni + 1, ni + 2));
			vi0 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			vi1 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			vi2 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			ni = normals.size();
			{
				array<Vector3, 3> faceVertices = {
					vertices.at(vi0),
					vertices.at(vi1),
					vertices.at(vi2)
				};
				array<Vector3, 3> faceNormals;
				ModelHelper::computeNormals(faceVertices, faceNormals);
				for (auto& normal : faceNormals) {
					normals.push_back(normal);
				}
			}
			faces.push_back(Face(group, vi0, vi1, vi2, ni + 0, ni + 1, ni + 2));
		}
	}
	// set up faces entity
	FacesEntity groupFacesEntity(group, "faces entity");
	groupFacesEntity.setMaterial(material);
	groupFacesEntity.setFaces(&faces);
	// group faces entities
	vector<FacesEntity> groupFacesEntities;
	groupFacesEntities.push_back(groupFacesEntity);
	// setup group vertex data
	group->setVertices(vertices);
	group->setNormals(normals);
	group->setFacesEntities(groupFacesEntities);
	// determine features
	group->determineFeatures();
	// register group
	(*model->getGroups())["group"] = group;
	(*model->getSubGroups())["group"] = group;
	// prepare for indexed rendering
	ModelHelper::computeNormals(model);
	ModelHelper::prepareForIndexedRendering(model);
	//
	return model;
}

Model* PrimitiveModel::createCapsuleModel(Capsule* capsule, const string& id, int32_t segmentsX, int32_t segmentsY)
{
	// capsule properties
	auto radius = capsule->getRadius();
	auto& a = capsule->getA();
	auto& b = capsule->getB();
	auto center = a.clone().add(b).scale(0.5f);
	// rotation quaternion
	Quaternion rotationQuaternion;
	rotationQuaternion.identity();
	// angle between a and b
	Vector3 yAxis(0.0f, -1.0f, 0.0f);
	Vector3 abNormalized = a.clone().sub(b).normalize();
	auto& abNormalizedVectorXYZ = abNormalized.getArray();
	Vector3 rotationAxis;
	if (Math::abs(abNormalizedVectorXYZ[0]) < Math::EPSILON && Math::abs(abNormalizedVectorXYZ[2]) < Math::EPSILON) {
		rotationAxis.set(abNormalizedVectorXYZ[1], 0.0f, 0.0f);
	} else {
		Vector3::computeCrossProduct(yAxis, abNormalized, rotationAxis).normalize();
	}
	auto angle = Vector3::computeAngle(yAxis, abNormalized, yAxis);
	rotationQuaternion.rotate(angle, rotationAxis);
	// model
	auto model = new Model(id, id, UpVector::Y_UP, RotationOrder::XYZ, nullptr);
	// material
	auto material = new Material("tdme.primitive.material");
	material->setAmbientColor(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	material->setDiffuseColor(Color4(1.0f, 0.5f, 0.5f, 0.5f));
	material->setSpecularColor(Color4(0.0f, 0.0f, 0.0f, 1.0f));
	(*model->getMaterials())[material->getId()] = material;
	// group
	auto group = new Group(model, nullptr, "group", "group");
	// vertices
	vector<Vector3> vertices;
	//	bottom half sphere
	for (auto ySegment = 0; ySegment < segmentsY / 2; ySegment++)
	for (auto xSegment = 0; xSegment < segmentsX; xSegment++) {
		auto vertex = Vector3();
		rotationQuaternion.multiply(
			Vector3(
				((Math::sin(Math::PI * ySegment / segmentsY) * Math::cos(Math::PI * 2 * xSegment / segmentsX))),
				((Math::cos(Math::PI * ySegment / segmentsY))),
				((Math::sin(Math::PI * ySegment / segmentsY) * Math::sin(Math::PI * 2 * xSegment / segmentsX)))
			),
			vertex
		);
		vertex.scale(radius);
		vertex.add(b);
		vertices.push_back(transformVector3(capsule, toRP3DVector3(vertex)));
	}
	//	top half sphere
	for (auto ySegment = segmentsY / 2; ySegment < segmentsY + 1; ySegment++)
	for (auto xSegment = 0; xSegment < segmentsX; xSegment++) {
		auto vertex = Vector3();
		rotationQuaternion.multiply(
			Vector3(
				((Math::sin(Math::PI * ySegment / segmentsY) * Math::cos(Math::PI * 2 * xSegment / segmentsX))),
				((Math::cos(Math::PI * ySegment / segmentsY))),
				((Math::sin(Math::PI * ySegment / segmentsY) * Math::sin(Math::PI * 2 * xSegment / segmentsX)))
			),
			vertex
		);
		vertex.scale(radius);
		vertex.add(a);
		vertices.push_back(transformVector3(capsule, toRP3DVector3(vertex)));
	}
	// normals
	vector<Vector3> normals;
	// faces
	vector<Face> faces;
	int32_t vi0, vi1, vi2;
	int32_t ni;
	for (auto y = 0; y < segmentsY + 1; y++) {
		for (auto x = 0; x < segmentsX; x++) {
			vi0 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			vi1 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			vi2 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			ni = normals.size();
			{
				array<Vector3, 3> faceVertices = {
					vertices.at(vi0),
					vertices.at(vi1),
					vertices.at(vi2)
				};
				array<Vector3, 3> faceNormals;
				ModelHelper::computeNormals(faceVertices, faceNormals);
				for (auto& normal : faceNormals) {
					normals.push_back(normal);
				}
			}
			faces.push_back(Face(group, vi0, vi1, vi2, ni + 0, ni + 1, ni + 2));
			vi0 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			vi1 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			vi2 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			{
				array<Vector3, 3> faceVertices = {
					vertices.at(vi0),
					vertices.at(vi1),
					vertices.at(vi2)
				};
				array<Vector3, 3> faceNormals;
				ModelHelper::computeNormals(faceVertices, faceNormals);
				for (auto& normal : faceNormals) {
					normals.push_back(normal);
				}
			}
			faces.push_back(Face(group, vi0, vi1, vi2, ni + 0, ni + 1, ni + 2));
		}
	}
	// group faces entities
	FacesEntity groupFacesEntity(group, "faces entity");
	groupFacesEntity.setMaterial(material);
	groupFacesEntity.setFaces(&faces);
	// set up faces entity
	vector<FacesEntity> groupFacesEntities;
	groupFacesEntities.push_back(groupFacesEntity);
	// setup group vertex data
	group->setVertices(vertices);
	group->setNormals(normals);
	group->setFacesEntities(groupFacesEntities);
	// determine features
	group->determineFeatures();
	// register group
	(*model->getGroups())["group"] = group;
	(*model->getSubGroups())["group"] = group;
	// prepare for indexed rendering
	ModelHelper::computeNormals(model);
	ModelHelper::prepareForIndexedRendering(model);
	//
	return model;
}

Model* PrimitiveModel::createConvexMeshModel(ConvexMesh* mesh, const string& id) {
	Console::println("PrimitiveModel::createConvexMeshModel(): This is not supported. Rather load the model and use PrimitiveModel::setupConvexMeshModel().");
	return nullptr;
}

void PrimitiveModel::setupConvexMeshModel(Model* model)
{
	// TODO: take bounding volume scale into account
	//	Note: there is no hurry as LE and ME do not use scale for level editor entity bounding volumes
	model->getImportTransformationsMatrix().scale(1.01f);
	auto material = new Material("tdme.primitive.material");
	material->setAmbientColor(Color4(0.5f, 0.5f, 0.5f, 1.0f));
	material->setDiffuseColor(Color4(1.0f, 0.5f, 0.5f, 0.5f));
	material->setSpecularColor(Color4(0.0f, 0.0f, 0.0f, 1.0f));
	(*model->getMaterials())[material->getId()] = material;
	setupConvexMeshMaterial(model->getSubGroups(), material);
}

void PrimitiveModel::setupConvexMeshMaterial(map<string, Group*>* groups, Material* material)
{
	for (auto it: *groups) {
		Group* group = it.second;
		for (auto& faceEntity : *group->getFacesEntities()) {
			faceEntity.setMaterial(material);
		}
		setupConvexMeshMaterial(group->getSubGroups(), material);
	}
}

Model* PrimitiveModel::createModel(BoundingBox* boundingVolume, const string& id)
{
	return PrimitiveModel::createBoundingBoxModel(boundingVolume, id);
}

Model* PrimitiveModel::createModel(BoundingVolume* boundingVolume, const string& id)
{
	if (dynamic_cast< OrientedBoundingBox* >(boundingVolume) != nullptr) {
		return PrimitiveModel::createOrientedBoundingBoxModel(dynamic_cast< OrientedBoundingBox* >(boundingVolume), id);
	} else
	if (dynamic_cast< Sphere* >(boundingVolume) != nullptr) {
		return PrimitiveModel::createSphereModel(dynamic_cast< Sphere* >(boundingVolume), id, SPHERE_SEGMENTS_X, SPHERE_SEGMENTS_Y);
	} else
	if (dynamic_cast< Capsule* >(boundingVolume) != nullptr) {
		return PrimitiveModel::createCapsuleModel(dynamic_cast< Capsule* >(boundingVolume), id, CAPSULE_SEGMENTS_X, CAPSULE_SEGMENTS_Y);
	} else
	if (dynamic_cast< ConvexMesh* >(boundingVolume) != nullptr) {
		return PrimitiveModel::createConvexMeshModel(dynamic_cast< ConvexMesh* >(boundingVolume), id);
	} else {
		Console::println(string("PrimitiveModel::createModel(): unsupported bounding volume"));
		return nullptr;
	}
}
