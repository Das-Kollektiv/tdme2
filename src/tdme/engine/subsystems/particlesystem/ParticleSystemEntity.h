// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/ParticleSystemEntity.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;



/** 
 * Particle System Entity Interface
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::subsystems::particlesystem::ParticleSystemEntity
	: public virtual Object
{

	/** 
	 * @return object id
	 */
	virtual String* getId() = 0;

	/** 
	 * @return true if enabled to be rendered
	 */
	virtual bool isEnabled() = 0;

	/** 
	 * @return true if active / particles available
	 */
	virtual bool isActive() = 0;

	/** 
	 * Enable/disable rendering
	 * @param enabled
	 */
	virtual void setEnabled(bool enabled) = 0;

	/** 
	 * @return if object is pickable
	 */
	virtual bool isPickable() = 0;

	/** 
	 * Set this object pickable
	 * @param pickable
	 */
	virtual void setPickable(bool pickable) = 0;

	/** 
	 * @return if auto emit is enabled
	 */
	virtual bool isAutoEmit() = 0;

	/** 
	 * Set auto emit
	 * @param auto emit
	 */
	virtual void setAutoEmit(bool autoEmit) = 0;

	/** 
	 * The effect color will be multiplied with fragment color
	 * @return effect color
	 */
	virtual Color4* getEffectColorMul() = 0;

	/** 
	 * The effect color will be added to fragment color
	 * @return effect color
	 */
	virtual Color4* getEffectColorAdd() = 0;

	/** 
	 * @return particle emitter
	 */
	virtual ParticleEmitter* getParticleEmitter() = 0;

	/** 
	 * Updates the particle entity
	 */
	virtual void updateParticles() = 0;

	/** 
	 * Adds particles to this particle entity at given position
	 */
	virtual int32_t emitParticles() = 0;

	/** 
	 * Set up this transformations from given transformations
	 * @param transformations
	 */
	virtual void fromTransformations(Transformations* transformations) = 0;

	/** 
	 * Update transformations
	 */
	virtual void update() = 0;

	// Generated
	static ::java::lang::Class *class_();
};
