#include <tdme/engine/subsystems/object/Object3DVBORenderer.h>

#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <string>

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
#include <tdme/engine/subsystems/object/Object3DVBORenderer_TransparentRenderFacesGroupPool.h>
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
#include <tdme/utils/_Console.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using std::find;
using std::map;
using std::set;
using std::sort;
using std::vector;
using std::wstring;
using std::to_wstring;

using tdme::engine::subsystems::object::Object3DVBORenderer;
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
using tdme::engine::subsystems::object::Object3DVBORenderer_TransparentRenderFacesGroupPool;
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
using tdme::utils::_Console;

Object3DVBORenderer::Object3DVBORenderer(Engine* engine, GLRenderer* renderer) 
{
	this->engine = engine;
	this->renderer = renderer;
	transparentRenderFacesPool = nullptr;
	pseTransparentRenderPointsPool = nullptr;
	psePointBatchVBORenderer = nullptr;
	transparentRenderFacesGroupPool = new Object3DVBORenderer_TransparentRenderFacesGroupPool();
	transparentRenderFacesPool = new TransparentRenderFacesPool();
	pseTransparentRenderPointsPool = new TransparentRenderPointsPool(16384);
	psePointBatchVBORenderer = new BatchVBORendererPoints(renderer, 0);
}

constexpr int32_t Object3DVBORenderer::BATCHVBORENDERER_MAX;

void Object3DVBORenderer::initialize()
{
	psePointBatchVBORenderer->initialize();
}

void Object3DVBORenderer::dispose()
{
	for (auto batchVBORenderer: trianglesBatchVBORenderers) {
		batchVBORenderer->dispose();
		batchVBORenderer->release();
	}
	psePointBatchVBORenderer->dispose();
}

BatchVBORendererTriangles* Object3DVBORenderer::acquireTrianglesBatchVBORenderer()
{
	auto i = 0;
	for (auto batchVBORenderer: trianglesBatchVBORenderers) {
		if (batchVBORenderer->acquire()) return batchVBORenderer;
		i++;
	}
	if (i < BATCHVBORENDERER_MAX) {
		auto batchVBORenderer = new BatchVBORendererTriangles(renderer, i);
		batchVBORenderer->initialize();
		trianglesBatchVBORenderers.push_back(batchVBORenderer);
		if (batchVBORenderer->acquire()) return batchVBORenderer;

	}
	_Console::println(wstring(L"Object3DVBORenderer::acquireTrianglesBatchVBORenderer()::failed"));
	return nullptr;
}

void Object3DVBORenderer::reset()
{
	visibleObjectsByModels.clear();
}

void Object3DVBORenderer::render(const vector<Object3D*>& objects, bool renderTransparentFaces)
{
	transparentRenderFacesPool->reset();
	releaseTransparentFacesGroups();
	for (auto objectIdx = 0; objectIdx < objects.size(); objectIdx++) {
		auto object = objects.at(objectIdx);
		auto modelId = object->getModel()->getId();
		auto& visibleObjectsByModel = visibleObjectsByModels[modelId];
		visibleObjectsByModel.push_back(object);
	}
	for (auto& objectsByModelIt: visibleObjectsByModels) {
		auto& objectsByModel = objectsByModelIt.second;
		if (objectsByModel.size() > 0) {
			renderObjectsOfSameType(objectsByModel, renderTransparentFaces);
			objectsByModel.clear();
		}
	}
	auto transparentRenderFaces = transparentRenderFacesPool->getTransparentRenderFaces();
	if (transparentRenderFaces->size() > 0) {
		sort(transparentRenderFaces->begin(), transparentRenderFaces->end(), TransparentRenderFace::compare);
		renderer->disableDepthBuffer();
		renderer->disableCulling();
		renderer->enableBlending();
		renderer->setFrontFace(renderer->FRONTFACE_CCW);
		for (auto transparentRenderFace: *transparentRenderFacesPool->getTransparentRenderFaces()) {
			if (groupTransparentRenderFaces.size() == 0) {
				groupTransparentRenderFaces.push_back(transparentRenderFace);
			} else if (groupTransparentRenderFaces.size() > 0) {
				if (groupTransparentRenderFaces.at(0)->object3DGroup == transparentRenderFace->object3DGroup) {
					groupTransparentRenderFaces.push_back(transparentRenderFace);
				} else {
					prepareTransparentFaces(groupTransparentRenderFaces);
					groupTransparentRenderFaces.clear();
					groupTransparentRenderFaces.push_back(transparentRenderFace);
				}
			}
		}
		if (groupTransparentRenderFaces.size() > 0) {
			prepareTransparentFaces(groupTransparentRenderFaces);
			groupTransparentRenderFaces.clear();
		}
		renderTransparentFacesGroups();
		renderer->disableBlending();
		renderer->enableCulling();
		renderer->enableDepthBuffer();
	}
}

