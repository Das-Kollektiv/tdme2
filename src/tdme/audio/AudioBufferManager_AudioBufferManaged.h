#pragma once

#include <string>

#include <fwd-tdme.h>
#include <tdme/audio/fwd-tdme.h>

using std::wstring;

using tdme::audio::AudioBufferManager;

/** 
 * Managed audio buffer entity
 * @author Andreas Drewke
 */
class tdme::audio::AudioBufferManager_AudioBufferManaged
{
	friend class AudioBufferManager;

public: /* package */
	wstring id {  };
	int32_t alId {  };
	int32_t referenceCounter {  };

public: /* protected */

	/** 
	 * @return audio buffer id
	 */
	virtual const wstring& getId();

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

private:
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
	 * @param referenceCounter
	 */
	AudioBufferManager_AudioBufferManaged(AudioBufferManager* audioBufferManager, const wstring& id, int32_t alId);

private:
	AudioBufferManager* audioBufferManager;
};
