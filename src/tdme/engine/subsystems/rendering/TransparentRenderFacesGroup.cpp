#include <tdme/engine/subsystems/rendering/TransparentRenderFacesGroup.h>

#include <string>

#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/subsystems/rendering/BatchVBORendererTriangles.h>
#include <tdme/engine/subsystems/rendering/Object3DGroup.h>
#include <tdme/engine/subsystems/rendering/Object3DVBORenderer.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/Console.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::rendering::TransparentRenderFacesGroup;
using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::subsystems::rendering::BatchVBORendererTriangles;
using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::engine::subsystems::rendering::Object3DVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::utils::Key;
using tdme::utils::Console;

TransparentRenderFacesGroup::TransparentRenderFacesGroup() 
{
	this->object3DVBORenderer = nullptr;
	this->model = nullptr;
	this->object3DGroup = nullptr;
	this->facesEntityIdx = -1;
	this->material = nullptr;
	this->textureCoordinates = false;
}

void TransparentRenderFacesGroup::set(Object3DVBORenderer* object3DVBORenderer, Model* model, Object3DGroup* object3DGroup, int32_t facesEntityIdx, const Color4& effectColorAdd, const Color4& effectColorMul, Material* material, bool textureCoordinates, const string& shader)
{
	this->object3DVBORenderer = object3DVBORenderer;
	this->batchVBORenderers.clear();
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

void TransparentRenderFacesGroup::render(GLRenderer* renderer)
{
	if (renderer->shaderId != shader) {
		renderer->setShader(shader);
		renderer->onUpdateShader();
	}
	// store model view matrix
	Matrix4x4 modelViewMatrix;
	modelViewMatrix.set(renderer->getModelViewMatrix());
	// effect
	renderer->setEffectColorMul(effectColorMul.getArray());
	renderer->setEffectColorAdd(effectColorAdd.getArray());
	renderer->onUpdateEffect();
	// material
	string materialKey;
	object3DVBORenderer->setupMaterial(object3DGroup, facesEntityIdx, Object3DVBORenderer::RENDERTYPE_ALL, false, materialKey);
	// model view matrix
	renderer->getModelViewMatrix().identity();
	renderer->onUpdateModelViewMatrix();
	// render, reset
	for (auto batchVBORendererTriangles: batchVBORenderers) {
		batchVBORendererTriangles->render();
		batchVBORendererTriangles->clear();
		batchVBORendererTriangles->release();
	}
	batchVBORenderers.clear();
	// restore GL state, model view matrix
	renderer->unbindBufferObjects();
	renderer->getModelViewMatrix().set(modelViewMatrix);
	renderer->onUpdateModelViewMatrix();
}
