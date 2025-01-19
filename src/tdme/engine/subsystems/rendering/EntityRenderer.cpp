#include <tdme/engine/subsystems/rendering/EntityRenderer.h>

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/PBRMaterialProperties.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/lines/LinesShader.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/particlesystem/FogParticleSystemInternal.h>
#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>
#include <tdme/engine/subsystems/particlesystem/ParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/PointsParticleSystemInternal.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/subsystems/rendering/BatchRendererPoints.h>
#include <tdme/engine/subsystems/rendering/BatchRendererTriangles.h>
#include <tdme/engine/subsystems/rendering/EntityRenderer_InstancedRenderFunctionParameters.h>
#include <tdme/engine/subsystems/rendering/EntityRenderer_TransparentRenderFacesGroupPool.h>
#include <tdme/engine/subsystems/rendering/ObjectBase.h>
#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>
#include <tdme/engine/subsystems/rendering/ObjectNode.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeRenderer.h>
#include <tdme/engine/subsystems/rendering/RenderTransparentRenderPointsPool.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFace.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFacesGroup.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFacesPool.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPointsPool.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityHierarchy.h>
#include <tdme/engine/EnvironmentMapping.h>
#include <tdme/engine/FogParticleSystem.h>
#include <tdme/engine/Lines.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/PointsParticleSystem.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/FloatBuffer.h>
#include <tdme/utilities/Pool.h>

using std::find;
using std::make_unique;
using std::map;
using std::set;
using std::sort;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::Texture;
using tdme::engine::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::PBRMaterialProperties;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::lines::LinesShader;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::particlesystem::FogParticleSystemInternal;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::particlesystem::PointsParticleSystemInternal;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::rendering::BatchRendererPoints;
using tdme::engine::subsystems::rendering::BatchRendererTriangles;
using tdme::engine::subsystems::rendering::EntityRenderer;
using tdme::engine::subsystems::rendering::EntityRenderer_InstancedRenderFunctionParameters;
using tdme::engine::subsystems::rendering::EntityRenderer_TransparentRenderFacesGroupPool;
using tdme::engine::subsystems::rendering::ObjectBase;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::engine::subsystems::rendering::ObjectNodeRenderer;
using tdme::engine::subsystems::rendering::RenderTransparentRenderPointsPool;
using tdme::engine::subsystems::rendering::TransparentRenderFace;
using tdme::engine::subsystems::rendering::TransparentRenderFacesGroup;
using tdme::engine::subsystems::rendering::TransparentRenderFacesPool;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EntityHierarchy;
using tdme::engine::EnvironmentMapping;
using tdme::engine::FogParticleSystem;
using tdme::engine::Lines;
using tdme::engine::Object;
using tdme::engine::PointsParticleSystem;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::os::threading::Thread;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::FloatBuffer;
using tdme::utilities::Pool;

constexpr int32_t EntityRenderer::BATCHRENDERER_MAX;
constexpr int32_t EntityRenderer::INSTANCEDRENDERING_OBJECTS_MAX;

EntityRenderer::EntityRenderer(Engine* engine, RendererBackend* rendererBackend) {
	this->engine = engine;
	this->rendererBackend = rendererBackend;
	transparentRenderFacesGroupPool = make_unique<EntityRenderer_TransparentRenderFacesGroupPool>();
	transparentRenderFacesPool = make_unique<TransparentRenderFacesPool>();
	renderTransparentRenderPointsPool = make_unique<RenderTransparentRenderPointsPool>(65535);
	psePointBatchRenderer = make_unique<BatchRendererPoints>(rendererBackend, 0);
	threadCount = rendererBackend->isSupportingMultithreadedRendering() == true?Engine::getThreadCount():1;
	contexts.resize(threadCount);
	if (this->rendererBackend->isInstancedRenderingAvailable() == true) {
		for (auto& contextIdx: contexts) {
			contextIdx.bbEffectColorMuls = unique_ptr<ByteBuffer>(ByteBuffer::allocate(4 * sizeof(float) * INSTANCEDRENDERING_OBJECTS_MAX));
			contextIdx.bbEffectColorAdds = unique_ptr<ByteBuffer>(ByteBuffer::allocate(4 * sizeof(float) * INSTANCEDRENDERING_OBJECTS_MAX));
			contextIdx.bbMvMatrices = unique_ptr<ByteBuffer>(ByteBuffer::allocate(16 * sizeof(float) * INSTANCEDRENDERING_OBJECTS_MAX));
		}
	}
}

EntityRenderer::~EntityRenderer() {
}

void EntityRenderer::initialize()
{
	psePointBatchRenderer->initialize();
	for (auto i = 0; i < threadCount; i++) {
		auto created = false;
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO("tdme.objectrenderer.instancedrendering." + to_string(i), 3, false, false, created);
		contexts[i].vboInstancedRenderingIds = vboManaged->getVBOIds();
	}
}

void EntityRenderer::dispose()
{
	// dispose VBOs
	for (auto i = 0; i < threadCount; i++) {
		Engine::getInstance()->getVBOManager()->removeVBO("tdme.objectrenderer.instancedrendering." + to_string(i));
	}
	// dispose batch vbo renderer
	for (const auto& batchRenderer: trianglesBatchRenderers) {
		batchRenderer->dispose();
		batchRenderer->release();
	}
	psePointBatchRenderer->dispose();
}

BatchRendererTriangles* EntityRenderer::acquireTrianglesBatchRenderer()
{
	// check for free batch vbo renderer
	auto i = 0;
	for (const auto& batchRenderer: trianglesBatchRenderers) {
		if (batchRenderer->acquire()) return batchRenderer.get();
		i++;
	}
	// try to add one
	if (i < BATCHRENDERER_MAX) {
		trianglesBatchRenderers.push_back(make_unique<BatchRendererTriangles>(rendererBackend, i));
		const auto& batchRenderer = trianglesBatchRenderers[trianglesBatchRenderers.size() - 1];
		batchRenderer->initialize();
		if (batchRenderer->acquire()) return batchRenderer.get();

	}
	Console::printLine(string("EntityRenderer::acquireTrianglesBatchRenderer()::failed"));
	// nope
	return nullptr;
}

void EntityRenderer::reset()
{
}

void EntityRenderer::render(Entity::RenderPass renderPass, const vector<Object*>& objects, bool renderTransparentFaces, int32_t renderTypes)
{
	if (rendererBackend->isSupportingMultithreadedRendering() == false) {
		renderFunction(0, renderPass, objects, objectsByModels, renderTransparentFaces, renderTypes, transparentRenderFacesPool.get());
	} else {
		auto elementsIssued = 0;
		auto queueElement = Engine::engineThreadQueueElementPool.allocate();
		queueElement->type = Engine::EngineThreadQueueElement::TYPE_RENDERING;
		queueElement->engine = engine;
		queueElement->rendering.renderPass = renderPass;
		queueElement->rendering.collectTransparentFaces = renderTransparentFaces;
		queueElement->rendering.renderTypes = renderTypes;
		for (auto i = 0; i < objects.size(); i++) {
			queueElement->objects.push_back(objects[i]);
			if (queueElement->objects.size() == Engine::ENGINETHREADSQUEUE_RENDER_DISPATCH_COUNT) {
				auto queueElementToSubmit = queueElement;
				queueElement = Engine::engineThreadQueueElementPool.allocate();
				queueElement->type = Engine::EngineThreadQueueElement::TYPE_RENDERING;
				queueElement->engine = engine;
				queueElement->rendering.renderPass = renderPass;
				queueElement->rendering.collectTransparentFaces = renderTransparentFaces;
				queueElement->rendering.renderTypes = renderTypes;
				elementsIssued++;
				engine->engineThreadsQueue->addElement(queueElementToSubmit, false);
			}
		}
		if (queueElement->objects.empty() == false) {
			elementsIssued++;
			engine->engineThreadsQueue->addElement(queueElement, false);
		}

		// wait until all elements have been processed
		while (true == true) {
			auto elementsProcessed = 0;
			for (const auto& engineThread: Engine::engineThreads) elementsProcessed+= engineThread->getProcessedElements();
			if (elementsProcessed == elementsIssued) {
				for (const auto& engineThread: Engine::engineThreads) engineThread->resetProcessedElements();
				break;
			}
		}

		//
		Engine::engineThreadQueueElementPool.reset();

		//
		for (const auto& engineThread: Engine::engineThreads) {
			transparentRenderFacesPool->merge(engineThread->transparentRenderFacesPool.get());
			engineThread->transparentRenderFacesPool->reset();
		}
	}
}

