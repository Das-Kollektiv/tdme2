// Generated from /tdme/src/tdme/engine/subsystems/object/BatchVBORendererTriangles.java
#include <tdme/engine/subsystems/object/BatchVBORendererTriangles.h>

#include <java/lang/Byte.h>
#include <java/lang/Float.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
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

BatchVBORendererTriangles::BatchVBORendererTriangles(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

BatchVBORendererTriangles::BatchVBORendererTriangles(GLRenderer* renderer, int32_t id) 
	: BatchVBORendererTriangles(*static_cast< ::default_init_tag* >(0))
{
	ctor(renderer,id);
}

void BatchVBORendererTriangles::init()
{
	vertices = 0;
	fbVertices = ByteBuffer::allocateDirect(VERTEX_COUNT * 3 * Float::SIZE / Byte::SIZE)->asFloatBuffer();
	fbNormals = ByteBuffer::allocateDirect(VERTEX_COUNT * 3 * Float::SIZE / Byte::SIZE)->asFloatBuffer();
	fbTextureCoordinates = ByteBuffer::allocateDirect(VERTEX_COUNT * 2 * Float::SIZE / Byte::SIZE)->asFloatBuffer();
}

int32_t BatchVBORendererTriangles::VERTEX_COUNT;

floatArray* BatchVBORendererTriangles::TEXTURECOORDINATE_NONE;

void BatchVBORendererTriangles::ctor(GLRenderer* renderer, int32_t id)
{
	super::ctor();
	init();
	this->id = id;
	this->renderer = renderer;
	this->acquired = false;
	this->vertices = 0;
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
	// fbVertices->flip();
	// fbNormals->flip();
	// fbTextureCoordinates->flip();
	if (fbVertices->position() == 0 || fbNormals->position() == 0 || fbTextureCoordinates->position() == 0)
		return;

	auto triangles = fbVertices->position() / 3 / 3;
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

String* BatchVBORendererTriangles::toString()
{
	return ::java::lang::StringBuilder().append(u"BatchVBORenderer [vboIds="_j)->append(Arrays::toString(vboIds))
		->append(u", id="_j)
		->append(id)
		->append(u", acquired="_j)
		->append(acquired)
		->append(u", fbVertices="_j)
		->append(fbVertices->position())
		->append(u", fbNormals="_j)
		->append(fbNormals->position())
		->append(u", fbTextureCoordinates="_j)
		->append(fbTextureCoordinates->position())
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* BatchVBORendererTriangles::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.BatchVBORendererTriangles", 55);
    return c;
}

void BatchVBORendererTriangles::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		VERTEX_COUNT = 1024 * 3;
		TEXTURECOORDINATE_NONE = (new floatArray({
			0.0f,
			0.0f
		}));
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* BatchVBORendererTriangles::getClass0()
{
	return class_();
}

