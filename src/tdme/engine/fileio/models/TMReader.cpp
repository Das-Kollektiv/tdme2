// Generated from /tdme/src/tdme/engine/fileio/models/TMReader.java
#include <tdme/engine/fileio/models/TMReader.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Cloneable.h>
#include <java/lang/Float.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuffer.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/fileio/models/ModelFileIOException.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model_UpVector.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/_HashMap.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::engine::fileio::models::TMReader;
using tdme::engine::fileio::models::TMReaderInputStream;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::ClassCastException;
using java::lang::Cloneable;
using java::lang::Float;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuffer;
using java::lang::StringBuilder;
using tdme::engine::fileio::models::ModelFileIOException;
using tdme::engine::model::Animation;
using tdme::engine::model::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Group;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;
using tdme::engine::model::Material;
using tdme::engine::model::Model_UpVector;
using tdme::engine::model::Model;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::primitives::BoundingBox;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
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
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

namespace
{
template<typename F>
struct finally_
{
    finally_(F f) : f(f), moved(false) { }
    finally_(finally_ &&x) : f(x.f), moved(false) { x.moved = true; }
    ~finally_() { if(!moved) f(); }
private:
    finally_(const finally_&); finally_& operator=(const finally_&);
    F f;
    bool moved;
};

template<typename F> finally_<F> finally(F f) { return finally_<F>(f); }
}
TMReader::TMReader(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

TMReader::TMReader()
	: TMReader(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Model* TMReader::read(String* pathName, String* fileName) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	TMReaderInputStream* is = nullptr;
	{
		auto finally0 = finally([&] {
			if (is != nullptr) {
				delete is;
			}
		});
		try {
			is = new TMReaderInputStream(_FileSystem::getInstance()->getContent(pathName, fileName));
			auto fileId = is->readString();
			if (fileId == nullptr || fileId->equals(u"TDME Model"_j) == false) {
				throw new ModelFileIOException(::java::lang::StringBuilder().append(u"File is not a TDME model file, file id = '"_j)->append(fileId)
					->append(u"'"_j)->toString());
			}
			auto version = new int8_tArray(3);
			(*version)[0] = is->readByte();
			(*version)[1] = is->readByte();
			(*version)[2] = is->readByte();
			if ((*version)[0] != 1 || (*version)[1] != 0 || (*version)[2] != 0) {
				throw new ModelFileIOException(::java::lang::StringBuilder().append(u"Version mismatch, should be 1.0.0, but is "_j)->append((*version)[0])
					->append(u"."_j)
					->append((*version)[1])
					->append(u"."_j)
					->append((*version)[2])->toString());
			}
			auto name = is->readString();
			auto upVector = Model_UpVector::valueOf(is->readString());
			auto rotationOrder = RotationOrder::valueOf(is->readString());
			auto boundingBox = new BoundingBox(new Vector3(is->readFloatArray()), new Vector3(is->readFloatArray()));
			auto model = new Model(
				::java::lang::StringBuilder().
				 append(pathName)->
				 append(L'/')->
				 append(fileName)->
				 toString(),
				fileName,
				upVector,
				rotationOrder,
				boundingBox
			);
			model->setFPS(is->readFloat());
			model->getImportTransformationsMatrix()->set(is->readFloatArray());
			auto materialCount = is->readInt();
			for (auto i = 0; i < materialCount; i++) {
				auto material = readMaterial(is);
				model->getMaterials()->put(material->getId(), material);
			}
			readSubGroups(is, model, nullptr, model->getSubGroups());
			return model;
		}/* catch (IOException* ioe) {
			throw ioe;
		}*/ catch (ModelFileIOException* mfioe) {
			throw mfioe;
		}
	}
}

Material* TMReader::readMaterial(TMReaderInputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	auto id = is->readString();
	auto m = new Material(id);
	m->getAmbientColor()->set(is->readFloatArray());
	m->getDiffuseColor()->set(is->readFloatArray());
	m->getSpecularColor()->set(is->readFloatArray());
	m->getEmissionColor()->set(is->readFloatArray());
	m->setShininess(is->readFloat());
	auto diffuseTexturePathName = is->readString();
	auto diffuseTextureFileName = is->readString();
	if (diffuseTextureFileName != nullptr && diffuseTexturePathName != nullptr) {
		m->setDiffuseTexture(diffuseTexturePathName, diffuseTextureFileName);
	}
	auto specularTexturePathName = is->readString();
	auto specularTextureFileName = is->readString();
	if (specularTextureFileName != nullptr && specularTexturePathName != nullptr) {
		m->setSpecularTexture(specularTexturePathName, specularTextureFileName);
	}
	auto normalTexturePathName = is->readString();
	auto normalTextureFileName = is->readString();
	if (normalTextureFileName != nullptr && normalTexturePathName != nullptr) {
		m->setNormalTexture(normalTexturePathName, normalTextureFileName);
	}
	auto displacementTexturePathName = is->readString();
	auto displacementTextureFileName = is->readString();
	if (displacementTextureFileName != nullptr && displacementTexturePathName != nullptr) {
		m->setDisplacementTexture(displacementTexturePathName, displacementTextureFileName);
	}
	return m;
}

Vector3Array* TMReader::readVertices(TMReaderInputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	if (is->readBoolean() == false) {
		return nullptr;
	} else {
		auto v = new Vector3Array(is->readInt());
		for (auto i = 0; i < v->length; i++) {
			v->set(i, new Vector3(is->readFloatArray()));
		}
		return v;
	}
}

TextureCoordinateArray* TMReader::readTextureCoordinates(TMReaderInputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	if (is->readBoolean() == false) {
		return nullptr;
	} else {
		auto tc = new TextureCoordinateArray(is->readInt());
		for (auto i = 0; i < tc->length; i++) {
			tc->set(i, new TextureCoordinate(is->readFloatArray()));
		}
		return tc;
	}
}

int32_tArray* TMReader::readIndices(TMReaderInputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	if (is->readBoolean() == false) {
		return nullptr;
	} else {
		auto indices = new int32_tArray(is->readInt());
		for (auto i = 0; i < indices->length; i++) {
			(*indices)[i] = is->readInt();
		}
		return indices;
	}
}

Animation* TMReader::readAnimation(TMReaderInputStream* is, Group* g) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	if (is->readBoolean() == false) {
		return nullptr;
	} else {
		g->createAnimation(is->readInt());
		for (auto i = 0; i < g->getAnimation()->getTransformationsMatrices()->length; i++) {
			(*g->getAnimation()->getTransformationsMatrices())[i]->set(is->readFloatArray());
		}
		ModelHelper::createDefaultAnimation(g->getModel(), g->getAnimation()->getTransformationsMatrices()->length);
		return g->getAnimation();
	}
}