void EntityRenderer::renderTransparentFaces() {
	// use default context
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;
	// render transparent render faces if any exist
	auto& transparentRenderFaces = transparentRenderFacesPool->getTransparentRenderFaces();
	if (transparentRenderFaces.size() > 0) {
		// sort transparent render faces from far to near
		sort(
			transparentRenderFaces.begin(),
			transparentRenderFaces.end(),
			[](const TransparentRenderFace* face1, const TransparentRenderFace* face2) {
				return face1->distanceFromCamera > face2->distanceFromCamera;
			}
		);
		// second render pass, draw color buffer for transparent objects
		// 	set up blending, but no culling and no depth buffer
		//	TODO: enabling depth buffer let shadow disappear
		//rendererBackend->disableDepthBufferWriting();  // TODO: a.drewke, verify that this works ok in all cases?
		rendererBackend->disableCulling(contextIdx);
		rendererBackend->enableBlending();
		// disable foliage animation
		// reset shader
		// TODO: shader parameters
		rendererBackend->setShader(contextIdx, string());
		rendererBackend->onUpdateShader(contextIdx);
		// have identity texture matrix
		rendererBackend->getTextureMatrix(contextIdx).identity();
		rendererBackend->onUpdateTextureMatrix(contextIdx);
		// actually this should not make any difference as culling is disabled
		// but having a fixed value is not a bad idea except that it is a renderer call
		// TODO: confirm this
		rendererBackend->setFrontFace(contextIdx, rendererBackend->FRONTFACE_CCW);
		for (auto transparentRenderFace: transparentRenderFaces) {
			// do we have any faces yet?
			if (nodeTransparentRenderFaces.size() == 0) {
				// nope, so add this one
				nodeTransparentRenderFaces.push_back(transparentRenderFace);
			} else
			// do we have more than face already?
			if (nodeTransparentRenderFaces.size() > 0) {
				// check if we have more of first type
				if (nodeTransparentRenderFaces[0]->objectNode == transparentRenderFace->objectNode) {
					// yep, we can add this one
					nodeTransparentRenderFaces.push_back(transparentRenderFace);
				} else {
					// no, render nodeed faces
					prepareTransparentFaces(nodeTransparentRenderFaces);
					// reset
					nodeTransparentRenderFaces.clear();
					// add current face
					nodeTransparentRenderFaces.push_back(transparentRenderFace);
				}
			}
		}
		// 	check if there are any left overs
		if (nodeTransparentRenderFaces.size() > 0) {
			prepareTransparentFaces(nodeTransparentRenderFaces);
			nodeTransparentRenderFaces.clear();
		}
		// render transparent faces nodes
		renderTransparentFacesGroups(contextIdx);
		//	no blending, but culling and depth buffer
		rendererBackend->disableBlending();
		rendererBackend->enableCulling(contextIdx);
		//rendererBackend->enableDepthBufferWriting(); // TODO: a.drewke, verify that this works ok in all cases?
		// done!
	}

	// clear transparent render faces data
	transparentRenderFacesPool->reset();
	releaseTransparentFacesGroups();
}

void EntityRenderer::prepareTransparentFaces(const vector<TransparentRenderFace*>& transparentRenderFaces)
{
	// all those faces should share the object and object node, ...
	auto objectNode = transparentRenderFaces[0]->objectNode;
	auto object = static_cast<Object*>(objectNode->object);
	// model view matrix to be used with given transparent render faces
	Matrix4x4 modelViewMatrix;
	if (objectNode->mesh->skinning == true) {
		modelViewMatrix.identity();
	} else {
		modelViewMatrix.set(*objectNode->nodeTransformMatrix).multiply(object->getTransformMatrix());
	}
	//
	auto model = objectNode->object->getModel();
	const auto& facesEntities = objectNode->node->getFacesEntities();
	const FacesEntity* facesEntity = nullptr;
	// attributes we collect for a transparent render face node
	const auto& effectColorAdd = object->getEffectColorAdd();
	const auto& effectColorMul = object->getEffectColorMul();
	const Material* material = nullptr;
	auto textureCoordinates = false;
	// render transparent faces
	for (auto i = 0; i < transparentRenderFaces.size(); i++) {
		auto transparentRenderFace = transparentRenderFaces[i];
		auto facesEntityIdx = transparentRenderFace->facesEntityIdx;
		// determine if faces entity and so material did switch between last face and current face
		if (facesEntity != &facesEntities[facesEntityIdx]) {
			facesEntity = &facesEntities[facesEntityIdx];
			material = facesEntity->getMaterial();
		}
		textureCoordinates = facesEntity->isTextureCoordinatesAvailable();
		// create node key
		auto transparentRenderFacesNodeKey = TransparentRenderFacesGroup::createKey(model, objectNode, facesEntityIdx, effectColorAdd, effectColorMul, material, textureCoordinates, object->getUniqueShaderId());
		// get node
		TransparentRenderFacesGroup* trfNode = nullptr;
		auto trfNodeIt = transparentRenderFacesGroups.find(transparentRenderFacesNodeKey);
		if (trfNodeIt != transparentRenderFacesGroups.end()) {
			trfNode = trfNodeIt->second;
		}
		if (trfNode == nullptr) {
			// we do not have the node, create node
			trfNode = transparentRenderFacesGroupPool->allocate();
			trfNode->set(this, model, objectNode, facesEntityIdx, effectColorAdd, effectColorMul, material, textureCoordinates, object->getShader());
			transparentRenderFacesGroups[transparentRenderFacesNodeKey] = trfNode;
		}
		const auto& textureCoordinates = transparentRenderFace->objectNode->mesh->node->getTextureCoordinates();
		for (auto vertexIdx = 0; vertexIdx < 3; vertexIdx++) {
			auto arrayIdx = transparentRenderFace->objectNode->mesh->indices[transparentRenderFace->faceIdx * 3 + vertexIdx];
			trfNode->addVertex(
				modelViewMatrix.multiply((*transparentRenderFace->objectNode->mesh->vertices)[arrayIdx]),
				modelViewMatrix.multiplyNoTranslation((*transparentRenderFace->objectNode->mesh->normals)[arrayIdx]),
				transparentRenderFace->objectNode->textureMatricesByEntities[facesEntityIdx].multiply(
					textureCoordinates.size() > 0?
						Vector2(textureCoordinates[arrayIdx].getArray()):
						Vector2(0.0f, 0.0f)
				)
			);
		}
	}
}

void EntityRenderer::renderTransparentFacesGroups(int contextIdx) {
	for (const auto& [id, transparentRenderFacesGroup]: transparentRenderFacesGroups) {
		transparentRenderFacesGroup->render(engine, rendererBackend, contextIdx);
	}
}

void EntityRenderer::releaseTransparentFacesGroups()
{
	for (const auto& [id, transparentRenderFacesGroup]: transparentRenderFacesGroups) {
		transparentRenderFacesGroupPool->release(transparentRenderFacesGroup);
	}
	transparentRenderFacesGroups.clear();
}

