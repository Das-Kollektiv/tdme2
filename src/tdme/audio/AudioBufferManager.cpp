#include <tdme/audio/AudioBufferManager.h>

#include <map>
#include <string>

#include <tdme/audio/Audio.h>
#include <tdme/audio/AudioBufferManager_AudioBufferManaged.h>
#include <tdme/utils/Console.h>

using std::map;
using std::string;

using tdme::audio::AudioBufferManager;
using tdme::audio::Audio;
using tdme::audio::AudioBufferManager_AudioBufferManaged;
using tdme::utils::Console;

AudioBufferManager::AudioBufferManager() 
{
}

AudioBufferManager_AudioBufferManaged* AudioBufferManager::addAudioBuffer(const wstring& id)
{
	auto audioBufferManagedIt = audioBuffers.find(id);
	AudioBufferManager_AudioBufferManaged* audioBufferManaged = audioBufferManagedIt != audioBuffers.end()?audioBufferManagedIt->second:nullptr;
	if (audioBufferManaged != nullptr) {
		audioBufferManaged->incrementReferenceCounter();
		return audioBufferManaged;
	}
	audioBufferManaged = new AudioBufferManager_AudioBufferManaged(this, id, Audio::ALBUFFERID_NONE);
	audioBufferManaged->incrementReferenceCounter();
	audioBuffers[audioBufferManaged->getId()] = audioBufferManaged;
	return audioBufferManaged;
}

bool AudioBufferManager::removeAudioBuffer(const wstring& id)
{
	auto audioBufferManagedIt = audioBuffers.find(id);
	AudioBufferManager_AudioBufferManaged* audioBufferManaged = audioBufferManagedIt != audioBuffers.end()?audioBufferManagedIt->second:nullptr;
	if (audioBufferManaged != nullptr) {
		if (audioBufferManaged->decrementReferenceCounter()) {
			audioBuffers.erase(audioBufferManagedIt);
			delete audioBufferManaged;
			return true;
		} else {
			return false;
		}
	}
	Console::println(wstring(L"Warning: audio buffer not loaded by audio buffer manager"));
	return false;
}
