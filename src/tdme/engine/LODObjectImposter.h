#pragma once

#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/ObjectInternal.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/ImposterObject.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;
using std::unique_ptr;
using std::vector;

using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::rendering::ObjectInternal;
using tdme::engine::Color4;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EntityShaderParameters;
using tdme::engine::ImposterObject;
using tdme::engine::Object;
using tdme::engine::Rotation;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::Console;

/**
 * LOD object + imposter to be used with engine class
 * @author Andreas Drewke
 */
class tdme::engine::LODObjectImposter final:
	public Transform,
	public Entity
{
private:
	Engine* engine { nullptr };
	bool frustumCulling { true };

	Model* modelLOD1 { nullptr };
	float lod2MinDistance;
	float lodNoneMinDistance;

	string id;
	unique_ptr<Object> objectLOD1;
	unique_ptr<ImposterObject> objectLOD2;

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
		objectLOD1->setTransform(entityTransform);
		objectLOD2->setTransform(entityTransform);
	}

public:
	// forbid class copy
	FORBID_CLASS_COPY(LODObjectImposter)

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
	 * @returns LOD object 1
	 */
	inline Object* getLOD1Object() {
		return objectLOD1.get();
	}

	/**
	 * @returns LOD object 2
	 */
	inline ImposterObject* getLOD2Object() {
		return objectLOD2.get();
	}

	/**
	 * @returns LOD object
	 */
	inline Object* getLODObject() {
		return objectLOD;
	}

	/**
	 * Get current lod object
	 * @param camera camera
	 * @returns LOD object to render
	 */
	inline Object* determineLODObject(Camera* camera) {
		// determine LOD object and level type
		auto objectCamFromLengthSquared = getWorldBoundingBox()->computeClosestPointInBoundingBox(camera->getLookFrom()).sub(camera->getLookFrom()).computeLengthSquared();
		if (objectCamFromLengthSquared >= Math::square(lodNoneMinDistance)) {
			objectLOD = nullptr;
			levelLOD = 3;
		} else
		if (objectCamFromLengthSquared >= Math::square(lod2MinDistance)) {
			levelLOD = 2;
			objectLOD = objectLOD2->determineBillboardObject(camera);
		} else {
			objectLOD = objectLOD1.get();
			levelLOD = 1;
		}

		// done
		return objectLOD;
	}

	/**
	 * @returns effect color add for LOD2 level
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
	 * @returns effect color mul for LOD2 level
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
	void setRenderer(RendererBackend* rendererBackend) override;
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
		return objectLOD1->getBoundingBox();
	}

	inline BoundingBox* getWorldBoundingBox() override {
		return objectLOD1->getWorldBoundingBox();
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

	inline const Matrix4x4 getNodeTransformMatrix(const string& id) {
		return objectLOD1->getNodeTransformMatrix(id);
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

	inline const Transform& getParentTransform() const override {
		return parentTransform;
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
		objectLOD1->setRenderPass(renderPass);
		objectLOD2->setRenderPass(renderPass);
	}

	/**
	 * @returns shader id
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
	 * Returns shader parameter for given parameter name, if the value does not exist, the default will be returned
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @returns shader parameter
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

};
