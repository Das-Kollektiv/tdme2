#include <tdme/engine/subsystems/skinning/SkinningShader.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/renderer/GL3Renderer.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/rendering/Object3DBase.h>
#include <tdme/engine/subsystems/rendering/Object3DNodeMesh.h>
#include <tdme/engine/subsystems/rendering/Object3DNodeRenderer.h>
#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/FloatBuffer.h>
#include <tdme/utilities/IntBuffer.h>

using std::begin;
using std::copy;
using std::end;
using std::string;
using std::to_string;

using tdme::engine::subsystems::skinning::SkinningShader;

using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::Skinning;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::Object3DBase;
using tdme::engine::subsystems::rendering::Object3DNodeMesh;
using tdme::engine::subsystems::rendering::Object3DNodeRenderer;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::engine::Engine;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::FloatBuffer;
using tdme::utilities::IntBuffer;

SkinningShader::SkinningShader(Renderer* renderer): mutex("skinningshader-mutex")
{
	this->renderer = renderer;
	isRunning = false;
	initialized = false;
	auto threadCount = renderer->isSupportingMultithreadedRendering() == true?Engine::getThreadCount():1;
	contexts.resize(threadCount);
}

bool SkinningShader::isInitialized()
{
	return initialized;
}

void SkinningShader::initialize()
{
	#if defined (__APPLE__) && !defined(VULKAN)
		uniformMatrixCount = renderer->UNIFORM_CL_SKINNING_MATRIX_COUNT;
		uniformInstanceCount = renderer->UNIFORM_CL_SKINNING_INSTANCE_COUNT;
		uniformVertexCount = renderer->UNIFORM_CL_SKINNING_VERTEX_COUNT;
	#else
		auto shaderVersion = renderer->getShaderVersion();

		// shader
		shaderId = renderer->loadShader(
			renderer->SHADER_COMPUTE_SHADER,
			"shader/" + shaderVersion + "/skinning",
			"skinning.glsl"
		);
		if (shaderId == 0) return;

		// create, attach and link program
		programId = renderer->createProgram(renderer->PROGRAM_COMPUTE);
		renderer->attachShaderToProgram(programId, shaderId);

		// link program
		if (renderer->linkProgram(programId) == false) return;

		//
		uniformVertexCount = renderer->getProgramUniformLocation(programId, "vertexCount");
		if (uniformVertexCount == -1) return;
		uniformMatrixCount = renderer->getProgramUniformLocation(programId, "matrixCount");
		if (uniformMatrixCount == -1) return;
		uniformInstanceCount = renderer->getProgramUniformLocation(programId, "instanceCount");
		if (uniformInstanceCount == -1) return;
	#endif

	//
	initialized = true;
}

void SkinningShader::useProgram()
{
	isRunning = true;
}

