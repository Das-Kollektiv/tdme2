#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/utilities/Enum.h>

using std::string;

using tdme::utilities::Enum;

using tdme::engine::prototype::PrototypePhysics_BodyType;

/**
 * Prototype physics body type enum
 * @author Andreas Drewke
 */
class tdme::engine::prototype::PrototypePhysics_BodyType final: public Enum
{
public:
	STATIC_DLL_IMPEXT static PrototypePhysics_BodyType* NONE;
	STATIC_DLL_IMPEXT static PrototypePhysics_BodyType* COLLISION_BODY;
	STATIC_DLL_IMPEXT static PrototypePhysics_BodyType* DYNAMIC_RIGIDBODY;
	STATIC_DLL_IMPEXT static PrototypePhysics_BodyType* STATIC_RIGIDBODY;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 */
	PrototypePhysics_BodyType(const string& name, int ordinal);

	/**
	 * Returns enum object given by name
	 * @param name name
	 * @returns enum object
	 */
	static PrototypePhysics_BodyType* valueOf(const string& name);

};
