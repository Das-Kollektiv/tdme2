// Generated from /tdme/src/tdme/math/TriangleTriangleIntersection.java

#pragma once

#include <array>

#include <fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>

using std::array;

using tdme::math::TriangleTriangleIntersection;

using tdme::math::Math;
using tdme::math::TriangleTriangleIntersection_ReturnValue;
using tdme::math::Vector2;
using tdme::math::Vector3;

/** 
 * Triangle Triangle Intersection see:
 * http://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/code/
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::math::TriangleTriangleIntersection final
{

public:
	enum ReturnValue { NOINTERSECTION, COPLANAR_INTERSECTION, INTERSECTION };

private:
	static constexpr float EPSILON { 0.01f };

	/** 
	 * Triangle Triangle Intersection see:
	 * http://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/code/
	 * @param V0
	 * @param U0
	 * @param U1
	 * @param i0
	 * @param i1
	 * @param Ax
	 * @param Ay
	 * @return
	 */
	inline static bool EDGE_EDGE_TEST(array<float, 3>& V0, array<float, 3>& U0, array<float, 3>& U1, int32_t i0, int32_t i1, float Ax, float Ay) {
		float Bx, By, Cx, Cy, e, d, f;
		Bx = U0[i0] - U1[i0];
		By = U0[i1] - U1[i1];
		Cx = V0[i0] - U0[i0];
		Cy = V0[i1] - U0[i1];
		f = Ay * Bx - Ax * By;
		d = By * Cx - Bx * Cy;
		if ((f > 0 && d >= 0 && d <= f) || (f < 0 && d <= 0 && d >= f)) {
			e = Ax * Cy - Ay * Cx;
			if (f > 0) {
				if (e >= 0 && e <= f)
					return true;

			} else {
				if (e <= 0 && e >= f)
					return true;

			}
		}
		return false;
	}

	/** 
	 * Triangle Triangle Intersection see:
	 * http://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/code/
	 * @param V0
	 * @param V1
	 * @param U0
	 * @param U1
	 * @param U2
	 * @param i0
	 * @param i1
	 * @return
	 */
	static bool EDGE_AGAINST_TRI_EDGES(array<float, 3>& V0, array<float, 3>& V1, array<float, 3>& U0, array<float, 3>& U1, array<float, 3>& U2, int32_t i0, int32_t i1) {
		float Ax, Ay;
		Ax = V1[i0] - V0[i0];
		Ay = V1[i1] - V0[i1];
		if (EDGE_EDGE_TEST(V0, U0, U1, i0, i1, Ax, Ay) == true)
			return true;

		if (EDGE_EDGE_TEST(V0, U1, U2, i0, i1, Ax, Ay) == true)
			return true;

		if (EDGE_EDGE_TEST(V0, U2, U0, i0, i1, Ax, Ay) == true)
			return true;

		return false;
	}

	/** 
	 * Triangle Triangle Intersection see:
	 * http://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/code/
	 * @param V0
	 * @param U0
	 * @param U1
	 * @param U2
	 * @param i0
	 * @param i1
	 * @return
	 */
	static bool POINT_IN_TRI(array<float, 3>& V0, array<float, 3>& U0, array<float, 3>& U1, array<float, 3>& U2, int32_t i0, int32_t i1) {
		float a, b, c, d0, d1, d2;
		a = U1[i1] - U0[i1];
		b = -(U1[i0] - U0[i0]);
		c = -a * U0[i0] - b * U0[i1];
		d0 = a * V0[i0] + b * V0[i1] + c;
		a = U2[i1] - U1[i1];
		b = -(U2[i0] - U1[i0]);
		c = -a * U1[i0] - b * U1[i1];
		d1 = a * V0[i0] + b * V0[i1] + c;
		a = U0[i1] - U2[i1];
		b = -(U0[i0] - U2[i0]);
		c = -a * U2[i0] - b * U2[i1];
		d2 = a * V0[i0] + b * V0[i1] + c;
		if (d0 * d1 > 0.0) {
			if (d0 * d2 > 0.0)
				return true;

		}
		return false;
	}

	/** 
	 * Triangle Triangle Intersection see:
	 * http://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/code/
	 * @param N
	 * @param V0
	 * @param V1
	 * @param V2
	 * @param U0
	 * @param U1
	 * @param U2
	 * @return
	 */
	static bool coplanar_tri_tri(array<float, 3>& N, array<float, 3>& V0, array<float, 3>& V1, array<float, 3>& V2, array<float, 3>& U0, array<float, 3>& U1, array<float, 3>& U2) {
		int32_t i0, i1;
		array<float, 3> A;
		A[0] = Math::abs(N[0]);
		A[1] = Math::abs(N[1]);
		A[2] = Math::abs(N[2]);
		if (A[0] > A[1]) {
			if (A[0] > A[2]) {
				i0 = 1;
				i1 = 2;
			} else {
				i0 = 0;
				i1 = 1;
			}
		} else {
			if (A[2] > A[1]) {
				i0 = 0;
				i1 = 1;
			} else {
				i0 = 0;
				i1 = 2;
			}
		}
		if (EDGE_AGAINST_TRI_EDGES(V0, V1, U0, U1, U2, i0, i1) == true)
			return true;

		if (EDGE_AGAINST_TRI_EDGES(V1, V2, U0, U1, U2, i0, i1) == true)
			return true;

		if (EDGE_AGAINST_TRI_EDGES(V2, V0, U0, U1, U2, i0, i1) == true)
			return true;

		if (POINT_IN_TRI(V0, U0, U1, U2, i0, i1) == true)
			return true;

		if (POINT_IN_TRI(U0, V0, V1, V2, i0, i1) == true)
			return true;

		return false;
	}

	/** 
	 * Triangle Triangle Intersection see:
	 * http://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/code/
	 * @param VTX0
	 * @param VTX1
	 * @param VTX2
	 * @param VV0
	 * @param VV1
	 * @param VV2
	 * @param D0
	 * @param D1
	 * @param D2
	 * @param isect0
	 * @param isect0Idx
	 * @param isect1
	 * @param isect1Idx
	 * @param isectpoint0
	 * @param isectpoint1
	 */
	static void isect2(const Vector3& VTX0, const Vector3& VTX1, const Vector3& VTX2, float VV0, float VV1, float VV2, float D0, float D1, float D2, Vector2& isect0, int32_t isect0Idx, Vector2& isect1, int32_t isect1Idx, Vector3& isectpoint0, Vector3& isectpoint1) {
		Vector3 diff;
		auto tmp = D0 / (D0 - D1);
		isect0.getArray()[isect0Idx] = VV0 + (VV1 - VV0) * tmp;
		diff.set(VTX1).sub(VTX0);
		diff.scale(tmp);
		isectpoint0.set(diff).add(VTX0);
		tmp = D0 / (D0 - D2);
		isect1.getArray()[isect1Idx] = VV0 + (VV2 - VV0) * tmp;
		diff.set(VTX2).sub(VTX0);
		diff.scale(tmp);
		isectpoint1.set(VTX0).add(diff);
	}

	/** 
	 * @param VERT0
	 * @param VERT1
	 * @param VERT2
	 * @param VV0
	 * @param VV1
	 * @param VV2
	 * @param D0
	 * @param D1
	 * @param D2
	 * @param D0D1
	 * @param D0D2
	 * @param isect0
	 * @param isect0Idx
	 * @param isect1
	 * @param isect1Idx
	 * @param isectpoint0
	 * @param isectpoint1
	 * @return
	 */
	static bool compute_intervals_isectline(const Vector3& VERT0, const Vector3& VERT1, const Vector3& VERT2, float VV0, float VV1, float VV2, float D0, float D1, float D2, float D0D1, float D0D2, Vector2& isect0, int32_t isect0Idx, Vector2& isect1, int32_t isect1Idx, Vector3& isectpoint0, Vector3& isectpoint1) {
		if (D0D1 > 0.0f) {
			isect2(VERT2, VERT0, VERT1, VV2, VV0, VV1, D2, D0, D1, isect0, isect0Idx, isect1, isect1Idx, isectpoint0, isectpoint1);
		} else if (D0D2 > 0.0f) {
			isect2(VERT1, VERT0, VERT2, VV1, VV0, VV2, D1, D0, D2, isect0, isect0Idx, isect1, isect1Idx, isectpoint0, isectpoint1);
		} else if (D1 * D2 > 0.0f || D0 != 0.0f) {
			isect2(VERT0, VERT1, VERT2, VV0, VV1, VV2, D0, D1, D2, isect0, isect0Idx, isect1, isect1Idx, isectpoint0, isectpoint1);
		} else if (D1 != 0.0f) {
			isect2(VERT1, VERT0, VERT2, VV1, VV0, VV2, D1, D0, D2, isect0, isect0Idx, isect1, isect1Idx, isectpoint0, isectpoint1);
		} else if (D2 != 0.0f) {
			isect2(VERT2, VERT0, VERT1, VV2, VV0, VV1, D2, D0, D1, isect0, isect0Idx, isect1, isect1Idx, isectpoint0, isectpoint1);
		} else {
			return true;
		}
		return false;
	}

	/** 
	 * Sort values and return smallest value index
	 * @param values
	 * @return smallest value index
	 */
	static int32_t SORT2(array<float, 2>& values) {
		if (values[0] > values[1]) {
			float tmp;
			tmp = values[0];
			values[0] = values[1];
			values[1] = tmp;
			return 1;
		} else {
			return 0;
		}
	}

public:

	/** 
	 * Compute triangle v0,v1,v2 vs. triangle u0,u1,u2 intersection test 
	 * @param V0
	 * @param V1
	 * @param V2
	 * @param U0
	 * @param U1
	 * @param U2
	 * @param isectpt1 intersection point 1 if not coplanar
	 * @param isectpt2 intersection point 2 if not coplanar
	 * @return
	 */
	static ReturnValue computeTriangleTriangleIntersection(const Vector3& V0, const Vector3& V1, const Vector3& V2, const Vector3& U0, const Vector3& U1, const Vector3& U2, Vector3& isectpt1, Vector3& isectpt2);

};
