#include <tdme/engine/subsystems/rendering/BatchRendererTriangles.h>

#include <array>
#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/FloatBuffer.h>

using std::array;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::vector;

using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::rendering::BatchRendererTriangles;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::engine::Engine;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;

constexpr int32_t BatchRendererTriangles::VERTEX_COUNT;

BatchRendererTriangles::BatchRendererTriangles(RendererBackend* rendererBackend, int32_t id)
{
	this->id = id;
	this->rendererBackend = rendererBackend;
	this->acquired = false;
	this->vertices = 0;
	this->fbVertices = (fbVerticesByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(VERTEX_COUNT * 3 * sizeof(float))))->asFloatBuffer();
	this->fbNormals = (fbNormalsByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(VERTEX_COUNT * 3 * sizeof(float))))->asFloatBuffer();
	this->fbTextureCoordinates = (fbTextureCoordinatesByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(VERTEX_COUNT * 2 * sizeof(float))))->asFloatBuffer();
	this->fbModelMatrices = (fbModelMatricesByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(1 * 16 * sizeof(float))))->asFloatBuffer();
	this->fbModelMatrices.put(Matrix4x4().identity().getArray());
	this->fbEffectColorMuls = (fbEffectColorMulsByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(1 * 4 * sizeof(float))))->asFloatBuffer();
	this->fbEffectColorMuls.put(Color4(1.0f, 1.0f, 1.0f, 1.0f).getArray());
	this->fbEffectColorAdds = (fbEffectColorAddsByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(1 * 4 * sizeof(float))))->asFloatBuffer();
	this->fbEffectColorAdds.put(Color4(0.0f, 0.0f, 0.0f, 0.0f).getArray());
}

BatchRendererTriangles::~BatchRendererTriangles()
{
}

bool BatchRendererTriangles::isAcquired()
{
	return acquired;
}

bool BatchRendererTriangles::acquire()
{
	if (acquired == true)
		return false;

	acquired = true;
	return true;
}

void BatchRendererTriangles::release()
{
	acquired = false;
}

void BatchRendererTriangles::initialize()
{
	// initialize if not yet done
	if (vboIds == nullptr) {
		auto created = false;
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO("tdme.batchvborenderertriangles." + to_string(id), 6, false, false, created);
		vboIds = vboManaged->getVBOIds();
	}
}

void BatchRendererTriangles::render()
{
	// skip if no vertex data exists
	if (fbVertices.getPosition() == 0 || fbNormals.getPosition() == 0 || fbTextureCoordinates.getPosition() == 0) return;
	// use default context
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;
	// determine triangles count
	auto triangles = fbVertices.getPosition() / 3 /*vertices*/ / 3 /*vector components*/;
	// upload vertices
	rendererBackend->uploadBufferObject(contextIdx, (*vboIds)[0], fbVertices.getPosition() * sizeof(float), &fbVertices);
	// upload normals
	rendererBackend->uploadBufferObject(contextIdx, (*vboIds)[1], fbNormals.getPosition() * sizeof(float), &fbNormals);
	// upload texture coordinates
	rendererBackend->uploadBufferObject(contextIdx, (*vboIds)[2], fbTextureCoordinates.getPosition() * sizeof(float), &fbTextureCoordinates);
	// bind vertices
	rendererBackend->bindVerticesBufferObject(contextIdx, (*vboIds)[0]);
	// bind normals
	rendererBackend->bindNormalsBufferObject(contextIdx, (*vboIds)[1]);
	// bind texture coordinates
	rendererBackend->bindTextureCoordinatesBufferObject(contextIdx, (*vboIds)[2]);
	// handle instanced rendering
	//	TODO: check if to move somewhere else
	if (rendererBackend->isInstancedRenderingAvailable() == true) {
		fbEffectColorMuls.clear();
		fbEffectColorMuls.put(rendererBackend->getEffectColorMul(contextIdx));
		fbEffectColorAdds.clear();
		fbEffectColorAdds.put(rendererBackend->getEffectColorAdd(contextIdx));
		rendererBackend->uploadBufferObject(contextIdx, (*vboIds)[3], fbModelMatrices.getPosition() * sizeof(float), &fbModelMatrices);
		rendererBackend->bindModelMatricesBufferObject(contextIdx, (*vboIds)[3]);
		rendererBackend->uploadBufferObject(contextIdx, (*vboIds)[4], fbEffectColorMuls.getPosition() * sizeof(float), &fbEffectColorMuls);
		rendererBackend->bindEffectColorMulsBufferObject(contextIdx, (*vboIds)[4], 1);
		rendererBackend->uploadBufferObject(contextIdx, (*vboIds)[5], fbEffectColorAdds.getPosition() * sizeof(float), &fbEffectColorAdds);
		rendererBackend->bindEffectColorAddsBufferObject(contextIdx, (*vboIds)[5], 1);

		// draw
		rendererBackend->drawInstancedTrianglesFromBufferObjects(contextIdx, triangles, 0, 1);
	} else {
		// draw
		rendererBackend->drawTrianglesFromBufferObjects(contextIdx, triangles, 0);
	}
}

void BatchRendererTriangles::dispose()
{
	if (vboIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO("tdme.batchvborenderertriangles." + to_string(id));
		vboIds = nullptr;
	}
}

void BatchRendererTriangles::clear()
{
	vertices = 0;
	fbVertices.clear();
	fbNormals.clear();
	fbTextureCoordinates.clear();
}
