#pragma once

#include <array>

#include <agui/agui.h>
#include <agui/gui/misc/fwd-agui.h>

using std::array;

/**
 * GUI Timing class
 * @author Andreas Drewke
 */
class agui::gui::misc::GUITiming final
{
	friend class GUI;

public:
	static constexpr int64_t UNDEFINED { -1LL };

private:
	int64_t frame;
	int64_t startTime;
	int64_t lastFrameAtTime;
	int64_t currentFrameAtTime;
	float fps;
	float avarageFPS;
	array<float, 60 * 3> avarageFPSSequence;
	int avarageFPSIndex { 0 };

public:
	// forbid class copy
	FORBID_CLASS_COPY(GUITiming)

	/**
	 * Public constructor
	 */
	GUITiming();

	/**
	 * @returns frames that have been rendered
	 */
	inline int64_t getFrame() {
		return frame;
	}

	/**
	 * @returns start time
	 */
	inline int64_t getStartTime() {
		return startTime;
	}

	/**
	 * @returns total time the engine is running
	 */
	inline int64_t getTotalTime() {
		return currentFrameAtTime - startTime;
	}

	/**
	 * @returns time last frame has been rendered in ms
	 */
	inline int64_t getLastFrameAtTime() {
		return lastFrameAtTime;
	}

	/**
	 * @returns time current frame has been rendered in ms
	 */
	inline int64_t getCurrentFrameAtTime() {
		return currentFrameAtTime;
	}

	/**
	 * Gets the time passed between last and current frame
	 * @returns delta time
	 */
	inline int64_t getDeltaTime() {
		if (currentFrameAtTime == UNDEFINED || lastFrameAtTime == UNDEFINED) {
			return 0LL;
		}
		return currentFrameAtTime - lastFrameAtTime;
	}

	/**
	 * Gets the time passed between last and current frame in seconds
	 * @returns delta time in seconds
	 */
	inline float getDeltaTimeSeconds() {
		return static_cast<float>(getDeltaTime()) / 1000.0f;
	}

	/**
	 * @returns avarage fps
	 */
	inline float getFPS() {
		return fps;
	}

	/**
	 * @returns avarage fps
	 */
	inline float getAvarageFPS() {
		return avarageFPS;
	}

	/**
	 * Updates timing
	 */
	void update();
};
