#include <tdme/engine/subsystems/object/ModelUtilitiesInternal.h>

#include <map>
#include <string>

#include <tdme/engine/Timing.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/object/AnimationState.h>
#include <tdme/engine/subsystems/object/ModelStatistics.h>
#include <tdme/engine/subsystems/object/Object3DGroup.h>
#include <tdme/engine/subsystems/object/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/object/Object3DModelInternal.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include "ModelStatistics.h"

using std::map;
using std::wstring;

using tdme::engine::subsystems::object::ModelUtilitiesInternal;
using tdme::engine::Timing;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Face;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::FacesEntity;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::object::AnimationState;
using tdme::engine::subsystems::object::ModelStatistics;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DGroupMesh;
using tdme::engine::subsystems::object::Object3DModelInternal;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

BoundingBox* ModelUtilitiesInternal::createBoundingBox(Model* model)
{
	return ModelUtilitiesInternal::createBoundingBox(new Object3DModelInternal(model));
}

BoundingBox* ModelUtilitiesInternal::createBoundingBox(Object3DModelInternal* object3DModelInternal)
{
	auto model = object3DModelInternal->getModel();
	auto defaultAnimation = model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT);
	float minX = 0.0f, minY = 0.0f, minZ = 0.0f;
	float maxX = 0.0f, maxY = 0.0f, maxZ = 0.0f;
	auto firstVertex = true;
	AnimationState animationState;
	animationState.setup = defaultAnimation;
	animationState.lastAtTime = Timing::UNDEFINED;
	animationState.currentAtTime = 0LL;
	animationState.time = 0.0f;
	animationState.finished = false;
	for (auto t = 0.0f; t <= (defaultAnimation != nullptr ? static_cast< float >(defaultAnimation->getFrames()) : 0.0f) / model->getFPS(); t += 1.0f / model->getFPS()) {
		Matrix4x4& parentTransformationsMatrix = object3DModelInternal->getModel()->getImportTransformationsMatrix();
		parentTransformationsMatrix.multiply(object3DModelInternal->getTransformationsMatrix());
		object3DModelInternal->computeTransformationsMatrices(model->getSubGroups(), parentTransformationsMatrix, &animationState, 0);
		Object3DGroup::computeTransformations(&object3DModelInternal->object3dGroups);
		for (auto object3DGroup : object3DModelInternal->object3dGroups) {
			for (auto vertex : *object3DGroup->mesh->vertices) {
				auto& vertexXYZ = vertex.getArray();
				if (firstVertex == true) {
					minX = vertexXYZ[0];
					minY = vertexXYZ[1];
					minZ = vertexXYZ[2];
					maxX = vertexXYZ[0];
					maxY = vertexXYZ[1];
					maxZ = vertexXYZ[2];
					firstVertex = false;
				} else {
					if (vertexXYZ[0] < minX) minX = vertexXYZ[0];
					if (vertexXYZ[1] < minY) minY = vertexXYZ[1];
					if (vertexXYZ[2] < minZ) minZ = vertexXYZ[2];
					if (vertexXYZ[0] > maxX) maxX = vertexXYZ[0];
					if (vertexXYZ[1] > maxY) maxY = vertexXYZ[1];
					if (vertexXYZ[2] > maxZ) maxZ = vertexXYZ[2];
				}
			}
		}
		animationState.currentAtTime = static_cast< int64_t >((t * 1000.0f));
		animationState.lastAtTime = static_cast< int64_t >((t * 1000.0f));
	}
	if (firstVertex == true)
		return nullptr;

	return new BoundingBox(new Vector3(minX, minY, minZ), new Vector3(maxX, maxY, maxZ));
}

void ModelUtilitiesInternal::invertNormals(Model* model)
{
	invertNormals(model->getSubGroups());
}

void ModelUtilitiesInternal::invertNormals(map<wstring, Group*>* groups)
{
	for (auto it: *groups) {
		Group* group = it.second;
		for (auto& normal : *group->getNormals()) {
			normal.scale(-1.0f);
		}
		invertNormals(group->getSubGroups());
	}
}

void ModelUtilitiesInternal::computeModelStatistics(Model* model, ModelStatistics* modelStatistics)
{
	Object3DModelInternal object3DModelInternal(model);
	computeModelStatistics(&object3DModelInternal, modelStatistics);
}

