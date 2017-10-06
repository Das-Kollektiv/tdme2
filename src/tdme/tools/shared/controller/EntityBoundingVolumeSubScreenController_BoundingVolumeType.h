#pragma once

#include <string>

#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/utils/Enum.h>

using std::wstring;

using tdme::utils::Enum;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType;

class tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType final
	: public Enum
{
	friend class EntityBoundingVolumeSubScreenController;
	friend class EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1;

public: /* package */
	static EntityBoundingVolumeSubScreenController_BoundingVolumeType *NONE;
	static EntityBoundingVolumeSubScreenController_BoundingVolumeType *SPHERE;
	static EntityBoundingVolumeSubScreenController_BoundingVolumeType *CAPSULE;
	static EntityBoundingVolumeSubScreenController_BoundingVolumeType *BOUNDINGBOX;
	static EntityBoundingVolumeSubScreenController_BoundingVolumeType *ORIENTEDBOUNDINGBOX;
	static EntityBoundingVolumeSubScreenController_BoundingVolumeType *CONVEXMESH;
	EntityBoundingVolumeSubScreenController_BoundingVolumeType(const wstring& name, int ordinal);

public:
	static EntityBoundingVolumeSubScreenController_BoundingVolumeType* valueOf(const wstring& a0);

};
