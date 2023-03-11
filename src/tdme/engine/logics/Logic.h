#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/Time.h>

using std::vector;

using tdme::engine::logics::Context;
using tdme::engine::physics::World;
using tdme::engine::Engine;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::utilities::MiniScript;
using tdme::utilities::Time;

/**
 * Logic
 * @author Andreas Drewke
 */
class tdme::engine::logics::Logic {
public:
	struct QueuedSound {
		QueuedSound(
			const string& id,
			bool attachedToLogic,
			const Vector3& position,
			int64_t timeIssuedAt,
			int timeDelay,
			float gain,
			float pitch,
			bool ignoreIfPlaying
		):
			id(id),
			attachedToLogic(attachedToLogic),
			position(position),
			timeIssuedAt(timeIssuedAt),
			timeDelay(timeDelay),
			gain(gain),
			pitch(pitch),
			ignoreIfPlaying(ignoreIfPlaying)
		{}
		string id;
		bool attachedToLogic;
		Vector3 position;
		int64_t timeIssuedAt;
		int timeDelay;
		float gain;
		float pitch;
		bool ignoreIfPlaying;
	};

	struct SignalStruct {
		SignalStruct(
			const string& signal,
			const vector<MiniScript::ScriptVariable>& arguments
		): signal(signal), arguments(arguments) {}
		string signal;
		vector<MiniScript::ScriptVariable> arguments;
	};
	vector<SignalStruct> signals;

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
	 * Update engine
	 */
	virtual void updateEngine() = 0;

	/**
	 * Update logic
	 */
	virtual void updateLogic() = 0;

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
	 * On logic added
	 */
	virtual void onLogicAdded();

	/**
	 * On logics processed
	 */
	virtual void onLogicsProcessed();

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
		queuedSounds.emplace_back(
			id,
			true,
			Vector3(),
			Time::getCurrentMillis(),
			delay,
			gain,
			pitch,
			ignoreIfPlaying
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
		queuedSounds.emplace_back(
			id,
			false,
			position,
			Time::getCurrentMillis(),
			delay,
			gain,
			pitch,
			ignoreIfPlaying
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
	 * Returns if a signal is in signal queue
	 * @return has signal
	 */
	inline bool hasSignal() {
		return signals.empty() == false;
	}

	/**
	 * Add signal
	 * @param signal signal
	 * @param arguments arguments
	 */
	inline void addSignal(const string& signal, const vector<MiniScript::ScriptVariable>& arguments) {
		signals.emplace_back(
			signal,
			arguments
		);
	}

	/**
	 * Get signal name from first signal in signal queue
	 * @return signal name
	 */
	inline const string getSignalName() {
		if (signals.empty() == true) return string();
		return signals[0].signal;
	}

	/**
	 * Get signal argument count
	 * @return signal argument count
	 */
	inline int getSignalArgumentCount() {
		if (signals.empty() == true) return 0;
		return signals[0].arguments.size();
	}

	/**
	 * Get signal argument
	 * @return signal argument at given index
	 */
	inline MiniScript::ScriptVariable getSignalArgument(int idx) {
		if (signals.empty() == true) return MiniScript::ScriptVariable();
		if (idx >= signals[0].arguments.size()) return MiniScript::ScriptVariable();
		return signals[0].arguments[idx];
	}

	/**
	 * Remove first signal from signal queue
	 */
	inline void removeSignal() {
		if (signals.empty() == true) return;
		signals.erase(signals.begin());
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
