#include <tdme/math/TriangleTriangleIntersection.h>

#include <array>

#include <tdme/math/Math.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>

using std::array;

using tdme::math::TriangleTriangleIntersection;
using tdme::math::Math;
using tdme::math::TriangleTriangleIntersection_ReturnValue;
using tdme::math::Vector2;
using tdme::math::Vector3;

constexpr float TriangleTriangleIntersection::EPSILON;

TriangleTriangleIntersection::ReturnValue TriangleTriangleIntersection::computeTriangleTriangleIntersection(const Vector3& V0, const Vector3& V1, const Vector3& V2, const Vector3& U0, const Vector3& U1, const Vector3& U2, Vector3& isectpt1, Vector3& isectpt2)
{
	float d1;
	float du0, du1, du2, dv0, dv1, dv2;
	float du0du1, du0du2, dv0dv1, dv0dv2;

	Vector3 E1;
	Vector3 E2;
	Vector3 N1;

	E1.set(V1).sub(V0);
	E2.set(V2).sub(V0);

	Vector3::computeCrossProduct(E1, E2, N1);
	d1 = -Vector3::computeDotProduct(N1, V0);

	du0 = Vector3::computeDotProduct(N1, U0) + d1;
	du1 = Vector3::computeDotProduct(N1, U1) + d1;
	du2 = Vector3::computeDotProduct(N1, U2) + d1;

	if (Math::abs(du0) < EPSILON)
		du0 = 0.0f;

	if (Math::abs(du1) < EPSILON)
		du1 = 0.0f;

	if (Math::abs(du2) < EPSILON)
		du2 = 0.0f;

	du0du1 = du0 * du1;
	du0du2 = du0 * du2;
	if (du0du1 > 0.0f && du0du2 > 0.0f)
		return NOINTERSECTION;

	float d2;

	E1.set(U1).sub(U0);
	E2.set(U2).sub(U0);
	Vector3 N2;

	Vector3::computeCrossProduct(E1, E2, N2);
	d2 = -Vector3::computeDotProduct(N2, U0);
	dv0 = Vector3::computeDotProduct(N2, V0) + d2;
	dv1 = Vector3::computeDotProduct(N2, V1) + d2;
	dv2 = Vector3::computeDotProduct(N2, V2) + d2;

	if (Math::abs(dv0) < EPSILON)
		dv0 = 0.0f;

	if (Math::abs(dv1) < EPSILON)
		dv1 = 0.0f;

	if (Math::abs(dv2) < EPSILON)
		dv2 = 0.0f;

	dv0dv1 = dv0 * dv1;
	dv0dv2 = dv0 * dv2;
	if (dv0dv1 > 0.0f && dv0dv2 > 0.0f)
		return NOINTERSECTION;

	float b, c, max;
	Vector3 D;
	Vector3::computeCrossProduct(N1, N2, D);
	D.abs();

	int index = 0;
	if (D[1] > D[0]) {
		D[0] = D[1];
		index = 1;
	}
	if (D[2] > D[0]) {
		D[0] = D[2];
		index = 2;
	}

	float vp0, vp1, vp2;
	float up0, up1, up2;

	vp0 = V0[index];
	vp1 = V1[index];
	vp2 = V2[index];
	up0 = U0[index];
	up1 = U1[index];
	up2 = U2[index];

	Vector2 isect1;
	Vector3 isectpointA1;
	Vector3 isectpointA2;
	auto coplanar = compute_intervals_isectline(V0, V1, V2, vp0, vp1, vp2, dv0, dv1, dv2, dv0dv1, dv0dv2, isect1, 0, isect1, 1, isectpointA1, isectpointA2);
	if (coplanar == true) {
		if (coplanar_tri_tri(N1, V0, V1, V2, U0, U1, U2) == true) {
			return COPLANAR_INTERSECTION;
		} else {
			return NOINTERSECTION;
		}
	}
	Vector3 isectpointB1;
	Vector3 isectpointB2;
	Vector2 isect2_;
	compute_intervals_isectline(U0, U1, U2, up0, up1, up2, du0, du1, du2, du0du1, du0du2, isect2_, 0, isect2_, 1, isectpointB1, isectpointB2);

	int32_t smallest1, smallest2;
	smallest1 = SORT2(isect1);
	smallest2 = SORT2(isect2_);

	if (isect1[1] < isect2_[0] || isect2_[1] < isect1[0])
		return NOINTERSECTION;

	if (isect2_[0] < isect1[0]) {
		if (smallest1 == 0) {
			isectpt1.set(isectpointA1);
		} else {
			isectpt1.set(isectpointA2);
		}
		if (isect2_[1] < isect1[1]) {
			if (smallest2 == 0) {
				isectpt2.set(isectpointB2);
			} else {
				isectpt2.set(isectpointB1);
			}
		} else {
			if (smallest1 == 0) {
				isectpt2.set(isectpointA2);
			} else {
				isectpt2.set(isectpointA1);
			}
		}
	} else {
		if (smallest2 == 0) {
			isectpt1.set(isectpointB1);
		} else {
			isectpt1.set(isectpointB2);
		}
		if (isect2_[1] > isect1[1]) {
			if (smallest1 == 0) {
				isectpt2.set(isectpointA2);
			} else {
				isectpt2.set(isectpointA1);
			}
		} else {
			if (smallest2 == 0) {
				isectpt2.set(isectpointB2);
			} else {
				isectpt2.set(isectpointB1);
			}
		}
	}
	return INTERSECTION;
}

