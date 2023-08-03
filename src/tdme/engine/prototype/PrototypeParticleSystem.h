#pragma once

#include <memory>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_BoundingBoxParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_CircleParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_Emitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_FogParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_ObjectParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_PointParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_PointParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_SphereParticleEmitter.h>
#include <tdme/engine/prototype/fwd-tdme.h>

using std::unique_ptr;

using tdme::engine::prototype::PrototypeParticleSystem_BoundingBoxParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_CircleParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::engine::prototype::PrototypeParticleSystem_Emitter;
using tdme::engine::prototype::PrototypeParticleSystem_FogParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_ObjectParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_PointParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_PointParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_SphereParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_Type;

/**
 * Prototype particle system definition
 * @author Andreas Drewke
 */
class tdme::engine::prototype::PrototypeParticleSystem final
{
private:
	PrototypeParticleSystem_Type* type { nullptr };
	unique_ptr<PrototypeParticleSystem_ObjectParticleSystem> ops;
	unique_ptr<PrototypeParticleSystem_PointParticleSystem> pps;
	unique_ptr<PrototypeParticleSystem_FogParticleSystem> fps;
	PrototypeParticleSystem_Emitter* emitter { nullptr };
	unique_ptr<PrototypeParticleSystem_PointParticleEmitter> ppe;
	unique_ptr<PrototypeParticleSystem_BoundingBoxParticleEmitter> bbpe;
	unique_ptr<PrototypeParticleSystem_CircleParticleEmitter> cpe;
	unique_ptr<PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity> cpepv;
	unique_ptr<PrototypeParticleSystem_SphereParticleEmitter> spe;

	/**
	 * Unset particle system type
	 */
	void unsetType();

	/**
	 * Unset emitter
	 */
	void unsetEmitter();

public:
	// forbid class copy
	FORBID_CLASS_COPY(PrototypeParticleSystem)

	/**
	 * Public constructor
	 */
	PrototypeParticleSystem();

	/**
	 * Destructor
	 */
	~PrototypeParticleSystem();

	/**
	 * @return particle system type
	 */
	inline PrototypeParticleSystem_Type* getType() {
		return type;
	}

	/**
	 * Set particle system type
	 * @param type type
	 */
	void setType(PrototypeParticleSystem_Type* type);

	/**
	 * @return object particle system
	 */
	inline PrototypeParticleSystem_ObjectParticleSystem* getObjectParticleSystem() {
		return ops.get();
	}

	/**
	 * @return point particle system
	 */
	inline PrototypeParticleSystem_PointParticleSystem* getPointParticleSystem() {
		return pps.get();
	}

	/**
	 * @return fog particle system
	 */
	inline PrototypeParticleSystem_FogParticleSystem* getFogParticleSystem() {
		return fps.get();
	}

	/**
	 * @return particle system emitter
	 */
	inline PrototypeParticleSystem_Emitter* getEmitter() {
		return emitter;
	}

	/**
	 * Set emitter
	 * @param emitter emitter
	 */
	void setEmitter(PrototypeParticleSystem_Emitter* emitter);

	/**
	 * @return point particle emitter
	 */
	inline PrototypeParticleSystem_PointParticleEmitter* getPointParticleEmitter() {
		return ppe.get();
	}

	/**
	 * @return bounding box particle emitter
	 */
	inline PrototypeParticleSystem_BoundingBoxParticleEmitter* getBoundingBoxParticleEmitters() {
		return bbpe.get();
	}

	/**
	 * @return circle particle emitter
	 */
	inline PrototypeParticleSystem_CircleParticleEmitter* getCircleParticleEmitter() {
		return cpe.get();
	}

	/**
	 * @return circle particle emitter plane velocity
	 */
	inline PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity* getCircleParticleEmitterPlaneVelocity() {
		return cpepv.get();
	}

	/**
	 * @return sphere particle emitter
	 */
	inline PrototypeParticleSystem_SphereParticleEmitter* getSphereParticleEmitter() {
		return spe.get();
	}

};
