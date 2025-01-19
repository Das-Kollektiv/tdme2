#pragma once

#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/LODObject.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::array;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

using tdme::engine::Color4;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EntityShaderParameters;
using tdme::engine::LODObject;
using tdme::engine::Object;
using tdme::engine::Rotation;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Object render group for static objects that might be animated by shaders
 * @author Andreas Drewke
 */
class tdme::engine::ObjectRenderGroup final:
	public Transform,
	public Entity
{
private:
	Engine* engine { nullptr };
	bool frustumCulling { true };

	string id;
	bool enabled;
	bool pickable;
	bool contributesShadows;
	bool receivesShadows;
	Color4 effectColorMul;
	Color4 effectColorAdd;
	BoundingBox boundingBox;
	BoundingBox worldBoundingBox;
	float modelLOD2MinDistance;
	float modelLOD3MinDistance;
	unique_ptr<Entity> combinedEntity;
	unordered_map<Model*, vector<Transform>> transformByModel;
	vector<unique_ptr<Model>> combinedModels;
	RenderPass renderPass { RENDERPASS_STANDARD };
	string shaderId { "default" };
	array<int, 3> lodReduceBy;

	EntityShaderParameters shaderParameters;

	bool optimizeModels;

	Transform parentTransform;
	Matrix4x4 entityTransformMatrix;

	/**
	 * Compute bounding box
	 */
	inline void updateBoundingBox() {
		if (combinedEntity == nullptr) return;
		boundingBox.fromBoundingVolume(combinedEntity->getBoundingBox());
		worldBoundingBox.fromBoundingVolumeWithTransformMatrix(&boundingBox, entityTransformMatrix);
	}

	/**
	 * Combine node into given combined model
	 * @param sourceNode source node to combine into current model
	 * @param origins origins
	 * @param objectParentTransformMatrices object parent transform matrix
	 * @param combinedModel combined model
	 * @param reduceFactorBy reduce factor by
	 */
	static void combineNode(Node* sourceNode, const vector<Vector3>& origins, const vector<Matrix4x4>& objectParentTransformMatrices, Model* combinedModel);

	/**
	 * Combine model with transform into current model
	 * @param model model
	 * @param transform transform
	 * @param combinedModel combined model
	 * @param reduceFactorBy reduce factor by
	 * @return model
	 */
	static void combineObjects(Model* model, const vector<Transform>& objectsTransform, Model* combinedModel);

	// overridden methods
	inline void setParentTransform(const Transform& parentTransform) override {
		//
		this->parentTransform = parentTransform;
		auto entityTransform = parentTransform * (*this);
		entityTransformMatrix = entityTransform.getTransformMatrix();
		//
		if (combinedEntity != nullptr) combinedEntity->setParentTransform(parentTransform);
		//
		updateBoundingBox();
	}

public:
	// forbid class copy
	FORBID_CLASS_COPY(ObjectRenderGroup)

	/**
	 * Public constructor
	 * @param id id
	 * @param model model
	 * @param lodLevels lod levels
	 * @param modelLOD2MinDistance model LOD 2 min distance
	 * @param modelLOD3MinDistance model LOD 3 min distance
	 * @param modelLOD2ReduceBy model LOD 2 reduce by factor
	 * @param modelLOD3ReduceBy model LOD 3 reduce by factor
	 * @param optimizeModels optimize models
	 */
	ObjectRenderGroup(
		const string& id,
		int lodLevels = 1,
		float modelLOD2MinDistance = 25.0f,
		float modelLOD3MinDistance = 50.0f,
		int modelLOD2ReduceBy = 4,
		int modelLOD3ReduceBy = 16,
		bool optimizeModels = true
	);

	/**
	 * Destructor
	 */
	~ObjectRenderGroup();

	// overridden methods
	inline EntityType getEntityType() override {
		return ENTITYTYPE_OBJECTRENDERGROUP;
	}

	/**
	 * Update render group model and bounding box
	 */
	void updateRenderGroup();

	/**
	 * @return entity
	 */
	inline Entity* getEntity() {
		return combinedEntity.get();
	}

	/**
	 * Adds a instance to this render group
	 * @param model model
	 * @param transform transform
	 */
	void addObject(Model* model, const Transform& transform);

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
		return &boundingBox;
	}

	inline BoundingBox* getWorldBoundingBox() override {
		return &worldBoundingBox;
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
		if (combinedEntity != nullptr) combinedEntity->setContributesShadows(contributesShadows);
	}

	inline bool isReceivesShadows() override {
		return receivesShadows;
	}

	inline void setReceivesShadows(bool receivesShadows) override {
		this->receivesShadows = receivesShadows;
		if (combinedEntity != nullptr) combinedEntity->setReceivesShadows(receivesShadows);
	}

	inline void setPickable(bool pickable) override {
		if (combinedEntity != nullptr) combinedEntity->setPickable(pickable);
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
		if (combinedEntity == nullptr) return;
		combinedEntity->setRenderPass(renderPass);
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
		shaderParameters.setShader(id);
		// TODO: put me into entity interface
		if (combinedEntity == nullptr) return;
		if (combinedEntity->getEntityType() == Entity::ENTITYTYPE_OBJECT) {
			static_cast<Object*>(combinedEntity.get())->setShader(id);
			shaderParameters.setShader(static_cast<Object*>(combinedEntity.get())->getShader());
		} else
		if (combinedEntity->getEntityType() == Entity::ENTITYTYPE_LODOBJECT) {
			static_cast<LODObject*>(combinedEntity.get())->setShader(id);
			shaderParameters.setShader(static_cast<LODObject*>(combinedEntity.get())->getShader());
		}
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
		if (combinedEntity == nullptr) return;
		if (combinedEntity->getEntityType() == Entity::ENTITYTYPE_OBJECT) {
			static_cast<Object*>(combinedEntity.get())->setShaderParameter(parameterName, parameterValue);
		} else
		if (combinedEntity->getEntityType() == Entity::ENTITYTYPE_LODOBJECT) {
			static_cast<LODObject*>(combinedEntity.get())->setShaderParameter(parameterName, parameterValue);
		}
	}

};
