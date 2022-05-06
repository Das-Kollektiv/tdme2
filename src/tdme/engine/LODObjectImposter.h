#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/ObjectInternal.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/ImposterObject.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transformations.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::ObjectInternal;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EntityShaderParameters;
using tdme::engine::ImposterObject;
using tdme::engine::Object;
using tdme::engine::Rotation;
using tdme::engine::Transformations;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::Console;

/**
 * LOD object + imposter to be used with engine class
 * @author Andreas Drewke
 */
class tdme::engine::LODObjectImposter final:
	public Transformations,
	public Entity
{
private:
	Engine* engine { nullptr };
	Entity* parentEntity { nullptr };
	bool frustumCulling { true };

	Model* modelLOD1 { nullptr };
	float lod2MinDistance;
	float lodNoneMinDistance;

	string id;
	Object* objectLOD1 { nullptr };
	ImposterObject* objectLOD2 { nullptr };

	Object* objectLOD { nullptr };

	int levelLOD;
	bool enabled;
	bool pickable;
	bool contributesShadows;
	bool receivesShadows;
	Color4 effectColorMul;
	Color4 effectColorAdd;
	Color4 effectColorMulLOD2;
	Color4 effectColorAddLOD2;
	RenderPass renderPass { RENDERPASS_STANDARD };
	string shaderId { "default" };
	string distanceShaderId { "" };
	float distanceShaderDistance { 50.0f };
	bool enableEarlyZRejection { false };

	EntityShaderParameters shaderParameters;
	EntityShaderParameters distanceShaderParameters;

	/**
	 * Set parent entity, needs to be called before adding to engine
	 * @param entity entity
	 */
	inline void setParentEntity(Entity* entity) override {
		this->parentEntity = entity;
	}

	/**
	 * @return parent entity
	 */
	inline Entity* getParentEntity() override {
		return parentEntity;
	}

	// overridden methods
	inline void applyParentTransformations(const Transformations& parentTransformations) override {
		Transformations::applyParentTransformations(parentTransformations);
		// delegate to LOD objects
		objectLOD1->fromTransformations(*this);
		objectLOD2->fromTransformations(*this);
	}

public:
	/**
	 * Public constructor
	 * @param id id
	 * @param modelLOD1 model LOD 1
	 * @param imposterModelsLOD2 imposter models LOD 2
	 * @param lod2MinDistance LOD2 min distance
	 * @param lodNoneMinDistance LOD None min distance
	 */
	LODObjectImposter(
		const string& id,
		Model* modelLOD1,
		const vector<Model*>& imposterModelsLOD2,
		float lod2MinDistance,
		float lodNoneMinDistance = 150.0f
	);

	/**
	 * Public destructor
	 */
	~LODObjectImposter();

	// overridden method
	inline EntityType getEntityType() override {
		return ENTITYTYPE_LODOBJECTIMPOSTER;
	}

	/**
	 * @return LOD object 1
	 */
	inline Object* getLOD1Object() {
		return objectLOD1;
	}

	/**
	 * @return LOD object 2
	 */
	inline ImposterObject* getLOD2Object() {
		return objectLOD2;
	}

	/**
	 * @return LOD object
	 */
	inline Object* getLODObject() {
		return objectLOD;
	}

	/**
	 * Get current lod object
	 * @param camera camera
	 * @return LOD object to render
	 */
	inline Object* determineLODObject(Camera* camera) {
		// determine LOD object and level type
		auto objectCamFromLengthSquared = getBoundingBoxTransformed()->computeClosestPointInBoundingBox(camera->getLookFrom()).sub(camera->getLookFrom()).computeLengthSquared();
		if (objectCamFromLengthSquared >= Math::square(lodNoneMinDistance)) {
			objectLOD = nullptr;
			levelLOD = 3;
		} else
		if (objectCamFromLengthSquared >= Math::square(lod2MinDistance)) {
			levelLOD = 2;
			objectLOD = objectLOD2->determineBillboardObject(camera);
		} else {
			objectLOD = objectLOD1;
			levelLOD = 1;
		}

		// done
		return objectLOD;
	}

	/**
	 * @return effect color add for LOD2 level
	 */
	inline const Color4& getEffectColorAddLOD2() const {
		return effectColorAddLOD2;
	}

	/**
	 * Set effect color add for LOD2 level
	 * @param effectColorAddLOD2 effect color add for LOD2 level
	 */
	inline void setEffectColorAddLOD2(const Color4& effectColorAddLOD2) {
		this->effectColorAddLOD2 = effectColorAddLOD2;
	}

	/**
	 * @return effect color mul for LOD2 level
	 */
	inline const Color4& getEffectColorMulLOD2() const {
		return effectColorMulLOD2;
	}

	/**
	 * Set effect color mul for LOD2 level
	 * @param effectColorMulLOD2 effect color mul for LOD2 level
	 */
	inline void setEffectColorMulLOD2(const Color4& effectColorMulLOD2) {
		this->effectColorMulLOD2 = effectColorMulLOD2;
	}

	// overridden methods
	void setEngine(Engine* engine) override;
	void setRenderer(Renderer* renderer) override;
	void initialize() override;
	void dispose() override;

	inline bool isEnabled() override {
		return enabled;
	}

	void setEnabled(bool enabled) override;
	bool isFrustumCulling() override;
	void setFrustumCulling(bool frustumCulling) override;
	void fromTransformations(const Transformations& transformations) override;
	void update() override;

	inline BoundingBox* getBoundingBox() override {
		return objectLOD1->getBoundingBox();
	}

	inline BoundingBox* getBoundingBoxTransformed() override {
		return objectLOD1->getBoundingBoxTransformed();
	}

	inline const Color4& getEffectColorMul() const override {
		return effectColorMul;
	}

	inline void setEffectColorMul(const Color4& effectColorMul) override {
		this->effectColorMul = effectColorMul;
	}

	inline const Color4& getEffectColorAdd() const override {
		return effectColorAdd;
	}

	inline void setEffectColorAdd(const Color4& effectColorAdd) override {
		this->effectColorAdd = effectColorAdd;
	}

	inline const string& getId() override {
		return id;
	}

	inline bool isPickable() override {
		return pickable;
	}

	inline bool isContributesShadows() override {
		return contributesShadows;
	}

	inline void setContributesShadows(bool contributesShadows) override {
		this->contributesShadows = contributesShadows;
		objectLOD1->setContributesShadows(contributesShadows);
		objectLOD2->setContributesShadows(contributesShadows);
	}

	inline bool isReceivesShadows() override {
		return receivesShadows;
	}

	inline void setReceivesShadows(bool receivesShadows) override {
		this->receivesShadows = receivesShadows;
		objectLOD1->setReceivesShadows(receivesShadows);
		objectLOD2->setReceivesShadows(receivesShadows);
	}

	inline void setPickable(bool pickable) override {
		this->pickable = pickable;
	}

	inline const Matrix4x4 getNodeTransformationsMatrix(const string& id) {
		return objectLOD1->getNodeTransformationsMatrix(id);
	}

	inline const Vector3& getTranslation() const override {
		return Transformations::getTranslation();
	}

	inline void setTranslation(const Vector3& translation) override {
		Transformations::setTranslation(translation);
	}

	inline const Vector3& getScale() const override {
		return Transformations::getScale();
	}

	inline void setScale(const Vector3& scale) override {
		Transformations::setScale(scale);
	}

	inline const Vector3& getPivot() const override {
		return Transformations::getPivot();
	}

	inline void setPivot(const Vector3& pivot) override {
		Transformations::setPivot(pivot);
	}

	inline const int getRotationCount() const override {
		return Transformations::getRotationCount();
	}

	inline Rotation& getRotation(const int idx) override {
		return Transformations::getRotation(idx);
	}

	inline void addRotation(const Vector3& axis, const float angle) override {
		Transformations::addRotation(axis, angle);
	}

	inline void removeRotation(const int idx) override {
		Transformations::removeRotation(idx);
	}

	inline const Vector3& getRotationAxis(const int idx) const override {
		return Transformations::getRotationAxis(idx);
	}

	inline void setRotationAxis(const int idx, const Vector3& axis) override {
		Transformations::setRotationAxis(idx, axis);
	}

	inline const float getRotationAngle(const int idx) const override {
		return Transformations::getRotationAngle(idx);
	}

	inline void setRotationAngle(const int idx, const float angle) override {
		Transformations::setRotationAngle(idx, angle);
	}

	inline const Quaternion& getRotationsQuaternion() const override {
		return Transformations::getRotationsQuaternion();
	}

	inline const Matrix4x4& getTransformationsMatrix() const override {
		return Transformations::getTransformationsMatrix();
	}

	inline const Transformations& getTransformations() const override {
		return *this;
	}

	inline RenderPass getRenderPass() const override {
		return renderPass;
	}

	inline void setRenderPass(RenderPass renderPass) override {
		this->renderPass = renderPass;
		objectLOD1->setRenderPass(renderPass);
		objectLOD2->setRenderPass(renderPass);
	}

	/**
	 * @return shader id
	 */
	inline const string& getShader() {
		return shaderId;
	}

	/**
	 * Set shader id
	 * @param id shader
	 */
	inline void setShader(const string& id) {
		this->shaderId = id;
		shaderParameters.setShader(shaderId);
		objectLOD1->setShader(shaderId);
		objectLOD2->setShader(shaderId);
	}

	/**
	 * @return distance shader id
	 */
	inline const string& getDistanceShader() {
		return distanceShaderId;
	}

	/**
	 * Set distance shader id
	 * @param id shader
	 */
	inline void setDistanceShader(const string& id) {
		this->distanceShaderId = id;
		distanceShaderParameters.setShader(distanceShaderId);
		objectLOD1->setDistanceShader(distanceShaderId);
		objectLOD2->setDistanceShader(distanceShaderId);
	}

	/**
	 * @return distance shader distance
	 */
	inline float getDistanceShaderDistance() {
		return distanceShaderDistance;
	}

	/**
	 * Set distance shader distance
	 * @param distanceShaderDistance shader
	 */
	inline void setDistanceShaderDistance(float distanceShaderDistance) {
		this->distanceShaderDistance = distanceShaderDistance;
		objectLOD1->setDistanceShaderDistance(distanceShaderDistance);
		objectLOD2->setDistanceShaderDistance(distanceShaderDistance);
	}

	/**
	 * @return If early z rejection is enabled
	 */
	bool isEnableEarlyZRejection() const {
		return enableEarlyZRejection;
	}

	/**
	 * Enable/disable early z rejection
	 * @param enableEarlyZRejection enable early z rejection
	 */
	void setEnableEarlyZRejection(bool enableEarlyZRejection);

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
		objectLOD1->setShaderParameter(parameterName, parameterValue);
		objectLOD2->setShaderParameter(parameterName, parameterValue);
	}

	/**
	 * Returns distance shader parameter for given parameter name, if the value does not exist, the default will be returned
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @return shader parameter
	 */
	inline const ShaderParameter getDistanceShaderParameter(const string& parameterName) {
		return distanceShaderParameters.getShaderParameter(parameterName);
	}

	/**
	 * Set distance shader parameter for given parameter name
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @param paraemterValue parameter value
	 */
	inline void setDistanceShaderParameter(const string& parameterName, const ShaderParameter& parameterValue) {
		distanceShaderParameters.setShaderParameter(parameterName, parameterValue);
		objectLOD1->setDistanceShaderParameter(parameterName, parameterValue);
		objectLOD2->setDistanceShaderParameter(parameterName, parameterValue);
	}

};
