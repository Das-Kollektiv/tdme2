#include <tdme/engine/subsystems/rendering/Object3DInternal.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/subsystems/rendering/ModelUtilitiesInternal.h>
#include <tdme/engine/subsystems/rendering/Object3DGroup.h>
#include <tdme/math/Vector3.h>

using std::string;

using tdme::engine::subsystems::rendering::Object3DInternal;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::model::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::engine::subsystems::rendering::ModelUtilitiesInternal;
using tdme::math::Vector3;

Object3DInternal::Object3DInternal(const string& id, Model* model) :
	Object3DBase(model, true, Engine::animationProcessingTarget)
{
	this->id = id;
	enabled = true;
	pickable = false;
	dynamicShadowing = false;
	effectColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	effectColorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
	boundingBox.fromBoundingVolume(model->getBoundingBox());
	boundingBoxTransformed.fromBoundingVolume(model->getBoundingBox());
	updateBoundingVolume();
}

Object3DInternal::~Object3DInternal() {
}

void Object3DInternal::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

void Object3DInternal::setPickable(bool pickable)
{
	this->pickable = pickable;
}

void Object3DInternal::setDynamicShadowingEnabled(bool dynamicShadowing)
{
	this->dynamicShadowing = dynamicShadowing;
}

void Object3DInternal::bindDiffuseTexture(FrameBuffer* frameBuffer, const string& groupId, const string& facesEntityId)
{
	bindDiffuseTexture(frameBuffer->getColorBufferTextureId(), groupId, facesEntityId);
}

void Object3DInternal::unbindDiffuseTexture(const string& groupId, const string& facesEntityId)
{
	bindDiffuseTexture(Object3DGroup::TEXTUREID_NONE, groupId, facesEntityId);
}

void Object3DInternal::bindDiffuseTexture(int32_t textureId, const string& groupId, const string& facesEntityId)
{
	for (auto i = 0; i < object3dGroups.size(); i++) {
		auto object3DGroup = object3dGroups[i];
		// skip if a group is desired but not matching
		if (groupId != "" && groupId != object3DGroup->group->getId())
			continue;

		auto& facesEntities = object3DGroup->group->getFacesEntities();
		for (auto facesEntityIdx = 0; facesEntityIdx < facesEntities.size(); facesEntityIdx++) {
			auto& facesEntity = facesEntities[facesEntityIdx];
			// skip if a faces entity is desired but not matching
			if (facesEntityId != "" && facesEntityId != facesEntity.getId())
				continue;
			// set dynamic texture id
			object3DGroup->dynamicDiffuseTextureIdsByEntities[facesEntityIdx] = textureId;
		}
	}
}

void Object3DInternal::setTextureMatrix(const Matrix2D3x3& textureMatrix, const string& groupId, const string& facesEntityId) {
	for (auto i = 0; i < object3dGroups.size(); i++) {
		auto object3DGroup = object3dGroups[i];
		// skip if a group is desired but not matching
		if (groupId != "" && groupId != object3DGroup->group->getId())
			continue;

		auto& facesEntities = object3DGroup->group->getFacesEntities();
		for (auto facesEntityIdx = 0; facesEntityIdx < facesEntities.size(); facesEntityIdx++) {
			auto& facesEntity = facesEntities[facesEntityIdx];
			// skip if a faces entity is desired but not matching
			if (facesEntityId != "" && facesEntityId != facesEntity.getId())
				continue;
			// set dynamic texture id
			object3DGroup->textureMatricesByEntities[facesEntityIdx].set(textureMatrix);
		}
	}
}

void Object3DInternal::setTransformationsMatrix(const string& id, const Matrix4x4& matrix) {
	Object3DBase::setTransformationsMatrix(id, matrix);
	map<string, Matrix4x4*> _overridenTransformationsMatrices;
	for (auto overridenTransformationsMatrixIt: overridenTransformationsMatrices) {
		_overridenTransformationsMatrices[overridenTransformationsMatrixIt.first] = new Matrix4x4(*overridenTransformationsMatrixIt.second);
	}
	auto newBoundingBox = ModelUtilitiesInternal::createBoundingBox(this->getModel(), _overridenTransformationsMatrices);
	boundingBox.fromBoundingVolume(newBoundingBox);
	delete newBoundingBox;
}

void Object3DInternal::unsetTransformationsMatrix(const string& id) {
	Object3DBase::unsetTransformationsMatrix(id);
	map<string, Matrix4x4*> _overridenTransformationsMatrices;
	for (auto overridenTransformationsMatrixIt: overridenTransformationsMatrices) {
		_overridenTransformationsMatrices[overridenTransformationsMatrixIt.first] = new Matrix4x4(*overridenTransformationsMatrixIt.second);
	}
	auto newBoundingBox = ModelUtilitiesInternal::createBoundingBox(this->getModel(), _overridenTransformationsMatrices);
	boundingBox.fromBoundingVolume(newBoundingBox);
	delete newBoundingBox;
}

void Object3DInternal::initialize()
{
	Object3DBase::initialize();
}

void Object3DInternal::dispose()
{
	Object3DBase::dispose();
}

void Object3DInternal::fromTransformations(const Transformations& transformations)
{
	Object3DBase::fromTransformations(transformations);
	updateBoundingVolume();
}

void Object3DInternal::update()
{
	Object3DBase::update();
	updateBoundingVolume();
}

