#include <tdme/engine/subsystems/skinning/SkinningShader.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/engine/subsystems/renderer/GL3Renderer.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupVBORenderer.h>
#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>
#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/IntBuffer.h>
#include <tdme/utils/FloatBuffer.h>

using std::copy;
using std::begin;
using std::end;
using std::to_string;
using std::string;

using tdme::engine::subsystems::skinning::SkinningShader;

using tdme::engine::Engine;
using tdme::engine::model::Group;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Model;
using tdme::engine::model::Skinning;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::renderer::GL3Renderer;
using tdme::engine::subsystems::rendering::Object3DGroupMesh;
using tdme::engine::subsystems::rendering::Object3DGroupVBORenderer;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::utils::ByteBuffer;
using tdme::utils::Console;
using tdme::utils::IntBuffer;
using tdme::utils::FloatBuffer;

SkinningShader::SkinningShader(GLRenderer* renderer)
{
	this->renderer = renderer;
	isRunning = false;
	initialized = false;
}

bool SkinningShader::isInitialized()
{
	return initialized;
}

void SkinningShader::initialize()
{
	auto rendererVersion = renderer->getGLVersion();

	// shader
	shaderId = renderer->loadShader(
		renderer->SHADER_COMPUTE_SHADER,
		"shader/" + rendererVersion + "/skinning",
		"skinning.c"
	);
	if (shaderId == 0) return;

	// create, attach and link program
	programId = renderer->createProgram();
	renderer->attachShaderToProgram(programId, shaderId);

	// link program
	if (renderer->linkProgram(programId) == false) return;

	//
	uniformSkinningCount = renderer->getProgramUniformLocation(programId, "skinningCount");
	if (uniformSkinningCount == -1) return;

	//
	initialized = true;
}

void SkinningShader::useProgram()
{
	isRunning = true;
	renderer->useProgram(programId);
}

