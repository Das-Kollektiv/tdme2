#pragma once

#include <map>
#include <string>

#include <tdme.h>
#include <tdme/audio/fwd-tdme.h>

using std::map;
using std::wstring;

using tdme::audio::AudioBufferManager_AudioBufferManaged;

/** 
 * Audio buffer manager
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::audio::AudioBufferManager final
{
	friend class AudioBufferManager_AudioBufferManaged;

private:
	map<wstring, AudioBufferManager_AudioBufferManaged*> audioBuffers;

public: /* protected */

	/** 
	 * Adds a audio buffer to manager / open al stack
	 * @param id
	 * @return audio buffer managed
	 */
	AudioBufferManager_AudioBufferManaged* addAudioBuffer(const wstring& id);

	/** 
	 * Removes a texture from manager / open gl stack
	 * @param id
	 * @return true if caller has to remove the audio buffer from open AL
	 */
	bool removeAudioBuffer(const wstring& id);

	/**
	 * Protected constructor
	 */
	AudioBufferManager();
};
