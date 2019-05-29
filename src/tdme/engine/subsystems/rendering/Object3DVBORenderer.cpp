#include <tdme/engine/subsystems/rendering/Object3DVBORenderer.h>

#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <unordered_set>

#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/PointsParticleSystem.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/rendering/BatchVBORendererPoints.h>
#include <tdme/engine/subsystems/rendering/BatchVBORendererTriangles.h>
#include <tdme/engine/subsystems/rendering/Object3DBase.h>
#include <tdme/engine/subsystems/rendering/Object3DGroup.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupVBORenderer.h>
#include <tdme/engine/subsystems/rendering/Object3DVBORenderer_TransparentRenderFacesGroupPool.h>
#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFace.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFacesGroup.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFacesPool.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPointsPool.h>
#include <tdme/engine/subsystems/particlesystem/ParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>
#include <tdme/engine/subsystems/particlesystem/PointsParticleSystemInternal.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Matrix4x4Negative.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/threading/Semaphore.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/utils/Pool.h>
#include <tdme/utils/Console.h>

using std::find;
using std::map;
using std::set;
using std::sort;
using std::vector;
using std::string;
using std::to_string;
using std::unordered_set;

using tdme::engine::subsystems::rendering::Object3DVBORenderer;
using tdme::engine::Engine;
using tdme::engine::Object3D;
using tdme::engine::PointsParticleSystem;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::rendering::BatchVBORendererPoints;
using tdme::engine::subsystems::rendering::BatchVBORendererTriangles;
using tdme::engine::subsystems::rendering::Object3DBase;
using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::engine::subsystems::rendering::Object3DGroupMesh;
using tdme::engine::subsystems::rendering::Object3DGroupVBORenderer;
using tdme::engine::subsystems::rendering::Object3DVBORenderer_TransparentRenderFacesGroupPool;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::engine::subsystems::rendering::TransparentRenderFace;
using tdme::engine::subsystems::rendering::TransparentRenderFacesGroup;
using tdme::engine::subsystems::rendering::TransparentRenderFacesPool;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::particlesystem::PointsParticleSystemInternal;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Matrix4x4Negative;
using tdme::math::Vector3;
using tdme::os::threading::Semaphore;
using tdme::os::threading::Thread;
using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::utils::Pool;
using tdme::utils::Console;

constexpr int32_t Object3DVBORenderer::BATCHVBORENDERER_MAX;
constexpr int32_t Object3DVBORenderer::INSTANCEDRENDERING_OBJECTS_MAX;

Object3DVBORenderer::Object3DVBORenderer(Engine* engine, Renderer* renderer):
	renderThreadWaitSemaphore("object3dvborenderer-renderthread-waitsemaphore", 0),
	mainThreadWaitSemaphore("object3dvborenderer-mainthread-waitsemaphore", 0)
{
	this->engine = engine;
	this->renderer = renderer;
	transparentRenderFacesGroupPool = new Object3DVBORenderer_TransparentRenderFacesGroupPool();
	transparentRenderFacesPool = new TransparentRenderFacesPool();
	pseTransparentRenderPointsPool = new TransparentRenderPointsPool(65535);
	psePointBatchVBORenderer = new BatchVBORendererPoints(renderer, 0);
	if (this->renderer->isInstancedRenderingAvailable() == true) {
		threadCount = renderer->isSupportingMultithreadedRendering() == true?Engine::RENDERING_THREADS_MAX:1;
		bbEffectColorMuls.resize(threadCount);
		bbEffectColorAdds.resize(threadCount);
		bbMvMatrices.resize(threadCount);
		vboInstancedRenderingIds.resize(threadCount);
		for (auto i = 0; i < threadCount; i++) {
			bbEffectColorMuls[i] = ByteBuffer::allocate(4 * sizeof(float) * INSTANCEDRENDERING_OBJECTS_MAX);
			bbEffectColorAdds[i] = ByteBuffer::allocate(4 * sizeof(float) * INSTANCEDRENDERING_OBJECTS_MAX);
			bbMvMatrices[i] = ByteBuffer::allocate(16 * sizeof(float) * INSTANCEDRENDERING_OBJECTS_MAX);
		}
	}
}

Object3DVBORenderer::~Object3DVBORenderer() {
	for (auto batchVBORenderer: trianglesBatchVBORenderers) {
		delete batchVBORenderer;
	}
	delete transparentRenderFacesGroupPool;
	delete transparentRenderFacesPool;
	delete pseTransparentRenderPointsPool;
	delete psePointBatchVBORenderer;
}

void Object3DVBORenderer::initialize()
{
	psePointBatchVBORenderer->initialize();
	for (auto i = 0; i < threadCount; i++) {
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO("tdme.object3dvborenderer.instancedrendering." + to_string(i), 3, false);
		vboInstancedRenderingIds[i] = vboManaged->getVBOIds();
	}
	if (threadCount > 1) {
		threads.resize(threadCount);
		for (auto i = 0; i < threadCount; i++) {
			threads[i] = new RenderThread(
				this,
				i,
				&renderThreadWaitSemaphore,
				&mainThreadWaitSemaphore,
				renderer->getContext(i)
			);
			threads[i]->start();
		}
	}
}

void Object3DVBORenderer::dispose()
{
	// dispose VBOs
	for (auto i = 0; i < threadCount; i++) {
		Engine::getInstance()->getVBOManager()->removeVBO("tdme.object3dvborenderer.instancedrendering." + to_string(i));
	}
	// dispose batch vbo renderer
	for (auto batchVBORenderer: trianglesBatchVBORenderers) {
		batchVBORenderer->dispose();
		batchVBORenderer->release();
	}
	psePointBatchVBORenderer->dispose();
}

