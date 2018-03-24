#include <tdme/engine/subsystems/rendering/BatchVBORendererPoints.h>

#include <string>

#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Vector3.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::rendering::BatchVBORendererPoints;

using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::engine::Engine;
using tdme::engine::model::Color4;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Vector3;

constexpr int32_t BatchVBORendererPoints::POINT_COUNT;

BatchVBORendererPoints::BatchVBORendererPoints(GLRenderer* renderer, int32_t id) 
{
	this->id = id;
	this->renderer = renderer;
	this->acquired = false;
	fbVertices = (fbVerticesByteBuffer = ByteBuffer::allocate(POINT_COUNT * 3 * sizeof(float)))->asFloatBuffer();
	fbColors = (fbColorsByteBuffer = ByteBuffer::allocate(POINT_COUNT * 4 * sizeof(float)))->asFloatBuffer();
}

BatchVBORendererPoints::~BatchVBORendererPoints()
{
	delete fbVerticesByteBuffer;
	delete fbColorsByteBuffer;
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
	// initialize if not yet done
	if (vboIds == nullptr) {
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO("tdme.batchvborendererpoints." + to_string(id), 2);
		vboIds = vboManaged->getVBOGlIds();
	}
}

void BatchVBORendererPoints::render()
{
	// skip if no vertex data exists
	if (fbVertices.getPosition() == 0 || fbColors.getPosition() == 0)
		return;

	// determine point count
	auto points = fbVertices.getPosition() / 3 /* 3 components */;
	// upload vertices
	renderer->uploadBufferObject((*vboIds)[0], fbVertices.getPosition() * sizeof(float), &fbVertices);
	// upload colors
	renderer->uploadBufferObject((*vboIds)[1], fbColors.getPosition() * sizeof(float), &fbColors);
	// bind vertices
	renderer->bindVerticesBufferObject((*vboIds)[0]);
	// bind colors
	renderer->bindColorsBufferObject((*vboIds)[1]);
	// draw
	renderer->drawPointsFromBufferObjects(points, 0);
}

void BatchVBORendererPoints::dispose()
{
	if (vboIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO("tdme.batchvborendererpoints." + to_string(id));
		vboIds = nullptr;
	}
}

void BatchVBORendererPoints::clear()
{
	fbVertices.clear();
	fbColors.clear();
}

void BatchVBORendererPoints::addPoint(TransparentRenderPoint* point)
{
	fbVertices.put(point->point.getArray());
	fbColors.put(point->color.getArray());
}
