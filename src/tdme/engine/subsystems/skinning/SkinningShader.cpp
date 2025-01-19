#include <tdme/engine/subsystems/skinning/SkinningShader.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/subsystems/rendering/ObjectBase.h>
#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeRenderer.h>
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
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::rendering::ObjectBase;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::engine::subsystems::rendering::ObjectNodeRenderer;
using tdme::engine::Engine;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::FloatBuffer;
using tdme::utilities::IntBuffer;

SkinningShader::SkinningShader(RendererBackend* rendererBackend): mutex("skinningshader-mutex")
{
	this->rendererBackend = rendererBackend;
	isRunning = false;
	initialized = false;
	auto threadCount = rendererBackend->isSupportingMultithreadedRendering() == true?Engine::getThreadCount():1;
	contexts.resize(threadCount);
}

bool SkinningShader::isInitialized()
{
	return initialized;
}

void SkinningShader::initialize()
{
	if (rendererBackend->isGLCLAvailable() == true) {
		uniformMatrixCount = rendererBackend->UNIFORM_CL_SKINNING_MATRIX_COUNT;
		uniformInstanceCount = rendererBackend->UNIFORM_CL_SKINNING_INSTANCE_COUNT;
		uniformVertexCount = rendererBackend->UNIFORM_CL_SKINNING_VERTEX_COUNT;
	} else {
		auto shaderVersion = rendererBackend->getShaderVersion();

		// shader
		shaderId = rendererBackend->loadShader(
			rendererBackend->SHADER_COMPUTE_SHADER,
			"shader/" + shaderVersion + "/skinning",
			"skinning.glsl"
		);
		if (shaderId == 0) return;

		// create, attach and link program
		programId = rendererBackend->createProgram(rendererBackend->PROGRAM_COMPUTE);
		rendererBackend->attachShaderToProgram(programId, shaderId);

		// link program
		if (rendererBackend->linkProgram(programId) == false) return;

		//
		uniformVertexCount = rendererBackend->getProgramUniformLocation(programId, "vertexCount");
		if (uniformVertexCount == -1) return;
		uniformMatrixCount = rendererBackend->getProgramUniformLocation(programId, "matrixCount");
		if (uniformMatrixCount == -1) return;
		uniformInstanceCount = rendererBackend->getProgramUniformLocation(programId, "instanceCount");
		if (uniformInstanceCount == -1) return;
	}

	//
	initialized = true;
}

void SkinningShader::useProgram()
{
	isRunning = true;
}

