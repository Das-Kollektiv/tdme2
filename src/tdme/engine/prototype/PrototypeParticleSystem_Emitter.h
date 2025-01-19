#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/utilities/Enum.h>

using std::string;

using tdme::utilities::Enum;

/**
 * Prototype particle system emitter type enum
 * @author Andreas Drewke
 */
class tdme::engine::prototype::PrototypeParticleSystem_Emitter final: public Enum {
public:
	STATIC_DLL_IMPEXT static PrototypeParticleSystem_Emitter* NONE;
	STATIC_DLL_IMPEXT static PrototypeParticleSystem_Emitter* POINT_PARTICLE_EMITTER;
	STATIC_DLL_IMPEXT static PrototypeParticleSystem_Emitter* BOUNDINGBOX_PARTICLE_EMITTER;
	STATIC_DLL_IMPEXT static PrototypeParticleSystem_Emitter* CIRCLE_PARTICLE_EMITTER;
	STATIC_DLL_IMPEXT static PrototypeParticleSystem_Emitter* CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY;
	STATIC_DLL_IMPEXT static PrototypeParticleSystem_Emitter* SPHERE_PARTICLE_EMITTER;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 */
	PrototypeParticleSystem_Emitter(const string& name, int ordinal);

	/**
	 * Returns enum object given by name
	 * @param name name
	 * @returns enum object
	 */
	static PrototypeParticleSystem_Emitter* valueOf(const string& name);
};
