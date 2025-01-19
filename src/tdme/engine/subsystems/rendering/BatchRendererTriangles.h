#pragma once

#include <array>
#include <memory>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/FloatBuffer.h>

using std::array;
using std::unique_ptr;
using std::vector;

using tdme::engine::Color4;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;

/**
 * Batch renderer for transparent triangles
 * @author andreas.drewke
 */
class tdme::engine::subsystems::rendering::BatchRendererTriangles final
{
	friend class TransparentRenderFacesGroup;

private:
	static constexpr int32_t TRIANGLE_COUNT { 1024 };
	static constexpr int32_t VERTEX_COUNT { TRIANGLE_COUNT * 3 };
	RendererBackend* rendererBackend { nullptr };
	vector<int32_t>* vboIds { nullptr };
	int32_t id;
	bool acquired;
	int32_t vertices;
	unique_ptr<ByteBuffer> fbModelMatricesByteBuffer;
	FloatBuffer fbModelMatrices;
	unique_ptr<ByteBuffer> fbEffectColorMulsByteBuffer;
	FloatBuffer fbEffectColorMuls;
	unique_ptr<ByteBuffer> fbEffectColorAddsByteBuffer;
	FloatBuffer fbEffectColorAdds;
	unique_ptr<ByteBuffer> fbVerticesByteBuffer;
	FloatBuffer fbVertices;
	unique_ptr<ByteBuffer> fbNormalsByteBuffer;
	FloatBuffer fbNormals;
	unique_ptr<ByteBuffer> fbTextureCoordinatesByteBuffer;
	FloatBuffer fbTextureCoordinates;

	/**
	 * Clears this batch vbo rendererBackend
	 */
	void clear();

	/**
	 * Render
	 */
	void render();

	/**
	 * Adds a vertex to this transparent render faces group
	 * @param vertex vertex
	 * @param normal normal
	 * @param textureCoordinate texture coordinate
	 * @return success
	 */
	inline bool addVertex(const Vector3& vertex, const Vector3& normal, const Vector2& textureCoordinate) {
		// check if full
		if (vertices == VERTEX_COUNT) return false;

		// otherwise
		fbVertices.put(vertex.getArray());
		fbNormals.put(normal.getArray());
		fbTextureCoordinates.put(textureCoordinate.getArray());

		//
		vertices++;
		return true;
	}

public:
	// forbid class copy
	FORBID_CLASS_COPY(BatchRendererTriangles)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 * @param id id
	 */
	BatchRendererTriangles(RendererBackend* rendererBackend, int32_t id);

	/**
	 * Destructor
	 */
	~BatchRendererTriangles();

	/**
	 * @return acquired
	 */
	bool isAcquired();

	/**
	 * Acquire
	 */
	bool acquire();

	/**
	 * Release
	 */
	void release();

	/**
	 * Init
	 */
	void initialize();

	/**
	 * Dispose
	 */
	void dispose();

};
