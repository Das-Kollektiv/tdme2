#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/audio/fwd-tdme.h>

using std::string;

using tdme::audio::AudioBufferManager;

/** 
 * Managed audio buffer entity
 * @author Andreas Drewke
 */
class tdme::audio::AudioBufferManager_AudioBufferManaged
{
	friend class AudioBufferManager;
	friend class Sound;

private:
	string id {  };
	int32_t alId {  };
	int32_t referenceCounter {  };

	/** 
	 * @return audio buffer id
	 */
	virtual const string& getId();

	/** 
	 * @return Open AL id
	 */
	virtual int32_t getAlId();

	/** 
	 * Set up Open AL audio buffer id
	 * @param al Id
	 */
	virtual void setAlId(int32_t alId);

	/** 
	 * @return reference counter
	 */
	virtual int32_t getReferenceCounter();

	/** 
	 * decrement reference counter
	 * @return if reference counter = 0
	 */
	bool decrementReferenceCounter();

	/** 
	 * increment reference counter
	 */
	void incrementReferenceCounter();

	/**
	 * Protected constructor
	 * @param audio buffer manager
	 * @param id
	 * @param Open AL id
	 */
	AudioBufferManager_AudioBufferManaged(AudioBufferManager* audioBufferManager, const string& id, int32_t alId);

	// variables
	AudioBufferManager* audioBufferManager;
};
