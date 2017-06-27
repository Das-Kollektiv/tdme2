// Generated from /tdme/src/tdme/engine/Frustum.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::Plane;
using tdme::engine::primitives::Sphere;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace primitives {
typedef ::SubArray< ::tdme::engine::primitives::Plane, ::java::lang::ObjectArray > PlaneArray;
}  // namespace primitives
}  // namespace engine
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::engine::primitives::PlaneArray;

struct default_init_tag;

/** 
 * Frustum class
 * based on http://www.crownandcutlass.com/features/technicaldetails/frustum.html
 * @author Mark Morley, Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Frustum final
	: public Object
{

public:
	typedef Object super;

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
	Matrix4x4* projectionMatrixTransposed {  };
	Matrix4x4* modelViewMatrixTransposed {  };
	Matrix4x4* frustumMatrix {  };

private:
	PlaneArray* planes {  };
protected:

	/** 
	 * Public default constructor
	 * @param renderer
	 */
	void ctor(GLRenderer* renderer);

public:

	/** 
	 * @return planes
	 */
	PlaneArray* getPlanes();

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
	bool isVisible(Vector3* v);

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

	// Generated
	Frustum(GLRenderer* renderer);
protected:
	Frustum(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
