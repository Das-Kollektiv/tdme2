#include <tdme/engine/primitives/Triangle.h>

#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>

using tdme::engine::primitives::Triangle;

using tdme::math::Math;
using tdme::math::Vector3;

Triangle::Triangle()
{
	this->vertices.resize(3);
}

Triangle::Triangle(const Vector3& vertex0, const Vector3& vertex1, const Vector3& vertex2)
{
	this->vertices.resize(3);
	this->vertices[0].set(vertex0);
	this->vertices[1].set(vertex1);
	this->vertices[2].set(vertex2);
}

void Triangle::computeClosestPointOnBoundingVolume(const Vector3& point, Vector3& closestPoint) const {
	// see: http://www.gamedev.net/topic/552906-closest-point-on-triangle/
	Vector3 edge0;
	Vector3 edge1;
	Vector3 v0Point;
	edge0.set(vertices[1]).sub(vertices[0]);
	edge1.set(vertices[2]).sub(vertices[0]);
	v0Point.set(vertices[0]).sub(point);
	auto a = Vector3::computeDotProduct(edge0, edge0);
	auto b = Vector3::computeDotProduct(edge0, edge1);
	auto c = Vector3::computeDotProduct(edge1, edge1);
	auto d = Vector3::computeDotProduct(edge0, v0Point);
	auto e = Vector3::computeDotProduct(edge1, v0Point);
	auto det = a * c - b * b;
	auto s = b * e - c * d;
	auto t = b * d - a * e;
	if (s + t < det) {
		if (s < 0.0f) {
			if (t < 0.0f) {
				if (d < 0.0f) {
					s = Math::clamp(-d / a, 0.0f, 1.0f);
					t = 0.0f;
				} else {
					s = 0.0f;
					t = Math::clamp(-e / c, 0.0f, 1.0f);
				}
			} else {
				s = 0.0f;
				t = Math::clamp(-e / c, 0.0f, 1.0f);
			}
		} else if (t < 0.0f) {
			s = Math::clamp(-d / a, 0.0f, 1.0f);
			t = 0.0f;
		} else {
			auto invDet = 1.0f / det;
			s *= invDet;
			t *= invDet;
		}
	} else {
		if (s < 0.0f) {
			auto tmp0 = b + d;
			auto tmp1 = c + e;
			if (tmp1 > tmp0) {
				auto numer = tmp1 - tmp0;
				auto denom = a - 2 * b + c;
				s = Math::clamp(numer / denom, 0.0f, 1.0f);
				t = 1 - s;
			} else {
				t = Math::clamp(-e / c, 0.0f, 1.0f);
				s = 0.0f;
			}
		} else if (t < 0.0f) {
			if (a + d > b + e) {
				auto numer = c + e - b - d;
				auto denom = a - 2 * b + c;
				s = Math::clamp(numer / denom, 0.0f, 1.0f);
				t = 1 - s;
			} else {
				s = Math::clamp(-e / c, 0.0f, 1.0f);
				t = 0.0f;
			}
		} else {
			auto numer = c + e - b - d;
			auto denom = a - 2 * b + c;
			s = Math::clamp(numer / denom, 0.0f, 1.0f);
			t = 1.0f - s;
		}
	}
	closestPoint.set(vertices[0]).add(edge0.scale(s)).add(edge1.scale(t));
}
