// Generated from /tdme/src/tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.java
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController_BoundingVolumeType.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Enum.h>
#include <java/lang/IllegalArgumentException.h>
#include <java/lang/String.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::Comparable;
using java::lang::Enum;
using java::lang::IllegalArgumentException;
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
namespace tools {
namespace shared {
namespace controller {
typedef ::SubArray< ::tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType, ::java::lang::EnumArray > EntityBoundingVolumeSubScreenController_BoundingVolumeTypeArray;
}  // namespace controller
}  // namespace shared
}  // namespace tools
}  // namespace tdme

EntityBoundingVolumeSubScreenController_BoundingVolumeType::EntityBoundingVolumeSubScreenController_BoundingVolumeType(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

EntityBoundingVolumeSubScreenController_BoundingVolumeType::EntityBoundingVolumeSubScreenController_BoundingVolumeType(::java::lang::String* name, int ordinal)
	: EntityBoundingVolumeSubScreenController_BoundingVolumeType(*static_cast< ::default_init_tag* >(0))
{
	ctor(name, ordinal);
}

EntityBoundingVolumeSubScreenController_BoundingVolumeType* tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType::NONE = new EntityBoundingVolumeSubScreenController_BoundingVolumeType(u"NONE"_j, 0);
EntityBoundingVolumeSubScreenController_BoundingVolumeType* tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType::SPHERE = new EntityBoundingVolumeSubScreenController_BoundingVolumeType(u"SPHERE"_j, 1);
EntityBoundingVolumeSubScreenController_BoundingVolumeType* tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType::CAPSULE = new EntityBoundingVolumeSubScreenController_BoundingVolumeType(u"CAPSULE"_j, 2);
EntityBoundingVolumeSubScreenController_BoundingVolumeType* tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType::BOUNDINGBOX = new EntityBoundingVolumeSubScreenController_BoundingVolumeType(u"BOUNDINGBOX"_j, 3);
EntityBoundingVolumeSubScreenController_BoundingVolumeType* tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType::ORIENTEDBOUNDINGBOX = new EntityBoundingVolumeSubScreenController_BoundingVolumeType(u"ORIENTEDBOUNDINGBOX"_j, 4);
EntityBoundingVolumeSubScreenController_BoundingVolumeType* tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType::CONVEXMESH = new EntityBoundingVolumeSubScreenController_BoundingVolumeType(u"CONVEXMESH"_j, 5);
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* EntityBoundingVolumeSubScreenController_BoundingVolumeType::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.controller.EntityBoundingVolumeSubScreenController.BoundingVolumeType", 87);
    return c;
}

EntityBoundingVolumeSubScreenController_BoundingVolumeType* EntityBoundingVolumeSubScreenController_BoundingVolumeType::valueOf(String* a0)
{
	if (BOUNDINGBOX->toString()->equals(a0))
		return BOUNDINGBOX;
	if (CAPSULE->toString()->equals(a0))
		return CAPSULE;
	if (CONVEXMESH->toString()->equals(a0))
		return CONVEXMESH;
	if (NONE->toString()->equals(a0))
		return NONE;
	if (ORIENTEDBOUNDINGBOX->toString()->equals(a0))
		return ORIENTEDBOUNDINGBOX;
	if (SPHERE->toString()->equals(a0))
		return SPHERE;
	throw new IllegalArgumentException(a0);
}

EntityBoundingVolumeSubScreenController_BoundingVolumeTypeArray* EntityBoundingVolumeSubScreenController_BoundingVolumeType::values()
{
	return new EntityBoundingVolumeSubScreenController_BoundingVolumeTypeArray({
		BOUNDINGBOX,
		CAPSULE,
		CONVEXMESH,
		NONE,
		ORIENTEDBOUNDINGBOX,
		SPHERE,
	});
}

java::lang::Class* EntityBoundingVolumeSubScreenController_BoundingVolumeType::getClass0()
{
	return class_();
}

