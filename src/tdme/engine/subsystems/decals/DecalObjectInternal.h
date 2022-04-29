#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/decals/fwd-tdme.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/Transformations.h>

using std::string;
using std::vector;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::Transformations;
using tdme::math::Matrix4x4;

/**
 * Decal object internal
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::decals::DecalObjectInternal
	: public Transformations
{
	friend class tdme::engine::subsystems::rendering::EntityRenderer;

protected:
	string id;
	Engine* engine { nullptr };
	Renderer* renderer { nullptr };
	bool enabled;
	Texture* texture { nullptr };

	BoundingBox boundingBox;
	BoundingBox boundingBoxTransformed;
	Color4 effectColorMul;
	Color4 effectColorAdd;
	bool pickable;
	bool contributesShadows;
	bool receivesShadows;

	/**
	 * Update bounding volume
	 */
	inline void updateBoundingBox() {
		boundingBoxTransformed.fromBoundingVolumeWithTransformations(&boundingBox, *this);
	}

public:
	/**
	 * Public constructor
	 * @param id id
	 * @param texture optional texture
	 */
	DecalObjectInternal(const string& id, Texture* texture = nullptr);

	/**
	 * Destructor
	 */
	virtual ~DecalObjectInternal();

	/**
	 * @return id
	 */
	inline const string& getId() {
		return id;
	}

	/**
	 * Set renderer
	 * @param renderer renderer
	 */
	inline void setRenderer(Renderer* renderer) {
		this->renderer = renderer;
	}

	/**
	 * Set engine
	 * @param engine engine
	 */
	inline void setEngine(Engine* engine) {
		this->engine = engine;
	}

	/**
	 * @return is enabled
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
	 * @return effect color mul
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
	 * @return effect color mul
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
	 * @return is pickable
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
	 * @return if entity contributes to shadows
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
	 * @return if entity receives shadows
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
	 * @return bounding box
	 */
	inline BoundingBox* getBoundingBox() {
		return &boundingBox;
	}

	/**
	 * @return bounding box transformed
	 */
	inline BoundingBox* getBoundingBoxTransformed() {
		return &boundingBoxTransformed;
	}

	/**
	 * Update transformations
	 */
	void update() override;

	/**
	 * From transformations
	 * @param transformations transformations
	 */
	void fromTransformations(const Transformations& transformations) override;

	/**
	 * Initialize
	 */
	void initialize();

	/**
	 * Dispose
	 */
	void dispose();

};
