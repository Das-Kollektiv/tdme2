#include <tdme/engine/Object3DRenderGroup.h>

#include <string>
#include <vector>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/Console.h>

using std::string;
using std::vector;

using tdme::engine::Object3DRenderGroup;
using tdme::engine::Engine;
using tdme::engine::Object3D;
using tdme::engine::Partition;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::Transformations;
using tdme::engine::primitives::BoundingBox;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Matrix4x4;
using tdme::utils::Console;

Object3DRenderGroup::Object3DRenderGroup(
	const string& id
):
	id(id)
{
	this->enabled = true;
	this->pickable = false;
	this->dynamicShadowing = false;
	this->effectColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	this->effectColorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
	this->identityMatrix.identity();
	this->combinedModel = nullptr;
}

Object3DRenderGroup::~Object3DRenderGroup() {
	for (auto object: objects) delete object;
	for (auto object: objectsCombined) delete object;
	if (combinedModel != nullptr) delete combinedModel;
}

void Object3DRenderGroup::computeBoundingBox() {
	if (objects.size() == 0) return;

	float minX = objects[0]->getBoundingBoxTransformed()->getMin().getX();
	float minY = objects[0]->getBoundingBoxTransformed()->getMin().getY();
	float minZ = objects[0]->getBoundingBoxTransformed()->getMin().getZ();
	float maxX = objects[0]->getBoundingBoxTransformed()->getMax().getX();
	float maxY = objects[0]->getBoundingBoxTransformed()->getMax().getY();
	float maxZ = objects[0]->getBoundingBoxTransformed()->getMax().getZ();
	for (auto i = 1; i < objects.size(); i++) {
		minX = Math::min(minX, objects[i]->getBoundingBoxTransformed()->getMin().getX());
		minY = Math::min(minY, objects[i]->getBoundingBoxTransformed()->getMin().getY());
		minZ = Math::min(minZ, objects[i]->getBoundingBoxTransformed()->getMin().getZ());
		maxX = Math::max(maxX, objects[i]->getBoundingBoxTransformed()->getMax().getX());
		maxY = Math::max(maxY, objects[i]->getBoundingBoxTransformed()->getMax().getY());
		maxZ = Math::max(maxZ, objects[i]->getBoundingBoxTransformed()->getMax().getZ());
	}

	boundingBox.getMin().set(minX, minY, minZ);
	boundingBox.getMax().set(maxX, maxY, maxZ);
	boundingBox.update();
}

