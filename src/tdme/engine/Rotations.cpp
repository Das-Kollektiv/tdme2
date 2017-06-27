// Generated from /tdme/src/tdme/engine/Rotations.java
#include <tdme/engine/Rotations.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/Rotation.h>
#include <tdme/math/Quaternion.h>
#include <tdme/utils/_ArrayList.h>

using tdme::engine::Rotations;
using java::lang::ClassCastException;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::Rotation;
using tdme::math::Quaternion;
using tdme::utils::_ArrayList;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

Rotations::Rotations(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Rotations::Rotations() 
	: Rotations(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void Rotations::ctor()
{
	super::ctor();
	rotations = new _ArrayList();
	quaternion = new Quaternion();
}

int32_t Rotations::size()
{
	return rotations->size();
}

Rotation* Rotations::get(int32_t index)
{
	return java_cast< Rotation* >(rotations->get(index));
}

void Rotations::add(Rotation* rotation)
{
	rotations->add(rotation);
}

void Rotations::set(int32_t index, Rotation* rotation)
{
	rotations->set(index, rotation);
}

Rotation* Rotations::remove(int32_t index)
{
	return java_cast< Rotation* >(rotations->remove(index));
}

Quaternion* Rotations::getQuaternion()
{
	return quaternion;
}

void Rotations::fromRotations(Rotations* transformations)
{
	auto rotationIdx = 0;
	for (; rotationIdx < transformations->size(); rotationIdx++) {
		auto rotation = transformations->get(rotationIdx);
		auto _rotation = rotationIdx < java_cast< _ArrayList* >(this->rotations)->size() ? java_cast< Rotation* >(java_cast< _ArrayList* >(this->rotations)->get(rotationIdx)) : static_cast< Rotation* >(nullptr);
		if (_rotation == nullptr) {
			_rotation = new Rotation();
			java_cast< _ArrayList* >(this->rotations)->add(_rotation);
		}
		_rotation->fromRotation(rotation);
	}
	while (rotationIdx < java_cast< _ArrayList* >(this->rotations)->size()) {
		java_cast< _ArrayList* >(this->rotations)->remove(java_cast< _ArrayList* >(this->rotations)->size() - 1);
	}
	this->quaternion->set(transformations->quaternion);
}

void Rotations::update()
{
	quaternion->identity();
	for (auto i = 0; i < rotations->size(); i++) {
		auto rotation = java_cast< Rotation* >(rotations->get(i));
		rotation->update();
		quaternion->multiply(rotation->getQuaternion());
	}
}

String* Rotations::toString()
{
	return ::java::lang::StringBuilder().append(u"Rotations [rotations="_j)->append(static_cast< Object* >(rotations))
		->append(u", quaternion="_j)
		->append(static_cast< Object* >(quaternion))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Rotations::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.Rotations", 21);
    return c;
}

java::lang::Class* Rotations::getClass0()
{
	return class_();
}

