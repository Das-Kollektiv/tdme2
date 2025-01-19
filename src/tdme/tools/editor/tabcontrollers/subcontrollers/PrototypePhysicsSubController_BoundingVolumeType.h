#pragma once

#include <string>

#include <tdme/tdme.h>
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
	STATIC_DLL_IMPEXT static PrototypePhysicsSubController_BoundingVolumeType* NONE;
	STATIC_DLL_IMPEXT static PrototypePhysicsSubController_BoundingVolumeType* SPHERE;
	STATIC_DLL_IMPEXT static PrototypePhysicsSubController_BoundingVolumeType* CAPSULE;
	STATIC_DLL_IMPEXT static PrototypePhysicsSubController_BoundingVolumeType* BOUNDINGBOX;
	STATIC_DLL_IMPEXT static PrototypePhysicsSubController_BoundingVolumeType* ORIENTEDBOUNDINGBOX;
	STATIC_DLL_IMPEXT static PrototypePhysicsSubController_BoundingVolumeType* CONVEXMESH;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 */
	PrototypePhysicsSubController_BoundingVolumeType(const string& name, int ordinal);


	/**
	 * Returns enum object given by name
	 * @param name name
	 * @returns enum object
	 */
	static PrototypePhysicsSubController_BoundingVolumeType* valueOf(const string& name);

};