BatchVBORendererTriangles* Object3DVBORenderer::acquireTrianglesBatchVBORenderer()
{
	// check for free batch vbo renderer
	auto i = 0;
	for (auto batchVBORenderer: trianglesBatchVBORenderers) {
		if (batchVBORenderer->acquire()) return batchVBORenderer;
		i++;
	}
	// try to add one
	if (i < BATCHVBORENDERER_MAX) {
		auto batchVBORenderer = new BatchVBORendererTriangles(renderer, i);
		batchVBORenderer->initialize();
		trianglesBatchVBORenderers.push_back(batchVBORenderer);
		if (batchVBORenderer->acquire()) return batchVBORenderer;

	}
	Console::println(string("Object3DVBORenderer::acquireTrianglesBatchVBORenderer()::failed"));
	// nope
	return nullptr;
}

void Object3DVBORenderer::reset()
{
	visibleObjectsByModels.clear();
}

void Object3DVBORenderer::render(const vector<Object3D*>& objects, bool renderTransparentFaces, int32_t renderTypes)
{
	// clear transparent render faces data
	transparentRenderFacesPool->reset();
	releaseTransparentFacesGroups();

	// sort objects by model
	for (auto objectIdx = 0; objectIdx < objects.size(); objectIdx++) {
		auto object = objects[objectIdx];
		auto modelId = object->getModel()->getId();
		auto& visibleObjectsByModel = visibleObjectsByModels[modelId];
		visibleObjectsByModel.push_back(object);
	}

	// render objects
	for (auto& objectsByModelIt: visibleObjectsByModels) {
		auto& objectsByModel = objectsByModelIt.second;
		if (objectsByModel.size() > 0) {
			renderObjectsOfSameType(objectsByModel, renderTransparentFaces, renderTypes);
			objectsByModel.clear();
		}
	}
	// use default context
	auto context = renderer->getDefaultContext();
	// render transparent render faces if any exist
	auto transparentRenderFaces = transparentRenderFacesPool->getTransparentRenderFaces();
	if (transparentRenderFaces->size() > 0) {
		// sort transparent render faces from far to near
		sort(transparentRenderFaces->begin(), transparentRenderFaces->end(), TransparentRenderFace::compare);
		// second render pass, draw color buffer for transparent objects
		// 	set up blending, but no culling and no depth buffer
		//	TODO: enabling depth buffer let shadow disappear
		//renderer->disableDepthBufferWriting();  // TODO: a.drewke, verify that this works ok in all cases?
		renderer->disableCulling();
		renderer->enableBlending();
		// disable foliage animation
		renderer->setShader("default");
		renderer->onUpdateShader(context);
		// have identity texture matrix
		renderer->getTextureMatrix(context).identity();
		renderer->onUpdateTextureMatrix(context);
		// actually this should not make any difference as culling is disabled
		// but having a fixed value is not a bad idea except that it is a renderer call
		// TODO: confirm this
		renderer->setFrontFace(renderer->FRONTFACE_CCW);
		for (auto transparentRenderFace: *transparentRenderFaces) {
			// do we have any faces yet?
			if (groupTransparentRenderFaces.size() == 0) {
				// nope, so add this one
				groupTransparentRenderFaces.push_back(transparentRenderFace);
			} else
			// do we have more than face already?
			if (groupTransparentRenderFaces.size() > 0) {
				// check if we have more of first type
				if (groupTransparentRenderFaces[0]->object3DGroup == transparentRenderFace->object3DGroup) {
					// yep, we can add this one
					groupTransparentRenderFaces.push_back(transparentRenderFace);
				} else {
					// no, render grouped faces
					prepareTransparentFaces(groupTransparentRenderFaces);
					// reset
					groupTransparentRenderFaces.clear();
					// add current face
					groupTransparentRenderFaces.push_back(transparentRenderFace);
				}
			}
		}
		// 	check if there are any left overs
		if (groupTransparentRenderFaces.size() > 0) {
			prepareTransparentFaces(groupTransparentRenderFaces);
			groupTransparentRenderFaces.clear();
		}
		// render transparent faces groups
		renderTransparentFacesGroups(context);
		//	no blending, but culling and depth buffer
		renderer->disableBlending();
		renderer->enableCulling();
		//renderer->enableDepthBufferWriting(); // TODO: a.drewke, verify that this works ok in all cases?
		// done!
	}
}

void Object3DVBORenderer::prepareTransparentFaces(const vector<TransparentRenderFace*>& transparentRenderFaces)
{
	// all those faces should share the object and object 3d group, ...
	auto object3DGroup = transparentRenderFaces[0]->object3DGroup;
	auto object3D = dynamic_cast<Object3D*>(object3DGroup->object);
	// model view matrix to be used with given transparent render faces
	Matrix4x4 modelViewMatrix;
	if (object3DGroup->mesh->skinning == true) {
		modelViewMatrix.identity();
	} else {
		if (renderer->isInstancedRenderingAvailable() == true) {
			modelViewMatrix.set(*object3DGroup->groupTransformationsMatrix).multiply(object3D->getTransformationsMatrix());
		} else {
			modelViewMatrix.set(*object3DGroup->groupTransformationsMatrix).multiply(object3D->getTransformationsMatrix()).multiply(renderer->getCameraMatrix());
		}
	}
	//
	auto model = object3DGroup->object->getModel();
	auto facesEntities = object3DGroup->group->getFacesEntities();
	FacesEntity* facesEntity = nullptr;
	// attributes we collect for a transparent render face group
	auto depthBuffer = false;
	auto& effectColorAdd = object3D->getEffectColorAdd();
	auto& effectColorMul = object3D->getEffectColorMul();
	Material* material = nullptr;
	auto textureCoordinates = false;
	Vector3 transformedVector;
	Vector3 transformedNormal;
	Vector2 transformedTextureCoordinate;
	// render transparent faces
	for (auto i = 0; i < transparentRenderFaces.size(); i++) {
		auto transparentRenderFace = transparentRenderFaces[i];
		auto facesEntityIdx = transparentRenderFace->facesEntityIdx;
		// determine if faces entity and so material did switch between last face and current face
		if (facesEntity != &(*facesEntities)[facesEntityIdx]) {
			facesEntity = &(*facesEntities)[facesEntityIdx];
			material = facesEntity->getMaterial();
		}
		textureCoordinates = facesEntity->isTextureCoordinatesAvailable();
		// create group key
		string transparentRenderFacesGroupKey = TransparentRenderFacesGroup::createKey(model, object3DGroup, facesEntityIdx, effectColorAdd, effectColorMul, material, textureCoordinates, object3D->getShader());
		// get group
		TransparentRenderFacesGroup* trfGroup = nullptr;
		auto trfGroupIt = transparentRenderFacesGroups.find(transparentRenderFacesGroupKey);
		if (trfGroupIt != transparentRenderFacesGroups.end()) {
			trfGroup = trfGroupIt->second;
		}
		if (trfGroup == nullptr) {
			// we do not have the group, create group
			trfGroup = transparentRenderFacesGroupPool->allocate();
			trfGroup->set(this, model, object3DGroup, facesEntityIdx, effectColorAdd, effectColorMul, material, textureCoordinates, object3D->getShader());
			transparentRenderFacesGroups[transparentRenderFacesGroupKey] = trfGroup;
		}
		for (auto vertexIdx = 0; vertexIdx < 3; vertexIdx++) {
			auto arrayIdx = transparentRenderFace->object3DGroup->mesh->indices[transparentRenderFace->faceIdx * 3 + vertexIdx];
			trfGroup->addVertex(
				modelViewMatrix.multiply((*transparentRenderFace->object3DGroup->mesh->vertices)[arrayIdx], transformedVector),
				modelViewMatrix.multiplyNoTranslation((*transparentRenderFace->object3DGroup->mesh->normals)[arrayIdx], transformedNormal),
				transparentRenderFace->object3DGroup->textureMatricesByEntities[facesEntityIdx].multiply(
					transparentRenderFace->object3DGroup->mesh->textureCoordinates->size() >0 ?
						Vector2((*transparentRenderFace->object3DGroup->mesh->textureCoordinates)[arrayIdx].getArray()):
						Vector2(0.0f, 0.0f),
						transformedTextureCoordinate
				)
			);
		}
	}
}

