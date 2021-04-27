#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController_BoundingVolumeType.h>

#include <string>

#include <tdme/utilities/Enum.h>

using std::string;

using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController_BoundingVolumeType;
using tdme::utilities::Enum;

PrototypePhysicsSubController_BoundingVolumeType::PrototypePhysicsSubController_BoundingVolumeType(const string& name, int ordinal)
	: Enum(name, ordinal)
{
}

PrototypePhysicsSubController_BoundingVolumeType* tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController_BoundingVolumeType::NONE = new PrototypePhysicsSubController_BoundingVolumeType("NONE", 0);
PrototypePhysicsSubController_BoundingVolumeType* tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController_BoundingVolumeType::SPHERE = new PrototypePhysicsSubController_BoundingVolumeType("SPHERE", 1);
PrototypePhysicsSubController_BoundingVolumeType* tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController_BoundingVolumeType::CAPSULE = new PrototypePhysicsSubController_BoundingVolumeType("CAPSULE", 2);
PrototypePhysicsSubController_BoundingVolumeType* tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController_BoundingVolumeType::BOUNDINGBOX = new PrototypePhysicsSubController_BoundingVolumeType("BOUNDINGBOX", 3);
PrototypePhysicsSubController_BoundingVolumeType* tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController_BoundingVolumeType::ORIENTEDBOUNDINGBOX = new PrototypePhysicsSubController_BoundingVolumeType("ORIENTEDBOUNDINGBOX", 4);
PrototypePhysicsSubController_BoundingVolumeType* tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController_BoundingVolumeType::CONVEXMESH = new PrototypePhysicsSubController_BoundingVolumeType("CONVEXMESH", 5);

PrototypePhysicsSubController_BoundingVolumeType* PrototypePhysicsSubController_BoundingVolumeType::valueOf(const string& name)
{
	if (BOUNDINGBOX->getName() == name) return BOUNDINGBOX;
	if (CAPSULE->getName() == name) return CAPSULE;
	if (CONVEXMESH->getName() == name) return CONVEXMESH;
	if (NONE->getName() == name) return NONE;
	if (ORIENTEDBOUNDINGBOX->getName() == name) return ORIENTEDBOUNDINGBOX;
	if (SPHERE->getName() == name) return SPHERE;
	// TODO: throw exception here maybe
	return nullptr;
}
