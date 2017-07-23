// Generated from /tdme/src/tdme/engine/model/Model.java
#include <tdme/engine/model/Model.h>

#include <map>
#include <string>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Iterator.h>
#include <tdme/engine/ModelUtilities.h>
#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/model/Animation.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/model/Model_UpVector.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/object/Object3DModelInternal.h>
#include <tdme/math/Matrix4x4.h>
#include <ObjectArray.h>
#include <SubArray.h>

using std::map;
using std::wstring;

using tdme::engine::model::Model;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Iterator;
using tdme::engine::ModelUtilities;
using tdme::engine::Object3DModel;
using tdme::engine::model::Animation;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Group;
using tdme::engine::model::Material;
using tdme::engine::model::Model_UpVector;
using tdme::engine::model::RotationOrder;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::object::Object3DModelInternal;
using tdme::math::Matrix4x4;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace math {
typedef ::SubArray< ::tdme::math::Matrix4x4, ::java::lang::ObjectArray > Matrix4x4Array;
}  // namespace math
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

Model::Model(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Model::Model(String* id, String* name, Model_UpVector* upVector, RotationOrder* rotationOrder, BoundingBox* boundingBox) 
	: Model(*static_cast< ::default_init_tag* >(0))
{
	ctor(id,name,upVector,rotationOrder,boundingBox);
}

wstring Model::ANIMATIONSETUP_DEFAULT;

constexpr float Model::FPS_DEFAULT;

void Model::ctor(String* id, String* name, Model_UpVector* upVector, RotationOrder* rotationOrder, BoundingBox* boundingBox)
{
	super::ctor();
	this->id = id;
	this->name = name;
	this->upVector = upVector;
	this->rotationOrder = rotationOrder;
	hasSkinning_ = false;
	fps = FPS_DEFAULT;
	importTransformationsMatrix = (new Matrix4x4())->identity();
	this->boundingBox = boundingBox;
}

String* Model::getId()
{
	return id;
}

void Model::setId(String* id)
{
	this->id = id;
}

String* Model::getName()
{
	return name;
}

Model_UpVector* Model::getUpVector()
{
	return upVector;
}

RotationOrder* Model::getRotationOrder()
{
	return rotationOrder;
}

map<wstring, Material*>* Model::getMaterials()
{
	return &materials;
}

map<wstring, Group*>* Model::getGroups()
{
	return &groups;
}

Group* Model::getGroupById(String* id)
{
	auto groupIt = groups.find(id->getCPPWString());
	if (groupIt != groups.end()) {
		return groupIt->second;
	}
	return nullptr;

}

map<wstring, Group*>* Model::getSubGroups()
{
	return &subGroups;
}

Group* Model::getSubGroupById(String* id)
{
	auto groupIt = subGroups.find(id->getCPPWString());
	if (groupIt != subGroups.end()) {
		return groupIt->second;
	}
	return nullptr;
}

bool Model::hasSkinning()
{
	return hasSkinning_;
}

void Model::setHasSkinning(bool hasSkinning)
{
	this->hasSkinning_ = hasSkinning;
}

float Model::getFPS()
{
	return fps;
}

void Model::setFPS(float fps)
{
	this->fps = fps;
}

AnimationSetup* Model::addAnimationSetup(const wstring& id, int32_t startFrame, int32_t endFrame, bool loop)
{
	auto animationSetup = new AnimationSetup(this, id, startFrame, endFrame, loop, L"");
	animationSetups[id] = animationSetup;
	return animationSetup;
}

AnimationSetup* Model::addOverlayAnimationSetup(const wstring& id, const wstring& overlayFromGroupId, int32_t startFrame, int32_t endFrame, bool loop)
{
	auto animationSetup = new AnimationSetup(this, id, startFrame, endFrame, loop, overlayFromGroupId);
	animationSetups[id] = animationSetup;
	return animationSetup;
}

AnimationSetup* Model::getAnimationSetup(const wstring& id)
{
	auto animationSetupIt = animationSetups.find(id);
	if (animationSetupIt != animationSetups.end()) {
		return animationSetupIt->second;
	}
	return nullptr;
}

map<wstring, AnimationSetup*>* Model::getAnimationSetups()
{
	return &animationSetups;
}

bool Model::hasAnimations()
{
	return animationSetups.size() > 0;
}

Matrix4x4* Model::getImportTransformationsMatrix()
{
	return importTransformationsMatrix;
}

BoundingBox* Model::getBoundingBox()
{
	if (boundingBox == nullptr) {
		boundingBox = ModelUtilities::createBoundingBox(static_cast< Object3DModelInternal* >(new Object3DModel(this)));
	}
	return boundingBox;
}

Matrix4x4* Model::computeTransformationsMatrix(int32_t frame, String* groupId)
{
	return computeTransformationsMatrix(&subGroups, importTransformationsMatrix, frame, groupId);
}

Matrix4x4* Model::computeTransformationsMatrix(map<wstring, Group*>* groups, Matrix4x4* parentTransformationsMatrix, int32_t frame, String* groupId)
{
	for (auto it: *groups) {
		Group* group = it.second;
		Matrix4x4* transformationsMatrix = nullptr;
		auto animation = group->getAnimation();
		if (animation != nullptr) {
			auto animationMatrices = animation->getTransformationsMatrices();
			transformationsMatrix = (*animationMatrices)[frame % animationMatrices->length]->clone();
		}
		if (transformationsMatrix == nullptr) {
			transformationsMatrix = group->getTransformationsMatrix()->clone();
		} else {
			transformationsMatrix->multiply(group->getTransformationsMatrix());
		}
		if (parentTransformationsMatrix != nullptr) {
			transformationsMatrix->multiply(parentTransformationsMatrix);
		}
		if (group->getId() == groupId->getCPPWString())
			return transformationsMatrix;

		auto subGroups = group->getSubGroups();
		if (subGroups->size() > 0) {
			auto tmp = computeTransformationsMatrix(subGroups, transformationsMatrix, frame, groupId);
			if (tmp != nullptr)
				return tmp;

		}
	}

	return nullptr;
}

String* Model::toString()
{
	return ::java::lang::StringBuilder().
		append(u"Model [name="_j)->
		append(name)->
		/*
		// TODO: implement me!
		append(u", subGroups="_j)->
		append(static_cast< Object* >(subGroups))->
		*/
		append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Model::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.Model", 23);
    return c;
}

void Model::clinit()
{
struct string_init_ {
	string_init_() {
		ANIMATIONSETUP_DEFAULT = L"tdme.default";
	}
	};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* Model::getClass0()
{
	return class_();
}

