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

	// add vertices and such
	auto combinedModelGroupVerticesIdx = combinedModelGroup->getVertices()->size();
	auto combinedModelGroupNormalsIdx = combinedModelGroup->getNormals()->size();
	auto combinedModelGroupTextureCoordinatesIdx = combinedModelGroup->getTextureCoordinates()->size();
	auto combinedModelGroupTangentsIdx = combinedModelGroup->getTangents()->size();
	auto combinedModelGroupBitangentsIdx = combinedModelGroup->getBitangents()->size();
	Vector3 tmpVector3;
	for (auto vertex: *sourceGroup->getVertices()) {
		combinedModelGroup->getVertices()->push_back(transformationsMatrix.multiply(vertex, tmpVector3));
	}
	for (auto normal: *sourceGroup->getNormals()) {
		combinedModelGroup->getNormals()->push_back(transformationsMatrix.multiplyNoTranslation(normal, tmpVector3));
	}
	for (auto textureCoordinate: *sourceGroup->getTextureCoordinates()) {
		combinedModelGroup->getTextureCoordinates()->push_back(textureCoordinate);
	}
	for (auto tangent: *sourceGroup->getTangents()) {
		combinedModelGroup->getTangents()->push_back(transformationsMatrix.multiplyNoTranslation(tangent, tmpVector3));
	}
	for (auto bitangent: *sourceGroup->getBitangents()) {
		combinedModelGroup->getBitangents()->push_back(transformationsMatrix.multiplyNoTranslation(bitangent, tmpVector3));
	}

	//
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
			auto& faceVertexIndices = *face.getVertexIndices();
			auto& faceNormalIndices = *face.getNormalIndices();
			auto& faceTextureCoordinatesIndices = *face.getTextureCoordinateIndices();
			auto& faceTangentIndices = *face.getTangentIndices();
			auto& faceBitangentIndices = *face.getBitangentIndices();

			//
			combinedModelGroupFacesEntity->getFaces()->push_back(
				Face(
					combinedModelGroup,
					combinedModelGroupVerticesIdx + faceVertexIndices[0],
					combinedModelGroupVerticesIdx + faceVertexIndices[1],
					combinedModelGroupVerticesIdx + faceVertexIndices[2],
					combinedModelGroupNormalsIdx + faceNormalIndices[0],
					combinedModelGroupNormalsIdx + faceNormalIndices[1],
					combinedModelGroupNormalsIdx + faceNormalIndices[2]
				)
			);
			if (haveTextureCoordinates == true) {
				(*combinedModelGroupFacesEntity->getFaces())[combinedModelGroupFacesEntity->getFaces()->size() - 1].setTextureCoordinateIndices(
					combinedModelGroupTextureCoordinatesIdx + faceTextureCoordinatesIndices[0],
					combinedModelGroupTextureCoordinatesIdx + faceTextureCoordinatesIndices[1],
					combinedModelGroupTextureCoordinatesIdx + faceTextureCoordinatesIndices[2]
				);
			}
			if (haveTangentsBitangents == true) {
				(*combinedModelGroupFacesEntity->getFaces())[combinedModelGroupFacesEntity->getFaces()->size() - 1].setTangentIndices(
					combinedModelGroupTangentsIdx + faceTangentIndices[0],
					combinedModelGroupTangentsIdx + faceTangentIndices[1],
					combinedModelGroupTangentsIdx + faceTangentIndices[2]
				);
				(*combinedModelGroupFacesEntity->getFaces())[combinedModelGroupFacesEntity->getFaces()->size() - 1].setBitangentIndices(
					combinedModelGroupBitangentsIdx + faceBitangentIndices[0],
					combinedModelGroupBitangentsIdx + faceBitangentIndices[1],
					combinedModelGroupBitangentsIdx + faceBitangentIndices[2]
				);
			}
		}
	}

	// features
	combinedModelGroup->determineFeatures();

	// do child groups
	for (auto groupIt: *sourceGroup->getSubGroups()) {
		combineGroup(groupIt.second, transformationsMatrix, combinedModel);
	}
}

void Object3DRenderGroup::combineObject(Model* model, const Transformations& transformations, Model* combinedModel) {
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
			combineObject(model, object->getTransformations(), combinedModel);
		}
		ModelHelper::shrinkToFit(combinedModel);
		ModelHelper::createDefaultAnimation(combinedModel, 0);
		ModelHelper::setupJoints(combinedModel);
		ModelHelper::fixAnimationLength(combinedModel);
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