void EntityRenderer::renderObjectsOfSameTypeNonInstanced(const vector<Object*>& objects, bool collectTransparentFaces, int32_t renderTypes) {
	Vector3 objectCamFromAxis;
	auto camera = engine->getCamera();

	// use default context
	auto& objectRenderContext = contexts[0];
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;

	//
	auto shadowMapping = engine->getShadowMapping();
	Matrix4x4 modelViewMatrix;
	Matrix4x4 cameraMatrix;
	cameraMatrix.set(rendererBackend->getModelViewMatrix());
	// render faces entities
	auto currentFrontFace = -1;
	string shaderParametersHash;
	auto firstObject = objects[0];
	// all objects share the same object node structure, so we just take the first one
	vector<int32_t>* boundVBOBaseIds = nullptr;
	vector<int32_t>* boundVBOTangentBitangentIds = nullptr;
	vector<int32_t>* boundVBOOrigins = nullptr;
	auto currentLODLevel = -1;
	int32_t boundEnvironmentMappingCubeMapTextureId = -1;
	Vector3 boundEnvironmentMappingCubeMapPosition;
	for (auto objectNodeIdx = 0; objectNodeIdx < firstObject->objectNodes.size(); objectNodeIdx++) {
		auto objectNode = firstObject->objectNodes[objectNodeIdx];
		// render each faces entity
		const auto& facesEntities = objectNode->node->getFacesEntities();
		auto faceIdx = 0;
		auto facesEntityIdxCount = facesEntities.size();
		for (auto faceEntityIdx = 0; faceEntityIdx < facesEntityIdxCount; faceEntityIdx++) {
			auto facesEntity = &facesEntities[faceEntityIdx];
			auto isTextureCoordinatesAvailable = facesEntity->isTextureCoordinatesAvailable();
			auto faces = facesEntity->getFaces().size() * firstObject->instances;
			auto facesToRender = facesEntity->getFaces().size() * firstObject->enabledInstances;
			// material
			auto material = facesEntity->getMaterial();
			auto specularMaterialProperties = material != nullptr?material->getSpecularMaterialProperties():nullptr;
			// determine if transparent
			auto transparentFacesEntity = false;
			//	via material
			if (specularMaterialProperties != nullptr) {
				if (specularMaterialProperties->hasColorTransparency() == true || specularMaterialProperties->hasTextureTransparency() == true) transparentFacesEntity = true;
				if (material->isDoubleSided() == true ||
					(specularMaterialProperties->hasDiffuseTextureTransparency() == true && specularMaterialProperties->hasDiffuseTextureMaskedTransparency() == true)) {
					rendererBackend->disableCulling(contextIdx);
				}
			}
			// skip, if requested
			if (transparentFacesEntity == true) {
				// add to transparent render faces, if requested
				auto objectCount = objects.size();
				for (auto objectIdx = 0; objectIdx < objectCount; objectIdx++) {
					auto object = objects[objectIdx];
					auto _objectNode = object->objectNodes[objectNodeIdx];
					// set up textures
					ObjectNode::setupTextures(rendererBackend, contextIdx, objectNode, faceEntityIdx);
					// set up transparent render faces
					if (collectTransparentFaces == true) {
						transparentRenderFacesPool->createTransparentRenderFaces(
							(_objectNode->mesh->skinning == true?
								modelViewMatrix.identity():
								modelViewMatrix.set(*_objectNode->nodeTransformMatrix).multiply(object->getTransformMatrix())
							).multiply(cameraMatrix),
							object->objectNodes[objectNodeIdx],
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
				auto _objectNode = object->objectNodes[objectNodeIdx];
				//	check transparency via effect
				if (object->effectColorMul.getAlpha() < 1.0f - Math::EPSILON ||
					object->effectColorAdd.getAlpha() < -Math::EPSILON) {
					// add to transparent render faces, if requested
					if (collectTransparentFaces == true) {
						transparentRenderFacesPool->createTransparentRenderFaces(
							(_objectNode->mesh->skinning == true ?
								modelViewMatrix.identity() :
								modelViewMatrix.set(*_objectNode->nodeTransformMatrix).multiply(object->getTransformMatrix())
							).multiply(cameraMatrix),
							_objectNode,
							faceEntityIdx,
							faceIdx
						);
					}
					// skip to next object
					continue;
				}

				// shader
				// TODO: shader parameters
				if (rendererBackend->getShader(contextIdx) != object->getShader()) {
					rendererBackend->setShader(contextIdx, object->getShader());
					rendererBackend->onUpdateShader(contextIdx);
					// update lights
					for (auto j = 0; j < engine->lights.size(); j++) engine->lights[j]->update(contextIdx);
					materialUpdateOnly = false;
				}
				// set up material on first object
				string materialKey;
				if (materialUpdateOnly == false || checkMaterialChangable(_objectNode, faceEntityIdx, renderTypes) == true) {
					setupMaterial(contextIdx, _objectNode, faceEntityIdx, renderTypes, materialUpdateOnly, materialKey);
					// only update materials for next calls
					materialUpdateOnly = true;
				}
				// shader parameters
				if (shaderParametersHash.empty() == true || shaderParametersHash != rendererBackend->getShaderParameters(contextIdx).getShaderParametersHash()) {
					rendererBackend->setShaderParameters(contextIdx, object->shaderParameters);
					rendererBackend->onUpdateShaderParameters(contextIdx);
					shaderParametersHash = rendererBackend->getShaderParameters(contextIdx).getShaderParametersHash();
				}
				// bind buffer base objects if not bound yet
				auto currentVBOBaseIds = _objectNode->rendererBackend->vboBaseIds;
				if (boundVBOBaseIds != currentVBOBaseIds) {
					boundVBOBaseIds = currentVBOBaseIds;
					//	texture coordinates
					if (isTextureCoordinatesAvailable == true &&
						(((renderTypes & RENDERTYPE_TEXTUREARRAYS) == RENDERTYPE_TEXTUREARRAYS) ||
						((renderTypes & RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY) == RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY && specularMaterialProperties != nullptr && specularMaterialProperties->hasDiffuseTextureMaskedTransparency() == true))) {
						rendererBackend->bindTextureCoordinatesBufferObject(contextIdx, (*currentVBOBaseIds)[3]);
					}
					// 	indices
					rendererBackend->bindIndicesBufferObject(contextIdx, (*currentVBOBaseIds)[0]);
					// 	vertices
					rendererBackend->bindVerticesBufferObject(contextIdx, (*currentVBOBaseIds)[1]);
					// 	normals
					if ((renderTypes & RENDERTYPE_NORMALS) == RENDERTYPE_NORMALS) rendererBackend->bindNormalsBufferObject(contextIdx, (*currentVBOBaseIds)[2]);
				}
				auto currentVBOLods = _objectNode->rendererBackend->vboLods;
				if (currentVBOLods != nullptr) {
					auto distanceSquared = objectCamFromAxis.set(object->getWorldBoundingBox()->computeClosestPointInBoundingBox(camera->getLookFrom())).sub(camera->getLookFrom()).computeLengthSquared();
					// index buffer
					auto lodLevel = 0;
					if (currentVBOLods->size() >= 3 && distanceSquared >= Math::square(_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD3Distance())) {
						lodLevel = 3;
					} else
					if (currentVBOLods->size() >= 2 && distanceSquared >= Math::square(_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD2Distance())) {
						lodLevel = 2;
					} else
					if (currentVBOLods->size() >= 1 && distanceSquared >= Math::square(_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD1Distance())) {
						lodLevel = 1;
					}
					if (lodLevel == 0) {
						rendererBackend->bindIndicesBufferObject(contextIdx, (*currentVBOBaseIds)[0]);
					} else {
						rendererBackend->bindIndicesBufferObject(contextIdx, (*currentVBOLods)[lodLevel - 1]);
						switch(lodLevel) {
							case 3:
								faces = (_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD3Indices().size() / 3) * firstObject->instances;
								facesToRender = (_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD3Indices().size() / 3) * firstObject->enabledInstances;
								break;
							case 2:
								faces = (_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD2Indices().size() / 3) * firstObject->instances;
								facesToRender = (_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD2Indices().size() / 3) * firstObject->enabledInstances;
								break;
							case 1:
								faces = (_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD1Indices().size() / 3) * firstObject->instances;
								facesToRender = (_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD1Indices().size() / 3) * firstObject->enabledInstances;
								break;
							default: break;
						}
					}
					currentLODLevel = lodLevel;
				}
				// bind tangent, bitangend buffers if not yet bound
				auto currentVBONormalMappingIds = _objectNode->rendererBackend->vboNormalMappingIds;
				if ((renderTypes & RENDERTYPE_NORMALS) == RENDERTYPE_NORMALS &&
					rendererBackend->isNormalMappingAvailable() && currentVBONormalMappingIds != nullptr && currentVBONormalMappingIds != boundVBOTangentBitangentIds) {
					// tangent
					rendererBackend->bindTangentsBufferObject(contextIdx, (*currentVBONormalMappingIds)[0]);
					// bitangent
					rendererBackend->bindBitangentsBufferObject(contextIdx, (*currentVBONormalMappingIds)[1]);
				}
				// bind render node object origins
				auto currentVBOOrigins = _objectNode->rendererBackend->vboOrigins;
				if (currentVBOOrigins != nullptr && currentVBOOrigins != boundVBOOrigins) {
					rendererBackend->bindOriginsBufferObject(contextIdx, (*currentVBOOrigins)[0]);
				}
				// set up local -> world transform matrix
				rendererBackend->getModelViewMatrix().set(
					_objectNode->mesh->skinning == true?
						modelViewMatrix.identity():
						modelViewMatrix.set(*_objectNode->nodeTransformMatrix).multiply(object->getTransformMatrix())
				);
				rendererBackend->onUpdateModelViewMatrix(contextIdx);
				// set up front face
				auto objectFrontFace = objectRenderContext.rightHandedMatrix.isRightHanded(rendererBackend->getModelViewMatrix()) == false ? rendererBackend->FRONTFACE_CCW : rendererBackend->FRONTFACE_CW;
				if (objectFrontFace != currentFrontFace) {
					rendererBackend->setFrontFace(contextIdx, objectFrontFace);
					currentFrontFace = objectFrontFace;
				}
				// set up effect color
				if ((renderTypes & RENDERTYPE_EFFECTCOLORS) == RENDERTYPE_EFFECTCOLORS) {
					rendererBackend->getEffectColorMul(contextIdx) = object->effectColorMul.getArray();
					rendererBackend->getEffectColorAdd(contextIdx) = object->effectColorAdd.getArray();
					rendererBackend->onUpdateEffect(contextIdx);
				}
				// do transform start to shadow mapping
				if ((renderTypes & RENDERTYPE_SHADOWMAPPING) == RENDERTYPE_SHADOWMAPPING &&
					shadowMapping != nullptr) {
					shadowMapping->startObjectTransform(
						contextIdx,
						_objectNode->mesh->skinning == true ?
							modelViewMatrix.identity() :
							modelViewMatrix.set(*_objectNode->nodeTransformMatrix).multiply(object->getTransformMatrix())
					);
				}
				// set up texture matrix
				//	TODO: check if texture is in use
				if ((renderTypes & RENDERTYPE_TEXTURES) == RENDERTYPE_TEXTURES ||
					(renderTypes & RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) == RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) {
					rendererBackend->getTextureMatrix(contextIdx).set(_objectNode->textureMatricesByEntities[faceEntityIdx]);
					rendererBackend->onUpdateTextureMatrix(contextIdx);
				}
				EnvironmentMapping* environmentMappingEntity = nullptr;
				// reflection source
				if (object->getReflectionEnvironmentMappingId().empty() == false) {
					auto environmentMappingEntityCandidate = engine->getEntity(object->getReflectionEnvironmentMappingId());
					if (environmentMappingEntityCandidate != nullptr) {
						if (environmentMappingEntityCandidate->getEntityType() == Entity::ENTITYTYPE_ENVIRONMENTMAPPING) {
							environmentMappingEntity = static_cast<EnvironmentMapping*>(environmentMappingEntityCandidate);
						} else
						if (environmentMappingEntityCandidate->getEntityType() == Entity::ENTITYTYPE_ENTITYHIERARCHY) {
							auto entityHierarchyEnvironmentMappingEntity = static_cast<EntityHierarchy*>(environmentMappingEntityCandidate)->getEntityByType(Entity::ENTITYTYPE_ENVIRONMENTMAPPING);
							if (entityHierarchyEnvironmentMappingEntity != nullptr) environmentMappingEntity = static_cast<EnvironmentMapping*>(entityHierarchyEnvironmentMappingEntity);
						}
					}
					if (environmentMappingEntity != nullptr) {
						Vector3 environmentMappingTranslation;
						object->getTransformMatrix().getTranslation(environmentMappingTranslation);
						auto environmentMappingCubeMapTextureId = environmentMappingEntity->getCubeMapTextureId();
						Vector3 environmentMappingCubeMapPosition = object->hasReflectionEnvironmentMappingPosition() == true?object->getReflectionEnvironmentMappingPosition():environmentMappingTranslation;
						if (environmentMappingCubeMapTextureId != boundEnvironmentMappingCubeMapTextureId || environmentMappingCubeMapPosition.equals(boundEnvironmentMappingCubeMapPosition) == false) {
							boundEnvironmentMappingCubeMapTextureId = environmentMappingCubeMapTextureId;
							boundEnvironmentMappingCubeMapPosition = environmentMappingCubeMapPosition;
							rendererBackend->setEnvironmentMappingCubeMapPosition(contextIdx, environmentMappingCubeMapPosition.getArray());
							rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_ENVIRONMENT);
							rendererBackend->bindCubeMapTexture(contextIdx, environmentMappingCubeMapTextureId);
							rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE);
						}
					}
				}
				if (environmentMappingEntity == nullptr && boundEnvironmentMappingCubeMapTextureId != -1) {
					rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_ENVIRONMENT);
					rendererBackend->bindCubeMapTexture(contextIdx, rendererBackend->ID_NONE);
					rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE);
					boundEnvironmentMappingCubeMapTextureId = -1;
				}
				// draw
				rendererBackend->drawIndexedTrianglesFromBufferObjects(contextIdx, facesToRender, faceIdx);
				// do transform end to shadow mapping
				if ((renderTypes & RENDERTYPE_SHADOWMAPPING) == RENDERTYPE_SHADOWMAPPING &&
					shadowMapping != nullptr) {
					shadowMapping->endObjectTransform();
				}
			}
			// keep track of rendered faces
			faceIdx += faces;
			if (specularMaterialProperties != nullptr) {
				if (material->isDoubleSided() == true ||
					(specularMaterialProperties->hasDiffuseTextureTransparency() == true && specularMaterialProperties->hasDiffuseTextureMaskedTransparency() == true)) {
					rendererBackend->enableCulling(contextIdx);
				}
			}
		}
	}
	// unbind buffers
	rendererBackend->unbindBufferObjects(contextIdx);
	// restore model view matrix / view matrix
	rendererBackend->getModelViewMatrix().set(cameraMatrix);
}

