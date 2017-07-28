// Generated from /tdme/src/tdme/math/TriangleTriangleIntersection.java

#pragma once

#include <array>

#include <fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using std::array;

using java::lang::Object;
using tdme::math::TriangleTriangleIntersection_ReturnValue;
using tdme::math::Vector2;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Triangle Triangle Intersection see:
 * http://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/code/
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::math::TriangleTriangleIntersection final
	: public Object
{

public:
	typedef Object super;

private:
	static constexpr float EPSILON { 0.01f };
	Vector3* E1 {  };
	Vector3* E2 {  };
	Vector3* N1 {  };
	Vector3* N2 {  };
	Vector3* D {  };
	Vector2* isect1 {  };
	Vector2* isect2_ {  };
	Vector3* isectpointA1 {  };
	Vector3* isectpointA2 {  };
	Vector3* isectpointB1 {  };
	Vector3* isectpointB2 {  };
	Vector3* diff {  };
	floatArray* A {  };

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
	static bool EDGE_EDGE_TEST(array<float, 3>* V0, array<float, 3>* U0, array<float, 3>* U1, int32_t i0, int32_t i1, float Ax, float Ay);

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
	static bool EDGE_AGAINST_TRI_EDGES(array<float, 3>* V0, array<float, 3>* V1, array<float, 3>* U0, array<float, 3>* U1, array<float, 3>* U2, int32_t i0, int32_t i1);

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
	static bool POINT_IN_TRI(array<float, 3>* V0, array<float, 3>* U0, array<float, 3>* U1, array<float, 3>* U2, int32_t i0, int32_t i1);

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
	bool coplanar_tri_tri(array<float, 3>* N, array<float, 3>* V0, array<float, 3>* V1, array<float, 3>* V2, array<float, 3>* U0, array<float, 3>* U1, array<float, 3>* U2);

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
	void isect2(Vector3* VTX0, Vector3* VTX1, Vector3* VTX2, float VV0, float VV1, float VV2, float D0, float D1, float D2, Vector2* isect0, int32_t isect0Idx, Vector2* isect1, int32_t isect1Idx, Vector3* isectpoint0, Vector3* isectpoint1);

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
	bool compute_intervals_isectline(Vector3* VERT0, Vector3* VERT1, Vector3* VERT2, float VV0, float VV1, float VV2, float D0, float D1, float D2, float D0D1, float D0D2, Vector2* isect0, int32_t isect0Idx, Vector2* isect1, int32_t isect1Idx, Vector3* isectpoint0, Vector3* isectpoint1);

	/** 
	 * Sort values and return smallest value index
	 * @param values
	 * @return smallest value index
	 */
	static int32_t SORT2(array<float, 2>* values);

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
	TriangleTriangleIntersection_ReturnValue* computeTriangleTriangleIntersection(Vector3* V0, Vector3* V1, Vector3* V2, Vector3* U0, Vector3* U1, Vector3* U2, Vector3* isectpt1, Vector3* isectpt2);

	// Generated
	TriangleTriangleIntersection();
protected:
	void ctor();
	TriangleTriangleIntersection(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
	friend class TriangleTriangleIntersection_ReturnValue;
};
