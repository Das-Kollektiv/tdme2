// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DVBORenderer.java
#include <tdme/engine/subsystems/object/Object3DVBORenderer.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Iterator.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/PointsParticleSystemEntity.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/object/BatchVBORendererPoints.h>
#include <tdme/engine/subsystems/object/BatchVBORendererTriangles.h>
#include <tdme/engine/subsystems/object/Object3DBase.h>
#include <tdme/engine/subsystems/object/Object3DGroup.h>
#include <tdme/engine/subsystems/object/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/object/Object3DGroupVBORenderer.h>
#include <tdme/engine/subsystems/object/Object3DVBORenderer_1.h>
#include <tdme/engine/subsystems/object/Object3DVBORenderer_Object3DVBORenderer_2.h>
#include <tdme/engine/subsystems/object/Object3DVBORenderer_Object3DVBORenderer_3.h>
#include <tdme/engine/subsystems/object/TransparentRenderFace.h>
#include <tdme/engine/subsystems/object/TransparentRenderFacesGroup.h>
#include <tdme/engine/subsystems/object/TransparentRenderFacesPool.h>
#include <tdme/engine/subsystems/object/TransparentRenderPoint.h>
#include <tdme/engine/subsystems/object/TransparentRenderPointsPool.h>
#include <tdme/engine/subsystems/particlesystem/ParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/PointsParticleSystemEntityInternal.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Matrix4x4Negative.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Key.h>
#include <tdme/utils/Pool.h>
#include <tdme/utils/QuickSort.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_HashMap_KeysIterator.h>
#include <tdme/utils/_HashMap_ValuesIterator.h>
#include <tdme/utils/_HashMap.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using tdme::engine::subsystems::object::Object3DVBORenderer;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Iterator;
using tdme::engine::Engine;
using tdme::engine::Object3D;
using tdme::engine::PointsParticleSystemEntity;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::object::BatchVBORendererPoints;
using tdme::engine::subsystems::object::BatchVBORendererTriangles;
using tdme::engine::subsystems::object::Object3DBase;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::Object3DGroupMesh;
using tdme::engine::subsystems::object::Object3DGroupVBORenderer;
using tdme::engine::subsystems::object::Object3DVBORenderer_1;
using tdme::engine::subsystems::object::Object3DVBORenderer_Object3DVBORenderer_2;
using tdme::engine::subsystems::object::Object3DVBORenderer_Object3DVBORenderer_3;
using tdme::engine::subsystems::object::TransparentRenderFace;
using tdme::engine::subsystems::object::TransparentRenderFacesGroup;
using tdme::engine::subsystems::object::TransparentRenderFacesPool;
using tdme::engine::subsystems::object::TransparentRenderPoint;
using tdme::engine::subsystems::object::TransparentRenderPointsPool;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::particlesystem::PointsParticleSystemEntityInternal;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::math::MathTools;
using tdme::math::Matrix4x4;
using tdme::math::Matrix4x4Negative;
using tdme::math::Vector3;
using tdme::utils::Key;
using tdme::utils::Pool;
using tdme::utils::QuickSort;
using tdme::utils::_ArrayList;
using tdme::utils::_Console;
using tdme::utils::_HashMap_KeysIterator;
using tdme::utils::_HashMap_ValuesIterator;
using tdme::utils::_HashMap;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::Face, ::java::lang::ObjectArray > FaceArray;
typedef ::SubArray< ::tdme::engine::model::FacesEntity, ::java::lang::ObjectArray > FacesEntityArray;
typedef ::SubArray< ::tdme::engine::model::TextureCoordinate, ::java::lang::ObjectArray > TextureCoordinateArray;
}  // namespace model

namespace subsystems {
namespace object {
typedef ::SubArray< ::tdme::engine::subsystems::object::Object3DGroup, ::java::lang::ObjectArray > Object3DGroupArray;
}  // namespace object
}  // namespace subsystems
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

Object3DVBORenderer::Object3DVBORenderer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Object3DVBORenderer::Object3DVBORenderer(Engine* engine, GLRenderer* renderer) 
	: Object3DVBORenderer(*static_cast< ::default_init_tag* >(0))
{
	ctor(engine,renderer);
}

