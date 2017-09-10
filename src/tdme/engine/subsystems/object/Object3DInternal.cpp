#include <tdme/engine/subsystems/object/Object3DInternal.h>

#include <string>

#include <java/lang/String.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/subsystems/object/Object3DGroup.h>
#include <tdme/engine/subsystems/object/Object3DGroupVBORenderer.h>
#include <tdme/math/Vector3.h>

using std::wstring;

using tdme::engine::subsystems::object::Object3DInternal;
using java::lang::String;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::model::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DGroupVBORenderer;
using tdme::math::Vector3;

Object3DInternal::Object3DInternal(const wstring& id, Model* model) :
	Object3DBase(model, true, Engine::animationProcessingTarget)
{
	this->id = id;
	enabled = true;
	pickable = false;
	dynamicShadowing = false;
	effectColorMul = new Color4(1.0f, 1.0f, 1.0f, 1.0f);
	effectColorAdd = new Color4(0.0f, 0.0f, 0.0f, 0.0f);
	boundingBox = dynamic_cast< BoundingBox* >(model->getBoundingBox()->clone());
	boundingBoxTransformed = dynamic_cast< BoundingBox* >(boundingBox->clone());
	boundingBoxTransformed->fromBoundingVolumeWithTransformations(boundingBox, this);
	boundingBoxTransformed->getMin()->sub(0.05f);
	boundingBoxTransformed->getMax()->add(0.05f);
	boundingBoxTransformed->update();
}

const wstring& Object3DInternal::getId()
{
	return id;
}

bool Object3DInternal::isEnabled()
{
	return enabled;
}

void Object3DInternal::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

bool Object3DInternal::isPickable()
{
	return pickable;
}

void Object3DInternal::setPickable(bool pickable)
{
	this->pickable = pickable;
}

bool Object3DInternal::isDynamicShadowingEnabled()
{
	return dynamicShadowing;
}

void Object3DInternal::setDynamicShadowingEnabled(bool dynamicShadowing)
{
	this->dynamicShadowing = dynamicShadowing;
}

Color4* Object3DInternal::getEffectColorMul()
{
	return &effectColorMul;
}

Color4* Object3DInternal::getEffectColorAdd()
{
	return &effectColorAdd;
}

BoundingBox* Object3DInternal::getBoundingBox()
{
	return boundingBox;
}

BoundingBox* Object3DInternal::getBoundingBoxTransformed()
{
	return boundingBoxTransformed;
}

void Object3DInternal::bindDiffuseTexture(FrameBuffer* frameBuffer)
{
	setDynamicDiffuseTexture(L"", L"", frameBuffer->getColorBufferTextureId());
}

void Object3DInternal::bindDiffuseTexture(const wstring& groupId, FrameBuffer* frameBuffer)
{
	setDynamicDiffuseTexture(groupId, L"", frameBuffer->getColorBufferTextureId());
}

void Object3DInternal::bindDiffuseTexture(const wstring& groupId, const wstring& facesEntityId, FrameBuffer* frameBuffer)
{
	setDynamicDiffuseTexture(groupId, facesEntityId, frameBuffer->getColorBufferTextureId());
}

void Object3DInternal::unbindDiffuseTexture()
{
	setDynamicDiffuseTexture(L"", L"", Object3DGroup::GLTEXTUREID_NONE);
}

void Object3DInternal::unbindDiffuseTexture(const wstring& groupId)
{
	setDynamicDiffuseTexture(groupId, L"", Object3DGroup::GLTEXTUREID_NONE);
}

void Object3DInternal::unbindDiffuseTexture(const wstring& groupId, const wstring& facesEntityId)
{
	setDynamicDiffuseTexture(groupId, facesEntityId, Object3DGroup::GLTEXTUREID_NONE);
}

void Object3DInternal::setDynamicDiffuseTexture(const wstring& groupId, const wstring& facesEntityId, int32_t textureId)
{
	for (auto i = 0; i < object3dGroups.size(); i++) {
		auto object3DGroup = object3dGroups[i];
		if (groupId != L"" && groupId != object3DGroup->group->getId())
			continue;

		auto facesEntities = object3DGroup->group->getFacesEntities();
		for (auto facesEntityIdx = 0; facesEntityIdx < facesEntities->size(); facesEntityIdx++) {
			auto& facesEntity = (*facesEntities)[facesEntityIdx];
			if (facesEntityId != L"" && facesEntityId != facesEntity.getId())
				continue;

			object3DGroup->dynamicDiffuseTextureIdsByEntities[facesEntityIdx] = textureId;
		}
	}
}

void Object3DInternal::initialize()
{
	Object3DBase::initialize();
}

void Object3DInternal::dispose()
{
	Object3DBase::dispose();
	for (auto i = 0; i < object3dGroups.size(); i++) {
		auto object3DGroup = object3dGroups[i];
		object3DGroup->renderer->dispose();
		object3DGroup->dispose();
	}
}

void Object3DInternal::fromTransformations(Transformations* transformations)
{
	Object3DBase::fromTransformations(transformations);
	boundingBoxTransformed->fromBoundingVolumeWithTransformations(boundingBox, this);
	boundingBoxTransformed->getMin()->sub(0.05f);
	boundingBoxTransformed->getMax()->add(0.05f);
	boundingBoxTransformed->update();
}

void Object3DInternal::update()
{
	Object3DBase::update();
	boundingBoxTransformed->fromBoundingVolumeWithTransformations(boundingBox, this);
	boundingBoxTransformed->getMin()->sub(0.05f);
	boundingBoxTransformed->getMax()->add(0.05f);
	boundingBoxTransformed->update();
}

