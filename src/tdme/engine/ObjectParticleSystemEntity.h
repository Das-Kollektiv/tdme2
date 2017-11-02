#pragma once

#include <vector>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/ObjectParticleSystemEntityInternal.h>
#include <tdme/engine/Entity.h>

using std::vector;
using std::string;

using tdme::engine::subsystems::particlesystem::ObjectParticleSystemEntityInternal;
using tdme::engine::Entity;
using tdme::engine::Engine;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::particlesystem::ParticleEmitter;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Object particle system entity to be used with engine class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::ObjectParticleSystemEntity final
	: public ObjectParticleSystemEntityInternal
	, public Entity
{
private:
	bool frustumCulling { true };

public:
	void initialize() override;
	BoundingBox* getBoundingBox() override;
	BoundingBox* getBoundingBoxTransformed() override;

	/** 
	 * @return enabled objects
	 */
	const vector<Object3D*>* getEnabledObjects();
	void fromTransformations(Transformations* transformations) override;
	void update() override;
	void setEnabled(bool enabled) override;
	void updateParticles() override;
	bool isFrustumCulling() override;
	void setFrustumCulling(bool frustumCulling) override;

	/**
	 * Public constructor
	 * @param id
	 * @param model
	 * @param scale
	 * @param auto emit
	 * @param enable dynamic shadows
	 * @param max count
	 * @param emitter
	 */
	ObjectParticleSystemEntity(const string& id, Model* model, const Vector3& scale, bool autoEmit, bool enableDynamicShadows, int32_t maxCount, ParticleEmitter* emitter);

public:
	virtual void dispose();
	virtual Color4& getEffectColorAdd();
	virtual Color4& getEffectColorMul();
	virtual const string& getId();
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
