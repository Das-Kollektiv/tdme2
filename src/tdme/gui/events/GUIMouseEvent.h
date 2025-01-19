#pragma once

#include <tdme/tdme.h>
#include <tdme/application/InputDefinitions.h>
#include <tdme/gui/events/fwd-tdme.h>

/**
 * GUI mouse event
 * @author Andreas Drewke
 */
class tdme::gui::events::GUIMouseEvent final
{
public:
	enum GUIMouseEventType {
		MOUSEEVENT_NONE,
		MOUSEEVENT_WHEEL_MOVED,
		MOUSEEVENT_PRESSED,
		MOUSEEVENT_RELEASED,
		MOUSEEVENT_MOVED,
		MOUSEEVENT_DRAGGED
	};

	enum GUIMouseEventButton {
		MOUSEEVENT_BUTTON_NONE = MOUSE_BUTTON_NONE,
		MOUSEEVENT_BUTTON_LEFT = MOUSE_BUTTON_LEFT,
		MOUSEEVENT_BUTTON_RIGHT = MOUSE_BUTTON_RIGHT,
		MOUSEEVENT_BUTTON_MIDDLE = MOUSE_BUTTON_MIDDLE
	};

private:
	int64_t time { -1LL };
	GUIMouseEventType type { MOUSEEVENT_NONE };
	int xUnscaled { -1 };
	int yUnscaled { -1 };
	int x { -1 };
	int y { -1 };
	int button { -1 };
	float wheelX { 0.0f };
	float wheelY { 0.0f };
	float wheelZ { 0.0f };
	bool metaDown { false };
	bool controlDown { false };
	bool altDown { false };
	bool shiftDown { false };
	bool processed { false };

public:
	/**
	 * Constructor
	 */
	inline GUIMouseEvent() {
	}

	/**
	 * Destructor
	 */
	inline ~GUIMouseEvent() {
	}

	/**
	 * @returns time in milliseconds
	 */
	inline int64_t getTime() const {
		return time;
	}

	/**
	 * Set time
	 * @param time time
	 */
	inline void setTime(int64_t time) {
		this->time = time;
	}

	/**
	 * @returns type
	 */
	inline GUIMouseEventType getType() const {
		return type;
	}

	/**
	 * Set type
	 * @param type type
	 */
	inline void setType(GUIMouseEventType type) {
		this->type = type;
	}

	/**
	 * @returns x unscaled
	 */
	inline int getXUnscaled() const {
		return xUnscaled;
	}

	/**
	 * Set x unscaled
	 * @param x x unscaled
	 */
	inline void setXUnscaled(int xUnscaled) {
		this->xUnscaled = xUnscaled;
	}

	/**
	 * @returns y unscaled
	 */
	inline int getYUnscaled() const {
		return yUnscaled;
	}

	/**
	 * Set y unscaled
	 * @param y y  unscaled
	 */
	inline void setYUnscaled(int yUnscaled) {
		this->yUnscaled = yUnscaled;
	}

	/**
	 * @returns x
	 */
	inline int getX() const {
		return x;
	}

	/**
	 * Set x
	 * @param x x
	 */
	inline void setX(int x) {
		this->x = x;
	}

	/**
	 * @returns y
	 */
	inline int getY() const {
		return y;
	}

	/**
	 * Set y
	 * @param y y
	 */
	inline void setY(int y) {
		this->y = y;
	}

	/**
	 * @returns button
	 */
	inline int getButton() const {
		return button;
	}

	/**
	 * Set button
	 * @param button button
	 */
	inline void setButton(int button) {
		this->button = button;
	}

	/**
	 * @returns wheel x
	 */
	inline float getWheelX() const {
		return wheelX;
	}

	/**
	 * Set up wheel x
	 * @param wheelX wheel x
	 */
	inline void setWheelX(float wheelX) {
		this->wheelX = wheelX;
	}

	/**
	 * @returns wheel y
	 */
	inline float getWheelY() const {
		return wheelY;
	}

	/**
	 * Set up wheel y
	 * @param wheelY wheel y
	 */
	inline void setWheelY(float wheelY) {
		this->wheelY = wheelY;
	}

	/**
	 * @returns wheel z
	 */
	inline float getWheelZ() const {
		return wheelZ;
	}

	/**
	 * Set up wheel z
	 * @param wheelZ wheel z
	 */
	inline void setWheelZ(float wheelZ) {
		this->wheelZ = wheelZ;
	}

	/**
	 * @returns is meta down
	 */
	inline bool isMetaDown() const {
		return metaDown;
	}

	/**
	 * Set meta down
	 * @param metaDown meta down
	 */
	inline void setMetaDown(bool metaDown) {
		this->metaDown = metaDown;
	}

	/**
	 * @returns control down
	 */
	inline bool isControlDown() const {
		return controlDown;
	}

	/**
	 * Set control down
	 * @param controlDown control down
	 */
	inline void setControlDown(bool controlDown) {
		this->controlDown = controlDown;
	}

	/**
	 * @returns is alt down
	 */
	inline bool isAltDown() const {
		return altDown;
	}

	/**
	 * Set alt down
	 * @param altDown alt down
	 */
	inline void setAltDown(bool altDown) {
		this->altDown = altDown;
	}

	/**
	 * @returns is shift down
	 */
	inline bool isShiftDown() const {
		return shiftDown;
	}

	/**
	 * Set shift down
	 * @param shiftDown shiftDown
	 */
	inline void setShiftDown(bool shiftDown) {
		this->shiftDown = shiftDown;
	}

	/**
	 * @returns processed
	 */
	inline bool isProcessed() const {
		return processed;
	}

	/**
	 * Set processed
	 * @param processed processed
	 */
	inline void setProcessed(bool processed) {
		this->processed = processed;
	}

};
