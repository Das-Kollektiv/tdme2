#include <tdme/engine/subsystems/object/TransparentRenderFacesGroup.h>

#include <string>
#include <vector>

#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/subsystems/object/BatchVBORendererTriangles.h>
#include <tdme/engine/subsystems/object/Object3DGroup.h>
#include <tdme/engine/subsystems/object/Object3DVBORenderer.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/Key.h>
#include <tdme/utils/_Console.h>

using std::vector;
using std::wstring;
using std::to_wstring;

using tdme::engine::subsystems::object::TransparentRenderFacesGroup;
using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::subsystems::object::BatchVBORendererTriangles;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::utils::Key;
using tdme::utils::_Console;

TransparentRenderFacesGroup::TransparentRenderFacesGroup() 
{
	this->object3DVBORenderer = nullptr;
	this->model = nullptr;
	this->object3DGroup = nullptr;
	this->facesEntityIdx = -1;
	this->material = nullptr;
	this->textureCoordinates = false;
}

void TransparentRenderFacesGroup::set(Object3DVBORenderer* object3DVBORenderer, Model* model, Object3DGroup* object3DGroup, int32_t facesEntityIdx, Color4* effectColorAdd, Color4* effectColorMul, Material* material, bool textureCoordinates)
{
	this->object3DVBORenderer = object3DVBORenderer;
	this->batchVBORenderers.clear();
	this->model = model;
	this->object3DGroup = object3DGroup;
	this->facesEntityIdx = facesEntityIdx;
	this->effectColorAdd.set(*effectColorAdd);
	this->effectColorMul.set(*effectColorMul);
	this->material = material;
	this->textureCoordinates = textureCoordinates;
}

const wstring TransparentRenderFacesGroup::createKey(Model* model, Object3DGroup* object3DGroup, int32_t facesEntityIdx, Color4* effectColorAdd, Color4* effectColorMul, Material* material, bool textureCoordinates)
{
	auto& efcmData = effectColorMul->getArray();
	auto& efcaData = effectColorAdd->getArray();
	wstring key =
		model->getId() +
		L"," +
		object3DGroup->id +
		L"," +
		to_wstring(facesEntityIdx) +
		L"," +
		to_wstring(efcmData[0]) +
		L"," +
		to_wstring(efcmData[1]) +
		L"," +
		to_wstring(efcmData[2]) +
		L"," +
		to_wstring(efcmData[3]) +
		L"," +
		to_wstring(efcaData[0]) +
		L"," +
		to_wstring(efcaData[1]) +
		L"," +
		to_wstring(efcaData[2]) +
		L"," +
		to_wstring(efcaData[3]) +
		L"," +
		(material == nullptr ? L"tdme.material.none" : material->getId()) +
		L"," +
		(textureCoordinates == true ? L"TCT" : L"TCF");
	return key;
}

void TransparentRenderFacesGroup::addVertex(const Vector3& vertex, const Vector3& normal, TextureCoordinate* textureCoordinate)
{
	if (batchVBORenderers.size() == 0) {
		auto batchVBORendererTriangles = object3DVBORenderer->acquireTrianglesBatchVBORenderer();
		if (batchVBORendererTriangles == nullptr) {
			_Console::println(wstring(L"TransparentRenderFacesGroup::addVertex(): could not acquire triangles batch vbo renderer"));
			return;
		}
		batchVBORenderers.push_back(batchVBORendererTriangles);
	}
	auto batchVBORendererTriangles = batchVBORenderers.at(batchVBORenderers.size() - 1);
	if (batchVBORendererTriangles->addVertex(vertex, normal, textureCoordinate) == true)
		return;

	batchVBORendererTriangles = object3DVBORenderer->acquireTrianglesBatchVBORenderer();
	if (batchVBORendererTriangles == nullptr) {
		_Console::println(wstring(L"TransparentRenderFacesGroup::addVertex(): could not acquire triangles batch vbo renderer"));
		return;
	}
	batchVBORenderers.push_back(batchVBORendererTriangles);
	batchVBORendererTriangles->addVertex(vertex, normal, textureCoordinate);
}

void TransparentRenderFacesGroup::render(GLRenderer* renderer)
{
	Matrix4x4 modelViewMatrix;
	modelViewMatrix.set(renderer->getModelViewMatrix());
	if (textureCoordinates == true) {
		if (renderer->renderingTexturingClientState == false) {
			renderer->enableClientState(renderer->CLIENTSTATE_TEXTURECOORD_ARRAY);
			renderer->renderingTexturingClientState = true;
		}
	} else {
		if (renderer->renderingTexturingClientState == true) {
			renderer->disableClientState(renderer->CLIENTSTATE_TEXTURECOORD_ARRAY);
			renderer->renderingTexturingClientState = false;
		}
	}
	renderer->setEffectColorMul(effectColorMul.getArray());
	renderer->setEffectColorAdd(effectColorAdd.getArray());
	renderer->onUpdateEffect();
	object3DVBORenderer->setupMaterial(object3DGroup, facesEntityIdx);
	renderer->getModelViewMatrix().identity();
	renderer->onUpdateModelViewMatrix();
	for (auto batchVBORendererTriangles: batchVBORenderers) {
		batchVBORendererTriangles->render();
		batchVBORendererTriangles->clear();
		batchVBORendererTriangles->release();
	}
	batchVBORenderers.clear();
	renderer->unbindBufferObjects();
	renderer->getModelViewMatrix().set(modelViewMatrix);
	renderer->onUpdateModelViewMatrix();
}
