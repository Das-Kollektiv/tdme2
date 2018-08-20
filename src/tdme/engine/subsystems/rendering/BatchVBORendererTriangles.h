#pragma once

#include <array>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Matrix4x4.h>

using std::array;
using std::vector;

using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::engine::model::Color4;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Matrix4x4;

/** 
 * Batch VBO renderer
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::BatchVBORendererTriangles final
{
	friend class TransparentRenderFacesGroup;

private:
	static constexpr int32_t TRIANGLE_COUNT { 1024 };
	static constexpr int32_t VERTEX_COUNT { TRIANGLE_COUNT * 3 };
	GLRenderer* renderer {  };
	vector<int32_t>* vboIds {  };
	int32_t id {  };
	bool acquired {  };
	int32_t vertices {  };
	ByteBuffer* fbModelMatricesByteBuffer;
	FloatBuffer fbModelMatrices {  };
	ByteBuffer* fbEffectColorMulsByteBuffer;
	FloatBuffer fbEffectColorMuls {  };
	ByteBuffer* fbEffectColorAddsByteBuffer;
	FloatBuffer fbEffectColorAdds {  };
	ByteBuffer* fbVerticesByteBuffer;
	FloatBuffer fbVertices {  };
	ByteBuffer* fbNormalsByteBuffer {  };
	FloatBuffer fbNormals {  };
	ByteBuffer* fbTextureCoordinatesByteBuffer {  };
	FloatBuffer fbTextureCoordinates {  };

	/**
	 * Clears this batch vbo renderer
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
	/**
	 * Public constructor
	 * @param renderer renderer
	 * @param id id
	 */
	BatchVBORendererTriangles(GLRenderer* renderer, int32_t id);

	/**
	 * Destructor
	 */
	~BatchVBORendererTriangles();
};
