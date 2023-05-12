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
#include <tdme/engine/Object.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
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
using tdme::engine::Object;
using tdme::engine::Rotation;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::Console;

/**
 * Imposter object to be used with engine class
 * @author Andreas Drewke
 */
class tdme::engine::ImposterObject final:
	public Transform,
	public Entity
{
	friend class LODObjectImposter;

private:
	Engine* engine { nullptr };
	bool frustumCulling { true };

	vector<Model*> billboardModels;

	string id;
	vector<Object*> billboardObjects;
	Object* billboardObject { nullptr };

	bool enabled;
	bool pickable;
	bool contributesShadows;
	bool receivesShadows;
	Color4 effectColorMul;
	Color4 effectColorAdd;
	RenderPass renderPass { RENDERPASS_STANDARD };
	string shaderId { "default" };
	bool enableEarlyZRejection { false };

	EntityShaderParameters shaderParameters;

	Transform parentTransform;
	Matrix4x4 entityTransformMatrix;

	// overridden methods
	inline void setParentTransform(const Transform& parentTransform) override {
		//
		this->parentTransform = parentTransform;
		auto entityTransform = parentTransform * (*this);
		entityTransformMatrix = entityTransform.getTransformMatrix();
		// delegate to LOD objects
		for (auto billboardObject: billboardObjects) billboardObject->setTransform(entityTransform);
	}

public:
	/**
	 * Public constructor
	 * @param id id
	 * @param billboardModels billboard models
	 */
	ImposterObject(
		const string& id,
		const vector<Model*>& billboardModels
	);

	/**
	 * Public destructor
	 */
	~ImposterObject();

	// overridden method
	inline EntityType getEntityType() override {
		return ENTITYTYPE_IMPOSTEROBJECT;
	}

	/**
	 * @return billboard objects
	 */
	inline const vector<Object*> getBillboardObjects() {
		return billboardObjects;
	}

	/**
	 * @return billboard object
	 */
	inline Object* getBillboardObject() {
		//
		return billboardObject;
	}

	/**
	 * Get current billboard object
	 * @param camera camera
	 * @return LOD object to render
	 */
	inline Object* determineBillboardObject(Camera* camera) {
		Vector3 cameraForwardVector = getWorldBoundingBox()->getCenter().clone().sub(camera->getLookFrom()).setY(0.0f).normalize();
		auto angle = Vector3::computeAngle(Vector3(0.0, 0.0f, -1.0f), cameraForwardVector, Rotation::Y_AXIS);
		auto imposterIdx = static_cast<int>(angle / 360.0f * billboardModels.size()) % billboardModels.size();
		billboardObject = billboardObjects[imposterIdx];
		// done
		return billboardObject;
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
	void update() override;

	inline BoundingBox* getBoundingBox() override {
		return billboardObject->getBoundingBox();
	}

	inline BoundingBox* getWorldBoundingBox() override {
		return billboardObject->getWorldBoundingBox();
	}

	inline const Color4& getEffectColorMul() const override {
		return effectColorMul;
	}

	inline void setEffectColorMul(const Color4& effectColorMul) override {
		this->effectColorMul = effectColorMul;
		for (auto billboardObject: billboardObjects) billboardObject->setEffectColorMul(effectColorMul);
	}

	inline const Color4& getEffectColorAdd() const override {
		return effectColorAdd;
	}

	inline void setEffectColorAdd(const Color4& effectColorAdd) override {
		this->effectColorAdd = effectColorAdd;
		for (auto billboardObject: billboardObjects) billboardObject->setEffectColorAdd(effectColorAdd);
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
		for (auto billboardObject: billboardObjects) billboardObject->setContributesShadows(contributesShadows);
	}

	inline bool isReceivesShadows() override {
		return receivesShadows;
	}

	inline void setReceivesShadows(bool receivesShadows) override {
		this->receivesShadows = receivesShadows;
		for (auto billboardObject: billboardObjects) billboardObject->setReceivesShadows(receivesShadows);
	}

	inline void setPickable(bool pickable) override {
		this->pickable = pickable;
	}

	inline const Matrix4x4 getNodeTransformMatrix(const string& id) {
		return billboardObject->getNodeTransformMatrix(id);
	}

	inline const Vector3& getTranslation() const override {
		return Transform::getTranslation();
	}

	inline void setTranslation(const Vector3& translation) override {
		Transform::setTranslation(translation);
	}

	inline const Vector3& getScale() const override {
		return Transform::getScale();
	}

	inline void setScale(const Vector3& scale) override {
		Transform::setScale(scale);
	}

	inline const Vector3& getPivot() const override {
		return Transform::getPivot();
	}

	inline void setPivot(const Vector3& pivot) override {
		Transform::setPivot(pivot);
	}

	inline const int getRotationCount() const override {
		return Transform::getRotationCount();
	}

	inline Rotation& getRotation(const int idx) override {
		return Transform::getRotation(idx);
	}

	inline void addRotation(const Vector3& axis, const float angle) override {
		Transform::addRotation(axis, angle);
	}

	inline void removeRotation(const int idx) override {
		Transform::removeRotation(idx);
	}

	inline const Vector3& getRotationAxis(const int idx) const override {
		return Transform::getRotationAxis(idx);
	}

	inline void setRotationAxis(const int idx, const Vector3& axis) override {
		Transform::setRotationAxis(idx, axis);
	}

	inline const float getRotationAngle(const int idx) const override {
		return Transform::getRotationAngle(idx);
	}

	inline void setRotationAngle(const int idx, const float angle) override {
		Transform::setRotationAngle(idx, angle);
	}

	inline const Quaternion& getRotationsQuaternion() const override {
		return Transform::getRotationsQuaternion();
	}

	inline const Matrix4x4& getTransformMatrix() const override {
		return entityTransformMatrix;
	}

	inline const Transform& getTransform() const override {
		return *this;
	}

	void setTransform(const Transform& transform) override;

	inline RenderPass getRenderPass() const override {
		return renderPass;
	}

	inline void setRenderPass(RenderPass renderPass) override {
		this->renderPass = renderPass;
		for (auto billboardObject: billboardObjects) billboardObject->setRenderPass(renderPass);
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
		for (auto billboardObject: billboardObjects) billboardObject->setShader(shaderId);
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
		for (auto billboardObject: billboardObjects) billboardObject->setShaderParameter(parameterName, parameterValue);
	}

};