void Object3DVBORenderer::init()
{
	visibleObjectsByModels = nullptr;
	keyPool = nullptr;
	groupTransparentRenderFaces = nullptr;
	transparentRenderFacesPool = nullptr;
	transparentRenderFacesGroups = nullptr;
	pseKeyPool = new Object3DVBORenderer_1(this);
	pseKeys = new _ArrayList();
	pseTransparentRenderPointsPool = nullptr;
	psePointBatchVBORenderer = nullptr;
	modelViewMatrixBackup = new Matrix4x4();
	modelViewMatrix = new Matrix4x4();
	transformedVertex = new Vector3();
	transformedNormal = new Vector3();
	matrix4x4Negative = new Matrix4x4Negative();
}

constexpr int32_t Object3DVBORenderer::BATCHVBORENDERER_MAX;

void Object3DVBORenderer::ctor(Engine* engine, GLRenderer* renderer)
{
	super::ctor();
	init();
	this->engine = engine;
	this->renderer = renderer;
	trianglesBatchVBORenderers = new _ArrayList();
	visibleObjectsByModels = new _HashMap();
	keyPool = new Object3DVBORenderer_Object3DVBORenderer_2(this);
	groupTransparentRenderFaces = new _ArrayList();
	transparentRenderFacesGroupPool = new Object3DVBORenderer_Object3DVBORenderer_3(this);
	transparentRenderFacesPool = new TransparentRenderFacesPool();
	transparentRenderFacesGroups = new _HashMap();
	pseTransparentRenderPointsPool = new TransparentRenderPointsPool(16384);
	psePointBatchVBORenderer = new BatchVBORendererPoints(renderer, 0);
}

void Object3DVBORenderer::initialize()
{
	psePointBatchVBORenderer->initialize();
}

void Object3DVBORenderer::dispose()
{
	for (auto _i = trianglesBatchVBORenderers->iterator(); _i->hasNext(); ) {
		BatchVBORendererTriangles* batchVBORenderer = java_cast< BatchVBORendererTriangles* >(_i->next());
		{
			batchVBORenderer->dispose();
			batchVBORenderer->release();
		}
	}
	psePointBatchVBORenderer->dispose();
}

BatchVBORendererTriangles* Object3DVBORenderer::acquireTrianglesBatchVBORenderer()
{
	auto i = 0;
	for (auto _i = trianglesBatchVBORenderers->iterator(); _i->hasNext(); ) {
		BatchVBORendererTriangles* batchVBORenderer = java_cast< BatchVBORendererTriangles* >(_i->next());
		{
			if (batchVBORenderer->acquire())
				return batchVBORenderer;

			i++;
		}
	}
	if (i < BATCHVBORENDERER_MAX) {
		auto batchVBORenderer = new BatchVBORendererTriangles(renderer, i);
		batchVBORenderer->initialize();
		trianglesBatchVBORenderers->add(batchVBORenderer);
		if (batchVBORenderer->acquire())
			return batchVBORenderer;

	}
	_Console::println(static_cast< Object* >(u"Object3DVBORenderer::acquireTrianglesBatchVBORenderer()::failed"_j));
	return nullptr;
}

void Object3DVBORenderer::reset()
{
	visibleObjectsByModels->clear();
}

