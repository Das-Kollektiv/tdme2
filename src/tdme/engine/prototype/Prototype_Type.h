#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Enum.h>

using std::string;

using tdme::engine::prototype::Prototype_Type;
using tdme::math::Vector3;
using tdme::utilities::Enum;

/**
 * Prototype type enum
 * @author Andreas Drewke
 */
class tdme::engine::prototype::Prototype_Type final: public Enum {
private:
	int boundingVolumeCount;
	int32_t gizmoTypeMask;
	bool nonEditScaleDownMode;
	Vector3 nonEditScaleDownModeDimension;

public:
	STATIC_DLL_IMPEXT static Prototype_Type* EMPTY;
	STATIC_DLL_IMPEXT static Prototype_Type* MODEL;
	STATIC_DLL_IMPEXT static Prototype_Type* PARTICLESYSTEM;
	STATIC_DLL_IMPEXT static Prototype_Type* TRIGGER;
	STATIC_DLL_IMPEXT static Prototype_Type* ENVIRONMENTMAPPING;
	STATIC_DLL_IMPEXT static Prototype_Type* TERRAIN;
	STATIC_DLL_IMPEXT static Prototype_Type* DECAL;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 * @param boundingVolumeCount bounding volume count or -1 for default
	 * @param gizmoTypeMask gizmo type mask, see Gizmo::GIZMO_TYPE
	 * @param nonEditScaleDownMode non edit scale down mode
	 * @param nonEditScaleDownModeDimension non edit scale down mode dimension
	 */
	Prototype_Type(const string& name, int ordinal, int boundingVolumeCount, int gizmoTypeMask, bool nonEditScaleDownMode, const Vector3& nonEditScaleDownModeDimension);

	/**
	 * @returns bounding volume count
	 */
	inline int getBoundingVolumeCount() {
		return boundingVolumeCount;
	}

	/**
	 * @returns gizmo types
	 */
	inline int32_t getGizmoTypeMask() {
		return gizmoTypeMask;
	}

	/**
	 * @returns has non edit scale down mode
	 */
	inline bool hasNonEditScaleDownMode() {
		return nonEditScaleDownMode;
	}

	/**
	 * @returns has non edit scale down mode
	 */
	inline const Vector3& getNonEditScaleDownModeDimension() {
		return nonEditScaleDownModeDimension;
	}

	/**
	 * Returns enum object given by name
	 * @param name name
	 * @returns enum object
	 */
	static Prototype_Type* valueOf(const string& name);

};
