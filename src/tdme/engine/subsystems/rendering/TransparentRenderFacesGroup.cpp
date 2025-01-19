#include <tdme/engine/subsystems/rendering/TransparentRenderFacesGroup.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/subsystems/rendering/BatchRendererTriangles.h>
#include <tdme/engine/subsystems/rendering/EntityRenderer.h>
#include <tdme/engine/subsystems/rendering/ObjectNode.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;

using tdme::engine::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::rendering::BatchRendererTriangles;
using tdme::engine::subsystems::rendering::EntityRenderer;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::engine::subsystems::rendering::TransparentRenderFacesGroup;
using tdme::math::Matrix4x4;
using tdme::utilities::Console;

TransparentRenderFacesGroup::TransparentRenderFacesGroup()
{
	this->entityRenderer = nullptr;
	this->model = nullptr;
	this->objectNode = nullptr;
	this->facesEntityIdx = -1;
	this->material = nullptr;
	this->textureCoordinates = false;
}

void TransparentRenderFacesGroup::set(EntityRenderer* entityRenderer, Model* model, ObjectNode* objectNode, int32_t facesEntityIdx, const Color4& effectColorAdd, const Color4& effectColorMul, const Material* material, bool textureCoordinates, const string& shader)
{
	this->entityRenderer = entityRenderer;
	this->batchRenderers.clear();
	this->model = model;
	this->objectNode = objectNode;
	this->facesEntityIdx = facesEntityIdx;
	this->effectColorAdd.set(effectColorAdd);
	this->effectColorMul.set(effectColorMul);
	this->material = material;
	this->textureCoordinates = textureCoordinates;
	this->shader = shader;
}

void TransparentRenderFacesGroup::render(Engine* engine, RendererBackend* rendererBackend, int contextIdx)
{
	//
	if (rendererBackend->getShader(contextIdx) != shader) {
		// update sahder
		rendererBackend->setShader(contextIdx, shader);
		rendererBackend->onUpdateShader(contextIdx);
		// update lights
		for (auto j = 0; j < engine->lights.size(); j++) {
			engine->lights[j]->update(contextIdx);
		}
		// have identity texture matrix
		rendererBackend->getTextureMatrix(contextIdx).identity();
		rendererBackend->onUpdateTextureMatrix(contextIdx);
	}
	// store model view matrix
	Matrix4x4 modelViewMatrix;
	modelViewMatrix.set(rendererBackend->getModelViewMatrix());
	// effect
	rendererBackend->getEffectColorMul(contextIdx) = effectColorMul.getArray();
	rendererBackend->getEffectColorAdd(contextIdx) = effectColorAdd.getArray();
	rendererBackend->onUpdateEffect(contextIdx);
	// material
	string materialKey;
	entityRenderer->setupMaterial(contextIdx, objectNode, facesEntityIdx, EntityRenderer::RENDERTYPE_ALL, false, materialKey);
	// model view matrix
	rendererBackend->getModelViewMatrix().identity();
	rendererBackend->onUpdateModelViewMatrix(contextIdx);
	// render, reset
	for (auto batchRendererTriangles: batchRenderers) {
		batchRendererTriangles->render();
		batchRendererTriangles->clear();
		batchRendererTriangles->release();
	}
	batchRenderers.clear();
	// restore GL state, model view matrix
	rendererBackend->unbindBufferObjects(contextIdx);
	rendererBackend->getModelViewMatrix().set(modelViewMatrix);
	rendererBackend->onUpdateModelViewMatrix(contextIdx);
}
