// Generated from /tdme/src/tdme/engine/fileio/models/TMReader.java
#include <tdme/engine/fileio/models/TMReader.h>

#include <java/io/File.h>
#include <java/io/IOException.h>
#include <java/io/InputStream.h>
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
using java::io::File;
using java::io::IOException;
using java::io::InputStream;
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
	InputStream* is = nullptr;
	{
		auto finally0 = finally([&] {
			if (is != nullptr) {
				is->close();
			}
		});
		try {
			is = _FileSystem::getInstance()->getInputStream(pathName, fileName);
			auto fileId = readString(is);
			if (fileId == nullptr || fileId->equals(u"TDME Model"_j) == false) {
				throw new ModelFileIOException(::java::lang::StringBuilder().append(u"File is not a TDME model file, file id = '"_j)->append(fileId)
					->append(u"'"_j)->toString());
			}
			auto version = new int8_tArray(3);
			(*version)[0] = readByte(is);
			(*version)[1] = readByte(is);
			(*version)[2] = readByte(is);
			if ((*version)[0] != 1 || (*version)[1] != 0 || (*version)[2] != 0) {
				throw new ModelFileIOException(::java::lang::StringBuilder().append(u"Version mismatch, should be 1.0.0, but is "_j)->append((*version)[0])
					->append(u"."_j)
					->append((*version)[1])
					->append(u"."_j)
					->append((*version)[2])->toString());
			}
			auto name = readString(is);
			auto upVector = Model_UpVector::valueOf(readString(is));
			auto rotationOrder = RotationOrder::valueOf(readString(is));
			auto boundingBox = new BoundingBox(new Vector3(readFloatArray(is)), new Vector3(readFloatArray(is)));
			auto model = new Model(::java::lang::StringBuilder().append(pathName)->append(File::separator)
				->append(fileName)->toString(), fileName, upVector, rotationOrder, boundingBox);
			model->setFPS(readFloat(is));
			model->getImportTransformationsMatrix()->set(readFloatArray(is));
			auto materialCount = readInt(is);
			for (auto i = 0; i < materialCount; i++) {
				auto material = readMaterial(is);
				model->getMaterials()->put(material->getId(), material);
			}
			readSubGroups(is, model, nullptr, model->getSubGroups());
			return model;
		} catch (IOException* ioe) {
			throw ioe;
		} catch (ModelFileIOException* mfioe) {
			throw mfioe;
		}
	}
}

bool TMReader::readBoolean(InputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	return readByte(is) == 1;
}

int8_t TMReader::readByte(InputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	auto i = is->read();
	if (i == -1) {
		throw new ModelFileIOException(u"End of stream"_j);
	}
	return static_cast< int8_t >(i);
}

int32_t TMReader::readInt(InputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	auto i = ((static_cast< int32_t >(readByte(is)) & 255) << 24) + ((static_cast< int32_t >(readByte(is)) & 255) << 16) + ((static_cast< int32_t >(readByte(is)) & 255) << 8)+ ((static_cast< int32_t >(readByte(is)) & 255) << 0);
	return i;
}

float TMReader::readFloat(InputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	auto i = readInt(is);
	return Float::intBitsToFloat(i);
}

String* TMReader::readString(InputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	if (readBoolean(is) == false) {
		return nullptr;
	} else {
		auto l = readInt(is);
		auto sb = new StringBuffer();
		for (auto i = 0; i < l; i++) {
			sb->append(static_cast< char16_t >(readByte(is)));
		}
		return sb->toString();
	}
}

floatArray* TMReader::readFloatArray(InputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	auto f = new floatArray(readInt(is));
	for (auto i = 0; i < f->length; i++) {
		(*f)[i] = readFloat(is);
	}
	return f;
}

Material* TMReader::readMaterial(InputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	auto id = readString(is);
	auto m = new Material(id);
	m->getAmbientColor()->set(readFloatArray(is));
	m->getDiffuseColor()->set(readFloatArray(is));
	m->getSpecularColor()->set(readFloatArray(is));
	m->getEmissionColor()->set(readFloatArray(is));
	m->setShininess(readFloat(is));
	auto diffuseTexturePathName = readString(is);
	auto diffuseTextureFileName = readString(is);
	if (diffuseTextureFileName != nullptr && diffuseTexturePathName != nullptr) {
		m->setDiffuseTexture(diffuseTexturePathName, diffuseTextureFileName);
	}
	auto specularTexturePathName = readString(is);
	auto specularTextureFileName = readString(is);
	if (specularTextureFileName != nullptr && specularTexturePathName != nullptr) {
		m->setSpecularTexture(specularTexturePathName, specularTextureFileName);
	}
	auto normalTexturePathName = readString(is);
	auto normalTextureFileName = readString(is);
	if (normalTextureFileName != nullptr && normalTexturePathName != nullptr) {
		m->setNormalTexture(normalTexturePathName, normalTextureFileName);
	}
	auto displacementTexturePathName = readString(is);
	auto displacementTextureFileName = readString(is);
	if (displacementTextureFileName != nullptr && displacementTexturePathName != nullptr) {
		m->setDisplacementTexture(displacementTexturePathName, displacementTextureFileName);
	}
	return m;
}

