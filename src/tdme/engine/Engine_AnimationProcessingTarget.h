// Generated from /tdme/src/tdme/engine/Engine.java

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <java/lang/Enum.h>

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::Engine;
using java::lang::Object;
using tdme::engine::Engine_AnimationProcessingTarget;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::Enum, ObjectArray, ComparableArray, ::java::io::SerializableArray > EnumArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace engine {
typedef ::SubArray< ::tdme::engine::Engine_AnimationProcessingTarget, ::java::lang::EnumArray > Engine_AnimationProcessingTargetArray;
}  // namespace engine
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::engine::Engine_AnimationProcessingTargetArray;

struct default_init_tag;
class tdme::engine::Engine_AnimationProcessingTarget final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static Engine_AnimationProcessingTarget *CPU;
	static Engine_AnimationProcessingTarget *CPU_NORENDERING;

	// Generated

public:
	Engine_AnimationProcessingTarget(::java::lang::String* name, int ordinal);
protected:
	Engine_AnimationProcessingTarget(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static Engine_AnimationProcessingTarget* valueOf(String* a0);
	static Engine_AnimationProcessingTargetArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class Engine;
	friend class Engine_initialize_1;
	friend class Engine_initialize_2;
	friend class Engine_initialize_3;
};
