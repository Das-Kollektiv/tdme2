#pragma once

#include <string>

#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/utilities/Enum.h>

using std::string;

using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController_BoundingVolumeType;
using tdme::utilities::Enum;

/**
 * Prototype physics sub screen controller bounding volume type enum
 */
class tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController_BoundingVolumeType final: public Enum
{
public:
	static PrototypePhysicsSubController_BoundingVolumeType* NONE;
	static PrototypePhysicsSubController_BoundingVolumeType* SPHERE;
	static PrototypePhysicsSubController_BoundingVolumeType* CAPSULE;
	static PrototypePhysicsSubController_BoundingVolumeType* BOUNDINGBOX;
	static PrototypePhysicsSubController_BoundingVolumeType* ORIENTEDBOUNDINGBOX;
	static PrototypePhysicsSubController_BoundingVolumeType* CONVEXMESH;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 */
	PrototypePhysicsSubController_BoundingVolumeType(const string& name, int ordinal);


	/**
	 * Returns enum object given by name
	 * @param name name
	 * @return enum object
	 */
	static PrototypePhysicsSubController_BoundingVolumeType* valueOf(const string& name);

};