void Object3DRenderGroup::combineGroup(Group* sourceGroup, const Matrix4x4& parentTransformationsMatrix, Model* combinedModel) {
	Matrix4x4 transformationsMatrix;
	transformationsMatrix.set(sourceGroup->getTransformationsMatrix());
	transformationsMatrix.multiply(parentTransformationsMatrix);

	Vector3 vertex0;
	Vector3 vertex1;
	Vector3 vertex2;
	Vector3 normal0;
	Vector3 normal1;
	Vector3 normal2;
	TextureCoordinate textureCoordinate0;
	TextureCoordinate textureCoordinate1;
	TextureCoordinate textureCoordinate2;
	Vector3 tangent0;
	Vector3 tangent1;
	Vector3 tangent2;
	Vector3 bitangent0;
	Vector3 bitangent1;
	Vector3 bitangent2;

	Vector3 vertex0Transformed;
	Vector3 vertex1Transformed;
	Vector3 vertex2Transformed;

	// create group in combined model
	auto combinedModelGroup = combinedModel->getGroupById(sourceGroup->getId());
	if (combinedModelGroup == nullptr) {
		combinedModelGroup = new Group(
			combinedModel,
			sourceGroup->getParentGroup() == nullptr?nullptr:combinedModel->getGroupById(sourceGroup->getParentGroup()->getId()),
			sourceGroup->getId(),
			sourceGroup->getName()
		);
		if (sourceGroup->getParentGroup() == nullptr) {
			(*combinedModel->getSubGroups())[combinedModelGroup->getId()] = combinedModelGroup;
		} else {
			(*combinedModelGroup->getParentGroup()->getSubGroups())[combinedModelGroup->getId()] = combinedModelGroup;
		}
		(*combinedModel->getGroups())[combinedModelGroup->getId()] = combinedModelGroup;
	}

	for (auto& facesEntity: *sourceGroup->getFacesEntities()) {
		bool haveTextureCoordinates = facesEntity.isTextureCoordinatesAvailable();
		bool haveTangentsBitangents = facesEntity.isTangentBitangentAvailable();

		// get faces entity
		FacesEntity* combinedModelGroupFacesEntity = nullptr;
		for (auto& combinedModelGroupFacesEntityExisting: *combinedModelGroup->getFacesEntities()) {
			if (combinedModelGroupFacesEntityExisting.getId() == facesEntity.getId()) {
				combinedModelGroupFacesEntity = &combinedModelGroupFacesEntityExisting;
			}
		}
		// create
		if (combinedModelGroupFacesEntity == nullptr) {
			combinedModelGroup->getFacesEntities()->push_back(
				FacesEntity(
					combinedModelGroup,
					facesEntity.getId()
				)
			);
			combinedModelGroupFacesEntity = &(*combinedModelGroup->getFacesEntities())[combinedModelGroup->getFacesEntities()->size() - 1];
			auto combinedModelGroupFacesEntityMaterial = (*combinedModel->getMaterials())[facesEntity.getMaterial()->getId()];
			if (combinedModelGroupFacesEntityMaterial == nullptr) {
				combinedModelGroupFacesEntityMaterial = ModelHelper::cloneMaterial(facesEntity.getMaterial());
				(*combinedModel->getMaterials())[combinedModelGroupFacesEntityMaterial->getId()] = combinedModelGroupFacesEntityMaterial;
			}
			combinedModelGroupFacesEntity->setMaterial(combinedModelGroupFacesEntityMaterial);
		}

		// add faces
		for (auto& face: *facesEntity.getFaces()) {
			// get face vertices and such
			auto& vertexIndices = *face.getVertexIndices();
			auto& normalIndices = *face.getNormalIndices();
			auto& textureCoordinatesIndices = *face.getTextureCoordinateIndices();
			auto& tangentIndices = *face.getTangentIndices();
			auto& bitangentIndices = *face.getBitangentIndices();
			vertex0.set((*sourceGroup->getVertices())[vertexIndices[0]]);
			vertex1.set((*sourceGroup->getVertices())[vertexIndices[1]]);
			vertex2.set((*sourceGroup->getVertices())[vertexIndices[2]]);
			transformationsMatrix.multiply(vertex0, vertex0);
			transformationsMatrix.multiply(vertex1, vertex1);
			transformationsMatrix.multiply(vertex2, vertex2);
			normal0.set((*sourceGroup->getNormals())[normalIndices[0]]);
			normal1.set((*sourceGroup->getNormals())[normalIndices[1]]);
			normal2.set((*sourceGroup->getNormals())[normalIndices[2]]);
			transformationsMatrix.multiplyNoTranslation(normal0, normal0);
			transformationsMatrix.multiplyNoTranslation(normal1, normal1);
			transformationsMatrix.multiplyNoTranslation(normal2, normal2);
			if (haveTextureCoordinates == true) {
				textureCoordinate0.set((*sourceGroup->getTextureCoordinates())[textureCoordinatesIndices[0]]);
				textureCoordinate1.set((*sourceGroup->getTextureCoordinates())[textureCoordinatesIndices[1]]);
				textureCoordinate2.set((*sourceGroup->getTextureCoordinates())[textureCoordinatesIndices[2]]);
			}
			if (haveTangentsBitangents == true) {
				tangent0.set((*sourceGroup->getTangents())[tangentIndices[0]]);
				tangent1.set((*sourceGroup->getTangents())[tangentIndices[1]]);
				tangent2.set((*sourceGroup->getTangents())[tangentIndices[2]]);
				transformationsMatrix.multiplyNoTranslation(tangent0, tangent0);
				transformationsMatrix.multiplyNoTranslation(tangent1, tangent1);
				transformationsMatrix.multiplyNoTranslation(tangent2, tangent2);
				bitangent0.set((*sourceGroup->getBitangents())[bitangentIndices[0]]);
				bitangent1.set((*sourceGroup->getBitangents())[bitangentIndices[1]]);
				bitangent2.set((*sourceGroup->getBitangents())[bitangentIndices[2]]);
				transformationsMatrix.multiplyNoTranslation(bitangent0, bitangent0);
				transformationsMatrix.multiplyNoTranslation(bitangent1, bitangent1);
				transformationsMatrix.multiplyNoTranslation(bitangent2, bitangent2);
			}

			// add vertices and such
			auto verticesIdx = combinedModelGroup->getVertices()->size();
			combinedModelGroup->getVertices()->push_back(vertex0);
			combinedModelGroup->getVertices()->push_back(vertex1);
			combinedModelGroup->getVertices()->push_back(vertex2);
			combinedModelGroup->getNormals()->push_back(normal0);
			combinedModelGroup->getNormals()->push_back(normal1);
			combinedModelGroup->getNormals()->push_back(normal2);
			if (haveTextureCoordinates == true) {
				combinedModelGroup->getTextureCoordinates()->push_back(textureCoordinate0);
				combinedModelGroup->getTextureCoordinates()->push_back(textureCoordinate1);
				combinedModelGroup->getTextureCoordinates()->push_back(textureCoordinate2);
			}
			if (haveTangentsBitangents == true) {
				combinedModelGroup->getTangents()->push_back(tangent0);
				combinedModelGroup->getTangents()->push_back(tangent1);
				combinedModelGroup->getTangents()->push_back(tangent2);
				combinedModelGroup->getBitangents()->push_back(bitangent0);
				combinedModelGroup->getBitangents()->push_back(bitangent1);
				combinedModelGroup->getBitangents()->push_back(bitangent2);
			}
			combinedModelGroupFacesEntity->getFaces()->push_back(
				Face(
					combinedModelGroup,
					verticesIdx + 0,
					verticesIdx + 1,
					verticesIdx + 2,
					verticesIdx + 0,
					verticesIdx + 1,
					verticesIdx + 2
				)
			);
			if (haveTextureCoordinates == true) {
				(*combinedModelGroupFacesEntity->getFaces())[combinedModelGroupFacesEntity->getFaces()->size() - 1].setTextureCoordinateIndices(
					verticesIdx + 0,
					verticesIdx + 1,
					verticesIdx + 2
				);
			}
			if (haveTangentsBitangents == true) {
				(*combinedModelGroupFacesEntity->getFaces())[combinedModelGroupFacesEntity->getFaces()->size() - 1].setTangentIndices(
					verticesIdx + 0,
					verticesIdx + 1,
					verticesIdx + 2
				);
				(*combinedModelGroupFacesEntity->getFaces())[combinedModelGroupFacesEntity->getFaces()->size() - 1].setBitangentIndices(
					verticesIdx + 0,
					verticesIdx + 1,
					verticesIdx + 2
				);
			}
		}
	}

	combinedModelGroup->determineFeatures();

	for (auto groupIt: *sourceGroup->getSubGroups()) {
		combineGroup(groupIt.second, transformationsMatrix, combinedModel);
	}
}