void TMReader::readFacesEntities(TMReaderInputStream* is, Group* g) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	auto facesEntities = new FacesEntityArray(is->readInt());
	for (auto i = 0; i < facesEntities->length; i++) {
		facesEntities->set(i, new FacesEntity(g, is->readString()));
		if (is->readBoolean() == true) {
			(*facesEntities)[i]->setMaterial(java_cast< Material* >(g->getModel()->getMaterials()->get(is->readString())));
		}
		auto faces = new FaceArray(is->readInt());
		for (auto j = 0; j < faces->length; j++) {
			auto vertexIndices = readIndices(is);
			auto normalIndices = readIndices(is);
			faces->set(j, new Face(g, (*vertexIndices)[0], (*vertexIndices)[1], (*vertexIndices)[2], (*normalIndices)[0], (*normalIndices)[1], (*normalIndices)[2]));
			auto textureCoordinateIndices = readIndices(is);
			if (textureCoordinateIndices != nullptr && textureCoordinateIndices->length > 0) {
				(*faces)[j]->setTextureCoordinateIndices((*textureCoordinateIndices)[0], (*textureCoordinateIndices)[1], (*textureCoordinateIndices)[2]);
			}
			auto tangentIndices = readIndices(is);
			auto bitangentIndices = readIndices(is);
			if (tangentIndices != nullptr && tangentIndices->length > 0 && bitangentIndices != nullptr && bitangentIndices->length > 0) {
				(*faces)[j]->setTangentIndices((*tangentIndices)[0], (*tangentIndices)[1], (*tangentIndices)[2]);
				(*faces)[j]->setBitangentIndices((*bitangentIndices)[0], (*bitangentIndices)[1], (*bitangentIndices)[2]);
			}
		}
		(*facesEntities)[i]->setFaces(faces);
	}
	g->setFacesEntities(facesEntities);
}

Joint* TMReader::readSkinningJoint(TMReaderInputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	auto joint = new Joint(is->readString());
	joint->getBindMatrix()->set(is->readFloatArray());
	return joint;
}

JointWeight* TMReader::readSkinningJointWeight(TMReaderInputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	return new JointWeight(is->readInt(), is->readInt());
}

void TMReader::readSkinning(TMReaderInputStream* is, Group* g) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	if (is->readBoolean() == true) {
		auto skinning = g->createSkinning();
		skinning->setWeights(is->readFloatArray());
		auto joints = new JointArray(is->readInt());
		for (auto i = 0; i < joints->length; i++) {
			joints->set(i, readSkinningJoint(is));
		}
		skinning->setJoints(joints);
		auto verticesJointsWeight = new JointWeightArrayArray(is->readInt());
		for (auto i = 0; i < verticesJointsWeight->length; i++) {
			verticesJointsWeight->set(i, new JointWeightArray(is->readInt()));
			for (auto j = 0; j < (*verticesJointsWeight)[i]->length; j++) {
				(*verticesJointsWeight)[i]->set(j, readSkinningJointWeight(is));
			}
		}
		skinning->setVerticesJointsWeights(verticesJointsWeight);
	}
}

void TMReader::readSubGroups(TMReaderInputStream* is, Model* model, Group* parentGroup, _HashMap* subGroups) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	auto subGroupCount = is->readInt();
	for (auto i = 0; i < subGroupCount; i++) {
		auto subGroup = readGroup(is, model, parentGroup);
		subGroups->put(subGroup->getId(), subGroup);
		model->getGroups()->put(subGroup->getId(), subGroup);
	}
}

Group* TMReader::readGroup(TMReaderInputStream* is, Model* model, Group* parentGroup) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	auto group = new Group(model, parentGroup, is->readString(), is->readString());
	group->setJoint(is->readBoolean());
	group->getTransformationsMatrix()->set(is->readFloatArray());
	group->setVertices(readVertices(is));
	group->setNormals(readVertices(is));
	group->setTextureCoordinates(readTextureCoordinates(is));
	group->setTangents(readVertices(is));
	group->setBitangents(readVertices(is));
	readAnimation(is, group);
	readSkinning(is, group);
	readFacesEntities(is, group);
	group->determineFeatures();
	readSubGroups(is, model, parentGroup, group->getSubGroups());
	return group;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TMReader::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.fileio.models.TMReader", 34);
    return c;
}

java::lang::Class* TMReader::getClass0()
{
	return class_();
}