void EntityRenderer::renderObjectsOfSameTypeInstanced(int threadIdx, const vector<Object*>& objects, bool collectTransparentFaces, int32_t renderTypes, TransparentRenderFacesPool* transparentRenderFacesPool)
{
	// contexts
	auto& objectRenderContext = contexts[threadIdx];
	auto contextIdx = threadIdx;

	//
	RightHandedMatrix4x4 rightHandedMatrix;

	//
	auto cameraMatrix = rendererBackend->getCameraMatrix();
	Vector3 objectCamFromAxis;
	Matrix4x4 modelViewMatrixTemp;
	Matrix4x4 modelViewMatrix;

	//
	auto camera = engine->camera.get();
	auto frontFace = -1;
	auto cullingMode = 1;

	// render faces entities
	auto firstObject = objects[0];

	// all objects share the same object node structure, so we just take the first one
	for (auto objectNodeIdx = 0; objectNodeIdx < firstObject->objectNodes.size(); objectNodeIdx++) {
		auto objectNode = firstObject->objectNodes[objectNodeIdx];
		// render each faces entity
		const auto& facesEntities = objectNode->node->getFacesEntities();
		auto faceIdx = 0;
		auto facesEntityIdxCount = facesEntities.size();
		for (auto faceEntityIdx = 0; faceEntityIdx < facesEntityIdxCount; faceEntityIdx++) {
			auto facesEntity = &facesEntities[faceEntityIdx];
			auto isTextureCoordinatesAvailable = facesEntity->isTextureCoordinatesAvailable();
			auto faces = facesEntity->getFaces().size() * firstObject->instances;
			auto facesToRender = facesEntity->getFaces().size() * firstObject->enabledInstances;
			// material
			auto material = facesEntity->getMaterial();
			auto specularMaterialProperties = material != nullptr?material->getSpecularMaterialProperties():nullptr;
			// determine if transparent
			auto transparentFacesEntity = false;
			//	via material
			if (specularMaterialProperties != nullptr) {
				if (specularMaterialProperties->hasColorTransparency() == true || specularMaterialProperties->hasTextureTransparency() == true) transparentFacesEntity = true;

				// skip, if requested
				if (transparentFacesEntity == true) {
					// add to transparent render faces, if requested
					auto objectCount = objects.size();
					for (auto objectIdx = 0; objectIdx < objectCount; objectIdx++) {
						auto object = objects[objectIdx];
						auto _objectNode = object->objectNodes[objectNodeIdx];
						// set up textures
						ObjectNode::setupTextures(rendererBackend, contextIdx, objectNode, faceEntityIdx);
						// set up transparent render faces
						if (collectTransparentFaces == true) {
							transparentRenderFacesPool->createTransparentRenderFaces(
								(_objectNode->mesh->skinning == true?
									modelViewMatrixTemp.identity() :
									modelViewMatrixTemp.set(*_objectNode->nodeTransformMatrix).multiply(object->getTransformMatrix())
								).multiply(cameraMatrix),
								object->objectNodes[objectNodeIdx],
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

				if (material->isDoubleSided() == true ||
					(specularMaterialProperties->hasDiffuseTextureTransparency() == true && specularMaterialProperties->hasDiffuseTextureMaskedTransparency() == true)) {
					if (cullingMode != 0) {
						rendererBackend->disableCulling(contextIdx);
						cullingMode = 0;
					}
				} else {
					if (cullingMode != 1) {
						rendererBackend->enableCulling(contextIdx);
						cullingMode = 1;
					}
				}
			} else {
				if (cullingMode != 1) {
					rendererBackend->enableCulling(contextIdx);
					cullingMode = 1;
				}
			}

			// draw this faces entity for each object
			objectRenderContext.objectsToRender = objects;
			do {
				auto hadFrontFaceSetup = false;
				auto hadShaderSetup = false;

				Vector3 objectCamFromAxis;
				Matrix4x4 modelViewMatrixTemp;
				Matrix4x4 modelViewMatrix;

				FloatBuffer fbEffectColorMuls = objectRenderContext.bbEffectColorMuls->asFloatBuffer();
				FloatBuffer fbEffectColorAdds = objectRenderContext.bbEffectColorAdds->asFloatBuffer();
				FloatBuffer fbMvMatrices = objectRenderContext.bbMvMatrices->asFloatBuffer();

				string materialKey;
				string shaderParametersHash;
				bool materialUpdateOnly = false;
				vector<int32_t>* boundVBOBaseIds = nullptr;
				vector<int32_t>* boundVBOTangentBitangentIds = nullptr;
				vector<int32_t>* boundVBOOrigins = nullptr;
				auto currentLODLevel = -1;
				int32_t boundEnvironmentMappingCubeMapTextureId = -1;
				Vector3 boundEnvironmentMappingCubeMapPosition;
				auto objectCount = objectRenderContext.objectsToRender.size();

				//
				auto textureMatrix = objectRenderContext.objectsToRender[0]->objectNodes[objectNodeIdx]->textureMatricesByEntities[faceEntityIdx];

				// draw objects
				for (auto objectIdx = 0; objectIdx < objectCount; objectIdx++) {
					auto object = objectRenderContext.objectsToRender[objectIdx];
					auto _objectNode = object->objectNodes[objectNodeIdx];

					//	check transparency via effect
					if (object->effectColorMul.getAlpha() < 1.0f - Math::EPSILON ||
						object->effectColorAdd.getAlpha() < -Math::EPSILON) {
						// add to transparent render faces, if requested
						if (collectTransparentFaces == true) {
							transparentRenderFacesPool->createTransparentRenderFaces(
								(_objectNode->mesh->skinning == true ?
									modelViewMatrixTemp.identity() :
									modelViewMatrixTemp.set(*_objectNode->nodeTransformMatrix).multiply(object->getTransformMatrix())
								).multiply(cameraMatrix),
								_objectNode,
								faceEntityIdx,
								faceIdx
							);
						}
						// skip to next object
						continue;
					}

					// limit objects to render to INSTANCEDRENDERING_OBJECTS_MAX
					if (fbMvMatrices.getPosition() / 16 == INSTANCEDRENDERING_OBJECTS_MAX) {
						objectRenderContext.objectsNotRendered.push_back(object);
						continue;
					}

					// check if texture matrix did change
					if (_objectNode->textureMatricesByEntities[faceEntityIdx].equals(textureMatrix) == false) {
						objectRenderContext.objectsNotRendered.push_back(object);
						continue;
					}

					// shader
					if (hadShaderSetup == false) {
						if (object->getShader() != rendererBackend->getShader(contextIdx)) {
							rendererBackend->setShader(contextIdx, object->getShader());
							rendererBackend->onUpdateShader(contextIdx);
							for (auto j = 0; j < engine->lights.size(); j++) engine->lights[j]->update(contextIdx);
							// issue upload matrices
							rendererBackend->onUpdateCameraMatrix(contextIdx);
							rendererBackend->onUpdateProjectionMatrix(contextIdx);
							rendererBackend->onUpdateTextureMatrix(contextIdx);
						}
						hadShaderSetup = true;
					} else
					if (object->getShader() != rendererBackend->getShader(contextIdx)) {
						objectRenderContext.objectsNotRendered.push_back(object);
						continue;
					}

					// set up material on first object and update on succeeding
					auto materialKeyCurrent = materialKey;
					if (materialUpdateOnly == false || checkMaterialChangable(_objectNode, faceEntityIdx, renderTypes) == true) {
						setupMaterial(contextIdx, _objectNode, faceEntityIdx, renderTypes, materialUpdateOnly, materialKeyCurrent, materialKey);
						// only update material for next material calls
						if (materialUpdateOnly == false) {
							materialKey = materialKeyCurrent;
							materialUpdateOnly = true;
						}
					}

					// check if material key has not been set yet
					if (materialKey != materialKeyCurrent) {
						objectRenderContext.objectsNotRendered.push_back(object);
						continue;
					}

					// shader parameters
					if (shaderParametersHash.empty() == true) {
						rendererBackend->setShaderParameters(contextIdx, object->shaderParameters);
						rendererBackend->onUpdateShaderParameters(contextIdx);
						shaderParametersHash = rendererBackend->getShaderParameters(contextIdx).getShaderParametersHash();
					} else
					if (shaderParametersHash != rendererBackend->getShaderParameters(contextIdx).getShaderParametersHash()) {
						objectRenderContext.objectsNotRendered.push_back(object);
					}

					// bind buffer base objects if not bound yet
					auto currentVBOBaseIds = _objectNode->rendererBackend->vboBaseIds;
					if (boundVBOBaseIds == nullptr) {
						boundVBOBaseIds = currentVBOBaseIds;
						//	texture coordinates
						if (isTextureCoordinatesAvailable == true &&
							(((renderTypes & RENDERTYPE_TEXTUREARRAYS) == RENDERTYPE_TEXTUREARRAYS) ||
							((renderTypes & RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY) == RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY && specularMaterialProperties != nullptr && specularMaterialProperties->hasDiffuseTextureMaskedTransparency() == true))) {
							rendererBackend->bindTextureCoordinatesBufferObject(contextIdx, (*currentVBOBaseIds)[3]);
						}
						// 	indices
						rendererBackend->bindIndicesBufferObject(contextIdx, (*currentVBOBaseIds)[0]);
						// 	vertices
						rendererBackend->bindVerticesBufferObject(contextIdx, (*currentVBOBaseIds)[1]);
						// 	normals
						if ((renderTypes & RENDERTYPE_NORMALS) == RENDERTYPE_NORMALS) {
							rendererBackend->bindNormalsBufferObject(contextIdx, (*currentVBOBaseIds)[2]);
						}
					} else
					// check if buffers did change, then skip and render in next step
					if (boundVBOBaseIds != currentVBOBaseIds) {
						objectRenderContext.objectsNotRendered.push_back(object);
						continue;
					}
					auto currentVBOLods = _objectNode->rendererBackend->vboLods;
					if (currentVBOLods != nullptr) {
						auto distanceSquared = objectCamFromAxis.set(object->getWorldBoundingBox()->computeClosestPointInBoundingBox(camera->getLookFrom())).sub(camera->getLookFrom()).computeLengthSquared();
						// index buffer
						auto lodLevel = 0;
						if (currentVBOLods->size() >= 3 && distanceSquared >= Math::square(_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD3Distance())) {
							lodLevel = 3;
						} else
						if (currentVBOLods->size() >= 2 && distanceSquared >= Math::square(_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD2Distance())) {
							lodLevel = 2;
						} else
						if (currentVBOLods->size() >= 1 && distanceSquared >= Math::square(_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD1Distance())) {
							lodLevel = 1;
						}
						if (currentLODLevel != -1 && lodLevel != currentLODLevel) {
							objectRenderContext.objectsNotRendered.push_back(object);
							continue;
						}
						if (lodLevel > 0) {
							rendererBackend->bindIndicesBufferObject(contextIdx, (*currentVBOLods)[lodLevel - 1]);
							switch(lodLevel) {
								case 3:
									faces = (_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD3Indices().size() / 3) * firstObject->instances;
									facesToRender = (_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD3Indices().size() / 3) * firstObject->enabledInstances;
									break;
								case 2:
									faces = (_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD2Indices().size() / 3) * firstObject->instances;
									facesToRender = (_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD2Indices().size() / 3) * firstObject->enabledInstances;
									break;
								case 1:
									faces = (_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD1Indices().size() / 3) * firstObject->instances;
									facesToRender = (_objectNode->node->getFacesEntities()[faceEntityIdx].getLOD1Indices().size() / 3) * firstObject->enabledInstances;
									break;
								default: break;
							}
						}
						currentLODLevel = lodLevel;
					}
					// bind tangent, bitangend buffers
					auto currentVBONormalMappingIds = _objectNode->rendererBackend->vboNormalMappingIds;
					if ((renderTypes & RENDERTYPE_NORMALS) == RENDERTYPE_NORMALS &&
						rendererBackend->isNormalMappingAvailable() == true && currentVBONormalMappingIds != nullptr) {
						// bind tangent, bitangend buffers if not yet done
						if (boundVBOTangentBitangentIds == nullptr) {
							// tangent
							rendererBackend->bindTangentsBufferObject(contextIdx, (*currentVBONormalMappingIds)[0]);
							// bitangent
							rendererBackend->bindBitangentsBufferObject(contextIdx, (*currentVBONormalMappingIds)[1]);
							//
							boundVBOTangentBitangentIds = currentVBONormalMappingIds;
						} else
						// check if buffers did change, then skip and render in next step
						if (currentVBONormalMappingIds != boundVBOTangentBitangentIds) {
							objectRenderContext.objectsNotRendered.push_back(object);
							continue;
						}
					}

					// bind render node object origins
					auto currentVBOOrigins = _objectNode->rendererBackend->vboOrigins;
					if (currentVBOOrigins != nullptr) {
						// bind render node object origins if not yet done
						if (boundVBOOrigins == nullptr) {
							rendererBackend->bindOriginsBufferObject(contextIdx, (*currentVBOOrigins)[0]);
							//
							boundVBOOrigins = currentVBOOrigins;
						} else
						// check if buffers did change, then skip and render in next step
						if (currentVBOOrigins != boundVBOOrigins) {
							objectRenderContext.objectsNotRendered.push_back(object);
							continue;
						}
					}

					// set up local -> world transform matrix
					modelViewMatrix.set(
						_objectNode->mesh->skinning == true?
							modelViewMatrixTemp.identity() :
							modelViewMatrixTemp.set(*_objectNode->nodeTransformMatrix).
							multiply(object->getTransformMatrix())
					);

					// set up front face
					auto objectFrontFace = rightHandedMatrix.isRightHanded(modelViewMatrix) == false ? rendererBackend->FRONTFACE_CCW : rendererBackend->FRONTFACE_CW;
					// if front face changed just render in next step, this all makes only sense if culling is enabled
					if (cullingMode == 1) {
						if (hadFrontFaceSetup == false) {
							hadFrontFaceSetup = true;
							if (objectFrontFace != frontFace) {
								frontFace = objectFrontFace;
								rendererBackend->setFrontFace(contextIdx, frontFace);
							}
						} else
						if (objectFrontFace != frontFace) {
							objectRenderContext.objectsNotRendered.push_back(object);
							continue;
						}
					}

					// reflection source
					if (object->getReflectionEnvironmentMappingId().empty() == false) {
						EnvironmentMapping* environmentMappingEntity = nullptr;
						// some note: engine->getEntity() is not thread safe if having multithreaded renderer, but at this time there should be no other access anyways
						auto environmentMappingEntityCandidate = engine->getEntity(object->getReflectionEnvironmentMappingId());
						if (environmentMappingEntityCandidate != nullptr) {
							if (environmentMappingEntityCandidate->getEntityType() == Entity::ENTITYTYPE_ENVIRONMENTMAPPING) {
								environmentMappingEntity = static_cast<EnvironmentMapping*>(environmentMappingEntityCandidate);
							} else
							if (environmentMappingEntityCandidate->getEntityType() == Entity::ENTITYTYPE_ENTITYHIERARCHY) {
								auto entityHierarchyEnvironmentMappingEntity = static_cast<EntityHierarchy*>(environmentMappingEntityCandidate)->getEntityByType(Entity::ENTITYTYPE_ENVIRONMENTMAPPING);
								if (entityHierarchyEnvironmentMappingEntity != nullptr) environmentMappingEntity = static_cast<EnvironmentMapping*>(entityHierarchyEnvironmentMappingEntity);

							}
						}
						if (environmentMappingEntity != nullptr) {
							Vector3 environmentMappingTranslation;
							object->getTransformMatrix().getTranslation(environmentMappingTranslation);
							auto environmentMappingCubeMapTextureId = environmentMappingEntity->getCubeMapTextureId();
							Vector3 environmentMappingCubeMapPosition = object->hasReflectionEnvironmentMappingPosition() == true?object->getReflectionEnvironmentMappingPosition():environmentMappingTranslation;
							if (boundEnvironmentMappingCubeMapTextureId == -1) {
								boundEnvironmentMappingCubeMapTextureId = environmentMappingCubeMapTextureId;
								boundEnvironmentMappingCubeMapPosition = environmentMappingCubeMapPosition;
								rendererBackend->setEnvironmentMappingCubeMapPosition(contextIdx, environmentMappingCubeMapPosition.getArray());
								rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_ENVIRONMENT);
								rendererBackend->bindCubeMapTexture(contextIdx, environmentMappingCubeMapTextureId);
								rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE);
							} else
							if (boundEnvironmentMappingCubeMapTextureId != environmentMappingCubeMapTextureId || environmentMappingCubeMapPosition.equals(boundEnvironmentMappingCubeMapPosition) == false) {
								objectRenderContext.objectsNotRendered.push_back(object);
								continue;
							}
						}
					} else
					if (boundEnvironmentMappingCubeMapTextureId != -1) {
						objectRenderContext.objectsNotRendered.push_back(object);
						continue;
					}
					// set up effect color
					if ((renderTypes & RENDERTYPE_EFFECTCOLORS) == RENDERTYPE_EFFECTCOLORS) {
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
						rendererBackend->uploadBufferObject(contextIdx, (*objectRenderContext.vboInstancedRenderingIds)[0], fbMvMatrices.getPosition() * sizeof(float), &fbMvMatrices);
						rendererBackend->bindModelMatricesBufferObject(contextIdx, (*objectRenderContext.vboInstancedRenderingIds)[0]);
					}

					// upload effects
					if ((renderTypes & RENDERTYPE_EFFECTCOLORS) == RENDERTYPE_EFFECTCOLORS) {
						// upload effect color mul
						rendererBackend->uploadBufferObject(contextIdx, (*objectRenderContext.vboInstancedRenderingIds)[1], fbEffectColorMuls.getPosition() * sizeof(float), &fbEffectColorMuls);
						rendererBackend->bindEffectColorMulsBufferObject(contextIdx, (*objectRenderContext.vboInstancedRenderingIds)[1], 1);
						rendererBackend->uploadBufferObject(contextIdx, (*objectRenderContext.vboInstancedRenderingIds)[2], fbEffectColorAdds.getPosition() * sizeof(float), &fbEffectColorAdds);
						rendererBackend->bindEffectColorAddsBufferObject(contextIdx, (*objectRenderContext.vboInstancedRenderingIds)[2], 1);
					}

					// set up texture matrix
					//	TODO: check if texture is in use
					if ((renderTypes & RENDERTYPE_TEXTURES) == RENDERTYPE_TEXTURES ||
						(renderTypes & RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) == RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) {
						rendererBackend->getTextureMatrix(contextIdx).set(textureMatrix);
						rendererBackend->onUpdateTextureMatrix(contextIdx);
					}

					// draw
					rendererBackend->drawInstancedIndexedTrianglesFromBufferObjects(contextIdx, facesToRender, faceIdx, objectsToRenderIssue);
				}

				// clear list of objects we did not render
				objectRenderContext.objectsToRender = objectRenderContext.objectsNotRendered;
				objectRenderContext.objectsNotRendered.clear();

				// TODO: improve me!
				if (boundEnvironmentMappingCubeMapTextureId != -1) {
					rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_ENVIRONMENT);
					rendererBackend->bindCubeMapTexture(contextIdx, rendererBackend->ID_NONE);
					rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE);
				}
			} while (objectRenderContext.objectsToRender.size() > 0);

			// keep track of rendered faces
			faceIdx += faces;
		}
	}

	//
	if (cullingMode != 1) {
		rendererBackend->enableCulling(contextIdx);
		cullingMode = 1;
	}

	// unbind buffers
	rendererBackend->unbindBufferObjects(contextIdx);

	// reset objects to render
	objectRenderContext.objectsToRender.clear();
	objectRenderContext.objectsNotRendered.clear();
}