void SkinningShader::computeSkinning(void* context, Object3DBase* object3DBase, Object3DNodeMesh* object3DNodeMesh)
{
	//
	auto contextIdx = renderer->getContextIndex(context);
	auto& skinningContext = contexts[contextIdx];
	if (skinningContext.running == false) {
		skinningContext.running = true;
		renderer->useProgram(context, programId);
		renderer->setLighting(context, renderer->LIGHTING_NONE);
	}

	// vbo base ids
	auto vboBaseIds = object3DNodeMesh->object3DNodeRenderer->vboBaseIds;

	//
	ModelSkinningCache* modelSkinningCacheCached = nullptr;
	auto node = object3DNodeMesh->node;
	auto& vertices = node->getVertices();
	auto id = node->getModel()->getId() + "." + node->getId();
	mutex.lock();
	auto cacheIt = cache.find(id);
	if (cacheIt == cache.end()) {
		ModelSkinningCache modelSkinningCache;

		auto created = false;
		auto skinning = node->getSkinning();
		auto& verticesJointsWeights = skinning->getVerticesJointsWeights();
		auto& weights = skinning->getWeights();

		// vbos
		{
			auto vboManaged = Engine::getVBOManager()->addVBO("skinning_compute_shader." + id + ".vbos", 5, true, true, created);
			modelSkinningCache.vboIds = vboManaged->getVBOIds();
		}
		{
			if (renderer->isSupportingMultithreadedRendering() == true) {
				for (auto i = 0; i < Engine::getThreadCount(); i++) {
					auto vboManaged = Engine::getVBOManager()->addVBO("skinning_compute_shader." + id + ".vbos.matrices." + to_string(i), 1, false, false, created);
					modelSkinningCache.matricesVboIds.push_back(vboManaged->getVBOIds());
				}
			} else {
				auto vboManaged = Engine::getVBOManager()->addVBO("skinning_compute_shader." + id + ".vbos.matrices", 1, false, false, created);
				modelSkinningCache.matricesVboIds.push_back(vboManaged->getVBOIds());
			}
		}

		// vertices
		{
			object3DNodeMesh->setupVerticesBuffer(renderer, context, (*modelSkinningCache.vboIds)[0]);
		}

		// normals
		{
			object3DNodeMesh->setupNormalsBuffer(renderer, context, (*modelSkinningCache.vboIds)[1]);
		}

		{
			// vertices joints
			auto ibVerticesJoints = ObjectBuffer::getByteBuffer(context, vertices.size() * 1 * sizeof(int))->asIntBuffer();
			for (auto nodeVertexIndex = 0; nodeVertexIndex < vertices.size(); nodeVertexIndex++) {
				auto vertexJoints = verticesJointsWeights[nodeVertexIndex].size();
				// put number of joints
				ibVerticesJoints.put((int)vertexJoints);
			}
			renderer->uploadSkinningBufferObject(context, (*modelSkinningCache.vboIds)[2], ibVerticesJoints.getPosition() * sizeof(int), &ibVerticesJoints);
		}

		{
			// vertices joints indices
			auto ibVerticesVertexJointsIdxs = ObjectBuffer::getByteBuffer(context, vertices.size() * 4 * sizeof(float))->asIntBuffer();
			for (auto nodeVertexIndex = 0; nodeVertexIndex < vertices.size(); nodeVertexIndex++) {
				auto& vertexJointsWeight = verticesJointsWeights[nodeVertexIndex];
				// vertex joint idx 1..4
				for (auto i = 0; i < 4; i++) {
					auto jointIndex = i < vertexJointsWeight.size()?vertexJointsWeight[i].getJointIndex():-1;
					ibVerticesVertexJointsIdxs.put((int)jointIndex);
				}
			}
			renderer->uploadSkinningBufferObject(context, (*modelSkinningCache.vboIds)[3], ibVerticesVertexJointsIdxs.getPosition() * sizeof(int), &ibVerticesVertexJointsIdxs);
		}

		{
			// vertices joints weights
			auto fbVerticesVertexJointsWeights = ObjectBuffer::getByteBuffer(context, vertices.size() * 4 * sizeof(float))->asFloatBuffer();
			for (auto nodeVertexIndex = 0; nodeVertexIndex < vertices.size(); nodeVertexIndex++) {
				auto& vertexJointsWeight = verticesJointsWeights[nodeVertexIndex];
				// vertex joint weight 1..4
				for (auto i = 0; i < 4; i++) {
					fbVerticesVertexJointsWeights.put(static_cast<float>(i < vertexJointsWeight.size()?weights[vertexJointsWeight[i].getWeightIndex()]:0.0f));
				}
			}
			renderer->uploadSkinningBufferObject(context, (*modelSkinningCache.vboIds)[4], fbVerticesVertexJointsWeights.getPosition() * sizeof(float), &fbVerticesVertexJointsWeights);
		}

		// add to cache
		cache[id] = modelSkinningCache;
		modelSkinningCacheCached = &cache[id];
	} else {
		modelSkinningCacheCached = &cacheIt->second;
	}
	mutex.unlock();

	// bind
	renderer->bindSkinningVerticesBufferObject(context, (*modelSkinningCacheCached->vboIds)[0]);
	renderer->bindSkinningNormalsBufferObject(context, (*modelSkinningCacheCached->vboIds)[1]);
	renderer->bindSkinningVertexJointsBufferObject(context, (*modelSkinningCacheCached->vboIds)[2]);
	renderer->bindSkinningVertexJointIdxsBufferObject(context, (*modelSkinningCacheCached->vboIds)[3]);
	renderer->bindSkinningVertexJointWeightsBufferObject(context, (*modelSkinningCacheCached->vboIds)[4]);

	// bind output / result buffers
	renderer->bindSkinningVerticesResultBufferObject(context, (*vboBaseIds)[1]);
	renderer->bindSkinningNormalsResultBufferObject(context, (*vboBaseIds)[2]);

	// upload matrices and set corresponding uniforms
	{
		Matrix4x4 skinningMatrix;
		auto currentInstance = object3DBase->getCurrentInstance();
		auto skinning = node->getSkinning();
		auto& skinningJoints = skinning->getJoints();
		auto fbMatrices = ObjectBuffer::getByteBuffer(context, object3DBase->instances * skinningJoints.size() * 16 * sizeof(float))->asFloatBuffer();
		for (auto i = 0; i < object3DBase->instances; i++) {
			if (object3DBase->instanceEnabled[i] == false) continue;
			object3DBase->setCurrentInstance(i);
			for (auto jointSkinningMatrix: object3DNodeMesh->jointsSkinningMatrices[i]) {
				fbMatrices.put((skinningMatrix.set(*jointSkinningMatrix).multiply(object3DBase->getTransformationsMatrix()).getArray()));
			}
		}
		object3DBase->setCurrentInstance(currentInstance);
		renderer->uploadSkinningBufferObject(context, (*modelSkinningCacheCached->matricesVboIds[contextIdx])[0], fbMatrices.getPosition() * sizeof(float), &fbMatrices);
		renderer->setProgramUniformInteger(context, uniformMatrixCount, skinningJoints.size());
		renderer->setProgramUniformInteger(context, uniformInstanceCount, object3DBase->enabledInstances);
	}

	//
	renderer->bindSkinningMatricesBufferObject(context, (*modelSkinningCacheCached->matricesVboIds[contextIdx])[0]);

	// skinning count
	renderer->setProgramUniformInteger(context, uniformVertexCount, vertices.size());

	// do it so
	renderer->dispatchCompute(
		context,
		(int)Math::ceil(vertices.size() / 16.0f),
		(int)Math::ceil(object3DBase->instances / 16.0f),
		1
	);
}

void SkinningShader::unUseProgram()
{
	if (isRunning == false) return;
	isRunning = false;
	for (auto& skinningContext: contexts) skinningContext.running = false;
	// we are done, do memory barrier
	renderer->memoryBarrier();
}

void SkinningShader::reset() {
	for (auto& modelSkinningCacheIt: cache) {
		Engine::getVBOManager()->removeVBO("skinning_compute_shader." + modelSkinningCacheIt.second.id + ".vbos");
	}
	// TODO: Remove vaos
	cache.clear();
}
