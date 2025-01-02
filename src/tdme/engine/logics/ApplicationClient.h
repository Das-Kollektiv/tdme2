#pragma once

#include <memory>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/physics/World.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>

#include <yannet/network/udpclient/UDPClient.h>

using std::vector;
using std::unique_ptr;

using tdme::engine::logics::Context;
using tdme::engine::logics::Logic;
using tdme::engine::physics::World;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;

using yannet::network::udpclient::UDPClient;

/**
 * Application client
 * @author Andreas Drewke
 */
class tdme::engine::logics::ApplicationClient: public Thread {
public:
	// forbid class copy
	FORBID_CLASS_COPY(ApplicationClient)

	/**
	 * Public constructor
	 * @param context context
	 * @param udpClient UDP client
	 */
	ApplicationClient(Context* context, UDPClient* udpClient = nullptr);

	/**
	 * Public constructor
	 */
	virtual ~ApplicationClient();

	/**
	 * @return mutex
	 */
	inline Mutex* getMutex() {
		return &mutex;
	}

	/**
	 * @return audio gain
	 */
	inline float getAudioGain() {
		return audioGain;
	}

	/**
	 * Set audio gain
	 * @param gain gain
	 */
	void setAudioGain(float gain) {
		this->audioGain = gain;
	}

	/**
	 * @return context
	 */
	inline Context* getContext() {
		return context.get();
	}

	/**
	 * Collect HID events to pass to logics that have handling HID events enabled
	 * @param mouseEvents mouse events
	 * @param keyEvents keyboard events
	 */
	void handleHIDEvents(vector<GUIMouseEvent>& mouseEvents, vector<GUIKeyboardEvent>& keyEvents);

	/**
	 * Updates engine and audio to context engine and audio instances
	 */
	void update();

private:
	struct QueuedSound {
		QueuedSound(
			const string& gameLogicId,
			const string& id,
			float gain,
			float pitch,
			bool ignoreIfPlaying,
			bool attachedToLogic,
			const Vector3& position,
			float distanceFromCamera
		):
			gameLogicId(gameLogicId),
			id(id),
			gain(gain),
			pitch(pitch),
			ignoreIfPlaying(ignoreIfPlaying),
			attachedToLogic(attachedToLogic),
			position(position),
			distanceFromCamera(distanceFromCamera)
		{}
		string gameLogicId;
		string id;
		float gain;
		float pitch;
		bool ignoreIfPlaying;
		bool attachedToLogic;
		Vector3 position;
		float distanceFromCamera;
	};

	struct ActiveSound {
		string id;
		bool attachedToLogic;
		string gameLogicId;
	};

	vector<QueuedSound> queuedSounds;
	unordered_map<string, ActiveSound> activeSounds;

	// overridden methods
	virtual void run() override;

	/**
	 * Handle in logic network packets
	 * @param logics logics
	 * @param inGameNetworkPackets incoming logic network packets
	 */
	void handleInNetworkPackets(const vector<Logic*>& logics, vector<LogicNetworkPacket>& inLogicNetworkPackets);

private:
	unique_ptr<Context> context;
	Mutex mutex;
	unique_ptr<UDPClient> udpClient;
	float audioGain { 1.0f };
};
