#include <tdme/engine/subsystems/object/BatchVBORendererTriangles.h>

#include <string>

#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Vector3.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::object::BatchVBORendererTriangles;
using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::engine::Engine;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Vector3;

constexpr int32_t BatchVBORendererTriangles::VERTEX_COUNT;
array<float, 2> BatchVBORendererTriangles::TEXTURECOORDINATE_NONE = {{ 0.0f, 0.0f }};

BatchVBORendererTriangles::BatchVBORendererTriangles(GLRenderer* renderer, int32_t id) 
{
	this->id = id;
	this->renderer = renderer;
	this->acquired = false;
	this->vertices = 0;
	this->fbVertices = (fbVerticesByteBuffer = ByteBuffer::allocate(VERTEX_COUNT * 3 * sizeof(float)))->asFloatBuffer();
	this->fbNormals = (fbNormalsByteBuffer = ByteBuffer::allocate(VERTEX_COUNT * 3 * sizeof(float)))->asFloatBuffer();
	this->fbTextureCoordinates = (fbTextureCoordinatesByteBuffer = ByteBuffer::allocate(VERTEX_COUNT * 2 * sizeof(float)))->asFloatBuffer();
}

BatchVBORendererTriangles::~BatchVBORendererTriangles()
{
	delete fbVerticesByteBuffer;
	delete fbNormalsByteBuffer;
	delete fbTextureCoordinatesByteBuffer;
}

bool BatchVBORendererTriangles::isAcquired()
{
	return acquired;
}

bool BatchVBORendererTriangles::acquire()
{
	if (acquired == true)
		return false;

	acquired = true;
	return true;
}

void BatchVBORendererTriangles::release()
{
	acquired = false;
}

void BatchVBORendererTriangles::initialize()
{
	// initialize if not yet done
	if (vboIds == nullptr) {
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO("tdme.batchvborenderertriangles." + to_string(id), 3);
		vboIds = vboManaged->getVBOGlIds();
	}
}

void BatchVBORendererTriangles::render()
{
	// skip if no vertex data exists
	if (fbVertices.getPosition() == 0 || fbNormals.getPosition() == 0 || fbTextureCoordinates.getPosition() == 0)
		return;
	// determine triangles count
	auto triangles = fbVertices.getPosition() / 3 /*vertices*/ / 3 /*vector components*/;
	// upload vertices
	renderer->uploadBufferObject((*vboIds)[0], fbVertices.getPosition() * sizeof(float), &fbVertices);
	// upload normals
	renderer->uploadBufferObject((*vboIds)[1], fbNormals.getPosition() * sizeof(float), &fbNormals);
	// upload texture coordinates
	renderer->uploadBufferObject((*vboIds)[2], fbTextureCoordinates.getPosition() * sizeof(float), &fbTextureCoordinates);
	// bind vertices
	renderer->bindVerticesBufferObject((*vboIds)[0]);
	// bind normals
	renderer->bindNormalsBufferObject((*vboIds)[1]);
	// bind texture coordinates
	renderer->bindTextureCoordinatesBufferObject((*vboIds)[2]);
	// draw
	renderer->drawTrianglesFromBufferObjects(triangles, 0);
}

void BatchVBORendererTriangles::dispose()
{
	if (vboIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO("tdme.batchvborenderertriangles." + to_string(id));
		vboIds = nullptr;
	}
}

void BatchVBORendererTriangles::clear()
{
	vertices = 0;
	fbVertices.clear();
	fbNormals.clear();
	fbTextureCoordinates.clear();
}