void Object3DVBORenderer::prepareTransparentFaces(const vector<TransparentRenderFace*>& transparentRenderFaces)
{
	auto object3DGroup = transparentRenderFaces.at(0)->object3DGroup;
	auto object3D = dynamic_cast<Object3D*>(object3DGroup->object);
	Matrix4x4 modelViewMatrix;
	if (object3DGroup->mesh->skinning == true) {
		modelViewMatrix.identity();
	} else {
		modelViewMatrix.set(*object3DGroup->groupTransformationsMatrix).multiply(object3D->getTransformationsMatrix()).multiply(renderer->getModelViewMatrix());
	}
	auto model = object3DGroup->object->getModel();
	auto facesEntities = object3DGroup->group->getFacesEntities();
	FacesEntity* facesEntity = nullptr;
	auto depthBuffer = false;
	auto& effectColorAdd = object3D->getEffectColorAdd();
	auto& effectColorMul = object3D->getEffectColorMul();
	Material* material = nullptr;
	auto textureCoordinates = false;
	Vector3 transformedVector;
	Vector3 transformedNormal;
	for (auto i = 0; i < transparentRenderFaces.size(); i++) {
		auto transparentRenderFace = transparentRenderFaces.at(i);
		auto facesEntityIdx = transparentRenderFace->facesEntityIdx;
		if (facesEntity != &(*facesEntities)[facesEntityIdx]) {
			facesEntity = &(*facesEntities)[facesEntityIdx];
			material = facesEntity->getMaterial();
		}
		textureCoordinates = facesEntity->isTextureCoordinatesAvailable();
		wstring transparentRenderFacesGroupKey = TransparentRenderFacesGroup::createKey(model, object3DGroup, facesEntityIdx, effectColorAdd, effectColorMul, material, textureCoordinates);
		TransparentRenderFacesGroup* trfGroup = nullptr;
		auto trfGroupIt = transparentRenderFacesGroups.find(transparentRenderFacesGroupKey);
		if (trfGroupIt != transparentRenderFacesGroups.end()) {
			trfGroup = trfGroupIt->second;
		}
		if (trfGroup == nullptr) {
			trfGroup = static_cast<TransparentRenderFacesGroup*>(transparentRenderFacesGroupPool->allocate());
			trfGroup->set(this, model, object3DGroup, facesEntityIdx, effectColorAdd, effectColorMul, material, textureCoordinates);
			transparentRenderFacesGroups[transparentRenderFacesGroupKey] = trfGroup;
		}
		for (auto vertexIdx = 0; vertexIdx < 3; vertexIdx++) {
			auto arrayIdx = transparentRenderFace->object3DGroup->mesh->indices[transparentRenderFace->faceIdx * 3 + vertexIdx];
			trfGroup->addVertex(
				modelViewMatrix.multiply((*transparentRenderFace->object3DGroup->mesh->vertices)[arrayIdx], transformedVector),
				modelViewMatrix.multiplyNoTranslation((*transparentRenderFace->object3DGroup->mesh->normals)[arrayIdx], transformedNormal),
				transparentRenderFace->object3DGroup->mesh->textureCoordinates->size() >0 ?
					&(*transparentRenderFace->object3DGroup->mesh->textureCoordinates)[arrayIdx] :
					static_cast< TextureCoordinate* >(nullptr)
			);
		}
	}
}

