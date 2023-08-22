#pragma once

#if defined(__APPLE__)
	#include <OpenAL/alc.h>
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__linux__) || defined(_WIN32) || defined(__HAIKU__)
	#include <AL/alc.h>
#endif

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/audio/AudioBufferManager.h>
#include <tdme/math/Vector3.h>

using std::string;
using std::unordered_map;

using tdme::audio::AudioBufferManager;
using tdme::audio::AudioEntity;
using tdme::math::Vector3;

/**
 * Interface to audio module
 * @author Andreas Drewke
 */
class tdme::audio::Audio final
{
	friend class AudioBufferManager;
	friend class AudioStream;
	friend class Sound;

private:
	static constexpr uint32_t ALBUFFERID_NONE { 0 };
	static constexpr uint32_t ALSOURCEID_NONE { 0 };
	STATIC_DLL_IMPEXT static Audio* instance;

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

public:

	/**
	 * @return audio singleton instance
	 */
	inline static Audio* getInstance() {
		if (Audio::instance == nullptr) {
			Audio::instance = new Audio();
		}
		return Audio::instance;
	}

	/**
	 * @return listener position
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
	 * @return listener velocity
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
	 * @return listener orientation at
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
	 * @return listener orientation up
	 */
	inline const Vector3& getListenerOrientationUp() const {
		return listenerOrientationUp;
	}

	/**
	 * Set listener orientation up
	 * @return listener orientation up
	 */
	inline void setListenerOrientationUp(const Vector3& listenerOrientationUp) {
		this->listenerOrientationUp = listenerOrientationUp;
	}

	/**
	 * Returns an audio entity identified by given id
	 * @param id id
	 * @return audio entity
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
	 * Shuts the audio down
	 */
	void shutdown();

	/**
	 * Update and transfer audio entity states to open AL
	 */
	void update();

};
