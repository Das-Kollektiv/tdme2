// Generated from /tdme/src/tdme/engine/model/Face.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>

using tdme::engine::model::Group;

/** 
 * Represents a object group face, consisting of vertex indices and texture coordinate indices
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::model::Face final
{
private:
	Group* group {  };
	int32_tArray* vertexIndices {  };
	int32_tArray* normalIndices {  };
	int32_tArray* textureCoordinateIndices {  };
	int32_tArray* tangentIndices {  };
	int32_tArray* bitangentIndices {  };
public:

	/**
	 * Init
	 */
	void init();

	/** 
	 * @return group
	 */
	Group* getGroup();

	/** 
	 * @return vertex indices
	 */
	int32_tArray* getVertexIndices();

	/** 
	 * @return normal indices
	 */
	int32_tArray* getNormalIndices();

	/** 
	 * Set up optional texture coordinate indices
	 * @param vtX
	 * @param vtY
	 * @param vtZ
	 */
	void setTextureCoordinateIndices(int32_t vt0, int32_t vt1, int32_t vt2);

	/** 
	 * @return texture coordinate indices or null (optional)
	 */
	int32_tArray* getTextureCoordinateIndices();

	/** 
	 * Set tangent indices
	 * @param ti0
	 * @param ti1
	 * @param ti2
	 */
	void setTangentIndices(int32_t ti0, int32_t ti1, int32_t ti2);

	/** 
	 * @return tangent indices
	 */
	int32_tArray* getTangentIndices();

	/** 
	 * Set bitangent indices
	 * @param bi0
	 * @param bi1
	 * @param bi2
	 */
	void setBitangentIndices(int32_t bi0, int32_t bi1, int32_t bi2);

	/** 
	 * @return bi tangent indices
	 */
	int32_tArray* getBitangentIndices();

public: /* protected */

	/** 
	 * Prepared this face for indexed rendering
	 * @param new face vertex indices
	 */
	void setIndexedRenderingIndices(int32_tArray* faceVertexIndices);

public:

	/**
	 * Public constructor
	 */
	Face();

	/**
	 * Public constructor, requires vertex, normals indices
	 * we only support triangulated faces
	 * @param model
	 * @param vertex index 0
	 * @param vertex index 1
	 * @param vertex index 2
	 * @param normal index 0
	 * @param normal index 1
	 * @param normal index 2
	 */
	Face(Group* group, int32_t vi0, int32_t vi1, int32_t vi2, int32_t ni0, int32_t ni1, int32_t ni2);

	/**
	 * Public constructor, requires vertex, normals indices, texture coordinate indices
	 * we only support triangulated faces
	 * @param model
	 * @param vertex index 0
	 * @param vertex index 1
	 * @param vertex index 2
	 * @param normal index 0
	 * @param normal index 1
	 * @param normal index 2
	 * @param texture coordinate index 0
	 * @param texture coordinate index 1
	 * @param texture coordinate index 2
	 */
	Face(Group* group, int32_t vi0, int32_t vi1, int32_t vi2, int32_t ni0, int32_t ni1, int32_t ni2, int32_t vt0, int32_t vt1, int32_t vt2);
};
