#pragma once

#include <agui/agui.h>
#include <agui/gui/events/GUIInputEventHandler.h>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/tools/fwd-tdme.h>
#include <tdme/engine/Transform.h>

using agui::gui::events::GUIInputEventHandler;

using tdme::engine::primitives::BoundingBox;
using tdme::engine::tools::CameraRotationInputHandlerEventHandler;
using tdme::engine::Engine;
using tdme::engine::Transform;

/**
 * Camera Rotation Input Handler
 * @author Andreas Drewke
 */
class tdme::engine::tools::CameraRotationInputHandler final
	: public GUIInputEventHandler
{
private:
	Engine* engine { nullptr };
	bool mouseDragging;
	bool keyLeft;
	bool keyRight;
	bool keyUp;
	bool keyDown;
	bool keyPeriod;
	bool keyComma;
	bool keyPlus;
	bool keyMinus;
	bool keyR;
	int mouseLastX;
	int mouseLastY;
	Transform lookFromRotations;
	float defaultScale;
	float scale;
	bool resetRequested;
	BoundingBox worldBoundingBox;
	CameraRotationInputHandlerEventHandler* eventHandler { nullptr };

public:
	// forbid class copy
	FORBID_CLASS_COPY(CameraRotationInputHandler)

	/**
	 * Public constructor
	 * @param engine engine
	 * @param eventHandler event handler
	 */
	CameraRotationInputHandler(Engine* engine, CameraRotationInputHandlerEventHandler* eventHandler = nullptr);

	/**
	 * Destructor
	 */
	~CameraRotationInputHandler();

	/**
	 * @returns look from rotation
	 */
	const Transform& getLookFromRotations();

	/**
	 * @returns default scale
	 */
	inline float getDefaultScale() {
		return defaultScale;
	}

	/**
	 * Set default scale
	 * @param scale default scale
	 */
	inline void setDefaultScale(float defaultScale) {
		this->defaultScale = defaultScale;
	}

	/**
	 * @returns scale
	 */
	inline float getScale() {
		return scale;
	}

	/**
	 * Set scale
	 * @param scale scale
	 */
	inline void setScale(float scale) {
		this->scale = scale;
	}

	/**
	 * Reset
	 */
	void reset();

	// overridden methods
	void handleInputEvents() override;

};
