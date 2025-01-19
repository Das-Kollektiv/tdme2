#pragma once

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/audio/fwd-tdme.h>

using std::string;
using std::unordered_map;

/**
 * Audio buffer manager
 * @author Andreas Drewke
 */
class tdme::audio::AudioBufferManager final
{
	friend class Audio;
	friend class Sound;
public:
	/**
	 * Managed audio buffer
	 */
	class ManagedAudioBuffer
	{
		friend class AudioBufferManager;
		friend class Sound;

	private:
		AudioBufferManager* audioBufferManager;
		string id;
		uint32_t alId { 0 };
		int32_t referenceCounter { 0 };

		// forbid class copy
		FORBID_CLASS_COPY(ManagedAudioBuffer)

		/**
		 * Protected constructor
		 * @param audioBufferManager audio buffer manager
		 * @param id id
		 * @param alId OpenAL buffer id
		 */
		inline ManagedAudioBuffer(AudioBufferManager* audioBufferManager, const string& id, int32_t alId):
			audioBufferManager(audioBufferManager),
			id(id),
			alId(alId) {
			//
		}

		/**
		 * @return audio buffer id
		 */
		inline const string& getId() {
			return id;
		}

		/**
		 * @return OpenAL buffer id
		 */
		inline uint32_t getAlId() {
			return alId;
		}

		/**
		 * Set up OpenAL audio buffer id
		 * @param alId OpenAL buffer id
		 */
		inline void setAlId(uint32_t alId) {
			this->alId = alId;
		}

		/**
		 * @return reference counter
		 */
		inline int32_t getReferenceCounter() {
			return referenceCounter;
		}

		/**
		 * decrement reference counter
		 * @return if reference counter = 0
		 */
		inline bool decrementReferenceCounter() {
			referenceCounter--;
			return referenceCounter == 0;
		}

		/**
		 * increment reference counter
		 */
		inline void incrementReferenceCounter() {
			referenceCounter++;
		}
	};

private:
	unordered_map<string, ManagedAudioBuffer*> audioBuffers;

	// forbid class copy
	FORBID_CLASS_COPY(AudioBufferManager)

	/**
	 * Private constructor
	 */
	inline AudioBufferManager() {}

	/**
	 * Adds a audio buffer to manager / open al stack
	 * @param id id
	 * @return audio buffer managed
	 */
	ManagedAudioBuffer* addAudioBuffer(const string& id);

	/**
	 * Removes a texture from manager / open gl stack
	 * @param id id
	 * @return true if caller has to remove the audio buffer from open AL
	 */
	bool removeAudioBuffer(const string& id);

};
