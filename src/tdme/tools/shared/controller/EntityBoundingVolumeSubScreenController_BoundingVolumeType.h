// Generated from /tdme/src/tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.java

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <java/lang/Enum.h>

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::String;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using java::lang::Object;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType;

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
namespace tools {
namespace shared {
namespace controller {
typedef ::SubArray< ::tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType, ::java::lang::EnumArray > EntityBoundingVolumeSubScreenController_BoundingVolumeTypeArray;
}  // namespace controller
}  // namespace shared
}  // namespace tools
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeTypeArray;

struct default_init_tag;
class tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static EntityBoundingVolumeSubScreenController_BoundingVolumeType *NONE;
	static EntityBoundingVolumeSubScreenController_BoundingVolumeType *SPHERE;
	static EntityBoundingVolumeSubScreenController_BoundingVolumeType *CAPSULE;
	static EntityBoundingVolumeSubScreenController_BoundingVolumeType *BOUNDINGBOX;
	static EntityBoundingVolumeSubScreenController_BoundingVolumeType *ORIENTEDBOUNDINGBOX;
	static EntityBoundingVolumeSubScreenController_BoundingVolumeType *CONVEXMESH;

	// Generated

public:
	EntityBoundingVolumeSubScreenController_BoundingVolumeType(::java::lang::String* name, int ordinal);
protected:
	EntityBoundingVolumeSubScreenController_BoundingVolumeType(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static EntityBoundingVolumeSubScreenController_BoundingVolumeType* valueOf(String* a0);
	static EntityBoundingVolumeSubScreenController_BoundingVolumeTypeArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class EntityBoundingVolumeSubScreenController;
	friend class EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1;
};
