#pragma once

#include <map>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/ObjectAnimation.h>
#include <tdme/engine/subsystems/rendering/ObjectInternal.h>
#include <tdme/engine/subsystems/rendering/ObjectNode.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeRenderer.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>

using std::map;
using std::string;
using std::to_string;

using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::EntityRenderer;
using tdme::engine::subsystems::rendering::ObjectAnimation;
using tdme::engine::subsystems::rendering::ObjectInternal;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::engine::subsystems::rendering::ObjectNodeRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMap;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EntityShaderParameters;
using tdme::engine::Timing;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;

/**
 * Object to be used with engine class
 * @author Andreas Drewke
 */
class tdme::engine::Object final
	: public ObjectInternal
	, public Entity
{
private:

	friend class Engine;
	friend class ImposterObject;
	friend class LODObject;
	friend class LODObjectImposter;
	friend class ObjectRenderGroup;
	friend class ObjectParticleSystem;
	friend class SkinnedObjectRenderGroup;
	friend class tdme::engine::subsystems::rendering::EntityRenderer;
	friend class tdme::engine::subsystems::shadowmapping::ShadowMap;

	Engine* engine { nullptr };
	bool frustumCulling { true };
	RenderPass renderPass { RENDERPASS_STANDARD };
	string shaderId;
	uint8_t uniqueShaderId { 0 };
	string reflectionEnvironmentMappingId;
	bool reflectionEnvironmentMappingPositionSet { false };
	Vector3 reflectionEnvironmentMappingPosition;
	Engine::EffectPass excludeFromEffectPass { Engine::EFFECTPASS_NONE };
	bool enableEarlyZRejection { false };
	bool disableDepthTest { false };
	int64_t frameTransformLast { -1LL };
	int64_t timeTransformLast { -1LL };
	EntityShaderParameters shaderParameters;
	bool requiresPreRender { false };
	bool requiresForwardShading { false };
	bool animationComputingLODEnabled { false };

	static constexpr int UNIQUEMODELID_NONE { -1 };

	int uniqueModelId { UNIQUEMODELID_NONE };

	/**
	 * Set unique model id
	 * @param uniqueModelId unique model id
	 */
	inline void setUniqueModelId(int uniqueModelId) {
		this->uniqueModelId = uniqueModelId;
	}

	/**
	 * @return unique model id
	 */
	inline int getUniqueModelId() {
		return uniqueModelId;
	}

	/**
	 * @return if this object instance requries animation computation each frame
	 */
	inline bool isRequiringAnimationComputation() {
		return model->hasSkinning() == true || model->hasAnimations() == true;
	}

	/**
	 * Compute animations
	 * @param contextIdx context index
	 */
	inline void computeAnimations(int contextIdx) {
		auto timing = engine->getTiming();
		auto currentFrameAtTime = timing->getCurrentFrameAtTime();
		auto currentFrame = timing->getFrame();
		auto distanceFromCamera = (engine->getCamera()->getLookFrom() - getWorldBoundingBox()->computeClosestPointInBoundingBox(engine->getCamera()->getLookFrom())).computeLengthSquared();
		if (animationComputingLODEnabled == true) {
			if (distanceFromCamera > Math::square(Engine::getAnimationComputationReduction2Distance())) {
				if (frameTransformLast != -1LL && currentFrame - frameTransformLast < 4) return;
			} else
			if (distanceFromCamera > Math::square(Math::square(Engine::getAnimationComputationReduction1Distance()))) {
				if (frameTransformLast != -1LL && currentFrame - frameTransformLast < 2) return;
			}
		}
		computeAnimation(contextIdx, timeTransformLast, currentFrameAtTime);
		frameTransformLast = timing->getFrame();
		timeTransformLast = currentFrameAtTime;
	}

	/**
	 * Compute animations
	 * @param contextIdx context index
	 * @param lastFrameAtTime time of last animation computation
	 * @param currentFrameAtTime time of current animation computation
	 */
	inline void computeAnimation(int contextIdx, int64_t lastFrameAtTime, int64_t currentFrameAtTime) override {
		ObjectInternal::computeAnimation(contextIdx, lastFrameAtTime, currentFrameAtTime);
	}

	/**
	 * @return if this object instance requires a preRender() call each frame
	 */
	inline bool isRequiringPreRender() {
		return
			requiresPreRender == true ||
			(Engine::animationProcessingTarget != Engine::GPU && model->hasSkinning() == true);
	}

	/**
	 * Pre render step like uploading VBOs and such
	 * @param contextIdx context index
	 */
	inline void preRender(int contextIdx) {
		if (model->hasBoundingBoxUpdate() == true) updateBoundingBox();
		for (auto objectNode: objectNodes) {
			if (objectNode->renderer->needsPreRender() == true) {
				objectNode->renderer->preRender(contextIdx);
			}
		}
	}

	/**
	 * @return if this object needs forward shading
	 */
	inline bool isRequiringForwardShading() {
		return requiresForwardShading == true || reflectionEnvironmentMappingId.empty() == false;
	}

	// overridden methods
	inline void setParentTransform(const Transform& parentTransform) override {
		//
		ObjectInternal::setParentTransform(parentTransform);
		//
		updateBoundingBox();
	}

public:
	/**
	 * Public constructor
	 * @param id id
	 * @param model model
	 * @param instances instances to compute and render by duplication, which only is intended to be used with skinned meshes
	 */
	Object(const string& id, Model* model, int instances);

	/**
	 * Public constructor
	 * @param id id
	 * @param model model
	 */
	Object(const string& id, Model* model);

	/**
	 * Set up if this object instance needs a preRender() call each frame
	 * @param requiresPreRender requires pre render
	 */
	inline void setRequiresPreRender(bool requiresPreRender) {
		this->requiresPreRender = requiresPreRender;
	}

	// overridden methods
	inline EntityType getEntityType() override {
		return ENTITYTYPE_OBJECT;
	}

	void setEngine(Engine* engine) override;
	void setRenderer(Renderer* renderer) override;
	void initialize() override;
	void dispose() override;

	inline bool isEnabled() override {
		return ObjectInternal::isEnabled();
	}

	void setEnabled(bool enabled) override;
	bool isFrustumCulling() override;
	void setFrustumCulling(bool frustumCulling) override;
	void update() override;

	inline BoundingBox* getBoundingBox() override {
		return ObjectInternal::getBoundingBox();
	}

	inline BoundingBox* getWorldBoundingBox() override {
		return ObjectInternal::getWorldBoundingBox();
	}

	inline const Color4& getEffectColorAdd() const override {
		return ObjectInternal::getEffectColorAdd();
	}

	inline void setEffectColorAdd(const Color4& effectColorAdd) override {
		return ObjectInternal::setEffectColorAdd(effectColorAdd);
	}

	inline const Color4& getEffectColorMul() const override {
		return ObjectInternal::getEffectColorMul();
	}

	inline void setEffectColorMul(const Color4& effectColorMul) override {
		return ObjectInternal::setEffectColorMul(effectColorMul);
	}

	inline const string& getId() override {
		return ObjectInternal::getId();
	}

	inline bool isContributesShadows() override {
		return ObjectInternal::isContributesShadows();
	}

	inline void setContributesShadows(bool contributesShadows) override {
		ObjectInternal::setContributesShadows(contributesShadows);
	}

	inline bool isReceivesShadows() override {
		return ObjectInternal::isReceivesShadows();
	}

	inline void setReceivesShadows(bool receivesShadows) override {
		ObjectInternal::setReceivesShadows(receivesShadows);
	}

	inline bool isPickable() override {
		return ObjectInternal::isPickable();
	}

	inline void setPickable(bool pickable) override {
		ObjectInternal::setPickable(pickable);
	}

	inline const Vector3& getTranslation() const override {
		return instanceTransform[currentInstance].getTranslation();
	}

	inline void setTranslation(const Vector3& translation) override {
		instanceTransform[currentInstance].setTranslation(translation);
	}

	inline const Vector3& getScale() const override {
		return instanceTransform[currentInstance].getScale();
	}

	inline void setScale(const Vector3& scale) override {
		instanceTransform[currentInstance].setScale(scale);
	}

	inline const int getRotationCount() const override {
		return instanceTransform[currentInstance].getRotationCount();
	}

	inline Rotation& getRotation(const int idx) override {
		return instanceTransform[currentInstance].getRotation(idx);
	}

	inline void addRotation(const Vector3& axis, const float angle) override {
		instanceTransform[currentInstance].addRotation(axis, angle);
	}

	inline void removeRotation(const int idx) override {
		instanceTransform[currentInstance].removeRotation(idx);
	}

	inline const Vector3& getRotationAxis(const int idx) const override {
		return instanceTransform[currentInstance].getRotationAxis(idx);
	}

	inline void setRotationAxis(const int idx, const Vector3& axis) override {
		instanceTransform[currentInstance].setRotationAxis(idx, axis);
	}

	inline const float getRotationAngle(const int idx) const override {
		return instanceTransform[currentInstance].getRotationAngle(idx);
	}

	inline void setRotationAngle(const int idx, const float angle) override {
		instanceTransform[currentInstance].setRotationAngle(idx, angle);
	}

	inline const Quaternion& getRotationsQuaternion() const override {
		return instanceTransform[currentInstance].getRotationsQuaternion();
	}

	inline const Matrix4x4& getTransformMatrix() const override {
		return ObjectBase::getTransformMatrix();
	}

	inline const Transform& getParentTransform() const override {
		return parentTransform;
	}

	inline const Transform& getTransform() const override {
		return instanceTransform[currentInstance];
	}

	void setTransform(const Transform& transform) override;

	inline RenderPass getRenderPass() const override {
		return renderPass;
	}

	inline void setRenderPass(RenderPass renderPass) override {
		this->renderPass = renderPass;
	}

	/**
	 * @return shader id
	 */
	inline const string& getShader() {
		return shaderId;
	}

	/**
	 * Set shader
	 * @param id shader id
	 */
	void setShader(const string& id);

	/**
	 * @return unique shader id
	 */
	inline uint8_t getUniqueShaderId() {
		return uniqueShaderId;
	}

	/**
	 * @return reflection environment mapping id
	 */
	inline const string& getReflectionEnvironmentMappingId() {
		return reflectionEnvironmentMappingId;
	}

	/**
	 * @return reflection environment mapping id
	 */
	inline void setReflectionEnvironmentMappingId(const string& reflectionEnvironmentMappingId) {
		this->reflectionEnvironmentMappingId = reflectionEnvironmentMappingId;
	}

	/**
	 * @return if object has a reflection environment mapping position
	 */
	inline bool hasReflectionEnvironmentMappingPosition() {
		return reflectionEnvironmentMappingPositionSet;
	}

	/**
	 * @return reflection environment mapping position
	 */
	inline const Vector3& getReflectionEnvironmentMappingPosition() {
		return reflectionEnvironmentMappingPosition;
	}

	/**
	 * Set reflection environment mapping position
	 * @param reflectionEnvironmentMappingPosition reflection environment mapping position
	 */
	inline void setReflectionEnvironmentMappingPosition(const Vector3& reflectionEnvironmentMappingPosition) {
		this->reflectionEnvironmentMappingPositionSet = true;
		this->reflectionEnvironmentMappingPosition = reflectionEnvironmentMappingPosition;
	}

	/**
	 * Unset reflection environment mapping position
	 */
	inline void unsetReflectionEnvironmentMappingPosition() {
		this->reflectionEnvironmentMappingPositionSet = false;
		this->reflectionEnvironmentMappingPosition.set(0.0f, 0.0f, 0.0f);
	}

	/**
	 * @return if to exclude from a certain effect pass
	 */
	inline Engine::EffectPass getExcludeFromEffectPass() const {
		return excludeFromEffectPass;
	}

	/**
	 * Set exclude from effect pass
	 * @param effectPass effect pass
	 */
	inline void setExcludeEffectPass(Engine::EffectPass effectPass) {
		this->excludeFromEffectPass = effectPass;
	}

	/**
	 * @return If early z rejection is enabled
	 */
	inline bool isEnableEarlyZRejection() const {
		return enableEarlyZRejection;
	}

	/**
	 * Enable/disable early z rejection
	 * @param enableEarlyZRejection enable early z rejection
	 */
	inline void setEnableEarlyZRejection(bool enableEarlyZRejection) {
		this->enableEarlyZRejection = enableEarlyZRejection;
	}

	/**
	 * @return if depth test is disabled
	 */
	inline bool isDisableDepthTest() const {
		return disableDepthTest;
	}

	/**
	 * Set disable depth test
	 * @param disableDepthTest disable depth test
	 */
	inline void setDisableDepthTest(bool disableDepthTest) {
		this->disableDepthTest = disableDepthTest;
	}

	/**
	 * Returns shader parameter for given parameter name, if the value does not exist, the default will be returned
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @return shader parameter
	 */
	inline const ShaderParameter getShaderParameter(const string& parameterName) {
		return shaderParameters.getShaderParameter(parameterName);
	}

	/**
	 * Set shader parameter for given parameter name
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @param paraemterValue parameter value
	 */
	inline void setShaderParameter(const string& parameterName, const ShaderParameter& parameterValue) {
		shaderParameters.setShaderParameter(parameterName, parameterValue);
	}

	/**
	 * @return if transform computing LOD is enabled
	 */
	inline bool isAnimationComputationLODEnabled() const {
		return animationComputingLODEnabled;
	}

	/**
	 * Set transform computing LOD enabled
	 * @param animationComputationLODEnabled animation computation LOD enabled
	 */
	inline void setAnimationComputationLODEnabled(bool animationComputationLODEnabled) {
		this->animationComputingLODEnabled = animationComputationLODEnabled;
	}

};
