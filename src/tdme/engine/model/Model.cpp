// Generated from /tdme/src/tdme/engine/model/Model.java
#include <tdme/engine/model/Model.h>

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
#include <tdme/utils/_HashMap_ValuesIterator.h>
#include <tdme/utils/_HashMap.h>
#include <ObjectArray.h>
#include <SubArray.h>

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
using tdme::engine::model::Model_UpVector;
using tdme::engine::model::RotationOrder;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::object::Object3DModelInternal;
using tdme::math::Matrix4x4;
using tdme::utils::_HashMap_ValuesIterator;
using tdme::utils::_HashMap;

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

String* Model::ANIMATIONSETUP_DEFAULT;

constexpr float Model::FPS_DEFAULT;

void Model::ctor(String* id, String* name, Model_UpVector* upVector, RotationOrder* rotationOrder, BoundingBox* boundingBox)
{
	super::ctor();
	this->id = id;
	this->name = name;
	this->upVector = upVector;
	this->rotationOrder = rotationOrder;
	materials = new _HashMap();
	groups = new _HashMap();
	subGroups = new _HashMap();
	hasSkinning_ = false;
	fps = FPS_DEFAULT;
	animationSetups = new _HashMap();
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

_HashMap* Model::getMaterials()
{
	return materials;
}

_HashMap* Model::getGroups()
{
	return groups;
}

Group* Model::getGroupById(String* id)
{
	return java_cast< Group* >(groups->get(id));
}

_HashMap* Model::getSubGroups()
{
	return subGroups;
}

Group* Model::getSubGroupById(String* id)
{
	return java_cast< Group* >(subGroups->get(id));
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

AnimationSetup* Model::addAnimationSetup(String* id, int32_t startFrame, int32_t endFrame, bool loop)
{
	auto animationSetup = new AnimationSetup(this, id, startFrame, endFrame, loop, nullptr);
	animationSetups->put(id, animationSetup);
	return animationSetup;
}

AnimationSetup* Model::addOverlayAnimationSetup(String* id, String* overlayFromGroupId, int32_t startFrame, int32_t endFrame, bool loop)
{
	auto animationSetup = new AnimationSetup(this, id, startFrame, endFrame, loop, overlayFromGroupId);
	animationSetups->put(id, animationSetup);
	return animationSetup;
}

AnimationSetup* Model::getAnimationSetup(String* id)
{
	return java_cast< AnimationSetup* >(animationSetups->get(id));
}

_HashMap* Model::getAnimationSetups()
{
	return animationSetups;
}

bool Model::hasAnimations()
{
	return animationSetups->size() > 0;
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
	return computeTransformationsMatrix(subGroups, importTransformationsMatrix, frame, groupId);
}

Matrix4x4* Model::computeTransformationsMatrix(_HashMap* groups, Matrix4x4* parentTransformationsMatrix, int32_t frame, String* groupId)
{
	for (auto _i = groups->getValuesIterator()->iterator(); _i->hasNext(); ) {
		Group* group = java_cast< Group* >(_i->next());
		{
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
			if (group->getId()->equals(groupId))
				return transformationsMatrix;

			auto subGroups = group->getSubGroups();
			if (subGroups->size() > 0) {
				auto tmp = computeTransformationsMatrix(subGroups, transformationsMatrix, frame, groupId);
				if (tmp != nullptr)
					return tmp;

			}
		}
	}
	return nullptr;
}

String* Model::toString()
{
	return ::java::lang::StringBuilder().append(u"Model [name="_j)->append(name)
		->append(u", subGroups="_j)
		->append(static_cast< Object* >(subGroups))
		->append(u"]"_j)->toString();
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
	ANIMATIONSETUP_DEFAULT = u"tdme.default"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* Model::getClass0()
{
	return class_();
}