void Object3DVBORenderer::renderTransparentFacesGroups()
{
	for (auto it: transparentRenderFacesGroups) {
		it.second->render(renderer);
	}
}

void Object3DVBORenderer::releaseTransparentFacesGroups()
{
	for (auto it: transparentRenderFacesGroups) {
		transparentRenderFacesGroupPool->release(it.second);
	}
	transparentRenderFacesGroups.clear();
}

void Object3DVBORenderer::renderObjectsOfSameType(const vector<Object3D*>& objects, bool collectTransparentFaces)
{
	for (auto object: objects) {
		for (auto j = 0; j < object->object3dGroups.size(); j++) {
			auto object3DGroup = object->object3dGroups[j];
			object3DGroup->renderer->preRender(this);
		}
	}
	auto shadowMapping = engine->getShadowMapping();
	Matrix4x4 modelViewMatrix;
	Matrix4x4 modelViewMatrixBackup;
	modelViewMatrixBackup.set(renderer->getModelViewMatrix());
	auto currentFrontFace = -1;
	auto firstObject = objects.at(0);
	vector<int32_t>* boundVBOBaseIds = nullptr;
	vector<int32_t>* boundVBOTangentBitangentIds = nullptr;
	vector<int32_t>* boundSkinningIds = nullptr;
	for (auto object3DGroupIdx = 0; object3DGroupIdx < firstObject->object3dGroups.size(); object3DGroupIdx++) {
		auto object3DGroup = firstObject->object3dGroups[object3DGroupIdx];
		auto facesEntities = object3DGroup->group->getFacesEntities();
		auto faceIdx = 0;
		auto facesEntityIdxCount = facesEntities->size();
		for (auto faceEntityIdx = 0; faceEntityIdx < facesEntityIdxCount; faceEntityIdx++) {
			auto facesEntity = &(*facesEntities)[faceEntityIdx];
			auto isTextureCoordinatesAvailable = facesEntity->isTextureCoordinatesAvailable();
			auto faces = facesEntity->getFaces()->size();
			auto material = facesEntity->getMaterial();
			auto transparentFacesEntity = false;
			if (material != nullptr) {
				if (material->hasTransparency() == true)
					transparentFacesEntity = true;

			}
			if (transparentFacesEntity == true) {
				auto objectCount = objects.size();
				for (auto objectIdx = 0; objectIdx < objectCount; objectIdx++) {
					auto object = objects.at(objectIdx);
					auto _object3DGroup = object->object3dGroups[object3DGroupIdx];
					Object3DGroup::setupTextures(renderer, object3DGroup, faceEntityIdx);
					if (collectTransparentFaces == true) {
						transparentRenderFacesPool->createTransparentRenderFaces(
							(_object3DGroup->mesh->skinning == true ?
								modelViewMatrix.identity() :
								modelViewMatrix.set(*_object3DGroup->groupTransformationsMatrix)
							).
								multiply(object->getTransformationsMatrix()).multiply(modelViewMatrixBackup),
								object->object3dGroups[object3DGroupIdx],
								faceEntityIdx,
								faceIdx
							);
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
			auto objectCount = objects.size();
			for (auto objectIdx = 0; objectIdx < objectCount; objectIdx++) {
				auto object = objects.at(objectIdx);
				auto _object3DGroup = object->object3dGroups[object3DGroupIdx];
				if (objectIdx == 0) {
					setupMaterial(_object3DGroup, faceEntityIdx);
				} else {
					Object3DGroup::setupTextures(renderer, _object3DGroup, faceEntityIdx);
				}
				if (object->effectColorMul.getAlpha() < 1.0f - MathTools::EPSILON || object->effectColorAdd.getAlpha() < -MathTools::EPSILON) {
					if (collectTransparentFaces == true) {
						transparentRenderFacesPool->createTransparentRenderFaces(
							(_object3DGroup->mesh->skinning == true ?
								modelViewMatrix.identity() :
								modelViewMatrix.set(*_object3DGroup->groupTransformationsMatrix)
							).multiply(object->getTransformationsMatrix()).multiply(modelViewMatrixBackup),
							_object3DGroup,
							faceEntityIdx,
							faceIdx
						);
					}
					continue;
				}
				auto currentVBOGlIds = _object3DGroup->renderer->vboBaseIds;
				if (boundVBOBaseIds != currentVBOGlIds) {
					boundVBOBaseIds = currentVBOGlIds;
					if (isTextureCoordinatesAvailable == true) {
						renderer->bindTextureCoordinatesBufferObject((*currentVBOGlIds)[3]);
					}
					renderer->bindVerticesBufferObject((*currentVBOGlIds)[1]);
					renderer->bindNormalsBufferObject((*currentVBOGlIds)[2]);
					renderer->bindIndicesBufferObject((*currentVBOGlIds)[0]);
				}
				auto currentVBOTangentBitangentIds = _object3DGroup->renderer->vboTangentBitangentIds;
				if (renderer->isNormalMappingAvailable() && currentVBOTangentBitangentIds != nullptr && currentVBOTangentBitangentIds != boundVBOTangentBitangentIds) {
					renderer->bindTangentsBufferObject((*currentVBOTangentBitangentIds)[0]);
					renderer->bindBitangentsBufferObject((*currentVBOTangentBitangentIds)[1]);
				}
				renderer->getModelViewMatrix().set(
					(_object3DGroup->mesh->skinning == true ?
						modelViewMatrix.identity() :
						modelViewMatrix.set(*_object3DGroup->groupTransformationsMatrix)
					).
						multiply(object->getTransformationsMatrix()).
						multiply(modelViewMatrixBackup)
				);
				renderer->onUpdateModelViewMatrix();
				auto objectFrontFace = matrix4x4Negative.isNegative(renderer->getModelViewMatrix()) == false ? renderer->FRONTFACE_CCW : renderer->FRONTFACE_CW;
				if (objectFrontFace != currentFrontFace) {
					renderer->setFrontFace(objectFrontFace);
					currentFrontFace = objectFrontFace;
				}
				renderer->setEffectColorMul(object->effectColorMul.getArray());
				renderer->setEffectColorAdd(object->effectColorAdd.getArray());
				renderer->onUpdateEffect();
				if (shadowMapping != nullptr) {
					shadowMapping->startObjectTransformations(
						(_object3DGroup->mesh->skinning == true ?
							modelViewMatrix.identity() :
							modelViewMatrix.set(*_object3DGroup->groupTransformationsMatrix)
						).multiply(object->getTransformationsMatrix()));
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
	renderer->getModelViewMatrix().set(modelViewMatrixBackup);
}

void Object3DVBORenderer::setupMaterial(Object3DGroup* object3DGroup, int32_t facesEntityIdx)
{
	auto facesEntities = object3DGroup->group->getFacesEntities();
	auto material = (*facesEntities)[facesEntityIdx].getMaterial();
	if (material == nullptr)
		material = Material::getDefaultMaterial();

	Object3DGroup::setupTextures(renderer, object3DGroup, facesEntityIdx);
	renderer->setMaterialAmbient(material->getAmbientColor().getArray());
	renderer->setMaterialDiffuse(material->getDiffuseColor().getArray());
	renderer->setMaterialSpecular(material->getSpecularColor().getArray());
	renderer->setMaterialEmission(material->getEmissionColor().getArray());
	renderer->setMaterialShininess(material->getShininess());
	renderer->onUpdateMaterial();
	renderer->setTextureUnit(LightingShader::TEXTUREUNIT_DIFFUSE);
	renderer->bindTexture(object3DGroup->dynamicDiffuseTextureIdsByEntities[facesEntityIdx] != Object3DGroup::GLTEXTUREID_NONE ? object3DGroup->dynamicDiffuseTextureIdsByEntities[facesEntityIdx] : object3DGroup->materialDiffuseTextureIdsByEntities[facesEntityIdx]);
	if (renderer->isSpecularMappingAvailable() == true) {
		renderer->setTextureUnit(LightingShader::TEXTUREUNIT_SPECULAR);
		renderer->bindTexture(object3DGroup->materialSpecularTextureIdsByEntities[facesEntityIdx]);
	}
	if (renderer->isDisplacementMappingAvailable() == true) {
		renderer->setTextureUnit(LightingShader::TEXTUREUNIT_DISPLACEMENT);
		renderer->bindTexture(object3DGroup->materialDisplacementTextureIdsByEntities[facesEntityIdx]);
	}
	if (renderer->isNormalMappingAvailable() == true) {
		renderer->setTextureUnit(LightingShader::TEXTUREUNIT_NORMAL);
		renderer->bindTexture(object3DGroup->materialNormalTextureIdsByEntities[facesEntityIdx]);
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

const wstring Object3DVBORenderer::createPseKey(Color4& effectColorAdd, Color4& effectColorMul, bool depthBuffer, bool sort)
{
	auto& efcaData = effectColorAdd.getArray();
	auto& efcmData = effectColorMul.getArray();
	wstring key =
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
		(depthBuffer == true ? L"DBT" : L"DBF") +
		L"," +
		(sort == true ? L"DS" : L"NS");
	return key;
}

void Object3DVBORenderer::render(const vector<PointsParticleSystemEntity*>& visiblePses)
{
	if (visiblePses.size() == 0)
		return;

	Matrix4x4 modelViewMatrix;
	modelViewMatrix.set(renderer->getModelViewMatrix());
	auto depthBuffer = false;
	renderer->enableBlending();
	renderer->disableDepthBuffer();
	renderer->disableClientState(renderer->CLIENTSTATE_NORMAL_ARRAY);
	renderer->enableClientState(renderer->CLIENTSTATE_COLOR_ARRAY);
	if (renderer->renderingTexturingClientState == false) {
		renderer->enableClientState(renderer->CLIENTSTATE_TEXTURECOORD_ARRAY);
		renderer->renderingTexturingClientState = true;
	}
	renderer->getModelViewMatrix().identity();
	renderer->onUpdateModelViewMatrix();
	set<wstring> pseKeys;
	for (auto i = 0; i < visiblePses.size(); i++) {
		PointsParticleSystemEntityInternal* ppse = visiblePses.at(i);
		wstring pseKey = createPseKey(ppse->getEffectColorAdd(), ppse->getEffectColorMul(), ppse->isPickable(), ppse->getParticleEmitter()->getColorStart()->equals(*ppse->getParticleEmitter()->getColorEnd()) == false);
		pseKeys.insert(pseKey);
	}
	for (auto pseKey: pseKeys) {
		auto pseSort = false;
		PointsParticleSystemEntityInternal* currentPse = nullptr;
		for (auto j = 0; j < visiblePses.size(); j++) {
			PointsParticleSystemEntityInternal* ppse = visiblePses.at(j);
			wstring innerPseKey = createPseKey(ppse->getEffectColorAdd(), ppse->getEffectColorMul(), ppse->isPickable(), ppse->getParticleEmitter()->getColorStart()->equals(*ppse->getParticleEmitter()->getColorEnd()) == false);
			if (pseKey != innerPseKey) {
				continue;
			} else {
				currentPse = visiblePses.at(j);
				pseSort = ppse->getParticleEmitter()->getColorStart()->equals(*ppse->getParticleEmitter()->getColorEnd()) == false;
			}
			pseTransparentRenderPointsPool->merge(ppse->getRenderPointsPool());
		}

		if (pseSort == true) pseTransparentRenderPointsPool->sort();

		for (auto& point: *pseTransparentRenderPointsPool->getTransparentRenderPoints()) {
			if (point.acquired == false)
				break;

			psePointBatchVBORenderer->addPoint(&point);
		}
		renderer->setEffectColorAdd(currentPse->getEffectColorAdd().getArray());
		renderer->setEffectColorMul(currentPse->getEffectColorMul().getArray());
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
	renderer->disableBlending();
	if (depthBuffer == false)
		renderer->enableDepthBuffer();

	renderer->unbindBufferObjects();
	renderer->enableClientState(renderer->CLIENTSTATE_NORMAL_ARRAY);
	renderer->disableClientState(renderer->CLIENTSTATE_COLOR_ARRAY);
	renderer->getModelViewMatrix().set(modelViewMatrix);
}
