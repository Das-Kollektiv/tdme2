#include <tdme/engine/subsystems/rendering/BatchRendererTriangles.h>

#include <string>

#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/math/Vector3.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::rendering::BatchRendererTriangles;
using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::engine::Engine;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Vector3;

constexpr int32_t BatchRendererTriangles::VERTEX_COUNT;

BatchRendererTriangles::BatchRendererTriangles(Renderer* renderer, int32_t id)
{
	this->id = id;
	this->renderer = renderer;
	this->acquired = false;
	this->vertices = 0;
	this->fbVertices = (fbVerticesByteBuffer = ByteBuffer::allocate(VERTEX_COUNT * 3 * sizeof(float)))->asFloatBuffer();
	this->fbNormals = (fbNormalsByteBuffer = ByteBuffer::allocate(VERTEX_COUNT * 3 * sizeof(float)))->asFloatBuffer();
	this->fbTextureCoordinates = (fbTextureCoordinatesByteBuffer = ByteBuffer::allocate(VERTEX_COUNT * 2 * sizeof(float)))->asFloatBuffer();
	this->fbModelMatrices = (fbModelMatricesByteBuffer = ByteBuffer::allocate(1 * 16 * sizeof(float)))->asFloatBuffer();
	this->fbModelMatrices.put(Matrix4x4().identity().getArray());
	this->fbEffectColorMuls = (fbEffectColorMulsByteBuffer = ByteBuffer::allocate(1 * 4 * sizeof(float)))->asFloatBuffer();
	this->fbEffectColorMuls.put(Color4(1.0f, 1.0f, 1.0f, 1.0f).getArray());
	this->fbEffectColorAdds = (fbEffectColorAddsByteBuffer = ByteBuffer::allocate(1 * 4 * sizeof(float)))->asFloatBuffer();
	this->fbEffectColorAdds.put(Color4(0.0f, 0.0f, 0.0f, 0.0f).getArray());
}

BatchRendererTriangles::~BatchRendererTriangles()
{
	delete fbVerticesByteBuffer;
	delete fbNormalsByteBuffer;
	delete fbTextureCoordinatesByteBuffer;
	delete fbModelMatricesByteBuffer;
	delete fbEffectColorMulsByteBuffer;
	delete fbEffectColorAddsByteBuffer;
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
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO("tdme.batchvborenderertriangles." + to_string(id), 6, false);
		vboIds = vboManaged->getVBOIds();
	}
}

void BatchRendererTriangles::render()
{
	// skip if no vertex data exists
	if (fbVertices.getPosition() == 0 || fbNormals.getPosition() == 0 || fbTextureCoordinates.getPosition() == 0) return;
	// use default context
	auto context = renderer->getDefaultContext();
	// determine triangles count
	auto triangles = fbVertices.getPosition() / 3 /*vertices*/ / 3 /*vector components*/;
	// upload vertices
	renderer->uploadBufferObject(context, (*vboIds)[0], fbVertices.getPosition() * sizeof(float), &fbVertices);
	// upload normals
	renderer->uploadBufferObject(context, (*vboIds)[1], fbNormals.getPosition() * sizeof(float), &fbNormals);
	// upload texture coordinates
	renderer->uploadBufferObject(context, (*vboIds)[2], fbTextureCoordinates.getPosition() * sizeof(float), &fbTextureCoordinates);
	// bind vertices
	renderer->bindVerticesBufferObject(context, (*vboIds)[0]);
	// bind normals
	renderer->bindNormalsBufferObject(context, (*vboIds)[1]);
	// bind texture coordinates
	renderer->bindTextureCoordinatesBufferObject(context, (*vboIds)[2]);
	// handle instanced rendering
	//	TODO: check if to move somewhere else
	if (renderer->isInstancedRenderingAvailable() == true) {
		fbEffectColorMuls.clear();
		fbEffectColorMuls.put(renderer->effectColorMul);
		fbEffectColorAdds.clear();
		fbEffectColorAdds.put(renderer->effectColorAdd);
		renderer->uploadBufferObject(context, (*vboIds)[3], fbModelMatrices.getPosition() * sizeof(float), &fbModelMatrices);
		renderer->bindModelMatricesBufferObject(context, (*vboIds)[3]);
		renderer->uploadBufferObject(context, (*vboIds)[4], fbEffectColorMuls.getPosition() * sizeof(float), &fbEffectColorMuls);
		renderer->bindEffectColorMulsBufferObject(context, (*vboIds)[4]);
		renderer->uploadBufferObject(context, (*vboIds)[5], fbEffectColorAdds.getPosition() * sizeof(float), &fbEffectColorAdds);
		renderer->bindEffectColorAddsBufferObject(context, (*vboIds)[5]);

		// draw
		renderer->drawInstancedTrianglesFromBufferObjects(context, triangles, 0, 1);
	} else {
		// draw
		renderer->drawTrianglesFromBufferObjects(context, triangles, 0);
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
