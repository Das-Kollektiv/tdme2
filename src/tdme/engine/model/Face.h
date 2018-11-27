#pragma once

#include <array>

#include <tdme/tdme.h>
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
	friend class ModelHelper;

private:
	Group* group {  };
	array<int32_t, 3> vertexIndices {  };
	array<int32_t, 3> normalIndices {  };
	array<int32_t, 3> textureCoordinateIndices {  };
	array<int32_t, 3> tangentIndices {  };
	array<int32_t, 3> bitangentIndices {  };

	/**
	 * Prepared this face for indexed rendering
	 * @param indices indices
	 */
	void setIndexedRenderingIndices(const array<int32_t, 3>& indices);

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
	 * Set normal indices
	 * @param ni0 ni0
	 * @param ni1 ni1
	 * @param ni2 ni2
	 */
	void setNormalIndices(int32_t ni0, int32_t ni1, int32_t ni2);

	/**
	 * Set up optional texture coordinate indices
	 * @param vt0 vtX
	 * @param vt1 vtY
	 * @param vt2 vtZ
	 */
	void setTextureCoordinateIndices(int32_t vt0, int32_t vt1, int32_t vt2);

	/** 
	 * @return texture coordinate indices or null (optional)
	 */
	array<int32_t, 3>* getTextureCoordinateIndices();

	/** 
	 * Set tangent indices
	 * @param ti0 ti0
	 * @param ti1 ti1
	 * @param ti2 ti2
	 */
	void setTangentIndices(int32_t ti0, int32_t ti1, int32_t ti2);

	/** 
	 * @return tangent indices
	 */
	array<int32_t, 3>* getTangentIndices();

	/** 
	 * Set bitangent indices
	 * @param bi0 bi0
	 * @param bi1 bi1
	 * @param bi2 bi2
	 */
	void setBitangentIndices(int32_t bi0, int32_t bi1, int32_t bi2);

	/** 
	 * @return bi tangent indices
	 */
	array<int32_t, 3>* getBitangentIndices();

	/**
	 * Public constructor
	 */
	Face();

	/**
	 * Public constructor, requires vertex, normals indices
	 * we only support triangulated faces
	 * @param group model
	 * @param vi0 vertex index 0
	 * @param vi1 vertex index 1
	 * @param vi2 vertex index 2
	 * @param ni0 normal index 0
	 * @param ni1 normal index 1
	 * @param ni2 normal index 2
	 */
	Face(Group* group, int32_t vi0, int32_t vi1, int32_t vi2, int32_t ni0, int32_t ni1, int32_t ni2);

	/**
	 * Public constructor, requires vertex, normals indices, texture coordinate indices
	 * we only support triangulated faces
	 * @param group model
	 * @param vi0 vertex index 0
	 * @param vi1 vertex index 1
	 * @param vi2 vertex index 2
	 * @param ni0 normal index 0
	 * @param ni1 normal index 1
	 * @param ni2 normal index 2
	 * @param vt0 texture coordinate index 0
	 * @param vt1 texture coordinate index 1
	 * @param vt2 texture coordinate index 2
	 */
	Face(Group* group, int32_t vi0, int32_t vi1, int32_t vi2, int32_t ni0, int32_t ni1, int32_t ni2, int32_t vt0, int32_t vt1, int32_t vt2);
};
