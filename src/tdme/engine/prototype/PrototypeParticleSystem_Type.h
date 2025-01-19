#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/utilities/Enum.h>

using std::string;

using tdme::utilities::Enum;

/**
 * Prototype particle system type enum
 * @author Andreas Drewke
 */
class tdme::engine::prototype::PrototypeParticleSystem_Type final: public Enum
{
public:
	STATIC_DLL_IMPEXT static PrototypeParticleSystem_Type* NONE;
	STATIC_DLL_IMPEXT static PrototypeParticleSystem_Type* OBJECT_PARTICLE_SYSTEM;
	STATIC_DLL_IMPEXT static PrototypeParticleSystem_Type* POINT_PARTICLE_SYSTEM;
	STATIC_DLL_IMPEXT static PrototypeParticleSystem_Type* FOG_PARTICLE_SYSTEM;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 */
	PrototypeParticleSystem_Type(const string& name, int ordinal);

	/**
	 * Returns enum object given by name
	 * @param name name
	 * @returns enum object
	 */
	static PrototypeParticleSystem_Type* valueOf(const string& name);

};