void Object3DVBORenderer::renderTransparentFacesGroups(void* context) {
	for (auto it: transparentRenderFacesGroups) {
		it.second->render(renderer, context);
	}
}

void Object3DVBORenderer::releaseTransparentFacesGroups()
{
	for (auto it: transparentRenderFacesGroups) {
		transparentRenderFacesGroupPool->release(it.second);
	}
	transparentRenderFacesGroups.clear();
}

void Object3DVBORenderer::renderObjectsOfSameType(const vector<Object3D*>& objects, bool collectTransparentFaces, int32_t renderTypes) {
	if (renderer->isInstancedRenderingAvailable() == true) {
		renderObjectsOfSameTypeInstanced(objects, collectTransparentFaces, renderTypes);
	} else {
		renderObjectsOfSameTypeNonInstanced(objects, collectTransparentFaces, renderTypes);
	}
}

void Object3DVBORenderer::renderObjectsOfSameTypeNonInstanced(const vector<Object3D*>& objects, bool collectTransparentFaces, int32_t renderTypes)
{
	Vector3 objectCamFromAxis;
	auto camera = engine->getCamera();

	// use default context
	auto context = renderer->getDefaultContext();

	//
	auto shadowMapping = engine->getShadowMapping();
	Matrix4x4 modelViewMatrix;
	Matrix4x4 cameraMatrix;
	cameraMatrix.set(renderer->getModelViewMatrix());
	// render faces entities
	auto currentFrontFace = -1;
	auto firstObject = objects[0];
	// all objects share the same object 3d group structure, so we just take the first one
	vector<int32_t>* boundVBOBaseIds = nullptr;
	vector<int32_t>* boundVBOTangentBitangentIds = nullptr;
	string currentShader;
	for (auto object3DGroupIdx = 0; object3DGroupIdx < firstObject->object3dGroups.size(); object3DGroupIdx++) {
		auto object3DGroup = firstObject->object3dGroups[object3DGroupIdx];
		// render each faces entity
		auto facesEntities = object3DGroup->group->getFacesEntities();
		auto faceIdx = 0;
		auto facesEntityIdxCount = facesEntities->size();
		for (auto faceEntityIdx = 0; faceEntityIdx < facesEntityIdxCount; faceEntityIdx++) {
			auto facesEntity = &(*facesEntities)[faceEntityIdx];
			auto isTextureCoordinatesAvailable = facesEntity->isTextureCoordinatesAvailable();
			auto faces = facesEntity->getFaces()->size();
			// material
			auto material = facesEntity->getMaterial();
			// determine if transparent
			auto transparentFacesEntity = false;
			//	via material
			if (material != nullptr) {
				if (material->hasColorTransparency() == true || material->hasTextureTransparency() == true) transparentFacesEntity = true;
				if (material->hasDiffuseTextureTransparency() == true && material->hasDiffuseTextureMaskedTransparency() == true) {
					renderer->disableCulling();
				}
			}
			// skip, if requested
			if (transparentFacesEntity == true) {
				// add to transparent render faces, if requested
				auto objectCount = objects.size();
				for (auto objectIdx = 0; objectIdx < objectCount; objectIdx++) {
					auto object = objects[objectIdx];
					auto _object3DGroup = object->object3dGroups[object3DGroupIdx];
					// set up textures
					Object3DGroup::setupTextures(renderer, object3DGroup, faceEntityIdx);
					// set up transparent render faces
					if (collectTransparentFaces == true) {
						transparentRenderFacesPool->createTransparentRenderFaces(
							(_object3DGroup->mesh->skinning == true ?
								modelViewMatrix.identity() :
								modelViewMatrix.set(*_object3DGroup->groupTransformationsMatrix)
							).
								multiply(object->getTransformationsMatrix()).multiply(cameraMatrix),
								object->object3dGroups[object3DGroupIdx],
								faceEntityIdx,
								faceIdx
							);
					}
				}
				// keep track of rendered faces
				faceIdx += faces;
				// skip to next entity
				continue;
			}
			// draw this faces entity for each object
			bool materialUpdateOnly = false;
			auto objectCount = objects.size();
			for (auto objectIdx = 0; objectIdx < objectCount; objectIdx++) {
				auto object = objects[objectIdx];
				auto _object3DGroup = object->object3dGroups[object3DGroupIdx];
				//	check transparency via effect
				if (object->effectColorMul.getAlpha() < 1.0f - Math::EPSILON ||
					object->effectColorAdd.getAlpha() < -Math::EPSILON) {
					// add to transparent render faces, if requested
					if (collectTransparentFaces == true) {
						transparentRenderFacesPool->createTransparentRenderFaces(
							(_object3DGroup->mesh->skinning == true ?
								modelViewMatrix.identity() :
								modelViewMatrix.set(*_object3DGroup->groupTransformationsMatrix)
							).multiply(object->getTransformationsMatrix()).multiply(cameraMatrix),
							_object3DGroup,
							faceEntityIdx,
							faceIdx
						);
					}
					// skip to next object
					continue;
				}
				// shader
				auto objectShader = object->getDistanceShader().length() == 0?
					object->getShader():
					objectCamFromAxis.set(object->getBoundingBoxTransformed()->getCenter()).sub(camera->getLookFrom()).computeLengthSquared() < Math::square(object->getDistanceShaderDistance())?
						object->getShader():
						object->getDistanceShader();
				if (currentShader != objectShader) {
					currentShader = objectShader;
					renderer->setShader(currentShader);
					renderer->onUpdateShader(context);
					// update lights
					for (auto j = 0; j < engine->lights.size(); j++) {
						engine->lights[j].update(context);
					}
				}
				// set up material on first object
				string materialKey;
				if (materialUpdateOnly == false || checkMaterialChangable(_object3DGroup, faceEntityIdx, renderTypes) == true) {
					setupMaterial(context, _object3DGroup, faceEntityIdx, renderTypes, materialUpdateOnly, materialKey);
					// only update materials for next calls
					materialUpdateOnly = true;
				}
				// bind buffer base objects if not bound yet
				auto currentVBOIds = _object3DGroup->renderer->vboBaseIds;
				if (boundVBOBaseIds != currentVBOIds) {
					boundVBOBaseIds = currentVBOIds;
					//	texture coordinates
					if (isTextureCoordinatesAvailable == true &&
						(((renderTypes & RENDERTYPE_TEXTUREARRAYS) == RENDERTYPE_TEXTUREARRAYS) ||
						((renderTypes & RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY) == RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY && material != nullptr && material->hasDiffuseTextureMaskedTransparency() == true))) {
						renderer->bindTextureCoordinatesBufferObject(context, (*currentVBOIds)[3]);
					}
					// 	indices
					renderer->bindIndicesBufferObject(context, (*currentVBOIds)[0]);
					// 	vertices
					renderer->bindVerticesBufferObject(context, (*currentVBOIds)[1]);
					// 	normals
					if ((renderTypes & RENDERTYPE_NORMALS) == RENDERTYPE_NORMALS) renderer->bindNormalsBufferObject(context, (*currentVBOIds)[2]);
				}
				// bind tangent, bitangend buffers if not yet bound
				auto currentVBOTangentBitangentIds = _object3DGroup->renderer->vboTangentBitangentIds;
				if ((renderTypes & RENDERTYPE_NORMALS) == RENDERTYPE_NORMALS &&
					renderer->isNormalMappingAvailable() && currentVBOTangentBitangentIds != nullptr && currentVBOTangentBitangentIds != boundVBOTangentBitangentIds) {
					// tangent
					renderer->bindTangentsBufferObject(context, (*currentVBOTangentBitangentIds)[0]);
					// bitangent
					renderer->bindBitangentsBufferObject(context, (*currentVBOTangentBitangentIds)[1]);
				}
				// set up local -> world transformations matrix
				renderer->getModelViewMatrix().set(
					(_object3DGroup->mesh->skinning == true ?
						modelViewMatrix.identity() :
						modelViewMatrix.set(*_object3DGroup->groupTransformationsMatrix)
					).
						multiply(object->getTransformationsMatrix()).
						multiply(cameraMatrix)
				);
				renderer->onUpdateModelViewMatrix(context);
				// set up front face
				auto objectFrontFace = matrix4x4Negative.isNegative(renderer->getModelViewMatrix()) == false ? renderer->FRONTFACE_CCW : renderer->FRONTFACE_CW;
				if (objectFrontFace != currentFrontFace) {
					renderer->setFrontFace(objectFrontFace);
					currentFrontFace = objectFrontFace;
				}
				// set up effect color
				if ((renderTypes & RENDERTYPE_EFFECTCOLORS) == RENDERTYPE_EFFECTCOLORS) {
					renderer->setEffectColorMul(context, object->effectColorMul.getArray());
					renderer->setEffectColorAdd(context, object->effectColorAdd.getArray());
					renderer->onUpdateEffect(context);
				}
				// do transformation start to shadow mapping
				if ((renderTypes & RENDERTYPE_SHADOWMAPPING) == RENDERTYPE_SHADOWMAPPING &&
					shadowMapping != nullptr) {
					shadowMapping->startObjectTransformations(
						context,
						(_object3DGroup->mesh->skinning == true ?
							modelViewMatrix.identity() :
							modelViewMatrix.set(*_object3DGroup->groupTransformationsMatrix)
						).multiply(object->getTransformationsMatrix()));
				}
				// set up texture matrix
				//	TODO: check if texture is in use
				if ((renderTypes & RENDERTYPE_TEXTURES) == RENDERTYPE_TEXTURES ||
					(renderTypes & RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) == RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) {
					renderer->getTextureMatrix(context).set(_object3DGroup->textureMatricesByEntities[faceEntityIdx]);
					renderer->onUpdateTextureMatrix(context);
				}
				// draw
				renderer->drawIndexedTrianglesFromBufferObjects(context, faces, faceIdx);
				// do transformations end to shadow mapping
				if ((renderTypes & RENDERTYPE_SHADOWMAPPING) == RENDERTYPE_SHADOWMAPPING &&
					shadowMapping != nullptr) {
					shadowMapping->endObjectTransformations();
				}
			}
			// keep track of rendered faces
			faceIdx += faces;
			if (material != nullptr) {
				if (material->hasDiffuseTextureTransparency() == true && material->hasDiffuseTextureMaskedTransparency() == true) {
					renderer->enableCulling();
				}
			}
		}
	}
	// unbind buffers
	renderer->unbindBufferObjects(context);
	// restore model view matrix / view matrix
	renderer->getModelViewMatrix().set(cameraMatrix);
}

