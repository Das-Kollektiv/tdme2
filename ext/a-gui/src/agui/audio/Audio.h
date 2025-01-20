#pragma once

#if defined(__APPLE__)
	#include <OpenAL/alc.h>
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__linux__) || defined(_WIN32) || defined(__HAIKU__)
	#include <AL/alc.h>
#endif

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/audio/fwd-agui.h>
#include <agui/audio/AudioBufferManager.h>
#include <agui/math/Vector3.h>

using std::string;
using std::unordered_map;

// namespaces
namespace agui {
namespace audio {
	using ::agui::math::Vector3;
}
}

/**
 * Interface to audio module
 * @author Andreas Drewke
 */
class agui::audio::Audio final
{
	friend class AudioBufferManager;
	friend class AudioStream;
	friend class Sound;

private:
	static constexpr uint32_t ALBUFFERID_NONE { 0 };
	static constexpr uint32_t ALSOURCEID_NONE { 0 };
	AGUI_STATIC_DLL_IMPEXT static Audio* instance;

	ALCdevice* device { nullptr };
	ALCcontext* context { nullptr };

	unordered_map<string, AudioEntity*> audioEntities;

	AudioBufferManager audioBufferManager;
	Vector3 listenerPosition;
	Vector3 listenerVelocity;
	Vector3 listenerOrientationAt;
	Vector3 listenerOrientationUp;

	// forbid class copy
	FORBID_CLASS_COPY(Audio)

	/**
	 * Private constructor
	 */
	Audio();

	/**
	 * Private destructor
	 */
	~Audio();

public:

	/**
	 * @returns audio singleton instance
	 */
	inline static Audio* getInstance() {
		if (Audio::instance == nullptr) {
			Audio::instance = new Audio();
		}
		return Audio::instance;
	}

	/**
	 * Shuts the audio down
	 */
	static void shutdown();

	/**
	 * @returns listener position
	 */
	inline const Vector3& getListenerPosition() const {
		return listenerPosition;
	}

	/**
	 * Set listener position
	 * @param listenerPosition listener position
	 */
	inline void setListenerPosition(const Vector3& listenerPosition) {
		this->listenerPosition = listenerPosition;
	}

	/**
	 * @returns listener velocity
	 */
	inline const Vector3& getListenerVelocity() const {
		return listenerVelocity;
	}

	/**
	 * Set listener velocity
	 * @param listenerVelocity listener velocity
	 */
	inline void setListenerVelocity(const Vector3& listenerVelocity) {
		this->listenerVelocity = listenerVelocity;
	}

	/**
	 * @returns listener orientation at
	 */
	inline const Vector3& getListenerOrientationAt() const {
		return listenerOrientationAt;
	}

	/**
	 * Set listener orientation at
	 * @param listenerOrientationAt listener orientation at
	 */
	inline void setListenerOrientationAt(const Vector3& listenerOrientationAt) {
		this->listenerOrientationAt = listenerOrientationAt;
	}

	/**
	 * @returns listener orientation up
	 */
	inline const Vector3& getListenerOrientationUp() const {
		return listenerOrientationUp;
	}

	/**
	 * Set listener orientation up
	 * @returns listener orientation up
	 */
	inline void setListenerOrientationUp(const Vector3& listenerOrientationUp) {
		this->listenerOrientationUp = listenerOrientationUp;
	}

	/**
	 * Returns an audio entity identified by given id
	 * @param id id
	 * @returns audio entity
	 */
	inline AudioEntity* getEntity(const string& id) {
		auto audioEntityIt = audioEntities.find(id);
		if (audioEntityIt == audioEntities.end()) return nullptr;
		return audioEntityIt->second;
	}

	/**
	 * Adds a audio entity
	 * @param entity audio entity
	 */
	void addEntity(AudioEntity* entity);

	/**
	 * Removes an audio entity
	 * @param id id
	 */
	void removeEntity(const string& id);

	/**
	 * Clears all audio entities
	 */
	void reset();

	/**
	 * Update and transfer audio entity states to open AL
	 */
	void update();

};
