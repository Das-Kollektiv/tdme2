// Generated from /tdme/src/tdme/engine/Engine.java
#include <tdme/engine/Engine_AnimationProcessingTarget.h>

#include <string>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::wstring;

using tdme::engine::Engine_AnimationProcessingTarget;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::Enum;
using java::lang::String;

template<typename ComponentType, typename ... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray<::java::io::Serializable, ::java::lang::ObjectArray> SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray<::java::lang::Comparable, ObjectArray> ComparableArray;
typedef ::SubArray<::java::lang::Enum, ObjectArray, ComparableArray,
		::java::io::SerializableArray> EnumArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace engine {
typedef ::SubArray<::tdme::engine::Engine_AnimationProcessingTarget,
		::java::lang::EnumArray> Engine_AnimationProcessingTargetArray;
}  // namespace engine
}  // namespace tdme

Engine_AnimationProcessingTarget::Engine_AnimationProcessingTarget(
		const ::default_init_tag&) :
		super(*static_cast<::default_init_tag*>(0)) {
	clinit();
}

Engine_AnimationProcessingTarget::Engine_AnimationProcessingTarget(
		const wstring& name, int ordinal) :
		Engine_AnimationProcessingTarget(*static_cast<::default_init_tag*>(0)) {
	ctor(name, ordinal);
}

Engine_AnimationProcessingTarget* tdme::engine::Engine_AnimationProcessingTarget::CPU =
		new Engine_AnimationProcessingTarget(L"CPU", 0);
Engine_AnimationProcessingTarget* tdme::engine::Engine_AnimationProcessingTarget::CPU_NORENDERING =
		new Engine_AnimationProcessingTarget(L"CPU_NORENDERING", 1);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Engine_AnimationProcessingTarget::class_() {
	static ::java::lang::Class* c = ::class_(u"tdme.engine.Engine.AnimationProcessingTarget", 44);
	return c;
}

Engine_AnimationProcessingTarget* Engine_AnimationProcessingTarget::valueOf(const wstring& a0) {
	if (CPU->name() == a0) return CPU;
	if (CPU_NORENDERING->name() == a0) return CPU_NORENDERING;
	// TODO: throw exception here maybe
	return nullptr;
}

Engine_AnimationProcessingTargetArray* Engine_AnimationProcessingTarget::values() {
	return new Engine_AnimationProcessingTargetArray( { CPU, CPU_NORENDERING, });
}

java::lang::Class* Engine_AnimationProcessingTarget::getClass0() {
	return class_();
}

