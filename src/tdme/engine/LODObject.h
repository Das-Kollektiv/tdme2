#pragma once

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Color4.h>
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
using std::unique_ptr;

using tdme::engine::Color4;
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
 * LOD object to be used with engine class
 * @author Andreas Drewke
 */
class tdme::engine::LODObject final:
	public Transform,
	public Entity
{
public:
	enum LODLevelType { LODLEVELTYPE_NONE, LODLEVELTYPE_MODEL, LODLEVELTYPE_IGNORE };

private:
	friend class ObjectRenderGroup;

	Engine* engine { nullptr };
	bool frustumCulling { true };

	Model* modelLOD1 { nullptr };
	Model* modelLOD2 { nullptr };
	Model* modelLOD3 { nullptr };
	float modelLOD2MinDistance;
	float modelLOD3MinDistance;
	float lodNoneMinDistance;
	LODLevelType levelTypeLOD2;
	LODLevelType levelTypeLOD3;

	string id;
	unique_ptr<Object> objectLOD1;
	unique_ptr<Object> objectLOD2;
	unique_ptr<Object> objectLOD3;
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
	Color4 effectColorMulLOD3;
	Color4 effectColorAddLOD3;
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
		if (objectLOD1 != nullptr) objectLOD1->setTransform(entityTransform);
		if (objectLOD2 != nullptr) objectLOD2->setTransform(entityTransform);
		if (objectLOD3 != nullptr) objectLOD3->setTransform(entityTransform);
	}

