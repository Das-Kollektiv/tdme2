#include <tdme/engine/subsystems/rendering/BatchRendererPoints.h>

#include <string>

#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/math/Vector3.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::rendering::BatchRendererPoints;

using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::engine::Engine;
using tdme::engine::model::Color4;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Vector3;

constexpr int32_t BatchRendererPoints::POINT_COUNT;

BatchRendererPoints::BatchRendererPoints(Renderer* renderer, int32_t id)
{
	this->id = id;
	this->renderer = renderer;
	this->acquired = false;
	fbVertices = (fbVerticesByteBuffer = ByteBuffer::allocate(POINT_COUNT * 3 * sizeof(float)))->asFloatBuffer();
	fbColors = (fbColorsByteBuffer = ByteBuffer::allocate(POINT_COUNT * 4 * sizeof(float)))->asFloatBuffer();
}

BatchRendererPoints::~BatchRendererPoints()
{
	delete fbVerticesByteBuffer;
	delete fbColorsByteBuffer;
}

void BatchRendererPoints::initialize()
{
	// initialize if not yet done
	if (vboIds == nullptr) {
		auto created = false;
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO("tdme.batchvborendererpoints." + to_string(id), 2, false, false, created);
		vboIds = vboManaged->getVBOIds();
	}
}

void BatchRendererPoints::render(void* context)
{
	// skip if no vertex data exists
	if (fbVertices.getPosition() == 0 || fbColors.getPosition() == 0)
		return;

	// determine point count
	auto points = fbVertices.getPosition() / 3 /* 3 components */;
	// upload vertices
	renderer->uploadBufferObject(context, (*vboIds)[0], fbVertices.getPosition() * sizeof(float), &fbVertices);
	// upload colors
	renderer->uploadBufferObject(context, (*vboIds)[1], fbColors.getPosition() * sizeof(float), &fbColors);
	// bind vertices
	renderer->bindVerticesBufferObject(context, (*vboIds)[0]);
	// bind colors
	renderer->bindColorsBufferObject(context, (*vboIds)[1]);
	// draw
	renderer->drawPointsFromBufferObjects(context, points, 0);
}

void BatchRendererPoints::dispose()
{
	if (vboIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO("tdme.batchvborendererpoints." + to_string(id));
		vboIds = nullptr;
	}
}

void BatchRendererPoints::clear()
{
	fbVertices.clear();
	fbColors.clear();
}