void Object3DRenderGroup::combine(Model* model, const Transformations& transformations, Model* combinedModel) {
	Matrix4x4 transformationsMatrix;
	transformationsMatrix.set(model->getImportTransformationsMatrix());
	transformationsMatrix.multiply(transformations.getTransformationsMatrix());
	for (auto groupIt: *model->getSubGroups()) {
		combineGroup(groupIt.second, transformationsMatrix, combinedModel);
	}
}

void Object3DRenderGroup::updateRenderGroup() {
	// combine objects to a new model
	for (auto object: objectsCombined) {
		object->dispose();
		delete object;
	}
	if (combinedModel != nullptr) {
		delete combinedModel;
		combinedModel = nullptr;
	}
	objectsCombined.clear();
	if (objects.size() > 0) {
		auto model = objects[0]->getModel();
		// combine objects to a new model
		combinedModel = new Model(
			id,
			id,
			model->getUpVector(),
			model->getRotationOrder(),
			nullptr
		);
		for (auto object: objects) {
			combine(model, object->getTransformations(), combinedModel);
		}
		ModelHelper::createDefaultAnimation(combinedModel, 0);
		ModelHelper::setupJoints(combinedModel);
		ModelHelper::fixAnimationLength(combinedModel);
		ModelHelper::prepareForIndexedRendering(combinedModel);
		auto objectCombined = new Object3D(id, combinedModel);
		objectCombined->initialize();
		objectsCombined.push_back(objectCombined);
	}
}

void Object3DRenderGroup::addObject(Object3D* object) {
	if (objects.size() > 0 && objects[0]->getModel() != object->getModel()) {
		Console::println("Object3DRenderGroup::addObject(): a object rendergroup is designed for a single model with multiple objects. Not adding object!");
	}
	// initialize object
	object->initialize();
	// add to objects
	objects.push_back(object);
}

void Object3DRenderGroup::setEngine(Engine* engine)
{
	this->engine = engine;
}

