// Generated from /tdme/src/tdme/engine/model/ModelHelper.java
#include <tdme/engine/model/ModelHelper.h>

#include <vector>

#include <java/io/Serializable.h>
#include <java/lang/Cloneable.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/System.h>
#include <java/util/Iterator.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper_VertexOrder.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::vector;

using tdme::engine::model::ModelHelper;
using java::io::Serializable;
using java::lang::Cloneable;
using java::lang::Object;
using java::lang::String;
using java::lang::System;
using java::util::Iterator;
using tdme::engine::model::Animation;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper_VertexOrder;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::utils::_Console;

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

namespace engine {
namespace model {
typedef ::SubArray< ::tdme::engine::model::JointWeightArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > JointWeightArrayArray;
}  // namespace model
}  // namespace engine
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

ModelHelper::ModelHelper(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ModelHelper::ModelHelper()
	: ModelHelper(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

ModelHelper_VertexOrder* ModelHelper::determineVertexOrder(Vector3Array* vertices)
{
	clinit();
	auto edgeSum = 0;
	for (auto i = 0; i < vertices->length; i++) {
		auto currentVertexXYZ = (*vertices)[i]->getArray();
		auto nextVertexXYZ = (*vertices)[(i + 1) % vertices->length]->getArray();
		edgeSum += ((*nextVertexXYZ)[0] - (*currentVertexXYZ)[0]) * ((*nextVertexXYZ)[1] - (*currentVertexXYZ)[1]) * ((*nextVertexXYZ)[2] - (*currentVertexXYZ)[0]);
	}
	if (edgeSum >= 0) {
		return ModelHelper_VertexOrder::CLOCKWISE;
	} else {
		return ModelHelper_VertexOrder::COUNTERCLOCKWISE;
	}
}

Vector3* ModelHelper::computeNormal(Vector3Array* vertices)
{
	clinit();
	return Vector3::computeCrossProduct((*vertices)[1]->clone()->sub((*vertices)[0]), (*vertices)[2]->clone()->sub((*vertices)[0]))->normalize();
}

Vector3Array* ModelHelper::computeNormals(Vector3Array* vertices)
{
	clinit();
	auto normal = computeNormal(vertices);
	auto normals = new Vector3Array(3);
	for (auto i = 0; i < vertices->length; i++) {
		normals->set(i, normal->clone());
	}
	return normals;
}

void ModelHelper::createNormalTangentsAndBitangents(Group* group)
{
	clinit();
	vector<Vector3*> tangentsArrayList;
	vector<Vector3*> bitangentsArrayList;
	auto uv0 = new Vector2();
	auto uv1 = new Vector2();
	auto uv2 = new Vector2();
	auto deltaPos1 = new Vector3();
	auto deltaPos2 = new Vector3();
	auto deltaUV1 = new Vector2();
	auto deltaUV2 = new Vector2();
	auto tmpVector3 = new Vector3();
	auto vertices = group->getVertices();
	auto normals = group->getNormals();
	auto textureCoordinates = group->getTextureCoordinates();
	for (auto faceEntity : *group->getFacesEntities()) 
		if (faceEntity->getMaterial() != nullptr && faceEntity->getMaterial()->hasNormalTexture() == true) {
			for (auto face : *faceEntity->getFaces()) {
				auto verticesIndexes = face->getVertexIndices();
				auto v0 = (*vertices)[(*verticesIndexes)[0]];
				auto v1 = (*vertices)[(*verticesIndexes)[1]];
				auto v2 = (*vertices)[(*verticesIndexes)[2]];
				auto textureCoordinatesIndexes = face->getTextureCoordinateIndices();
				uv0->set((*textureCoordinates)[(*textureCoordinatesIndexes)[0]]->getArray());
				uv0->setY(1.0f - uv0->getY());
				uv1->set((*textureCoordinates)[(*textureCoordinatesIndexes)[1]]->getArray());
				uv1->setY(1.0f - uv1->getY());
				uv2->set((*textureCoordinates)[(*textureCoordinatesIndexes)[2]]->getArray());
				uv2->setY(1.0f - uv2->getY());
				deltaPos1->set(v1)->sub(v0);
				deltaPos2->set(v2)->sub(v0);
				deltaUV1->set(uv1)->sub(uv0);
				deltaUV2->set(uv2)->sub(uv0);
				auto r = 1.0f / (deltaUV1->getX() * deltaUV2->getY() - deltaUV1->getY() * deltaUV2->getX());
				auto tangent = (new Vector3(deltaPos1))->scale(deltaUV2->getY())->sub(tmpVector3->set(deltaPos2)->scale(deltaUV1->getY()))->scale(r);
				auto bitangent = (new Vector3(deltaPos2))->scale(deltaUV1->getX())->sub(tmpVector3->set(deltaPos1)->scale(deltaUV2->getX()))->scale(r);
				face->setTangentIndices(tangentsArrayList.size() + 0, tangentsArrayList.size() + 1, tangentsArrayList.size() + 2);
				face->setBitangentIndices(bitangentsArrayList.size() + 0, bitangentsArrayList.size() + 1, bitangentsArrayList.size() + 2);
				tangentsArrayList.push_back(tangent);
				tangentsArrayList.push_back(tangent);
				tangentsArrayList.push_back(tangent);
				bitangentsArrayList.push_back(bitangent);
				bitangentsArrayList.push_back(bitangent);
				bitangentsArrayList.push_back(bitangent);
			}
		}

	if (tangentsArrayList.size() > 0 && bitangentsArrayList.size() > 0) {
		group->setTangents(tangentsArrayList);
		group->setBitangents(bitangentsArrayList);
		auto tangents = group->getTangents();
		auto bitangents = group->getBitangents();
		for (auto faceEntity : *group->getFacesEntities()) 
		if (faceEntity->getMaterial() != nullptr && faceEntity->getMaterial()->hasNormalTexture() == true) {
			for (auto face : *faceEntity->getFaces())
				for (auto i = 0; i < 3; i++) {
				auto normal = (*normals)[(*face->getNormalIndices())[i]];
				auto tangent = (*tangents)[(*face->getTangentIndices())[i]];
				auto bitangent = (*bitangents)[(*face->getBitangentIndices())[i]];
				tangent->sub(tmpVector3->set(normal)->scale(Vector3::computeDotProduct(normal, tangent)))->normalize();
				if (Vector3::computeDotProduct(Vector3::computeCrossProduct(normal, tangent, tmpVector3), bitangent) < 0.0f) {
					tangent->scale(-1.0f);
				}
				bitangent->normalize();
			}
		}
	}
}

void ModelHelper::prepareForIndexedRendering(Model* model)
{
	clinit();
	prepareForIndexedRendering(model->getSubGroups());
}

void ModelHelper::prepareForIndexedRendering(map<wstring, Group*>* groups)
{
	clinit();
	for (auto it: *groups) {
		Group* group = it.second;
		auto groupVertices = group->getVertices();
		auto groupNormals = group->getNormals();
		auto groupTextureCoordinates = group->getTextureCoordinates();
		auto groupTangents = group->getTangents();
		auto groupBitangents = group->getBitangents();
		auto groupFaceCount = group->getFaceCount();
		auto verticeMapping = new int32_tArray(groupFaceCount * 3);
		auto indexedVertices = new Vector3Array(groupFaceCount * 3);
		auto indexedNormals = new Vector3Array(groupFaceCount * 3);
		auto indexedTextureCoordinates = groupTextureCoordinates != nullptr ? new TextureCoordinateArray(groupFaceCount * 3) : static_cast< TextureCoordinateArray* >(nullptr);
		auto indexedTangents = groupTangents != nullptr ? new Vector3Array(groupFaceCount * 3) : static_cast< Vector3Array* >(nullptr);
		auto indexedBitangents = groupBitangents != nullptr ? new Vector3Array(groupFaceCount * 3) : static_cast< Vector3Array* >(nullptr);
		auto preparedIndices = 0;
		for (auto facesEntity : *group->getFacesEntities()) {
			for (auto face : *facesEntity->getFaces()) {
				auto faceVertexIndices = face->getVertexIndices();
				auto faceNormalIndices = face->getNormalIndices();
				auto faceTextureIndices = face->getTextureCoordinateIndices();
				auto faceTangentIndices = face->getTangentIndices();
				auto faceBitangentIndices = face->getBitangentIndices();
				auto indexedFaceVertexIndices = new int32_tArray(3);
				for (auto idx = 0; idx < 3; idx++) {
					auto groupVertexIndex = (*faceVertexIndices)[idx];
					auto groupNormalIndex = (*faceNormalIndices)[idx];
					auto groupTextureCoordinateIndex = faceTextureIndices != nullptr ? (*faceTextureIndices)[idx] : 0;
					auto groupTangentIndex = faceTangentIndices != nullptr ? (*faceTangentIndices)[idx] : 0;
					auto groupBitangentIndex = faceBitangentIndices != nullptr ? (*faceBitangentIndices)[idx] : 0;
					auto vertex = (*groupVertices)[groupVertexIndex];
					auto normal = (*groupNormals)[groupNormalIndex];
					auto textureCoordinate = groupTextureCoordinates != nullptr ? (*groupTextureCoordinates)[groupTextureCoordinateIndex] : static_cast< TextureCoordinate* >(nullptr);
					auto tangent = groupTangents != nullptr ? (*groupTangents)[groupTangentIndex] : static_cast< Vector3* >(nullptr);
					auto bitangent = groupBitangents != nullptr ? (*groupBitangents)[groupBitangentIndex] : static_cast< Vector3* >(nullptr);
					auto newIndex = preparedIndices;
					for (auto i = 0; i < preparedIndices; i++)
					if ((*indexedVertices)[i]->equals(vertex) && (*indexedNormals)[i]->equals(normal) && (groupTextureCoordinates == nullptr || (*indexedTextureCoordinates)[i]->equals(textureCoordinate))&& (groupTangents == nullptr || (*indexedTangents)[i]->equals(tangent))&& (groupBitangents == nullptr || (*indexedBitangents)[i]->equals(bitangent))) {
						newIndex = i;
						break;
					}

					if (newIndex == preparedIndices)
						preparedIndices++;

					(*verticeMapping)[newIndex] = groupVertexIndex;
					indexedVertices->set(newIndex, vertex);
					indexedNormals->set(newIndex, normal);
					if (groupTextureCoordinates != nullptr)
						indexedTextureCoordinates->set(newIndex, textureCoordinate);

					if (groupTangents != nullptr)
						indexedTangents->set(newIndex, tangent);

					if (groupBitangents != nullptr)
						indexedBitangents->set(newIndex, bitangent);

					(*indexedFaceVertexIndices)[idx] = newIndex;
				}
				face->setIndexedRenderingIndices(indexedFaceVertexIndices);
			}
		}
		auto skinning = group->getSkinning();
		if (skinning != nullptr) {
			prepareForIndexedRendering(skinning, verticeMapping, preparedIndices);
		}
		auto vertices = new Vector3Array(preparedIndices);
		System::arraycopy(indexedVertices, 0, vertices, 0, preparedIndices);
		group->setVertices(vertices);
		auto normals = new Vector3Array(preparedIndices);
		System::arraycopy(indexedNormals, 0, normals, 0, preparedIndices);
		group->setNormals(normals);
		if (groupTextureCoordinates != nullptr) {
			auto textureCoordinates = new TextureCoordinateArray(preparedIndices);
			System::arraycopy(indexedTextureCoordinates, 0, textureCoordinates, 0, preparedIndices);
			group->setTextureCoordinates(textureCoordinates);
		}
		if (groupTangents != nullptr && groupBitangents != nullptr) {
			auto tangents = new Vector3Array(preparedIndices);
			System::arraycopy(indexedTangents, 0, tangents, 0, preparedIndices);
			group->setTangents(tangents);
			auto bitangents = new Vector3Array(preparedIndices);
			System::arraycopy(indexedBitangents, 0, bitangents, 0, preparedIndices);
			group->setBitangents(bitangents);
		}
		prepareForIndexedRendering(group->getSubGroups());
	}
}

void ModelHelper::prepareForIndexedRendering(Skinning* skinning, int32_tArray* vertexMapping, int32_t vertices)
{
	clinit();
	auto originalVerticesJointsWeights = skinning->getVerticesJointsWeights();
	auto verticesJointsWeights = new JointWeightArrayArray(vertices);
	for (auto i = 0; i < vertices; i++) {
		auto vertexOriginalMappedToIdx = (*vertexMapping)[i];
		verticesJointsWeights->set(i, new JointWeightArray((*originalVerticesJointsWeights)[vertexOriginalMappedToIdx]->length));
		for (auto j = 0; j < (*verticesJointsWeights)[i]->length; j++) {
			(*verticesJointsWeights)[i]->set(j, (*(*originalVerticesJointsWeights)[vertexOriginalMappedToIdx])[j]);
		}
	}
	skinning->setVerticesJointsWeights(verticesJointsWeights);
}

void ModelHelper::setupJoints(Model* model)
{
	clinit();
	auto groups = model->getGroups();
	for (auto it: *model->getSubGroups()) {
		Group* group = it.second;
		auto skinning = group->getSkinning();
		if (skinning != nullptr) {
			for (auto joint : *skinning->getJoints()) {
				auto jointGroupIt = groups->find(joint->getGroupId());
				if (jointGroupIt != groups->end()) {
					setJoint(jointGroupIt->second);
				}
			}
		}
	}
}

void ModelHelper::setJoint(Group* root)
{
	clinit();
	root->setJoint(true);
	for (auto it: *root->getSubGroups()) {
		Group* group = it.second;
		setJoint(group);
	}
}

void ModelHelper::fixAnimationLength(Model* model)
{
	clinit();
	auto defaultAnimation = model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT);
	if (defaultAnimation != nullptr) {
		for (auto it: *model->getSubGroups()) {
			Group* group = it.second;
			fixAnimationLength(group, defaultAnimation->getFrames());
		}
	}
}

void ModelHelper::fixAnimationLength(Group* root, int32_t frames)
{
	clinit();
	auto animation = root->getAnimation();
	vector<Matrix4x4>* transformationsMatrices;
	if (animation != nullptr) {
		transformationsMatrices = root->getAnimation()->getTransformationsMatrices();
		animation = root->createAnimation(frames);
		for (auto i = 0; i < transformationsMatrices->size(); i++) {
			(*animation->getTransformationsMatrices())[i].set(&(*transformationsMatrices)[i]);
		}
	}
	for (auto it: *root->getSubGroups()) {
		Group* group = it.second;
		fixAnimationLength(group, frames);
	}
}

void ModelHelper::createDefaultAnimation(Model* model, int32_t frames)
{
	clinit();
	auto defaultAnimation = model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT);
	if (defaultAnimation == nullptr) {
		model->addAnimationSetup(Model::ANIMATIONSETUP_DEFAULT, 0, frames - 1, true);
	} else {
		if (defaultAnimation->getStartFrame() != 0 || defaultAnimation->getEndFrame() != frames - 1) {
			_Console::println(static_cast< Object* >(u"Warning: default animation mismatch"_j));
		}
		if (frames - 1 > defaultAnimation->getEndFrame()) {
			_Console::println(static_cast< Object* >(u"Warning: default animation mismatch, will be fixed"_j));
			model->addAnimationSetup(Model::ANIMATIONSETUP_DEFAULT, 0, frames - 1, true);
		}
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ModelHelper::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.ModelHelper", 29);
    return c;
}

java::lang::Class* ModelHelper::getClass0()
{
	return class_();
}

