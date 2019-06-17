#include <tdme/engine/subsystems/rendering/TransparentRenderFacesGroup.h>

#include <string>

#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/subsystems/rendering/BatchRendererTriangles.h>
#include <tdme/engine/subsystems/rendering/Object3DGroup.h>
#include <tdme/engine/subsystems/rendering/Object3DRenderer.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/Console.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::rendering::TransparentRenderFacesGroup;
using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::subsystems::rendering::BatchRendererTriangles;
using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::engine::subsystems::rendering::Object3DRenderer;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix4x4;
using tdme::utils::Key;
using tdme::utils::Console;

TransparentRenderFacesGroup::TransparentRenderFacesGroup() 
{
	this->object3DRenderer = nullptr;
	this->model = nullptr;
	this->object3DGroup = nullptr;
	this->facesEntityIdx = -1;
	this->material = nullptr;
	this->textureCoordinates = false;
}

void TransparentRenderFacesGroup::set(Object3DRenderer* object3DRenderer, Model* model, Object3DGroup* object3DGroup, int32_t facesEntityIdx, const Color4& effectColorAdd, const Color4& effectColorMul, Material* material, bool textureCoordinates, const string& shader)
{
	this->object3DRenderer = object3DRenderer;
	this->batchRenderers.clear();
	this->model = model;
	this->object3DGroup = object3DGroup;
	this->facesEntityIdx = facesEntityIdx;
	this->effectColorAdd.set(effectColorAdd);
	this->effectColorMul.set(effectColorMul);
	this->material = material;
	this->textureCoordinates = textureCoordinates;
	this->shader = shader;
}

const string TransparentRenderFacesGroup::createKey(Model* model, Object3DGroup* object3DGroup, int32_t facesEntityIdx, const Color4& effectColorAdd, const Color4& effectColorMul, Material* material, bool textureCoordinates, const string& shader)
{
	auto& efcmData = effectColorMul.getArray();
	auto& efcaData = effectColorAdd.getArray();
	string key =
		model->getId() +
		"," +
		object3DGroup->id +
		"," +
		to_string(facesEntityIdx) +
		"," +
		to_string(efcmData[0]) +
		"," +
		to_string(efcmData[1]) +
		"," +
		to_string(efcmData[2]) +
		"," +
		to_string(efcmData[3]) +
		"," +
		to_string(efcaData[0]) +
		"," +
		to_string(efcaData[1]) +
		"," +
		to_string(efcaData[2]) +
		"," +
		to_string(efcaData[3]) +
		"," +
		(material == nullptr ? "tdme.material.none" : material->getId()) + // TODO: material id could contain this "," delimiter
		"," +
		to_string(object3DGroup->dynamicDiffuseTextureIdsByEntities[facesEntityIdx]) +
		"," +
		(textureCoordinates == true ? "TCT" : "TCF");
		"," +
		shader;
	return key;
}

void TransparentRenderFacesGroup::render(Renderer* renderer, void* context)
{
	//
	if (renderer->shaderId != shader) {
		renderer->setShader(shader);
		renderer->onUpdateShader(context);
	}
	// store model view matrix
	Matrix4x4 modelViewMatrix;
	modelViewMatrix.set(renderer->getModelViewMatrix());
	// effect
	renderer->setEffectColorMul(context, effectColorMul.getArray());
	renderer->setEffectColorAdd(context, effectColorAdd.getArray());
	renderer->onUpdateEffect(context);
	// material
	string materialKey;
	object3DRenderer->setupMaterial(context, object3DGroup, facesEntityIdx, Object3DRenderer::RENDERTYPE_ALL, false, materialKey);
	// model view matrix
	renderer->getModelViewMatrix().identity();
	renderer->onUpdateModelViewMatrix(context);
	// render, reset
	for (auto batchRendererTriangles: batchRenderers) {
		batchRendererTriangles->render();
		batchRendererTriangles->clear();
		batchRendererTriangles->release();
	}
	batchRenderers.clear();
	// restore GL state, model view matrix
	renderer->unbindBufferObjects(context);
	renderer->getModelViewMatrix().set(modelViewMatrix);
	renderer->onUpdateModelViewMatrix(context);
}
