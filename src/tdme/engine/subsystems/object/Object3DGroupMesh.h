// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DGroupMesh.java

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::Cloneable;
using java::nio::FloatBuffer;
using java::nio::ShortBuffer;
using tdme::engine::Engine_AnimationProcessingTarget;
using tdme::engine::model::Group;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utils::_HashMap;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Cloneable, ObjectArray > CloneableArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::TextureCoordinate, ::java::lang::ObjectArray > TextureCoordinateArray;
}  // namespace model
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Matrix4x4, ::java::lang::ObjectArray > Matrix4x4Array;
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

namespace  {
typedef ::SubArray< ::floatArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > floatArrayArray;
}  // namespace 

namespace tdme {
namespace math {
typedef ::SubArray< ::tdme::math::Matrix4x4Array, ::java::lang::CloneableArray, ::java::io::SerializableArray > Matrix4x4ArrayArray;
}  // namespace math
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::CloneableArray;
using java::lang::ObjectArray;
using tdme::engine::model::TextureCoordinateArray;
using tdme::math::Matrix4x4Array;
using tdme::math::Matrix4x4ArrayArray;
using tdme::math::Vector3Array;

struct default_init_tag;
class tdme::engine::subsystems::object::Object3DGroupMesh final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	Group* group {  };
	int32_t faceCount {  };
	int16_tArray* indices {  };
	Vector3Array* vertices {  };
	Vector3Array* normals {  };
	Vector3Array* tangents {  };
	Vector3Array* bitangents {  };
	TextureCoordinateArray* textureCoordinates {  };
	Engine_AnimationProcessingTarget* animationProcessingTarget {  };

private:
	int32_t cSkinningMaxVertexWeights {  };
	floatArrayArray* cSkinningJointWeight {  };

public: /* protected */
	Matrix4x4* cGroupTransformationsMatrix {  };

private:
	Matrix4x4ArrayArray* cSkinningJointTransformationsMatrices {  };
	Vector3* tmpVector3 {  };

public: /* protected */
	bool skinning {  };
	int32_t skinningJoints {  };

private:
	bool recreatedBuffers {  };

public: /* protected */

	/** 
	 * Creates a object3d group mesh from group
	 * @param animation processing target
	 * @param group
	 * @param transformationm matrices
	 * @param skinning matrices 
	 * @return object 3d group mesh
	 */
	static Object3DGroupMesh* createMesh(Engine_AnimationProcessingTarget* animationProcessingTarget, Group* group, _HashMap* transformationMatrices, _HashMap* skinningMatrices);

	/** 
	 * Computes mesh transformations
	 * @param group
	 */
	void computeTransformations(Group* group);

	/** 
	 * Recreates group float buffers
	 */
	void recreateBuffers();

	/** 
	 * @return if buffers has been recreated and unsets state
	 */
	bool hasRecreatedBuffers();

	/** 
	 * Set up vertex indices buffer
	 * @return vertex indices buffer
	 */
	ShortBuffer* setupVertexIndicesBuffer();

	/** 
	 * Set up texture coordinates buffer
	 * @return texture coordinates buffer
	 */
	FloatBuffer* setupTextureCoordinatesBuffer();

	/** 
	 * Set up vertices buffer
	 * @return vertices buffer
	 */
	FloatBuffer* setupVerticesBuffer();

	/** 
	 * Set up normals buffer
	 * @return normals buffer
	 */
	FloatBuffer* setupNormalsBuffer();

	/** 
	 * Set up tangents buffer
	 * @return tangents buffer
	 */
	FloatBuffer* setupTangentsBuffer();

	/** 
	 * Set up bitangents buffer
	 * @return bitangents buffer
	 */
	FloatBuffer* setupBitangentsBuffer();

	// Generated

public:
	Object3DGroupMesh();
protected:
	void ctor();
	Object3DGroupMesh(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
