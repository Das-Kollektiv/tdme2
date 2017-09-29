#include <tdme/engine/Frustum.h>

#include <array>

#include <tdme/math/Math.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/Plane.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::array;

using tdme::engine::Frustum;
using tdme::math::Math;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::Plane;
using tdme::engine::primitives::Sphere;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

Frustum::Frustum(GLRenderer* renderer) 
{
	this->renderer = renderer;
}

constexpr int32_t Frustum::PLANE_RIGHT;

constexpr int32_t Frustum::PLANE_LEFT;

constexpr int32_t Frustum::PLANE_BOTTOM;

constexpr int32_t Frustum::PLANE_TOP;

constexpr int32_t Frustum::PLANE_FAR;

constexpr int32_t Frustum::PLANE_NEAR;

void Frustum::updateFrustum()
{
	projectionMatrixTransposed.set(renderer->getProjectionMatrix()).transpose();
	modelViewMatrixTransposed.set(renderer->getModelViewMatrix()).transpose();
	frustumMatrix.set(projectionMatrixTransposed).multiply(modelViewMatrixTransposed);
	auto& data = frustumMatrix.getArray();
	float x, y, z, d, t;
	x = data[12] - data[0];
	y = data[13] - data[1];
	z = data[14] - data[2];
	d = data[15] - data[3];
	t = Math::sqrt((x * x) + (y * y) + (z * z));
	x /= t;
	y /= t;
	z /= t;
	d /= t;
	planes[0].getNormal()->set(x, y, z);
	planes[0].setDistance(d);
	x = data[12] + data[0];
	y = data[13] + data[1];
	z = data[14] + data[2];
	d = data[15] + data[3];
	t = Math::sqrt((x * x) + (y * y) + (z * z));
	x /= t;
	y /= t;
	z /= t;
	d /= t;
	planes[1].getNormal()->set(x, y, z);
	planes[1].setDistance(d);
	x = data[12] + data[4];
	y = data[13] + data[5];
	z = data[14] + data[6];
	d = data[15] + data[7];
	t = Math::sqrt((x * x) + (y * y) + (z * z));
	x /= t;
	y /= t;
	z /= t;
	d /= t;
	planes[2].getNormal()->set(x, y, z);
	planes[2].setDistance(d);
	x = data[12] - data[4];
	y = data[13] - data[5];
	z = data[14] - data[6];
	d = data[15] - data[7];
	t = Math::sqrt((x * x) + (y * y) + (z * z));
	x /= t;
	y /= t;
	z /= t;
	d /= t;
	planes[3].getNormal()->set(x, y, z);
	planes[3].setDistance(d);
	x = data[12] - data[8];
	y = data[13] - data[9];
	z = data[14] - data[10];
	d = data[15] - data[11];
	t = Math::sqrt((x * x) + (y * y) + (z * z));
	x /= t;
	y /= t;
	z /= t;
	d /= t;
	planes[4].getNormal()->set(x, y, z);
	planes[4].setDistance(d);
	x = data[12] + data[8];
	y = data[13] + data[9];
	z = data[14] + data[10];
	d = data[15] + data[11];
	t = Math::sqrt((x * x) + (y * y) + (z * z));
	x /= t;
	y /= t;
	z /= t;
	d /= t;
	planes[5].getNormal()->set(x, y, z);
	planes[5].setDistance(d);
}

bool Frustum::isVisible(Vector3* v)
{
	auto& vector = v->getArray();
	for (auto& p : planes) {
		auto& normal = p.getNormal()->getArray();
		if ((normal[0] * vector[0]) + (normal[1] * vector[1]) + (normal[2] * vector[2]) + p.getDistance() <= 0) {
			return false;
		}
	}
	return true;
}

bool Frustum::isVisible(Sphere* s)
{
	auto& center = s->getCenter()->getArray();
	auto radius = s->getRadius();
	for (auto& p : planes) {
		auto& normal = p.getNormal()->getArray();
		if ((normal[0] * center[0]) + (normal[1] * center[1]) + (normal[2] * center[2]) + p.getDistance() <= -radius) {
			return false;
		}
	}
	return true;
}

bool Frustum::isVisible(BoundingBox* b)
{
	auto& min = b->getMin()->getArray();
	auto& max = b->getMax()->getArray();
	auto minX = min[0];
	auto minY = min[1];
	auto minZ = min[2];
	auto maxX = max[0];
	auto maxY = max[1];
	auto maxZ = max[2];
	for (auto& p : planes) {
		auto& normal = p.getNormal()->getArray();
		auto distance = p.getDistance();
		if ((normal[0] * minX) + (normal[1] * minY) + (normal[2] * minZ) + distance > 0) {
			continue;
		}
		if ((normal[0] * maxX) + (normal[1] * minY) + (normal[2] * minZ) + distance > 0) {
			continue;
		}
		if ((normal[0] * minX) + (normal[1] * maxY) + (normal[2] * minZ) + distance > 0) {
			continue;
		}
		if ((normal[0] * maxX) + (normal[1] * maxY) + (normal[2] * minZ) + distance > 0) {
			continue;
		}
		if ((normal[0] * minX) + (normal[1] * minY) + (normal[2] * maxZ) + distance > 0) {
			continue;
		}
		if ((normal[0] * maxX) + (normal[1] * minY) + (normal[2] * maxZ) + distance > 0) {
			continue;
		}
		if ((normal[0] * minX) + (normal[1] * maxY) + (normal[2] * maxZ) + distance > 0) {
			continue;
		}
		if ((normal[0] * maxX) + (normal[1] * maxY) + (normal[2] * maxZ) + distance > 0) {
			continue;
		}
		return false;
	}
	return true;
}
