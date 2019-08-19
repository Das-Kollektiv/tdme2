#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/lines/fwd-tdme.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/Transformations.h>

using std::string;
using std::vector;

using tdme::engine::Transformations;
using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::model::Color4;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix4x4;

/** 
 * Lines object internal
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::lines::LinesObject3DInternal
	: public Transformations
{
	friend class tdme::engine::subsystems::rendering::Object3DRenderer;

protected:
	string id {  };
	Engine* engine {  };
	Renderer* renderer {  };
	bool enabled {  };
	float pointSize {  };
	Texture* texture { nullptr };
	int32_t textureId {  };

	BoundingBox boundingBox {  };
	BoundingBox boundingBoxTransformed {  };
	Color4 effectColorMul {  };
	Color4 effectColorAdd {  };
	bool pickable {  };
	bool dynamicShadowing {  };

	vector<Vector3> points;
	Color4 color;
	vector<Color4> colors;

	vector<int32_t>* vboIds;
public:
	/**
	 * @return id
	 */
	inline virtual const string& getId() {
		return id;
	}

	/**
	 * Set renderer
	 * @param renderer renderer
	 */
	inline virtual void setRenderer(Renderer* renderer) {
		this->renderer = renderer;
	}

	/**
	 * Set engine
	 * @param engine engine
	 */
	inline virtual void setEngine(Engine* engine) {
		this->engine = engine;
	}

	/**
	 * @return is enabled
	 */
	inline virtual bool isEnabled() {
		return enabled;
	}

	/**
	 * Set enabled
	 * @param enabled enabled
	 */
	inline virtual void setEnabled(bool enabled) {
		this->enabled = enabled;
	}

	/**
	 * @return effect color mul
	 */
	inline virtual const Color4& getEffectColorMul() const {
		return effectColorMul;
	}

	/**
	 * Set effect color mul
	 * @param effectColorMul effect color mul
	 */
	inline virtual void setEffectColorMul(const Color4& effectColorMul) {
		this->effectColorMul = effectColorMul;
	}

	/**
	 * @return effect color mul
	 */
	inline virtual const Color4& getEffectColorAdd() const {
		return effectColorMul;
	}

	/**
	 * Set effect color add
	 * @param effectColorAdd effect color add
	 */
	inline virtual void setEffectColorAdd(const Color4& effectColorAdd) {
		this->effectColorAdd = effectColorAdd;
	}

	/**
	 * @return is pickable
	 */
	inline virtual bool isPickable() const {
		return pickable;
	}

	/**
	 * Set pickable
	 * @param pickable pickable
	 */
	inline virtual void setPickable(bool pickable) {
		this->pickable = pickable;
	}

	/** 
	 * @return dynamic shadowing enabled
	 */
	inline virtual bool isDynamicShadowingEnabled() {
		return dynamicShadowing;
	}

	/** 
	 * Enable/disable dynamic shadowing
	 * @param dynamicShadowing dynamicShadowing
	 */
	inline virtual void setDynamicShadowingEnabled(bool dynamicShadowing) {
		this->dynamicShadowing = dynamicShadowing;
	}

	/**
	 * @return bounding box
	 */
	inline virtual BoundingBox* getBoundingBox() {
		return &boundingBox;
	}

	/**
	 * @return bounding box transformed
	 */
	inline virtual BoundingBox* getBoundingBoxTransformed() {
		return &boundingBoxTransformed;
	}

	/**
	 * @return point size
	 */
	inline float getPointSize() {
		return pointSize;
	}

	/**
	 * @return texture id
	 */
	inline int32_t getTextureId() {
		return textureId;
	}

	/** 
	 * Update transformations
	 */
	virtual void update() override;

	/**
	 * From transformations
	 * @param transformations transformations
	 */
	virtual void fromTransformations(const Transformations& transformations) override;

	/**
	 * Initialize
	 */
	virtual void initialize();

	/**
	 * Dispose
	 */
	virtual void dispose();

	/**
	 * Public constructor
	 * @param id id
	 * @param pointSize point size
	 * @param points points
	 * @param color color
	 * @param colors optional colors
	 * @param texture optional texture
	 */
	LinesObject3DInternal(const string& id, float pointSize, const vector<Vector3>& points, const Color4& color, const vector<Color4>& colors = {}, Texture* texture = nullptr);

	/**
	 * Destructor
	 */
	virtual ~LinesObject3DInternal();
};
