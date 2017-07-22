// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DGroupMesh.java
#include <tdme/engine/subsystems/object/Object3DGroupMesh.h>

#include <map>
#include <string>

#include <java/io/Serializable.h>
#include <java/lang/Byte.h>
#include <java/lang/Cloneable.h>
#include <java/lang/Float.h>
#include <java/lang/Math.h>
#include <java/lang/Object.h>
#include <java/lang/Short.h>
#include <java/lang/String.h>
#include <java/nio/ByteBuffer.h>
#include <java/nio/FloatBuffer.h>
#include <java/nio/ShortBuffer.h>
#include <tdme/engine/Engine_AnimationProcessingTarget.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/subsystems/object/_Buffer.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::map;
using std::wstring;

using tdme::engine::subsystems::object::Object3DGroupMesh;
using java::io::Serializable;
using java::lang::Byte;
using java::lang::Cloneable;
using java::lang::Float;
using java::lang::Math;
using java::lang::Object;
using java::lang::Short;
using java::lang::String;
using java::nio::ByteBuffer;
using java::nio::FloatBuffer;
using java::nio::ShortBuffer;
using tdme::engine::Engine_AnimationProcessingTarget;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::subsystems::object::_Buffer;
using tdme::math::MathTools;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

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
typedef ::SubArray< ::tdme::engine::model::Face, ::java::lang::ObjectArray > FaceArray;
typedef ::SubArray< ::tdme::engine::model::FacesEntity, ::java::lang::ObjectArray > FacesEntityArray;
typedef ::SubArray< ::tdme::engine::model::Joint, ::java::lang::ObjectArray > JointArray;
typedef ::SubArray< ::tdme::engine::model::JointWeight, ::java::lang::ObjectArray > JointWeightArray;
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
namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::JointWeightArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > JointWeightArrayArray;
}  // namespace model
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Matrix4x4Array, ::java::lang::CloneableArray, ::java::io::SerializableArray > Matrix4x4ArrayArray;
}  // namespace math
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

