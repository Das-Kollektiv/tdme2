#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/physics/World.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/network/udpclient/UDPClient.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>

using std::vector;

using tdme::engine::logics::Context;
using tdme::engine::logics::Logic;
using tdme::engine::physics::World;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::network::udpclient::UDPClient;
using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;

/**
 * Application client
 * @author Andreas Drewke
 */
class tdme::engine::logics::ApplicationClient: public Thread {
public:
	/**
	 * Public constructor
	 * @param context context
	 * @param udpClient UDP client
	 */
	ApplicationClient(Context* context, UDPClient* udpClient = nullptr);

	/**
	 * @return mutex
	 */
	Mutex* getMutex();

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
		inline static bool compare(QueuedSound& queuedSound1, QueuedSound& queuedSound2) {
			return queuedSound1.distanceFromCamera < queuedSound2.distanceFromCamera;
		}
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
	Context* context { nullptr };
	Mutex mutex;
	UDPClient* udpClient { nullptr };
	float audioGain { 1.0f };
};
