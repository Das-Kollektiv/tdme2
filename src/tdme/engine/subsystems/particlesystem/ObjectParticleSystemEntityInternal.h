// Generated from /tdme/src/tdme/engine/subsystems/particlesystem/ObjectParticleSystemEntityInternal.java

#pragma once

#include <vector>
#include <string>

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemEntity.h>

using std::vector;
using std::wstring;

using tdme::engine::Transformations;
using tdme::engine::subsystems::particlesystem::ParticleSystemEntity;
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

/** 
 * Particle system which displays objects as particles
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::particlesystem::ObjectParticleSystemEntityInternal
	: public Transformations
	, public virtual ParticleSystemEntity
{
public: /* protected */
	Engine* engine {  };
	wstring id {  };
	bool enabled {  };
	Model* model {  };
	bool autoEmit {  };
	bool enableDynamicShadows {  };
	vector<Particle*> particles {  };
	vector<Object3D*> objects {  };
	vector<Object3D*> enabledObjects {  };
	BoundingBox* boundingBox {  };
	BoundingBox* boundingBoxTransformed {  };
	Transformations inverseTransformation {  };
	ParticleEmitter* emitter {  };
	bool pickable {  };
	Color4 effectColorMul {  };
	Color4 effectColorAdd {  };
	float particlesToSpawnRemainder {  };
public:
	const wstring& getId() override;
	virtual void setEngine(Engine* engine);
	virtual void setRenderer(GLRenderer* renderer);
	bool isEnabled() override;
	bool isActive() override;
	void setEnabled(bool enabled) override;
	Color4& getEffectColorMul() override;
	Color4& getEffectColorAdd() override;
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
	ObjectParticleSystemEntityInternal(const wstring& id, Model* model, const Vector3& scale, bool autoEmit, bool enableDynamicShadows, int32_t maxCount, ParticleEmitter* emitter);
};