void EntityRenderer::setupMaterial(int contextIdx, ObjectNode* objectNode, int32_t facesEntityIdx, int32_t renderTypes, bool updateOnly, string& materialKey, const string& currentMaterialKey)
{
	const auto& facesEntities = objectNode->node->getFacesEntities();
	auto material = facesEntities[facesEntityIdx].getMaterial();
	// get material or use default
	if (material == nullptr) material = Material::getDefaultMaterial();
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	auto pbrMaterialProperties = material->getPBRMaterialProperties();

	// material key
	materialKey = material->getId();

	// setup textures
	ObjectNode::setupTextures(rendererBackend, contextIdx, objectNode, facesEntityIdx);

	//
	if (updateOnly == false) {
		if (rendererBackend->getLighting(contextIdx) == rendererBackend->LIGHTING_SPECULAR) {
			// apply materials
			if ((renderTypes & RENDERTYPE_MATERIALS) == RENDERTYPE_MATERIALS) {
				auto& rendererMaterial = rendererBackend->getSpecularMaterial(contextIdx);
				rendererMaterial.ambient = specularMaterialProperties->getAmbientColor().getArray();
				rendererMaterial.diffuse = specularMaterialProperties->getDiffuseColor().getArray();
				rendererMaterial.specular = specularMaterialProperties->getSpecularColor().getArray();
				rendererMaterial.emission = specularMaterialProperties->getEmissionColor().getArray();
				rendererMaterial.shininess = specularMaterialProperties->getShininess();
				rendererMaterial.reflection = specularMaterialProperties->getReflection();
				rendererMaterial.diffuseTextureMaskedTransparency = specularMaterialProperties->hasDiffuseTextureMaskedTransparency() == true?1:0;
				rendererMaterial.diffuseTextureMaskedTransparencyThreshold = specularMaterialProperties->getDiffuseTextureMaskedTransparencyThreshold();
				rendererBackend->onUpdateMaterial(contextIdx);
			}
			if ((renderTypes & RENDERTYPE_TEXTURES) == RENDERTYPE_TEXTURES) {
				// bind specular texture
				if (rendererBackend->isSpecularMappingAvailable() == true) {
					rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_SPECULAR);
					rendererBackend->bindTexture(contextIdx, objectNode->specularMaterialSpecularTextureIdsByEntities[facesEntityIdx]);
				}
				// bind normal texture
				if (rendererBackend->isNormalMappingAvailable() == true) {
					rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_NORMAL);
					rendererBackend->bindTexture(contextIdx, objectNode->specularMaterialNormalTextureIdsByEntities[facesEntityIdx]);
				}
				// switch back texture unit to diffuse unit
				rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE);
			}
		} else
		if (rendererBackend->getLighting(contextIdx) == rendererBackend->LIGHTING_PBR) {
			// apply materials
			if ((renderTypes & RENDERTYPE_MATERIALS) == RENDERTYPE_MATERIALS) {
				auto& rendererMaterial = rendererBackend->getPBRMaterial(contextIdx);
				if (pbrMaterialProperties == nullptr) {
					rendererMaterial.baseColorFactor = {{ 1.0f, 1.0f, 1.0f, 1.0f }};
					rendererMaterial.metallicFactor = 1.0f;
					rendererMaterial.roughnessFactor = 1.0f;
					rendererMaterial.normalScale = 1.0f;
					rendererMaterial.emissiveFactor = {{ 1.0f, 1.0f, 1.0f }};
					rendererMaterial.exposure = 1.0f;
					rendererMaterial.baseColorTextureMaskedTransparency = 0;
					rendererMaterial.baseColorTextureMaskedTransparencyThreshold = 0.0f;
				} else {
					rendererMaterial.baseColorFactor = pbrMaterialProperties->getBaseColorFactor().getArray();
					rendererMaterial.metallicFactor = pbrMaterialProperties->getMetallicFactor();
					rendererMaterial.roughnessFactor = pbrMaterialProperties->getRoughnessFactor();
					rendererMaterial.normalScale = pbrMaterialProperties->getNormalScale();
					rendererMaterial.emissiveFactor =
						{
							pbrMaterialProperties->getEmissiveFactor()[0],
							pbrMaterialProperties->getEmissiveFactor()[1],
							pbrMaterialProperties->getEmissiveFactor()[2]
						};
					rendererMaterial.exposure = pbrMaterialProperties->getExposure();
					rendererMaterial.baseColorTextureMaskedTransparency = pbrMaterialProperties->hasBaseColorTextureMaskedTransparency() == true?1:0;
					rendererMaterial.baseColorTextureMaskedTransparencyThreshold = pbrMaterialProperties->getBaseColorTextureMaskedTransparencyThreshold();
				}
				rendererBackend->onUpdateMaterial(contextIdx);
			}
			if ((renderTypes & RENDERTYPE_TEXTURES) == RENDERTYPE_TEXTURES) {
				// bind metallic roughness texture
				rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_METALLICROUGHNESS);
				rendererBackend->bindTexture(contextIdx, objectNode->pbrMaterialMetallicRoughnessTextureIdsByEntities[facesEntityIdx]);
				// bind normal texture
				rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_NORMAL);
				rendererBackend->bindTexture(contextIdx, objectNode->pbrMaterialNormalTextureIdsByEntities[facesEntityIdx]);
				// bind emissive texture
				rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_EMISSIVE);
				rendererBackend->bindTexture(contextIdx, objectNode->pbrMaterialEmissiveTextureIdsByEntities[facesEntityIdx]);
				// switch back texture unit to base color unit
				rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_BASECOLOR);
			}
		}
	}

	// bind diffuse/base color texture
	if ((renderTypes & RENDERTYPE_TEXTURES) == RENDERTYPE_TEXTURES ||
		((renderTypes & RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) == RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY)) {
		if (rendererBackend->getLighting(contextIdx) == rendererBackend->LIGHTING_SPECULAR) {
			auto& rendererMaterial = rendererBackend->getSpecularMaterial(contextIdx);
			auto diffuseTexture = specularMaterialProperties->getDiffuseTexture();
			rendererMaterial.diffuseTextureMaskedTransparency = specularMaterialProperties->hasDiffuseTextureMaskedTransparency() == true?1:0;
			rendererMaterial.diffuseTextureMaskedTransparencyThreshold = specularMaterialProperties->getDiffuseTextureMaskedTransparencyThreshold();
			rendererMaterial.textureAtlasSize = specularMaterialProperties->getTextureAtlasSize();
			rendererMaterial.textureAtlasPixelDimension = { 0.0f, 0.0f };
			if (rendererMaterial.textureAtlasSize > 1 && diffuseTexture != nullptr) {
				rendererMaterial.textureAtlasPixelDimension[0] = 1.0f / diffuseTexture->getTextureWidth();
				rendererMaterial.textureAtlasPixelDimension[1] = 1.0f / diffuseTexture->getTextureHeight();
			}
			rendererBackend->onUpdateMaterial(contextIdx);
			if ((renderTypes & RENDERTYPE_TEXTURES) == RENDERTYPE_TEXTURES ||
				specularMaterialProperties->hasDiffuseTextureMaskedTransparency() == true) {
				auto diffuseTextureId =
					objectNode->specularMaterialDynamicDiffuseTextureIdsByEntities[facesEntityIdx] != ObjectNode::TEXTUREID_NONE ?
					objectNode->specularMaterialDynamicDiffuseTextureIdsByEntities[facesEntityIdx] :
					objectNode->specularMaterialDiffuseTextureIdsByEntities[facesEntityIdx];
				materialKey+= ",";
				materialKey.append((const char*)&diffuseTextureId, sizeof(diffuseTextureId));
				if (updateOnly == false || currentMaterialKey.empty() == true) {
					rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE);
					rendererBackend->bindTexture(contextIdx, diffuseTextureId);
				}
			}
		} else
		if (rendererBackend->getLighting(contextIdx) == rendererBackend->LIGHTING_PBR) {
			auto& rendererMaterial = rendererBackend->getPBRMaterial(contextIdx);
			if (pbrMaterialProperties == nullptr) {
				rendererMaterial.baseColorTextureMaskedTransparency = 0;
				rendererMaterial.baseColorTextureMaskedTransparencyThreshold = 0.0f;
			} else {
				rendererMaterial.baseColorTextureMaskedTransparency = pbrMaterialProperties->hasBaseColorTextureMaskedTransparency() == true?1:0;
				rendererMaterial.baseColorTextureMaskedTransparencyThreshold = pbrMaterialProperties->getBaseColorTextureMaskedTransparencyThreshold();
			}
			rendererBackend->onUpdateMaterial(contextIdx);
			rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_BASECOLOR);
			rendererBackend->bindTexture(contextIdx, objectNode->pbrMaterialBaseColorTextureIdsByEntities[facesEntityIdx]);
		}
	}
}