Object3DGroupMesh::Object3DGroupMesh(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Object3DGroupMesh::Object3DGroupMesh()
	: Object3DGroupMesh(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void Object3DGroupMesh::ctor()
{
	super::ctor();
	init();
}

void Object3DGroupMesh::init()
{
	indices = nullptr;
	vertices = nullptr;
	normals = nullptr;
	tangents = nullptr;
	bitangents = nullptr;
	textureCoordinates = nullptr;
	cSkinningMaxVertexWeights = -1;
	cSkinningJointWeight = nullptr;
	cGroupTransformationsMatrix = nullptr;
	cSkinningJointTransformationsMatrices = nullptr;
	skinning = false;
	skinningJoints = -1;
}

Object3DGroupMesh* Object3DGroupMesh::createMesh(Engine_AnimationProcessingTarget* animationProcessingTarget, Group* group, map<wstring, Matrix4x4*>* transformationMatrices, map<wstring, Matrix4x4*>* skinningMatrices)
{
	clinit();
	auto mesh = new Object3DGroupMesh();
	mesh->group = group;
	auto groupVertices = group->getVertices();
	auto groupNormals = group->getNormals();
	auto groupTextureCoordinates = group->getTextureCoordinates();
	auto groupTangents = group->getTangents();
	auto groupBitangents = group->getBitangents();
	mesh->faceCount = group->getFaceCount();
	mesh->animationProcessingTarget = animationProcessingTarget;
	auto skinning = group->getSkinning();
	mesh->skinning = skinning != nullptr;
	if ((skinning != nullptr && animationProcessingTarget == Engine_AnimationProcessingTarget::CPU) || animationProcessingTarget == Engine_AnimationProcessingTarget::CPU_NORENDERING) {
		mesh->vertices = new Vector3Array(groupVertices->length);
		for (auto j = 0; j < mesh->vertices->length; j++) {
			mesh->vertices->set(j, (new Vector3())->set((*groupVertices)[j]));
		}
		mesh->normals = new Vector3Array(groupNormals->length);
		for (auto j = 0; j < mesh->normals->length; j++) {
			mesh->normals->set(j, (new Vector3())->set((*groupNormals)[j]));
		}
		if (groupTangents != nullptr) {
			mesh->tangents = new Vector3Array(groupTangents->length);
			for (auto j = 0; j < mesh->tangents->length; j++) {
				mesh->tangents->set(j, (new Vector3())->set((*groupTangents)[j]));
			}
		}
		if (groupBitangents != nullptr) {
			mesh->bitangents = new Vector3Array(groupBitangents->length);
			for (auto j = 0; j < mesh->bitangents->length; j++) {
				mesh->bitangents->set(j, (new Vector3())->set((*groupBitangents)[j]));
			}
		}
	} else {
		mesh->vertices = groupVertices;
		mesh->normals = groupNormals;
		if (groupTangents != nullptr) {
			mesh->tangents = groupTangents;
		}
		if (groupBitangents != nullptr) {
			mesh->bitangents = groupBitangents;
		}
	}
	mesh->textureCoordinates = groupTextureCoordinates;
	auto indicesCount = 0;
	for (auto facesEntity : *group->getFacesEntities()) {
		indicesCount += 3 * facesEntity->getFaces()->length;
	}
	mesh->indices = new int16_tArray(indicesCount);
	{
		auto j = 0;
		for (auto facesEntity : *group->getFacesEntities()) 
		for (auto face : *facesEntity->getFaces())
		for (auto vertexIndex : *face->getVertexIndices()) {
			(*mesh->indices)[j++] = static_cast< int16_t >(vertexIndex);
		}
	}
	mesh->recreatedBuffers = false;
	if (mesh->animationProcessingTarget == Engine_AnimationProcessingTarget::CPU || mesh->animationProcessingTarget == Engine_AnimationProcessingTarget::CPU_NORENDERING) {
		auto transformationMatrixIt = transformationMatrices->find(group->getId()->getCPPWString());
		mesh->cGroupTransformationsMatrix = transformationMatrixIt != transformationMatrices->end()?transformationMatrixIt->second:nullptr;
	}
	if ((skinning != nullptr && (animationProcessingTarget == Engine_AnimationProcessingTarget::CPU || animationProcessingTarget == Engine_AnimationProcessingTarget::CPU_NORENDERING))) {
		if (mesh->animationProcessingTarget == Engine_AnimationProcessingTarget::CPU || mesh->animationProcessingTarget == Engine_AnimationProcessingTarget::CPU_NORENDERING) {
			mesh->cSkinningJointWeight = new floatArrayArray(groupVertices->length);
			mesh->cSkinningJointTransformationsMatrices = new Matrix4x4ArrayArray(groupVertices->length);
			auto joints = skinning->getJoints();
			auto weights = skinning->getWeights();
			auto jointsWeights = skinning->getVerticesJointsWeights();
			for (auto vertexIndex = 0; vertexIndex < groupVertices->length; vertexIndex++) {
				auto vertexJointWeights = (*jointsWeights)[vertexIndex]->length;
				if (vertexJointWeights > mesh->cSkinningMaxVertexWeights)
					mesh->cSkinningMaxVertexWeights = vertexJointWeights;

				mesh->cSkinningJointWeight->set(vertexIndex, new floatArray(vertexJointWeights));
				mesh->cSkinningJointTransformationsMatrices->set(vertexIndex, new Matrix4x4Array(vertexJointWeights));
				auto jointWeightIdx = 0;
				for (auto jointWeight : *(*jointsWeights)[vertexIndex]) {
					auto joint = (*joints)[jointWeight->getJointIndex()];
					(*(*mesh->cSkinningJointWeight)[vertexIndex])[jointWeightIdx] = (*weights)[jointWeight->getWeightIndex()];
					auto skinningMatrixIt = skinningMatrices->find(joint->getGroupId()->getCPPWString());
					(*mesh->cSkinningJointTransformationsMatrices)[vertexIndex]->set(jointWeightIdx, skinningMatrixIt != skinningMatrices->end()?skinningMatrixIt->second:nullptr);
					jointWeightIdx++;
				}
			}
		}
	}
	mesh->tmpVector3 = new Vector3();
	mesh->recreateBuffers();
	return mesh;
}

void Object3DGroupMesh::computeTransformations(Group* group)
{
	auto groupVertices = group->getVertices();
	auto groupNormals = group->getNormals();
	auto groupTangent = group->getTangents();
	auto groupBitangent = group->getBitangents();
	auto skinning = group->getSkinning();
	if (skinning != nullptr && (animationProcessingTarget == Engine_AnimationProcessingTarget::CPU || animationProcessingTarget == Engine_AnimationProcessingTarget::CPU_NORENDERING)) {
		if (animationProcessingTarget == Engine_AnimationProcessingTarget::CPU || animationProcessingTarget == Engine_AnimationProcessingTarget::CPU_NORENDERING) {
			auto jointsWeights = skinning->getVerticesJointsWeights();
			Vector3* vertex;
			Vector3* transformedVertex;
			Vector3* normal;
			Vector3* transformedNormal;
			Vector3* tangent;
			Vector3* transformedTangent;
			Vector3* bitangent;
			Vector3* transformedBitangent;
			float totalWeights;
			float weightNormalized;
			for (auto vertexIndex = 0; vertexIndex < groupVertices->length; vertexIndex++) {
				vertex = (*groupVertices)[vertexIndex];
				transformedVertex = (*vertices)[vertexIndex]->set(0.0f, 0.0f, 0.0f);
				normal = (*groupNormals)[vertexIndex];
				transformedNormal = (*normals)[vertexIndex]->set(0.0f, 0.0f, 0.0f);
				tangent = groupTangent != nullptr ? (*groupTangent)[vertexIndex] : static_cast< Vector3* >(nullptr);
				transformedTangent = tangents != nullptr ? (*tangents)[vertexIndex]->set(0.0f, 0.0f, 0.0f) : static_cast< Vector3* >(nullptr);
				bitangent = groupTangent != nullptr ? (*groupBitangent)[vertexIndex] : static_cast< Vector3* >(nullptr);
				transformedBitangent = bitangents != nullptr ? (*bitangents)[vertexIndex]->set(0.0f, 0.0f, 0.0f) : static_cast< Vector3* >(nullptr);
				totalWeights = 0.0f;
				for (auto vertexJointWeightIdx = 0; vertexJointWeightIdx < (*jointsWeights)[vertexIndex]->length; vertexJointWeightIdx++) {
					auto weight = (*(*cSkinningJointWeight)[vertexIndex])[vertexJointWeightIdx];
					auto cTransformationsMatrix = (*(*cSkinningJointTransformationsMatrices)[vertexIndex])[vertexJointWeightIdx];
					transformedVertex->add(cTransformationsMatrix->multiply(vertex, tmpVector3)->scale(weight));
					transformedNormal->add(cTransformationsMatrix->multiplyNoTranslation(normal, tmpVector3)->scale(weight));
					if (tangent != nullptr) {
						transformedTangent->add(cTransformationsMatrix->multiplyNoTranslation(tangent, tmpVector3)->scale(weight));
					}
					if (bitangent != nullptr) {
						transformedBitangent->add(cTransformationsMatrix->multiplyNoTranslation(bitangent, tmpVector3)->scale(weight));
					}
					totalWeights += weight;
				}
				if (Math::abs(totalWeights - 1.0f) > MathTools::EPSILON) {
					weightNormalized = 1.0f / totalWeights;
					transformedVertex->scale(weightNormalized);
					transformedNormal->scale(weightNormalized);
					if (transformedTangent != nullptr) {
						transformedTangent->scale(weightNormalized);
					}
					if (transformedBitangent != nullptr) {
						transformedBitangent->scale(weightNormalized);
					}
				}
				transformedNormal->normalize();
			}
			recreateBuffers();
		}
	} else if (animationProcessingTarget == Engine_AnimationProcessingTarget::CPU_NORENDERING) {
		for (auto vertexIndex = 0; vertexIndex < groupVertices->length; vertexIndex++) {
			(*vertices)[vertexIndex]->set(cGroupTransformationsMatrix->multiply((*groupVertices)[vertexIndex], tmpVector3));
		}
		for (auto normalIndex = 0; normalIndex < groupNormals->length; normalIndex++) {
			(*normals)[normalIndex]->set(cGroupTransformationsMatrix->multiplyNoTranslation((*groupNormals)[normalIndex], tmpVector3)->normalize());
		}
		recreateBuffers();
	}
}

void Object3DGroupMesh::recreateBuffers()
{
	recreatedBuffers = true;
}

bool Object3DGroupMesh::hasRecreatedBuffers()
{
	if (recreatedBuffers == true) {
		recreatedBuffers = false;
		return true;
	} else {
		return false;
	}
}

ShortBuffer* Object3DGroupMesh::setupVertexIndicesBuffer()
{
	auto sbIndices = _Buffer::getByteBuffer(faceCount * 3 * Short::SIZE / Byte::SIZE)->asShortBuffer();
	for (auto index : *indices) {
		sbIndices->put(index);
	}
	// sbIndices->flip();
	return sbIndices;
}

FloatBuffer* Object3DGroupMesh::setupTextureCoordinatesBuffer()
{
	auto groupTextureCoordinates = group->getTextureCoordinates();
	if (groupTextureCoordinates == nullptr)
		return nullptr;

	auto fbTextureCoordinates = _Buffer::getByteBuffer(groupTextureCoordinates->length * 2 * Float::SIZE / Byte::SIZE)->asFloatBuffer();
	for (auto textureCoordinate : *groupTextureCoordinates) {
		fbTextureCoordinates->put(textureCoordinate->getArray());
	}
	// fbTextureCoordinates->flip();
	return fbTextureCoordinates;
}

FloatBuffer* Object3DGroupMesh::setupVerticesBuffer()
{
	auto fbVertices = _Buffer::getByteBuffer(vertices->length * 3 * Float::SIZE / Byte::SIZE)->asFloatBuffer();
	for (auto vertex : *vertices) {
		fbVertices->put(vertex->getArray());
	}
	// fbVertices->flip();
	return fbVertices;
}

FloatBuffer* Object3DGroupMesh::setupNormalsBuffer()
{
	auto fbNormals = _Buffer::getByteBuffer(normals->length * 3 * Float::SIZE / Byte::SIZE)->asFloatBuffer();
	for (auto normal : *normals) {
		fbNormals->put(normal->getArray());
	}
	// fbNormals->flip();
	return fbNormals;
}

FloatBuffer* Object3DGroupMesh::setupTangentsBuffer()
{
	if (tangents == nullptr) {
		return nullptr;
	}
	auto fbTangents = _Buffer::getByteBuffer(tangents->length * 3 * Float::SIZE / Byte::SIZE)->asFloatBuffer();
	for (auto tangent : *tangents) {
		fbTangents->put(tangent->getArray());
	}
	// fbTangents->flip();
	return fbTangents;
}

FloatBuffer* Object3DGroupMesh::setupBitangentsBuffer()
{
	if (bitangents == nullptr) {
		return nullptr;
	}
	auto fbBitangents = _Buffer::getByteBuffer(bitangents->length * 3 * Float::SIZE / Byte::SIZE)->asFloatBuffer();
	for (auto bitangent : *bitangents) {
		fbBitangents->put(bitangent->getArray());
	}
	// fbBitangents->flip();
	return fbBitangents;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Object3DGroupMesh::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.Object3DGroupMesh", 47);
    return c;
}

java::lang::Class* Object3DGroupMesh::getClass0()
{
	return class_();
}