void SkinningShader::computeSkinning(Object3DGroupMesh* object3DGroupMesh)
{
	if (isRunning == false) useProgram();

	// vbo base ids
	auto vboBaseIds = object3DGroupMesh->object3DGroupVBORenderer->vboBaseIds;

	//
	ModelSkinningCache* modelSkinningCacheCached = nullptr;
	auto group = object3DGroupMesh->group;
	auto& vertices = *group->getVertices();
	auto id = group->getModel()->getId() + "." + group->getId();
	auto cacheIt = cache.find(id);
	if (cacheIt == cache.end()) {
		ModelSkinningCache modelSkinningCache;

		auto skinning = group->getSkinning();
		auto& verticesJointsWeights = *skinning->getVerticesJointsWeights();
		auto& weights = *skinning->getWeights();

		// vbo
		auto vboManaged = Engine::getVBOManager()->addVBO("skinning_compute_shader." + id + ".vbos", 6);
		modelSkinningCache.vboIds = vboManaged->getVBOGlIds();

		// vertices
		{
			object3DGroupMesh->setupVerticesBuffer(renderer, (*modelSkinningCache.vboIds)[0]);
		}

		// normals
		{
			object3DGroupMesh->setupNormalsBuffer(renderer, (*modelSkinningCache.vboIds)[1]);
		}

		{
			// vertices joints
			auto ibVerticesJoints = ObjectBuffer::getByteBuffer(vertices.size() * 1 * sizeof(int))->asIntBuffer();
			for (int groupVertexIndex = 0; groupVertexIndex < vertices.size(); groupVertexIndex++) {
				int vertexJoints = verticesJointsWeights[groupVertexIndex].size();
				// put number of joints
				ibVerticesJoints.put((int)vertexJoints);
			}
			renderer->uploadSkinningBufferObject((*modelSkinningCache.vboIds)[2], ibVerticesJoints.getPosition() * sizeof(int), &ibVerticesJoints);
		}

		{
			// vertices joints indices
			auto ibVerticesVertexJointsIdxs = ObjectBuffer::getByteBuffer(vertices.size() * 4 * sizeof(float))->asIntBuffer();
			for (int groupVertexIndex = 0; groupVertexIndex < vertices.size(); groupVertexIndex++) {
				auto& vertexJointsWeight = verticesJointsWeights[groupVertexIndex];
				// vertex joint idx 1..4
				for (int i = 0; i < 4; i++) {
					auto jointIndex = i < vertexJointsWeight.size()?vertexJointsWeight[i].getJointIndex():-1;
					ibVerticesVertexJointsIdxs.put((int)jointIndex);
				}
			}
			renderer->uploadSkinningBufferObject((*modelSkinningCache.vboIds)[3], ibVerticesVertexJointsIdxs.getPosition() * sizeof(int), &ibVerticesVertexJointsIdxs);
		}

		{
			// vertices joints weights
			auto fbVerticesVertexJointsWeights = ObjectBuffer::getByteBuffer(vertices.size() * 4 * sizeof(float))->asFloatBuffer();
			for (int groupVertexIndex = 0; groupVertexIndex < vertices.size(); groupVertexIndex++) {
				auto& vertexJointsWeight = verticesJointsWeights[groupVertexIndex];
				// vertex joint weight 1..4
				for (int i = 0; i < 4; i++) {
					fbVerticesVertexJointsWeights.put(static_cast<float>(i < vertexJointsWeight.size()?weights[vertexJointsWeight[i].getWeightIndex()]:0.0f));
				}
			}
			renderer->uploadSkinningBufferObject((*modelSkinningCache.vboIds)[4], fbVerticesVertexJointsWeights.getPosition() * sizeof(float), &fbVerticesVertexJointsWeights);
		}

		// add to cache
		cache[id] = modelSkinningCache;
		modelSkinningCacheCached = &cache[id];
	} else {
		modelSkinningCacheCached = &cacheIt->second;
	}

	// upload matrices
	{
		auto skinning = group->getSkinning();
		auto skinningJoints = skinning->getJoints();
		auto fbMatrices = ObjectBuffer::getByteBuffer(skinningJoints->size() * 16 * sizeof(float))->asFloatBuffer();
		for (auto& joint: *skinningJoints) {
			fbMatrices.put(object3DGroupMesh->skinningMatrices->find(joint.getGroupId())->second->getArray());
		}
		renderer->uploadSkinningBufferObject((*modelSkinningCacheCached->vboIds)[5], fbMatrices.getPosition() * sizeof(float), &fbMatrices);
	}

	// bind
	renderer->bindSkinningVerticesBufferObject((*modelSkinningCacheCached->vboIds)[0]);
	renderer->bindSkinningNormalsBufferObject((*modelSkinningCacheCached->vboIds)[1]);
	renderer->bindSkinningVertexJointsBufferObject((*modelSkinningCacheCached->vboIds)[2]);
	renderer->bindSkinningVertexJointIdxsBufferObject((*modelSkinningCacheCached->vboIds)[3]);
	renderer->bindSkinningVertexJointWeightsBufferObject((*modelSkinningCacheCached->vboIds)[4]);
	renderer->bindSkinningMatricesBufferObject((*modelSkinningCacheCached->vboIds)[5]);

	// bind output / result buffers
	renderer->bindSkinningVerticesResultBufferObject((*vboBaseIds)[1]);
	renderer->bindSkinningNormalsResultBufferObject((*vboBaseIds)[2]);

	// skinning count
	renderer->setProgramUniformInteger(uniformSkinningCount, vertices.size());

	// do it so
	renderer->dispatchCompute((int)Math::ceil(vertices.size() / 16.0f), 1, 1);
}

void SkinningShader::unUseProgram()
{
	isRunning = false;
	// we are done, do memory barrier
	renderer->memoryBarrier();
}

void SkinningShader::reset() {
	for (auto& modelSkinningCacheIt: cache) {
		Engine::getVBOManager()->removeVBO("skinning_compute_shader." + modelSkinningCacheIt.second.id + ".vbos");
	}
	cache.clear();
}