void EntityRenderer::clearMaterial(int contextIdx)
{
	// TODO: optimize me! We do not need always to clear material
	if (rendererBackend->getLighting(contextIdx) == rendererBackend->LIGHTING_SPECULAR) {
		// unbind diffuse texture
		rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE);
		rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
		// unbind specular texture
		if (rendererBackend->isSpecularMappingAvailable() == true) {
			rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_SPECULAR);
			rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
		}
		// unbind normal texture
		if (rendererBackend->isNormalMappingAvailable()) {
			rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_NORMAL);
			rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
		}
		// set diffuse texture unit
		rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::SPECULAR_TEXTUREUNIT_DIFFUSE);
	} else
	if (rendererBackend->getLighting(contextIdx) == rendererBackend->LIGHTING_PBR) {
		// unbind base color texture
		rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_BASECOLOR);
		rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
		// unbind metallic roughness texture
		rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_METALLICROUGHNESS);
		rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
		// unbind normal texture
		rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_NORMAL);
		rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
		// unbind emissive texture
		rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_EMISSIVE);
		rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
		// set diffuse texture unit
		rendererBackend->setTextureUnit(contextIdx, LightingShaderConstants::PBR_TEXTUREUNIT_BASECOLOR);
	}
}

void EntityRenderer::render(Entity::RenderPass renderPass, const vector<Entity*>& pses)
{
	// TODO: Move me into own class
	if (pses.size() == 0) return;

	//
	struct PseParameters {
		const Color4* effectColorAdd;
		const Color4* effectColorMul;
		int32_t textureHorizontalSprites;
		int32_t textureVerticalSprites;
		float pointSize;
		int32_t atlasTextureIndex;
	};
	unordered_map<void*, PseParameters> rendererPseParameters;

	// use default context
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;

	// store model view matrix
	Matrix4x4 modelViewMatrix;
	modelViewMatrix.set(rendererBackend->getModelViewMatrix());

	// set up renderer state
	rendererBackend->enableBlending();
	// 	model view matrix
	rendererBackend->getModelViewMatrix().identity();
	rendererBackend->onUpdateModelViewMatrix(contextIdx);

	// switch back to texture unit 0, TODO: check where its set to another value but not set back
	rendererBackend->setTextureUnit(contextIdx, 0);

	// merge pses, transform them into camera space and sort them
	const auto& cameraMatrix = rendererBackend->getCameraMatrix();
	for (auto entity: pses) {
		if (entity->getRenderPass() != renderPass) continue;
		auto ppse = dynamic_cast<PointsParticleSystem*>(entity);
		if (ppse != nullptr) {
			int atlasTextureIndex = engine->ppsTextureAtlas.getTextureIdx(ppse->getTexture());
			if (atlasTextureIndex == TextureAtlas::TEXTURE_IDX_NONE) continue;
			rendererPseParameters[ppse] = {
				.effectColorAdd = &ppse->getEffectColorAdd(),
				.effectColorMul = &ppse->getEffectColorMul(),
				.textureHorizontalSprites = ppse->getTextureHorizontalSprites(),
				.textureVerticalSprites = ppse->getTextureVerticalSprites(),
				.pointSize = ppse->getPointSize(),
				.atlasTextureIndex = atlasTextureIndex
			};
			renderTransparentRenderPointsPool->merge(ppse->getRenderPointsPool(), cameraMatrix);
		} else {
			auto fpse = dynamic_cast<FogParticleSystem*>(entity);
			if (fpse != nullptr) {
				int atlasTextureIndex = engine->ppsTextureAtlas.getTextureIdx(fpse->getTexture());
				if (atlasTextureIndex == TextureAtlas::TEXTURE_IDX_NONE) continue;
				rendererPseParameters[fpse] = {
					.effectColorAdd = &fpse->getEffectColorAdd(),
					.effectColorMul = &fpse->getEffectColorMul(),
					.textureHorizontalSprites = fpse->getTextureHorizontalSprites(),
					.textureVerticalSprites = fpse->getTextureVerticalSprites(),
					.pointSize = fpse->getPointSize(),
					.atlasTextureIndex = atlasTextureIndex
				};
				renderTransparentRenderPointsPool->merge(fpse->getRenderPointsPool(), cameraMatrix);
			}
		}
	}
	if (renderTransparentRenderPointsPool->getTransparentRenderPointsCount() > 0) {
		renderTransparentRenderPointsPool->sort();
		// render
		auto points =  renderTransparentRenderPointsPool->getTransparentRenderPoints();
		auto pseParameters = &rendererPseParameters.find(points[0]->particleSystem)->second;
		auto currentPpse = static_cast<void*>(points[0]->particleSystem);
		if (rendererBackend->isSupportingIntegerProgramAttributes() == true) {
			for (auto i = 0; i < renderTransparentRenderPointsPool->getTransparentRenderPointsCount(); i++) {
				auto point = points[i];
				if (point->particleSystem != (void*)currentPpse) {
					pseParameters = &rendererPseParameters.find(point->particleSystem)->second;
					currentPpse = point->particleSystem;
				}
				psePointBatchRenderer->addPoint(
					point,
					pseParameters->atlasTextureIndex,
					pseParameters->pointSize,
					*pseParameters->effectColorMul,
					*pseParameters->effectColorAdd,
					pseParameters->textureHorizontalSprites,
					pseParameters->textureVerticalSprites
				);
			}
		} else {
			for (auto i = 0; i < renderTransparentRenderPointsPool->getTransparentRenderPointsCount(); i++) {
				auto point = points[i];
				if (point->particleSystem != (void*)currentPpse) {
					pseParameters = &rendererPseParameters.find(point->particleSystem)->second;
					currentPpse = point->particleSystem;
				}
				psePointBatchRenderer->addPointNoInteger(
					point,
					pseParameters->atlasTextureIndex,
					pseParameters->pointSize,
					*pseParameters->effectColorMul,
					*pseParameters->effectColorAdd,
					pseParameters->textureHorizontalSprites,
					pseParameters->textureVerticalSprites
				);
			}
		}

		// texture atlas
		engine->getParticlesShader()->setTextureAtlas(contextIdx, &engine->getPointParticleSystemTextureAtlas());

		// render, clear
		psePointBatchRenderer->render(contextIdx);
		psePointBatchRenderer->clear();

		// done
		renderTransparentRenderPointsPool->reset();
	}

	// unset renderer state
	rendererBackend->disableBlending();
	// restore renderer state
	rendererBackend->unbindBufferObjects(contextIdx);
	rendererBackend->getModelViewMatrix().set(modelViewMatrix);
}

