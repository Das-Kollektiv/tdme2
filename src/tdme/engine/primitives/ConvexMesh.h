#pragma once

#include <vector>

#include <reactphysics3d/collision/PolygonVertexArray.h>
#include <reactphysics3d/collision/PolyhedronMesh.h>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/fwd-tdme.h>


using std::vector;

using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Triangle;
using tdme::engine::ObjectModel;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;
using tdme::utilities::IntBuffer;

/**
 * Convex mesh physics primitive
 * @author Andreas Drewke
 */
class tdme::engine::primitives::ConvexMesh final
	: public BoundingVolume
{
private:
	static constexpr float VERTEX_COMPARE_EPSILON { Math::EPSILON };

	vector<Vector3> vertices;
	vector<int> facesVerticesCount;
	vector<int> indices;

	vector<reactphysics3d::PolygonVertexArray::PolygonFace> faces;
	reactphysics3d::PolygonVertexArray* polygonVertexArray { nullptr };
	reactphysics3d::PolyhedronMesh* polyhedronMesh { nullptr };
	ByteBuffer* verticesByteBuffer { nullptr };
	ByteBuffer* indicesByteBuffer { nullptr };

	// forbid class copy
	FORBID_CLASS_COPY(ConvexMesh)

	/**
	 * Public constructor
	 * @param vertices vertices
	 * @param facesVerticesCount faces vertices count
	 * @param indices indices
	 * @param scale scale
	 */
	ConvexMesh(const vector<Vector3>& vertices, const vector<int>& facesVerticesCount, const vector<int>& indices, const Vector3& scale = Vector3(1.0f, 1.0f, 1.0f));

	/**
	 * Public destructor
	 */
	~ConvexMesh();

	/**
	 * Checks if vertex lives on triangle plane
	 * @param triangle triangle
	 * @param vertex vertex
	 * @return if vertex lives on triangle plane
	 */
	inline bool isVertexOnTrianglePlane(const Triangle& triangle, const Vector3& vertex) {
		for (const auto& triangleVertex: triangle.getVertices()) {
			if (triangleVertex.equals(vertex, VERTEX_COMPARE_EPSILON) == true) return true;
		}
		// see: http://www.ambrsoft.com/TrigoCalc/Plan3D/PointsCoplanar.htm
		Vector3 v1;
		Vector3 v2;
		Vector3 v3;
		v1.set(triangle.getVertices()[1]).sub(triangle.getVertices()[0]).normalize();
		v2.set(triangle.getVertices()[2]).sub(triangle.getVertices()[0]).normalize();
		v3.set(vertex).sub(triangle.getVertices()[0]);
		auto v1Dotv2v3Cross = Vector3::computeDotProduct(v1, Vector3::computeCrossProduct(v2, v3).normalize());
		return Math::abs(v1Dotv2v3Cross) < 0.001;
	}

	/**
	 * Checks if 2 triangles are adjacent
	 * @param triangle1 triangle 1
	 * @param triangle2 triangle 2
	 * @return if triangles are adjacent
	 */
	inline bool areTrianglesAdjacent(const Triangle& triangle1, const Triangle& triangle2) {
		auto equalVertices = 0;
		for (const auto& triangle1Vertex: triangle1.getVertices()) {
			for (const auto& triangle2Vertex: triangle2.getVertices()) {
				if (triangle1Vertex.equals(triangle2Vertex, VERTEX_COMPARE_EPSILON)) equalVertices++;
			}
		}
		return equalVertices > 0;
	}

	/**
	 * Create convex mesh
	 * 	Note: it also translates center into origin
	 * @param vertices vertices
	 * @param facesVerticesCount faces vertices count
	 * @param indices indices
	 * @param scale scale
	 */
	void createConvexMesh(const vector<Vector3>& vertices, const vector<int>& facesVerticesCount, const vector<int>& indices, const Vector3& scale);

	// overriden methods
	void destroyCollisionShape() override;
	void createCollisionShape(World* world) override;

public:
	/**
	 * Public constructor
	 */
	ConvexMesh();

	/**
	 * Public constructor
	 * @param model model
	 * @param scale scale
	 */
	ConvexMesh(ObjectModel* model, const Vector3& scale = Vector3(1.0f, 1.0f, 1.0f));

	// overridden methods
	void setScale(const Vector3& scale) override;
	BoundingVolume* clone() const override;

	/**
	 * @return vertices
	 */
	const vector<Vector3>& getVertices();

};
