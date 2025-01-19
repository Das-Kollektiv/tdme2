#include <tdme/audio/AudioBufferManager.h>

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/audio/Audio.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::unordered_map;

using tdme::audio::Audio;
using tdme::audio::AudioBufferManager;
using tdme::utilities::Console;

AudioBufferManager::ManagedAudioBuffer* AudioBufferManager::addAudioBuffer(const string& id)
{
	// check if we already manage this audio buffer
	auto audioBufferManagedIt = audioBuffers.find(id);
	ManagedAudioBuffer* audioBufferManaged = audioBufferManagedIt != audioBuffers.end()?audioBufferManagedIt->second:nullptr;
	if (audioBufferManaged != nullptr) {
		audioBufferManaged->incrementReferenceCounter();
		// yep, return buffer
		return audioBufferManaged;
	}
	// not yet, create managed audio buffer with no AL id attached yet
	audioBufferManaged = new ManagedAudioBuffer(this, id, Audio::ALBUFFERID_NONE);
	audioBufferManaged->incrementReferenceCounter();
	// add it to our audioBuffers
	audioBuffers[audioBufferManaged->getId()] = audioBufferManaged;
	// return audio buffer
	return audioBufferManaged;
}

bool AudioBufferManager::removeAudioBuffer(const string& id)
{
	auto audioBufferManagedIt = audioBuffers.find(id);
	ManagedAudioBuffer* audioBufferManaged = audioBufferManagedIt != audioBuffers.end()?audioBufferManagedIt->second:nullptr;
	if (audioBufferManaged != nullptr) {
		if (audioBufferManaged->decrementReferenceCounter()) {
			// remove from our list
			audioBuffers.erase(audioBufferManagedIt);
			delete audioBufferManaged;
			// report to called that this audio buffer can be removed
			return true;
		} else {
			return false;
		}
	}
	// should never happen
	Console::printLine(string("Warning: audio buffer not loaded by audio buffer manager"));
	return false;
}
