#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/Plane.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>

using std::array;

using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::Plane;
using tdme::engine::primitives::Sphere;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Frustum class
 * based on http://www.crownandcutlass.com/features/technicaldetails/frustum.html
 * @author Mark Morley, Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Frustum final
{
private:
	GLRenderer* renderer {  };

	// right, left, bottom, top, far, near
	static constexpr int32_t PLANE_RIGHT { 0 };
	static constexpr int32_t PLANE_LEFT { 1 };
	static constexpr int32_t PLANE_BOTTOM { 2 };
	static constexpr int32_t PLANE_TOP { 3 };
	static constexpr int32_t PLANE_FAR { 4 };
	static constexpr int32_t PLANE_NEAR { 5 };

	Matrix4x4 projectionMatrixTransposed {  };
	Matrix4x4 modelViewMatrixTransposed {  };
	Matrix4x4 frustumMatrix {  };

	array<Plane, 6> planes {  };

public:
	/** 
	 * Setups frustum, should be called if frustum did change 
	 */
	void updateFrustum();

	/** 
	 * Checks if given vector is in frustum
	 * @param v
	 * @return visibility
	 */
	inline bool isVisible(const Vector3& v) {
		auto& vector = v.getArray();
		for (auto& p : planes) {
			auto& normal = p.getNormal().getArray();
			if ((normal[0] * vector[0]) + (normal[1] * vector[1]) + (normal[2] * vector[2]) + p.getDistance() <= 0) {
				return false;
			}
		}
		return true;
	}

	/** 
	 * Checks if sphere is in frustum
	 * @param s
	 * @return visibility
	 */
	inline bool isVisible(Sphere* s) {
		auto& center = s->getCenter().getArray();
		auto radius = s->getRadius();
		for (auto& p : planes) {
			auto& normal = p.getNormal().getArray();
			if ((normal[0] * center[0]) + (normal[1] * center[1]) + (normal[2] * center[2]) + p.getDistance() <= -radius) {
				return false;
			}
		}
		return true;
	}

	/** 
	 * Checks if bounding box is in frustum
	 * @param s
	 * @return visibility
	 */
	inline bool isVisible(BoundingBox* b) {
		auto& min = b->getMin().getArray();
		auto& max = b->getMax().getArray();
		auto minX = min[0];
		auto minY = min[1];
		auto minZ = min[2];
		auto maxX = max[0];
		auto maxY = max[1];
		auto maxZ = max[2];
		for (auto& p : planes) {
			auto& normal = p.getNormal().getArray();
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

	/**
	 * Public constructor
	 */
	Frustum(GLRenderer* renderer);
};