inline void Object3DVBORenderer::instancedRenderFunction(int threadIdx, void* context, InstancedRenderFunctionStruct& parameters, vector<Object3D*>& objectsNotRendered, TransparentRenderFacesPool* transparentRenderFacesPool) {
	Matrix4x4Negative matrix4x4Negative;

	Vector3 objectCamFromAxis;
	Matrix4x4 modelViewMatrixTemp;
	Matrix4x4 modelViewMatrix;

	FloatBuffer fbEffectColorMuls = bbEffectColorMuls[threadIdx]->asFloatBuffer();
	FloatBuffer fbEffectColorAdds = bbEffectColorAdds[threadIdx]->asFloatBuffer();
	FloatBuffer fbMvMatrices = bbMvMatrices[threadIdx]->asFloatBuffer();

	string materialKey;
	bool materialUpdateOnly = false;
	vector<int32_t>* boundVBOBaseIds = nullptr;
	vector<int32_t>* boundVBOTangentBitangentIds = nullptr;
	auto objectCount = objectsToRender.size();
	// issue upload matrices
	renderer->onUpdateCameraMatrix(context);
	renderer->onUpdateProjectionMatrix(context);
	// update lights
	for (auto j = 0; j < engine->lights.size(); j++) {
		engine->lights[j].update(context);
	}
	// draw objects
	for (auto objectIdx = 0; objectIdx < objectCount; objectIdx++) {
		if (threadCount > 1 && objectIdx % threadCount != threadIdx) continue;

		auto object = objectsToRender[objectIdx];
		auto _object3DGroup = object->object3dGroups[parameters.object3DGroupIdx];

		//	check transparency via effect
		if (object->effectColorMul.getAlpha() < 1.0f - Math::EPSILON ||
			object->effectColorAdd.getAlpha() < -Math::EPSILON) {
			// add to transparent render faces, if requested
			if (parameters.collectTransparentFaces == true) {
				transparentRenderFacesPool->createTransparentRenderFaces(
					(_object3DGroup->mesh->skinning == true ?
						modelViewMatrixTemp.identity() :
						modelViewMatrixTemp.set(*_object3DGroup->groupTransformationsMatrix)
					).multiply(object->getTransformationsMatrix()).multiply(parameters.cameraMatrix),
					_object3DGroup,
					parameters.faceEntityIdx,
					parameters.faceIdx
				);
			}
			// skip to next object
			continue;
		}

		// limit objects to render to INSTANCEDRENDERING_OBJECTS_MAX
		if (fbMvMatrices.getPosition() / 16 == INSTANCEDRENDERING_OBJECTS_MAX) {
			objectsNotRendered.push_back(object);
			continue;
		}

		// check if texture matrix did change
		if (_object3DGroup->textureMatricesByEntities[parameters.faceEntityIdx].equals(parameters.textureMatrix) == false) {
			objectsNotRendered.push_back(object);
			continue;
		}

		// check if shader did change
		// shader
		auto objectShader = object->getDistanceShader().length() == 0?
			object->getShader():
			objectCamFromAxis.set(object->getBoundingBoxTransformed()->getCenter()).sub(parameters.camera->getLookFrom()).computeLengthSquared() < Math::square(object->getDistanceShaderDistance())?
				object->getShader():
				object->getDistanceShader();
		if (objectShader != parameters.shader) {
			objectsNotRendered.push_back(object);
			continue;
		}

		// set up material on first object and update on succeeding
		auto materialKeyCurrent = materialKey;
		if (materialUpdateOnly == false || checkMaterialChangable(_object3DGroup, parameters.faceEntityIdx, parameters.renderTypes) == true) {
			setupMaterial(context, _object3DGroup, parameters.faceEntityIdx, parameters.renderTypes, materialUpdateOnly, materialKeyCurrent, materialKey);
			// only update material for next material calls
			if (materialUpdateOnly == false) {
				materialKey = materialKeyCurrent;
				materialUpdateOnly = true;
			}
		}

		// check if material key has not been set yet
		if (materialKey != materialKeyCurrent) {
			objectsNotRendered.push_back(object);
			continue;
		}

		// bind buffer base objects if not bound yet
		auto currentVBOBaseIds = _object3DGroup->renderer->vboBaseIds;
		if (boundVBOBaseIds == nullptr) {
			boundVBOBaseIds = currentVBOBaseIds;
			//	texture coordinates
			if (parameters.isTextureCoordinatesAvailable == true &&
				(((parameters.renderTypes & RENDERTYPE_TEXTUREARRAYS) == RENDERTYPE_TEXTUREARRAYS) ||
				((parameters.renderTypes & RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY) == RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY && parameters.material != nullptr && parameters.material->hasDiffuseTextureMaskedTransparency() == true))) {
				renderer->bindTextureCoordinatesBufferObject(context, (*currentVBOBaseIds)[3]);
			}
			// 	indices
			renderer->bindIndicesBufferObject(context, (*currentVBOBaseIds)[0]);
			// 	vertices
			renderer->bindVerticesBufferObject(context, (*currentVBOBaseIds)[1]);
			// 	normals
			if ((parameters.renderTypes & RENDERTYPE_NORMALS) == RENDERTYPE_NORMALS) {
				renderer->bindNormalsBufferObject(context, (*currentVBOBaseIds)[2]);
			}
		} else
		// check if buffers did change, then skip and render in next step
		if (boundVBOBaseIds != currentVBOBaseIds) {
			objectsNotRendered.push_back(object);
			continue;
		}
		// bind tangent, bitangend buffers
		auto currentVBOTangentBitangentIds = _object3DGroup->renderer->vboTangentBitangentIds;
		if ((parameters.renderTypes & RENDERTYPE_NORMALS) == RENDERTYPE_NORMALS &&
			renderer->isNormalMappingAvailable() == true && currentVBOTangentBitangentIds != nullptr) {
			// bind tangent, bitangend buffers if not yet done
			if (boundVBOTangentBitangentIds == nullptr) {
				// tangent
				renderer->bindTangentsBufferObject(context, (*currentVBOTangentBitangentIds)[0]);
				// bitangent
				renderer->bindBitangentsBufferObject(context, (*currentVBOTangentBitangentIds)[1]);
				//
				boundVBOTangentBitangentIds = currentVBOTangentBitangentIds;
			} else
			// check if buffers did change, then skip and render in next step
			if (currentVBOTangentBitangentIds != boundVBOTangentBitangentIds) {
				objectsNotRendered.push_back(object);
				continue;
			}
		}

		// set up local -> world transformations matrix
		modelViewMatrix.set(
			(_object3DGroup->mesh->skinning == true ?
				modelViewMatrixTemp.identity() :
				modelViewMatrixTemp.set(*_object3DGroup->groupTransformationsMatrix)
			).
				multiply(object->getTransformationsMatrix())
		);

		// set up front face
		auto objectFrontFace = matrix4x4Negative.isNegative(modelViewMatrix) == false ? renderer->FRONTFACE_CCW : renderer->FRONTFACE_CW;
		// if front face changed just render in next step
		if (objectFrontFace != parameters.frontFace) {
			objectsNotRendered.push_back(object);
			continue;
		}

		// set up effect color
		if ((parameters.renderTypes & RENDERTYPE_EFFECTCOLORS) == RENDERTYPE_EFFECTCOLORS) {
			fbEffectColorMuls.put(object->effectColorMul.getArray());
			fbEffectColorAdds.put(object->effectColorAdd.getArray());
		}

		// push mv, mvp to layouts
		fbMvMatrices.put(modelViewMatrix.getArray());
	}

	// it can happen that all faces to be rendered were transparent ones, check this and skip if feasible
	auto objectsToRenderIssue = fbMvMatrices.getPosition() / 16;
	if (objectsToRenderIssue > 0) {

		// upload model view matrices
		{
			renderer->uploadBufferObject(context, (*vboInstancedRenderingIds[threadIdx])[0], fbMvMatrices.getPosition() * sizeof(float), &fbMvMatrices);
			renderer->bindModelMatricesBufferObject(context, (*vboInstancedRenderingIds[threadIdx])[0]);
		}

		// upload effects
		if ((parameters.renderTypes & RENDERTYPE_EFFECTCOLORS) == RENDERTYPE_EFFECTCOLORS) {
			// upload effect color mul
			renderer->uploadBufferObject(context, (*vboInstancedRenderingIds[threadIdx])[1], fbEffectColorMuls.getPosition() * sizeof(float), &fbEffectColorMuls);
			renderer->bindEffectColorMulsBufferObject(context, (*vboInstancedRenderingIds[threadIdx])[1]);
			renderer->uploadBufferObject(context, (*vboInstancedRenderingIds[threadIdx])[2], fbEffectColorAdds.getPosition() * sizeof(float), &fbEffectColorAdds);
			renderer->bindEffectColorAddsBufferObject(context, (*vboInstancedRenderingIds[threadIdx])[2]);
		}

		// set up texture matrix
		//	TODO: check if texture is in use
		if ((parameters.renderTypes & RENDERTYPE_TEXTURES) == RENDERTYPE_TEXTURES ||
			(parameters.renderTypes & RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) == RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) {
			renderer->getTextureMatrix(context).set(parameters.textureMatrix);
			renderer->onUpdateTextureMatrix(context);
		}

		// draw
		renderer->drawInstancedIndexedTrianglesFromBufferObjects(context, parameters.faces, parameters.faceIdx, objectsToRenderIssue);
	}

	// unbind buffers
	renderer->unbindBufferObjects(context);
}

