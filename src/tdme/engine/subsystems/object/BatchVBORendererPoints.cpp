// Generated from /tdme/src/tdme/engine/subsystems/object/BatchVBORendererPoints.java
#include <tdme/engine/subsystems/object/BatchVBORendererPoints.h>

#include <java/lang/Byte.h>
#include <java/lang/Float.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/nio/ByteBuffer.h>
#include <java/nio/ByteOrder.h>
#include <java/nio/FloatBuffer.h>
#include <java/util/Arrays.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/object/TransparentRenderPoint.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using tdme::engine::subsystems::object::BatchVBORendererPoints;
using java::lang::Byte;
using java::lang::Float;
using java::lang::String;
using java::lang::StringBuilder;
using java::nio::ByteBuffer;
using java::nio::ByteOrder;
using java::nio::FloatBuffer;
using java::util::Arrays;
using tdme::engine::Engine;
using tdme::engine::model::Color4;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::object::TransparentRenderPoint;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Vector3;

BatchVBORendererPoints::BatchVBORendererPoints(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

BatchVBORendererPoints::BatchVBORendererPoints(GLRenderer* renderer, int32_t id) 
	: BatchVBORendererPoints(*static_cast< ::default_init_tag* >(0))
{
	ctor(renderer,id);
}

void BatchVBORendererPoints::init()
{
	fbVertices = ByteBuffer::allocateDirect(VERTEX_COUNT * 3 * Float::SIZE / Byte::SIZE)->asFloatBuffer();
	fbColors = ByteBuffer::allocateDirect(VERTEX_COUNT * 4 * Float::SIZE / Byte::SIZE)->asFloatBuffer();
}

int32_t BatchVBORendererPoints::VERTEX_COUNT;

void BatchVBORendererPoints::ctor(GLRenderer* renderer, int32_t id)
{
	super::ctor();
	init();
	this->id = id;
	this->renderer = renderer;
	this->acquired = false;
}

bool BatchVBORendererPoints::isAcquired()
{
	return acquired;
}

bool BatchVBORendererPoints::acquire()
{
	if (acquired == true)
		return false;

	acquired = true;
	return true;
}

void BatchVBORendererPoints::release()
{
	acquired = false;
}

void BatchVBORendererPoints::initialize()
{
	if (vboIds == nullptr) {
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO(::java::lang::StringBuilder().append(u"tdme.batchvborendererpoints."_j)->append(id)->toString(), 2);
		vboIds = vboManaged->getVBOGlIds();
	}
}

void BatchVBORendererPoints::render()
{
	// fbVertices->flip();
	// fbColors->flip();
	if (fbVertices->limit() == 0 || fbColors->limit() == 0)
		return;

	auto points = fbVertices->limit() / 3;
	renderer->uploadBufferObject((*vboIds)[0], fbVertices->limit() * Float::SIZE / Byte::SIZE, fbVertices);
	renderer->uploadBufferObject((*vboIds)[1], fbColors->limit() * Float::SIZE / Byte::SIZE, fbColors);
	renderer->bindVerticesBufferObject((*vboIds)[0]);
	renderer->bindColorsBufferObject((*vboIds)[1]);
	renderer->drawPointsFromBufferObjects(points, 0);
}

void BatchVBORendererPoints::dispose()
{
	if (vboIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO(::java::lang::StringBuilder().append(u"tdme.batchvborendererpoints."_j)->append(id)->toString());
		vboIds = nullptr;
	}
}

void BatchVBORendererPoints::clear()
{
	fbVertices->clear();
	fbColors->clear();
}

void BatchVBORendererPoints::addPoint(TransparentRenderPoint* point)
{
	fbVertices->put(point->point->getArray());
	fbColors->put(point->color->getArray());
}

String* BatchVBORendererPoints::toString()
{
	return ::java::lang::StringBuilder().append(u"BatchVBORenderer [vboIds="_j)->append(Arrays::toString(vboIds))
		->append(u", id="_j)
		->append(id)
		->append(u", acquired="_j)
		->append(acquired)
		->append(u", fbVertices="_j)
		->append(fbVertices->position())
		->append(u", fbNormals="_j)
		->append(fbColors->position())
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* BatchVBORendererPoints::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.BatchVBORendererPoints", 52);
    return c;
}

void BatchVBORendererPoints::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		VERTEX_COUNT = 32768;
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* BatchVBORendererPoints::getClass0()
{
	return class_();
}

