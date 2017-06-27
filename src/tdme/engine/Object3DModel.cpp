// Generated from /tdme/src/tdme/engine/Object3DModel.java
#include <tdme/engine/Object3DModel.h>

using tdme::engine::Object3DModel;
Object3DModel::Object3DModel(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Object3DModel::Object3DModel(Model* model) 
	: Object3DModel(*static_cast< ::default_init_tag* >(0))
{
	ctor(model);
}

void Object3DModel::ctor(Model* model)
{
	super::ctor(model);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Object3DModel::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.Object3DModel", 25);
    return c;
}

java::lang::Class* Object3DModel::getClass0()
{
	return class_();
}