void ModelUtilitiesInternal::computeModelStatistics(Object3DModelInternal* object3DModelInternal, ModelStatistics* modelStatistics)
{
	map<wstring, int32_t> materialCountById;
	auto opaqueFaceCount = 0;
	auto transparentFaceCount = 0;
	for (auto object3DGroup : object3DModelInternal->object3dGroups) {
		auto facesEntities = object3DGroup->group->getFacesEntities();
		auto facesEntityIdxCount = facesEntities->size();
		for (auto faceEntityIdx = 0; faceEntityIdx < facesEntityIdxCount; faceEntityIdx++) {
			auto& facesEntity = (*facesEntities)[faceEntityIdx];
			auto faces = facesEntity.getFaces()->size();
			auto material = facesEntity.getMaterial();
			auto transparentFacesEntity = false;
			if (material != nullptr) {
				if (material->hasTransparency() == true)
					transparentFacesEntity = true;

			}
			auto materialId = material == nullptr ? L"tdme.material.none" : material->getId();
			materialCountById[materialId]++;
			if (transparentFacesEntity == true) {
				transparentFaceCount += faces;
				continue;
			}
			opaqueFaceCount += faces;
		}
	}
	auto materialCount = materialCountById.size();
	modelStatistics->opaqueFaceCount = opaqueFaceCount;
	modelStatistics->transparentFaceCount = transparentFaceCount;
	modelStatistics->materialCount = materialCount;
}

bool ModelUtilitiesInternal::equals(Model* model1, Model* model2)
{
	return ModelUtilitiesInternal::equals(new Object3DModelInternal(model1), new Object3DModelInternal(model2));
}

bool ModelUtilitiesInternal::equals(Object3DModelInternal* object3DModel1Internal, Object3DModelInternal* object3DModel2Internal)
{
	if (object3DModel1Internal->object3dGroups.size() != object3DModel2Internal->object3dGroups.size())
		return false;

	for (auto i = 0; i < object3DModel1Internal->object3dGroups.size(); i++) {
		auto object3DGroupModel1 = object3DModel1Internal->object3dGroups[i];
		auto object3DGroupModel2 = object3DModel2Internal->object3dGroups[i];
		auto facesEntitiesModel1 = object3DGroupModel1->group->getFacesEntities();
		auto facesEntitiesModel2 = object3DGroupModel2->group->getFacesEntities();
		if (object3DGroupModel1->group->getTransformationsMatrix().equals(object3DGroupModel2->group->getTransformationsMatrix()) == false)
			return false;

		if (facesEntitiesModel1->size() != facesEntitiesModel2->size())
			return false;

		for (auto j = 0; j < facesEntitiesModel1->size(); j++) {
			auto facesEntityModel1 = &(*facesEntitiesModel1)[j];
			auto facesEntityModel2 = &(*facesEntitiesModel2)[j];
			if (facesEntityModel1->getMaterial() == nullptr && facesEntityModel2->getMaterial() != nullptr)
				return false;

			if (facesEntityModel1->getMaterial() != nullptr && facesEntityModel2->getMaterial() == nullptr)
				return false;

			if (facesEntityModel1->getMaterial() != nullptr && facesEntityModel2->getMaterial() != nullptr &&
				facesEntityModel1->getMaterial()->getId() != facesEntityModel2->getMaterial()->getId()) {
				return false;
			}
			auto facesModel1 = facesEntityModel1->getFaces();
			auto facesModel2 = facesEntityModel2->getFaces();
			if (facesModel1->size() != facesModel2->size())
				return false;

			for (auto k = 0; k < facesModel1->size(); k++) {
				auto vertexIndicesModel1 = (*facesModel1)[k].getVertexIndices();
				auto vertexIndicesModel2 = (*facesModel2)[k].getVertexIndices();
				if ((*vertexIndicesModel1)[0] != (*vertexIndicesModel2)[0] ||
					(*vertexIndicesModel1)[1] != (*vertexIndicesModel2)[1] ||
					(*vertexIndicesModel1)[2] != (*vertexIndicesModel2)[2]) {
					return false;
				}
			}
		}
	}
	return true;
}
