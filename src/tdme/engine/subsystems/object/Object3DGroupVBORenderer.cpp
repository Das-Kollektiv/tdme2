// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DGroupVBORenderer.java
#include <tdme/engine/subsystems/object/Object3DGroupVBORenderer.h>

#include <java/lang/Byte.h>
#include <java/lang/Float.h>
#include <java/lang/Short.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/nio/FloatBuffer.h>
#include <java/nio/ShortBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/object/Object3DGroup.h>
#include <tdme/engine/subsystems/object/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/object/Object3DVBORenderer.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Vector3.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using tdme::engine::subsystems::object::Object3DGroupVBORenderer;
using java::lang::Byte;
using java::lang::Float;
using java::lang::Short;
using java::lang::String;
using java::lang::StringBuilder;
using java::nio::FloatBuffer;
using java::nio::ShortBuffer;
using tdme::engine::Engine;
using tdme::engine::model::Group;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DGroupMesh;
using tdme::engine::subsystems::object::Object3DVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Vector3;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::TextureCoordinate, ::java::lang::ObjectArray > TextureCoordinateArray;
}  // namespace model
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

Object3DGroupVBORenderer::Object3DGroupVBORenderer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Object3DGroupVBORenderer::Object3DGroupVBORenderer(Object3DGroup* object3DGroup) 
	: Object3DGroupVBORenderer(*static_cast< ::default_init_tag* >(0))
{
	ctor(object3DGroup);
}

void Object3DGroupVBORenderer::ctor(Object3DGroup* object3DGroup)
{
	super::ctor();
	this->object3DGroup = object3DGroup;
	this->vboBaseIds = nullptr;
	this->vboTangentBitangentIds = nullptr;
	this->vboSkinningIds = nullptr;
}

void Object3DGroupVBORenderer::preRender(Object3DVBORenderer* object3DVBORenderer)
{
	auto meshUploaded = true;
	if (vboBaseIds == nullptr) {
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO(object3DGroup->id, object3DGroup->mesh->group->getTextureCoordinates() != nullptr ? 4 : 3);
		vboBaseIds = vboManaged->getVBOGlIds();
		meshUploaded = vboManaged->isUploaded();
	}
	if (object3DVBORenderer->renderer->isNormalMappingAvailable() && object3DGroup->mesh->group->getTangents()->size() > 0 && object3DGroup->mesh->group->getBitangents()->size() > 0 && vboTangentBitangentIds == nullptr) {
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO(::java::lang::StringBuilder().append(object3DGroup->id)->append(u".tangentbitangent"_j)->toString(), 2);
		vboTangentBitangentIds = vboManaged->getVBOGlIds();
	}
	if (object3DGroup->mesh->hasRecreatedBuffers() == true || meshUploaded == false) {
		if (meshUploaded == false) {
			auto sbIndices = object3DGroup->mesh->setupVertexIndicesBuffer();
			object3DVBORenderer->renderer->uploadIndicesBufferObject((*vboBaseIds)[0], sbIndices->position() * Short::SIZE / Byte::SIZE, sbIndices);
			if (object3DGroup->mesh->group->getTextureCoordinates() != nullptr) {
				auto fbTextureCoordinates = object3DGroup->mesh->setupTextureCoordinatesBuffer();
				object3DVBORenderer->renderer->uploadBufferObject((*vboBaseIds)[3], fbTextureCoordinates->position() * Float::SIZE / Byte::SIZE, fbTextureCoordinates);
			}
		}
		auto fbVertices = object3DGroup->mesh->setupVerticesBuffer();
		object3DVBORenderer->renderer->uploadBufferObject((*vboBaseIds)[1], fbVertices->position() * Float::SIZE / Byte::SIZE, fbVertices);
		auto fbNormals = object3DGroup->mesh->setupNormalsBuffer();
		object3DVBORenderer->renderer->uploadBufferObject((*vboBaseIds)[2], fbNormals->position() * Float::SIZE / Byte::SIZE, fbNormals);
		if (vboTangentBitangentIds != nullptr) {
			auto fbTangents = object3DGroup->mesh->setupTangentsBuffer();
			object3DVBORenderer->renderer->uploadBufferObject((*vboTangentBitangentIds)[0], fbTangents->position() * Float::SIZE / Byte::SIZE, fbTangents);
			auto fbBitangents = object3DGroup->mesh->setupBitangentsBuffer();
			object3DVBORenderer->renderer->uploadBufferObject((*vboTangentBitangentIds)[1], fbBitangents->position() * Float::SIZE / Byte::SIZE, fbBitangents);
		}
	}
}

void Object3DGroupVBORenderer::dispose()
{
	if (vboBaseIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO(object3DGroup->id);
		vboBaseIds = nullptr;
	}
	if (vboSkinningIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO(::java::lang::StringBuilder().append(object3DGroup->id)->append(u".skinning"_j)->toString());
		vboSkinningIds = nullptr;
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Object3DGroupVBORenderer::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.Object3DGroupVBORenderer", 54);
    return c;
}

java::lang::Class* Object3DGroupVBORenderer::getClass0()
{
	return class_();
}

