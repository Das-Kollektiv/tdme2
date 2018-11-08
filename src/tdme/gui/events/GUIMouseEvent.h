#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>

using tdme::gui::events::GUIMouseEvent_Type;

/** 
 * GUI mouse event
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::events::GUIMouseEvent
{

private:
	int64_t time {  };
	GUIMouseEvent_Type* type {  };
	int32_t xUnscaled {  };
	int32_t yUnscaled {  };
	int32_t x {  };
	int32_t y {  };
	int32_t button {  };
	float wheelX {  };
	float wheelY {  };
	float wheelZ {  };
	bool metaDown {  };
	bool controlDown {  };
	bool altDown {  };
	bool shiftDown {  };
	bool processed {  };

public:

	/** 
	 * @return time in milliseconds
	 */
	virtual int64_t getTime();

	/** 
	 * Set time
	 * @param time time
	 */
	virtual void setTime(int64_t time);

	/** 
	 * @return type
	 */
	virtual GUIMouseEvent_Type* getType();

	/** 
	 * Set type
	 * @param type type
	 */
	virtual void setType(GUIMouseEvent_Type* type);

	/** 
	 * @return x unscaled
	 */
	virtual int32_t getXUnscaled();

	/**
	 * Set x unscaled
	 * @param x x unscaled
	 */
	virtual void setXUnscaled(int32_t xUnscaled);

	/**
	 * @return y unscaled
	 */
	virtual int32_t getYUnscaled();

	/**
	 * Set y unscaled
	 * @param y y  unscaled
	 */
	virtual void setYUnscaled(int32_t yUnscaled);

	/**
	 * @return x
	 */
	virtual int32_t getX();

	/** 
	 * Set x
	 * @param x x
	 */
	virtual void setX(int32_t x);

	/** 
	 * @return y
	 */
	virtual int32_t getY();

	/** 
	 * Set y
	 * @param y y
	 */
	virtual void setY(int32_t y);

	/** 
	 * @return button
	 */
	virtual int32_t getButton();

	/** 
	 * Set button
	 * @param button button
	 */
	virtual void setButton(int32_t button);

	/** 
	 * @return wheel x
	 */
	virtual float getWheelX();

	/** 
	 * Set up wheel x
	 * @param wheelX wheel x
	 */
	virtual void setWheelX(float wheelX);

	/** 
	 * @return wheel y
	 */
	virtual float getWheelY();

	/** 
	 * Set up wheel y
	 * @param wheelY wheel y
	 */
	virtual void setWheelY(float wheelY);

	/** 
	 * @return wheel z
	 */
	virtual float getWheelZ();

	/** 
	 * Set up wheel z
	 * @param wheelZ wheel z
	 */
	virtual void setWheelZ(float wheelZ);

	/** 
	 * @return is meta down
	 */
	virtual bool isMetaDown();

	/**
	 * Set meta down
	 * @param metaDown meta down
	 */
	virtual void setMetaDown(bool metaDown);

	/**
	 * @return control down
	 */
	virtual bool isControlDown();

	/**
	 * Set control down
	 * @param controlDown control down
	 */
	virtual void setControlDown(bool controlDown);

	/**
	 * @return is alt down
	 */
	virtual bool isAltDown();

	/**
	 * Set alt down
	 * @param altDown alt down
	 */
	virtual void setAltDown(bool altDown);

	/**
	 * @return is shift down
	 */
	virtual bool isShiftDown();

	/**
	 * Set shift down
	 * @param shiftDown shiftDown
	 */
	virtual void setShiftDown(bool shiftDown);

	/**
	 * @return processed
	 */
	virtual bool isProcessed();

	/** 
	 * Set processed 
	 * @param processed processed
	 */
	virtual void setProcessed(bool processed);

	GUIMouseEvent();

private:
	friend class GUIMouseEvent_Type;
};
