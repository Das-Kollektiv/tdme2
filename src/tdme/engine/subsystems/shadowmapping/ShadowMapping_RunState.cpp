// Generated from /tdme/src/tdme/engine/subsystems/shadowmapping/ShadowMapping.java
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping_RunState.h>

#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::engine::subsystems::shadowmapping::ShadowMapping_RunState;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::Enum;
using java::lang::String;

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
namespace subsystems {
namespace shadowmapping {
typedef ::SubArray< ::tdme::engine::subsystems::shadowmapping::ShadowMapping_RunState, ::java::lang::EnumArray > ShadowMapping_RunStateArray;
}  // namespace shadowmapping
}  // namespace subsystems
}  // namespace engine
}  // namespace tdme

ShadowMapping_RunState::ShadowMapping_RunState(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ShadowMapping_RunState::ShadowMapping_RunState(::java::lang::String* name, int ordinal)
	: ShadowMapping_RunState(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

ShadowMapping_RunState* tdme::engine::subsystems::shadowmapping::ShadowMapping_RunState::NONE = new ShadowMapping_RunState(u"NONE"_j, 0);
ShadowMapping_RunState* tdme::engine::subsystems::shadowmapping::ShadowMapping_RunState::PRE = new ShadowMapping_RunState(u"PRE"_j, 1);
ShadowMapping_RunState* tdme::engine::subsystems::shadowmapping::ShadowMapping_RunState::RENDER = new ShadowMapping_RunState(u"RENDER"_j, 2);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ShadowMapping_RunState::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.shadowmapping.ShadowMapping.RunState", 59);
    return c;
}

ShadowMapping_RunState* ShadowMapping_RunState::valueOf(String* a0)
{
	if (NONE->toString()->equals(a0))
		return NONE;
	if (PRE->toString()->equals(a0))
		return PRE;
	if (RENDER->toString()->equals(a0))
		return RENDER;
	// TODO: throw exception here maybe
	return nullptr;
}

ShadowMapping_RunStateArray* ShadowMapping_RunState::values()
{
	return new ShadowMapping_RunStateArray({
		NONE,
		PRE,
		RENDER,
	});
}

java::lang::Class* ShadowMapping_RunState::getClass0()
{
	return class_();
}