void Object3DVBORenderer::renderObjectsOfSameTypeInstanced(const vector<Object3D*>& objects, bool collectTransparentFaces, int32_t renderTypes)
{	// use default context
	auto context = renderer->getDefaultContext();

	//
	InstancedRenderFunctionStruct parameters;

	//
	Vector3 objectCamFromAxis;
	Matrix4x4 cameraMatrix(renderer->getModelViewMatrix());
	Matrix4x4 modelViewMatrixTemp;
	Matrix4x4 modelViewMatrix;

	//
	auto shadowMapping = engine->getShadowMapping();

	// render faces entities
	auto firstObject = objects[0];

	// all objects share the same object 3d group structure, so we just take the first one
	for (auto object3DGroupIdx = 0; object3DGroupIdx < firstObject->object3dGroups.size(); object3DGroupIdx++) {
		auto object3DGroup = firstObject->object3dGroups[object3DGroupIdx];
		// render each faces entity
		auto facesEntities = object3DGroup->group->getFacesEntities();
		auto faceIdx = 0;
		auto facesEntityIdxCount = facesEntities->size();
		for (auto faceEntityIdx = 0; faceEntityIdx < facesEntityIdxCount; faceEntityIdx++) {
			auto facesEntity = &(*facesEntities)[faceEntityIdx];
			auto isTextureCoordinatesAvailable = facesEntity->isTextureCoordinatesAvailable();
			auto faces = facesEntity->getFaces()->size();
			// material
			auto material = facesEntity->getMaterial();
			// determine if transparent
			auto transparentFacesEntity = false;
			//	via material
			if (material != nullptr) {
				if (material->hasColorTransparency() == true || material->hasTextureTransparency() == true) transparentFacesEntity = true;
				if (material->hasDiffuseTextureTransparency() == true && material->hasDiffuseTextureMaskedTransparency() == true) {
					renderer->disableCulling();
				}
			}
			// skip, if requested
			if (transparentFacesEntity == true) {
				// add to transparent render faces, if requested
				auto objectCount = objects.size();
				for (auto objectIdx = 0; objectIdx < objectCount; objectIdx++) {
					auto object = objects[objectIdx];
					auto _object3DGroup = object->object3dGroups[object3DGroupIdx];
					// set up textures
					Object3DGroup::setupTextures(renderer, object3DGroup, faceEntityIdx);
					// set up transparent render faces
					if (collectTransparentFaces == true) {
						transparentRenderFacesPool->createTransparentRenderFaces(
							(_object3DGroup->mesh->skinning == true ?
								modelViewMatrixTemp.identity() :
								modelViewMatrixTemp.set(*_object3DGroup->groupTransformationsMatrix)
							).
								multiply(object->getTransformationsMatrix()).multiply(cameraMatrix),
								object->object3dGroups[object3DGroupIdx],
								faceEntityIdx,
								faceIdx
							);
					}
				}
				// keep track of rendered faces
				faceIdx += faces;
				// skip to next entity
				continue;
			}

			// draw this faces entity for each object
			objectsToRender = objects;
			do {
				auto firstObjectToRender = objectsToRender[0];
				auto object3DGroupToRender = firstObjectToRender->object3dGroups[object3DGroupIdx];
				modelViewMatrix.set(
					(object3DGroupToRender->mesh->skinning == true ?
						modelViewMatrixTemp.identity() :
						modelViewMatrixTemp.set(*object3DGroupToRender->groupTransformationsMatrix)
					).
						multiply(firstObjectToRender->getTransformationsMatrix())
				);
				parameters.shader = firstObjectToRender->getDistanceShader().length() == 0?
					firstObjectToRender->getShader():
					objectCamFromAxis.set(firstObjectToRender->getBoundingBoxTransformed()->getCenter()).sub(parameters.camera->getLookFrom()).computeLengthSquared() < Math::square(firstObjectToRender->getDistanceShaderDistance())?
						firstObjectToRender->getShader():
						firstObjectToRender->getDistanceShader();
				parameters.renderTypes = renderTypes;
				parameters.camera = engine->getCamera();
				parameters.cameraMatrix = cameraMatrix;
				parameters.object3DGroupIdx = object3DGroupIdx;
				parameters.faceEntityIdx = faceEntityIdx;
				parameters.faces = faces;
				parameters.faceIdx = faceIdx;
				parameters.isTextureCoordinatesAvailable = isTextureCoordinatesAvailable;
				parameters.material = material;
				parameters.frontFace = matrix4x4Negative.isNegative(modelViewMatrix) == false ? renderer->FRONTFACE_CCW : renderer->FRONTFACE_CW;
				parameters.textureMatrix = object3DGroupToRender->textureMatricesByEntities[parameters.faceEntityIdx];
				parameters.collectTransparentFaces = collectTransparentFaces;

				// shader
				renderer->setFrontFace(parameters.frontFace);
				renderer->setShader(parameters.shader);
				for (auto i = 0; i < threadCount; i++) renderer->onUpdateShader(renderer->getContext(i));
				// multiple threads
				if (threadCount > 1) {
					for (auto i = 0; i < threadCount; i++) threads[i]->setParameters(parameters);
					for (auto renderThread: threads) renderThread->busy = true;
					// renderThreadWaitSemaphore.increment(threadCount);
					// mainThreadWaitSemaphore.wait(threadCount);
					for (auto renderThread: threads) while(renderThread->busy == true);
					for (auto i = 0; i < threadCount; i++) objectsNotRendered.insert(objectsNotRendered.end(), threads[i]->getObjectsNotRendered().begin(), threads[i]->getObjectsNotRendered().end());
					for (auto i = 0; i < threadCount; i++) transparentRenderFacesPool->merge(threads[i]->getTransparentRenderFacesPool());
				} else {
					// nope, single one
					instancedRenderFunction(0, context, parameters, objectsNotRendered, transparentRenderFacesPool);
				}

				// clear list of objects we did not render
				objectsToRender = objectsNotRendered;
				objectsNotRendered.clear();
			} while (objectsToRender.size() > 0);

			// keep track of rendered faces
			faceIdx += faces;
			if (material != nullptr) {
				if (material->hasDiffuseTextureTransparency() == true && material->hasDiffuseTextureMaskedTransparency() == true) {
					renderer->enableCulling();
				}
			}
		}
	}

	// reset objects to render
	objectsToRender.clear();
	objectsNotRendered.clear();

	// restore model view matrix / view matrix
	renderer->getModelViewMatrix().set(cameraMatrix);
}

