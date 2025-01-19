#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/lines/fwd-tdme.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/Transform.h>

using std::string;
using std::vector;

using tdme::engine::Texture;
using tdme::engine::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;

/**
 * Lines entity internal
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::lines::LinesInternal
	: public Transform
{
	friend class tdme::engine::subsystems::rendering::EntityRenderer;

protected:
	string id;
	Engine* engine { nullptr };
	RendererBackend* rendererBackend { nullptr };
	bool enabled;
	float lineWidth;
	Texture* texture { nullptr };
	int32_t textureId { -1 };

	BoundingBox boundingBox;
	BoundingBox worldBoundingBox;
	Color4 effectColorMul;
	Color4 effectColorAdd;
	bool pickable;
	bool contributesShadows;
	bool receivesShadows;

	vector<Vector3> points;
	Color4 color;
	vector<Color4> colors;

	vector<int32_t>* vboIds;

	Transform parentTransform;
	Matrix4x4 entityTransformMatrix;

	/**
	 * Set parent transform
	 * @param parentTransform parent transform
	 */
	inline void setParentTransform(const Transform& parentTransform) {
		//
		this->parentTransform = parentTransform;
		auto entityTransform = parentTransform * (*this);
		entityTransformMatrix = entityTransform.getTransformMatrix();
		//
		updateBoundingBox();
	}
/**
	 * Update bounding volume
	 */
	inline void updateBoundingBox() {
		worldBoundingBox.fromBoundingVolumeWithTransformMatrix(&boundingBox, entityTransformMatrix);
		worldBoundingBox.getMin().sub(0.05f); // scale a bit up to make picking work better
		worldBoundingBox.getMax().add(0.05f); // same here
		worldBoundingBox.update();
	}

public:
	// forbid class copy
	FORBID_CLASS_COPY(LinesInternal)

	/**
	 * Public constructor
	 * @param id id
	 * @param lineWidth line width
	 * @param points points
	 * @param color color
	 * @param colors optional colors
	 * @param texture optional texture
	 */
	LinesInternal(const string& id, float lineWidth, const vector<Vector3>& points, const Color4& color, const vector<Color4>& colors = {}, Texture* texture = nullptr);

	/**
	 * Destructor
	 */
	virtual ~LinesInternal();

	/**
	 * @returns id
	 */
	inline const string& getId() {
		return id;
	}

	/**
	 * Set rendererBackend
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
	 * @returns line width
	 */
	inline float getLineWidth() {
		return lineWidth;
	}

	/**
	 * @returns texture id
	 */
	inline int32_t getTextureId() {
		return textureId;
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

};
