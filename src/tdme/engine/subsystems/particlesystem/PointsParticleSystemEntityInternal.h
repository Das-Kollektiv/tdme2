
#pragma once

#include <string>
#include <vector>

#include <tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/Particle.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemEntity.h>

using std::wstring;
using std::vector;

using tdme::engine::Transformations;
using tdme::engine::subsystems::particlesystem::ParticleSystemEntity;
using tdme::engine::Engine;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::object::TransparentRenderPointsPool;
using tdme::engine::subsystems::particlesystem::Particle;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Vector3;

/** 
 * Points particle system entity internal
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::particlesystem::PointsParticleSystemEntityInternal
	: public Transformations
	, public virtual ParticleSystemEntity
{

public: /* protected */
	wstring id {  };
	Engine* engine {  };
	GLRenderer* renderer {  };
	bool autoEmit {  };
	bool enabled {  };
	bool active {  };
	bool doCollisionTests {  };
	ParticleEmitter* emitter {  };
	vector<Particle> particles {  };
	int32_t maxPoints {  };
	TransparentRenderPointsPool* pointsRenderPool {  };

public: /* protected */
	BoundingBox* boundingBox {  };
	BoundingBox* boundingBoxTransformed {  };
	Transformations inverseTransformation {  };
	Color4 effectColorMul {  };
	Color4 effectColorAdd {  };
	bool pickable {  };
	float particlesToSpawnRemainder {  };
public:
	const wstring& getId() override;
	virtual void setRenderer(GLRenderer* renderer);
	virtual void setEngine(Engine* engine);
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
	void updateParticles() override;
	virtual void dispose();
	ParticleEmitter* getParticleEmitter() override;
	int32_t emitParticles() override;

	/** 
	 * @return render points pool
	 */
	virtual TransparentRenderPointsPool* getRenderPointsPool();

	/**
	 * Public constructor
	 * @param id
	 * @param do collision tests
	 * @param emitter
	 * @param max points
	 * @param auto emit
	 */
	PointsParticleSystemEntityInternal(const wstring& id, bool doCollisionTests, ParticleEmitter* emitter, int32_t maxPoints, bool autoEmit);

	/**
	 * Destructor
	 */
	virtual ~PointsParticleSystemEntityInternal();
};
