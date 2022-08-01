#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/utilities/Time.h>

using std::vector;

using tdme::engine::logics::Context;
using tdme::engine::physics::World;
using tdme::engine::Engine;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::utilities::Time;

/**
 * Logic
 * @author Andreas Drewke
 */
class tdme::engine::logics::Logic {
public:
	struct QueuedSound {
		string id;
		bool attachedToLogic;
		Vector3 position;
		int64_t timeIssuedAt;
		int timeDelay;
		float gain;
		float pitch;
		bool ignoreIfPlaying;
	};

	/**
	 * Public constructor
	 * @param context context
	 * @param id id
	 * @param handlingHIDInput is handling hid input
	 */
	Logic(Context* context, const string& id, bool handlingHIDInput);

	/**
	 * Destructor
	 */
	virtual ~Logic();

	/**
	 * @return context
	 */
	inline Context* getContext() {
		return context;
	}

	/**
	 * @return id
	 */
	inline const string& getId() {
		return id;
	}

	/**
	 * Update engine entities
	 */
	virtual void updateEngine() = 0;

	/**
	 * Update game logic
	 */
	virtual void updateGameLogic() = 0;

	/**
	 * @return if handling human interface devices input
	 */
	inline bool isHandlingHIDInput() {
		return handlingHIDInput;
	}

	/**
	 * Handle HID events
	 * @param mouseEvents mouse events
	 * @param keyEvents keyboard events
	 */
	virtual void handleHIDEvents(vector<GUIMouseEvent>& mouseEvents, vector<GUIKeyboardEvent>& keyEvents);

	/**
	 * On game logic added
	 */
	virtual void onGameLogicAdded();

	/**
	 * On game logics processed
	 */
	virtual void onGameLogicsProcessed();

	/**
	 * TODO: updated sounds that are already playing
	 * Queue sound
	 * @param id sound id
	 * @param delay delay
	 * @param gain gain
	 * @param pitch pitch
	 * @param ignoreIfPlaying ignore if already playing
	 */
	inline void queueSound(const string& id, int delay = 0, float gain = 1.0, float pitch = 1.0, bool ignoreIfPlaying = false) {
		queuedSounds.push_back(
			{
				.id = id,
				.attachedToLogic = true,
				.position = Vector3(),
				.timeIssuedAt = Time::getCurrentMillis(),
				.timeDelay = delay,
				.gain = gain,
				.pitch = pitch,
				.ignoreIfPlaying = ignoreIfPlaying
			}
		);
	}

	/**
	 * TODO: updated sounds that are already playing
	 * Queue sound with position
	 * @param id sound id
	 * @param position position
	 * @param delay delay
	 * @param gain gain
	 * @param pitch pitch
	 * @param ignoreIfPlaying ignore if already playing
	 */
	inline void queueSound(const string& id, const Vector3& position, int delay = 0, float gain = 1.0, float pitch = 1.0, bool ignoreIfPlaying = false) {
		queuedSounds.push_back(
			{
				.id = id,
				.attachedToLogic = false,
				.position = position,
				.timeIssuedAt = Time::getCurrentMillis(),
				.timeDelay = delay,
				.gain = gain,
				.pitch = pitch,
				.ignoreIfPlaying = ignoreIfPlaying
			}
		);
	}

	/**
	 * @return queued sounds associated with this game logic
	 */
	inline const vector<QueuedSound>& getQueuedSounds() {
		return queuedSounds;
	}

	/**
	 * Clear queued sounds
	 */
	inline void clearQueuedSounds() {
		queuedSounds.clear();
	}

	/**
	 * Set queued sounds
	 * @param queuedSounds queued sounds
	 */
	inline void setQueuedSounds(const vector<QueuedSound>& queuedSounds) {
		this->queuedSounds = queuedSounds;
	}

	/**
	 * Log state
	 */
	virtual void logState(int indent = 0);

protected:
	Context* context;
	string id;
	bool handlingHIDInput;
	vector<QueuedSound> queuedSounds;

};
