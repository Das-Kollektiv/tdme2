#include <agui/audio/AudioBufferManager.h>

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/audio/Audio.h>
#include <agui/utilities/Console.h>

using std::string;
using std::unordered_map;

using agui::audio::Audio;
using agui::audio::AudioBufferManager;
using agui::utilities::Console;

AudioBufferManager::ManagedAudioBuffer* AudioBufferManager::addAudioBuffer(const string& id)
{
	// check if we already manage this audio buffer
	auto managedAudioBufferIt = audioBuffers.find(id);
	ManagedAudioBuffer* managedAudioBuffer = managedAudioBufferIt != audioBuffers.end()?managedAudioBufferIt->second:nullptr;
	if (managedAudioBuffer != nullptr) {
		managedAudioBuffer->incrementReferenceCounter();
		// yep, return buffer
		return managedAudioBuffer;
	}
	// not yet, create managed audio buffer with no AL id attached yet
	managedAudioBuffer = new ManagedAudioBuffer(this, id, Audio::ALBUFFERID_NONE);
	managedAudioBuffer->incrementReferenceCounter();
	// add it to our audioBuffers
	audioBuffers[managedAudioBuffer->getId()] = managedAudioBuffer;
	// return audio buffer
	return managedAudioBuffer;
}

bool AudioBufferManager::removeAudioBuffer(const string& id)
{
	auto managedAudioBufferIt = audioBuffers.find(id);
	auto managedAudioBuffer = managedAudioBufferIt != audioBuffers.end()?managedAudioBufferIt->second:nullptr;
	if (managedAudioBuffer != nullptr) {
		if (managedAudioBuffer->decrementReferenceCounter()) {
			// remove from our list
			audioBuffers.erase(managedAudioBufferIt);
			delete managedAudioBuffer;
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
