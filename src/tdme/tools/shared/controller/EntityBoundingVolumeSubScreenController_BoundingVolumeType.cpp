#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController_BoundingVolumeType.h>

#include <string>

#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType;
using tdme::utils::Enum;

EntityBoundingVolumeSubScreenController_BoundingVolumeType::EntityBoundingVolumeSubScreenController_BoundingVolumeType(const wstring& name, int ordinal)
	: Enum(name, ordinal)
{
}

EntityBoundingVolumeSubScreenController_BoundingVolumeType* tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType::NONE = new EntityBoundingVolumeSubScreenController_BoundingVolumeType(L"NONE", 0);
EntityBoundingVolumeSubScreenController_BoundingVolumeType* tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType::SPHERE = new EntityBoundingVolumeSubScreenController_BoundingVolumeType(L"SPHERE", 1);
EntityBoundingVolumeSubScreenController_BoundingVolumeType* tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType::CAPSULE = new EntityBoundingVolumeSubScreenController_BoundingVolumeType(L"CAPSULE", 2);
EntityBoundingVolumeSubScreenController_BoundingVolumeType* tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType::BOUNDINGBOX = new EntityBoundingVolumeSubScreenController_BoundingVolumeType(L"BOUNDINGBOX", 3);
EntityBoundingVolumeSubScreenController_BoundingVolumeType* tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType::ORIENTEDBOUNDINGBOX = new EntityBoundingVolumeSubScreenController_BoundingVolumeType(L"ORIENTEDBOUNDINGBOX", 4);
EntityBoundingVolumeSubScreenController_BoundingVolumeType* tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType::CONVEXMESH = new EntityBoundingVolumeSubScreenController_BoundingVolumeType(L"CONVEXMESH", 5);

EntityBoundingVolumeSubScreenController_BoundingVolumeType* EntityBoundingVolumeSubScreenController_BoundingVolumeType::valueOf(const wstring& a0)
{
	if (BOUNDINGBOX->getName() == a0) return BOUNDINGBOX;
	if (CAPSULE->getName() == a0) return CAPSULE;
	if (CONVEXMESH->getName() == a0) return CONVEXMESH;
	if (NONE->getName() == a0) return NONE;
	if (ORIENTEDBOUNDINGBOX->getName() == a0) return ORIENTEDBOUNDINGBOX;
	if (SPHERE->getName() == a0) return SPHERE;
	// TODO: throw exception here maybe
	return nullptr;
}
