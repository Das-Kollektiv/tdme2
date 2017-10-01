// Generated from /tdme/src/tdme/engine/PointsParticleSystemEntity.java

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/PointsParticleSystemEntityInternal.h>
#include <tdme/engine/Entity.h>

using std::wstring;

using tdme::engine::subsystems::particlesystem::PointsParticleSystemEntityInternal;
using tdme::engine::Entity;
using tdme::engine::Engine;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Point particle system entity to be used with engine class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::PointsParticleSystemEntity final
	: public PointsParticleSystemEntityInternal
	, public Entity
{
public:
	void initialize() override;
	BoundingBox* getBoundingBox() override;
	BoundingBox* getBoundingBoxTransformed() override;
	void fromTransformations(Transformations* transformations) override;
	void update() override;
	void setEnabled(bool enabled) override;
	void updateParticles() override;

	/**
	 * Public constructor
	 * @param id
	 * @param do collision tests
	 * @param emitter
	 * @param max points
	 * @param auto emit
	 */
	PointsParticleSystemEntity(const wstring& id, bool doCollisionTests, ParticleEmitter* emitter, int32_t maxPoints, bool autoEmit);
public:
	virtual void dispose();
	virtual Color4* getEffectColorAdd();
	virtual Color4* getEffectColorMul();
	virtual const wstring& getId();
	virtual Vector3& getPivot();
	virtual Rotations* getRotations();
	virtual Vector3& getScale();
	virtual Matrix4x4& getTransformationsMatrix();
	virtual Vector3& getTranslation();
	virtual bool isDynamicShadowingEnabled();
	virtual bool isEnabled();
	virtual bool isPickable();
	virtual void setDynamicShadowingEnabled(bool dynamicShadowing);
	virtual void setEngine(Engine* engine);
	virtual void setPickable(bool pickable);
	virtual void setRenderer(GLRenderer* renderer);
};
