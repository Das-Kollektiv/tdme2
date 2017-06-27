// Generated from /tdme/src/tdme/engine/Object3D.java
#include <tdme/engine/Object3D.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Partition.h>

using tdme::engine::Object3D;
using tdme::engine::Engine;
using tdme::engine::Partition;

Object3D::Object3D(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Object3D::Object3D(String* id, Model* model) 
	: Object3D(*static_cast< ::default_init_tag* >(0))
{
	ctor(id,model);
}

void Object3D::ctor(String* id, Model* model)
{
	super::ctor(id, model);
}

void Object3D::setEngine(Engine* engine)
{
	this->engine = engine;
}

void Object3D::setRenderer(GLRenderer* renderer)
{
}

void Object3D::fromTransformations(Transformations* transformations)
{
	super::fromTransformations(transformations);
	if (engine != nullptr && enabled == true)
		engine->partition->updateEntity(this);

}

void Object3D::update()
{
	super::update();
	if (engine != nullptr && enabled == true)
		engine->partition->updateEntity(this);

}

void Object3D::setEnabled(bool enabled)
{
	if (this->enabled == enabled)
		return;

	if (enabled == true) {
		if (engine != nullptr)
			engine->partition->addEntity(this);

	} else {
		if (engine != nullptr)
			engine->partition->removeEntity(this);

	}
	super::setEnabled(enabled);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Object3D::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.Object3D", 20);
    return c;
}

void Object3D::dispose()
{
	Object3DInternal::dispose();
}

BoundingBox* Object3D::getBoundingBox()
{
	return Object3DInternal::getBoundingBox();
}

BoundingBox* Object3D::getBoundingBoxTransformed()
{
	return Object3DInternal::getBoundingBoxTransformed();
}

Color4* Object3D::getEffectColorAdd()
{
	return Object3DInternal::getEffectColorAdd();
}

Color4* Object3D::getEffectColorMul()
{
	return Object3DInternal::getEffectColorMul();
}

String* Object3D::getId()
{
	return Object3DInternal::getId();
}

Vector3* Object3D::getPivot()
{
	return Transformations::getPivot();
}

Rotations* Object3D::getRotations()
{
	return Transformations::getRotations();
}

Vector3* Object3D::getScale()
{
	return Transformations::getScale();
}

Matrix4x4* Object3D::getTransformationsMatrix()
{
	return Transformations::getTransformationsMatrix();
}

Vector3* Object3D::getTranslation()
{
	return Transformations::getTranslation();
}

void Object3D::initialize()
{
	Object3DInternal::initialize();
}

bool Object3D::isDynamicShadowingEnabled()
{
	return Object3DInternal::isDynamicShadowingEnabled();
}

bool Object3D::isEnabled()
{
	return Object3DInternal::isEnabled();
}

bool Object3D::isPickable()
{
	return Object3DInternal::isPickable();
}

void Object3D::setDynamicShadowingEnabled(bool dynamicShadowing)
{
	Object3DInternal::setDynamicShadowingEnabled(dynamicShadowing);
}

void Object3D::setPickable(bool pickable)
{
	Object3DInternal::setPickable(pickable);
}

Matrix4x4* Object3D::getTransformationsMatrix(String* id)
{
	return super::getTransformationsMatrix(id);
}

java::lang::Class* Object3D::getClass0()
{
	return class_();
}

