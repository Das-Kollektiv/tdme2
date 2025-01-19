#include <tdme/engine/subsystems/rendering/ObjectNodeRenderer.h>

#include <tdme/tdme.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/rendering/EntityRenderer.h>
#include <tdme/engine/subsystems/rendering/ObjectNode.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>
#include <tdme/engine/Engine.h>
#include <tdme/utilities/FloatBuffer.h>
#include <tdme/utilities/ShortBuffer.h>

using tdme::engine::model::Node;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::EntityRenderer;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::engine::subsystems::rendering::ObjectNodeRenderer;
using tdme::engine::Engine;
using tdme::utilities::FloatBuffer;
using tdme::utilities::ShortBuffer;

ObjectNodeRenderer::ObjectNodeRenderer(ObjectNode* objectNode)
{
	this->objectNode = objectNode;
	this->vboBaseIds = nullptr;
	this->vboNormalMappingIds = nullptr;
}

void ObjectNodeRenderer::preRender(int contextIdx)
{
	// TODO: maybe store these in ObjectNodeRenderer too
	auto meshUploaded = true;
	auto created = false;

	// initialize if not yet done
	if (vboBaseIds == nullptr) {
		vboManagedBase = Engine::getInstance()->getVBOManager()->addVBO(
			objectNode->id,
			3 + (objectNode->mesh->node->getTextureCoordinates().empty() == false?1:0),
			true,
			true,
			created
		);
		if (created == false) while (vboManagedBase->isUploaded() == false);
		vboBaseIds = vboManagedBase->getVBOIds();
		meshUploaded = created == false;

		// initialize tangents, bitangents
		if (Engine::getRenderer()->isNormalMappingAvailable() &&
			objectNode->mesh->node->getTangents().empty() == false &&
			objectNode->mesh->node->getBitangents().empty() == false &&
			vboNormalMappingIds == nullptr) {
			vboManagedNormalMapping = Engine::getInstance()->getVBOManager()->addVBO(objectNode->id + ".normalmapping", 2, true, true, created);
			if (created == false) while (vboManagedNormalMapping->isUploaded() == false);
			vboNormalMappingIds = vboManagedNormalMapping->getVBOIds();
		}

		// initialize origins
		if (objectNode->mesh->node->getOrigins().empty() == false &&
			vboOrigins == nullptr) {
			vboManagedOrigins = Engine::getInstance()->getVBOManager()->addVBO(objectNode->id + ".origins", 1, true, true, created);
			if (created == false) while (vboManagedOrigins->isUploaded() == false);
			vboOrigins = vboManagedOrigins->getVBOIds();
		}

		// initialize tangents, bitangents
		auto lodLevels = 0;
		// TODO: we only support faces entities 0 lod indices for terrain now
		if (objectNode->mesh->node->getFacesEntities()[0].getLOD1Indices().empty() == false) lodLevels++;
		if (objectNode->mesh->node->getFacesEntities()[0].getLOD2Indices().empty() == false) lodLevels++;
		if (objectNode->mesh->node->getFacesEntities()[0].getLOD3Indices().empty() == false) lodLevels++;
		if (lodLevels > 0 &&
			vboLods == nullptr) {
			vboManagedLods = Engine::getInstance()->getVBOManager()->addVBO(objectNode->id + ".lodindices", lodLevels, true, true, created);
			if (created == false) while (vboManagedLods->isUploaded() == false);
			vboLods = vboManagedLods->getVBOIds();
		}
	}

	//
	haveVBOs = true;

	// model node updates
	auto verticesUpdate = objectNode->node->hasVerticesUpdate();
	auto normalsUpdate = objectNode->node->hasNormalsUpdate();

	// check if to upload new mesh
	if (objectNode->mesh->getRecreatedBuffers() == true || meshUploaded == false) {
		if (meshUploaded == false) {
			// upload indices
			objectNode->mesh->setupVertexIndicesBuffer(Engine::getRenderer(), contextIdx, (*vboBaseIds)[0]);
			// upload texture coordinates
			if (objectNode->mesh->node->getTextureCoordinates().empty() == false) {
				objectNode->mesh->setupTextureCoordinatesBuffer(Engine::getRenderer(), contextIdx, (*vboBaseIds)[3]);
			}
			// upload render node object origins
			if (objectNode->mesh->node->getOrigins().empty() == false) {
				objectNode->mesh->setupOriginsBuffer(Engine::getRenderer(), contextIdx, (*vboOrigins)[0]);
				vboManagedOrigins->setUploaded(true);
			}
			// TODO: we only support faces entities 0 lod indices for terrain now
			auto lodLevel = 0;
			if (objectNode->mesh->node->getFacesEntities()[0].getLOD1Indices().empty() == false) {
				objectNode->mesh->setupLodBuffer(Engine::getRenderer(), contextIdx, (*vboLods)[lodLevel], 1);
				lodLevel++;
			}
			if (objectNode->mesh->node->getFacesEntities()[0].getLOD2Indices().empty() == false) {
				objectNode->mesh->setupLodBuffer(Engine::getRenderer(), contextIdx, (*vboLods)[lodLevel], 2);
				lodLevel++;
			}
			if (objectNode->mesh->node->getFacesEntities()[0].getLOD3Indices().empty() == false) {
				objectNode->mesh->setupLodBuffer(Engine::getRenderer(), contextIdx, (*vboLods)[lodLevel], 3);
				lodLevel++;
			}
			if (vboManagedLods != nullptr) vboManagedLods->setUploaded(true);
		}
		// upload vertices
		objectNode->mesh->setupVerticesBuffer(Engine::getRenderer(), contextIdx, (*vboBaseIds)[1]);
		// upload normals
		objectNode->mesh->setupNormalsBuffer(Engine::getRenderer(), contextIdx, (*vboBaseIds)[2]);
		// tangents, bitangents
		if (vboNormalMappingIds != nullptr) {
			objectNode->mesh->setupTangentsBuffer(Engine::getRenderer(), contextIdx, (*vboNormalMappingIds)[0]);
			objectNode->mesh->setupBitangentsBuffer(Engine::getRenderer(), contextIdx, (*vboNormalMappingIds)[1]);
			vboManagedNormalMapping->setUploaded(true);
		}
		vboManagedBase->setUploaded(true);
	} else
	if (verticesUpdate == true || normalsUpdate == true) {
		// upload vertices
		if (verticesUpdate == true) objectNode->mesh->setupVerticesBuffer(Engine::getRenderer(), contextIdx, (*vboBaseIds)[1]);
		// upload normals
		if (normalsUpdate == true) objectNode->mesh->setupNormalsBuffer(Engine::getRenderer(), contextIdx, (*vboBaseIds)[2]);
	}
}

void ObjectNodeRenderer::dispose()
{
	if (vboBaseIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO(objectNode->id);
		vboBaseIds = nullptr;
	}
	if (vboNormalMappingIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO(objectNode->id + ".normalmapping");
		vboNormalMappingIds = nullptr;
	}
	if (vboOrigins != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO(objectNode->id + ".origins");
		vboOrigins = nullptr;
	}
	if (vboLods != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO(objectNode->id + ".lodindices");
		vboLods = nullptr;
	}
}