void Object3DVBORenderer::render(_ArrayList* objects, bool renderTransparentFaces)
{
	transparentRenderFacesPool->reset();
	releaseTransparentFacesGroups();
	for (auto objectIdx = 0; objectIdx < objects->size(); objectIdx++) {
		auto object = java_cast< Object3D* >(objects->get(objectIdx));
		auto modelId = object->getModel()->getId();
		auto visibleObjectsByModel = java_cast< _ArrayList* >(visibleObjectsByModels->get(modelId));
		if (visibleObjectsByModel == nullptr) {
			visibleObjectsByModel = new _ArrayList();
			visibleObjectsByModels->put(modelId, visibleObjectsByModel);
		}
		visibleObjectsByModel->add(object);
	}
	for (auto _i = visibleObjectsByModels->getValuesIterator()->iterator(); _i->hasNext(); ) {
		_ArrayList* objectsByModel = java_cast< _ArrayList* >(_i->next());
		{
			if (objectsByModel->size() > 0) {
				renderObjectsOfSameType(objectsByModel, renderTransparentFaces);
				objectsByModel->clear();
			}
		}
	}
	auto transparentRenderFaces = transparentRenderFacesPool->getTransparentRenderFaces();
	if (transparentRenderFaces->size() > 0) {
		QuickSort::sort(transparentRenderFaces);
		renderer->disableDepthBuffer();
		renderer->disableCulling();
		renderer->enableBlending();
		renderer->setFrontFace(renderer->FRONTFACE_CCW);
		for (auto _i = transparentRenderFacesPool->getTransparentRenderFaces()->iterator(); _i->hasNext(); ) {
			TransparentRenderFace* transparentRenderFace = java_cast< TransparentRenderFace* >(_i->next());
			{
				if (groupTransparentRenderFaces->size() == 0) {
					groupTransparentRenderFaces->add(transparentRenderFace);
				} else if (groupTransparentRenderFaces->size() > 0) {
					if (java_cast< TransparentRenderFace* >(groupTransparentRenderFaces->get(0))->object3DGroup == transparentRenderFace->object3DGroup) {
						groupTransparentRenderFaces->add(transparentRenderFace);
					} else {
						prepareTransparentFaces(groupTransparentRenderFaces);
						groupTransparentRenderFaces->clear();
						groupTransparentRenderFaces->add(transparentRenderFace);
					}
				}
			}
		}
		if (groupTransparentRenderFaces->size() > 0) {
			prepareTransparentFaces(groupTransparentRenderFaces);
			groupTransparentRenderFaces->clear();
		}
		renderTransparentFacesGroups(transparentRenderFacesGroups);
		renderer->disableBlending();
		renderer->enableCulling();
		renderer->enableDepthBuffer();
	}
}

void Object3DVBORenderer::prepareTransparentFaces(_ArrayList* transparentRenderFaces)
{
	auto object3DGroup = java_cast< TransparentRenderFace* >(transparentRenderFaces->get(0))->object3DGroup;
	auto object3D = java_cast< Object3D* >(object3DGroup->object);
	modelViewMatrix = (object3DGroup->mesh->skinning == true ? modelViewMatrix->identity() : modelViewMatrix->set(object3DGroup->groupTransformationsMatrix))->multiply(object3D->transformationsMatrix)->multiply(renderer->getModelViewMatrix());
	auto model = (java_cast< Object3D* >(object3DGroup->object))->getModel();
	auto facesEntities = object3DGroup->group->getFacesEntities();
	FacesEntity* facesEntity = nullptr;
	auto depthBuffer = false;
	auto effectColorAdd = (java_cast< Object3D* >(object3D))->getEffectColorAdd();
	auto effectColorMul = (java_cast< Object3D* >(object3D))->getEffectColorMul();
	Material* material = nullptr;
	auto textureCoordinates = false;
	auto transparentRenderFacesGroupKey = java_cast< Key* >(keyPool->allocate());
	for (auto i = 0; i < transparentRenderFaces->size(); i++) {
		auto transparentRenderFace = java_cast< TransparentRenderFace* >(transparentRenderFaces->get(i));
		auto facesEntityIdx = transparentRenderFace->facesEntityIdx;
		if (facesEntity != (*facesEntities)[facesEntityIdx]) {
			facesEntity = (*facesEntities)[facesEntityIdx];
			material = facesEntity->getMaterial();
		}
		textureCoordinates = facesEntity->isTextureCoordinatesAvailable();
		TransparentRenderFacesGroup::createKey(transparentRenderFacesGroupKey, model, object3DGroup, facesEntityIdx, effectColorAdd, effectColorMul, material, textureCoordinates);
		auto trfGroup = java_cast< TransparentRenderFacesGroup* >(transparentRenderFacesGroups->get(transparentRenderFacesGroupKey));
		if (trfGroup == nullptr) {
			trfGroup = java_cast< TransparentRenderFacesGroup* >(transparentRenderFacesGroupPool->allocate());
			trfGroup->set(this, model, object3DGroup, facesEntityIdx, effectColorAdd, effectColorMul, material, textureCoordinates);
			auto hashtableKey = java_cast< Key* >(keyPool->allocate());
			transparentRenderFacesGroupKey->cloneInto(hashtableKey);
			if (java_cast< TransparentRenderFacesGroup* >(transparentRenderFacesGroups->put(hashtableKey, trfGroup)) != nullptr) {
				_Console::println(static_cast< Object* >(u"Object3DVBORenderer::prepareTransparentFaces::key already exists"_j));
				_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"-->"_j)->append(static_cast< Object* >(transparentRenderFacesGroupKey))->toString()));
				_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"-->"_j)->append(static_cast< Object* >(hashtableKey))->toString()));
			}
		}
		for (auto vertexIdx = 0; vertexIdx < 3; vertexIdx++) {
			auto arrayIdx = (*transparentRenderFace->object3DGroup->mesh->indices)[transparentRenderFace->faceIdx * 3 + vertexIdx];
			trfGroup->addVertex(modelViewMatrix->multiply((*transparentRenderFace->object3DGroup->mesh->vertices)[arrayIdx], transformedVertex), modelViewMatrix->multiplyNoTranslation((*transparentRenderFace->object3DGroup->mesh->normals)[arrayIdx], transformedNormal), transparentRenderFace->object3DGroup->mesh->textureCoordinates != nullptr ? (*transparentRenderFace->object3DGroup->mesh->textureCoordinates)[arrayIdx] : static_cast< TextureCoordinate* >(nullptr));
		}
	}
	keyPool->release(transparentRenderFacesGroupKey);
}

