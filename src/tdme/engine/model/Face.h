
#pragma once

#include <array>

#include <tdme.h>
#include <tdme/engine/model/fwd-tdme.h>

using std::array;

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
	array<int32_t, 3> vertexIndices {  };
	array<int32_t, 3> normalIndices {  };
	array<int32_t, 3> textureCoordinateIndices {  };
	array<int32_t, 3> tangentIndices {  };
	array<int32_t, 3> bitangentIndices {  };
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
	array<int32_t, 3>* getVertexIndices();

	/** 
	 * @return normal indices
	 */
	array<int32_t, 3>* getNormalIndices();

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
	array<int32_t, 3>* getTextureCoordinateIndices();

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
	array<int32_t, 3>* getTangentIndices();

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
	array<int32_t, 3>* getBitangentIndices();

public: /* protected */

	/** 
	 * Prepared this face for indexed rendering
	 * @param index 0
	 * @param index 1
	 * @param index 2
	 */
	void setIndexedRenderingIndices(array<int32_t, 3>* indices);

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
