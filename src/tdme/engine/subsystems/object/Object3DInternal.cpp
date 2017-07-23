// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DInternal.java
#include <tdme/engine/subsystems/object/Object3DInternal.h>

#include <java/lang/String.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/subsystems/object/Object3DGroup.h>
#include <tdme/engine/subsystems/object/Object3DGroupVBORenderer.h>
#include <tdme/math/Vector3.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using tdme::engine::subsystems::object::Object3DInternal;
using java::lang::String;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::model::Color4;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DGroupVBORenderer;
using tdme::math::Vector3;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::FacesEntity, ::java::lang::ObjectArray > FacesEntityArray;
}  // namespace model

namespace subsystems {
namespace object {
typedef ::SubArray< ::tdme::engine::subsystems::object::Object3DGroup, ::java::lang::ObjectArray > Object3DGroupArray;
}  // namespace object
}  // namespace subsystems
}  // namespace engine
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

Object3DInternal::Object3DInternal(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Object3DInternal::Object3DInternal(String* id, Model* model) 
	: Object3DInternal(*static_cast< ::default_init_tag* >(0))
{
	ctor(id,model);
}

void Object3DInternal::ctor(String* id, Model* model)
{
	super::ctor(model, true, Engine::animationProcessingTarget);
	this->id = id;
	enabled = true;
	pickable = false;
	dynamicShadowing = false;
	effectColorMul = new Color4(1.0f, 1.0f, 1.0f, 1.0f);
	effectColorAdd = new Color4(0.0f, 0.0f, 0.0f, 0.0f);
	boundingBox = java_cast< BoundingBox* >(model->getBoundingBox()->clone());
	boundingBoxTransformed = java_cast< BoundingBox* >(boundingBox->clone());
	boundingBoxTransformed->fromBoundingVolumeWithTransformations(boundingBox, this);
	boundingBoxTransformed->getMin()->sub(0.05f);
	boundingBoxTransformed->getMax()->add(0.05f);
	boundingBoxTransformed->update();
}

String* Object3DInternal::getId()
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
	return effectColorMul;
}

Color4* Object3DInternal::getEffectColorAdd()
{
	return effectColorAdd;
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
	setDynamicDiffuseTexture(nullptr, nullptr, frameBuffer->getColorBufferTextureId());
}

void Object3DInternal::bindDiffuseTexture(String* groupId, FrameBuffer* frameBuffer)
{
	setDynamicDiffuseTexture(groupId, nullptr, frameBuffer->getColorBufferTextureId());
}

void Object3DInternal::bindDiffuseTexture(String* groupId, String* facesEntityId, FrameBuffer* frameBuffer)
{
	setDynamicDiffuseTexture(groupId, facesEntityId, frameBuffer->getColorBufferTextureId());
}

void Object3DInternal::unbindDiffuseTexture()
{
	setDynamicDiffuseTexture(nullptr, nullptr, Object3DGroup::GLTEXTUREID_NONE);
}

void Object3DInternal::unbindDiffuseTexture(String* groupId)
{
	setDynamicDiffuseTexture(groupId, nullptr, Object3DGroup::GLTEXTUREID_NONE);
}

void Object3DInternal::unbindDiffuseTexture(String* groupId, String* facesEntityId)
{
	setDynamicDiffuseTexture(groupId, facesEntityId, Object3DGroup::GLTEXTUREID_NONE);
}

void Object3DInternal::setDynamicDiffuseTexture(String* groupId, String* facesEntityId, int32_t textureId)
{
	for (auto i = 0; i < object3dGroups->length; i++) {
		auto object3DGroup = (*object3dGroups)[i];
		if (groupId != nullptr && groupId->getCPPWString() != object3DGroup->group->getId())
			continue;

		auto facesEntities = object3DGroup->group->getFacesEntities();
		for (auto facesEntityIdx = 0; facesEntityIdx < facesEntities->length; facesEntityIdx++) {
			auto facesEntity = (*facesEntities)[facesEntityIdx];
			if (facesEntityId != nullptr && facesEntityId->getCPPWString() != facesEntity->getId())
				continue;

			(*object3DGroup->dynamicDiffuseTextureIdsByEntities)[facesEntityIdx] = textureId;
		}
	}
}

void Object3DInternal::initialize()
{
	super::initialize();
}

void Object3DInternal::dispose()
{
	super::dispose();
	for (auto i = 0; i < object3dGroups->length; i++) {
		auto object3DGroup = (*object3dGroups)[i];
		object3DGroup->renderer->dispose();
		object3DGroup->dispose();
	}
}

void Object3DInternal::fromTransformations(Transformations* transformations)
{
	super::fromTransformations(transformations);
	boundingBoxTransformed->fromBoundingVolumeWithTransformations(boundingBox, this);
	boundingBoxTransformed->getMin()->sub(0.05f);
	boundingBoxTransformed->getMax()->add(0.05f);
	boundingBoxTransformed->update();
}

void Object3DInternal::update()
{
	super::update();
	boundingBoxTransformed->fromBoundingVolumeWithTransformations(boundingBox, this);
	boundingBoxTransformed->getMin()->sub(0.05f);
	boundingBoxTransformed->getMax()->add(0.05f);
	boundingBoxTransformed->update();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Object3DInternal::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.Object3DInternal", 46);
    return c;
}

java::lang::Class* Object3DInternal::getClass0()
{
	return class_();
}