void Object3DVBORenderer::renderTransparentFacesGroups(_HashMap* transparentRenderFacesGroups)
{
	for (auto _i = transparentRenderFacesGroups->getValuesIterator()->iterator(); _i->hasNext(); ) {
		TransparentRenderFacesGroup* transparentRenderFacesGroup = java_cast< TransparentRenderFacesGroup* >(_i->next());
		{
			transparentRenderFacesGroup->render(renderer);
		}
	}
}

void Object3DVBORenderer::releaseTransparentFacesGroups()
{
	for (auto _i = transparentRenderFacesGroups->getKeysIterator()->iterator(); _i->hasNext(); ) {
		Key* trfgKey = java_cast< Key* >(_i->next());
		{
			keyPool->release(trfgKey);
		}
	}
	for (auto _i = transparentRenderFacesGroups->getValuesIterator()->iterator(); _i->hasNext(); ) {
		TransparentRenderFacesGroup* trfg = java_cast< TransparentRenderFacesGroup* >(_i->next());
		{
			transparentRenderFacesGroupPool->release(trfg);
		}
	}
	transparentRenderFacesGroups->clear();
}

void Object3DVBORenderer::renderObjectsOfSameType(_ArrayList* objects, bool collectTransparentFaces)
{
	for (auto i = 0; i < objects->size(); i++) {
		auto object = java_cast< Object3D* >(objects->get(i));
		for (auto j = 0; j < object->object3dGroups->length; j++) {
			auto object3DGroup = (*object->object3dGroups)[j];
			(java_cast< Object3DGroupVBORenderer* >(object3DGroup->renderer))->preRender(this);
		}
	}
	auto shadowMapping = engine->getShadowMapping();
	modelViewMatrixBackup->set(renderer->getModelViewMatrix());
	auto currentFrontFace = -1;
	auto firstObject = java_cast< Object3D* >(objects->get(0));
	int32_tArray* boundVBOBaseIds = nullptr;
	int32_tArray* boundVBOTangentBitangentIds = nullptr;
	int32_tArray* boundSkinningIds = nullptr;
	for (auto object3DGroupIdx = 0; object3DGroupIdx < firstObject->object3dGroups->length; object3DGroupIdx++) {
		auto object3DGroup = (*firstObject->object3dGroups)[object3DGroupIdx];
		auto facesEntities = object3DGroup->group->getFacesEntities();
		auto faceIdx = 0;
		auto facesEntityIdxCount = facesEntities->length;
		for (auto faceEntityIdx = 0; faceEntityIdx < facesEntityIdxCount; faceEntityIdx++) {
			auto facesEntity = (*facesEntities)[faceEntityIdx];
			auto isTextureCoordinatesAvailable = facesEntity->isTextureCoordinatesAvailable();
			auto faces = facesEntity->getFaces()->length;
			auto material = facesEntity->getMaterial();
			auto transparentFacesEntity = false;
			if (material != nullptr) {
				if (material->hasTransparency() == true)
					transparentFacesEntity = true;

			}
			if (transparentFacesEntity == true) {
				auto objectCount = objects->size();
				for (auto objectIdx = 0; objectIdx < objectCount; objectIdx++) {
					auto object = java_cast< Object3D* >(objects->get(objectIdx));
					auto _object3DGroup = (*object->object3dGroups)[object3DGroupIdx];
					Object3DGroup::setupTextures(renderer, object3DGroup, faceEntityIdx);
					if (collectTransparentFaces == true) {
						transparentRenderFacesPool->createTransparentRenderFaces((_object3DGroup->mesh->skinning == true ? modelViewMatrix->identity() : modelViewMatrix->set(_object3DGroup->groupTransformationsMatrix))->multiply(object->transformationsMatrix)->multiply(modelViewMatrixBackup), (*object->object3dGroups)[object3DGroupIdx], faceEntityIdx, faceIdx);
					}
				}
				faceIdx += faces;
				continue;
			}
			if (isTextureCoordinatesAvailable == true) {
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
			auto objectCount = objects->size();
			for (auto objectIdx = 0; objectIdx < objectCount; objectIdx++) {
				auto object = java_cast< Object3D* >(objects->get(objectIdx));
				auto _object3DGroup = (*object->object3dGroups)[object3DGroupIdx];
				if (objectIdx == 0) {
					setupMaterial(_object3DGroup, faceEntityIdx);
				} else {
					Object3DGroup::setupTextures(renderer, _object3DGroup, faceEntityIdx);
				}
				if (object->effectColorMul->getAlpha() < 1.0f - MathTools::EPSILON || object->effectColorAdd->getAlpha() < -MathTools::EPSILON) {
					if (collectTransparentFaces == true) {
						transparentRenderFacesPool->createTransparentRenderFaces((_object3DGroup->mesh->skinning == true ? modelViewMatrix->identity() : modelViewMatrix->set(_object3DGroup->groupTransformationsMatrix))->multiply(object->transformationsMatrix)->multiply(modelViewMatrixBackup), _object3DGroup, faceEntityIdx, faceIdx);
					}
					continue;
				}
				auto currentVBOGlIds = (java_cast< Object3DGroupVBORenderer* >(_object3DGroup->renderer))->vboBaseIds;
				if (boundVBOBaseIds != currentVBOGlIds) {
					boundVBOBaseIds = currentVBOGlIds;
					if (isTextureCoordinatesAvailable == true) {
						renderer->bindTextureCoordinatesBufferObject((*currentVBOGlIds)[3]);
					}
					renderer->bindVerticesBufferObject((*currentVBOGlIds)[1]);
					renderer->bindNormalsBufferObject((*currentVBOGlIds)[2]);
					renderer->bindIndicesBufferObject((*currentVBOGlIds)[0]);
				}
				auto currentVBOTangentBitangentIds = (java_cast< Object3DGroupVBORenderer* >(_object3DGroup->renderer))->vboTangentBitangentIds;
				if (renderer->isNormalMappingAvailable() && currentVBOTangentBitangentIds != nullptr && currentVBOTangentBitangentIds != boundVBOTangentBitangentIds) {
					renderer->bindTangentsBufferObject((*currentVBOTangentBitangentIds)[0]);
					renderer->bindBitangentsBufferObject((*currentVBOTangentBitangentIds)[1]);
				}
				renderer->getModelViewMatrix()->set((_object3DGroup->mesh->skinning == true ? modelViewMatrix->identity() : modelViewMatrix->set(_object3DGroup->groupTransformationsMatrix))->multiply(object->transformationsMatrix)->multiply(modelViewMatrixBackup));
				renderer->onUpdateModelViewMatrix();
				auto objectFrontFace = matrix4x4Negative->isNegative(renderer->getModelViewMatrix()) == false ? renderer->FRONTFACE_CCW : renderer->FRONTFACE_CW;
				if (objectFrontFace != currentFrontFace) {
					renderer->setFrontFace(objectFrontFace);
					currentFrontFace = objectFrontFace;
				}
				renderer->setEffectColorMul(object->effectColorMul->getArray());
				renderer->setEffectColorAdd(object->effectColorAdd->getArray());
				renderer->onUpdateEffect();
				if (shadowMapping != nullptr) {
					shadowMapping->startObjectTransformations((_object3DGroup->mesh->skinning == true ? modelViewMatrix->identity() : modelViewMatrix->set(_object3DGroup->groupTransformationsMatrix))->multiply(object->transformationsMatrix));
				}
				renderer->drawIndexedTrianglesFromBufferObjects(faces, faceIdx);
				if (shadowMapping != nullptr) {
					shadowMapping->endObjectTransformations();
				}
			}
			faceIdx += faces;
		}
	}
	renderer->unbindBufferObjects();
	renderer->getModelViewMatrix()->set(modelViewMatrixBackup);
}

void Object3DVBORenderer::setupMaterial(Object3DGroup* object3DGroup, int32_t facesEntityIdx)
{
	auto facesEntities = object3DGroup->group->getFacesEntities();
	auto material = (*facesEntities)[facesEntityIdx]->getMaterial();
	if (material == nullptr)
		material = Material::getDefaultMaterial();

	Object3DGroup::setupTextures(renderer, object3DGroup, facesEntityIdx);
	renderer->setMaterialAmbient(material->getAmbientColor()->getArray());
	renderer->setMaterialDiffuse(material->getDiffuseColor()->getArray());
	renderer->setMaterialSpecular(material->getSpecularColor()->getArray());
	renderer->setMaterialEmission(material->getEmissionColor()->getArray());
	renderer->setMaterialShininess(material->getShininess());
	renderer->onUpdateMaterial();
	renderer->setTextureUnit(LightingShader::TEXTUREUNIT_DIFFUSE);
	renderer->bindTexture((*object3DGroup->dynamicDiffuseTextureIdsByEntities)[facesEntityIdx] != Object3DGroup::GLTEXTUREID_NONE ? (*object3DGroup->dynamicDiffuseTextureIdsByEntities)[facesEntityIdx] : (*object3DGroup->materialDiffuseTextureIdsByEntities)[facesEntityIdx]);
	if (renderer->isSpecularMappingAvailable() == true) {
		renderer->setTextureUnit(LightingShader::TEXTUREUNIT_SPECULAR);
		renderer->bindTexture((*object3DGroup->materialSpecularTextureIdsByEntities)[facesEntityIdx]);
	}
	if (renderer->isDisplacementMappingAvailable() == true) {
		renderer->setTextureUnit(LightingShader::TEXTUREUNIT_DISPLACEMENT);
		renderer->bindTexture((*object3DGroup->materialDisplacementTextureIdsByEntities)[facesEntityIdx]);
	}
	if (renderer->isNormalMappingAvailable() == true) {
		renderer->setTextureUnit(LightingShader::TEXTUREUNIT_NORMAL);
		renderer->bindTexture((*object3DGroup->materialNormalTextureIdsByEntities)[facesEntityIdx]);
	}
	renderer->setTextureUnit(LightingShader::TEXTUREUNIT_DIFFUSE);
}

void Object3DVBORenderer::clearMaterial()
{
	renderer->setTextureUnit(LightingShader::TEXTUREUNIT_DIFFUSE);
	renderer->bindTexture(renderer->ID_NONE);
	if (renderer->isSpecularMappingAvailable() == true) {
		renderer->setTextureUnit(LightingShader::TEXTUREUNIT_SPECULAR);
		renderer->bindTexture(renderer->ID_NONE);
	}
	if (renderer->isDisplacementMappingAvailable() == true) {
		renderer->setTextureUnit(LightingShader::TEXTUREUNIT_DISPLACEMENT);
		renderer->bindTexture(renderer->ID_NONE);
	}
	if (renderer->isNormalMappingAvailable()) {
		renderer->setTextureUnit(LightingShader::TEXTUREUNIT_NORMAL);
		renderer->bindTexture(renderer->ID_NONE);
	}
	renderer->setTextureUnit(LightingShader::TEXTUREUNIT_DIFFUSE);
}

void Object3DVBORenderer::createPseKey(Key* key, Color4* effectColorAdd, Color4* effectColorMul, bool depthBuffer, bool sort)
{
	clinit();
	auto efcaData = effectColorAdd->getArray();
	auto efcmData = effectColorMul->getArray();
	key->reset();
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
	key->append((depthBuffer == true ? u"DBT"_j : u"DBF"_j));
	key->append(u","_j);
	key->append((sort == true ? u"DS"_j : u"NS"_j));
}

void Object3DVBORenderer::render(_ArrayList* visiblePses)
{
	if (visiblePses->size() == 0)
		return;

	modelViewMatrix->set(renderer->getModelViewMatrix());
	auto depthBuffer = false;
	renderer->enableBlending();
	renderer->disableDepthBuffer();
	renderer->disableClientState(renderer->CLIENTSTATE_NORMAL_ARRAY);
	renderer->enableClientState(renderer->CLIENTSTATE_COLOR_ARRAY);
	if (renderer->renderingTexturingClientState == false) {
		renderer->enableClientState(renderer->CLIENTSTATE_TEXTURECOORD_ARRAY);
		renderer->renderingTexturingClientState = true;
	}
	renderer->getModelViewMatrix()->identity();
	renderer->onUpdateModelViewMatrix();
	for (auto i = 0; i < visiblePses->size(); i++) {
		PointsParticleSystemEntityInternal* ppse = java_cast< PointsParticleSystemEntity* >(visiblePses->get(i));
		auto key = java_cast< Key* >(pseKeyPool->allocate());
		createPseKey(key, ppse->getEffectColorAdd(), ppse->getEffectColorMul(), ppse->isPickable(), ppse->getParticleEmitter()->getColorStart()->equals(static_cast< Color4Base* >(ppse->getParticleEmitter()->getColorEnd())) == false);
		if (pseKeys->contains(key) == false) {
			pseKeys->add(key);
		} else {
			pseKeyPool->release(key);
		}
	}
	auto innerPseKey = java_cast< Key* >(pseKeyPool->allocate());
	for (auto i = 0; i < pseKeys->size(); i++) {
		auto pseKey = java_cast< Key* >(pseKeys->get(i));
		auto pseSort = false;
		PointsParticleSystemEntityInternal* currentPse = nullptr;
		for (auto j = 0; j < visiblePses->size(); j++) {
			PointsParticleSystemEntityInternal* ppse = java_cast< PointsParticleSystemEntity* >(visiblePses->get(j));
			createPseKey(innerPseKey, ppse->getEffectColorAdd(), ppse->getEffectColorMul(), ppse->isPickable(), ppse->getParticleEmitter()->getColorStart()->equals(static_cast< Color4Base* >(ppse->getParticleEmitter()->getColorEnd())) == false);
			if (pseKey->equals(innerPseKey) == false) {
				continue;
			} else {
				currentPse = java_cast< PointsParticleSystemEntity* >(visiblePses->get(j));
				pseSort = ppse->getParticleEmitter()->getColorStart()->equals(static_cast< Color4Base* >(ppse->getParticleEmitter()->getColorEnd())) == false;
			}
			pseTransparentRenderPointsPool->merge(ppse->getRenderPointsPool());
		}
		if (pseSort == true)
			pseTransparentRenderPointsPool->sort();

		for (auto _i = pseTransparentRenderPointsPool->getTransparentRenderPoints()->iterator(); _i->hasNext(); ) {
			TransparentRenderPoint* point = java_cast< TransparentRenderPoint* >(_i->next());
			{
				if (point->acquired == false)
					break;

				psePointBatchVBORenderer->addPoint(point);
			}
		}
		renderer->setEffectColorAdd(currentPse->getEffectColorAdd()->getArray());
		renderer->setEffectColorMul(currentPse->getEffectColorMul()->getArray());
		renderer->onUpdateEffect();
		depthBuffer = currentPse->isPickable();
		if (depthBuffer) {
			renderer->enableDepthBuffer();
		} else {
			renderer->disableDepthBuffer();
		}
		psePointBatchVBORenderer->render();
		psePointBatchVBORenderer->clear();
		pseTransparentRenderPointsPool->reset();
	}
	for (auto i = 0; i < pseKeys->size(); i++) {
		pseKeyPool->release(java_cast< Key* >(pseKeys->get(i)));
	}
	pseKeys->clear();
	pseKeyPool->release(innerPseKey);
	renderer->disableBlending();
	if (depthBuffer == false)
		renderer->enableDepthBuffer();

	renderer->unbindBufferObjects();
	renderer->enableClientState(renderer->CLIENTSTATE_NORMAL_ARRAY);
	renderer->disableClientState(renderer->CLIENTSTATE_COLOR_ARRAY);
	renderer->getModelViewMatrix()->set(modelViewMatrix);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Object3DVBORenderer::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.Object3DVBORenderer", 49);
    return c;
}

java::lang::Class* Object3DVBORenderer::getClass0()
{
	return class_();
}

