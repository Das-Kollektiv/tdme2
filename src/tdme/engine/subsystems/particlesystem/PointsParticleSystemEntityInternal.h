// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/PointsParticleSystemEntityInternal.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemEntity.h>

using tdme::engine::Transformations;
using tdme::engine::subsystems::particlesystem::ParticleSystemEntity;
using java::lang::String;
using tdme::engine::Engine;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::object::TransparentRenderPointsPool;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Vector3;
using java::lang::Object;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace subsystems {
namespace particlesystem {
typedef ::SubArray< ::tdme::engine::subsystems::particlesystem::Particle, ::java::lang::ObjectArray > ParticleArray;
}  // namespace particlesystem
}  // namespace subsystems
}  // namespace engine
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::engine::subsystems::particlesystem::ParticleArray;

struct default_init_tag;

/** 
 * Points particle system entity internal
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::particlesystem::PointsParticleSystemEntityInternal
	: public Transformations
	, public virtual ParticleSystemEntity
{

public:
	typedef Transformations super;

public: /* protected */
	String* id {  };
	Engine* engine {  };
	GLRenderer* renderer {  };
	bool autoEmit {  };
	bool enabled {  };
	bool active {  };
	bool doCollisionTests {  };
	ParticleEmitter* emitter {  };
	ParticleArray* particles {  };
	int32_t maxPoints {  };
	TransparentRenderPointsPool* pointsRenderPool {  };
	Vector3* velocityForTime {  };

private:
	Vector3* point {  };

public: /* protected */
	BoundingBox* boundingBox {  };
	BoundingBox* boundingBoxTransformed {  };
	Transformations* inverseTransformation {  };
	Color4* effectColorMul {  };
	Color4* effectColorAdd {  };
	bool pickable {  };
	float particlesToSpawnRemainder {  };
protected:

	/** 
	 * Public constructor 
	 * @param id
	 * @param do collision tests
	 * @param emitter
	 * @param max points
	 * @param auto emit
	 */
	void ctor(String* id, bool doCollisionTests, ParticleEmitter* emitter, int32_t maxPoints, bool autoEmit);

public:
	String* getId() override;
	virtual void setRenderer(GLRenderer* renderer);
	virtual void setEngine(Engine* engine);
	bool isEnabled() override;
	bool isActive() override;
	void setEnabled(bool enabled) override;
	Color4* getEffectColorMul() override;
	Color4* getEffectColorAdd() override;
	bool isPickable() override;
	void setPickable(bool pickable) override;
	bool isAutoEmit() override;
	void setAutoEmit(bool autoEmit) override;

	/** 
	 * @return dynamic shadowing enabled
	 */
	virtual bool isDynamicShadowingEnabled();

	/** 
	 * Enable/disable dynamic shadowing
	 * @param dynamicShadowing
	 */
	virtual void setDynamicShadowingEnabled(bool dynamicShadowing);

	/** 
	 * Update transformations
	 */
	void update() override;
	void fromTransformations(Transformations* transformations) override;
	void updateParticles() override;
	virtual void dispose();
	ParticleEmitter* getParticleEmitter() override;
	int32_t emitParticles() override;

	/** 
	 * @return render points pool
	 */
	virtual TransparentRenderPointsPool* getRenderPointsPool();

	// Generated
	PointsParticleSystemEntityInternal(String* id, bool doCollisionTests, ParticleEmitter* emitter, int32_t maxPoints, bool autoEmit);
protected:
	PointsParticleSystemEntityInternal(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
