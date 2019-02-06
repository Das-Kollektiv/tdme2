
#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>

/** 
 * Timing class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Timing final
{
	friend class Engine;

public:
	static constexpr int64_t UNDEFINED { -1LL };

private:
	int32_t frame {  };
	int64_t startTime {  };
	int64_t lastFrameAtTime {  };
	int64_t currentFrameAtTime {  };
	float currentFPS {  };

	/** 
	 * Updates timing
	 */
	void updateTiming();

	/**
	 * Public constructor
	 */
	Timing();

public:

	/** 
	 * @return frames that have been rendered
	 */
	int32_t getFrame();

	/** 
	 * @return start time
	 */
	int64_t getStartTime();

	/** 
	 * @return time last frame has been rendered in ms
	 */
	int64_t getLastFrameAtTime();

	/** 
	 * @return time current frame has been rendered in ms
	 */
	int64_t getCurrentFrameAtTime();

	/** 
	 * Gets the time passed between last and current frame
	 * @return delta time
	 */
	int64_t getDeltaTime();

	/** 
	 * @return current fps
	 */
	float getCurrentFPS();

	/** 
	 * @return average fps
	 */
	float getAverageFPS();
};