Vector3Array* TMReader::readVertices(InputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	if (readBoolean(is) == false) {
		return nullptr;
	} else {
		auto v = new Vector3Array(readInt(is));
		for (auto i = 0; i < v->length; i++) {
			v->set(i, new Vector3(readFloatArray(is)));
		}
		return v;
	}
}

TextureCoordinateArray* TMReader::readTextureCoordinates(InputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	if (readBoolean(is) == false) {
		return nullptr;
	} else {
		auto tc = new TextureCoordinateArray(readInt(is));
		for (auto i = 0; i < tc->length; i++) {
			tc->set(i, new TextureCoordinate(readFloatArray(is)));
		}
		return tc;
	}
}

int32_tArray* TMReader::readIndices(InputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	if (readBoolean(is) == false) {
		return nullptr;
	} else {
		auto indices = new int32_tArray(readInt(is));
		for (auto i = 0; i < indices->length; i++) {
			(*indices)[i] = readInt(is);
		}
		return indices;
	}
}

Animation* TMReader::readAnimation(InputStream* is, Group* g) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	if (readBoolean(is) == false) {
		return nullptr;
	} else {
		g->createAnimation(readInt(is));
		for (auto i = 0; i < g->getAnimation()->getTransformationsMatrices()->length; i++) {
			(*g->getAnimation()->getTransformationsMatrices())[i]->set(readFloatArray(is));
		}
		ModelHelper::createDefaultAnimation(g->getModel(), g->getAnimation()->getTransformationsMatrices()->length);
		return g->getAnimation();
	}
}

void TMReader::readFacesEntities(InputStream* is, Group* g) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	auto facesEntities = new FacesEntityArray(readInt(is));
	for (auto i = 0; i < facesEntities->length; i++) {
		facesEntities->set(i, new FacesEntity(g, readString(is)));
		if (readBoolean(is) == true) {
			(*facesEntities)[i]->setMaterial(java_cast< Material* >(g->getModel()->getMaterials()->get(readString(is))));
		}
		auto faces = new FaceArray(readInt(is));
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

Joint* TMReader::readSkinningJoint(InputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	auto joint = new Joint(readString(is));
	joint->getBindMatrix()->set(readFloatArray(is));
	return joint;
}

JointWeight* TMReader::readSkinningJointWeight(InputStream* is) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	return new JointWeight(readInt(is), readInt(is));
}

void TMReader::readSkinning(InputStream* is, Group* g) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	if (readBoolean(is) == true) {
		auto skinning = g->createSkinning();
		skinning->setWeights(readFloatArray(is));
		auto joints = new JointArray(readInt(is));
		for (auto i = 0; i < joints->length; i++) {
			joints->set(i, readSkinningJoint(is));
		}
		skinning->setJoints(joints);
		auto verticesJointsWeight = new JointWeightArrayArray(readInt(is));
		for (auto i = 0; i < verticesJointsWeight->length; i++) {
			verticesJointsWeight->set(i, new JointWeightArray(readInt(is)));
			for (auto j = 0; j < (*verticesJointsWeight)[i]->length; j++) {
				(*verticesJointsWeight)[i]->set(j, readSkinningJointWeight(is));
			}
		}
		skinning->setVerticesJointsWeights(verticesJointsWeight);
	}
}

void TMReader::readSubGroups(InputStream* is, Model* model, Group* parentGroup, _HashMap* subGroups) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	auto subGroupCount = readInt(is);
	for (auto i = 0; i < subGroupCount; i++) {
		auto subGroup = readGroup(is, model, parentGroup);
		subGroups->put(subGroup->getId(), subGroup);
		model->getGroups()->put(subGroup->getId(), subGroup);
	}
}

Group* TMReader::readGroup(InputStream* is, Model* model, Group* parentGroup) /* throws(IOException, ModelFileIOException) */
{
	clinit();
	auto group = new Group(model, parentGroup, readString(is), readString(is));
	group->setJoint(readBoolean(is));
	group->getTransformationsMatrix()->set(readFloatArray(is));
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

