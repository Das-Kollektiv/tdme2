#include <tdme/engine/prototype/Prototype_EntityType.h>

#include <string>

#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/views/Gizmo.h>
#include <tdme/utilities/Enum.h>

using std::string;

using tdme::math::Vector3;
using tdme::utilities::Enum;
using tdme::engine::prototype::Prototype_EntityType;
using tdme::tools::shared::views::Gizmo;

Prototype_EntityType::Prototype_EntityType(const string& name, int ordinal, int boundingVolumeCount, int32_t gizmoTypeMask, bool nonEditScaleDownMode, const Vector3& nonEditScaleDownModeDimension):
	Enum(name, ordinal), boundingVolumeCount(boundingVolumeCount), gizmoTypeMask(gizmoTypeMask), nonEditScaleDownMode(nonEditScaleDownMode), nonEditScaleDownModeDimension(nonEditScaleDownModeDimension)
{
}

Prototype_EntityType* tdme::engine::prototype::Prototype_EntityType::EMPTY = new Prototype_EntityType("EMPTY", 0, 0, Gizmo::GIZMOTYPE_TRANSLATE | Gizmo::GIZMOTYPE_ROTATE | Gizmo::GIZMOTYPE_SCALE, false, Vector3());
Prototype_EntityType* tdme::engine::prototype::Prototype_EntityType::MODEL = new Prototype_EntityType("MODEL", 1, -1, Gizmo::GIZMOTYPE_TRANSLATE | Gizmo::GIZMOTYPE_ROTATE | Gizmo::GIZMOTYPE_SCALE, false, Vector3());
Prototype_EntityType* tdme::engine::prototype::Prototype_EntityType::PARTICLESYSTEM = new Prototype_EntityType("PARTICLESYSTEM", 2, -1, Gizmo::GIZMOTYPE_TRANSLATE | Gizmo::GIZMOTYPE_ROTATE | Gizmo::GIZMOTYPE_SCALE, false, Vector3());
Prototype_EntityType* tdme::engine::prototype::Prototype_EntityType::TRIGGER = new Prototype_EntityType("TRIGGER", 3, -1, Gizmo::GIZMOTYPE_TRANSLATE | Gizmo::GIZMOTYPE_ROTATE | Gizmo::GIZMOTYPE_SCALE, true, Vector3(1.0f, 1.0f, 1.0f));
Prototype_EntityType* tdme::engine::prototype::Prototype_EntityType::ENVIRONMENTMAPPING = new Prototype_EntityType("ENVIRONMENTMAPPING", 4, 1, Gizmo::GIZMOTYPE_TRANSLATE | Gizmo::GIZMOTYPE_SCALE, true, Vector3(1.0f, 1.0f, 1.0f));

Prototype_EntityType* Prototype_EntityType::valueOf(const string& name)
{
	if (EMPTY->getName() == name) return EMPTY;
	if (MODEL->getName() == name) return MODEL;
	if (PARTICLESYSTEM->getName() == name) return PARTICLESYSTEM;
	if (TRIGGER->getName() == name) return TRIGGER;
	if (ENVIRONMENTMAPPING->getName() == name) return ENVIRONMENTMAPPING;
	return nullptr;
}
