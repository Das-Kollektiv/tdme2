#pragma once

#include <array>

#include <tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/Plane.h>
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

public: /* protected */
	static constexpr int32_t PLANE_RIGHT { 0 };
	static constexpr int32_t PLANE_LEFT { 1 };
	static constexpr int32_t PLANE_BOTTOM { 2 };
	static constexpr int32_t PLANE_TOP { 3 };
	static constexpr int32_t PLANE_FAR { 4 };
	static constexpr int32_t PLANE_NEAR { 5 };

public: /* package */
	Matrix4x4 projectionMatrixTransposed {  };
	Matrix4x4 modelViewMatrixTransposed {  };
	Matrix4x4 frustumMatrix {  };

private:
	array<Plane, 6> planes {  };

public:
	/** 
	 * Setups frustum, should be called if frustum did change 
	 * @param gl
	 */
	void updateFrustum();

	/** 
	 * Checks if given vector is in frustum
	 * @param v
	 * @return visibility
	 */
	bool isVisible(const Vector3& v);

	/** 
	 * Checks if sphere is in frustum
	 * @param s
	 * @return visibility
	 */
	bool isVisible(Sphere* s);

	/** 
	 * Checks if bounding box is in frustum
	 * @param s
	 * @return visibility
	 */
	bool isVisible(BoundingBox* b);

	/**
	 * Public constructor
	 */
	Frustum(GLRenderer* renderer);
};
