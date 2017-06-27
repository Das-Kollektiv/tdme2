// Generated from /tdme/src/tdme/engine/subsystems/object/TransparentRenderFace.java
#include <tdme/engine/subsystems/object/TransparentRenderFace.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/subsystems/object/Object3DGroup.h>

using tdme::engine::subsystems::object::TransparentRenderFace;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::model::Group;
using tdme::engine::subsystems::object::Object3DGroup;

TransparentRenderFace::TransparentRenderFace(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

TransparentRenderFace::TransparentRenderFace()
	: TransparentRenderFace(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

int32_t TransparentRenderFace::compareTo(TransparentRenderFace* face2)
{
	if (distanceFromCamera > face2->distanceFromCamera)
		return -1;
	else if (distanceFromCamera < face2->distanceFromCamera)
		return +1;
	else
		return 0;
}

int32_t TransparentRenderFace::compareTo(Object* arg0)
{ 
	return compareTo(dynamic_cast< TransparentRenderFace* >(arg0));
}

String* TransparentRenderFace::toString()
{
	return ::java::lang::StringBuilder().append(u"TransparentRenderFace [group="_j)->append(object3DGroup->group->getName())
		->append(u", facesEntityIdx="_j)
		->append(facesEntityIdx)
		->append(u", faceIdx="_j)
		->append(faceIdx)
		->append(u", distanceFromCamera="_j)
		->append(distanceFromCamera)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TransparentRenderFace::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.TransparentRenderFace", 51);
    return c;
}

java::lang::Class* TransparentRenderFace::getClass0()
{
	return class_();
}

