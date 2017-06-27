// Generated from /tdme/src/tdme/engine/subsystems/shadowmapping/ShadowMapping.java

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <java/lang/Enum.h>

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using java::lang::Object;
using tdme::engine::subsystems::shadowmapping::ShadowMapping_RunState;

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

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::engine::subsystems::shadowmapping::ShadowMapping_RunStateArray;

struct default_init_tag;
class tdme::engine::subsystems::shadowmapping::ShadowMapping_RunState final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static ShadowMapping_RunState *NONE;
	static ShadowMapping_RunState *PRE;
	static ShadowMapping_RunState *RENDER;

	// Generated

public:
	ShadowMapping_RunState(::java::lang::String* name, int ordinal);
protected:
	ShadowMapping_RunState(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static ShadowMapping_RunState* valueOf(String* a0);
	static ShadowMapping_RunStateArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class ShadowMapping;
};