void Object3DVBORenderer::setupMaterial(void* context, Object3DGroup* object3DGroup, int32_t facesEntityIdx, int32_t renderTypes, bool updateOnly, string& materialKey, const string& currentMaterialKey)
{
	auto facesEntities = object3DGroup->group->getFacesEntities();
	auto material = (*facesEntities)[facesEntityIdx].getMaterial();
	// get material or use default
	if (material == nullptr) material = Material::getDefaultMaterial();

	// material key
	materialKey = material->getId();

	// setup textures
	Object3DGroup::setupTextures(renderer, object3DGroup, facesEntityIdx);

	//
	if (updateOnly == false) {
		// apply materials
		if ((renderTypes & RENDERTYPE_MATERIALS) == RENDERTYPE_MATERIALS) {
			renderer->setMaterialAmbient(context, material->getAmbientColor().getArray());
			renderer->setMaterialDiffuse(context, material->getDiffuseColor().getArray());
			renderer->setMaterialSpecular(context, material->getSpecularColor().getArray());
			renderer->setMaterialEmission(context, material->getEmissionColor().getArray());
			renderer->setMaterialShininess(context, material->getShininess());
			renderer->setMaterialDiffuseTextureMaskedTransparency(context, material->hasDiffuseTextureMaskedTransparency());
			renderer->setMaterialDiffuseTextureMaskedTransparencyThreshold(context, material->getDiffuseTextureMaskedTransparencyThreshold());
			renderer->onUpdateMaterial(context);
		}
		if ((renderTypes & RENDERTYPE_TEXTURES) == RENDERTYPE_TEXTURES) {
			// bind specular texture
			if (renderer->isSpecularMappingAvailable() == true) {
				renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_SPECULAR);
				renderer->bindTexture(context, object3DGroup->materialSpecularTextureIdsByEntities[facesEntityIdx]);
			}
			// bind displacement texture
			if (renderer->isDisplacementMappingAvailable() == true) {
				renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_DISPLACEMENT);
				renderer->bindTexture(context, object3DGroup->materialDisplacementTextureIdsByEntities[facesEntityIdx]);
			}
			// bind normal texture
			if (renderer->isNormalMappingAvailable() == true) {
				renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_NORMAL);
				renderer->bindTexture(context, object3DGroup->materialNormalTextureIdsByEntities[facesEntityIdx]);
			}
			// switch back texture unit to diffuse unit
			renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_DIFFUSE);
		}
	}

	// bind diffuse texture
	if ((renderTypes & RENDERTYPE_TEXTURES) == RENDERTYPE_TEXTURES ||
		((renderTypes & RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) == RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY)) {
		renderer->setMaterialDiffuseTextureMaskedTransparency(context, material->hasDiffuseTextureMaskedTransparency());
		renderer->onUpdateMaterial(context);
		if ((renderTypes & RENDERTYPE_TEXTURES) == RENDERTYPE_TEXTURES ||
			material->hasDiffuseTextureMaskedTransparency() == true) {
			auto diffuseTextureId =
				object3DGroup->dynamicDiffuseTextureIdsByEntities[facesEntityIdx] != Object3DGroup::TEXTUREID_NONE ?
				object3DGroup->dynamicDiffuseTextureIdsByEntities[facesEntityIdx] :
				object3DGroup->materialDiffuseTextureIdsByEntities[facesEntityIdx];
			materialKey+= "," + to_string(diffuseTextureId);
			if (updateOnly == false || currentMaterialKey.empty() == true) {
				renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_DIFFUSE);
				renderer->bindTexture(context, diffuseTextureId);
			}
		}
	}
}

