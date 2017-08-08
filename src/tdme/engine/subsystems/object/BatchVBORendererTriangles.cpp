// Generated from /tdme/src/tdme/engine/subsystems/object/BatchVBORendererTriangles.java
#include <tdme/engine/subsystems/object/BatchVBORendererTriangles.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/Byte.h>
#include <java/lang/Float.h>
#include <java/nio/ByteBuffer.h>
#include <java/nio/ByteOrder.h>
#include <java/nio/FloatBuffer.h>
#include <java/util/Arrays.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using tdme::engine::subsystems::object::BatchVBORendererTriangles;
using java::lang::Byte;
using java::lang::Float;
using java::lang::String;
using java::lang::StringBuilder;
using java::nio::ByteBuffer;
using java::nio::ByteOrder;
using java::nio::FloatBuffer;
using java::util::Arrays;
using tdme::engine::Engine;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Vector3;

constexpr int32_t BatchVBORendererTriangles::VERTEX_COUNT;
floatArray* BatchVBORendererTriangles::TEXTURECOORDINATE_NONE = new floatArray({0.0f, 0.0f});

BatchVBORendererTriangles::BatchVBORendererTriangles(GLRenderer* renderer, int32_t id) 
{
	this->id = id;
	this->renderer = renderer;
	this->acquired = false;
	this->vertices = 0;
	this->fbVertices = ByteBuffer::allocateDirect(VERTEX_COUNT * 3 * Float::SIZE / Byte::SIZE)->asFloatBuffer();
	this->fbNormals = ByteBuffer::allocateDirect(VERTEX_COUNT * 3 * Float::SIZE / Byte::SIZE)->asFloatBuffer();
	this->fbTextureCoordinates = ByteBuffer::allocateDirect(VERTEX_COUNT * 2 * Float::SIZE / Byte::SIZE)->asFloatBuffer();
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
	if (vboIds == nullptr) {
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO(::java::lang::StringBuilder().append(u"tdme.batchvborenderertriangles."_j)->append(id)->toString(), 3);
		vboIds = vboManaged->getVBOGlIds();
	}
}

void BatchVBORendererTriangles::render()
{
	if (fbVertices->position() == 0 || fbNormals->position() == 0 || fbTextureCoordinates->position() == 0)
		return;

	auto triangles = fbVertices->position() / 3 /*vertices*/ / 3 /*vector components*/ / 4 /* bytes per float*/;
	renderer->uploadBufferObject((*vboIds)[0], fbVertices->position() * Float::SIZE / Byte::SIZE, fbVertices);
	renderer->uploadBufferObject((*vboIds)[1], fbNormals->position() * Float::SIZE / Byte::SIZE, fbNormals);
	renderer->uploadBufferObject((*vboIds)[2], fbTextureCoordinates->position() * Float::SIZE / Byte::SIZE, fbTextureCoordinates);
	renderer->bindVerticesBufferObject((*vboIds)[0]);
	renderer->bindNormalsBufferObject((*vboIds)[1]);
	renderer->bindTextureCoordinatesBufferObject((*vboIds)[2]);
	renderer->drawTrianglesFromBufferObjects(triangles, 0);
}

void BatchVBORendererTriangles::dispose()
{
	if (vboIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO(::java::lang::StringBuilder().append(u"tdme.batchvborenderertriangles."_j)->append(id)->toString());
		vboIds = nullptr;
	}
}

void BatchVBORendererTriangles::clear()
{
	vertices = 0;
	fbVertices->clear();
	fbNormals->clear();
	fbTextureCoordinates->clear();
}

bool BatchVBORendererTriangles::addVertex(Vector3* vertex, Vector3* normal, TextureCoordinate* textureCoordinate)
{
	if (vertices == VERTEX_COUNT)
		return false;

	fbVertices->put(vertex->getArray());
	fbNormals->put(normal->getArray());
	if (textureCoordinate != nullptr) {
		fbTextureCoordinates->put(textureCoordinate->getArray());
	} else {
		fbTextureCoordinates->put(TEXTURECOORDINATE_NONE);
	}
	vertices++;
	return true;
}
