#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/decals/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/Time.h>

using std::string;

using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Color4;
using tdme::engine::Engine;
using tdme::engine::Texture;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::utilities::Time;

/**
 * Decal entity internal
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::decals::DecalInternal
	: public Transform
{
protected:
	string id;
	Engine* engine { nullptr };
	RendererBackend* rendererBackend { nullptr };
	bool enabled;
	OrientedBoundingBox* obb { nullptr };
	Texture* texture { nullptr };
	int32_t textureHorizontalSprites;
	int32_t textureVerticalSprites;
	float fps;
	float textureSpriteIdx { 0.0f };
	int64_t lastRenderedTime { -1ll };

	BoundingBox boundingBox;
	BoundingBox worldBoundingBox;
	Color4 effectColorMul;
	Color4 effectColorAdd;
	bool pickable;
	bool contributesShadows;
	bool receivesShadows;

	Matrix4x4 entityTransformMatrix;
	Matrix4x4 obbMatrix;
	Matrix4x4 worldObbMatrix;
	Matrix4x4 worldToDecalSpaceMatrix;

	Transform parentTransform;

	/**
	 * Set parent transform
	 * @param parentTransform parent transform
	 */
	inline void setParentTransform(const Transform& parentTransform) {
		this->parentTransform = parentTransform;
		auto entityTransform = parentTransform * (*this);
		entityTransformMatrix = entityTransform.getTransformMatrix();
		//
		updateInternal();
	}

	/**
	 * Update bounding volume and obb matrix with transform and finally world to decal space matrix
	 */
	inline void updateInternal() {
		worldBoundingBox.fromBoundingVolumeWithTransformMatrix(&boundingBox, entityTransformMatrix);
		worldObbMatrix = obbMatrix.clone().multiply(entityTransformMatrix);
		worldToDecalSpaceMatrix = worldObbMatrix.clone().invert();
	}

public:
	// forbid class copy
	FORBID_CLASS_COPY(DecalInternal)

	/**
	 * Public constructor
	 * @param id id
	 * @param obb oriented bounding box
	 * @param texture texture
	 * @param textureHorizonalSprites texture horizonal sprites
	 * @param textureVerticalSprites texture vertical sprites
	 * @param fps frames per seconds
	 */
	DecalInternal(const string& id, OrientedBoundingBox* obb, Texture* texture = nullptr, int32_t textureHorizontalSprites = 1, int32_t textureVerticalSprites = 1, float fps = 10.0f);

	/**
	 * Destructor
	 */
	virtual ~DecalInternal();

	/**
	 * @returns id
	 */
	inline const string& getId() {
		return id;
	}

	/**
	 * Set renderer backend
	 * @param rendererBackend renderer backend
	 */
	inline void setRenderer(RendererBackend* rendererBackend) {
		this->rendererBackend = rendererBackend;
	}

	/**
	 * Set engine
	 * @param engine engine
	 */
	inline void setEngine(Engine* engine) {
		this->engine = engine;
	}

	/**
	 * @returns is enabled
	 */
	inline bool isEnabled() {
		return enabled;
	}

	/**
	 * Set enabled
	 * @param enabled enabled
	 */
	inline void setEnabled(bool enabled) {
		this->enabled = enabled;
	}

	/**
	 * @returns effect color mul
	 */
	inline const Color4& getEffectColorMul() const {
		return effectColorMul;
	}

	/**
	 * Set effect color mul
	 * @param effectColorMul effect color mul
	 */
	inline void setEffectColorMul(const Color4& effectColorMul) {
		this->effectColorMul = effectColorMul;
	}

	/**
	 * @returns effect color mul
	 */
	inline const Color4& getEffectColorAdd() const {
		return effectColorMul;
	}

	/**
	 * Set effect color add
	 * @param effectColorAdd effect color add
	 */
	inline void setEffectColorAdd(const Color4& effectColorAdd) {
		this->effectColorAdd = effectColorAdd;
	}

	/**
	 * @returns is pickable
	 */
	inline bool isPickable() const {
		return pickable;
	}

	/**
	 * Set pickable
	 * @param pickable pickable
	 */
	inline void setPickable(bool pickable) {
		this->pickable = pickable;
	}

	/**
	 * @returns if entity contributes to shadows
	 */
	inline bool isContributesShadows() {
		return contributesShadows;
	}

	/**
	 * Enable/disable contributes shadows
	 * @param contributesShadows contributes shadows
	 */
	inline void setContributesShadows(bool contributesShadows) {
		this->contributesShadows = contributesShadows;
	}

	/**
	 * @returns if entity receives shadows
	 */
	inline bool isReceivesShadows() {
		return receivesShadows;
	}

	/**
	 * Enable/disable receives shadows
	 * @param receivesShadows receives shadows
	 */
	inline void setReceivesShadows(bool receivesShadows) {
		this->receivesShadows = receivesShadows;
	}

	/**
	 * @returns bounding box
	 */
	inline BoundingBox* getBoundingBox() {
		return &boundingBox;
	}

	/**
	 * @returns world bounding box
	 */
	inline BoundingBox* getWorldBoundingBox() {
		return &worldBoundingBox;
	}

	/**
	 * Update transform
	 */
	void update() override;

	/**
	 * From transform
	 * @param transform transform
	 */
	void setTransform(const Transform& transform) override;

	/**
	 * Initialize
	 */
	void initialize();

	/**
	 * Dispose
	 */
	void dispose();

	/**
	 * @returns decal texture
	 */
	inline Texture* getDecalTexture() {
		return texture;
	}

	/**
	 * @returns world to decal space matrix
	 */
	inline const Matrix4x4& getWorldToDecalSpaceMatrix() {
		return worldToDecalSpaceMatrix;
	}

	/**
	 * @returns texture horizontal sprites
	 */
	inline int32_t getTextureHorizontalSprites(){
		return textureHorizontalSprites;
	}

	/**
	 * @returns texture vertical sprites
	 */
	inline int32_t getTextureVerticalSprites(){
		return textureVerticalSprites;
	}

	/**
	 * @returns fps
	 */
	inline float getFPS(){
		return fps;
	}

	/**
	 * @returns current texture sprite index
	 */
	inline int32_t computeTextureSpriteIdx() {
		auto now = Time::getCurrentMillis();
		// first rendering?
		if (lastRenderedTime == -1ll) {
			lastRenderedTime = now;
			return textureSpriteIdx;
		}
		//
		auto timeElapsed = now - lastRenderedTime;
		textureSpriteIdx = Math::mod(textureSpriteIdx + (static_cast<float>(timeElapsed) / 1000.0f) * fps, static_cast<float>(textureHorizontalSprites * textureVerticalSprites));
		//
		lastRenderedTime = now;
		//
		return static_cast<int32_t>(textureSpriteIdx);
	}

};