void Object3DRenderGroup::setRenderer(GLRenderer* renderer)
{
}

void Object3DRenderGroup::fromTransformations(const Transformations& transformations)
{
	Transformations::fromTransformations(transformations);
	// update bounding box transformed
	boundingBoxTransformed.fromBoundingVolumeWithTransformations(&boundingBox, *this);
	// compute bounding box
	computeBoundingBox();
	// update object
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void Object3DRenderGroup::update()
{
	Transformations::update();
	// compute bounding box
	computeBoundingBox();
	// update render group
	updateRenderGroup();
	// update bounding box transformed
	boundingBoxTransformed.fromBoundingVolumeWithTransformations(&boundingBox, *this);
	// update object
	if (frustumCulling == true && engine != nullptr && enabled == true) engine->partition->updateEntity(this);
}

void Object3DRenderGroup::setEnabled(bool enabled)
{
	// return if enable state has not changed
	if (this->enabled == enabled) return;
	// frustum culling enabled?
	if (frustumCulling == true) {
		// yeo, add or remove from partition
		if (enabled == true) {
			if (engine != nullptr) engine->partition->addEntity(this);
		} else {
			if (engine != nullptr) engine->partition->removeEntity(this);
		}
	}
}

bool Object3DRenderGroup::isFrustumCulling() {
	return frustumCulling;
}

void Object3DRenderGroup::setFrustumCulling(bool frustumCulling) {
	// check if enabled and engine attached
	if (enabled == true && engine != nullptr) {
		// had frustum culling
		if (this->frustumCulling == true) {
			// yep, remove if set to false now
			if (frustumCulling == false) engine->partition->removeEntity(this);
		} else {
			// yep, add if set to true now
			if (frustumCulling == true) engine->partition->addEntity(this);
		}
	}
	this->frustumCulling = frustumCulling;
	// delegate change to engine
	if (engine != nullptr) engine->updateEntity(this);
}

void Object3DRenderGroup::dispose()
{
	// delegate to objects
	for (auto object: objects) object->dispose();
	// delegate to objects combined
	for (auto object: objectsCombined) object->dispose();
	if (combinedModel != nullptr) {
		delete combinedModel;
		combinedModel = nullptr;
	}
}

void Object3DRenderGroup::initialize()
{
}

void Object3DRenderGroup::setDynamicShadowingEnabled(bool dynamicShadowing)
{
	this->dynamicShadowing = dynamicShadowing;
}

void Object3DRenderGroup::setPickable(bool pickable)
{
	this->pickable = pickable;
}

Matrix4x4* Object3DRenderGroup::getTransformationsMatrix(const string& id)
{
	return &identityMatrix;
}

const Vector3& Object3DRenderGroup::getTranslation() const {
	return Transformations::getTranslation();
}

void Object3DRenderGroup::setTranslation(const Vector3& translation) {
	Transformations::setTranslation(translation);
}

const Vector3& Object3DRenderGroup::getScale() const {
	return Transformations::getScale();
}

void Object3DRenderGroup::setScale(const Vector3& scale) {
	Transformations::setScale(scale);
}

const Vector3& Object3DRenderGroup::getPivot() const {
	return Transformations::getPivot();
}

void Object3DRenderGroup::setPivot(const Vector3& pivot) {
	Transformations::setPivot(pivot);
}

const int Object3DRenderGroup::getRotationCount() const {
	return Transformations::getRotationCount();
}

Rotation& Object3DRenderGroup::getRotation(int idx) {
	return Transformations::getRotation(idx);
}

void Object3DRenderGroup::addRotation(const Vector3& axis, const float angle) {
	Transformations::addRotation(axis, angle);
}

void Object3DRenderGroup::removeRotation(const int idx) {
	Transformations::removeRotation(idx);
}

const Vector3& Object3DRenderGroup::getRotationAxis(const int idx) const {
	return Transformations::getRotationAxis(idx);
}

void Object3DRenderGroup::setRotationAxis(const int idx, const Vector3& axis) {
	Transformations::setRotationAxis(idx, axis);
}

const float Object3DRenderGroup::getRotationAngle(const int idx) const {
	return Transformations::getRotationAngle(idx);
}

void Object3DRenderGroup::setRotationAngle(const int idx, const float angle) {
	Transformations::setRotationAngle(idx, angle);
}

const Quaternion& Object3DRenderGroup::getRotationsQuaternion() const {
	return Transformations::getRotationsQuaternion();
}
