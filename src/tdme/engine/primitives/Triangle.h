#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using std::vector;

using tdme::math::Vector3;

/**
 * Triangle entity, this is not directly connectable with physics engine
 * @author Andreas Drewke
 */
class tdme::engine::primitives::Triangle final
{
public:
	/**
	 * Public constructor
	 */
	Triangle();

	/**
	 * Public constructor
	 * @param vertex0 vertex 0
	 * @param vertex1 vertex 1
	 * @param vertex2 vertex 2
	 */
	Triangle(const Vector3& vertex0, const Vector3& vertex1, const Vector3& vertex2);

	/**
	 * @return triangle vertices
	 */
	inline const
	vector<Vector3>& getVertices() const {
		return vertices;
	}

	/**
	 * Compute closest point on bounding volume
	 * @param point point
	 * @param closestPoint closest point
	 */
	void computeClosestPointOnBoundingVolume(const Vector3& point, Vector3& closestPoint) const;

private:
	vector<Vector3> vertices;
};
