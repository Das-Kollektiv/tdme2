// Generated from /tdme/src/tdme/engine/fileio/models/TMWriter.java
#include <tdme/engine/fileio/models/TMWriter.h>

#include <java/io/IOException.h>
#include <java/io/OutputStream.h>
#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Cloneable.h>
#include <java/lang/Float.h>
#include <java/lang/NullPointerException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/util/Iterator.h>
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
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/Skinning.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/_HashMap_ValuesIterator.h>
#include <tdme/utils/_HashMap.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::engine::fileio::models::TMWriter;
using java::io::IOException;
using java::io::OutputStream;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::ClassCastException;
using java::lang::Cloneable;
using java::lang::Float;
using java::lang::NullPointerException;
using java::lang::Object;
using java::lang::String;
using java::util::Iterator;
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
using tdme::engine::model::RotationOrder;
using tdme::engine::model::Skinning;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::primitives::BoundingBox;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::_HashMap_ValuesIterator;
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
TMWriter::TMWriter(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

TMWriter::TMWriter()
	: TMWriter(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void TMWriter::write(Model* model, String* pathName, String* fileName) /* throws(IOException) */
{
	clinit();
	OutputStream* os = nullptr;
	{
		auto finally0 = finally([&] {
			if (os != nullptr) {
				os->flush();
				os->close();
			}
		});
		try {
			os = _FileSystem::getInstance()->getOutputStream(pathName, fileName);
			writeString(os, u"TDME Model"_j);
			writeByte(os, static_cast< int8_t >(1));
			writeByte(os, static_cast< int8_t >(0));
			writeByte(os, static_cast< int8_t >(0));
			writeString(os, model->getName());
			writeString(os, model->getUpVector()->toString());
			writeString(os, model->getRotationOrder()->toString());
			writeFloatArray(os, model->getBoundingBox()->getMin()->getArray());
			writeFloatArray(os, model->getBoundingBox()->getMax()->getArray());
			writeFloat(os, model->getFPS());
			writeFloatArray(os, model->getImportTransformationsMatrix()->getArray());
			writeInt(os, model->getMaterials()->size());
			for (auto _i = model->getMaterials()->getValuesIterator()->iterator(); _i->hasNext(); ) {
				Material* material = java_cast< Material* >(_i->next());
				{
					writeMaterial(os, material);
				}
			}
			writeSubGroups(os, model->getSubGroups());
		} catch (IOException* ioe) {
			throw ioe;
		}
	}
}

void TMWriter::writeBoolean(OutputStream* os, bool b) /* throws(IOException) */
{
	clinit();
	os->write(static_cast< int32_t >(static_cast< int8_t >((b == true ? 1 : 0))));
}

void TMWriter::writeByte(OutputStream* os, int8_t b) /* throws(IOException) */
{
	clinit();
	os->write(static_cast< int32_t >(b));
}

void TMWriter::writeInt(OutputStream* os, int32_t i) /* throws(IOException) */
{
	clinit();
	os->write((i >> 24) & 255);
	os->write((i >> 16) & 255);
	os->write((i >> 8) & 255);
	os->write((i >> 0) & 255);
}

void TMWriter::writeFloat(OutputStream* os, float f) /* throws(IOException) */
{
	clinit();
	writeInt(os, Float::floatToIntBits(f));
}

void TMWriter::writeString(OutputStream* os, String* s) /* throws(IOException) */
{
	clinit();
	if (s == nullptr) {
		writeBoolean(os, false);
	} else {
		writeBoolean(os, true);
		writeInt(os, s->length());
		for (auto i = 0; i < s->length(); i++) {
			writeByte(os, static_cast< int8_t >(s->charAt(i)));
		}
	}
}

void TMWriter::writeFloatArray(OutputStream* os, floatArray* f) /* throws(IOException) */
{
	clinit();
	writeInt(os, f->length);
	for (auto i = 0; i < f->length; i++) {
		writeFloat(os, (*f)[i]);
	}
}

void TMWriter::writeMaterial(OutputStream* os, Material* m) /* throws(IOException) */
{
	clinit();
	writeString(os, m->getId());
	writeFloatArray(os, m->getAmbientColor()->getArray());
	writeFloatArray(os, m->getDiffuseColor()->getArray());
	writeFloatArray(os, m->getSpecularColor()->getArray());
	writeFloatArray(os, m->getEmissionColor()->getArray());
	writeFloat(os, m->getShininess());
	writeString(os, m->getDiffuseTexturePathName());
	writeString(os, m->getDiffuseTextureFileName());
	writeString(os, m->getSpecularTexturePathName());
	writeString(os, m->getSpecularTextureFileName());
	writeString(os, m->getNormalTexturePathName());
	writeString(os, m->getNormalTextureFileName());
	writeString(os, m->getDisplacementTexturePathName());
	writeString(os, m->getDisplacementTextureFileName());
}

void TMWriter::writeVertices(OutputStream* os, Vector3Array* v) /* throws(IOException) */
{
	clinit();
	if (v == nullptr) {
		writeBoolean(os, false);
	} else {
		writeBoolean(os, true);
		writeInt(os, v->length);
		for (auto i = 0; i < v->length; i++) {
			writeFloatArray(os, (*v)[i]->getArray());
		}
	}
}

void TMWriter::writeTextureCoordinates(OutputStream* os, TextureCoordinateArray* tc) /* throws(IOException) */
{
	clinit();
	if (tc == nullptr) {
		writeBoolean(os, false);
	} else {
		writeBoolean(os, true);
		writeInt(os, tc->length);
		for (auto i = 0; i < tc->length; i++) {
			writeFloatArray(os, (*tc)[i]->getArray());
		}
	}
}

void TMWriter::writeIndices(OutputStream* os, int32_tArray* indices) /* throws(IOException) */
{
	clinit();
	if (indices == nullptr) {
		writeBoolean(os, false);
	} else {
		writeBoolean(os, true);
		writeInt(os, indices->length);
		for (auto i = 0; i < indices->length; i++) {
			writeInt(os, (*indices)[i]);
		}
	}
}

void TMWriter::writeAnimation(OutputStream* os, Animation* a) /* throws(IOException) */
{
	clinit();
	if (a == nullptr) {
		writeBoolean(os, false);
	} else {
		writeBoolean(os, true);
		writeInt(os, a->getTransformationsMatrices()->length);
		for (auto i = 0; i < a->getTransformationsMatrices()->length; i++) {
			writeFloatArray(os, (*a->getTransformationsMatrices())[i]->getArray());
		}
	}
}

void TMWriter::writeFacesEntities(OutputStream* os, FacesEntityArray* facesEntities) /* throws(IOException) */
{
	clinit();
	writeInt(os, facesEntities->length);
	for (auto i = 0; i < facesEntities->length; i++) {
		auto fe = (*facesEntities)[i];
		writeString(os, fe->getId());
		if (fe->getMaterial() == nullptr) {
			writeBoolean(os, false);
		} else {
			writeBoolean(os, true);
			writeString(os, fe->getMaterial()->getId());
		}
		writeInt(os, fe->getFaces()->length);
		for (auto j = 0; j < fe->getFaces()->length; j++) {
			auto f = (*fe->getFaces())[j];
			writeIndices(os, f->getVertexIndices());
			writeIndices(os, f->getNormalIndices());
			writeIndices(os, f->getTextureCoordinateIndices());
			writeIndices(os, f->getTangentIndices());
			writeIndices(os, f->getBitangentIndices());
		}
	}
}

void TMWriter::writeSkinningJoint(OutputStream* os, Joint* joint) /* throws(IOException) */
{
	clinit();
	writeString(os, joint->getGroupId());
	writeFloatArray(os, joint->getBindMatrix()->getArray());
}

void TMWriter::writeSkinningJointWeight(OutputStream* os, JointWeight* jointWeight) /* throws(IOException) */
{
	clinit();
	writeInt(os, jointWeight->getJointIndex());
	writeInt(os, jointWeight->getWeightIndex());
}

void TMWriter::writeSkinning(OutputStream* os, Skinning* skinning) /* throws(IOException) */
{
	clinit();
	if (skinning == nullptr) {
		writeBoolean(os, false);
	} else {
		writeBoolean(os, true);
		writeFloatArray(os, skinning->getWeights());
		writeInt(os, skinning->getJoints()->length);
		for (auto i = 0; i < skinning->getJoints()->length; i++) {
			writeSkinningJoint(os, (*skinning->getJoints())[i]);
		}
		writeInt(os, skinning->getVerticesJointsWeights()->length);
		for (auto i = 0; i < skinning->getVerticesJointsWeights()->length; i++) {
			writeInt(os, (*skinning->getVerticesJointsWeights())[i]->length);
			for (auto j = 0; j < (*skinning->getVerticesJointsWeights())[i]->length; j++) {
				writeSkinningJointWeight(os, (*(*skinning->getVerticesJointsWeights())[i])[j]);
			}
		}
	}
}

void TMWriter::writeSubGroups(OutputStream* os, _HashMap* subGroups) /* throws(IOException) */
{
	clinit();
	writeInt(os, subGroups->size());
	for (auto _i = subGroups->getValuesIterator()->iterator(); _i->hasNext(); ) {
		Group* subGroup = java_cast< Group* >(_i->next());
		{
			writeGroup(os, subGroup);
		}
	}
}

void TMWriter::writeGroup(OutputStream* os, Group* g) /* throws(IOException) */
{
	clinit();
	writeString(os, g->getId());
	writeString(os, g->getName());
	writeBoolean(os, g->isJoint());
	writeFloatArray(os, g->getTransformationsMatrix()->getArray());
	writeVertices(os, g->getVertices());
	writeVertices(os, g->getNormals());
	writeTextureCoordinates(os, g->getTextureCoordinates());
	writeVertices(os, g->getTangents());
	writeVertices(os, g->getBitangents());
	writeAnimation(os, g->getAnimation());
	writeSkinning(os, g->getSkinning());
	writeFacesEntities(os, g->getFacesEntities());
	writeSubGroups(os, g->getSubGroups());
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TMWriter::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.fileio.models.TMWriter", 34);
    return c;
}

java::lang::Class* TMWriter::getClass0()
{
	return class_();
}

