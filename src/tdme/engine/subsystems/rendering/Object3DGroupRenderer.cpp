#include <tdme/engine/subsystems/rendering/Object3DGroupRenderer.h>

#include <tdme/utils/FloatBuffer.h>
#include <tdme/utils/ShortBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/rendering/Object3DGroup.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/rendering/Object3DRenderer.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/math/Vector3.h>

using tdme::engine::subsystems::rendering::Object3DGroupRenderer;
using tdme::utils::FloatBuffer;
using tdme::utils::ShortBuffer;
using tdme::engine::Engine;
using tdme::engine::model::Group;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::engine::subsystems::rendering::Object3DGroupMesh;
using tdme::engine::subsystems::rendering::Object3DRenderer;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Vector3;

Object3DGroupRenderer::Object3DGroupRenderer(Object3DGroup* object3DGroup)
{
	this->object3DGroup = object3DGroup;
	this->vboBaseIds = nullptr;
	this->vboTangentBitangentIds = nullptr;
}

void Object3DGroupRenderer::preRender(void* context)
{
	auto meshUploaded = true;

	// initialize if not yet done
	if (vboBaseIds == nullptr) {
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO(object3DGroup->id, 4, true); // TODO: check for texture coorditantes
		vboBaseIds = vboManaged->getVBOIds();
		meshUploaded = vboManaged->isUploaded();
	}

	// initialize tangents, bitangents
	if (Engine::renderer->isNormalMappingAvailable() &&
		object3DGroup->mesh->group->getTangents().size() > 0 &&
		object3DGroup->mesh->group->getBitangents().size() > 0 &&
		vboTangentBitangentIds == nullptr) {
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO(object3DGroup->id + ".tangentbitangent", 2, true);
		vboTangentBitangentIds = vboManaged->getVBOIds();
	}

	//
	haveVBOs = true;

	// check if to upload new mesh
	if (object3DGroup->mesh->getRecreatedBuffers() == true || meshUploaded == false) {
		if (meshUploaded == false) {
			// upload indices
			object3DGroup->mesh->setupVertexIndicesBuffer(Engine::renderer, context, (*vboBaseIds)[0]);
			// upload texture coordinates
			if (object3DGroup->mesh->group->getTextureCoordinates().size() > 0) {
				object3DGroup->mesh->setupTextureCoordinatesBuffer(Engine::renderer, (*vboBaseIds)[3]);
			}
		}
		// upload vertices
		object3DGroup->mesh->setupVerticesBuffer(Engine::renderer, context, (*vboBaseIds)[1]);
		// upload normals
		object3DGroup->mesh->setupNormalsBuffer(Engine::renderer, context, (*vboBaseIds)[2]);
		// tangents, bitangents
		if (vboTangentBitangentIds != nullptr) {
			object3DGroup->mesh->setupTangentsBuffer(Engine::renderer, context, (*vboTangentBitangentIds)[0]);
			object3DGroup->mesh->setupBitangentsBuffer(Engine::renderer, context, (*vboTangentBitangentIds)[1]);
		}
	}
}

void Object3DGroupRenderer::dispose()
{
	if (vboBaseIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO(object3DGroup->id);
		vboBaseIds = nullptr;
	}
	if (vboTangentBitangentIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO(object3DGroup->id + ".tangentbitangent");
		vboTangentBitangentIds = nullptr;
	}
}
