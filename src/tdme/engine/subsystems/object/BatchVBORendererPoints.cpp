#include <tdme/engine/subsystems/object/BatchVBORendererPoints.h>

#include <string>

#include <java/lang/Byte.h>
#include <java/lang/Float.h>
#include <java/nio/ByteBuffer.h>
#include <java/nio/ByteOrder.h>
#include <java/nio/FloatBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/object/TransparentRenderPoint.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using std::wstring;
using std::to_wstring;

using tdme::engine::subsystems::object::BatchVBORendererPoints;

using java::lang::Byte;
using java::lang::Float;
using java::nio::ByteBuffer;
using java::nio::ByteOrder;
using java::nio::FloatBuffer;
using tdme::engine::Engine;
using tdme::engine::model::Color4;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::object::TransparentRenderPoint;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Vector3;

constexpr int32_t BatchVBORendererPoints::VERTEX_COUNT;

BatchVBORendererPoints::BatchVBORendererPoints(GLRenderer* renderer, int32_t id) 
{
	this->id = id;
	this->renderer = renderer;
	this->acquired = false;
	fbVertices = ByteBuffer::allocateDirect(VERTEX_COUNT * 3 * Float::SIZE / Byte::SIZE)->asFloatBuffer();
	fbColors = ByteBuffer::allocateDirect(VERTEX_COUNT * 4 * Float::SIZE / Byte::SIZE)->asFloatBuffer();
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
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO(L"tdme.batchvborendererpoints." + to_wstring(id), 2);
		vboIds = vboManaged->getVBOGlIds();
	}
}

void BatchVBORendererPoints::render()
{
	if (fbVertices->position() == 0 || fbColors->position() == 0)
		return;

	auto points = fbVertices->position() / 3 /* 3 components */;
	renderer->uploadBufferObject((*vboIds)[0], fbVertices->position() * Float::SIZE / Byte::SIZE, fbVertices);
	renderer->uploadBufferObject((*vboIds)[1], fbColors->position() * Float::SIZE / Byte::SIZE, fbColors);
	renderer->bindVerticesBufferObject((*vboIds)[0]);
	renderer->bindColorsBufferObject((*vboIds)[1]);
	renderer->drawPointsFromBufferObjects(points, 0);
}

void BatchVBORendererPoints::dispose()
{
	if (vboIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO(L"tdme.batchvborendererpoints." + to_wstring(id));
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
	fbVertices->put(point->point.getArray());
	fbColors->put(point->color.getArray());
}