void SkinningShader::computeSkinning(int contextIdx, ObjectBase* objectBase, ObjectNodeMesh* objectNodeMesh)
{
	//
	auto& skinningContext = contexts[contextIdx];
	if (skinningContext.running == false) {
		skinningContext.running = true;
		rendererBackend->useProgram(contextIdx, programId);
		rendererBackend->setLighting(contextIdx, rendererBackend->LIGHTING_NONE);
	}

	// vbo base ids
	auto vboBaseIds = objectNodeMesh->objectNodeRenderer->vboBaseIds;

	//
	ModelSkinningCache* modelSkinningCacheCached = nullptr;
	auto node = objectNodeMesh->node;
	const auto& vertices = node->getVertices();
	auto id = node->getModel()->getId() + "." + node->getId();
	mutex.lock();
	auto cacheIt = cache.find(id);
	if (cacheIt == cache.end()) {
		ModelSkinningCache modelSkinningCache;

		auto created = false;
		auto skinning = node->getSkinning();
		const auto& verticesJointsWeights = skinning->getVerticesJointsWeights();
		const auto& weights = skinning->getWeights();

		// vbos
		{
			auto vboManaged = Engine::getVBOManager()->addVBO("skinning_compute_shader." + id + ".vbos", 5, true, true, created);
			modelSkinningCache.vboIds = vboManaged->getVBOIds();
		}
		{
			if (rendererBackend->isSupportingMultithreadedRendering() == true) {
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
			objectNodeMesh->setupVerticesBuffer(rendererBackend, contextIdx, (*modelSkinningCache.vboIds)[0]);
		}

		// normals
		{
			objectNodeMesh->setupNormalsBuffer(rendererBackend, contextIdx, (*modelSkinningCache.vboIds)[1]);
		}

		{
			// vertices joints
			auto ibVerticesJoints = ObjectBuffer::getByteBuffer(contextIdx, vertices.size() * 1 * sizeof(int))->asIntBuffer();
			for (auto nodeVertexIndex = 0; nodeVertexIndex < vertices.size(); nodeVertexIndex++) {
				auto vertexJoints = verticesJointsWeights[nodeVertexIndex].size();
				// put number of joints
				ibVerticesJoints.put((int)vertexJoints);
			}
			rendererBackend->uploadSkinningBufferObject(contextIdx, (*modelSkinningCache.vboIds)[2], ibVerticesJoints.getPosition() * sizeof(int), &ibVerticesJoints);
		}

		{
			// vertices joints indices
			auto ibVerticesVertexJointsIdxs = ObjectBuffer::getByteBuffer(contextIdx, vertices.size() * 4 * sizeof(float))->asIntBuffer();
			for (auto nodeVertexIndex = 0; nodeVertexIndex < vertices.size(); nodeVertexIndex++) {
				const auto& vertexJointsWeight = verticesJointsWeights[nodeVertexIndex];
				// vertex joint idx 1..4
				for (auto i = 0; i < 4; i++) {
					auto jointIndex = i < vertexJointsWeight.size()?vertexJointsWeight[i].getJointIndex():-1;
					ibVerticesVertexJointsIdxs.put((int)jointIndex);
				}
			}
			rendererBackend->uploadSkinningBufferObject(contextIdx, (*modelSkinningCache.vboIds)[3], ibVerticesVertexJointsIdxs.getPosition() * sizeof(int), &ibVerticesVertexJointsIdxs);
		}

		{
			// vertices joints weights
			auto fbVerticesVertexJointsWeights = ObjectBuffer::getByteBuffer(contextIdx, vertices.size() * 4 * sizeof(float))->asFloatBuffer();
			for (auto nodeVertexIndex = 0; nodeVertexIndex < vertices.size(); nodeVertexIndex++) {
				const auto& vertexJointsWeight = verticesJointsWeights[nodeVertexIndex];
				// vertex joint weight 1..4
				for (auto i = 0; i < 4; i++) {
					fbVerticesVertexJointsWeights.put(static_cast<float>(i < vertexJointsWeight.size()?weights[vertexJointsWeight[i].getWeightIndex()]:0.0f));
				}
			}
			rendererBackend->uploadSkinningBufferObject(contextIdx, (*modelSkinningCache.vboIds)[4], fbVerticesVertexJointsWeights.getPosition() * sizeof(float), &fbVerticesVertexJointsWeights);
		}

		// add to cache
		cache[id] = modelSkinningCache;
		modelSkinningCacheCached = &cache[id];
	} else {
		modelSkinningCacheCached = &cacheIt->second;
	}
	mutex.unlock();

	// bind
	rendererBackend->bindSkinningVerticesBufferObject(contextIdx, (*modelSkinningCacheCached->vboIds)[0]);
	rendererBackend->bindSkinningNormalsBufferObject(contextIdx, (*modelSkinningCacheCached->vboIds)[1]);
	rendererBackend->bindSkinningVertexJointsBufferObject(contextIdx, (*modelSkinningCacheCached->vboIds)[2]);
	rendererBackend->bindSkinningVertexJointIdxsBufferObject(contextIdx, (*modelSkinningCacheCached->vboIds)[3]);
	rendererBackend->bindSkinningVertexJointWeightsBufferObject(contextIdx, (*modelSkinningCacheCached->vboIds)[4]);

	// bind output / result buffers
	rendererBackend->bindSkinningVerticesResultBufferObject(contextIdx, (*vboBaseIds)[1]);
	rendererBackend->bindSkinningNormalsResultBufferObject(contextIdx, (*vboBaseIds)[2]);

	// upload matrices and set corresponding uniforms
	{
		Matrix4x4 skinningMatrix;
		auto currentInstance = objectBase->getCurrentInstance();
		auto skinning = node->getSkinning();
		const auto& skinningJoints = skinning->getJoints();
		auto fbMatrices = ObjectBuffer::getByteBuffer(contextIdx, objectBase->instances * skinningJoints.size() * 16 * sizeof(float))->asFloatBuffer();
		for (auto i = 0; i < objectBase->instances; i++) {
			if (objectBase->instanceEnabled[i] == false) continue;
			objectBase->setCurrentInstance(i);
			for (auto jointSkinningMatrix: objectNodeMesh->jointsSkinningMatrices[i]) {
				if (jointSkinningMatrix != nullptr) {
					fbMatrices.put((skinningMatrix.set(*jointSkinningMatrix).multiply(objectBase->getTransformMatrix()).getArray()));
				} else {
					fbMatrices.put(objectBase->getTransformMatrix().getArray());
				}
			}
		}
		objectBase->setCurrentInstance(currentInstance);
		rendererBackend->uploadSkinningBufferObject(contextIdx, (*modelSkinningCacheCached->matricesVboIds[contextIdx])[0], fbMatrices.getPosition() * sizeof(float), &fbMatrices);
		rendererBackend->setProgramUniformInteger(contextIdx, uniformMatrixCount, skinningJoints.size());
		rendererBackend->setProgramUniformInteger(contextIdx, uniformInstanceCount, objectBase->enabledInstances);
	}

	//
	rendererBackend->bindSkinningMatricesBufferObject(contextIdx, (*modelSkinningCacheCached->matricesVboIds[contextIdx])[0]);

	// skinning count
	rendererBackend->setProgramUniformInteger(contextIdx, uniformVertexCount, vertices.size());

	// do it so
	rendererBackend->dispatchCompute(
		contextIdx,
		(int)Math::ceil(vertices.size() / 16.0f),
		(int)Math::ceil(objectBase->instances / 16.0f),
		1
	);
}

void SkinningShader::unUseProgram()
{
	if (isRunning == false) return;
	isRunning = false;
	for (auto& skinningContext: contexts) skinningContext.running = false;
	// we are done, do memory barrier
	rendererBackend->memoryBarrier();
}

void SkinningShader::reset() {
	for (const auto& [cacheId, cacheEntry]: cache) {
		Engine::getVBOManager()->removeVBO("skinning_compute_shader." + cacheEntry.id + ".vbos");
	}
	// TODO: Remove vaos
	cache.clear();
}
