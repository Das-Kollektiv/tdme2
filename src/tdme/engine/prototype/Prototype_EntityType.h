#pragma once

#include <string>

#include <tdme/math/Vector3.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/utilities/Enum.h>

using std::string;

using tdme::math::Vector3;
using tdme::engine::prototype::Prototype_EntityType;
using tdme::utilities::Enum;

class tdme::engine::prototype::Prototype_EntityType final: public Enum
{

private:
	int boundingVolumeCount;
	int32_t gizmoTypeMask;
	bool nonEditScaleDownMode;
	Vector3 nonEditScaleDownModeDimension;

public:
	static Prototype_EntityType* EMPTY;
	static Prototype_EntityType* MODEL;
	static Prototype_EntityType* PARTICLESYSTEM;
	static Prototype_EntityType* TRIGGER;
	static Prototype_EntityType* ENVIRONMENTMAPPING;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 * @param boundingVolumeCount bounding volume count or -1 for default
	 * @param gizmoTypeMask gizmo type mask, see Gizmo::GIZMO_TYPE
	 * @param nonEditScaleDownMode non edit scale down mode
	 * @param nonEditScaleDownModeDimension non edit scale down mode dimension
	 */
	Prototype_EntityType(const string& name, int ordinal, int boundingVolumeCount, int gizmoTypeMask, bool nonEditScaleDownMode, const Vector3& nonEditScaleDownModeDimension);

	/**
	 * @return bounding volume count
	 */
	inline int getBoundingVolumeCount() {
		return boundingVolumeCount;
	}

	/**
	 * @return gizmo types
	 */
	inline int32_t getGizmoTypeMask() {
		return gizmoTypeMask;
	}

	/**
	 * @return has non edit scale down mode
	 */
	inline bool hasNonEditScaleDownMode() {
		return nonEditScaleDownMode;
	}

	/**
	 * @return has non edit scale down mode
	 */
	inline const Vector3& getNonEditScaleDownModeDimension() {
		return nonEditScaleDownModeDimension;
	}

	/**
	 * Returns enum object given by name
	 * @param name name
	 * @return enum object
	 */
	static Prototype_EntityType* valueOf(const string& name);

};
