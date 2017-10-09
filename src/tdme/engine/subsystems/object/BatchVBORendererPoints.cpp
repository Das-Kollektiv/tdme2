#include <tdme/engine/subsystems/object/BatchVBORendererPoints.h>

#include <string>

#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/object/TransparentRenderPoint.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Vector3.h>

using std::wstring;
using std::to_wstring;

using tdme::engine::subsystems::object::BatchVBORendererPoints;

using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
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
	fbVertices = ByteBuffer::allocate(VERTEX_COUNT * 3 * sizeof(float))->asFloatBuffer();
	fbColors = ByteBuffer::allocate(VERTEX_COUNT * 4 * sizeof(float))->asFloatBuffer();
}

BatchVBORendererPoints::~BatchVBORendererPoints()
{
	delete fbVertices;
	delete fbColors;
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
	if (fbVertices->getPosition() == 0 || fbColors->getPosition() == 0)
		return;

	auto points = fbVertices->getPosition() / 3 /* 3 components */;
	renderer->uploadBufferObject((*vboIds)[0], fbVertices->getPosition() * sizeof(float), fbVertices);
	renderer->uploadBufferObject((*vboIds)[1], fbColors->getPosition() * sizeof(float), fbColors);
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
