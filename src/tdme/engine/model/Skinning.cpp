// Generated from /tdme/src/tdme/engine/model/Skinning.java
#include <tdme/engine/model/Skinning.h>

#include <map>
#include <string>
#include <vector>

#include <java/io/Serializable.h>
#include <java/lang/Cloneable.h>
#include <java/lang/Float.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Arrays.h>
#include <tdme/engine/model/Joint.h>
#include <tdme/engine/model/JointWeight.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::map;
using std::wstring;
using std::vector;

using tdme::engine::model::Skinning;
using java::io::Serializable;
using java::lang::Cloneable;
using java::lang::Float;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Arrays;
using tdme::engine::model::Joint;
using tdme::engine::model::JointWeight;

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
typedef ::SubArray< ::tdme::engine::model::Joint, ::java::lang::ObjectArray > JointArray;
typedef ::SubArray< ::tdme::engine::model::JointWeight, ::java::lang::ObjectArray > JointWeightArray;
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

Skinning::Skinning(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Skinning::Skinning() 
	: Skinning(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void Skinning::ctor()
{
	super::ctor();
	weights = new floatArray(0);
	joints = new JointArray(0);
	verticesJointsWeights = __newMultiArray< JointWeightArrayArray >(0,0);
}

floatArray* Skinning::getWeights()
{
	return weights;
}

void Skinning::setWeights(floatArray* weights)
{
	this->weights = weights;
}

void Skinning::setWeights(const vector<float>& weights)
{
	this->weights = new floatArray(weights.size());
	int i = 0;
	for (float weight: weights) {
		(*this->weights)[i++] = weight;
	}
}

JointArray* Skinning::getJoints()
{
	return joints;
}

void Skinning::setJoints(JointArray* joints)
{
	this->joints = joints;
	setupJointsByName();
}

void Skinning::setJoints(const vector<Joint*>& joints)
{
	this->joints = new JointArray(joints.size());
	int i = 0;
	for (Joint* joint: joints) {
		this->joints->set(i++, joint);
	}
	setupJointsByName();
}

JointWeightArrayArray* Skinning::getVerticesJointsWeights()
{
	return verticesJointsWeights;
}

void Skinning::setVerticesJointsWeights(JointWeightArrayArray* verticesJointsWeights)
{
	this->verticesJointsWeights = verticesJointsWeights;
}

void Skinning::setVerticesJointsWeights(const vector<vector<JointWeight*>>& verticesJointsWeights)
{
	this->verticesJointsWeights = new JointWeightArrayArray(verticesJointsWeights.size());
	for (auto i = 0; i < verticesJointsWeights.size(); i++) {
		this->verticesJointsWeights->set(i, new JointWeightArray(verticesJointsWeights.at(i).size()));
		for (auto j = 0; j < verticesJointsWeights.at(i).size(); j++) {
			(*this->verticesJointsWeights)[i]->set(j, verticesJointsWeights.at(i).at(j));
		}
	}
}

void Skinning::setupJointsByName()
{
	for (auto i = 0; i < joints->length; i++) {
		auto joint = (*joints)[i];
		jointsByName[joint->getGroupId()] = joint;
	}
}

Joint* Skinning::getJointByName(const wstring& name)
{
	auto jointIt = jointsByName.find(name);
	if (jointIt != jointsByName.end()) {
		return jointIt->second;
	}
	return nullptr;
}

String* Skinning::toString()
{
	return ::java::lang::StringBuilder().append(u"Skinning [weights="_j)->append(Arrays::toString(weights))
		->append(u", joints="_j)
		->append(Arrays::toString(static_cast< ObjectArray* >(joints)))
		->append(u", verticesJointsWeights="_j)
		->append(Arrays::toString(static_cast< ObjectArray* >(verticesJointsWeights)))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Skinning::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.Skinning", 26);
    return c;
}

java::lang::Class* Skinning::getClass0()
{
	return class_();
}

