// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderFacesGroup.java
#include <tdme/engine/subsystems/object/TransparentRenderFacesGroup.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/subsystems/object/BatchVBORendererTriangles.h>
#include <tdme/engine/subsystems/object/Object3DGroup.h>
#include <tdme/engine/subsystems/object/Object3DVBORenderer.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/Key.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_Console.h>
#include <Array.h>

using tdme::engine::subsystems::object::TransparentRenderFacesGroup;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::subsystems::object::BatchVBORendererTriangles;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::utils::Key;
using tdme::utils::_ArrayList;
using tdme::utils::_Console;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

TransparentRenderFacesGroup::TransparentRenderFacesGroup(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

TransparentRenderFacesGroup::TransparentRenderFacesGroup() 
	: TransparentRenderFacesGroup(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Matrix4x4* TransparentRenderFacesGroup::modelViewMatrix;

void TransparentRenderFacesGroup::ctor()
{
	super::ctor();
	this->object3DVBORenderer = nullptr;
	this->batchVBORenderers = new _ArrayList();
	this->model = nullptr;
	this->object3DGroup = nullptr;
	this->facesEntityIdx = -1;
	this->effectColorAdd = nullptr;
	this->effectColorMul = nullptr;
	this->material = nullptr;
	this->textureCoordinates = false;
}

void TransparentRenderFacesGroup::set(Object3DVBORenderer* object3DVBORenderer, Model* model, Object3DGroup* object3DGroup, int32_t facesEntityIdx, Color4* effectColorAdd, Color4* effectColorMul, Material* material, bool textureCoordinates)
{
	this->object3DVBORenderer = object3DVBORenderer;
	java_cast< _ArrayList* >(this->batchVBORenderers)->clear();
	this->model = model;
	this->object3DGroup = object3DGroup;
	this->facesEntityIdx = facesEntityIdx;
	this->effectColorAdd = effectColorAdd;
	this->effectColorMul = effectColorMul;
	this->material = material;
	this->textureCoordinates = textureCoordinates;
}

void TransparentRenderFacesGroup::createKey(Key* key, Model* model, Object3DGroup* object3DGroup, int32_t facesEntityIdx, Color4* effectColorAdd, Color4* effectColorMul, Material* material, bool textureCoordinates)
{
	clinit();
	auto efcmData = effectColorMul->getArray();
	auto efcaData = effectColorAdd->getArray();
	key->reset();
	key->append(model->getId());
	key->append(u","_j);
	key->append(object3DGroup->id);
	key->append(u","_j);
	key->append(facesEntityIdx);
	key->append(u","_j);
	key->append((*efcmData)[0]);
	key->append((*efcmData)[1]);
	key->append((*efcmData)[2]);
	key->append((*efcmData)[3]);
	key->append(u","_j);
	key->append((*efcaData)[0]);
	key->append((*efcaData)[1]);
	key->append((*efcaData)[2]);
	key->append((*efcaData)[3]);
	key->append(u","_j);
	key->append((material == nullptr ? u"tdme.material.none"_j : material->getId()));
	key->append(u","_j);
	key->append((textureCoordinates == true ? u"TCT"_j : u"TCF"_j));
}

void TransparentRenderFacesGroup::addVertex(Vector3* vertex, Vector3* normal, TextureCoordinate* textureCoordinate)
{
	if (batchVBORenderers->size() == 0) {
		auto batchVBORendererTriangles = object3DVBORenderer->acquireTrianglesBatchVBORenderer();
		if (batchVBORendererTriangles == nullptr) {
			_Console::println(static_cast< Object* >(u"TransparentRenderFacesGroup::addVertex(): could not acquire triangles batch vbo renderer"_j));
			return;
		}
		batchVBORenderers->add(batchVBORendererTriangles);
	}
	auto batchVBORendererTriangles = java_cast< BatchVBORendererTriangles* >(batchVBORenderers->get(batchVBORenderers->size() - 1));
	if (batchVBORendererTriangles->addVertex(vertex, normal, textureCoordinate) == true)
		return;

	batchVBORendererTriangles = object3DVBORenderer->acquireTrianglesBatchVBORenderer();
	if (batchVBORendererTriangles == nullptr) {
		_Console::println(static_cast< Object* >(u"TransparentRenderFacesGroup::addVertex(): could not acquire triangles batch vbo renderer"_j));
		return;
	}
	batchVBORenderers->add(batchVBORendererTriangles);
	batchVBORendererTriangles->addVertex(vertex, normal, textureCoordinate);
}

void TransparentRenderFacesGroup::render(GLRenderer* renderer)
{
	modelViewMatrix->set(renderer->getModelViewMatrix());
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
	renderer->setEffectColorMul(effectColorMul->getArray());
	renderer->setEffectColorAdd(effectColorAdd->getArray());
	renderer->onUpdateEffect();
	object3DVBORenderer->setupMaterial(object3DGroup, facesEntityIdx);
	renderer->getModelViewMatrix()->identity();
	renderer->onUpdateModelViewMatrix();
	for (auto i = 0; i < batchVBORenderers->size(); i++) {
		auto batchVBORendererTriangles = java_cast< BatchVBORendererTriangles* >(batchVBORenderers->get(i));
		batchVBORendererTriangles->render();
		batchVBORendererTriangles->clear();
		batchVBORendererTriangles->release();
	}
	batchVBORenderers->clear();
	renderer->unbindBufferObjects();
	renderer->getModelViewMatrix()->set(modelViewMatrix);
	renderer->onUpdateModelViewMatrix();
}

String* TransparentRenderFacesGroup::toString()
{
	return ::java::lang::StringBuilder().append(u"TransparentRenderFacesGroup [model="_j)->append(model->getId())
		->append(u", object3DGroup="_j)
		->append(object3DGroup->id)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TransparentRenderFacesGroup::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.TransparentRenderFacesGroup", 57);
    return c;
}

void TransparentRenderFacesGroup::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		modelViewMatrix = new Matrix4x4();
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* TransparentRenderFacesGroup::getClass0()
{
	return class_();
}