void Object3DVBORenderer::clearMaterial(void* context)
{
	// TODO: optimize me! We do not need always to clear material
	// unbind diffuse texture
	renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_DIFFUSE);
	renderer->bindTexture(context, renderer->ID_NONE);
	// unbind specular texture
	if (renderer->isSpecularMappingAvailable() == true) {
		renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_SPECULAR);
		renderer->bindTexture(context, renderer->ID_NONE);
	}
	// unbind displacement texture
	if (renderer->isDisplacementMappingAvailable() == true) {
		renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_DISPLACEMENT);
		renderer->bindTexture(context, renderer->ID_NONE);
	}
	// unbind normal texture
	if (renderer->isNormalMappingAvailable()) {
		renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_NORMAL);
		renderer->bindTexture(context, renderer->ID_NONE);
	}
	// set diffuse texture unit
	renderer->setTextureUnit(context, LightingShaderConstants::TEXTUREUNIT_DIFFUSE);
}

void Object3DVBORenderer::render(const vector<PointsParticleSystem*>& visiblePses)
{
	// TODO: Move me into own class
	// TODO: check me performance wise again
	if (visiblePses.size() == 0) return;

	// use default context
	auto context = renderer->getDefaultContext();

	// switch back to texture unit 0, TODO: check where its set to another value but not set back
	renderer->setTextureUnit(context, 0);

	// merge ppses and sort them
	for (auto i = 0; i < visiblePses.size(); i++) {
		PointsParticleSystemInternal* ppse = visiblePses[i];
		pseTransparentRenderPointsPool->merge(ppse->getRenderPointsPool());
	}
	if (pseTransparentRenderPointsPool->getTransparentRenderPoints().size() == 0) return;
	pseTransparentRenderPointsPool->sort();

	// store model view matrix
	Matrix4x4 modelViewMatrix;
	modelViewMatrix.set(renderer->getModelViewMatrix());

	// set up renderer state
	renderer->enableBlending();
	// 	model view matrix
	renderer->getModelViewMatrix().identity();
	renderer->onUpdateModelViewMatrix(context);

	// render
	PointsParticleSystem* currentPpse = (PointsParticleSystem*)pseTransparentRenderPointsPool->getTransparentRenderPoints()[0].cookie;
	for (auto& point: pseTransparentRenderPointsPool->getTransparentRenderPoints()) {
		if (point.acquired == false) break;
		if (point.cookie != (void*)currentPpse) {
			// issue rendering
			renderer->setEffectColorAdd(context, currentPpse->getEffectColorAdd().getArray());
			renderer->setEffectColorMul(context, currentPpse->getEffectColorMul().getArray());
			renderer->onUpdateEffect(context);
			// TODO: maybe use onBindTexture() or onUpdatePointSize()
			engine->getParticlesShader()->setParameters(context, currentPpse->getTextureId(), currentPpse->getPointSize());
			// render, clear
			psePointBatchVBORenderer->render(context);
			psePointBatchVBORenderer->clear();
			//
			currentPpse = (PointsParticleSystem*)point.cookie;
		}
		psePointBatchVBORenderer->addPoint(point);
	}

	if (psePointBatchVBORenderer->hasPoints() == true) {
		// issue rendering
		renderer->setEffectColorAdd(context, currentPpse->getEffectColorAdd().getArray());
		renderer->setEffectColorMul(context, currentPpse->getEffectColorMul().getArray());
		renderer->onUpdateEffect(context);
		// TODO: maybe use onBindTexture() or onUpdatePointSize()
		engine->getParticlesShader()->setParameters(context, currentPpse->getTextureId(), currentPpse->getPointSize());
		// render, clear
		psePointBatchVBORenderer->render(context);
		psePointBatchVBORenderer->clear();
	}

	// done
	pseTransparentRenderPointsPool->reset();

	// unbind texture
	renderer->bindTexture(context, renderer->ID_NONE);
	// TODO: before render sort all pps by distance to camera and render them in correct order
	// unset renderer state
	renderer->disableBlending();
	// restore renderer state
	renderer->unbindBufferObjects(context);
	renderer->getModelViewMatrix().set(modelViewMatrix);
}