public:
	// forbid class copy
	FORBID_CLASS_COPY(LODObject)

	/**
	 * Public constructor
	 * @param id id
	 * @param modelLOD1 model LOD 1
	 * @param levelTypeLOD2 LOD level type LOD2
	 * @param modelLOD2MinDistance model LOD 2 min distance
	 * @param modelLOD2 model LOD 2
	 * @param levelTypeLOD3 LOD level type LOD3
	 * @param modelLOD3MinDistance model LOD 3 min distance
	 * @param modelLOD3 model LOD 3
	 * @param lodNoneMinDistance LOD None min distance
	 */
	LODObject(
		const string& id,
		Model* modelLOD1,
		LODLevelType levelTypeLOD2,
		float modelLOD2MinDistance,
		Model* modelLOD2,
		LODLevelType levelTypeLOD3,
		float modelLOD3MinDistance,
		Model* modelLOD3,
		float lodNoneMinDistance = 150.0f
	);

	/**
	 * Public destructor
	 */
	~LODObject();

	// overridden method
	inline EntityType getEntityType() override {
		return ENTITYTYPE_LODOBJECT;
	}

	/**
	 * @return LOD object 1
	 */
	inline Object* getLOD1Object() {
		return objectLOD1.get();
	}

	/**
	 * @return LOD object 2
	 */
	inline Object* getLOD2Object() {
		return objectLOD2.get();
	}

	/**
	 * @return LOD object 3
	 */
	inline Object* getLOD3Object() {
		return objectLOD3.get();
	}

	/**
	 * @return LOD object
	 */
	inline Object* getLODObject() {
		// set effect colors
		if (objectLOD != nullptr) {
			// set effect colors
			if (objectLOD != nullptr) {
				if (levelLOD == 3) {
					objectLOD->setEffectColorAdd(effectColorAddLOD3);
					objectLOD->setEffectColorMul(effectColorMulLOD3);
				} else
				if (levelLOD == 2) {
					objectLOD->setEffectColorAdd(effectColorAddLOD2);
					objectLOD->setEffectColorMul(effectColorMulLOD2);
				} else {
					objectLOD->setEffectColorAdd(Color4(0.0f, 0.0f, 0.0f, 0.0f));
					objectLOD->setEffectColorMul(Color4(1.0f, 1.0f, 1.0f, 1.0f));
				}
				auto effectColorAdd = objectLOD->getEffectColorAdd();
				auto effectColorMul = objectLOD->getEffectColorMul();
				effectColorAdd.add(this->effectColorAdd);
				effectColorMul.scale(this->effectColorMul);
				objectLOD->setEffectColorAdd(effectColorAdd);
				objectLOD->setEffectColorMul(effectColorMul);
			}
		}

		//
		return objectLOD;
	}

	/**
	 * Get current lod object
	 * @param camera camera
	 * @return LOD object to render
	 */
	inline Object* determineLODObject(Camera* camera) {
		LODObject::LODLevelType lodLevelType = LODObject::LODLEVELTYPE_NONE;
		// determine LOD object and level type
		auto objectCamFromLengthSquared = getWorldBoundingBox()->computeClosestPointInBoundingBox(camera->getLookFrom()).sub(camera->getLookFrom()).computeLengthSquared();
		if (objectCamFromLengthSquared >= Math::square(lodNoneMinDistance)) {
			objectLOD = nullptr;
			levelLOD = 4;
		} else
		if (levelTypeLOD3 != LODLEVELTYPE_NONE &&
			objectCamFromLengthSquared >= Math::square(modelLOD3MinDistance)) {
			objectLOD = objectLOD3.get();
			levelLOD = 3;
		} else
		if (levelTypeLOD2 != LODLEVELTYPE_NONE &&
			objectCamFromLengthSquared >= Math::square(modelLOD2MinDistance)) {
			objectLOD = objectLOD2.get();
			levelLOD = 2;
		} else {
			objectLOD = objectLOD1.get();
			levelLOD = 1;
		}

		// set effect colors
		if (objectLOD != nullptr) {
			if (levelLOD == 3) {
				objectLOD->setEffectColorAdd(effectColorAddLOD3);
				objectLOD->setEffectColorMul(effectColorMulLOD3);
			} else
			if (levelLOD == 2) {
				objectLOD->setEffectColorAdd(effectColorAddLOD2);
				objectLOD->setEffectColorMul(effectColorMulLOD2);
			} else {
				objectLOD->setEffectColorAdd(Color4(0.0f, 0.0f, 0.0f, 0.0f));
				objectLOD->setEffectColorMul(Color4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			auto effectColorAdd = objectLOD->getEffectColorAdd();
			auto effectColorMul = objectLOD->getEffectColorMul();
			effectColorAdd.add(this->effectColorAdd);
			effectColorMul.scale(this->effectColorMul);
			objectLOD->setEffectColorAdd(effectColorAdd);
			objectLOD->setEffectColorMul(effectColorMul);
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

	/**
	 * @return effect color add for LOD3 level
	 */
	inline const Color4& getEffectColorAddLOD3() const {
		return effectColorAddLOD3;
	}

	/**
	 * Set effect color add for LOD3 level
	 * @param effectColorAddLOD3 effect color add for LOD3 level
	 */
	inline void setEffectColorAddLOD3(const Color4& effectColorAddLOD3) {
		this->effectColorAddLOD3 = effectColorAddLOD3;
	}

	/**
	 * @return effect color mul for LOD3 level
	 */
	inline const Color4& getEffectColorMulLOD3() const {
		return effectColorMulLOD3;
	}

	/**
	 * Set effect color mul for LOD3 level
	 * @param effectColorMulLOD3 effect color mul for LOD3 level
	 */
	inline void setEffectColorMulLOD3(const Color4& effectColorMulLOD3) {
		this->effectColorMulLOD3 = effectColorMulLOD3;
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
		if (objectLOD1 != nullptr) objectLOD1->setContributesShadows(contributesShadows);
		if (objectLOD2 != nullptr) objectLOD2->setContributesShadows(contributesShadows);
		if (objectLOD3 != nullptr) objectLOD3->setContributesShadows(contributesShadows);
	}

	inline bool isReceivesShadows() override {
		return receivesShadows;
	}

	inline void setReceivesShadows(bool receivesShadows) override {
		this->receivesShadows = receivesShadows;
		if (objectLOD1 != nullptr) objectLOD1->setReceivesShadows(receivesShadows);
		if (objectLOD2 != nullptr) objectLOD2->setReceivesShadows(receivesShadows);
		if (objectLOD3 != nullptr) objectLOD3->setReceivesShadows(receivesShadows);
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
		if (objectLOD1 != nullptr) objectLOD1->setRenderPass(renderPass);
		if (objectLOD2 != nullptr) objectLOD2->setRenderPass(renderPass);
		if (objectLOD3 != nullptr) objectLOD3->setRenderPass(renderPass);
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
		if (objectLOD1 != nullptr) objectLOD1->setShader(shaderId);
		if (objectLOD2 != nullptr) objectLOD2->setShader(shaderId);
		if (objectLOD3 != nullptr) objectLOD3->setShader(shaderId);
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
		if (objectLOD1 != nullptr) objectLOD1->setShaderParameter(parameterName, parameterValue);
		if (objectLOD2 != nullptr) objectLOD2->setShaderParameter(parameterName, parameterValue);
		if (objectLOD3 != nullptr) objectLOD3->setShaderParameter(parameterName, parameterValue);
	}

};