void EntityRenderer::render(Entity::RenderPass renderPass, const vector<Lines*>& linesEntities) {
	// TODO: Move me into own class
	// TODO: check me performance wise again
	if (linesEntities.size() == 0) return;

	// use default context
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;

	// switch back to texture unit 0, TODO: check where its set to another value but not set back
	rendererBackend->setTextureUnit(contextIdx, 0);

	// store model view matrix
	Matrix4x4 modelViewMatrix;
	modelViewMatrix.set(rendererBackend->getModelViewMatrix());

	// set up renderer state
	rendererBackend->enableBlending();

	//
	for (auto entity: linesEntities) {
		if (entity->getRenderPass() != renderPass) continue;

		// 	model view matrix
		rendererBackend->getModelViewMatrix().set(entity->getTransformMatrix()).multiply(rendererBackend->getCameraMatrix());
		rendererBackend->onUpdateModelViewMatrix(contextIdx);

		// render
		// issue rendering
		rendererBackend->getEffectColorAdd(contextIdx) = entity->getEffectColorAdd().getArray();
		rendererBackend->getEffectColorMul(contextIdx) = entity->getEffectColorMul().getArray();
		rendererBackend->onUpdateEffect(contextIdx);

		// TODO: maybe use onBindTexture() or onUpdatePointSize()
		engine->getLinesShader()->setParameters(contextIdx, entity->getTextureId(), entity->getLineWidth());

		//
		rendererBackend->bindVerticesBufferObject(contextIdx, (*entity->vboIds)[0]);
		rendererBackend->bindColorsBufferObject(contextIdx, (*entity->vboIds)[1]);
		rendererBackend->drawLinesFromBufferObjects(contextIdx, entity->points.size(), 0);
	}

	// unbind texture
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	// unset renderer state
	rendererBackend->disableBlending();
	// restore renderer state
	rendererBackend->unbindBufferObjects(contextIdx);
	rendererBackend->getModelViewMatrix().set(modelViewMatrix);
}
