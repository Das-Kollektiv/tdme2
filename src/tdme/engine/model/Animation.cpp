// Generated from /tdme/src/tdme/engine/model/Animation.java
#include <tdme/engine/model/Animation.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Arrays.h>
#include <tdme/math/Matrix4x4.h>
#include <ObjectArray.h>
#include <SubArray.h>

using tdme::engine::model::Animation;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Arrays;
using tdme::math::Matrix4x4;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace math {
typedef ::SubArray< ::tdme::math::Matrix4x4, ::java::lang::ObjectArray > Matrix4x4Array;
}  // namespace math
}  // namespace tdme

Animation::Animation(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Animation::Animation(int32_t frames) 
	: Animation(*static_cast< ::default_init_tag* >(0))
{
	ctor(frames);
}

void Animation::ctor(int32_t frames)
{
	super::ctor();
	this->frames = frames;
	transformationsMatrices = new Matrix4x4Array(this->frames);
	for (auto i = 0; i < frames; i++) {
		transformationsMatrices->set(i, (new Matrix4x4())->identity());
	}
}

int32_t Animation::getFrames()
{
	return frames;
}

Matrix4x4Array* Animation::getTransformationsMatrices()
{
	return transformationsMatrices;
}

String* Animation::toString()
{
	return ::java::lang::StringBuilder().append(u"Animation [frames="_j)->append(frames)
		->append(u", transformationsMatrices="_j)
		->append(Arrays::toString(static_cast< ObjectArray* >(transformationsMatrices)))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Animation::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.Animation", 27);
    return c;
}

java::lang::Class* Animation::getClass0()
{
	return class_();
}

