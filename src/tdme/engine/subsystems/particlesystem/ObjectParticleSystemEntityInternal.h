// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/ObjectParticleSystemEntityInternal.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemEntity.h>

using std::vector;

using tdme::engine::Transformations;
using tdme::engine::subsystems::particlesystem::ParticleSystemEntity;
using java::lang::String;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Object3D;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::object::Object3DBase;
using tdme::engine::subsystems::object::Object3DInternal;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Vector3;
using java::lang::Object;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
typedef ::SubArray< ::tdme::engine::Entity, ::java::lang::ObjectArray > EntityArray;
typedef ::SubArray< ::tdme::engine::Transformations, ::java::lang::ObjectArray > TransformationsArray;

namespace subsystems {
namespace object {
typedef ::SubArray< ::tdme::engine::subsystems::object::Object3DBase, ::tdme::engine::TransformationsArray > Object3DBaseArray;
typedef ::SubArray< ::tdme::engine::subsystems::object::Object3DInternal, Object3DBaseArray > Object3DInternalArray;
}  // namespace object
}  // namespace subsystems
typedef ::SubArray< ::tdme::engine::Object3D, ::tdme::engine::subsystems::object::Object3DInternalArray, EntityArray > Object3DArray;

namespace subsystems {
namespace particlesystem {
typedef ::SubArray< ::tdme::engine::subsystems::particlesystem::Particle, ::java::lang::ObjectArray > ParticleArray;
}  // namespace particlesystem
}  // namespace subsystems
}  // namespace engine
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::engine::EntityArray;
using tdme::engine::Object3DArray;
using tdme::engine::TransformationsArray;
using tdme::engine::subsystems::object::Object3DBaseArray;
using tdme::engine::subsystems::object::Object3DInternalArray;
using tdme::engine::subsystems::particlesystem::ParticleArray;

struct default_init_tag;

/** 
 * Particle system which displays objects as particles
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::particlesystem::ObjectParticleSystemEntityInternal
	: public Transformations
	, public virtual ParticleSystemEntity
{

public:
	typedef Transformations super;

public: /* protected */
	Engine* engine {  };
	String* id {  };
	bool enabled {  };
	Model* model {  };
	bool autoEmit {  };
	bool enableDynamicShadows {  };
	ParticleArray* particles {  };
	Object3DArray* objects {  };
	vector<Object3D*> enabledObjects {  };
	BoundingBox* boundingBox {  };
	BoundingBox* boundingBoxTransformed {  };
	Transformations* inverseTransformation {  };
	ParticleEmitter* emitter {  };
	bool pickable {  };
	Color4* effectColorMul {  };
	Color4* effectColorAdd {  };
	Vector3* velocityForTime {  };
	float particlesToSpawnRemainder {  };
protected:

	/** 
	 * Public constructor
	 * @param id
	 * @param model
	 * @param scale
	 * @param auto emit
	 * @param enable dynamic shadows
	 * @param maxCount
	 * @param emitter
	 */
	void ctor(String* id, Model* model, Vector3* scale, bool autoEmit, bool enableDynamicShadows, int32_t maxCount, ParticleEmitter* emitter);

public:
	String* getId() override;
	virtual void setEngine(Engine* engine);
	virtual void setRenderer(GLRenderer* renderer);
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
	ParticleEmitter* getParticleEmitter() override;
	int32_t emitParticles() override;
	void updateParticles() override;
	virtual void dispose();
	String* toString() override;

	// Generated
	ObjectParticleSystemEntityInternal(String* id, Model* model, Vector3* scale, bool autoEmit, bool enableDynamicShadows, int32_t maxCount, ParticleEmitter* emitter);
protected:
	ObjectParticleSystemEntityInternal(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
